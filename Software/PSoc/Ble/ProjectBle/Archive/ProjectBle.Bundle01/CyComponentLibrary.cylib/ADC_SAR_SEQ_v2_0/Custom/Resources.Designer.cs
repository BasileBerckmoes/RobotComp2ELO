﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.34209
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace ADC_SAR_SEQ_v2_0 {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("ADC_SAR_SEQ_v2_0.Resources", typeof(Resources).Assembly);
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
        ///   Looks up a localized string similar to The maximum sampling rate allowed with this option
        ///is 100 ksps, except of “0.0 ± Vdda” input range. Use the Internal Vref,
        ///bypassed option for higher rates..
        /// </summary>
        internal static string ChannelSampleRateLimitError {
            get {
                return ResourceManager.GetString("ChannelSampleRateLimitError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The maximum sampling rate allowed with this option
        ///is 500 ksps for “0.0 ± Vdda” input range. Use the Internal Vref,
        ///bypassed option for higher rates..
        /// </summary>
        internal static string ChannelSampleRateVddaLimitError {
            get {
                return ResourceManager.GetString("ChannelSampleRateVddaLimitError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The clock frequency value must be between {0} MHz and {1} MHz..
        /// </summary>
        internal static string ClockFrequencyValueErrorDescription {
            get {
                return ResourceManager.GetString("ClockFrequencyValueErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Configuration.
        /// </summary>
        internal static string ConfigTabDisplayName {
            get {
                return ResourceManager.GetString("ConfigTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to External clock frequency value must be between {0} MHz and {1} MHz..
        /// </summary>
        internal static string DRCExternalClockFreq {
            get {
                return ResourceManager.GetString("DRCExternalClockFreq", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Internal clock frequency value must be between {0} MHz and {1} MHz..
        /// </summary>
        internal static string DRCInternalClockFreq {
            get {
                return ResourceManager.GetString("DRCInternalClockFreq", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Divider of  ADC SAR clock must be 2 or greater when the source clock frequency is between 15 MHz and 40 MHz..
        /// </summary>
        internal static string DRCSourceClockFreq {
            get {
                return ResourceManager.GetString("DRCSourceClockFreq", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The number of channels must be between {0} and {1} in {2} mode..
        /// </summary>
        internal static string NumChannelsValueErrorDescription {
            get {
                return ResourceManager.GetString("NumChannelsValueErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Channel sample rate (SPS): {0}.
        /// </summary>
        internal static string SampleRatePerChannelLabelFormat {
            get {
                return ResourceManager.GetString("SampleRatePerChannelLabelFormat", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The sample rate value must be unsigned integer number..
        /// </summary>
        internal static string SampleRateValueErrorDescription {
            get {
                return ResourceManager.GetString("SampleRateValueErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The reference voltage value must be between {0} V and VDDA/2 ({1} V)..
        /// </summary>
        internal static string VrefValueValueVddaDiv2ErrorDescription {
            get {
                return ResourceManager.GetString("VrefValueValueVddaDiv2ErrorDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The reference voltage value must be between {0} V and VDDA ({1} V)..
        /// </summary>
        internal static string VrefValueValueVddaErrorDescription {
            get {
                return ResourceManager.GetString("VrefValueValueVddaErrorDescription", resourceCulture);
            }
        }
    }
}
