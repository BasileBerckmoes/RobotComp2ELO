//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.18444
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace TCPWM_P4_v2_10 {
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
    public class Resources {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Resources() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        public static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("TCPWM_P4_v2_10.Resources", typeof(Resources).Assembly);
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
        ///   Looks up a localized string similar to Swaps the period (period, periodBuf) and/or compare (compare, compareBuf) registers at the next TC event..
        /// </summary>
        public static string CapturePWMTermDescription {
            get {
                return ResourceManager.GetString("CapturePWMTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Captures the current counter value..
        /// </summary>
        public static string CaptureTimerTermDescription {
            get {
                return ResourceManager.GetString("CaptureTimerTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The capture input terminal..
        /// </summary>
        public static string CaptureUnconfiguredTermDescription {
            get {
                return ResourceManager.GetString("CaptureUnconfiguredTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Comparison or capture output..
        /// </summary>
        public static string CCTermDescription {
            get {
                return ResourceManager.GetString("CCTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Clock freq: {0} {1}.
        /// </summary>
        public static string ClockDisplay {
            get {
                return ResourceManager.GetString("ClockDisplay", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Clock.
        /// </summary>
        public static string ClockTabDisplayName {
            get {
                return ResourceManager.GetString("ClockTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Clock defines operating frequency of the component..
        /// </summary>
        public static string ClockTermDescription {
            get {
                return ResourceManager.GetString("ClockTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Clock freq: UNKNOWN.
        /// </summary>
        public static string ClockUnknown {
            get {
                return ResourceManager.GetString("ClockUnknown", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Compare value could not be greater than Period value.
        /// </summary>
        public static string CompareValueError {
            get {
                return ResourceManager.GetString("CompareValueError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to One of the two counting inputs that control the count value, increment, and decrement, depending on their relationship and the mode..
        /// </summary>
        public static string CountQDTermDescription {
            get {
                return ResourceManager.GetString("CountQDTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Increments or decrements the counter value..
        /// </summary>
        public static string CountTimerPWMTermDescription {
            get {
                return ResourceManager.GetString("CountTimerPWMTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The count input terminal..
        /// </summary>
        public static string CountUnconfiguredTermDescription {
            get {
                return ResourceManager.GetString("CountUnconfiguredTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Sets the initial value for the comparison registers and selects whether one or two comparison values are used..
        /// </summary>
        public static string HintCompare {
            get {
                return ResourceManager.GetString("HintCompare", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Selects between compare and capture modes. In Compare mode the
        ///current count value is compared to the Compare Value to generate the cc
        ///output. Capture mode is used to capture the current counter value..
        /// </summary>
        public static string HintCompareCapture {
            get {
                return ResourceManager.GetString("HintCompareCapture", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Selects the counter direction.
        /// </summary>
        public static string HintCounterMode {
            get {
                return ResourceManager.GetString("HintCounterMode", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Mode determines edge sensitivity of the signal.
        /// </summary>
        public static string HintMode {
            get {
                return ResourceManager.GetString("HintMode", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Sets the initial value for the period registers and selects whether one or
        ///two period values are used.
        /// </summary>
        public static string HintPeriod {
            get {
                return ResourceManager.GetString("HintPeriod", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Divides the TCPWM clock to create the counter clock.
        /// </summary>
        public static string HintPrescaler {
            get {
                return ResourceManager.GetString("HintPrescaler", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Present check box determines whether pin is on the symbol.
        /// </summary>
        public static string HintPresent {
            get {
                return ResourceManager.GetString("HintPresent", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Selects between continuous and one shot mode.
        /// </summary>
        public static string HintRunMode {
            get {
                return ResourceManager.GetString("HintRunMode", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Sync check box determines whether the input is synchronized.
        /// </summary>
        public static string HintSync {
            get {
                return ResourceManager.GetString("HintSync", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Interconnect.
        /// </summary>
        public static string InterconnectTabDisplayName {
            get {
                return ResourceManager.GetString("InterconnectTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Interrupt as configured in the Interrupt section..
        /// </summary>
        public static string InterruptTermDescription {
            get {
                return ResourceManager.GetString("InterruptTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Inverted PWM output..
        /// </summary>
        public static string LineNTermDescription {
            get {
                return ResourceManager.GetString("LineNTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to PWM output..
        /// </summary>
        public static string LineTermDescription {
            get {
                return ResourceManager.GetString("LineTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Status of counter overflow..
        /// </summary>
        public static string OVTermDescription {
            get {
                return ResourceManager.GetString("OVTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Value must be between {0} and {1}..
        /// </summary>
        public static string RangeError {
            get {
                return ResourceManager.GetString("RangeError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Detects a reference position for the Quadrature Decoder..
        /// </summary>
        public static string ReloadQDTermDescription {
            get {
                return ResourceManager.GetString("ReloadQDTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Initializes and starts the counter..
        /// </summary>
        public static string ReloadTimerPWMTermDescription {
            get {
                return ResourceManager.GetString("ReloadTimerPWMTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The reload input terminal..
        /// </summary>
        public static string ReloadUnconfiguredTermDescription {
            get {
                return ResourceManager.GetString("ReloadUnconfiguredTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to {0}, {1}, {2} Period = {3}, {4} Compare = {5}.
        /// </summary>
        public static string SBComponentBodyTextPWM {
            get {
                return ResourceManager.GetString("SBComponentBodyTextPWM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to {0} Encoding Mode.
        /// </summary>
        public static string SBComponentBodyTextQUAD {
            get {
                return ResourceManager.GetString("SBComponentBodyTextQUAD", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to {0} Counter, {1} Mode, Period = {2}.
        /// </summary>
        public static string SBComponentBodyTextTIMERCapture {
            get {
                return ResourceManager.GetString("SBComponentBodyTextTIMERCapture", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to {0} Counter, {1} Mode, Period = {2}, {3} Compare = {4}.
        /// </summary>
        public static string SBComponentBodyTextTIMERCompare {
            get {
                return ResourceManager.GetString("SBComponentBodyTextTIMERCompare", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Firmware-Configured TCPWM.
        /// </summary>
        public static string SBComponentBodyTextUNCONFIG {
            get {
                return ResourceManager.GetString("SBComponentBodyTextUNCONFIG", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Settings have incorrect values! You must redefine them..
        /// </summary>
        public static string SettingsIncorrectValues {
            get {
                return ResourceManager.GetString("SettingsIncorrectValues", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to One of the two counting inputs that control the count value, increment, and decrement, depending on their relationship and the mode..
        /// </summary>
        public static string StartQDTermDescription {
            get {
                return ResourceManager.GetString("StartQDTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Continues counting from the current counter value..
        /// </summary>
        public static string StartTimerPWMTermDescription {
            get {
                return ResourceManager.GetString("StartTimerPWMTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The start input terminal..
        /// </summary>
        public static string StartUnconfiguredTermDescription {
            get {
                return ResourceManager.GetString("StartUnconfiguredTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The kill signal halts the counter..
        /// </summary>
        public static string StopPWMDTTermDescription {
            get {
                return ResourceManager.GetString("StopPWMDTTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The stop signal halts the counter..
        /// </summary>
        public static string StopQDPWMTermDescription {
            get {
                return ResourceManager.GetString("StopQDPWMTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The stop signal halts the counter..
        /// </summary>
        public static string StopTimerTermDescription {
            get {
                return ResourceManager.GetString("StopTimerTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The stop input terminal..
        /// </summary>
        public static string StopUnconfiguredTermDescription {
            get {
                return ResourceManager.GetString("StopUnconfiguredTermDescription", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        public static string TabBuiltIn {
            get {
                return ResourceManager.GetString("TabBuiltIn", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Configuration.
        /// </summary>
        public static string TabNameConfig {
            get {
                return ResourceManager.GetString("TabNameConfig", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to PWM.
        /// </summary>
        public static string TabNamePWM {
            get {
                return ResourceManager.GetString("TabNamePWM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Quadrature Decoder.
        /// </summary>
        public static string TabNameQuadDec {
            get {
                return ResourceManager.GetString("TabNameQuadDec", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Timer/Counter.
        /// </summary>
        public static string TabNameTC {
            get {
                return ResourceManager.GetString("TabNameTC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to TCPWM.
        /// </summary>
        public static string TabNameTCPWM {
            get {
                return ResourceManager.GetString("TabNameTCPWM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        public static System.Drawing.Bitmap timer_down_mode {
            get {
                object obj = ResourceManager.GetObject("timer_down_mode", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        public static System.Drawing.Bitmap timer_up_down_mode0 {
            get {
                object obj = ResourceManager.GetObject("timer_up_down_mode0", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        public static System.Drawing.Bitmap timer_up_down_mode1 {
            get {
                object obj = ResourceManager.GetObject("timer_up_down_mode1", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        public static System.Drawing.Bitmap timer_up_mode {
            get {
                object obj = ResourceManager.GetObject("timer_up_mode", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Status of counter underflow..
        /// </summary>
        public static string UNTermDescription {
            get {
                return ResourceManager.GetString("UNTermDescription", resourceCulture);
            }
        }
    }
}
