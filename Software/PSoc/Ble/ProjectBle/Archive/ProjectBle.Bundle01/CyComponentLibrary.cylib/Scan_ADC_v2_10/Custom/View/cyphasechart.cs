/*******************************************************************************
* Copyright 2011-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Text;
using System.Numerics;

namespace Scan_ADC_v2_10
{
    public class CyPhaseChart : CyLineChart
    {
        private CyConfigModel m_config;
        public List<PointF> m_idealPhases;
        public List<PointF> m_uabPhases;
        public List<Tick> m_phaseTicks;
        public List<Tick> m_frequencyTicks;
        public int PointMax { get; set; }
        public int DecibelMin { get; set; }
        public float LogStartFrequency { get; set; }

        public CyPhaseChart(CyConfigModel config, string title, Font font, bool isDebug)
            : base(title, font, null, null, isDebug)
        {
            this.m_series = new List<DataSeries>();
            this.m_config = config;
            this.m_idealPhases = new List<PointF>();
            this.m_uabPhases = new List<PointF>();
            this.m_phaseTicks = new List<Tick>();
            this.m_frequencyTicks = new List<Tick>();
            this.PointMax = 300;
            this.DecibelMin = -30;
            // Should start at a power of 10 (0.1, 1, 10, etc) to make the math easier
            this.LogStartFrequency = 1; 
        }

        public override void Resize(RectangleF rect)
        {
            var idealBiquad = CyFilterUtils.GetIdealFilterBiquad(this.m_config);
            var uabBiquad = new Biquad();
            try
            {
                var uabCaps = this.m_config.GetUabFilterCaps(idealBiquad);
                uabBiquad = this.m_config.GetUabFilterBiquad(uabCaps, idealBiquad);
            }
            catch (CapacitorMapperException)
            {
                uabBiquad.Den0 = 1;
            }

            this.m_idealPhases = CalcPhaseResponse(idealBiquad);
            this.m_uabPhases = CalcPhaseResponse(uabBiquad);

            this.m_series = new List<DataSeries>();
            if (this.m_isDebug)
            {
                this.m_series.Add(new CyLineChart.DataSeries(
                    "Ideal", this.m_idealPhases, Color.LightBlue, 4f));
            }
            this.m_series.Add(new CyLineChart.DataSeries(
                "Actual", this.m_uabPhases, Color.Black, 2f));
            const float PI = (float)Math.PI;
            this.m_initialHull = new CyLineChart.Hull(0f, 0f, -PI, PI);

            base.Resize(rect);

            this.m_xTicks = CalcFrequencyTicks();
            this.m_yTicks = CalcPhaseTicks(
                this.m_initialHull.MinY, this.m_initialHull.MaxY);
        }

        private List<PointF> CalcPhaseResponse(Biquad biquad)
        {
            var phases = new List<PointF>();
            for (int pointNum = 0; pointNum < this.PointMax; pointNum++)
            {
                var omega = (Math.PI * pointNum) / this.PointMax;
                float omegaPrime = LinearToLogTransform((float)omega);
                var z = new Complex(Math.Cos(omegaPrime), Math.Sin(omegaPrime));
                // The UAB filter realization inverts the response,
                // so negate the biquad transfer function evaluation.
                var response = - biquad.EvaluateZ(z);
                // Switch cap filters add a 180 degree phase shift.
                response = -response;
                var phase = response.Phase;
                var point = new PointF((float)omega, (float)phase);
                phases.Add(point);
            }
            return phases;
        }

        /// <summary>
        /// Transform a linear scale to a log scale based on f(omega) = A * exp(B * omega)
        /// where f(pi) = pi and f(0) = this.LogStartFrequency * pi / (Fs/2).
        /// </summary>
        /// <param name="omega"></param>
        /// <returns></returns>
        private float LinearToLogTransform(float omega)
        {
            float B;
            float A;
            CalcLinearToLogParameters(out B, out A);

            return A * (float)(Math.Exp(B * omega));
        }

        private float LogToLinearTransform(float omega)
        {
            float B;
            float A;
            CalcLinearToLogParameters(out B, out A);

            return (float)Math.Log(omega / A) / B;
        }

        private void CalcLinearToLogParameters(out float B, out float A)
        {
            float N = this.PointMax;
            float sampleFreq = (float)this.m_config.FilterSample;
            float sampleFreq_div_2 = sampleFreq / 2;

            float X1 = (float)Math.PI;
            float Y1 = (float)Math.PI;
            float X2 = 0;
            float Y2 = (float)(this.LogStartFrequency * Math.PI / sampleFreq_div_2);

            B = (float)(Math.Log(Y1 / Y2) / (X1 - X2));
            A = (float)(Y1 / Math.Exp(B * X1));
        }

        /// <summary>
        /// Transform a linear scale to a log scale based on f(omega) = A * exp(B * omega)
        /// where f(pi) = pi and f(0) = this.LogStartFrequency * pi / (Fs/2).
        /// NOTE: This function is duplicated in cyamplitudechart.cs. Both functions should
        /// be refactored into one function and combined in a different file.
        /// </summary>
        /// <param name="omega"></param>
        /// <returns></returns>
        private List<CyLineChart.Tick> CalcFrequencyTicks()
        {
            var ticks = new List<CyLineChart.Tick>();

            float sampleFreq = (float)this.m_config.FilterSample;
            float sampleFreq_div_2 = sampleFreq / 2;
            float tolerance = 0.0001F;

            for (float f = this.LogStartFrequency; f < (sampleFreq_div_2 + tolerance); f *= 10)
            {
                float coord;
                string label = "";
                CyLineChart.Emphasis emphasis = CyLineChart.Emphasis.MINOR;
                bool breakNext = false;

                for (int decadeTick = 1; decadeTick < 10; decadeTick++)
                {
                    if (breakNext)
                    {
                        break;
                    }
                    var currentFreq = decadeTick * f;
                    var nextFreq = (decadeTick + 1) * f;

                    if (nextFreq > (sampleFreq_div_2 + tolerance))
                    {
                        breakNext = true;
                    }
                    // Add labeled, major tick at each decade and last tick
                    if ((decadeTick == 1) || (breakNext == true))
                    {
                        label = string.Format("{0} kHz", Math.Round(currentFreq));
                        emphasis = CyLineChart.Emphasis.MAJOR;
                    }
                    else
                    {
                        label = "";
                        emphasis = CyLineChart.Emphasis.MINOR;
                    }
                    // Scale by PI/(Fs/2)
                    float scaledFreq = (float)(currentFreq * Math.PI / sampleFreq_div_2);
                    coord = LogToLinearTransform(scaledFreq);
                    ticks.Add(new CyLineChart.Tick(coord, label, emphasis));
                }
            }


            return ticks;
        }

        private List<CyLineChart.Tick> CalcPhaseTicks(float minY, float maxY)
        {
            var ticks = new List<CyLineChart.Tick>();

            int tickMax = 8 + 1;
            int tickCycle = 2;

            for (int tickNum = 0; tickNum < tickMax; tickNum++)
            {
                float coord = (float)((tickNum * 2 * Math.PI) / (tickMax - 1));
                coord -= (float)Math.PI;
                string label = "";
                CyLineChart.Emphasis emphasis = CyLineChart.Emphasis.MINOR;
                if (tickNum % tickCycle == 0)
                {
                    int degrees = (360 * tickNum) / (tickMax - 1) - 180;
                    label = string.Format("{0}", degrees);
                    emphasis = CyLineChart.Emphasis.MAJOR;
                }
                ticks.Add(new CyLineChart.Tick(coord, label, emphasis));
            }

            return ticks;
        }
    }
}