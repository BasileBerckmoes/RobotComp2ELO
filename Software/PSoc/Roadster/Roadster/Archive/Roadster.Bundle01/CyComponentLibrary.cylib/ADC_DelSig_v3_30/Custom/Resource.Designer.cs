﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace ADC_DelSig_v3_30 {
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
    internal class Resource {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Resource() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("ADC_DelSig_v3_30.Resource", typeof(Resource).Assembly);
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
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        internal static string BuiltInTabDisplayName {
            get {
                return ResourceManager.GetString("BuiltInTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap BypassBuffer {
            get {
                object obj = ResourceManager.GetObject("BypassBuffer", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Common.
        /// </summary>
        internal static string CommonTabDisplayName {
            get {
                return ResourceManager.GetString("CommonTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Illegal name - malformed or already in use..
        /// </summary>
        internal static string ConfigNameErrorDescription {
            get {
                return ResourceManager.GetString("ConfigNameErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Config.
        /// </summary>
        internal static string ConfigTabBaseDisplayName {
            get {
                return ResourceManager.GetString("ConfigTabBaseDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Failed to get VDDA value.
        /// </summary>
        internal static string DebugMsgVddaFail {
            get {
                return ResourceManager.GetString("DebugMsgVddaFail", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to +/-{0}V ( {1} ).
        /// </summary>
        internal static string DifferentialInputRangeDescriptionFormat {
            get {
                return ResourceManager.GetString("DifferentialInputRangeDescriptionFormat", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to &quot;Vssa to Vdda&quot; and &quot;Vssa to 2*Vref&quot; input ranges require that the input buffer gain be equal to 1. If a gain other than 1 is selected, the ADC will not operate properly..
        /// </summary>
        internal static string DRCErrorBufferGain {
            get {
                return ResourceManager.GetString("DRCErrorBufferGain", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Clock frequency is out of range for selected conversion mode and resolution. Valid range is {0} - {1} kHz..
        /// </summary>
        internal static string DRCErrorExternalClockRange {
            get {
                return ResourceManager.GetString("DRCErrorExternalClockRange", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Unable to set the desired clock frequency with the given MASTER_CLK frequency. Change MASTER_CLK frequency in the DWR file. .
        /// </summary>
        internal static string DRCErrorMasterClockFrequency {
            get {
                return ResourceManager.GetString("DRCErrorMasterClockFrequency", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Unable to set the desired charge pump clock frequency (4 * ADC_DelSig clock) with the given MASTER_CLK frequency. Change MASTER_CLK frequency in the DWR file. .
        /// </summary>
        internal static string DRCErrorMasterClockFrequencyCp {
            get {
                return ResourceManager.GetString("DRCErrorMasterClockFrequencyCp", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Vref value is outside the expected range of 0.9V to 1.3V. 
        ///For Internal Vdda/3 or Internal Vdda/4 and related Bypass reference options, Vref value is derived from Vdda value set in the DWR file. 
        ///Set proper Vdda value to use Vdda/3 or Vdda/4 or related Bypass reference options..
        /// </summary>
        internal static string DRCErrorReferenceVrefValue {
            get {
                return ResourceManager.GetString("DRCErrorReferenceVrefValue", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to ADC Conversion rate is out of the expected range. Set proper conversion rate in the Configure dialog..
        /// </summary>
        internal static string DRCErrorSampleRateRange {
            get {
                return ResourceManager.GetString("DRCErrorSampleRateRange", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Vref value is outside the expected range of 0.9V to 1.3V. 
        ///For Vssa to Vdda input range, the Vref value is derived from Vdda value set in the DWR file. 
        ///Set proper Vdda value to use Vssa to Vdda input range..
        /// </summary>
        internal static string DRCErrorVssaVddaVrefValue {
            get {
                return ResourceManager.GetString("DRCErrorVssaVddaVrefValue", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Vref value is outside the expected range of 0.9V to 1.3V..
        /// </summary>
        internal static string ErrorVrefRange {
            get {
                return ResourceManager.GetString("ErrorVrefRange", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Input options - {0} mode.
        /// </summary>
        internal static string InputOptionsGroupboxTitleFormat {
            get {
                return ResourceManager.GetString("InputOptionsGroupboxTitleFormat", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap LevelShift {
            get {
                object obj = ResourceManager.GetObject("LevelShift", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Number of configurations has invalid format..
        /// </summary>
        internal static string NumConfigFormatErrorDescription {
            get {
                return ResourceManager.GetString("NumConfigFormatErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Number of configurations must be between {0} and {1}..
        /// </summary>
        internal static string NumConfigValueErrorDescription {
            get {
                return ResourceManager.GetString("NumConfigValueErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap RailToRail {
            get {
                object obj = ResourceManager.GetObject("RailToRail", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The sample rate is out of range for the conversion mode, resolution, and frequency.
        /// </summary>
        internal static string SampleRateOutOfRange {
            get {
                return ResourceManager.GetString("SampleRateOutOfRange", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Range: {0} - {1} SPS.
        /// </summary>
        internal static string SampleRateRangeLabelText {
            get {
                return ResourceManager.GetString("SampleRateRangeLabelText", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Vssa to {0}V ( {1} ).
        /// </summary>
        internal static string SingleEndedInputRangeDescriptionFormat {
            get {
                return ResourceManager.GetString("SingleEndedInputRangeDescriptionFormat", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap Symbol_Information {
            get {
                object obj = ResourceManager.GetObject("Symbol Information", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Reference voltage value must be between {0} and {1}..
        /// </summary>
        internal static string VrefValueErrorDescription {
            get {
                return ResourceManager.GetString("VrefValueErrorDescription", resourceCulture);
            }
        }
    }
}
