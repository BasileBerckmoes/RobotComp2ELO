/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using CyDesigner.Common.Base;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    public class CyPinData
    {
        public const int PINS_PER_PORT = 8;

        #region Member Variables
        private readonly Func<string, CyCompDevParam> m_query;
        private readonly ICyDesignQuery_v1 m_designQuery;
        private readonly CyDeviceSupport m_deviceSupport;
        private readonly ICyInstEdit_v1 m_edit;
        private readonly CyErrorManager m_errMgr;

        // Add the formal parameters to the list for management by the cache, including side-effects for some.
        private readonly CyPinCache m_pinCache = new CyPinCache()
            .Add(Formal.Param.SIOGroups, false, Formal.SIOGroup_Default)
            .Add(Formal.Param.PinAliases, false, string.Empty)
            .Add(Formal.Param.PinTypes, true, Formal.PinTypes.Default, (value, index, data) =>
            {
                // Changing the pin type changes the defaults for drive mode and initial state - clear those caches
                string newDriveMode = GetDefaultDriveMode(Formal.GetPinType(value));
                data.m_pinCache.UpdateIfNotSetByUser(Formal.Param.DriveMode, index, newDriveMode);
                data.m_pins[index].DriveModeChanged();
                string newDriveState = data.GetDefaultDriveState(index);
                data.m_pinCache.UpdateIfNotSetByUser(Formal.Param.InitialDriveStates, index, newDriveState);
                data.m_pins[index].InitialDriveStateChanged();
                data.OnPinCountOrTypeChanged();
            })
            .Add(Formal.Param.DisplayInputHWConnections, Formal.Display_Default)
            .Add(Formal.Param.DisplayOutputHWConnections, Formal.Display_Default, (value, index, data) =>
            {
                // SW vs. HW for output can change initial drive state
                data.m_pins[index].IsOutHwChanged();
                string newInitState = data.GetDefaultDriveState(index);
                data.m_pinCache.UpdateIfNotSetByUser(Formal.Param.InitialDriveStates, index, newInitState);
                data.m_pins[index].InitialDriveStateChanged();
            })
            .Add(Formal.Param.ShowAnnotationTerm, Formal.ShowAnnotDefault)
            .Add(Formal.Param.DriveMode, null, null, (value, index, data) =>
            {
                data.m_pins[index].DriveModeChanged();
                string newDriveState = data.GetDefaultDriveState(index);
                data.m_pinCache.UpdateIfNotSetByUser(
                    Formal.Param.InitialDriveStates, index, newDriveState);
                data.m_pins[index].InitialDriveStateChanged();
            })
            .Add(Formal.Param.InitialDriveStates, false)
            .Add(Formal.Param.IOVoltages, Formal.IOVoltage_Default)
            .Add(Formal.Param.InputMultiplier, Formal.VrefMultipliers.Index_Default.ToString())
            .Add(Formal.Param.InterruptMode, Formal.AsString(CyInputInterruptTrigger.Default))
            .Add(Formal.Param.HotSwaps, Formal.HotSwap_Default)
            .Add(Formal.Param.InputBuffersEnabled)
            .Add(Formal.Param.InputSyncMode, Formal.AsString(CySyncMode.Default))
            .Add(Formal.Param.ThresholdLevels, Formal.AsString(CyInputThreshold.Default))
            .Add(Formal.Param.SlewRate, Formal.AsString(CyOutputSlewRate.Default))
            .Add(Formal.Param.OutputDriveLevels, Formal.AsString(CyOutputDriveLevel.Default))
            .Add(Formal.Param.OutputMultiplier, Formal.VrefMultipliers.Index_Default.ToString())
            .Add(Formal.Param.DriveStrength, Formal.AsString(CyDriveStrength.Default))
            .Add(Formal.Param.MaxFrequency, Formal.AsString(CyMaxFrequency.Default))
            .Add(Formal.Param.I2CMode, Formal.AsString(CyI2CMode.Default))
            .Add(Formal.Param.OutputCurrentCaps, Formal.AsString(CyOutputCurrentCap.Default))
            .Add(Formal.Param.OutputSyncMode, Formal.AsString(CySyncMode.Default))
            .Add(Formal.Param.OESyncs, Formal.OESyncs_Default);

        #endregion

        #region Unit Test code
        internal CyPinCache Cache { get { return m_pinCache; } }

        /// <summary>
        /// List all formal parameter values
        /// </summary>
        /// <returns>A list of formal parameter names.</returns>
        internal IEnumerable<string> FormalParameters
        {
            get
            {
                yield return Formal.Param.NumPins;
                yield return Formal.Param.DisplayAsBus;
                foreach (string param in m_pinCache.FormalParameters)
                    yield return param;
            }
        }
        #endregion

        #region Constructors
        public CyPinData(ICyInstEdit_v1 edit, CyErrorManager errMgr)
            : this(edit)
        {
            m_edit = edit;
            m_errMgr = errMgr;
            m_pinCache.SetEditor(edit);
        }

        public CyPinData(ICyInstQuery_v1 query)
            : this(query.GetCommittedParam, query.DeviceQuery)
        {
            m_designQuery = query.DesignQuery;
        }
        public CyPinData(ICyInstValidate_v1 query)
            : this(query.GetCommittedParam, query)
        {
        }

        // All other constructors call this one
        private CyPinData(Func<string, CyCompDevParam> query, ICyDeviceQuery_v1 deviceQuery)
        {
            m_query = query;
            m_deviceSupport = new CyDeviceSupport(deviceQuery);

            m_pinCache.Initialize(this, m_query, Validate);
        }
        #endregion

        #region Pins
        private byte? m_pinCount = null;
        public byte PinCount
        {
            get
            {
                if (null == m_pinCount)
                {
                    byte count = 1;
                    if (m_query != null)
                    {
                        CyCustErr err = m_query(Formal.Param.NumPins).TryGetValueAs<byte>(out count);
                        if (count < 1 || err.IsNotOk)
                            count = 1;
                    }
                    m_pinCount = count;

                    while (m_pins.Count < m_pinCount)
                    {
                        PerPin pin = new PerPin(m_pinCache, m_deviceSupport, m_pins.Count);
                        m_pins.Add(pin);
                    }
                }
                return m_pinCount.Value;
            }
            set
            {
                if (!m_pinCount.HasValue || m_pinCount.Value != value)
                {
                    if (m_edit.SetParamExpr(Formal.Param.NumPins, value.ToString()))
                    {
                        m_pinCount = value;
                        while (m_pins.Count < value)
                        {
                            PerPin pin = new PerPin(m_pinCache, m_deviceSupport, m_pins.Count);
                            m_pins.Add(pin);
                        }
                        OnPinCountOrTypeChanged();
                        Validate();
                    }
                }
            }
        }

        private bool? m_displayAsBus = null;
        public bool DisplayAsBus
        {
            get
            {
                if (null == m_displayAsBus)
                {
                    bool val;
                    m_query(Formal.Param.DisplayAsBus).TryGetValueAs(out val);
                    m_displayAsBus = val;
                }
                return m_displayAsBus.Value;
            }
            set
            {
                if (!m_displayAsBus.HasValue || m_displayAsBus.Value != value)
                {
                    if (m_edit.SetParamExpr(Formal.Param.DisplayAsBus, value.ToString()))
                    {
                        m_displayAsBus = value;
                        Validate();
                    }
                }
            }
        }

        internal void DisplayAsBusChanged()
        {
            m_displayAsBus = null;
        }

        internal void PinCountChanged()
        {
            m_pinCount = null;
        }

        public PerPin this[int idx]
        {
            get { return m_pins[idx]; }
        }

        private List<PerPin> m_pins = new List<PerPin>();
        public IList<PerPin> Pins
        {
            get
            {
                //We potentially have more pins in memory than are actually shown to the user,
                //We only want to return info for those that can be configured
                if (PinCount != m_pins.Count)
                {
                    PerPin[] pins = new PerPin[PinCount];
                    for (int i = 0; i < pins.Length; i++)
                        pins[i] = m_pins[i];
                    return new ReadOnlyCollection<PerPin>(pins);
                }

                return new ReadOnlyCollection<PerPin>(m_pins);
            }
        }

        public bool HasSameConnections
        {
            get
            {
                if (m_pins.Take(PinCount).Skip(1).Any(pin => !pin.HasSameConnectionsAs(m_pins[0])))
                    return false;
                return true;
            }
        }

        // Pass true to make a pair, and false to remove one
        #if !SIO_SUPPORT_ADDED
        [ExcludeFromCodeCoverage]
        #endif
        internal bool MakePair(int index0, int index1, bool pairUp)
        {
            if (index0 > index1)
            {
                int swap = index0;
                index0 = index1;
                index1 = swap;
            }
            Debug.Assert(index1 - index0 == 1);
 
            if (index1 >= PinCount)
                return false;

            Pins[index0].SioPair_1of2 = pairUp;
            Pins[index1].SioPair_2of2 = pairUp;
            return true;
        }

        #if !SIO_SUPPORT_ADDED
        [ExcludeFromCodeCoverage]
        #endif
        internal int GetSioGroupIndex(int index)
        {
            int sioCnt = Pins.Take(index + 1).Count(pin => pin.RequiresSIO && !pin.SioPair_2of2);
            return sioCnt - 1;
        }

        #region Per-Pin Settings
        internal static string GetDefaultDriveMode(CyPinType pinType)
        {
            if (pinType.Is(CyPinType.Digital_Out))
                return Formal.AsString(CyDriveMode.Strong_Drive);
            if (pinType.Is(CyPinType.Bidirectional))
                return Formal.AsString(CyDriveMode.Open_drain_Drive_low);
            if (pinType.Is(CyPinType.Digital_In))
                return Formal.AsString(CyDriveMode.High_impedance_digital);
            if (pinType == CyPinType.Analog)
                return Formal.AsString(CyDriveMode.High_impedance_analog);

            Debug.Fail("Unhandled pin type: " + pinType);
            return Formal.AsString(CyDriveMode.Default);
        }

        internal static string GetDefaultInputBuffersEnabled(CyPinType pinType)
        {
            return Formal.AsString(pinType.IsOneOf(CyPinType.Bidirectional | CyPinType.Digital_In));
        }

        internal string GetDefaultDriveState(int index)
        {
            PerPin pin = m_pins[index];
            // According to the SEROS, the default initial value for a DSI driven pin with OE should be '1'
            if (pin.Type.Is(CyPinType.Analog) ||
                pin.Type.Is(CyPinType.Bidirectional) ||
                pin.Type.Is(CyPinType.Digital_Out) && (pin.Type.Is(CyPinType.OE) || pin.TypeIsDigitalOutputHw))
                return Formal.High;

            switch (pin.GeneralDriveMode)
            {
                case CyDriveMode.High_impedance_analog:
                case CyDriveMode.Strong_Drive:
                case CyDriveMode.High_impedance_digital:
                case CyDriveMode.Open_drain_Drive_high:
                case CyDriveMode.Open_drain_Drive_low:
                case CyDriveMode.Resistive_pull_down:
                    return Formal.Low;
                case CyDriveMode.Resistive_pull_up:
                case CyDriveMode.Resistive_pull_up_down:
                    return Formal.High;
                default:
                    Debug.Fail(string.Format(Resource1.UnhandledDriveMode, pin.GeneralDriveMode));
                    return Formal.Low;
            }
        }

        #endregion
        #endregion

        #region Events
        internal event Action PinCountOrTypeChanged;

        private void OnPinCountOrTypeChanged()
        {
            Action evt = PinCountOrTypeChanged;
            if (null != evt)
                evt();
        }
        #endregion

        #region Functions
        public void DeletePin(int idx)
        {
            if (idx < 0 || idx >= m_pins.Count)
            {
                Debug.Fail("Invalid item to delete");
                return;
            }

            if (m_pins[idx].IsPairedSio)
            {
                // If paired, unpair both this and the other pin in the pair to avoid regrouping pairs
                int otherIdx = PerPin.GetOtherSIOIndex(m_pins[idx]); // Can't calculate after the next step
                MakePair(idx, otherIdx, false);
            }

            for (int i = idx + 1; i < m_pinCount; i++)
                m_pins[i].Index--;

            m_pins.RemoveAt(idx);
            PinCount--;
        }

        public void MoveUp(int idx)
        {
            if (idx > 0 && idx < m_pins.Count)
                SwapPins(idx, idx - 1);
            else
                Debug.Fail("Invalid item to move up");
        }

        public void MoveDown(int idx)
        {
            if (idx < m_pins.Count - 1)
                SwapPins(idx, idx + 1);
            else
                Debug.Fail("Invalid item to move down");
        }

        private void SwapPins(int first, int second)
        {
            PerPin firstPin = m_pins[first];
            PerPin secondPin = m_pins[second];
            IList<KeyValuePair<string, string>> formalsFirst = firstPin.ExportFormals();
            IList<KeyValuePair<string, string>> formalsSecond = secondPin.ExportFormals();
            // Move the pins, update their indices, then restore their formals. Changing the index
            // updates the formals, so we need to perform the restoration last.
            m_pins[first] = secondPin;
            m_pins[second] = firstPin;

            secondPin.Index = first;
            firstPin.Index = second;

            firstPin.RestoreFormals(formalsFirst);
            secondPin.RestoreFormals(formalsSecond);
        }

        #if !SIO_SUPPORT_ADDED
        [ExcludeFromCodeCoverage]
        #endif
        internal byte GetSioGroupCnt()
        {
            byte cnt = (byte)m_pins.Take(PinCount).Count(pin => pin.RequiresSIO && !pin.SioPair_2of2);
            return cnt;
        }

        public string GetPinPoundDefineName(int index)
        {
            if (null != m_query)
            {
                string instName = m_query(Formal.Param.Builtin_InstName).Value;

                string alias = m_pins[index].Alias;
                return string.IsNullOrEmpty(alias)
                    ? string.Format("{0}_{1}", instName, index)
                    : string.Format("{0}_{1}", instName, alias);
            }
            return string.Empty;
        }

        public CyPinAssignmentInfo_v1 GetAssignment(int index)
        {
            if (null != m_designQuery && m_designQuery.DesignInfoAvailable)
            {
                List<CyPinAssignmentInfo_v1> assignmentInfo = m_designQuery.GetPinAssignmentInfo_v1(index);
                if (assignmentInfo.Count == 1 && assignmentInfo[0].IsAssigned)
                    return assignmentInfo[0];
            }

            return null;
        }
        #endregion

        #region Validators
        private interface ICyErrorHandler
        {
            void AddError(string msg, Formal.ErrorKey settingOwner);
        }
        private class CyInstValidateErrorHandler : ICyErrorHandler
        {
            private ICyInstValidate_v1 m_instValidate;

            public CyInstValidateErrorHandler(ICyInstValidate_v1 instValidate)
            {
                m_instValidate = instValidate;
            }

            void ICyErrorHandler.AddError(string msg, Formal.ErrorKey owner)
            {
                m_instValidate.AddError(Formal.KeyParam(owner), new CyCustErr(msg));
            }
        }
        private class CyErrorMgrErrorHandler : ICyErrorHandler
        {
            private CyErrorManager m_errMgr;

            public CyErrorMgrErrorHandler(CyErrorManager instValidate)
            {
                m_errMgr = instValidate;
            }

            void ICyErrorHandler.AddError(string msg, Formal.ErrorKey owner)
            {
                m_errMgr.SetError(owner, msg);
            }
        }

        public static CyCustErr ValidateAlias(int index, string name)
        {
            string msg;
            return !string.IsNullOrEmpty(name) && !CyBasic.IsValidCCppIdentifierName(name, out msg)
                ? new CyCustErr(string.Format(Resource1.Err_NotValidCIdentifier, index, name, msg))
                : CyCustErr.Ok;
        }

        private void ValidateAlias(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < Pins.Count; ++i)
            {
                CyCustErr err = ValidateAlias(i, Pins[i].Alias);
                if (err.IsNotOk)
                    errHandler.AddError(err.Message, Formal.ErrorKey.PIN_ALIAS);
            }
        }

        /// <summary>
        /// This method is also called as a delegate to the PerPin class and to the cache
        /// </summary>
        internal void Validate()
        {
            m_edit.CommitParamExprs();
            m_errMgr.ClearErrors();
            Validate(new CyErrorMgrErrorHandler(m_errMgr));
        }

        public void Validate(ICyInstValidate_v1 instVal)
        {
            // The validator used had better be the same one as used to create me.
            Debug.Assert(instVal == m_deviceSupport.Query);
            Validate(new CyInstValidateErrorHandler(instVal));
        }

        private void Validate(ICyErrorHandler errHandler)
        {
            ValidateAlias(errHandler);

            //Validate per-pin data. Be sure to validate the GUI visible param not the corresponding verilog one
            //as that is the only way for the param to have an error show up on it when the user is entering values.

            CheckAtLeastOneTypeSelected(errHandler);
            CheckDisplayAsBusRequiresHomogenous(errHandler);

            // HSIOM-routed inputs only reliably work in high-z mode.
            // So on parts without a port adapter disallow other modes for hw routed inputs.
            if (!m_deviceSupport.HasPortAdapter)
            {
                CheckModesRequiringPortAdapter(errHandler);
                CheckCannotUsePAOnDevice(errHandler);
            }

            if (!m_deviceSupport.HasSyncModes)
            {
                CheckInputSync(errHandler);
                CheckOutputSync(errHandler);
            }

            CheckCannotBeResistivePullAndVrefOut(errHandler);

            CheckCannotUseAnalogIfSIO(errHandler);
            CheckSIOPairSettingsMatch(errHandler);
            if (!m_deviceSupport.HasSIO)
                CheckCannotUsePinTypeOnDevice(errHandler, pin => pin.GetSIOCauses());
            CheckCannotUsePinTypeOnDevice(errHandler, pin => pin.GetOVTCauses());
            CheckCannotUsePinTypeOnDevice(errHandler, pin => pin.OutputCurrentCauses());
            CheckCannotUsePinTypeOnDevice(errHandler, pin => pin.FrequencyCauses());
            CheckCannotUsePinTypeOnDevice(errHandler, pin => pin.SupplyVoltageCauses());

            CheckCannotRequireSIOAndOVT(errHandler);
            CheckSIOVrefSettingsMatch(errHandler);
            CheckVrefMultiplierRequirements(errHandler);
        }

        private void CheckInputSync(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < PinCount; i++)
            {
                if (m_pins[i].InputSyncMode == CySyncMode.Double)
                {
                    string error = string.Format(Resource1.Err_InputSyncInvalid, i, Resource1.SyncMode_DoubleSync);
                    errHandler.AddError(error, Formal.ErrorKey.INPUT_SYNC_MODE);
                }
                else if (m_pins[i].InputSyncMode == CySyncMode.Single)
                {
                    string error = string.Format(Resource1.Err_InputSyncInvalid, i, Resource1.SyncMode_SingleSync);
                    errHandler.AddError(error, Formal.ErrorKey.INPUT_SYNC_MODE);
                }
            }
        }

        private void CheckOutputSync(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < PinCount; i++)
            {
                if (m_pins[i].OutputSyncMode == CySyncMode.Single)
                {
                    string error = string.Format(Resource1.Err_OutputSyncInvalid, i, Resource1.SyncMode_SingleSync);
                    errHandler.AddError(error, Formal.ErrorKey.OUTPUT_SYNC_MODE);
                }
            }
        }

        private void CheckDisplayAsBusRequiresHomogenous(ICyErrorHandler errHandler)
        {
            if (DisplayAsBus && !HasSameConnections)
                errHandler.AddError(Resource1.Err_DisplayAsBusRequiresHomogenous, Formal.ErrorKey.DISPLAY_AS_BUS);
        }

        private void CheckCannotBeResistivePullAndVrefOut(ICyErrorHandler errHandler)
        {
            foreach (PerPin pin in m_pins.Take(PinCount).Where(pin => pin.OutputDriveLevel == CyOutputDriveLevel.Vref))
            {
                if (pin.GeneralDriveMode == CyDriveMode.Resistive_pull_up ||
                    pin.GeneralDriveMode == CyDriveMode.Resistive_pull_down ||
                    pin.GeneralDriveMode == CyDriveMode.Resistive_pull_up_down)
                {
                    errHandler.AddError(Resource1.Err_P35_ResistivePullAndVrefOut, Formal.ErrorKey.GENERAL_DRIVE_MODE);
                    errHandler.AddError(Resource1.Err_P35_ResistivePullAndVrefOut, Formal.ErrorKey.OUTPUT_DRIVE_LEVEL);
                }
            }
        }

        /// <summary>
        /// Ensures that, if a pin uses an sio internal vref, the following rules are met:
        /// * The minimum supply voltage is set
        /// * The multiplier output is less than VDDIO - 400 mV
        /// </summary>
        /// <param name="errHandler"></param>
        private void CheckVrefMultiplierRequirements(ICyErrorHandler errHandler)
        {
            const double INTERNAL_VREF_VALUE = 1.2;
            for (int i = 0; i < PinCount; ++i)
            {
                PerPin pin = m_pins[i];
                double minimumSupply = 0;
                bool hasMinimumSupply = !string.IsNullOrEmpty(pin.GeneralMinimumSupply) &&
                                        double.TryParse(pin.GeneralMinimumSupply, out minimumSupply);

                if (pin.Type.IsOneOf(CyPinType.Digital_Out | CyPinType.Bidirectional) &&
                    pin.OutputDriveLevel == CyOutputDriveLevel.Vref_Internal)
                {
                    if (!hasMinimumSupply)
                    {
                        string error = string.Format(Resource1.Err_M0S8_VrefDriveLevelRequiresMinimumSupply, i);
                        errHandler.AddError(error, Formal.ErrorKey.OUTPUT_DRIVE_LEVEL);
                        errHandler.AddError(error, Formal.ErrorKey.GENERAL_MINIMUM_SUPPLY);
                    }
                    else
                    {
                        double multiplierOutput = INTERNAL_VREF_VALUE * pin.OutputMultiplier;
                        double maxMultiplierOutput = minimumSupply - 0.4;
                        if (multiplierOutput > maxMultiplierOutput)
                        {
                            string error = string.Format(Resource1.Err_M0S8_MultiplierOutputTooHigh, i);
                            errHandler.AddError(error, Formal.ErrorKey.OUTPUT_MULTIPLIER);
                            errHandler.AddError(error, Formal.ErrorKey.GENERAL_MINIMUM_SUPPLY);
                        }
                    }
                }
                if (pin.Type.IsOneOf(CyPinType.Digital_In | CyPinType.Bidirectional) &&
                   (pin.InputThreshold == CyInputThreshold.Vref_internal || pin.InputThreshold == CyInputThreshold.Pt5_Vref_internal))
                {
                    if (!hasMinimumSupply)
                    {
                        string error = string.Format(Resource1.Err_M0S8_VrefThresholdRequiresMinimumSupply, i);
                        errHandler.AddError(error, Formal.ErrorKey.INPUT_THRESHOLD);
                        errHandler.AddError(error, Formal.ErrorKey.GENERAL_MINIMUM_SUPPLY);
                    }
                    else
                    {
                        double vrefVal = (pin.InputThreshold == CyInputThreshold.Pt5_Vref_internal) ?
                            INTERNAL_VREF_VALUE * 0.5 : INTERNAL_VREF_VALUE;
                        double multiplierOutput = vrefVal * pin.InputMultiplier;
                        double maxMultiplierOutput = minimumSupply - 0.4;
                        if (multiplierOutput > maxMultiplierOutput)
                        {
                            string error = string.Format(Resource1.Err_M0S8_MultiplierOutputTooHigh, i);
                            errHandler.AddError(error, Formal.ErrorKey.INPUT_MULTIPLIER);
                            errHandler.AddError(error, Formal.ErrorKey.GENERAL_MINIMUM_SUPPLY);
                        }
                    }
                }
            }
        }

        /// <summary>
        /// If a pin is both an input and an output, ensure that:
        /// * Vref sources match if both input and output use them
        /// * Multipliers match, if both input and output use vref
        /// </summary>
        /// <param name="errHandler"></param>
        private void CheckSIOVrefSettingsMatch(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < PinCount; ++i)
            {
                PerPin pin = Pins[i];
                if (pin.Type.Is(CyPinType.Bidirectional) ||
                    pin.Type.Is(CyPinType.Digital_In | CyPinType.Digital_Out))
                {
                    CyVrefSource inputSource = GetVrefSource(pin.InputThreshold);
                    CyVrefSource outputSource = GetVrefSource(pin.OutputDriveLevel);
                    if (inputSource != CyVrefSource.DontCare && outputSource != CyVrefSource.DontCare)
                    {
                        if (inputSource != outputSource)
                        {
                            string message = string.Format(Resource1.Err_M0S8_SioRefSelMustMatch, i);
                            errHandler.AddError(message, Formal.ErrorKey.INPUT_THRESHOLD);
                            errHandler.AddError(message, Formal.ErrorKey.OUTPUT_DRIVE_LEVEL);
                        }

                        if (pin.InputMultiplier != pin.OutputMultiplier)
                        {
                            string message = string.Format(Resource1.Err_M0S8_MultipliersMustMatch, i);
                            errHandler.AddError(message, Formal.ErrorKey.INPUT_MULTIPLIER);
                            errHandler.AddError(message, Formal.ErrorKey.OUTPUT_MULTIPLIER);
                        }
                    }
                }
            }
        }

        private static CyVrefSource GetVrefSource(CyInputThreshold threshold)
        {
            switch (threshold)
            {
                case CyInputThreshold.Pt5_Vref:
                case CyInputThreshold.Vref:
                    return CyVrefSource.Routed;
                case CyInputThreshold.Pt5_Vref_internal:
                case CyInputThreshold.Vref_internal:
                    return CyVrefSource.Internal;
                default:
                    return CyVrefSource.DontCare;
            }
        }

        private static CyVrefSource GetVrefSource(CyOutputDriveLevel driveLevel)
        {
            switch (driveLevel)
            {
                case CyOutputDriveLevel.Vref:
                    return CyVrefSource.Routed;
                case CyOutputDriveLevel.Vref_Internal:
                    return CyVrefSource.Internal;
                default:
                    return CyVrefSource.DontCare;
            }
        }

        private bool SIOVrefSourcesCompatible(CyVrefSource source0, CyVrefSource source1)
        {
            return source0 == CyVrefSource.DontCare ||
                   source1 == CyVrefSource.DontCare ||
                   source0 == source1;
        }

        #if !SIO_SUPPORT_ADDED
        [ExcludeFromCodeCoverage]
        #endif
        private void CheckSIOPairSettingsMatch(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < PinCount - 1; i++)
            {
                if (m_pins[i].SioPair_1of2)
                {
                    PerPin pin1 = m_pins[i];
                    PerPin pin2 = m_pins[i + 1];
                    if (!SIOVrefSourcesCompatible(pin1.VRefSource, pin2.VRefSource))
                    {
                        errHandler.AddError(string.Format(Resource1.Err_M0S8_SioPairRefSelMustMatch, i),
                            Formal.ErrorKey.INPUT_THRESHOLD);
                        errHandler.AddError(string.Format(Resource1.Err_M0S8_SioPairRefSelMustMatch, i),
                            Formal.ErrorKey.OUTPUT_DRIVE_LEVEL);
                        errHandler.AddError(string.Format(Resource1.Err_M0S8_SioPairRefSelMustMatch, i + 1),
                            Formal.ErrorKey.INPUT_THRESHOLD);
                        errHandler.AddError(string.Format(Resource1.Err_M0S8_SioPairRefSelMustMatch, i + 1),
                            Formal.ErrorKey.OUTPUT_DRIVE_LEVEL);
                    }

                    if ((pin1.Type & pin2.Type).Is(CyPinType.Digital_In))
                    {
                        if (pin1.InputThreshold != pin2.InputThreshold)
                        {
                            errHandler.AddError(string.Format(Resource1.Err_SIOPairInputsDontMatch, i),
                                Formal.ErrorKey.INPUT_THRESHOLD);
                            errHandler.AddError(string.Format(Resource1.Err_SIOPairInputsDontMatch, i + 1),
                                Formal.ErrorKey.INPUT_THRESHOLD);
                        }
                    }
                    else if ((pin1.Type & pin2.Type).Is(CyPinType.Digital_Out))
                    {
                        if (pin1.OutputDriveLevel != pin2.OutputDriveLevel)
                        {
                            errHandler.AddError(string.Format(Resource1.Err_SIOPairOutputsDontMatch, i),
                                Formal.ErrorKey.OUTPUT_DRIVE_LEVEL);
                            errHandler.AddError(string.Format(Resource1.Err_SIOPairOutputsDontMatch, i + 1),
                                Formal.ErrorKey.OUTPUT_DRIVE_LEVEL);
                        }
                    }
                    if (pin1.MultiplierIndex != pin2.MultiplierIndex)
                    {
                        errHandler.AddError(string.Format(Resource1.Err_M0S8_SioPairMultipliersMustMatch, i),
                            Formal.ErrorKey.OUTPUT_MULTIPLIER);
                        errHandler.AddError(string.Format(Resource1.Err_M0S8_SioPairMultipliersMustMatch, i),
                            Formal.ErrorKey.INPUT_MULTIPLIER);
                        errHandler.AddError(string.Format(Resource1.Err_M0S8_SioPairMultipliersMustMatch, i + 1),
                            Formal.ErrorKey.OUTPUT_MULTIPLIER);
                        errHandler.AddError(string.Format(Resource1.Err_M0S8_SioPairMultipliersMustMatch, i + 1),
                            Formal.ErrorKey.INPUT_MULTIPLIER);
                    }
                }
            }
        }

        #if !SIO_SUPPORT_ADDED
        [ExcludeFromCodeCoverage]
        #endif
        private void CheckCannotUseAnalogIfSIO(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < PinCount; i++)
            {
                if ((m_pins[i].Type.Is(CyPinType.Analog)) && m_pins[i].RequiresSIO)
                {
                    List<Formal.ErrorKey> errors = new List<Formal.ErrorKey>();
                    errors.Add(Formal.ErrorKey.TYPE_IS_ANALOG);

                    if (m_pins[i].GeneralHotSwap)
                        errors.Add(Formal.ErrorKey.INPUT_HOT_SWAP);
                    if (m_pins[i].OutputDriveLevel == CyOutputDriveLevel.Vref)
                        errors.Add(Formal.ErrorKey.OUTPUT_DRIVE_LEVEL);
                    if (m_pins[i].InputThreshold != CyInputThreshold.CMOS &&
                        m_pins[i].InputThreshold != CyInputThreshold.CMOS_LVTTL &&
                        m_pins[i].InputThreshold != CyInputThreshold.LVTTL)
                    {
                        errors.Add(Formal.ErrorKey.INPUT_THRESHOLD);
                    }

                    if (errors.Count > 1)
                    {
                        string msg = string.Format(Resource1.Err_CannotUseAnalogAndSIO, i);
                        foreach (Formal.ErrorKey err in errors)
                            errHandler.AddError(msg, err);
                    }
                }
            }
        }

        private void CheckModesRequiringPortAdapter(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < PinCount; ++i)
            {
                PerPin pin = m_pins[i];
                if (pin.Type.Is(CyPinType.Digital_In) &&
                    !pin.Type.IsOneOf(CyPinType.Bidirectional | CyPinType.Digital_Out | CyPinType.OE) &&
                    pin.TypeIsDigitalInputHw)
                {
                    switch (pin.GeneralDriveMode)
                    {
                        case CyDriveMode.High_impedance_digital:
                        case CyDriveMode.High_impedance_analog:
                        case CyDriveMode.Resistive_pull_up:
                        case CyDriveMode.Resistive_pull_up_down:
                        case CyDriveMode.Resistive_pull_down:
                            break;
                        default:
                            string error = string.Format(Resource1.Err_DriveModeRequiresPA, i);
                            errHandler.AddError(error, Formal.ErrorKey.GENERAL_DRIVE_MODE);
                            break;
                    }
                }
            }
        }

        private void CheckCannotUsePinTypeOnDevice(ICyErrorHandler errHandler,
                                                    Func<PerPin, IEnumerable<PinRequirementError>> getCauses)
        {
            for (int i = 0; i < PinCount; ++i)
            {
                IEnumerable<PinRequirementError> causes = getCauses(m_pins[i]);
                foreach (PinRequirementError cause in causes)
                {
                    string error = string.Format(Resource1.Err_CannotUsePinTypeonDevice, i, cause.Requirement);
                    errHandler.AddError(error, cause.Key);
                }
            }
        }

        private void CheckCannotRequireSIOAndOVT(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < PinCount; ++i)
            {
                PerPin pin = m_pins[i];

                IEnumerable<PinRequirementError> ovtCauses = pin.GetOVTCauses();
                if (!ovtCauses.Any())
                    continue;

                IEnumerable<PinRequirementError> sioCauses = pin.GetSIOCauses();
                if (!sioCauses.Any())
                    continue;

                // Flag each field which requires OVT, mentioning the first field which requires SIO. 
                // Do the same for each field which requires SIO
                foreach (PinRequirementError cause in ovtCauses)
                {
                    // Only look at the first SIO cause to avoid an overwhelming cascade of errors
                    string error = string.Format(Resource1.Err_OvtAndSioFeaturesUsed, i, CyDeviceSupport.OVT,
                        Formal.KeyFriendlyName(cause.Key), CyDeviceSupport.SIO);
                    errHandler.AddError(error, cause.Key);
                }
                foreach (PinRequirementError cause in sioCauses)
                {
                    // Only look at the first OVT cause to avoid an overwhelming cascade of errors
                    string error = string.Format(Resource1.Err_OvtAndSioFeaturesUsed, i, CyDeviceSupport.SIO,
                        Formal.KeyFriendlyName(cause.Key), CyDeviceSupport.OVT);
                    errHandler.AddError(error, cause.Key);
                }
            }
        }

        private void CheckCannotUsePAOnDevice(ICyErrorHandler errHandler)
        {
            foreach (PerPin pin in m_pins)
            {
                if (pin.OutputSyncMode != CySyncMode.Transparent && pin.OutputSyncMode != CySyncMode.Single)
                    errHandler.AddError(Resource1.Err_CannotUsePAonDevice, Formal.ErrorKey.OUTPUT_SYNC_MODE);
                if (pin.OutputEnableSynchronized)
                    errHandler.AddError(Resource1.Err_CannotUsePAonDevice, Formal.ErrorKey.OUTPUT_ENABLE_SYNCHRONIZED);
            }
        }

        private void CheckAtLeastOneTypeSelected(ICyErrorHandler errHandler)
        {
            for (int i = 0; i < Pins.Count; ++i)
            {
                if (Pins[i].Type == CyPinType.None)
                {
                    string err = string.Format(Resource1.Err_CannotUncheckAllTypes, i);
                    errHandler.AddError(err, Formal.ErrorKey.GENERAL_TYPE);
                }
            }
        }
        #endregion

        public class PerPin
        {
            #region Member Variables
            private readonly CyPinCache m_pinCache;
            private readonly CyDeviceSupport m_deviceSupport;
            private int m_index;
            #endregion

            public PerPin(CyPinCache cache, CyDeviceSupport deviceSupport, int index)
            {
                m_pinCache = cache;
                m_deviceSupport = deviceSupport;
                m_index = index; // Don't use the setter - want to bypass PropagateNewIndex
            }

            #region Force cache reloads
            internal void DriveModeChanged()
            {
                m_generalDriveMode = null;
            }

            internal void InputSyncChanged()
            {
                m_inputSyncMode = null;
            }

            internal void InitialDriveStateChanged()
            {
                m_generalInitialState = null;
            }

            internal void IsOutHwChanged()
            {
                m_typeIsDigitalOutputHw = null;
            }
            #endregion

            #region Pins-Global
            public int Index
            {
                get { return m_index; }
                set
                {
                    int oldIndex = m_index;
                    m_index = value;
                    m_pinCache.PropagateNewIndex(oldIndex, m_index, Type);
                }
            }

            public bool SioPair_1of2
            {
                get { return SIOPairID == 0; }
                internal set { SIOPairID = value ? 0 : -1; }
            }
            public bool SioPair_2of2
            {
                get { return SIOPairID == 1; }
                internal set { SIOPairID = value ? 1 : -1; }
            }
            public bool IsPairedSio { get { return SioPair_1of2 || SioPair_2of2; } }

            [ExcludeFromCodeCoverage]
            private int SIOPairID
            {
                get
                {
                    // Deliberately not cached, as this can change if pins preceding us are
                    // grouped/ungrouped/changed between being an SIO or not
                    string grouped = m_pinCache.Get(Formal.Param.SIOGroups, Index, Type);
                    if (grouped == Formal.Grouped)
                    {
                        // If there are an odd number of grouped SIOs preceding us, then we 
                        // are the second SIO in a pair. Otherwise, we're the first
                        int numPrecedingGrouped = 0;
                        for (int i = Index - 1; i >= 0; i--)
                        {
                            grouped = m_pinCache.Get(Formal.Param.SIOGroups, i, Type);
                            if (grouped != Formal.Grouped)
                                break;

                            ++numPrecedingGrouped;
                        }
                        return numPrecedingGrouped % 2;
                    }

                    return -1;
                }
                set
                {
                    string val = (value >= 0) ? Formal.Grouped : Formal.Not_grouped;
                    if (m_pinCache.Set(Formal.Param.SIOGroups, val, Index))
                        m_pinCache.Validate();
                }
            }

            private string m_alias = null;
            public string Alias
            {
                get
                {
                    if (null == m_alias)
                        m_alias = m_pinCache.Get(Formal.Param.PinAliases, Index, Type);
                    return m_alias;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.PinAliases, value, Index))
                    {
                        m_alias = value.Trim().Replace(" ", "_");
                        m_pinCache.Validate();
                    }
                }
            }

            internal IList<KeyValuePair<string, string>> ExportFormals()
            {
                return m_pinCache.ExportFormals(Index, Type);
            }

            internal void RestoreFormals(IList<KeyValuePair<string, string>> exprs)
            {
                m_pinCache.RestoreFormals(exprs, Index);
            }
            #endregion

            #region Pins-Type
            private CyPinType? m_type = null;
            public CyPinType Type
            {
                get
                {
                    if (null == m_type)
                        m_type = Formal.GetPinType(m_pinCache.Get(Formal.Param.PinTypes, Index, CyPinType.OE));
                    return m_type.Value;
                }
                set
                {
                    //Set before saving to handle side-effects correctly; ugly but less so then passing delegates
                    CyPinType? oldType = m_type;
                    m_type = value;
                    if (!m_pinCache.Set(Formal.Param.PinTypes, Formal.AsString(value), Index))
                        m_type = oldType;

                    if (null != m_type)
                        InputBufferEnabled = m_type.Value.IsOneOf(CyPinType.Bidirectional | CyPinType.Digital_In);
                    m_pinCache.Validate();
                }
            }

            private bool? m_typeIsDigitalInputHw = null;
            public bool TypeIsDigitalInputHw
            {
                get
                {
                    if (null == m_typeIsDigitalInputHw)
                        m_typeIsDigitalInputHw = (Formal.True == m_pinCache.Get(Formal.Param.DisplayInputHWConnections, Index, Type));
                    return m_typeIsDigitalInputHw.Value;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.DisplayInputHWConnections, Formal.AsString(value), Index))
                    {
                        m_typeIsDigitalInputHw = value;
                        m_pinCache.Validate();
                    }
                }
            }

            private bool? m_typeIsDigitalOutputHw = null;
            public bool TypeIsDigitalOutputHw
            {
                get
                {
                    if (null == m_typeIsDigitalOutputHw)
                        m_typeIsDigitalOutputHw = (Formal.True == m_pinCache.Get(Formal.Param.DisplayOutputHWConnections, Index, Type));
                    return m_typeIsDigitalOutputHw.Value;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.DisplayOutputHWConnections, Formal.AsString(value), Index))
                    {
                        m_typeIsDigitalOutputHw = value;
                        m_pinCache.Validate();
                    }
                }
            }

            private bool? m_typeShowExternalTerm = null;
            public bool TypeShowExternalTerm
            {
                get
                {
                    if (null == m_typeShowExternalTerm)
                        m_typeShowExternalTerm = (Formal.True == m_pinCache.Get(Formal.Param.ShowAnnotationTerm, Index, Type));
                    return m_typeShowExternalTerm.Value;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.ShowAnnotationTerm, Formal.AsString(value), Index))
                    {
                        m_typeShowExternalTerm = value;
                        m_pinCache.Validate();
                    }
                }
            }
            #endregion

            #region Pins-General
            internal int MultiplierIndex
            {
                get
                {
                    int multiplier = 0;
                    // Multiplier must match for input and output, so only check the output multiplier if we're bidirectional
                    if (Type.IsOneOf(CyPinType.Digital_Out | CyPinType.Bidirectional) &&
                        OutputDriveLevel != CyOutputDriveLevel.Vddio) // Only vref-based drive levels impact this setting
                    {
                        multiplier = Formal.VrefMultipliers.IndexOf(OutputMultiplier);
                    }
                    else if (Type.Is(CyPinType.Digital_In))
                    {
                        // Multiplier is only set if input threshold is vref-based
                        switch (InputThreshold)
                        {
                            case CyInputThreshold.Pt5_Vref:
                            case CyInputThreshold.Pt5_Vref_internal:
                            case CyInputThreshold.Vref:
                            case CyInputThreshold.Vref_internal:
                                multiplier = Formal.VrefMultipliers.IndexOf(InputMultiplier);
                                break;
                            default:
                                multiplier = 0;
                                break;
                        }
                    }
                    return multiplier;
                }
            }

            internal CyVrefSource VRefSource
            {
                get
                {
                    CyVrefSource result = CyVrefSource.DontCare;
                    if (Type.IsOneOf(CyPinType.Digital_In | CyPinType.Bidirectional))
                    {
                        result = CyPinData.GetVrefSource(InputThreshold);
                    }
                    // This is required to match between input and output, so only check output if input was don't care
                    // Input could have used a non-vref threshold, so check bidirectional here as well
                    if (result == CyVrefSource.DontCare &&
                        Type.IsOneOf(CyPinType.Digital_Out | CyPinType.Bidirectional))
                    {
                        result = CyPinData.GetVrefSource(OutputDriveLevel);
                    }
                    return result;
                }
            }

            private CyDriveMode? m_generalDriveMode = null;
            public CyDriveMode GeneralDriveMode
            {
                get
                {
                    if (null == m_generalDriveMode)
                        m_generalDriveMode = GetDriveMode();
                    return m_generalDriveMode.Value;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.DriveMode, Formal.AsString(value), Index))
                    {
                        m_generalDriveMode = value;
                        m_pinCache.Validate();
                    }
                }
            }

            CyDriveMode GetDriveMode()
            {
                #if !V0_5_PHASEDOUT
                string mode = m_pinCache.Get(Formal.Param.DriveMode, Index, Type);
                if (mode == "HI_ZA")
                    return CyDriveMode.High_impedance_analog;
                if (mode == "HI_ZD")
                    return CyDriveMode.High_impedance_digital;
                if (mode == "RES_UP")
                    return CyDriveMode.Resistive_pull_up;
                if (mode == "RES_DWN")
                    return CyDriveMode.Resistive_pull_down;
                if (mode == "OPEN_DR_LO")
                    return CyDriveMode.Open_drain_Drive_low;
                if (mode == "OPEN_DR_HI")
                    return CyDriveMode.Open_drain_Drive_high;
                if (mode == "STRONG")
                    return CyDriveMode.Strong_Drive;
                if (mode == "RES_UP_DWN")
                    return CyDriveMode.Resistive_pull_up_down;
                return Formal.GetValue<CyDriveMode>(mode);
                #else
                return m_pinCache.Get<CyDriveMode>(Formal.Param.DriveMode, Index, Type);
                #endif
            }

            private bool? m_generalInitialState = null;
            public bool GeneralInitialState
            {
                get
                {
                    // If we're an output pin with a hw connection, initial state won't behave
                    // in the way the user expects, so always force it to high
                    if (Type.Is(CyPinType.Digital_Out) && TypeIsDigitalOutputHw)
                        return true; // Don't update the cache since this is just a temporary override
                    if (null == m_generalInitialState)
                        m_generalInitialState = GetInitialDriveState();
                    return m_generalInitialState.Value;
                }
                set
                {
                    string val = value ? Formal.High : Formal.Low;
                    if (m_pinCache.Set(Formal.Param.InitialDriveStates, val, Index))
                    {
                        m_generalInitialState = value;
                        m_pinCache.Validate();
                    }
                }
            }

            bool GetInitialDriveState()
            {
                #if !V0_5_PHASEDOUT
                string state = m_pinCache.Get(Formal.Param.InitialDriveStates, Index, Type);
                if (state == "INIT_LO")
                    return false;
                if (state == "INIT_HI")
                    return true;
                return Formal.High == state;
                #else
                return Formal.High == m_pinCache.Get(Formal.Param.InitialDriveStates, Index, Type);
                #endif
            }

            private string m_generalMinimumSupply = null;
            public string GeneralMinimumSupply
            {
                get
                {
                    if (null == m_generalMinimumSupply)
                        m_generalMinimumSupply = m_pinCache.Get(Formal.Param.IOVoltages, Index, Type);
                    return (m_generalMinimumSupply != Formal.IOVoltage_Default) ? m_generalMinimumSupply : "";
                }
                set
                {
                    string newSupply = string.IsNullOrEmpty(value) ? Formal.IOVoltage_Default : value.Trim();
                    if (m_pinCache.Set(Formal.Param.IOVoltages, newSupply, Index))
                    {
                        m_generalMinimumSupply = newSupply;
                        m_pinCache.Validate();
                    }
                }
            }

            private CyMaxFrequency? m_maxFrequency;
            public CyMaxFrequency MaxFrequency
            {
                get
                {
                    if (null == m_maxFrequency)
                        m_maxFrequency = m_pinCache.Get<CyMaxFrequency>(Formal.Param.MaxFrequency, Index, Type);
                    return m_maxFrequency.Value;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.MaxFrequency, Formal.AsString(value), Index))
                    {
                        m_maxFrequency = value;
                        if (m_maxFrequency != CyMaxFrequency.MHz_NA)
                            I2CMode = CyI2CMode.I2C_NA;
                        m_pinCache.Validate();
                    }
                }
            }

            private CyI2CMode? m_i2cMode;
            public CyI2CMode I2CMode
            {
                get
                {
                    if (null == m_i2cMode)
                        m_i2cMode = m_pinCache.Get<CyI2CMode>(Formal.Param.I2CMode, Index, Type);
                    return m_i2cMode.Value;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.I2CMode, Formal.AsString(value), Index))
                    {
                        m_i2cMode = value;
                        if (m_i2cMode != CyI2CMode.I2C_NA)
                            MaxFrequency = CyMaxFrequency.MHz_NA;
                        m_pinCache.Validate();
                    }
                }
            }
            #endregion

            #region Pins-Input
            private CyInputThreshold? m_inputThreshold = null;
            public CyInputThreshold InputThreshold
            {
                get
                {
                    if (CyMaxFrequency.MHz_NA == MaxFrequency)
                        return CyInputThreshold.Default;
                    return GetSharedSIOSetting(ref m_inputThreshold, Formal.Param.ThresholdLevels,
                        CyInputThreshold.Default, GetInputThreshold,
                        CyPinType.Digital_In|CyPinType.Bidirectional);
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.ThresholdLevels, Formal.AsString(value), Index))
                    {
                        m_inputThreshold = value;
                        // The choice of threshold can impact the multiplier, so clear that as well
                        m_inputMultiplier = null;
                        UpdateSIOPaired(); // Can impact SIO-ness
                        m_pinCache.Validate();
                    }
                }
            }

            CyInputThreshold GetInputThreshold(string threshold)
            {
                #if !V0_5_PHASEDOUT
                if (threshold == "VTRIP_CMOS")
                    return CyInputThreshold.CMOS;
                if (threshold == "VTRIP_LVTTL")
                    return CyInputThreshold.LVTTL;
                if (threshold == "VTRIP_CMOS_LVTTL")
                    return CyInputThreshold.CMOS_LVTTL;
                #endif
                return Formal.GetValue<CyInputThreshold>(threshold);
            }

            private double? m_inputMultiplier = null;
            public double InputMultiplier
            {
                get
                {
                    switch (InputThreshold)
                    {
                        case CyInputThreshold.Vddio:
                            return Formal.VddioMultipliers.Vddio(m_pinCache.Get(Formal.Param.InputMultiplier, Index, Type));
                        case CyInputThreshold.Pt5_Vref:
                        case CyInputThreshold.Pt5_Vref_internal:
                        case CyInputThreshold.Vref:
                        case CyInputThreshold.Vref_internal:
                            return GetSharedSIOSetting(ref m_inputMultiplier, Formal.Param.InputMultiplier,
                                Formal.VrefMultipliers.Default,
                                s => Formal.VrefMultipliers.Vref(s),
                                CyPinType.Digital_In|CyPinType.Bidirectional);
                        default:
                            return Formal.VrefMultipliers.Default;
                    }
                }
                set
                {
                    string valStr;
                    switch (InputThreshold)
                    {
                        case CyInputThreshold.Vddio:
                            valStr = Formal.VddioMultipliers.AsString(value);
                            break;
                        case CyInputThreshold.Pt5_Vref:
                        case CyInputThreshold.Pt5_Vref_internal:
                        case CyInputThreshold.Vref:
                        case CyInputThreshold.Vref_internal:
                            valStr = Formal.VrefMultipliers.AsString(value);
                            break;
                        default:
                            // Other modes are always at 1
                            Debug.Assert(value == 1, "Multiplier " + value + " is not valid for this threshold");
                            valStr = Formal.VrefMultipliers.Index_Default.ToString();
                            break;
                    }

                    if (m_pinCache.Set(Formal.Param.InputMultiplier, valStr, Index))
                    {
                        m_inputMultiplier = value;
                        m_pinCache.Validate();
                    }

                }
            }

            private CyInputInterruptTrigger? m_inputInterrupt = null;
            public CyInputInterruptTrigger InputInterrupt
            {
                get
                {
                    if (null == m_inputInterrupt)
                        m_inputInterrupt = GetInterrupt();

                    if (Type.IsOneOf(CyPinType.Digital_In | CyPinType.Bidirectional))
                        return m_inputInterrupt.Value;

                    // Ignore leftover interrupt settings if the pin is no longer an input
                    return CyInputInterruptTrigger.None;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.InterruptMode, Formal.AsString(value), Index))
                    {
                        m_inputInterrupt = value;
                        m_pinCache.Validate();
                    }
                }
            }

            CyInputInterruptTrigger GetInterrupt()
            {
                #if !V0_5_PHASEDOUT
                string intr = m_pinCache.Get(Formal.Param.InterruptMode, Index, Type);
                if (intr == "NONE")
                    return CyInputInterruptTrigger.None;
                if (intr == "RISING_EDGE")
                    return CyInputInterruptTrigger.Rising_edge;
                if (intr == "FALLING_EDGE")
                    return CyInputInterruptTrigger.Falling_edge;
                if (intr == "BOTH_EDGES")
                    return CyInputInterruptTrigger.Both_edges;
                return Formal.GetValue<CyInputInterruptTrigger>(intr);
                #else
                return m_pinCache.Get<CyInputInterruptTrigger>(Formal.Param.InterruptMode, Index, Type);
                #endif
            }

            private bool? m_generalHotSwap = null;
            public bool GeneralHotSwap
            {
                get
                {
                    CyPinType type = Type;
                    if (null == m_generalHotSwap)
                        m_generalHotSwap = (Formal.Enabled == m_pinCache.Get(Formal.Param.HotSwaps, Index, type));
                    if (!m_deviceSupport.CanHotSwap(type))
                        return false;
                    return m_generalHotSwap.Value;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.HotSwaps, Formal.AsString(value), Index))
                    {
                        m_generalHotSwap = value;
                        UpdateSIOPaired(); // Can impact SIO-ness
                        m_pinCache.Validate();
                    }
                }
            }

            private bool? m_inputBufferEnabled = null;
            public bool InputBufferEnabled
            {
                get
                {
                    if (null == m_inputBufferEnabled)
                        m_inputBufferEnabled = GetInputBufferEnabled();
                    return m_inputBufferEnabled.Value;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.InputBuffersEnabled, Formal.AsString(value), Index))
                    {
                        m_inputBufferEnabled = value;
                        m_pinCache.Validate();
                    }
                }
            }

            bool GetInputBufferEnabled()
            {
                #if !V0_5_PHASEDOUT
                string enabled = m_pinCache.Get(Formal.Param.InputBuffersEnabled, Index, Type);
                if (enabled == "ENABLED")
                    return true;
                if (enabled == "DISABLED")
                    return false;
                return Formal.Enabled == enabled;
                #else
                return Formal.Enabled == m_pinCache.Get(Formal.Param.InputBuffersEnabled, Index, Type);
                #endif
            }

            private CySyncMode? m_inputSyncMode = null;
            public CySyncMode InputSyncMode
            {
                get
                {
                    if (null == m_inputSyncMode)
                        m_inputSyncMode = GetInputSyncMode();
                    return (Type.IsOneOf(CyPinType.Digital_In | CyPinType.Bidirectional) && TypeIsDigitalInputHw)
                        ? m_inputSyncMode.Value
                        : CySyncMode.Transparent;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.InputSyncMode, Formal.AsString(value), Index))
                    {
                        m_inputSyncMode = value;
                        m_pinCache.Validate();
                    }
                }
            }

            CySyncMode GetInputSyncMode()
            {
                #if !V0_5_PHASEDOUT
                string mode = m_pinCache.Get(Formal.Param.InputSyncMode, Index, Type);
                if (mode == "DOUBLE_SYNC")
                    return CySyncMode.Double;
                if (mode == "SINGLE_SYNC")
                    return CySyncMode.Single;
                if (mode == "NO_SYNC")
                    return CySyncMode.Transparent;
                return Formal.GetValue<CySyncMode>(mode);
                #else
                return m_pinCache.Get<CySyncMode>(Formal.Param.InputSyncMode, Index, Type);
                #endif
            }
            #endregion

            #region Pins-Output
            private CyOutputSlewRate? m_outputSlewRate = null;
            public CyOutputSlewRate OutputSlewRate
            {
                get
                {
                    if (CyMaxFrequency.MHz_NA == MaxFrequency)
                        return CyI2CMode.I2C_SM == I2CMode ? CyOutputSlewRate.Fast : CyOutputSlewRate.Slow;
                    if (null == m_outputSlewRate)
                        m_outputSlewRate = GetOutputSlewRate();
                    return m_outputSlewRate.Value;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.SlewRate, Formal.AsString(value), Index))
                    {
                        m_outputSlewRate = value;
                        m_pinCache.Validate();
                    }
                }
            }

            CyOutputSlewRate GetOutputSlewRate()
            {
                string rate = m_pinCache.Get(Formal.Param.SlewRate, Index, Type);
                #if !V0_5_PHASEDOUT
                if (rate == "FAST")
                    return CyOutputSlewRate.Fast;
                if (rate == "SLOW")
                    return CyOutputSlewRate.Slow;
                return Formal.GetValue<CyOutputSlewRate>(rate);
                #else
                return m_pinCache.Get<CyOutputSlewRate>(Formal.Param.SlewRate, Index, Type);
                #endif
            }

            private CyOutputDriveLevel? m_outputDriveLevel = null;
            public CyOutputDriveLevel OutputDriveLevel
            {
                get
                {
                    return GetSharedSIOSetting(ref m_outputDriveLevel, Formal.Param.OutputDriveLevels,
                        CyOutputDriveLevel.Vddio, Formal.GetValue<CyOutputDriveLevel>,
                        CyPinType.Digital_Out|CyPinType.Bidirectional);
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.OutputDriveLevels, Formal.AsString(value), Index))
                    {
                        m_outputDriveLevel = value;
                        m_outputMultiplier = null; // Drive level impacts the valid multipliers
                        UpdateSIOPaired(); // Can impact SIO-ness
                        m_pinCache.Validate();
                    }
                }
            }

            private double? m_outputMultiplier = null;
            public double OutputMultiplier 
            {
                get
                {
                    if (OutputDriveLevel == CyOutputDriveLevel.Vddio)
                        return Formal.VddioMultipliers.Default; // VDDIO output only supports 1x

                    return GetSharedSIOSetting(ref m_outputMultiplier, Formal.Param.OutputMultiplier,
                                               Formal.VrefMultipliers.Default,
                                               s => Formal.VrefMultipliers.Vref(s),
                                               CyPinType.Digital_Out|CyPinType.Bidirectional);
                }
                set
                {
                    Debug.Assert(OutputDriveLevel != CyOutputDriveLevel.Vddio);
                    if (m_pinCache.Set(Formal.Param.OutputMultiplier, Formal.VrefMultipliers.AsString(value), Index))
                    {
                        m_outputMultiplier = value;
                        m_pinCache.Validate();
                    }
                }
            }

            /// <summary>
            /// Gets the value for a setting which is shared between paired SIOs, but which is only valid for a 
            /// particular pin type
            /// </summary>
            /// <typeparam name="T">Type of the setting to be retrieved</typeparam>
            /// <param name="paramName">Formal parameter for the setting</param>
            /// <param name="convertValue">Delegate to convert a string into the desired value</param>
            /// <param name="cacheVar">Member variable which caches the value for this setting</param>
            /// <param name="applicableTypes">Pin types to which the setting applies</param>
            /// <returns>The value for the desired type</returns>
            private T GetSharedSIOSetting<T>(ref T? cacheVar, string paramName, T defaultVal,
                                             Func<string, T> convertValue, CyPinType applicableTypes) where T : struct
            {
                if (null == cacheVar)
                    cacheVar = convertValue(m_pinCache.Get(paramName, Index, Type));

                // Return 1) our value if type matches; 2) our pair's value if paired and matched, else the default
                // (SIO pairs must have the same value for this, so we don't need to look at the other pin.)
                if (Type.IsOneOf(applicableTypes))
                    return cacheVar.Value;

                if (IsPairedSio) // SIO and paired - check the other half
                {
                    int ixOther = GetOtherSIOIndex(this);
                    CyPinType otherType = Formal.GetPinType(m_pinCache.Get(Formal.Param.PinTypes, ixOther,
                                                         CyPinType.Digital_Out /* not used when getting type */));
                    if (otherType.IsOneOf(applicableTypes))
                        return convertValue(m_pinCache.Get(paramName, ixOther, otherType));
                }

                return defaultVal;
            }

            private CyOutputCurrentCap? m_outputCurrentCap = null;
            public CyOutputCurrentCap OutputCurrentCap
            {
                get
                {
                    CyPinType type = Type;
                    if (null == m_outputCurrentCap)
                    {
                        m_outputCurrentCap = m_pinCache.Get<CyOutputCurrentCap>(Formal.Param.OutputCurrentCaps, Index, type);
                    }
                    return type.IsOneOf(CyPinType.Bidirectional | CyPinType.Digital_Out)
                        ? m_outputCurrentCap.Value
                        : CyOutputCurrentCap.Default;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.OutputCurrentCaps, Formal.AsString(value), Index))
                    {
                        m_outputCurrentCap = value;
                        UpdateSIOPaired(); // Can impact SIO-ness
                        m_pinCache.Validate();
                    }
                }
            }

            private CyDriveStrength? m_driveStrength = null;
            public CyDriveStrength DriveStrength
            {
                get
                {
                    CyPinType type = Type;
                    if (null == m_driveStrength)
                        m_driveStrength = m_pinCache.Get<CyDriveStrength>(Formal.Param.DriveStrength, Index, type);
                    return m_driveStrength.Value;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.DriveStrength, Formal.AsString(value), Index))
                    {
                        m_driveStrength = value;
                        m_pinCache.Validate();
                    }
                }
            }

            private CySyncMode? m_outputSyncMode = null;
            public CySyncMode OutputSyncMode
            {
                get
                {
                    CyPinType type = Type;
                    if (null == m_outputSyncMode)
                        m_outputSyncMode = Formal.GetOutputSyncMode(m_pinCache.Get(Formal.Param.OutputSyncMode, Index, type));
                    return type.IsOneOf(CyPinType.Digital_Out | CyPinType.Bidirectional)
                        ? m_outputSyncMode.Value
                        : CySyncMode.Transparent;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.OutputSyncMode, Formal.AsString(value), Index))
                    {
                        m_outputSyncMode = value;
                        m_pinCache.Validate();
                    }
                }
            }

            private bool? m_outputEnableSynchronized = null;
            public bool OutputEnableSynchronized
            {
                get
                {
                    if (null == m_outputEnableSynchronized)
                        m_outputEnableSynchronized = (Formal.Enabled == m_pinCache.Get(Formal.Param.OESyncs, Index, Type));
                    return m_outputEnableSynchronized.Value;
                }
                set
                {
                    if (m_pinCache.Set(Formal.Param.OESyncs, Formal.AsString(value), Index))
                    {
                        m_outputEnableSynchronized = value;
                        m_pinCache.Validate();
                    }
                }
            }

            #endregion

            #region Error checking functions

            public bool RequiresSIO { get { return GetSIOCauses().Any(); } }

            /// <summary>
            /// Determine whether this pin requires SIO and for which reasons.
            /// </summary>
            /// <returns>A non-empty list of PinRequirementError if this pin requires SIO, an empty list otherwise.</returns>
            internal IEnumerable<PinRequirementError> GetSIOCauses()
            {
                /* 
                 * A pin is SIO if any one of the following is true:
                 * 1. HotSwaps(index) is used and we don't have OVT
                 * 2. ThresholdLevels(index) is not CMOS or LVTTL (or both):
                 * 3. OutputDriveLevels(index) is Vref
                 */

                if (m_deviceSupport.RequiresSio(GeneralHotSwap))
                    yield return new PinRequirementError("SIO", Formal.ErrorKey.INPUT_HOT_SWAP);
                if (RequiresSio(InputThreshold))
                    yield return new PinRequirementError("SIO", Formal.ErrorKey.INPUT_THRESHOLD);
                if (RequiresSio(OutputDriveLevel))
                    yield return new PinRequirementError("SIO", Formal.ErrorKey.OUTPUT_DRIVE_LEVEL);
            }

            internal static bool RequiresSio(CyInputThreshold threshold)
            {
                return threshold != CyInputThreshold.CMOS &&
                       threshold != CyInputThreshold.LVTTL &&
                       threshold != CyInputThreshold.CMOS_LVTTL;
            }

            internal static bool RequiresSio(CyOutputDriveLevel driveLevel)
            {
                return driveLevel == CyOutputDriveLevel.Vref || driveLevel == CyOutputDriveLevel.Vref_Internal;
            }

            #if !SIO_SUPPORT_ADDED
            [ExcludeFromCodeCoverage]
            #endif
            public static int GetOtherSIOIndex(PerPin pin)
            {
                Debug.Assert(pin.IsPairedSio, "SIO Not Paired");
                int otherIdx = pin.SioPair_1of2 ? pin.Index + 1 : pin.Index - 1;
                return otherIdx;
            }

            #if !SIO_SUPPORT_ADDED
            [ExcludeFromCodeCoverage]
            #endif
            public void UpdateSIOPaired()
            {
                // If we changed a setting which impacts "sio-ness" in such a way that we are no longer an SIO,
                // we need to also make sure that we are no longer listed as part of an SIO pair.
                // To avoid regrouping, we also need to update the other pin in our pair as well.
                if (IsPairedSio && !RequiresSIO)
                {
                    int otherIdx = GetOtherSIOIndex(this); // Can't compute after we mark unpaired in the next line
                    m_pinCache.Set(Formal.Param.SIOGroups, Formal.Not_grouped, Index);
                    m_pinCache.Set(Formal.Param.SIOGroups, Formal.Not_grouped, otherIdx);
                    // SIOPairID is not cached, so it is sufficient to update the parameters
                }
            }

            public bool HasSameConnectionsAs(PerPin otherPin)
            {
                if (otherPin.Type == Type &&
                    otherPin.TypeIsDigitalInputHw == TypeIsDigitalInputHw &&
                    otherPin.TypeIsDigitalOutputHw == TypeIsDigitalOutputHw &&
                    otherPin.TypeShowExternalTerm == TypeShowExternalTerm &&
                    otherPin.RequiresSIO == RequiresSIO)
                    return true;
                return false;
            }

            /// <summary>
            /// Determine whether this pin requires OVT and for which reasons.
            /// </summary>
            /// <returns>A non-empty list of PinRequirementError if this pin requires OVT, an empty list otherwise.</returns>
            internal IEnumerable<PinRequirementError> GetOVTCauses()
            {
                string required = m_deviceSupport.Require(GeneralHotSwap);
                if (required != null)
                    yield return new PinRequirementError(required, Formal.ErrorKey.INPUT_HOT_SWAP);
            }

            internal IEnumerable<PinRequirementError> OutputCurrentCauses()
            {
                string required = m_deviceSupport.Require(OutputCurrentCap);
                if (null != required)
                    yield return new PinRequirementError(required, Formal.ErrorKey.OUTPUT_CURR_CAP);
            }

            internal IEnumerable<PinRequirementError> FrequencyCauses()
            {
                string required = (CyMaxFrequency.MHz_NA != MaxFrequency)
                    ? m_deviceSupport.Require(MaxFrequency)
                    : m_deviceSupport.Require(I2CMode);
                if (null != required)
                    yield return new PinRequirementError(required, Formal.ErrorKey.GENERAL_MAX_FREQUENCY);
            }

            internal IEnumerable<PinRequirementError> SupplyVoltageCauses()
            {
                double minimumSupply = 0.0;
                if (!string.IsNullOrEmpty(GeneralMinimumSupply) &&
                    double.TryParse(GeneralMinimumSupply, out minimumSupply))
                {
                    string required = m_deviceSupport.Require(minimumSupply);
                    if (null != required)
                        yield return new PinRequirementError(required, Formal.ErrorKey.GENERAL_MINIMUM_SUPPLY);
                }
            }

            #endregion Functions
        }

        internal class PinRequirementError
        {
            internal readonly string Requirement;
            /// <summary>
            /// Error mgr key for the setting (used to map to controls for ErrorProvider display)
            /// </summary>
            internal readonly Formal.ErrorKey Key;

            internal PinRequirementError(string pinType, Formal.ErrorKey key)
            {
                Requirement = pinType;
                Key = key;
            }
        }
    }
}
