/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


using System;
using System.Collections.Generic;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Diagnostics;
 
namespace USBFS_v3_10
{
    [CyCompDevCustomizer()]
    public partial class CyCustomizer : ICyParamEditHook_v1, ICyBootLoaderSupport, ICyDRCProvider_v1
    {
        public const string PARAM_TAB_NAME_DEVICE = "Device";
        public const string PARAM_TAB_NAME_STRING = "String";
        public const string PARAM_TAB_NAME_HID = "Hid";
        public const string PARAM_TAB_NAME_AUDIO = "Audio";
        public const string PARAM_TAB_NAME_MIDI = "Midi";
        public const string PARAM_TAB_NAME_CDC = "CDC";
        public const string PARAM_TAB_NAME_MASS_STORAGE = "MSC";
        public const string PARAM_TAB_NAME_INTERRUPTS = "Interrupts";
        public const string PARAM_TAB_NAME_ADVANCED = "Advanced";
        public const string PARAM_TAB_BUILTIN = "Built-in";

        #region ICyParamEditHook_v1 Members

        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            CyUSBFSParameters parameters = new CyUSBFSParameters(edit);
            CyCDCDescriptorPage cdcPage = new CyCDCDescriptorPage(parameters);
            CyMidiDescriptorPage midiPage = new CyMidiDescriptorPage(parameters);
            CyMassStoragePage mscPage = new CyMassStoragePage(parameters);
            CyInterruptsPage intrPage = new CyInterruptsPage(parameters);
            CyAdvancedPage advPage = new CyAdvancedPage(parameters);

