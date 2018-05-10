/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.IO;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyDesigner.Common.Base.Controls;

namespace Cypress.Components.System.cy_vref_v1_70
{
    public class CyCustomizer : ICyParamEditHook_v1, ICyVerilogCustomize_v1, ICyToolTipCustomize_v1,
        ICyShapeCustomize_v1, ICyExprEval_v2
    {
        //-----------------------------

        const string TABNAME_BUILTIN = "Built-in";
        const string TABNAME_BASIC = "Basic";
        const string TABNAME_ADVANCED = "Advanced";

        //Version of component in verilog code can differ from current component version.
        const string VERILOG_COMPONENTNAME = "cy_vref_v1_0";

        //-----------------------------

        #region ICyParamEditHook_v1 Members

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        /// <summary>
        /// Displays a custom parameter editor to the user to allow them to edit the port params.
        /// </summary>
        /// <param name="edit"></param>
        /// <param name="mgr"></param>
        /// <returns></returns>
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            if (edit.DesignQuery != null && edit.DesignQuery.DesignInfoAvailable)
            {
                List<CyVRef> vRefs = new List<CyVRef>();

                //If the id has not been set it will be the empty string, in which case the default ref will be used.
                string defaultName = string.Format("Default <{0}>",
                    edit.DesignQuery.GetVRefName(edit.DesignQuery.VRefDefaultID));
                vRefs.Add(new CyVRef(string.Empty, defaultName));

                foreach (string id in edit.DesignQuery.VRefIDs)
                {
                    vRefs.Add(new CyVRef(id, edit.DesignQuery.GetVRefName(id)));
                }

                string selectedID = CyVRefInfo.GetVRefIDValue(edit);
                CyVRefIDControl control = new CyVRefIDControl(edit, vRefs, selectedID);
                control.Dock = DockStyle.Fill;

                ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
                editor.AddCustomPage(Resources.TABTITLE_BASIC, control, control.Update, TABNAME_BASIC);
                editor.AddDefaultPage(Resources.TABTITLE_ADVANCED, TABNAME_ADVANCED);
                editor.AddDefaultPage(Resources.TABTITLE_BUILTIN, TABNAME_BUILTIN);
                return editor.ShowDialog();
            }
            else
            {
                //Show error message. This component cannot be configured without a DesigneQuery available.
                CyMsgControl msgControl = new CyMsgControl();
                msgControl.Text =  Resources.ERRMSG_DESIGNEQUERY;

                ICyParamEditor editor = edit.CreateParamEditor(msgControl);
                return editor.ShowDialog();
            }
        }

        private class CyMsgControl : CyCenteredTextControl, ICyParamEditingControl
        {
            #region ICyParamEditingControl Members

            public Control DisplayControl
            {
                get { return this; }
            }

            public IEnumerable<CyCustErr> GetErrors()
            {
                return new CyCustErr[] { };
            }

            #endregion
        }

        /// <summary>
        /// Gets whether or not EditParams should be called when a port is initailly
        /// dropped onto a canvas.
        /// </summary>
        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        #endregion

        //-----------------------------

        #region ICyVerilogCustomize_v1 Members

