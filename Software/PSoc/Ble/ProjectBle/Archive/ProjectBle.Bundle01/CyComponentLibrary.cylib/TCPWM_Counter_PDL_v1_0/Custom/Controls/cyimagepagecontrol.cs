/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Drawing;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;
using CyDesigner.Toolkit;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using TCPWM_Counter_PDL_v1_0.Utils;

namespace TCPWM_Counter_PDL_v1_0
{
    public class CyImagePageControl : CyImageDefaultPageControl, IDisposable
    {
        public CyImagePageControl(Image image, PictureBoxSizeMode sizeMode, bool onTop, SizeType sizeType, int height)
            : base(image, sizeMode, onTop, sizeType, height)
        {
            TypeSpecificControl.BackColor = Color.White;
        }

        public override void Refresh(CyQueryArgs args)
        {
            ICyInstQuery_v1 instQuery = args.InstQuery;
            uint period = CyParameters.GetPeriod(instQuery);
            uint compare0 = CyParameters.GetCompare0(instQuery);
            uint compare1 = CyParameters.GetCompare1(instQuery);
            bool compareSwap = CyParameters.GetCompareSwap(instQuery);
            CyEnums.CyCountDirection countDirection = CyParameters.GetCountDirection(instQuery);
            CyEnums.CyCompareOrCapture compareOrCapture = CyParameters.GetCompareOrCapture(instQuery);
            CyEnums.CyInterruptSources interruptSource = CyParameters.GetInterruptSource(instQuery);

            TypeSpecificControl.Size = Image.Size;
            UpdateDrawing(period, countDirection, compare0, compare1, compareSwap, compareOrCapture, interruptSource);
            base.Refresh(args);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                // dispose of managed disposable members
                Image.Dispose();
            }
            // release unmanaged resources
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        ~CyImagePageControl()
        {
            Dispose(false);
        }