            CyParamExprDelegate ParamCommitted = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                if (param.TabName == PARAM_TAB_NAME_ADVANCED)
                {
                    advPage.InitFields();
                }
                else if (param.TabName == PARAM_TAB_NAME_CDC)
                {
                    cdcPage.InitAdditionalCheckBoxes();
                }
                else if (param.TabName == PARAM_TAB_NAME_MASS_STORAGE)
                {
                    mscPage.InitAdditionalControls();
                }
                else if (param.TabName == PARAM_TAB_NAME_MIDI)
                {
                    midiPage.InitAdditionalCheckBoxes();
                }
                else if (param.TabName == PARAM_TAB_NAME_INTERRUPTS)
                {
                    intrPage.UpdateUI();
                }
                else if (param.TabName == PARAM_TAB_NAME_DEVICE)
                {
                    intrPage.UpdateInterruptsTableView();
                }
                parameters.GlobalEditMode = true;
            };

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            editor.UseBigEditor = true;
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_DEVDESC,
                                 new CyDeviceDescriptorPage(parameters), ParamCommitted,  PARAM_TAB_NAME_DEVICE);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_STRDESC,
                                 new CyStringDescriptorPage(parameters), ParamCommitted, PARAM_TAB_NAME_STRING);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_HIDDESC, new CyHidDescriptorPage(parameters),
                                 ParamCommitted, PARAM_TAB_NAME_HID);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_AUDIODESC,
                                 new CyAudioDescriptorPage(parameters), ParamCommitted, PARAM_TAB_NAME_AUDIO);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_MIDIDESC,
                                 midiPage, ParamCommitted, PARAM_TAB_NAME_MIDI);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_CDCDESC, cdcPage, ParamCommitted, PARAM_TAB_NAME_CDC);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_MSCDESC, mscPage, ParamCommitted,
                PARAM_TAB_NAME_MASS_STORAGE);
            if(parameters.IsPSoC4AL_IpBlock)
                editor.AddCustomPage(Properties.Resources.PAGE_TITLE_INERRUPTS, intrPage, ParamCommitted, 
                    PARAM_TAB_NAME_INTERRUPTS);
            editor.AddCustomPage(Properties.Resources.PAGE_TITLE_ADV, advPage, ParamCommitted, PARAM_TAB_NAME_ADVANCED);
            editor.AddDefaultPage(Properties.Resources.PAGE_TITLE_BUILTIN, PARAM_TAB_BUILTIN);

            parameters.GlobalEditMode = true;
            DialogResult result = editor.ShowDialog();
            return result;
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

        #region ICyBootLoaderSupport Members

        /// <summary>
        /// The bootloader requires that the communication component is configured for
        /// both transfer in and out of the PSoC device. This method lets the implementing
        /// component inform PSoC Creator if it is currently configured to handle input and
        /// output.
        /// <param name="query">The ICyInstQuery for the relevant instance of the component.</param>
        /// </summary>
        public CyCustErr IsBootloaderReady(ICyInstQuery_v1 query)
        {
            CyCustErr supportBootloader = CyCustErr.OK;

            CyCompDevParam param = query.GetCommittedParam(CyUSBFSParameters.PARAM_DEVICEDESCRIPTORS);
            //Extract parameters
            CyUSBFSParameters parameters = new CyUSBFSParameters(query);
            if (parameters.CheckBootloaderReady() == false)
                supportBootloader = new CyCustErr(Properties.Resources.MSG_BOOTLOADER_SUPPORT);
            return supportBootloader;
        }

        #endregion

        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            //Extract parameters
            CyUSBFSParameters parameters = new CyUSBFSParameters(args.InstQueryV1);

            #region DRCs for endpoints

            // 1. Generate error in DRC when MaxPacketSize is greater then 512 and EMM is not "DMA w/AutomaticMM".
            if (!parameters.CheckEPMaxPacketSize(parameters.DeviceTree.Nodes[0]))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    Properties.Resources.ERR_EP_MAXPACKETSIZE);
            }

            // 2.a Generate DRC error when total sum of the MaxPacketSize for all EPs in one Configuration is greater 
            //then 512 when EMM has static allocation.
            if (!parameters.CheckSumEpBuffSizeStatAlloc(parameters.DeviceTree.Nodes[0]))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    Properties.Resources.MSG_DRC_EP_SUM_STATT_ALLOC);
            }

            // 2.b Generate DRC error when total sum of the MaxPacketSize for all EPs in one Device is greater then 512 
            // when EMM is not "DMA w/AutomaticMM".
            if (!parameters.CheckSumEpBuffSizeNotAutoDma(parameters.DeviceTree.Nodes[0]))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    Properties.Resources.MSG_DRC_EP_SUM_MANUAL);
            }

            // 3. Generate DRC error when total ISO EPs sum is greater then 1100 (this is bandwith limitation).
            if (!parameters.CheckSumEPMaxPacketSizeAll(parameters.DeviceTree.Nodes[0]))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    Properties.Resources.MSG_DRC_EP_SUM_AUTO);
            }

            // 4. Generate DRC error when Bulk EP MaxPacketSize is not from the list {8, 16, 32, 64}.
            if (!parameters.CheckEPBulkMaxPacketSize(parameters.DeviceTree.Nodes[0]))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    Properties.Resources.MSG_BULK_MAXPACKETSIZE);
            }

            #endregion DRCs for endpoints

            #region DRCs for BCD
            // 1. Generate DRC error if BCD is selected and if BCD is not supported for the selected device
            if (!parameters.CheckBattChargDetectDevicesSupport())
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                                             Properties.Resources.ERR_BATT_CHARG_DETECT_DEVICE);
            }
            // 2. Generate DRC warning when Battery Charging Detection is enabled and VBUS monitoring is disabled.
            else if (parameters.EnableBattChargDetect && !parameters.Mon_vbus)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning, 
                    Properties.Resources.WRG_DRC_BATT_CHARG_DETECT_CONFIG);
            }

            #endregion DRCs for BCD

            #region DRCs for VBUS Power Pad
            // 1. Generate DRC error when Battery Charging Detection is not available for the selected devices
            if (!parameters.CheckVbusPowerPadDevicesSupport())
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                                             Properties.Resources.ERR_VBUS_POWER_PAD_DEVICE);
            }
            #endregion DRCs for VBUS Power Pad

            #region DRCs for device tree

            // 1. Generate DRC error when Descriptor Root is empty
            if (parameters.DeviceTree.Nodes[0].Nodes.Count == 0)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    Properties.Resources.ERR_DESCRIPTOR_ROOT_EMPTY);
            }

            // 2. Generate DRC error when device descriptor is not full (does not contain interface descriptors)
            CyCustErr custErr = parameters.CheckAllDeviceDescsAreFull(parameters.DeviceTree.Nodes[0]);
            if (custErr.IsNotOK)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, custErr.Message);
            }

            // 3. Generate error when BOS descriptor is not available for the selected devices
            if (parameters.CheckBosDescIsPresent(parameters.DeviceTree.Nodes[0]) && !parameters.IsPSoC4AL_IpBlock)
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error,
                    Properties.Resources.ERR_BOS_DEVICE);
            }

            // 4. Generate error when device is Bus Powered and Max Power is set to 0.
            if (parameters.CheckMaxPower(parameters.DeviceTree.Nodes[0]))
            {
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning,
                    Properties.Resources.WRG_MAX_POWER);
            }


            #endregion DRCs for device tree

        }
    }
}