        /// <summary>
        /// Needed to convert the default empty string to the default ID.
        /// </summary>
        /// <param name="query"></param>
        /// <param name="termQuery"></param>
        /// <param name="codeSnippet"></param>
        /// <returns></returns>
        public CyCustErr CustomizeVerilog(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery, out string codeSnippet)
        {
            CyCustErr err = CyCustErr.Ok;
            codeSnippet = string.Empty;

            //Version of component in verilog code can differ from current component version.
            CyVerilogWriter vw = new CyVerilogWriter(VERILOG_COMPONENTNAME, query.InstanceName);

            //Add Generics.
            foreach (string paramName in query.GetParamNames())
            {
                CyCompDevParam param = query.GetCommittedParam(paramName);
                if (param.IsHardware)
                {
                    string value;
                    if (CyVRefInfo.IsGUIDParam(param))
                        value = "\"" + GetVRefID(query) + "\"";
                    else if (CyVRefInfo.IsNameParam(param))
                        value = "\"" + GetVRefName(query) + "\"";
                    else if (CyVRefInfo.IsBoolParam(param))
                        value = param.Value.Equals("true", StringComparison.InvariantCultureIgnoreCase) ? "1" : "0";
                    else
                        value = param.Value;
                    vw.AddGeneric(ParamNameToHdlName(param.Name), value);
                }
            }

            //Add Ports.
            foreach (string termCanonicalName in termQuery.GetTerminalNames())
            {
                string value = termQuery.GetTermSigSegName(termCanonicalName);

                CyCompDevTermDir dir = termQuery.GetTermDirection(termCanonicalName);
                bool hasNoDrivers = termQuery.GetHasNoDrivers(termCanonicalName);
                if (dir != CyCompDevTermDir.OUTPUT && hasNoDrivers)
                {
                    value = termQuery.GetTermDefaultVlogExpr(termCanonicalName);
                }

                string baseTermName = termQuery.GetTermBaseName(termCanonicalName);
                vw.AddPort(baseTermName, value);
            }

            codeSnippet = vw.ToString();
            return err;
        }

        private static string ParamNameToHdlName(string name)
        {
            switch (name)
            {
                case "AutoEnable":
                    return "autoenable";
                case "RefName":
                    return "name";
                default:
                    return name;
            }
        }

        #endregion

        //-----------------------------

        #region ICyToolTipCustomize_v1

        /// <summary>
        /// Looks up the human readable name for the reference.
        /// </summary>
        /// <param name="query"></param>
        /// <returns></returns>
        public string CustomizeToolTip(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            string id = CyVRefInfo.GetVRefIDValue(query);
            bool isDefault = string.IsNullOrEmpty(id);
            string refName = GetVRefName(query);

            string formatStr = isDefault ? "{0}{1}VRefName = Default <{2}>" : "{0}{1}VRefName = {2}";
            string newToolTip = string.Format(formatStr, query.DefaultToolTipText, Environment.NewLine, refName);

            return newToolTip;
        }

        #endregion

        //-----------------------------

        #region ICyShapeCustomize_v1 Members

        const string NAMETAG_INST = "name";
        const string NAMETAG_BODY = "body";

        /// <summary>
        /// Add the instance name.
        /// </summary>
        /// <param name="query"></param>
        /// <param name="shapeEdit"></param>
        /// <param name="termEdit"></param>
        /// <returns></returns>
        public CyCustErr CustomizeShapes(ICyInstQuery_v1 query, ICySymbolShapeEdit_v1 shapeEdit,
            ICyTerminalEdit_v1 termEdit)
        {
            string dspName = GetVRefName(query);

            RectangleF bounds = shapeEdit.GetShapeBounds(NAMETAG_BODY);
            StringFormat fmt = new StringFormat();
            fmt.Alignment = StringAlignment.Far;
            fmt.LineAlignment = StringAlignment.Center;

            CyCustErr err = shapeEdit.CreateAnnotation(new string[] { NAMETAG_INST },
                dspName,
                new PointF(bounds.Left, bounds.Top + (bounds.Height / 2.0f)),
                new Font(FontFamily.GenericSansSerif, 10, FontStyle.Regular),
                fmt);
            if (err.IsNotOk) return err;

            err = shapeEdit.SetFillColor(NAMETAG_INST, Color.Black);
            if (err.IsNotOk) return err;

            err = shapeEdit.ClearOutline(NAMETAG_INST);
            return err;
        }

        #endregion

        //-----------------------------

        #region ICyExprEval_v2 Members
        public CyExprEvalFuncEx GetFunction(string exprFuncName)
        {
            switch (exprFuncName)
            {
                case "GetDefaultName":
                    return new CyExprEvalFuncEx(GetVrefDefaultName);

                default:
                    //Return null to indicate that the customizer didn't process the 
                    //function call so PSoC Creator should continue trying to process it.
                    return null;
            }
        }

