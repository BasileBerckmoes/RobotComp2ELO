﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace Scan_ADC_v2_0.View {
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
    public class cyguierrors {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal cyguierrors() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        public static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("Scan_ADC_v2_0.View.cyguierrors", typeof(cyguierrors).Assembly);
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
        public static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to ADC clock {0} out of range {1}.
        /// </summary>
        public static string AdcClockOutOfRange {
            get {
                return ResourceManager.GetString("AdcClockOutOfRange", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Warning: Averaged channels always use 12-bit resolution, not alternate resolution..
        /// </summary>
        public static string AltResolutionAverage {
            get {
                return ResourceManager.GetString("AltResolutionAverage", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Interleaved averaging is a summation and may overflow if more 
        ///than 16 samples are averaged..
        /// </summary>
        public static string AverageOverflowNotice {
            get {
                return ResourceManager.GetString("AverageOverflowNotice", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Press Apply to switch the design to the external ADCclock or connect the aclk terminal to a clock source..
        /// </summary>
        public static string ExternalClockNotice {
            get {
                return ResourceManager.GetString("ExternalClockNotice", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Icon similar to (Icon).
        /// </summary>
        public static System.Drawing.Icon InformationIconIco {
            get {
                object obj = ResourceManager.GetObject("InformationIconIco", resourceCulture);
                return ((System.Drawing.Icon)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Press Apply to switch the design to the internal ADCclock..
        /// </summary>
        public static string InternalClockNotice {
            get {
                return ResourceManager.GetString("InternalClockNotice", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Low limit must be smaller than High limit, if the compare mode uses both..
        /// </summary>
        public static string LimitNotice {
            get {
                return ResourceManager.GetString("LimitNotice", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Noise and offsets can cause unsigned results to underflow 
        ///(wrap-round to +ve full scale) when Vneg is set to Vssa or External..
        /// </summary>
        public static string VnegResultNotice {
            get {
                return ResourceManager.GetString("VnegResultNotice", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Off-chip Vref bypass does not have any effect when Vref is set to Vdda.
        ///.
        /// </summary>
        public static string VrefBypassNotice {
            get {
                return ResourceManager.GetString("VrefBypassNotice", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Vref must be less than or equal to VDDA, {0} V..
        /// </summary>
        public static string VrefTooHigh {
            get {
                return ResourceManager.GetString("VrefTooHigh", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Vref must be greater than or equal to {0} V..
        /// </summary>
        public static string VrefTooLow {
            get {
                return ResourceManager.GetString("VrefTooLow", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Icon similar to (Icon).
        /// </summary>
        public static System.Drawing.Icon WarningIco {
            get {
                object obj = ResourceManager.GetObject("WarningIco", resourceCulture);
                return ((System.Drawing.Icon)(obj));
            }
        }
    }
}
