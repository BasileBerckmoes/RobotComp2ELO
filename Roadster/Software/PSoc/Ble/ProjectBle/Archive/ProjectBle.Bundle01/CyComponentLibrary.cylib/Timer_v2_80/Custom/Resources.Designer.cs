﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace Timer_v2_80 {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("Timer_v2_80.Resources", typeof(Resources).Assembly);
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
        ///   Looks up a localized string similar to Configure.
        /// </summary>
        internal static string ConfigureTabDisplayName {
            get {
                return ResourceManager.GetString("ConfigureTabDisplayName", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to In the Fixed Function implementation the Capture Mode should be set to None or Rising Edge..
        /// </summary>
        internal static string ErrorMsgCaptureMode {
            get {
                return ResourceManager.GetString("ErrorMsgCaptureMode", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Period = UNKNOWN SOURCE FREQ.
        /// </summary>
        internal static string ErrorMsgClockFreqUnknown {
            get {
                return ResourceManager.GetString("ErrorMsgClockFreqUnknown", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Capture Counter can be enabled when Capture Mode is not None..
        /// </summary>
        internal static string ErrorMsgEnableCaptureCounter {
            get {
                return ResourceManager.GetString("ErrorMsgEnableCaptureCounter", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to In the Fixed Function implementation the Capture Counter should be disabled..
        /// </summary>
        internal static string ErrorMsgEnableCaptureCounterFF {
            get {
                return ResourceManager.GetString("ErrorMsgEnableCaptureCounterFF", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to In the Fixed Function implementation the Enable Mode should be set to Software Only or Software and Hardware..
        /// </summary>
        internal static string ErrorMsgEnableMode {
            get {
                return ResourceManager.GetString("ErrorMsgEnableMode", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Component does not support the Fixed Function implementation for PSoC 4 devices..
        /// </summary>
        internal static string ErrorMsgImplementation {
            get {
                return ResourceManager.GetString("ErrorMsgImplementation", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to In the Fixed Function implementation the Interrupt on FIFO Full should be disabled..
        /// </summary>
        internal static string ErrorMsgIntFifoFull {
            get {
                return ResourceManager.GetString("ErrorMsgIntFifoFull", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Interrupt on Capture can be enabled when Capture Mode is not None..
        /// </summary>
        internal static string ErrorMsgIntOnCapture {
            get {
                return ResourceManager.GetString("ErrorMsgIntOnCapture", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to In the Fixed Function implementation the Interrupt on Capture should be disabled..
        /// </summary>
        internal static string ErrorMsgIntOnCaptureFF {
            get {
                return ResourceManager.GetString("ErrorMsgIntOnCaptureFF", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Period of {0}-bit Timer must be between 2 and {1}.
        /// </summary>
        internal static string ErrorMsgPeriod {
            get {
                return ResourceManager.GetString("ErrorMsgPeriod", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to In the Fixed Function implementation the supported Resolutions are 8-bit and 16-bit..
        /// </summary>
        internal static string ErrorMsgResolution {
            get {
                return ResourceManager.GetString("ErrorMsgResolution", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to In the Fixed Function implementation the Trigger Mode should be set to None..
        /// </summary>
        internal static string ErrorMsgTriggerMode {
            get {
                return ResourceManager.GetString("ErrorMsgTriggerMode", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Component does not support the Fixed Function implementation for PSoC 4 devices. Please open the Configure dialog and change the implementation to UDB..
        /// </summary>
        internal static string ImplementationDrcError {
            get {
                return ResourceManager.GetString("ImplementationDrcError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to On Capture.
        /// </summary>
        internal static string LblTitleIntOnCaptureFF {
            get {
                return ResourceManager.GetString("LblTitleIntOnCaptureFF", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to On Capture [1-4].
        /// </summary>
        internal static string LblTitleIntOnCaptureUdb {
            get {
                return ResourceManager.GetString("LblTitleIntOnCaptureUdb", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value range is from {0} to {1}{2}..
        /// </summary>
        internal static string MsgValueRange {
            get {
                return ResourceManager.GetString("MsgValueRange", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Period = {0}{1}.
        /// </summary>
        internal static string PeriodFormattedValue {
            get {
                return ResourceManager.GetString("PeriodFormattedValue", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to One Shot (Halt on Interrupt) is not supported for Fixed Function Timer implementations. The UDB implementation can be used for this functionality..
        /// </summary>
        internal static string RunModeDrcError {
            get {
                return ResourceManager.GetString("RunModeDrcError", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Icon similar to (Icon).
        /// </summary>
        internal static System.Drawing.Icon Symbol_Warning_2 {
            get {
                object obj = ResourceManager.GetObject("Symbol_Warning_2", resourceCulture);
                return ((System.Drawing.Icon)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Please make sure that the &apos;enable&apos; pin is not tied to logic high while enabling the Timer..
        /// </summary>
        internal static string WarnMsgRunMode {
            get {
                return ResourceManager.GetString("WarnMsgRunMode", resourceCulture);
            }
        }
    }
}