using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Scan_ADC_v1_30
{
    /// <summary>
    /// Holds static functions to generate S and Z plane transfer functions from filter parameters.
    /// 
    /// Algorithms are from JAPR-17 UAB SC-Filter Design.
    /// </summary>
    public class BiquadMaker
    {
        /// <summary>
        /// Make a low pass filter Z-plane transfer function.
        /// </summary>
        /// <param name="f0">3Db frequency</param>
        /// <param name="fNotch">Notch frequency</param>
        /// <param name="fSample">Sampling frequency</param>
        /// <returns>Z-plane transfer function</returns>
        static public Biquad MakeLowpass(double f0, double fNotch, double fSample)
        {
            double omega0 = Prewarp(f0, fSample);
            double omegaNotch = Prewarp(fNotch, fSample);

            Biquad sPlaneXfer = MakeSplaneLowpass(omega0, omegaNotch);

            Biquad zPlaneXfer = BilinearXform(sPlaneXfer, fSample);

            return zPlaneXfer;
        }

        /// <summary>
        /// Make a high pass filter Z-plane transfer function.
        /// </summary>
        /// <param name="f0">3Db frequency</param>
        /// <param name="fNotch">Notch frequency</param>
        /// <param name="fSample">Sampling frequency</param>
        /// <returns>Z-plane transfer function</returns>
        static public Biquad MakeHighpass(double f0, double fNotch, double fSample)
        {
            double omega0 = Prewarp(f0, fSample);
            double omegaNotch = Prewarp(fNotch, fSample);

            Biquad sPlaneXfer = MakeSplaneHighpass(omega0, omegaNotch);

            Biquad zPlaneXfer = BilinearXform(sPlaneXfer, fSample);

            return zPlaneXfer;
        }

        /// <summary>
        /// Make a band pass filter Z-plane transfer function.
        /// </summary>
        /// <param name="f1">Low 3Db frequency</param>
        /// <param name="f2">High 3Db frequency</param>
        /// <param name="fSample">Sampling frequency</param>
        /// <returns>Z-plane transfer function</returns>
        static public Biquad MakeBandpass(double f1, double f2, double fSample)
        {
            double omega1 = Prewarp(f1, fSample);
            double omega2 = Prewarp(f2, fSample);

            Biquad sPlaneXfer = MakeSplaneBandpass(omega1, omega2);

            Biquad xPlaneXfer = BilinearXform(sPlaneXfer, fSample);

            return xPlaneXfer;
        }

        /// <summary>
        /// Make a band stop filter Z-plane transfer function.
        /// </summary>
        /// <param name="f0">Notch frequency</param>
        /// <param name="f1or2">Low or high 3Db frequency</param>
        /// <param name="fSample">Sampling frequency</param>
        /// <returns>Z-plane transfer function</returns>
        static public Biquad MakeBandstop(double f0, double f1or2, double fSample)
        {
            double omega0 = Prewarp(f0, fSample);
            double omega1or2 = Prewarp(f1or2, fSample);

            Biquad sPlaneXfer = MakeSplaneBandstop(omega0, omega1or2);

            Biquad zPlaneXfer = BilinearXform(sPlaneXfer, fSample);

            return zPlaneXfer;
        }

        /// <summary>
        /// Make a low pass filter S-plane transfer function.
        /// </summary>
        /// <param name="omega0">3Db frequency</param>
        /// <param name="omegaNotch">Notch frequency</param>
        /// <returns>S-plane transfer function</returns>
        static public Biquad MakeSplaneLowpass(double omega0, double omegaNotch)
        {
            double k = (omega0 * omega0) / (omegaNotch * omegaNotch);
            double d = Math.Sqrt(2.0) * (1 - k);

            Biquad sPlaneXfer = new Biquad
            {
                Num2 = k,
                Num1 = 0.0,
                Num0 = k * omegaNotch * omegaNotch,
                Den2 = 1.0,
                Den1 = omega0 * d,
                Den0 = omega0 * omega0
            };

            return sPlaneXfer;
        }

        /// <summary>
        /// Make a high pass filter S-plane transfer function
        /// </summary>
        /// <param name="omega0">3Db frequency</param>
        /// <param name="omegaNotch">Notch frequency</param>
        /// <returns>S-plane transfer function</returns>
        static public Biquad MakeSplaneHighpass(double omega0, double omegaNotch)
        {
            double k = 1.0;
            double d = Math.Sqrt(2.0)
                * Math.Abs((omegaNotch * omegaNotch) / (omega0 * omega0) - 1);

            Biquad sPlaneXfer = new Biquad
            {
                Num2 = k,
                Num1 = 0.0,
                Num0 = k * omegaNotch * omegaNotch,
                Den2 = 1.0,
                Den1 = omega0 * d,
                Den0 = omega0 * omega0
            };

            return sPlaneXfer;
        }

        /// <summary>
        ///  Make a band pass filter S-plane transfer function.
        /// </summary>
        /// <param name="omega1">Low 3Db frequency</param>
        /// <param name="omega2">High 3Db frequency</param>
        /// <returns>S-plane transfer function</returns>
        static public Biquad MakeSplaneBandpass(double omega1, double omega2)
        {
            double omega0 = Math.Sqrt(omega1 * omega2);
            double d = (omega2 - omega1) / omega0;

            Biquad sPlaneXfer = new Biquad
            {
                Num2 = 0.0,
                Num1 = omega0 * d,
                Num0 = 0.0,
                Den2 = 1.0,
                Den1 = omega0 * d,
                Den0 = omega0 * omega0
            };

            return sPlaneXfer;
        }

        /// <summary>
        /// Make a band stop filter S-plane transfer function.
        /// </summary>
        /// <param name="omega0">Notch frequency</param>
        /// <param name="omega1or2">Low or high 3Db frequency</param>
        /// <returns>S-plane transfer function</returns>
        static public Biquad MakeSplaneBandstop(double omega0, double omega1or2)
        {
            double omega1;
            double omega2;

            if (omega0 < omega1or2)
            {
                omega2 = omega1or2;
                omega1 = (omega0 * omega0) / omega2;
            }
            else
            {
                omega1 = omega1or2;
                omega2 = (omega0 * omega0) / omega1;
            }

            double d = (omega2 - omega1) / omega0;

            Biquad sPlaneXfer = new Biquad
            {
                Num2 = 1.0,
                Num1 = 0.0,
                Num0 = omega0 * omega0,
                Den2 = 1.0,
                Den1 = omega0 * d,
                Den0 = omega0 * omega0
            };

            return sPlaneXfer;
        }

        /// <summary>
        /// Pre-warp frequency for bilinear transform at given sampling frequency.
        /// </summary>
        /// <param name="freq">Target frequency</param>
        /// <param name="fSample">Sampling frequency</param>
        /// <returns>Pre-warped frequency</returns>
        static public double Prewarp(double freq, double fSample)
        {
            double period = 1 / fSample;
            double omega = (2.0 / period) * Math.Tan(Math.PI * freq * period);
            return omega;
        }

        /// <summary>
        /// Apply bilinear transform to S-plane transfer function.
        /// </summary>
        /// <param name="sPlaneXfer">S-plane transfer function</param>
        /// <param name="fSample">Sampling frequency</param>
        /// <returns>Z-plane transfer function</returns>
        static public Biquad BilinearXform(Biquad sPlaneXfer, double fSample)
        {
            double period = 1.0 / fSample;

            double a0;
            double a1;
            double a2;
            BilinearXHalf(sPlaneXfer.Num0, sPlaneXfer.Num1, sPlaneXfer.Num2,
                period, out a0, out a1, out a2);

            double b0;
            double b1;
            double b2;
            BilinearXHalf(sPlaneXfer.Den0, sPlaneXfer.Den1, sPlaneXfer.Den2,
                period, out b0, out b1, out b2);

            Biquad zPlaneXfer = new Biquad
            {
                Num0 = a0,
                Num1 = a1,
                Num2 = a2,
                Den0 = b0,
                Den1 = b1,
                Den2 = b2,
            };

            return zPlaneXfer;
        }

        /// <summary>
        /// Apply bilinear transform to quadratic function.
        /// 
        /// See JAPR-17 page 12
        /// </summary>
        static public void BilinearXHalf(
            double a0, double a1, double a2, double t,
            out double c0, out double c1, out double c2)
        {
            c2 = t * t * a0 + 2.0 * t * a1 + 4.0 * a2;
            c1 = 2.0 * t * t * a0 - 8.0 * a2;
            c0 = t * t * a0 - 2.0 * t * a1 + 4.0 * a2;
        }
    }
}
