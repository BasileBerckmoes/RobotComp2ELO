/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Linq;
using System.Diagnostics;
using System.Windows.Forms;
using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using SCB_UART_PDL_v2_0.Controls;

namespace SCB_UART_PDL_v2_0
{
    sealed public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1, ICyExprEval_v3
    {
        #region ICyParamEditHook_v1 members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);

            // Create control with dynamicaly calculated labels
            CyDynamicDataControl dynamicDataControl = new CyDynamicDataControl(parameters);
            CyDefaultPageUserControl userControl = new CyDefaultPageUserControl(dynamicDataControl,
                false, SizeType.Absolute, 200);

            CyTabParamEditorDefaultPageExtender extender = new CyTabParamEditorDefaultPageExtender();
            extender.InnerRightBottomControl = userControl;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;

            // Create tab pages
            editor.AddDefaultPage(Resources.BasicTabDisplayName, extender);
            editor.AddDefaultPage(Resources.AdvancedTabDisplayName, "Advanced");
            editor.AddDefaultPage(Resources.PinsTabDisplayName, "Pins");
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");

            edit.NotifyWhenDesignUpdates(parameters.OnDesignUpdated);

            parameters.EditMode = true;
            return editor.ShowDialog();
        }

        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        #endregion

        #region ICyExprEval_v3 members
        const string GET_SCB_CLOCK_FUNC_NAME = "GetScbClock";
        const string GET_SCB_CLOCK_MINUS_TOLERANCE_FUNC_NAME = "GetScbClockMinusTolerance";
        const string GET_SCB_CLOCK_PLUS_TOLERANCE_FUNC_NAME = "GetScbClockPlusTolerance";

        public CyExprEvalFuncEx GetFunction(string exprFuncName)
        {
            switch (exprFuncName)
            {
                case GET_SCB_CLOCK_FUNC_NAME:
                    return new CyExprEvalFuncEx(GetScbClock);
                case GET_SCB_CLOCK_MINUS_TOLERANCE_FUNC_NAME:
                    return new CyExprEvalFuncEx(GetScbClockMinusTolerance);
                case GET_SCB_CLOCK_PLUS_TOLERANCE_FUNC_NAME:
                    return new CyExprEvalFuncEx(GetScbClockPlusTolerance);
                default:
                    return null;
            }
        }

        object GetScbClock(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            if (args.Length == 2)
            {
                try
                {
                    uint baudRate = typeConverter.GetAsUInt(args[0]);
                    ushort ovs = typeConverter.GetAsUShort(args[1]);

                    return (double)(ovs * baudRate) / 1000; // baudRate units is bps, so divide by 1000 to get KHz
                }
                catch (InvalidCastException ex)
                {
                    Debug.Fail(ex.Message);
                    
                    return (double)1000; // 1KHz
                }
            }
            else
            {
                return new CyCustErr(Resources.ExprBaudRateArgCheck);
            }
        }

        object GetScbClockMinusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            return (double)CyETolerance.DEFAULT;
        }

        object GetScbClockPlusTolerance(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
            ICyExprTypeConverter typeConverter)
        {
            return (double)CyETolerance.DEFAULT;
        }

        public IEnumerable<CyExprEvalCustomFunctionData> GetCustomFunctionData()
        {
            yield return new CyExprEvalCustomFunctionData(GET_SCB_CLOCK_FUNC_NAME,
                String.Format("{0}(baudRate, oversampling) : double", GET_SCB_CLOCK_FUNC_NAME),
                "Gets SCB clock frequency.");

            yield return new CyExprEvalCustomFunctionData(GET_SCB_CLOCK_MINUS_TOLERANCE_FUNC_NAME,
                String.Format("{0}() : double", GET_SCB_CLOCK_MINUS_TOLERANCE_FUNC_NAME),
                "Gets SCB clock minus tolerance.");

            yield return new CyExprEvalCustomFunctionData(GET_SCB_CLOCK_PLUS_TOLERANCE_FUNC_NAME,
                String.Format("{0}() : double", GET_SCB_CLOCK_PLUS_TOLERANCE_FUNC_NAME),
                "Gets SCB clock plus tolerance.");
        }
        #endregion

        #region ICyDRCProvider_v1 members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1, args.TermQueryV1);

            if (parameters.IsDmaCapable == false && (parameters.RxOutput || parameters.TxOutput))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, Resources.DMASupportError);
            }
        }
        #endregion
    }
}
