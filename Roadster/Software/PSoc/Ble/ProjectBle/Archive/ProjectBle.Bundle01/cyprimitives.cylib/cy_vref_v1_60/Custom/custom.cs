/*******************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
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

namespace Cypress.Components.System.cy_vref_v1_60
{
    public class CyCustomizer : ICyParamEditHook_v1, ICyVerilogCustomize_v1, ICyToolTipCustomize_v1,
        ICyShapeCustomize_v1, ICyExprEval_v2
    {
        //-----------------------------

        const string m_builtinTabName = "Built-in";
        const string m_basicTabName = "Basic";
		const string m_advancedTabName = "Advanced";

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
                editor.AddCustomPage(m_basicTabName, control, control.Update, m_basicTabName);
				editor.AddDefaultPage(m_advancedTabName, m_advancedTabName);
                editor.AddDefaultPage(m_builtinTabName, m_builtinTabName);
                return editor.ShowDialog();
            }
            else
            {
                //Show error message. This component cannot be configured without a DesigneQuery available.
                CyMsgControl msgControl = new CyMsgControl();
                msgControl.Text = "Unable to configure this VRef component. This component requires family specific " +
                                  "information. It cannot be added at the Generic level in a library project. To " +
                                  "use this component add it to a family or device specific implementation.";

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
            CyVerilogWriter vw = new CyVerilogWriter("cy_vref_v1_0", query.InstanceName);

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

            string newToolTip = query.DefaultToolTipText;

            newToolTip += Environment.NewLine;
            newToolTip += "VRefName = " + ((isDefault) ? "Default <" + refName + ">" : refName);

            return newToolTip;
        }

        #endregion

        //-----------------------------

        #region ICyShapeCustomize_v1 Members

        const string InstNameTag = "name";
        const string BodyNameTag = "body";

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

            RectangleF bounds = shapeEdit.GetShapeBounds(BodyNameTag);
            StringFormat fmt = new StringFormat();
            fmt.Alignment = StringAlignment.Far;
            fmt.LineAlignment = StringAlignment.Center;

            CyCustErr err = shapeEdit.CreateAnnotation(new string[] { InstNameTag },
                dspName,
                new PointF(bounds.Left, bounds.Top + (bounds.Height / 2.0f)),
                new Font(FontFamily.GenericSansSerif, 10, FontStyle.Regular),
                fmt);
            if (err.IsNotOk) return err;

            err = shapeEdit.SetFillColor(InstNameTag, Color.Black);
            if (err.IsNotOk) return err;

            err = shapeEdit.ClearOutline(InstNameTag);
            if (err.IsNotOk) return err;

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
                    "Incorrect number of arguements to call function '{0}' (no arguement expected).",
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
        const string ParamNameVRefID = "guid";
        const string ParamNameVRefName = "RefName";
		const string ParamNameAutoEnable = "AutoEnable";

        public static string GetVRefIDValue(ICyInstQuery_v1 query)
        {
            if (query.ContainsParam(ParamNameVRefID))
            {
                CyCompDevParam param = query.GetCommittedParam(ParamNameVRefID);
                return param.Value;
            }
            return String.Empty;
        }

        public static void SetVRefIDExpr(ICyInstEdit_v1 edit, string expr)
        {
            edit.SetParamExpr(ParamNameVRefID, expr);
        }

        public static string GetVRefNameValue(ICyInstQuery_v1 query)
        {
            if (query.ContainsParam(ParamNameVRefName))
            {
                CyCompDevParam param = query.GetCommittedParam(ParamNameVRefName);
                return param.Value;
            }
            return String.Empty;
        }

        public static void SetVRefNameExpr(ICyInstEdit_v1 edit, string expr)
        {
            edit.SetParamExpr(ParamNameVRefName, expr);
        }

        public static bool IsGUIDParam(CyCompDevParam param)
        {
            return param.Name == ParamNameVRefID;
        }

        public static bool IsNameParam(CyCompDevParam param)
        {
            return param.Name == ParamNameVRefName;
        }

		public static bool IsBoolParam(CyCompDevParam param)
		{
			return param.Name == ParamNameAutoEnable;
		}
    }
}
