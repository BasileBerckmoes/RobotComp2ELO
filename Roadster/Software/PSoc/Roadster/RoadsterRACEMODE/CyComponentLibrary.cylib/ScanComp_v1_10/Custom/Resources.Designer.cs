//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.18052
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace ScanComp_v1_10 {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("ScanComp_v1_10.Resources", typeof(Resources).Assembly);
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
        ///   Looks up a localized string similar to Channels.
        /// </summary>
        internal static string ChanelsTabDisplayName {
            get {
                return ResourceManager.GetString("ChanelsTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Channels table contains invalid data..
        /// </summary>
        internal static string ChannelsDataGridContainsError {
            get {
                return ResourceManager.GetString("ChannelsDataGridContainsError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Clock frequency value must be between {0} KHz and {1} MHz..
        /// </summary>
        internal static string ClockFrequencyErrorMsg {
            get {
                return ResourceManager.GetString("ClockFrequencyErrorMsg", resourceCulture);
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
        ///   Looks up a localized string similar to Component does not support Internal VDAC as negative input for PSoC 4 device. Please open config dialog and change Negative Input value (by pressing &quot;Apply&quot; button)..
        /// </summary>
        internal static string InternalVDACForPSoC4 {
            get {
                return ResourceManager.GetString("InternalVDACForPSoC4", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Clock frequency for &quot;{0}&quot; reference must be less than {1} kHz. Please use &quot;{0}, bypassed&quot; for higher clock frequency..
        /// </summary>
        internal static string InvalidReferenceErrorMsg {
            get {
                return ResourceManager.GetString("InvalidReferenceErrorMsg", resourceCulture);
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
        ///   Looks up a localized string similar to Clock frequency value must be between {0} Hz and {1} MHz..
        /// </summary>
        internal static string ScanRateErrorMsg {
            get {
                return ResourceManager.GetString("ScanRateErrorMsg", resourceCulture);
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
        ///   Looks up a localized string similar to Value must be between {0} and {1}..
        /// </summary>
        internal static string ValueOutOfRange {
            get {
                return ResourceManager.GetString("ValueOutOfRange", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to VDAC voltage is not a multiple to {0}. The value will be rounded..
        /// </summary>
        internal static string VdacVoltageNotMultiple {
            get {
                return ResourceManager.GetString("VdacVoltageNotMultiple", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Channels table contains VDAC voltage that is not a multiple to {0}. The value will be rounded..
        /// </summary>
        internal static string VDACVoltageTableNotMultiple {
            get {
                return ResourceManager.GetString("VDACVoltageTableNotMultiple", resourceCulture);
            }
        }
    }
}