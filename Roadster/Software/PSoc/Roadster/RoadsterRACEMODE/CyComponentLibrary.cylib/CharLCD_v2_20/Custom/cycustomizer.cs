/*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System.Collections.Generic;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.Windows.Forms;
using System;
using CyDesigner.Toolkit.TerminalControl_v1;
using CyTerminalControl_v1 = CyDesigner.Toolkit.TerminalControl_v1.CyTerminalControl_v1;

namespace CharLCD_v2_20
{
    [CyCompDevCustomizer]
    sealed public partial class CyCustomizer : ICyParamEditHook_v1, ICySystemBuilderComp_v1
    {
        #region ICyParamEditHook_v1 Members
        // Type of dialog box. Advanced opens with a button on the generic form. Complete opens immediately
        private const CyCompDevParamEditorMode MODE = CyCompDevParamEditorMode.COMPLETE;
        // Run Instance Customizer on Instance Selection
        private const bool EDIT_ON_DROP = false;
        private CyCharacterLCDEditingControl m_editControl;

        /// <summary>
        /// Edit Params initializes the data in the customizer as well as 
        /// instantiating the dialog.
        /// </summary>
        /// <param name="instEdit"> Is a component object containing the parameter information for the object. </param>
        /// <returns>A DialogResult object associated with the form.  
        /// OK means accept changes.  Cancel means reject changes.</returns>
        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 instEdit, ICyTerminalQuery_v1 termQuery, 
            ICyExpressMgr_v1 mgr)
        {
            ICyTabbedParamEditor editor = instEdit.CreateTabbedParamEditor();

            CyTerminalControl_v1 interconnectTab = null;

            m_editControl = new CyCharacterLCDEditingControl(instEdit);
            editor.AddCustomPage("General", m_editControl, ExpView_ParamChanged, "General");
            // System Builder support
            if (instEdit.IsInSystemBuilder)
            {
                interconnectTab = new CyTerminalControl_v1(instEdit);
                editor.AddCustomPage(Resources.InterconnectTabDisplayName, interconnectTab, ExpView_ParamChanged,
                    "Interconnect");
            }
            editor.AddDefaultPage("Built-in", "Built-in");
            UpdateSBTabsVisibility(instEdit, editor);
            System.Windows.Forms.DialogResult result = editor.ShowDialog();
            return result;
        }

        private static void UpdateSBTabsVisibility(ICyInstEdit_v1 obj, ICyTabbedParamEditor editor)
        {
            if (obj.IsInSystemBuilder)
            {                
                editor.ShowCustomPage(Resources.InterconnectTabDisplayName);
            }
            else
            {
                editor.HideCustomPage(Resources.InterconnectTabDisplayName);
            }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return MODE;
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get { return EDIT_ON_DROP; }
        }
        #endregion

        private void ExpView_ParamChanged(ICyParamEditor custEditor, CyCompDevParam param)
        {
            if (param.ErrorCount == 0)
            {
                ((CyCharLCDControl)(m_editControl.DisplayControl)).InitializeParameters();                
            }
        }

        #region ICySystemBuilderComp_v1 members
        public CyCustErr GetTitleText(ICySystemBuilderCompArgs_v1 args, out string title)
        {
            title = Resources.SBComponentTitle;
            return CyCustErr.OK;
        }
        public CyCustErr GetBodyText(ICySystemBuilderCompArgs_v1 args, out string bodyText)
        {
            string conversionRoutinesDisplayName = "";
            string conversionCustomCharSet = "";

            CyCompDevParam paramCR = args.InstQuery.GetCommittedParam(CyCharLCDControl.CR_PARAM);
            if (paramCR.ErrorCount == 0)
            {
                bool includeASCII;
                paramCR.TryGetValueAs<bool>(out includeASCII);
                if (includeASCII == false)
                {
                    conversionRoutinesDisplayName = Resources.SBIncludeASCIILabel;
                }
            }

            CyCompDevParam paramCharSet = 
                args.InstQuery.GetCommittedParam(CyCharLCDControl.CUSTOM_CHARACTER_SET_PARAM);

            if (paramCharSet.ErrorCount == 0)
            {
                CyCustomCharacterSetTypes conversionCustomCharSetInt;
                paramCharSet.TryGetValueAs<CyCustomCharacterSetTypes>(out conversionCustomCharSetInt);

                switch (conversionCustomCharSetInt)
                {
                    case CyCustomCharacterSetTypes.NONE:
                        conversionCustomCharSet = Resources.SBCustomCharacterSetLabelNone;
                        break;
                    case CyCustomCharacterSetTypes.HORIZONTAL:
                        conversionCustomCharSet = Resources.SBCustomCharacterSetLabelHorizontalBarGraph;
                        break;
                    case CyCustomCharacterSetTypes.VERTICAL:
                        conversionCustomCharSet = Resources.SBCustomCharacterSetLabelVerticalBarGraph;
                        break;
                    case CyCustomCharacterSetTypes.USERDEFINED:
                        conversionCustomCharSet = Resources.SBCustomCharacterSetLabelUserDefined;
                        break;
                }                
            }

            bodyText = String.Format(Resources.SBComponentBodyText, conversionCustomCharSet, 
                                     conversionRoutinesDisplayName);

            return CyCustErr.OK;
        }        
        #endregion
    }

    public class CyCharacterLCDEditingControl : ICyParamEditingControl
    {
        private CyCharLCDControl m_control;

        public CyCharacterLCDEditingControl(ICyInstEdit_v1 obj)
        {
            this.m_control = new CyCharLCDControl(obj);
            this.m_control.Dock = DockStyle.Fill;
        }

        #region ICyParamEditingControl Members

        public Control DisplayControl
        {
            get { return m_control; }
        }

        public IEnumerable<CyCustErr> GetErrors()
        {
            return new CyCustErr[] { };
        }

        #endregion
    }
}
