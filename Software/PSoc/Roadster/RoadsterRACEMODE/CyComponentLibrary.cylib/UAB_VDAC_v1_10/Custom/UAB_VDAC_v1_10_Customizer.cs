/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace UAB_VDAC_v1_10
{
    [CyCompDevCustomizer()]
    public partial class CyCustomizer : ICyParamEditHook_v1 , ICyShapeCustomize_v1
    {
        private const bool m_editParamsOnDrop = false;
        private const CyCompDevParamEditorMode m_mode = CyCompDevParamEditorMode.COMPLETE;
        private CyParameters m_parameters;

        #region ICyParamEditHook_v1 method(s)
        DialogResult ICyParamEditHook_v1.EditParams(
            ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            m_parameters = new CyParameters(edit, edit, termQuery);
            CyParamExprDelegate paramChange = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
            };

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            //UseBigEditor is:
            //      true  = 640x480 (~595x330 useable) 
            //      false = 515x390 (~475x230 useable)
            editor.UseBigEditor = true;
            CyUAB_VDAC_v1_10EditingControl basicTab = new CyUAB_VDAC_v1_10EditingControl(m_parameters);
            editor.AddCustomPage(UAB_VDAC_v1_10_resource.tabNameBasic, basicTab, paramChange, "Basic");

            editor.AddDefaultPage(UAB_VDAC_v1_10_resource.tabNameBuiltIn, "Built-in");

            edit.NotifyWhenDesignUpdates(basicTab.m_control.helper_DesignUpdated);
            
            return editor.ShowDialog();
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get
            {
                return m_editParamsOnDrop;
            }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return m_mode;
        }
        #endregion

        #region ICyShapeCustomize_v1 method(s)
        /// <summary>
        /// The symbol portrays analog wires; this method styles the wires to
        /// resemble the user's preferences.  Called only by Creator.
        /// </summary>
        /// <param name="query"></param>
        /// <param name="shapeEdit"></param>
        /// <param name="termEdit"></param>
        /// <returns></returns>
        CyCustErr ICyShapeCustomize_v1.CustomizeShapes(ICyInstQuery_v1 query, ICySymbolShapeEdit_v1 shapeEdit, ICyTerminalEdit_v1 termEdit)
        {
            CyCustErr funcStatus;
            System.Drawing.Color analogColor = query.Preferences.AnalogWireColor;
            System.Single wireSize = query.Preferences.WireSize;
            //"AnalogWire" is the tag of the lines in the symbol.  To see it: Open .cysym; right click line -> Format Shape.
            funcStatus = shapeEdit.SetOutlineColor("AnalogWire", analogColor);
            if (funcStatus != CyCustErr.Ok)
            {
                return funcStatus;
            }
            funcStatus = shapeEdit.SetOutlineWidth("AnalogWire", wireSize);
            return funcStatus;
        }
        #endregion
    }

    public class CyUAB_VDAC_v1_10EditingControl : ICyParamEditingControl
    {
        public CyUAB_VDAC_v1_10Control m_control;

        public CyUAB_VDAC_v1_10EditingControl(CyParameters parameters)
        {
            m_control = new CyUAB_VDAC_v1_10Control(parameters);
            parameters.m_control = m_control;
            m_control.Dock = DockStyle.Fill;
        }

        Control ICyParamEditingControl.DisplayControl
        {
            get { return m_control; }
        }

        IEnumerable<CyCustErr> ICyParamEditingControl.GetErrors()
        {
            return new CyCustErr[] { };
        }
    }
}
