﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace CSD_Comp_P4_v1_0.Properties {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("CSD_Comp_P4_v1_0.Properties.Resources", typeof(Resources).Assembly);
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
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap csdCompImg {
            get {
                object obj = ResourceManager.GetObject("csdCompImg", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Internal Bandgap is not available as a voltage reference source if Vdda is less than {0} V (Vbgr + {1} V). Use an external Vinref or increase Vdda..
        /// </summary>
        internal static string ERR_DRC_VBGR_FORMATSTR2 {
            get {
                return ResourceManager.GetString("ERR_DRC_VBGR_FORMATSTR2", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Internal Bandgap is not available if Vdda is less than {0} V (Vbgr + {1} V)..
        /// </summary>
        internal static string ERR_GUI_VBGR_FORMATSTR2 {
            get {
                return ResourceManager.GetString("ERR_GUI_VBGR_FORMATSTR2", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to External Vinref must be between {0} V and {1} V..
        /// </summary>
        internal static string ERR_VINREF_FORMATSTR2 {
            get {
                return ResourceManager.GetString("ERR_VINREF_FORMATSTR2", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to External Vinref must be between {0} V and {1} V (Vdda - 0.6 V)..
        /// </summary>
        internal static string ERR_VINREF_VDDA_FORMATSTR2 {
            get {
                return ResourceManager.GetString("ERR_VINREF_VDDA_FORMATSTR2", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Actual Vrange must be between {0} V ({2}) and {1} V..
        /// </summary>
        internal static string ERR_VRANGE_FORMATSTR3 {
            get {
                return ResourceManager.GetString("ERR_VRANGE_FORMATSTR3", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Actual Vrange must be between {0} V ({2}) and {1} V (Vdda - 0.6 V)..
        /// </summary>
        internal static string ERR_VRANGE_VDDA_FORMATSTR3 {
            get {
                return ResourceManager.GetString("ERR_VRANGE_VDDA_FORMATSTR3", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Adjustable Vref must be greater than or equal to 0.6 V..
        /// </summary>
        internal static string ERR_VREF_ADJ {
            get {
                return ResourceManager.GetString("ERR_VREF_ADJ", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        internal static string TAB_NAME_BUILTIN {
            get {
                return ResourceManager.GetString("TAB_NAME_BUILTIN", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to General.
        /// </summary>
        internal static string TAB_NAME_GENERAL {
            get {
                return ResourceManager.GetString("TAB_NAME_GENERAL", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Vdda = {0} V (value is set in cydwr).
        /// </summary>
        internal static string VDDA_VALUE_FORMATSTR1 {
            get {
                return ResourceManager.GetString("VDDA_VALUE_FORMATSTR1", resourceCulture);
            }
        }
    }
}
