﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.18444
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace Scan_ADC_v1_20.Controller {
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
    public class cydrcerrors {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal cydrcerrors() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        public static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("Scan_ADC_v1_20.Controller.cydrcerrors", typeof(cydrcerrors).Assembly);
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
        ///   Looks up a localized string similar to Configuration {0} ADC clock {1} out of range {2}.
        /// </summary>
        public static string AdcClockOutOfRange {
            get {
                return ResourceManager.GetString("AdcClockOutOfRange", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to At least one input channel must be enabled in each configuration..
        /// </summary>
        public static string AllChannelsDisabled {
            get {
                return ResourceManager.GetString("AllChannelsDisabled", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Averaged channels always use 12-bit resolution, not alternate resolution..
        /// </summary>
        public static string AltResolutionAverageNotice {
            get {
                return ResourceManager.GetString("AltResolutionAverageNotice", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Average mode is interleaved, and more than 16 samples averaged..
        /// </summary>
        public static string AverageOverflowNotice {
            get {
                return ResourceManager.GetString("AverageOverflowNotice", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Low limit must be smaller than High limit when both limits are used by the compare mode..
        /// </summary>
        public static string LimitNotice {
            get {
                return ResourceManager.GetString("LimitNotice", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Scans rescheduled during build..
        /// </summary>
        public static string ScheduleChanged {
            get {
                return ResourceManager.GetString("ScheduleChanged", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to  Conversions cannot be guaranteed to be correctly respresented in an unsigned variable when Vneg is VSSA or EXTERNAL..
        /// </summary>
        public static string VnegResultNotice {
            get {
                return ResourceManager.GetString("VnegResultNotice", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Off-chip Vref bypass does not have any effect when Vref is set to VDDA..
        /// </summary>
        public static string VrefBypassNotice {
            get {
                return ResourceManager.GetString("VrefBypassNotice", resourceCulture);
            }
        }
    }
}