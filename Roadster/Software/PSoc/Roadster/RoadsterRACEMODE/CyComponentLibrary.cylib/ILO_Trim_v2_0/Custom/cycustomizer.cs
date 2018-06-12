using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace ILO_Trim_v2_0
{
    public class CyCustomizer : ICyParamEditHook_v1, ICyAPICustomize_v1, ICyDRCProvider_v1
    {
        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit, termQuery);
            parameters.GlobalEditMode = false;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            //editor.UseBigEditor = false;

            // Create tab pages
            CyGeneralTab generalTab = new CyGeneralTab(parameters);

            CyParamExprDelegate dataChanged =
            delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                generalTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            // Add tabs to the customizer
            editor.AddCustomPage(Resources.GeneralTabDisplayName, generalTab, dataChanged, generalTab.TabName);
            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");

            generalTab.UpdateUI();

            parameters.GlobalEditMode = true;

            edit.NotifyWhenDesignUpdates(generalTab.UpdateClockData);

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

        #region ICyAPICustomize_v1 Members
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();

            if (customizers.Count > 0)
            {
                paramDict = customizers[0].MacroDictionary;
            }

            CyParameters parameters = new CyParameters(query, termQuery);

            double refFrequency = parameters.ReferenceClockKHz;
            if (CyParameters.IsFrequencyKnown(refFrequency))
            {
                paramDict.Add("RefFrequency", refFrequency.ToString("0.000"));
            }

            double iloFrequency = parameters.ILOClockKHz;
            if (CyParameters.IsFrequencyKnown(iloFrequency))
            {
                paramDict.Add("ILOFrequency", ((int)iloFrequency).ToString());
            }

            UInt32 ratio = CyParameters.GetRatio(refFrequency, iloFrequency);
            paramDict.Add("ClkRatio", ratio.ToString() + "u");

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
            }

            return customizers;
        }
        #endregion

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CyParameters parameters = new CyParameters(args.InstQueryV1, args.TermQueryV1);
            if (string.IsNullOrEmpty(parameters.RatioErrorDescription) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, parameters.RatioErrorDescription);
            }

            double refFrequency = parameters.ReferenceClockKHz;
            if (CyParameters.IsFrequencyKnown(refFrequency) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    "Reference clock frequency is unknown.");
            }

            double iloFrequency = parameters.ILOClockKHz;
            if (CyParameters.IsFrequencyKnown(iloFrequency) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, "ILO clock frequency is unknown.");
            }

            UInt32 ratio = CyParameters.GetRatio(refFrequency, iloFrequency);

            if (string.IsNullOrEmpty(parameters.ILOFrequencyErrorDescription) == false)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, parameters.ILOFrequencyErrorDescription);
            }
        }
        #endregion
    }
}
