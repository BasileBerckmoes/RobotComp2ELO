﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace I2S_PDL_v2_0 {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("I2S_PDL_v2_0.Resources", typeof(Resources).Assembly);
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
        ///   Looks up a localized string similar to Basic.
        /// </summary>
        internal static string BasicTabDisplayName {
            get {
                return ResourceManager.GetString("BasicTabDisplayName", resourceCulture);
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
        ///   Looks up a localized string similar to In the TDM mode the channel length is fixed to 32 bits..
        /// </summary>
        internal static string ErrorMsgChannelLength {
            get {
                return ResourceManager.GetString("ErrorMsgChannelLength", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to In the I2S and Left justified modes the number of channels must be 2..
        /// </summary>
        internal static string ErrorMsgChannels {
            get {
                return ResourceManager.GetString("ErrorMsgChannels", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to In the I2S and Left justified modes the WS pulse length must equal 1 channel length..
        /// </summary>
        internal static string ErrorMsgPulseWidth {
            get {
                return ResourceManager.GetString("ErrorMsgPulseWidth", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The maximum RX FIFO Trigger Level value is {0} when the number of RX channels is {1}. .
        /// </summary>
        internal static string ErrorMsgRxFifoTriggerLevel {
            get {
                return ResourceManager.GetString("ErrorMsgRxFifoTriggerLevel", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Word length value must be less than or equal Channel length..
        /// </summary>
        internal static string ErrorMsgWordLength {
            get {
                return ResourceManager.GetString("ErrorMsgWordLength", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to RX SDI latching time should be Normal in Slave mode.
        /// </summary>
        internal static string ErrorRxSdiLatchingTime {
            get {
                return ResourceManager.GetString("ErrorRxSdiLatchingTime", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to TX SDO latching time should be Normal in Master mode.
        /// </summary>
        internal static string ErrorTxSdoLatchingTime {
            get {
                return ResourceManager.GetString("ErrorTxSdoLatchingTime", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value range is from {0} to {1} {2}..
        /// </summary>
        internal static string MsgValueRange {
            get {
                return ResourceManager.GetString("MsgValueRange", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Unknown.
        /// </summary>
        internal static string UnknownClock {
            get {
                return ResourceManager.GetString("UnknownClock", resourceCulture);
            }
        }
    }
}