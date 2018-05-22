//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace ADC_SAR_SEQ_P4_v2_50 {
    using System;
    
    
    /// <summary>
    ///   A strongly-typed resource class, for looking up localized strings, etc.
    /// </summary>
    // This class was auto-generated by the StronglyTypedResourceBuilder
    // class via a tool like ResGen or Visual Studio.
    // To add or remove a member, edit your .ResX file then rerun ResGen
    // with the /str option, or rebuild your VS project.
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")]
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    internal class Resources {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Resources() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("ADC_SAR_SEQ_P4_v2_50.Resources", typeof(Resources).Assembly);
                    resourceMan = temp;
                }
                return resourceMan;
            }
        }
        
        /// <summary>
        ///   Overrides the current thread's CurrentUICulture property for all
        ///   resource lookups using this strongly typed resource class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Clock value must be between {0} and {1}..
        /// </summary>
        internal static string AcqTimeErrorDescription {
            get {
                return ResourceManager.GetString("AcqTimeErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Actual clock frequency value must be between {0} MHz and {1} MHz..
        /// </summary>
        internal static string ActualClockFrequencyValueErrorDescription {
            get {
                return ResourceManager.GetString("ActualClockFrequencyValueErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Resolution should be equal to {0} when channel is averaged..
        /// </summary>
        internal static string AveragedChannelResolutionErrorDescription {
            get {
                return ResourceManager.GetString("AveragedChannelResolutionErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Averaging is not supported for left Data format justification..
        /// </summary>
        internal static string AvgLeftJustificationError {
            get {
                return ResourceManager.GetString("AvgLeftJustificationError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        internal static string BuiltInTabDisplayName {
            get {
                return ResourceManager.GetString("BuiltInTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Channels.
        /// </summary>
        internal static string ChannelsTabDisplayName {
            get {
                return ResourceManager.GetString("ChannelsTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Clock frequency value must be between {0} MHz and {1} MHz..
        /// </summary>
        internal static string ClockFrequencyErrorMsg {
            get {
                return ResourceManager.GetString("ClockFrequencyErrorMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Clock frequency value must be less than {0} MHz, half of High Frequency Clock (HFCLK) taken from the Design-Wide Resources (DWR) Clock Editor..
        /// </summary>
        internal static string ClockFrequencyHFCLKErrorMsg {
            get {
                return ResourceManager.GetString("ClockFrequencyHFCLKErrorMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Analog ADC clock input..
        /// </summary>
        internal static string ClockTermDescription {
            get {
                return ResourceManager.GetString("ClockTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Failed to get a Bandgap Voltage value..
        /// </summary>
        internal static string DebugMsgBandgapFail {
            get {
                return ResourceManager.GetString("DebugMsgBandgapFail", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Failed to get VDDA value..
        /// </summary>
        internal static string DebugMsgVddaFail {
            get {
                return ResourceManager.GetString("DebugMsgVddaFail", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to At least one input channel must be enabled..
        /// </summary>
        internal static string DRCAllChannelsDisabledError {
            get {
                return ResourceManager.GetString("DRCAllChannelsDisabledError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The actual sample rate ({0} SPS) differs from the desired sample rate ({1} SPS) due to the clock configuration in the DWR..
        /// </summary>
        internal static string DRCSampleRateInfo {
            get {
                return ResourceManager.GetString("DRCSampleRateInfo", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to VDDA/2; VDDA; Internal {0} volts; Internal {0} volts, bypassed; Internal Vref; Internal Vref, bypassed; VDDA/2, bypassed; External Vref.
        /// </summary>
        internal static string EnumVrefSelect {
            get {
                return ResourceManager.GetString("EnumVrefSelect", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to End of Conversion output..
        /// </summary>
        internal static string EOCTermDescription {
            get {
                return ResourceManager.GetString("EOCTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to General.
        /// </summary>
        internal static string GeneralTabDisplayName {
            get {
                return ResourceManager.GetString("GeneralTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Input buffer gain is not supported for current device type..
        /// </summary>
        internal static string InputBufferGainIncorrectValue {
            get {
                return ResourceManager.GetString("InputBufferGainIncorrectValue", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Interconnect.
        /// </summary>
        internal static string InterconnectTabDisplayName {
            get {
                return ResourceManager.GetString("InterconnectTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Interrupt limit must be between {0} and {1}..
        /// </summary>
        internal static string InterruptValueError {
            get {
                return ResourceManager.GetString("InterruptValueError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Clock frequency for &quot;{0}&quot; reference must be less than {1} kHz. Please use &quot;{2}, bypassed&quot; for higher clock frequency..
        /// </summary>
        internal static string InvalidReferenceErrorMsg {
            get {
                return ResourceManager.GetString("InvalidReferenceErrorMsg", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Left Data format justification is not compatible with averaging..
        /// </summary>
        internal static string LeftJustificationAvgError {
            get {
                return ResourceManager.GetString("LeftJustificationAvgError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Minus Input for the Injection Channel..
        /// </summary>
        internal static string MinusINJTermDescription {
            get {
                return ResourceManager.GetString("MinusINJTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Minus Input .
        /// </summary>
        internal static string MinusInputTermDescription {
            get {
                return ResourceManager.GetString("MinusInputTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Current channels configuration cannot be supported by the device. Decrease number of the sequenced channels or change differential mode to single ended for the channels..
        /// </summary>
        internal static string NumSeqChannelsErrorDescription {
            get {
                return ResourceManager.GetString("NumSeqChannelsErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Number of sequenced channels must be between {0} and {1}..
        /// </summary>
        internal static string NumSeqChannelsFormatErrorDescription {
            get {
                return ResourceManager.GetString("NumSeqChannelsFormatErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Plus Input for the Injection Channel..
        /// </summary>
        internal static string PlusINJTermDescription {
            get {
                return ResourceManager.GetString("PlusINJTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Plus Input .
        /// </summary>
        internal static string PlusInputTermDescription {
            get {
                return ResourceManager.GetString("PlusInputTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Calculating.
        /// </summary>
        internal static string SBCalcSPSLable {
            get {
                return ResourceManager.GetString("SBCalcSPSLable", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to {0}-Channel, {1}Channel sample rate (SPS): {2}.
        /// </summary>
        internal static string SBComponentBodyText {
            get {
                return ResourceManager.GetString("SBComponentBodyText", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to ADC SAR Seq.
        /// </summary>
        internal static string SBComponentTitle {
            get {
                return ResourceManager.GetString("SBComponentTitle", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Sample Done output..
        /// </summary>
        internal static string SDONETermDescription {
            get {
                return ResourceManager.GetString("SDONETermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Settings have incorrect values. You must redefine them..
        /// </summary>
        internal static string SettingsIncorrectValues {
            get {
                return ResourceManager.GetString("SettingsIncorrectValues", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Start of Conversion input.
        /// </summary>
        internal static string SOCTermDescription {
            get {
                return ResourceManager.GetString("SOCTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Common negative input reference..
        /// </summary>
        internal static string VINNEGTermDescription {
            get {
                return ResourceManager.GetString("VINNEGTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The selected type of voltage reference is not supported for the current device type..
        /// </summary>
        internal static string VrefSelectIncorrectValue {
            get {
                return ResourceManager.GetString("VrefSelectIncorrectValue", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Voltage Reference input.
        /// </summary>
        internal static string VREFTermDescription {
            get {
                return ResourceManager.GetString("VREFTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Vref value must be between {0} and {1}..
        /// </summary>
        internal static string VrefValueErrorDescription {
            get {
                return ResourceManager.GetString("VrefValueErrorDescription", resourceCulture);
            }
        }
    }
}
