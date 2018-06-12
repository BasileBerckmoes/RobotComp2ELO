/*******************************************************************************
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Collections.Generic;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;

using CyDesigner.Extensions.Gde;

namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    public class CyDeviceSupport
    {
        public const string OVT = "OVT";
        public const string SIO = "SIO";
        public const string HSIO = "HSIO";
        public const string GPIO = "GPIO";
        public const string GPIO_5V = "GPIO_5V";
        public const string GPIO_5V_SMC = "GPIO_5V_SMC";

        public readonly bool HasSIO;
        public readonly bool HasPortAdapter;
        public readonly bool HasSyncModes;
        public readonly bool HasOutLevelVref;
        public readonly bool HasInternalVref;
        public readonly int MaxPinCount;

        private readonly bool HasData;
        private readonly bool HasGPIO;
        private readonly bool HasGPIO5V;
        private readonly bool HasGPIO5VSMC;
        private readonly bool HasOVT;
        private readonly bool HasHSIO;

        // Compare the query to prevent the use of a different device validator than was used to create the data object
        public readonly ICyDeviceQuery_v1 Query;

        public CyDeviceSupport(ICyDeviceQuery_v1 deviceQuery)
        {
            HasData = deviceQuery.DeviceFamilyAvailable;
            HasGPIO = !HasData || DeviceFeature.GetHasGPIO(deviceQuery);
            HasGPIO5V = !HasData || DeviceFeature.GetHasGPIO5V(deviceQuery);
            HasGPIO5VSMC = !HasData || DeviceFeature.GetHasGPIO5VSMC(deviceQuery);
            HasOVT = !HasData || DeviceFeature.GetHasOVT(deviceQuery);
            HasSIO = !HasData || DeviceFeature.GetHasSIO(deviceQuery);
            HasHSIO = !HasData || DeviceFeature.GetHasHSIO(deviceQuery);
            HasPortAdapter = DeviceFeature.GetHasPortAdapter(deviceQuery);
            MaxPinCount = DeviceFeature.GetMaxPinCount(deviceQuery);

            HasSyncModes = !HasData || HasPortAdapter;
            HasOutLevelVref = HasSIO;
            HasInternalVref = HasSIO;
        }

        public IEnumerable<CyOutputCurrentCap> AvailableCurrentCaps
        {
            get
            {
                if (null == Require(CyOutputCurrentCap.Source_5ma_Sink_5ma))
                    yield return CyOutputCurrentCap.Source_5ma_Sink_5ma;
                if (null == Require(CyOutputCurrentCap.Source_8ma_Sink_8ma))
                    yield return CyOutputCurrentCap.Source_8ma_Sink_8ma;
                if (null == Require(CyOutputCurrentCap.Source_16ma_Sink_16ma))
                    yield return CyOutputCurrentCap.Source_16ma_Sink_16ma;
                if (null == Require(CyOutputCurrentCap.Source_40ma_Sink_40ma))
                    yield return CyOutputCurrentCap.Source_40ma_Sink_40ma;
            }
        }

        public IEnumerable<CyMaxFrequency> AvailableFrequencies
        {
            get
            {
                if (null == Require(CyMaxFrequency.MHz_200))
                    yield return CyMaxFrequency.MHz_200;
                if (null == Require(CyMaxFrequency.MHz_100))
                    yield return CyMaxFrequency.MHz_100;
                if (null == Require(CyMaxFrequency.MHz_80))
                    yield return CyMaxFrequency.MHz_80;
                if (null == Require(CyMaxFrequency.MHz_50))
                    yield return CyMaxFrequency.MHz_50;
                if (null == Require(CyMaxFrequency.MHz_1))
                    yield return CyMaxFrequency.MHz_1;
            }
        }

        public IEnumerable<CyI2CMode> AvailableI2CModes
        {
            get
            {
                yield return CyI2CMode.I2C_SM;
                if (null == Require(CyI2CMode.I2C_FM))
                    yield return CyI2CMode.I2C_FM;
                if (null == Require(CyI2CMode.I2C_FM_plus))
                    yield return CyI2CMode.I2C_FM_plus;
                if (null == Require(CyI2CMode.I2C_HS))
                    yield return CyI2CMode.I2C_HS;
            }
        }

        /// <summary>
        /// Determine if hot swap is an option for this device.
        /// 
        /// Hot swap is enabled according to different rules depending on the device capabilities:
        /// If the device has SIO, Hot Swap is only enabled if we found digital.
        /// If the device has OVT, Hot Swap is always enabled.
        /// If we have neither OVT nor SIO, Hot Swap is never enabled,
        /// but if we found a pin with hotswap enabled already, enabled so that the user can uncheck it if necessary.
        /// </summary>
        /// <param name="anyHotswap">True if any pin already had selected hot swap.</param>
        /// <param name="anyDigital">True if any pin is digital.</param>
        /// <returns>True if hot swap is allowed.</returns>
        [ExcludeFromCodeCoverage]
        public bool CanHotSwap(bool anyHotSwap, bool anyDigital)
        {
            bool enableHotSwap = anyHotSwap;
            if (HasSIO) enableHotSwap |= anyDigital;
            enableHotSwap |= HasOVT;
            return enableHotSwap;
        }

        /// <summary>
        /// Determine if hot swap is an option for this device.
        /// 
        /// If pure analog and no OVT on the part, hotswap is false (and the checkbox is disabled)
        /// If there is a mix of analog and digital on this pin, the user will get an error if they try
        /// to use HotSwap, so we check type against analog directly.
        /// </summary>
        /// <param name="pinType">The selected pin type.</param>
        /// <returns>True if hot swap is allowed.</returns>
        public bool CanHotSwap(CyPinType pinType)
        {
            return HasOVT || pinType != CyPinType.Analog;
        }

        /// <summary>
        /// Hotswap only requires SIO if we don't have OVT. To avoid duplicate errors, if we have neither
        /// OVT nor SIO, consider HotSwap to require OVT since it is expected to be on more chips in the future,
        /// and considering it to require both will generate redundant "missing feature" errors.
        /// </summary>
        /// <param name="hotSwap">True if hot swap needed.</param>
        /// <returns><True if SIO is required./returns>
        public bool RequiresSio(bool hotSwap)
        {
            return hotSwap && !HasOVT && HasSIO;
        }

        /// <summary>
        /// Hotswap only requires OVT if we don't have SIO.
        /// </summary>
        /// <param name="hotSwap">True if hot swap needed.</param>
        /// <returns>"OVT" if Ovt is required, null otherwise.</returns>
        public string Require(bool hotSwap)
        {
            return (hotSwap && !HasOVT && !HasSIO) ? OVT : null;
        }

        public string Require(double minimumSupplyVoltage)
        {
            // Value as specified in SEROS 002_11527_A. section 7.6.6.2.5
            if (minimumSupplyVoltage > 3.3)
                return RequireFeature(GPIO_5V, GPIO_5V_SMC);

            return null;
        }

        public string Require(CyOutputCurrentCap outCurrCap)
        {
            switch (outCurrCap)
            {
                case CyOutputCurrentCap.Source_5ma_Sink_5ma:
                    return RequireFeature(GPIO, GPIO_5V, OVT, SIO, GPIO_5V_SMC, HSIO);
                case CyOutputCurrentCap.Source_8ma_Sink_8ma:
                    return RequireFeature(GPIO, OVT, SIO, HSIO, GPIO_5V_SMC);
                case CyOutputCurrentCap.Source_16ma_Sink_16ma:
                    return RequireFeature(HSIO, GPIO_5V_SMC);
                case CyOutputCurrentCap.Source_40ma_Sink_40ma:
                    return RequireFeature(GPIO_5V_SMC);
                default:
                    Debug.Fail("Invalid output current");
                    return GPIO; // Call attention to the failure
            }
        }

        public string Require(CyMaxFrequency maxFrequency)
        {
            // Get raw value in MHz
            double mHz;
            if (!double.TryParse(Formal.AsString(maxFrequency), out mHz))
            {
                Debug.Fail("Invalid frequency");
                return GPIO; // Call attention to the failure
            }

            // Values from SEROS 002_11527_A
            if (mHz > 100.0)
                return RequireFeature(HSIO);
            if (mHz > 80.0)
                return RequireFeature(HSIO, OVT, GPIO);
            if (mHz > 50.0)
                return RequireFeature(HSIO, SIO, OVT, GPIO_5V, GPIO_5V_SMC);
            if (mHz > 1.0)
                return RequireFeature(HSIO, SIO, OVT, GPIO_5V, GPIO_5V_SMC);

            return RequireFeature(OVT, GPIO, GPIO_5V, GPIO_5V_SMC);
        }

        public string Require(CyI2CMode i2cMode)
        {
            switch (i2cMode)
            {
                case CyI2CMode.I2C_SM:
                    return null; // All IO allowable

                case CyI2CMode.I2C_FM:
                    return RequireFeature(SIO, OVT, GPIO, GPIO_5V, GPIO_5V_SMC);

                case CyI2CMode.I2C_FM_plus:
                case CyI2CMode.I2C_HS:
                    return RequireFeature(GPIO_5V_SMC);

                default:
                    Debug.Fail("Invalid I2C mode");
                    return GPIO; // Call attention to the failure
            }
        }

        private string RequireFeature(params string[] features)
        {
            foreach (string feature in features)
            {
                switch (feature)
                {
                    case GPIO:
                        if (HasGPIO)
                            return null;
                        break;
                    case GPIO_5V:
                        if (HasGPIO5V)
                            return null;
                        break;
                    case OVT:
                        if (HasOVT)
                            return null;
                        break;
                    case SIO:
                        if (HasSIO)
                            return null;
                        break;
                    case HSIO:
                        if (HasHSIO)
                            return null;
                        break;
                    case GPIO_5V_SMC:
                        if (HasGPIO5VSMC)
                            return null;
                        break;
                    default:
                        Debug.Fail("Unhandled feature");
                        return "Internal error in CyDeviceSupport";
                }
            }

            return string.Join(Resource1.OR, features);
        }

        private static class DeviceFeature
        {
            private const string IO_BLOCK = "mxs40ioss";
            private const string PARAM_GPIO_PORT_CNT = "GPIO.GPIO_PORT_NR";
            private const string PARAM_HS_PORT_CNT = "HSIOM.HSIOM_PORT_NR";
            private const string PARAM_IS_GPIO_PORT = "GPIO_PRT.GPIO[{0}]";
            private const string PARAM_IS_GPIO5V_PORT = "GPIO_PRT.GPIO5V[{0}]";
            private const string PARAM_IS_GPIO5VSMC_PORT = "GPIO_PRT.GPIO5VSMC[{0}]";   //NYI - returns false
            private const string PARAM_IS_OVT_PORT = "GPIO_PRT.GPIO_OVT[{0}]";
            private const string PARAM_IS_SIO_PORT = "GPIO_PRT.SIO[{0}]";
            private const string PARAM_IS_HSIO_PORT = "GPIO_PRT.HSIO[{0}]";
            private const string UDB_BLOCK = "mxudb";

            internal static bool GetHasGPIO(ICyDeviceQuery_v1 deviceQuery)
            {
                int portCount = deviceQuery.GetFeatureParameter(IO_BLOCK, PARAM_GPIO_PORT_CNT);
                for (int i = 0; i < portCount; i++)
                    if (deviceQuery.GetFeatureParameter(IO_BLOCK, string.Format(PARAM_IS_GPIO_PORT, i)) == 1)
                        return true;

                return false;
            }

            internal static bool GetHasGPIO5V(ICyDeviceQuery_v1 deviceQuery)
            {
                int portCount = deviceQuery.GetFeatureParameter(IO_BLOCK, PARAM_GPIO_PORT_CNT);
                for (int i = 0; i < portCount; i++)
                    if (deviceQuery.GetFeatureParameter(IO_BLOCK, string.Format(PARAM_IS_GPIO5V_PORT, i)) == 1)
                        return true;

                return false;
            }

            internal static bool GetHasGPIO5VSMC(ICyDeviceQuery_v1 deviceQuery)
            {
                int portCount = deviceQuery.GetFeatureParameter(IO_BLOCK, PARAM_GPIO_PORT_CNT);
                for (int i = 0; i < portCount; i++)
                    if (deviceQuery.GetFeatureParameter(IO_BLOCK, string.Format(PARAM_IS_GPIO5VSMC_PORT, i)) == 1)
                        return true;

                return false;
            }

            internal static bool GetHasOVT(ICyDeviceQuery_v1 deviceQuery)
            {
                int portCount = deviceQuery.GetFeatureParameter(IO_BLOCK, PARAM_HS_PORT_CNT);
                for (int i = 0; i < portCount; i++)
                    if (deviceQuery.GetFeatureParameter(IO_BLOCK, string.Format(PARAM_IS_OVT_PORT, i)) == 1)
                        return true;

                return false;
            }

            internal static bool GetHasSIO(ICyDeviceQuery_v1 deviceQuery)
            {
                int portCount = deviceQuery.GetFeatureParameter(IO_BLOCK, PARAM_HS_PORT_CNT);
                for (int i = 0; i < portCount; i++)
                    if (deviceQuery.GetFeatureParameter(IO_BLOCK, string.Format(PARAM_IS_SIO_PORT, i)) == 1)
                        return true;

                return false;
            }

            internal static bool GetHasHSIO(ICyDeviceQuery_v1 deviceQuery)
            {
                int portCount = deviceQuery.GetFeatureParameter(IO_BLOCK, PARAM_HS_PORT_CNT);
                for (int i = 0; i < portCount; i++)
                    if (deviceQuery.GetFeatureParameter(IO_BLOCK, string.Format(PARAM_IS_HSIO_PORT, i)) == 1)
                        return true;

                return false;
            }

            internal static bool GetHasPortAdapter(ICyDeviceQuery_v1 deviceQuery)
            {
                return deviceQuery.GetFeatureCountDie(UDB_BLOCK) > 0;
            }

            internal static int GetMaxPinCount(ICyDeviceQuery_v1 deviceQuery)
            {
                int maxPins = deviceQuery.GetResourcePinCount(string.Empty, -1, string.Empty);
                return maxPins;
            }
        }
    }
}
