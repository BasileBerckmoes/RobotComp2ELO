﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.18444
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace UAB_VDAC_v1_10 {
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
    public class UAB_VDAC_v1_10_resource {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal UAB_VDAC_v1_10_resource() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        public static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("UAB_VDAC_v1_10.UAB_VDAC_v1_10_resource", typeof(UAB_VDAC_v1_10_resource).Assembly);
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
        ///   Looks up a localized string similar to The clock frequency should be between {0} kHz and {1} kHz..
        /// </summary>
        public static string clkWarning {
            get {
                return ResourceManager.GetString("clkWarning", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Select whether to use an internal clock, or expose a terminal and route a clock from the schematic..
        /// </summary>
        public static string clockRateEnableToolTip {
            get {
                return ResourceManager.GetString("clockRateEnableToolTip", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Select clock frequency.  Refresh rate will be half of this value..
        /// </summary>
        public static string clockRateToolTip {
            get {
                return ResourceManager.GetString("clockRateToolTip", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Choose the maximum deviation from Vagnd.  Output will be limited by the power rails..
        /// </summary>
        public static string dacRangeToolTip {
            get {
                return ResourceManager.GetString("dacRangeToolTip", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Select DAC mode.  Modes have different binary encoding..
        /// </summary>
        public static string dacSelectToolTip {
            get {
                return ResourceManager.GetString("dacSelectToolTip", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Default output voltage at DAC power up..
        /// </summary>
        public static string defaultOutVoltsToolTip {
            get {
                return ResourceManager.GetString("defaultOutVoltsToolTip", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Select the signal to use as Vref.  Selecting External exposes a terminal..
        /// </summary>
        public static string externalReferencesToolTip {
            get {
                return ResourceManager.GetString("externalReferencesToolTip", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Select whether the DAC updates immediately when it recieves a new value, or the DAC waits until it receives a digital strobe.  Selecting External exposes a terminal..
        /// </summary>
        public static string externalStrobeToolTip {
            get {
                return ResourceManager.GetString("externalStrobeToolTip", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Place an external mod bit terminal
        ///on the schematic symbol.  Option available only in Unsigned 12bit mode..
        /// </summary>
        public static string extModBitToolTip {
            get {
                return ResourceManager.GetString("extModBitToolTip", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Select whether the output is simply buffered, or the output opamp has open feedback.  Choosing Opamp exposes a terminal..
        /// </summary>
        public static string outputFeedbackToolTip {
            get {
                return ResourceManager.GetString("outputFeedbackToolTip", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Basic.
        /// </summary>
        public static string tabNameBasic {
            get {
                return ResourceManager.GetString("tabNameBasic", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built In.
        /// </summary>
        public static string tabNameBuiltIn {
            get {
                return ResourceManager.GetString("tabNameBuiltIn", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Vagnd input voltage.
        ///If using External Vagnd, must be entered manually..
        /// </summary>
        public static string VagndVoltsToolTip {
            get {
                return ResourceManager.GetString("VagndVoltsToolTip", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Vagnd should be between {0} V and {1} V..
        /// </summary>
        public static string vagndWarning {
            get {
                return ResourceManager.GetString("vagndWarning", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Vref input voltage.
        ///If using External Vref, must be entered manually..
        /// </summary>
        public static string VrefVoltsToolTip {
            get {
                return ResourceManager.GetString("VrefVoltsToolTip", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Vref should be between {0} V and {1} V..
        /// </summary>
        public static string vrefWarning {
            get {
                return ResourceManager.GetString("vrefWarning", resourceCulture);
            }
        }
    }
}