        private void UpdateDrawing(uint period, CyEnums.CyCountDirection countDirection, uint compare0, uint compare1, bool compareSwap,
            CyEnums.CyCompareOrCapture compareOrCapture, CyEnums.CyInterruptSources interruptSource)
        {
            int prevY = 20;
            using (Bitmap updatedBitmap = new Bitmap(700, 500)) // this is more than maximum possible size
            using (Graphics g = Graphics.FromImage(updatedBitmap))
            using (CyWaveform waveform = new CyWaveform(g, updatedBitmap.Width, countDirection, period))
            {
                const int RECT_HEIGHT = 20;
                const int BREAK_LINE_STAIR = 3;
                const int MIN_CAPTURE_STAIR = 3;
                int breakLineY1 = 0;
                int breakLineY2 = 0;
                int[] captureStairs = new int[0];
                uint[] captureArrows = new uint[0];
                int linesDistance = CyWaveform.STAIR_HEIGHT / 2;

                CyGraphicsUtils.MakeHighQualityForDrawing(g);

                //
                // Calculate Capture line
                //
                switch (countDirection)
                {
                    case CyEnums.CyCountDirection.COUNT_UP:
                    case CyEnums.CyCountDirection.COUNT_DOWN:
                        uint[] periods = period >= MIN_CAPTURE_STAIR ? new uint[] { 1, period - 1 } : new uint[] { 1 };
                        captureStairs = waveform.GetStairsPositions(periods);
                        captureArrows = period >= MIN_CAPTURE_STAIR ? new uint[] { 1, period - 1 } : new uint[] { 1 };
                        break;
                    case CyEnums.CyCountDirection.COUNT_UPDOWN0:
                    case CyEnums.CyCountDirection.COUNT_UPDOWN1:
                        captureStairs = waveform.GetStairsPositions(new uint[] { 1 }, true);
                        captureArrows = new uint[] { 1 };
                        break;
                    default:
                        Debug.Fail("unhandled enum item.");
                        break;
                }

                switch (compareOrCapture)
                {
                    case CyEnums.CyCompareOrCapture.MODE_COMPARE:
                        //
                        // Draw period and compare rectangles
                        //
                        int rectWidth = updatedBitmap.Width - CyWaveform.LINES_X - 5;
                        waveform.DrawRectangle(rectWidth, RECT_HEIGHT, prevY, period.ToString(), "Period");
                        prevY += RECT_HEIGHT + linesDistance;
                        waveform.DrawRectangle(rectWidth, RECT_HEIGHT, prevY, compare0.ToString(), "Compare 0");
                        prevY += RECT_HEIGHT + linesDistance;
                        if (compareSwap)
                        {
                            waveform.DrawRectangle(rectWidth, RECT_HEIGHT, prevY, compare1.ToString(), "Compare 1");
                            prevY += RECT_HEIGHT + linesDistance;
                        }
                        break;
                    case CyEnums.CyCompareOrCapture.MODE_CAPTURE:
                        //
                        // Draw Capture line
                        //
                        waveform.DrawLine(prevY, captureStairs, CyEStairPart.Middle, "Capture");
                        prevY += linesDistance;
                        break;
                    default:
                        Debug.Fail("unhandled enum item.");
                        break;
                }
                breakLineY1 = prevY - linesDistance / 2;

                //
                // Draw stairs
                //
                waveform.DrawStairs(prevY);
                prevY += CyWaveform.STAIR_HEIGHT * waveform.GetStairCount();

                //
                // Draw Overflow/Underflow lines
                //
                int[] overflowStairPos = new int[0];
                int[] underflowStairPos = new int[0];
                switch (countDirection)
                {
                    case CyEnums.CyCountDirection.COUNT_UP:
                        // Draw Overflow
                        overflowStairPos = waveform.GetStairsPositions(new uint[] { period });
                        waveform.DrawLine(prevY, overflowStairPos, CyEStairPart.End, "Overflow");
                        break;
                    case CyEnums.CyCountDirection.COUNT_DOWN:
                        // Draw Underflow
                        underflowStairPos = waveform.GetStairsPositions(new uint[] { 0 });
                        waveform.DrawLine(prevY, underflowStairPos, CyEStairPart.End, "Underflow");
                        break;
                    case CyEnums.CyCountDirection.COUNT_UPDOWN0:
                    case CyEnums.CyCountDirection.COUNT_UPDOWN1:
                        // Draw Overflow
                        overflowStairPos = waveform.GetStairsPositions(new uint[] { period }, true);
                        waveform.DrawLine(prevY, overflowStairPos, CyEStairPart.End, "Overflow");
                        prevY += linesDistance * 2;
                        // Draw Underflow
                        underflowStairPos = waveform.GetStairsPositions(new uint[] { 0 }, true);
                        waveform.DrawLine(prevY, underflowStairPos, CyEStairPart.End, "Underflow");
                        break;
                    default:
                        Debug.Fail("unhandled enum item.");
                        break;
                }
                prevY += linesDistance * 2;

                //
                // Draw Capture Out
                //
                if (compareOrCapture == CyEnums.CyCompareOrCapture.MODE_CAPTURE)
                {
                    waveform.DrawLine(prevY, captureStairs, CyEStairPart.End, "Capture_Out");
                    prevY += linesDistance * 2;
                }

                //
                // Draw Compare line
                //
                List<int> mergedCompareStairs = new List<int>();
                if (compareOrCapture == CyEnums.CyCompareOrCapture.MODE_COMPARE)
                {
                    // Prepare arrays with compare arrows positions
                    int[] compare0Stairs = new int[0];
                    int[] compare1Stairs = new int[0];
                    compare0Stairs = waveform.GetStairsPositions(new uint[] { compare0 });
                    if (compareSwap)
                    {
                        compare1Stairs = waveform.GetStairsPositions(new uint[] { compare1 });
                    }

                    // Draw compare arrows
                    if (compareSwap)
                    {
                        switch (countDirection)
                        {
                            case CyEnums.CyCountDirection.COUNT_UP:
                                for (int i = 0; i < Math.Max(compare0Stairs.Length, compare1Stairs.Length); i++)
                                {
                                    if (compare0Stairs.Length > i)
                                        mergedCompareStairs.Add(compare0Stairs[i]);
                                    if (compare1Stairs.Length > i)
                                        mergedCompareStairs.Add(compare1Stairs[i]);
                                }
                                if (compare0 > compare1)
                                {
                                    // Compare0 should always go before compare1. 
                                    // Remove first element, which contains compare1 first arrow position.
                                    if (mergedCompareStairs.Count > 1)
                                        mergedCompareStairs.RemoveAt(1);
                                }
                                break;
                            case CyEnums.CyCountDirection.COUNT_DOWN:
                                for (int i = 0; i < compare0Stairs.Length; i++)
                                {
                                    if (compare0Stairs.Length > i)
                                        mergedCompareStairs.Add(compare0Stairs[i]);
                                    if (compare1Stairs.Length > i)
                                        mergedCompareStairs.Add(compare1Stairs[i]);
                                }
                                if (compare0 < compare1)
                                {
                                    // Compare0 should always go before compare1. 
                                    // Remove first element, which contains compare1 first arrow position.
                                    if (mergedCompareStairs.Count > 1)
                                        mergedCompareStairs.RemoveAt(1);
                                }
                                break;
                            case CyEnums.CyCountDirection.COUNT_UPDOWN0:
                            case CyEnums.CyCountDirection.COUNT_UPDOWN1:
                                if (compare0Stairs.Length > 0)
                                {
                                    mergedCompareStairs.Add(compare0Stairs[0]);
                                    mergedCompareStairs.Add(compare1Stairs[0]);
                                    if (compare0 > compare1)
                                    {
                                        for (int i = 2; i < Math.Max(compare0Stairs.Length, compare1Stairs.Length); i++)
                                        {
                                            if (i % 2 == 0)
                                            {
                                                if (compare1Stairs.Length > i)
                                                    mergedCompareStairs.Add(compare1Stairs[i - 1]);
                                            }
                                            else
                                            {
                                                if (compare0Stairs.Length > i)
                                                    mergedCompareStairs.Add(compare0Stairs[i - 1]);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        for (int i = 2; i < Math.Max(compare0Stairs.Length, compare1Stairs.Length); i++)
                                        {
                                            if (i % 2 == 0)
                                            {
                                                if (compare0Stairs.Length > i)
                                                    mergedCompareStairs.Add(compare0Stairs[i - 1]);
                                            }
                                            else
                                            {
                                                if (compare1Stairs.Length > i)
                                                    mergedCompareStairs.Add(compare1Stairs[i - 1]);
                                            }
                                        }
                                    }

                                    if (compare0 > compare1)
                                    {
                                        // Compare0 should always go before compare1. 
                                        // Remove first element, which contains compare1 first arrow position.
                                        if (mergedCompareStairs.Count > 1)
                                            mergedCompareStairs.RemoveAt(1);
                                    }
                                }
                                break;
                            default:
                                Debug.Fail("unhandled enum item.");
                                break;
                        }

                        waveform.DrawLine(prevY, mergedCompareStairs.ToArray(), CyEStairPart.End, "Compare");
                    }
                    else
                    {
                        mergedCompareStairs = new List<int>(compare0Stairs);
                        waveform.DrawLine(prevY, mergedCompareStairs.ToArray(), CyEStairPart.End, "Compare");
                    }

                    prevY += linesDistance * 2;
                }

                //
                // Draw Interrupt line
                //
                bool onOverflow = false;
                bool onUnderflow = false;
                bool onCapture = false;
                bool onCompare = false;
                switch (interruptSource)
                {
                    case CyEnums.CyInterruptSources.INT_NONE:
                        break;
                    case CyEnums.CyInterruptSources.INT_ON_TC:
                        switch (countDirection)
                        {
                            case CyEnums.CyCountDirection.COUNT_UP:
                                onOverflow = true;
                                break;
                            case CyEnums.CyCountDirection.COUNT_DOWN:
                            case CyEnums.CyCountDirection.COUNT_UPDOWN0:
                                onUnderflow = true;
                                break;
                            case CyEnums.CyCountDirection.COUNT_UPDOWN1:
                                onOverflow = true;
                                onUnderflow = true;
                                break;
                            default:
                                Debug.Fail("unhandled enum item.");
                                break;
                        }
                        break;
                    case CyEnums.CyInterruptSources.INT_ON_CC:
                        switch (compareOrCapture)
                        {
                            case CyEnums.CyCompareOrCapture.MODE_COMPARE:
                                onCompare = true;
                                break;
                            case CyEnums.CyCompareOrCapture.MODE_CAPTURE:
                                onCapture = true;
                                break;
                            default:
                                Debug.Fail("unhandled enum item.");
                                break;
                        }
                        break;
                    case CyEnums.CyInterruptSources.INT_ON_TC_CC:
                        switch (countDirection)
                        {
                            case CyEnums.CyCountDirection.COUNT_UP:
                                onOverflow = true;
                                break;
                            case CyEnums.CyCountDirection.COUNT_DOWN:
                            case CyEnums.CyCountDirection.COUNT_UPDOWN0:
                                onUnderflow = true;
                                break;
                            case CyEnums.CyCountDirection.COUNT_UPDOWN1:
                                onOverflow = true;
                                onUnderflow = true;
                                break;
                            default:
                                Debug.Fail("unhandled enum item.");
                                break;
                        }
                        switch (compareOrCapture)
                        {
                            case CyEnums.CyCompareOrCapture.MODE_COMPARE:
                                onCompare = true;
                                break;
                            case CyEnums.CyCompareOrCapture.MODE_CAPTURE:
                                onCapture = true;
                                break;
                            default:
                                Debug.Fail("unhandled enum item.");
                                break;
                        }
                        break;
                    default:
                        Debug.Fail("unhandled enum item.");
                        break;
                }

                bool drawTitle = true;
                if (onOverflow)
                {
                    waveform.DrawLine(prevY, overflowStairPos, CyEStairPart.End, drawTitle ? "Interrupt" : "");
                    drawTitle = false;
                }
                if (onUnderflow)
                {
                    waveform.DrawLine(prevY, underflowStairPos, CyEStairPart.End, drawTitle ? "Interrupt" : "");
                    drawTitle = false;
                }
                if (onCapture)
                {
                    waveform.DrawLine(prevY, captureStairs, CyEStairPart.End, drawTitle ? "Interrupt" : "");
                }
                else if (onCompare)
                {
                    waveform.DrawLine(prevY, mergedCompareStairs.ToArray(), CyEStairPart.End, drawTitle ? "Interrupt" : "");
                }

                if (onOverflow || onUnderflow || onCapture || onCompare)
                    prevY += linesDistance;

                breakLineY2 = prevY - linesDistance;

                //
                // Draw Capture Reg rectangles
                //
                if (compareOrCapture == CyEnums.CyCompareOrCapture.MODE_CAPTURE)
                {
                    string[] captureRegValues = new string[captureStairs.Length];
                    string[] captureBufRegValues = new string[captureStairs.Length];
                    if (captureRegValues.Length == 0 || captureBufRegValues.Length == 0)
                    {
                        captureRegValues = new string[1];
                        captureBufRegValues = new string[1];
                    }
                    captureRegValues[0] = "0";
                    captureBufRegValues[0] = "0";
                    bool isDown = countDirection == CyEnums.CyCountDirection.COUNT_DOWN;
                    int j = isDown ? captureArrows.Length - 1 : 0;
                    for (int i = 1; i < captureRegValues.Length; i++)
                    {
                        captureRegValues[i] = captureArrows[j].ToString();
                        if (isDown)
                            j--;
                        else
                            j++;
                        captureBufRegValues[i] = captureRegValues[i - 1];
                        if (isDown)
                        {
                            if (j < 0)
                                j = captureArrows.Length - 1;
                        }
                        else
                        {
                            if (j >= captureArrows.Length)
                                j = 0;
                        }
                    }

                    if (period == 0)
                    {
                        int rectWidth = updatedBitmap.Width - CyWaveform.LINES_X - 5;
                        waveform.DrawRectangle(rectWidth, RECT_HEIGHT, prevY, "0", "Capture Reg");
                        prevY += RECT_HEIGHT + linesDistance;
                        waveform.DrawRectangle(rectWidth, RECT_HEIGHT, prevY, "0", "Capture Buf Reg");
                    }
                    else
                    {
                        waveform.DrawRectanglesByStairs(captureStairs, RECT_HEIGHT, prevY, captureRegValues,
                            "Capture Reg", CyEStairPart.End);
                        prevY += linesDistance * 3;
                        waveform.DrawRectanglesByStairs(captureStairs, RECT_HEIGHT, prevY, captureBufRegValues,
                            "Capture Buf Reg", CyEStairPart.End);
                    }
                    prevY += RECT_HEIGHT + linesDistance;
                }

                //
                // Draw break line
                //
                if (period > CyWaveform.MAX_STAIR_COUNT)
                {
                    waveform.DrawBreakLines(CyWaveform.LINES_X + CyWaveform.STAIR_HEIGHT * BREAK_LINE_STAIR,
                        breakLineY1, breakLineY2, CyEStairPart.Middle);
                }

                //
                // Assign the image and dispose resources
                //
                Bitmap old = Image as Bitmap;
                Image = CyGraphicsUtils.CropImage(updatedBitmap, (int)(prevY * 2.5), prevY);
                if (old != null)
                {
                    old.Dispose();
                }
            }
        }
    }
}