        object GetVrefDefaultName(string exprFuncName, object[] callingArgs, ICyExprEvalArgs_v2 creatorArgs,
            ICyExprTypeConverter typeConverter)
        {
            //Generate an error if the wrong number of arguements have been passed in.
            if (callingArgs.Length != 0)
            {
                return new CyCustErr(string.Format(
                    "Incorrect number of arguments to call function '{0}' (no arguments expected).",
                    exprFuncName));
            }
            else
            {
                ICyInstQuery_v1 query = creatorArgs.InstQuery;
                if (query != null && query.DesignQuery != null && query.DesignQuery.DesignInfoAvailable)
                {
                    string id = GetVRefID(query);
                    string name = query.DesignQuery.GetVRefName(id);
                    if (!string.IsNullOrEmpty(name))
                    {
                        return name;
                    }
                }

                return String.Empty;
            }
        }
        #endregion

        //-----------------------------

        /// <summary>
        /// Gets the ID substituting the Default ID for the empty string if needed.
        /// </summary>
        /// <param name="query"></param>
        /// <returns></returns>
        string GetVRefID(ICyInstQuery_v1 query)
        {
            string id = CyVRefInfo.GetVRefIDValue(query);

            //If the guid is not set, use the default Global Signal Reference.
            if (string.IsNullOrEmpty(id) && query.DesignQuery != null && query.DesignQuery.DesignInfoAvailable)
            {
                id = query.DesignQuery.VRefDefaultID;
            }

            return id;
        }

        /// <summary>
        /// Gets the human readable name of the reference. If the ID is empty the Default ID is used.
        /// </summary>
        /// <param name="query"></param>
        /// <returns></returns>
        string GetVRefName(ICyInstQuery_v1 query)
        {
            if (query.DesignQuery != null && query.DesignQuery.DesignInfoAvailable)
            {
                string id = GetVRefID(query);
                string name = query.DesignQuery.GetVRefName(id);
                if (!string.IsNullOrEmpty(name))
                {
                    return name;
                }
            }
            return CyVRefInfo.GetVRefNameValue(query);
        }
    }

    internal static class CyVRefInfo
    {
        const string PARAMNAME_VREFID = "guid";
        const string PARAMNAME_VREFNAME = "RefName";
        const string PARAMNAME_AUTOENABLE = "AutoEnable";

        public static string GetVRefIDValue(ICyInstQuery_v1 query)
        {
            if (query.ContainsParam(PARAMNAME_VREFID))
            {
                CyCompDevParam param = query.GetCommittedParam(PARAMNAME_VREFID);
                return param.Value;
            }
            return String.Empty;
        }

        public static void SetVRefIDExpr(ICyInstEdit_v1 edit, string expr)
        {
            edit.SetParamExpr(PARAMNAME_VREFID, expr);
        }

        public static string GetVRefNameValue(ICyInstQuery_v1 query)
        {
            if (query.ContainsParam(PARAMNAME_VREFNAME))
            {
                CyCompDevParam param = query.GetCommittedParam(PARAMNAME_VREFNAME);
                return param.Value;
            }
            return String.Empty;
        }

        public static void SetVRefNameExpr(ICyInstEdit_v1 edit, string expr)
        {
            edit.SetParamExpr(PARAMNAME_VREFNAME, expr);
        }

        public static bool IsGUIDParam(CyCompDevParam param)
        {
            return param.Name == PARAMNAME_VREFID;
        }

        public static bool IsNameParam(CyCompDevParam param)
        {
            return param.Name == PARAMNAME_VREFNAME;
        }

        public static bool IsBoolParam(CyCompDevParam param)
        {
            return param.Name == PARAMNAME_AUTOENABLE;
        }
    }
}
