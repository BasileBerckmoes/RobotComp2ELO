//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.34209
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace USBFS_v3_20.Properties {
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
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("USBFS_v3_20.Properties.Resources", typeof(Resources).Assembly);
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
        ///   Looks up a localized string similar to CDC Interfaces.
        /// </summary>
        internal static string CDC_INTERFACES_HEADER_TEXT {
            get {
                return ResourceManager.GetString("CDC_INTERFACES_HEADER_TEXT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The battery charger detection functionality is not available for the selected device..
        /// </summary>
        internal static string ERR_BATT_CHARG_DETECT_DEVICE {
            get {
                return ResourceManager.GetString("ERR_BATT_CHARG_DETECT_DEVICE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The BOS Descriptor is not available for the selected device..
        /// </summary>
        internal static string ERR_BOS_DEVICE {
            get {
                return ResourceManager.GetString("ERR_BOS_DEVICE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Each configuration descriptor must contain at least one interface descriptor..
        /// </summary>
        internal static string ERR_CONFIG_DESCRIPTOR_NOT_FULL {
            get {
                return ResourceManager.GetString("ERR_CONFIG_DESCRIPTOR_NOT_FULL", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The descriptor root must contain at least one device descriptor..
        /// </summary>
        internal static string ERR_DESCRIPTOR_ROOT_EMPTY {
            get {
                return ResourceManager.GetString("ERR_DESCRIPTOR_ROOT_EMPTY", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Each device descriptor must contain at least one interface descriptor..
        /// </summary>
        internal static string ERR_DEVICE_DESCRIPTOR_NOT_FULL {
            get {
                return ResourceManager.GetString("ERR_DEVICE_DESCRIPTOR_NOT_FULL", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to For Interrupt endpoints the Interval (ms) value cannot be 0..
        /// </summary>
        internal static string ERR_EP_INTR_BINTERVAL_0 {
            get {
                return ResourceManager.GetString("ERR_EP_INTR_BINTERVAL_0", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The maximum value for MaxPacketSize for ISOC endpoints cannot be greater than 512 bytes when Endpoint Memory Management parameter is not &quot;DMA w/Automatic MM&quot;..
        /// </summary>
        internal static string ERR_EP_MAXPACKETSIZE {
            get {
                return ResourceManager.GetString("ERR_EP_MAXPACKETSIZE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Each interface descriptor must contain at least one alternate setting..
        /// </summary>
        internal static string ERR_INTERFACE_DESCRIPTOR_NOT_FULL {
            get {
                return ResourceManager.GetString("ERR_INTERFACE_DESCRIPTOR_NOT_FULL", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to All the Endpoints in one Alternate Setting must have a unique Endpoint Number..
        /// </summary>
        internal static string ERR_NOTUNIQUE_EP_NUMBER {
            get {
                return ResourceManager.GetString("ERR_NOTUNIQUE_EP_NUMBER", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Container ID value format is wrong..
        /// </summary>
        internal static string ERR_UUID_WRONG_FORMAT {
            get {
                return ResourceManager.GetString("ERR_UUID_WRONG_FORMAT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The VBUS power pad is not available for the selected device..
        /// </summary>
        internal static string ERR_VBUS_POWER_PAD_DEVICE {
            get {
                return ResourceManager.GetString("ERR_VBUS_POWER_PAD_DEVICE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap Help {
            get {
                object obj = ResourceManager.GetObject("Help", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap imadd {
            get {
                object obj = ResourceManager.GetObject("imadd", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap imcomponentadd {
            get {
                object obj = ResourceManager.GetObject("imcomponentadd", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap imconfiguration {
            get {
                object obj = ResourceManager.GetObject("imconfiguration", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap imdelete {
            get {
                object obj = ResourceManager.GetObject("imdelete", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap imimport {
            get {
                object obj = ResourceManager.GetObject("imimport", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap imsave {
            get {
                object obj = ResourceManager.GetObject("imsave", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap imscript {
            get {
                object obj = ResourceManager.GetObject("imscript", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap imscriptadd {
            get {
                object obj = ResourceManager.GetObject("imscriptadd", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to A Collection item identifies a relationship between two or more data (Input, Output, or Feature). For example, a mouse can be described as a collection of two to four data (x, y, button 1, button 2). 
        ///The Collection item opens a collection of data..
        /// </summary>
        internal static string INFO_HID_COLLECTION {
            get {
                return ResourceManager.GetString("INFO_HID_COLLECTION", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to This is a non-executable item used to provide documentation..
        /// </summary>
        internal static string INFO_HID_COMMENT {
            get {
                return ResourceManager.GetString("INFO_HID_COMMENT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Creates a custom item with a custom prefix and value..
        /// </summary>
        internal static string INFO_HID_CUSTOM {
            get {
                return ResourceManager.GetString("INFO_HID_CUSTOM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Defines the beginning or end of a set of local items..
        /// </summary>
        internal static string INFO_HID_DELIMITER {
            get {
                return ResourceManager.GetString("INFO_HID_DELIMITER", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Determines the body part used for a control. The index points to a designator in the Physical descriptor..
        /// </summary>
        internal static string INFO_HID_DESIGNATOR_INDEX {
            get {
                return ResourceManager.GetString("INFO_HID_DESIGNATOR_INDEX", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Defines the index of the ending designator associated with an array or bitmap..
        /// </summary>
        internal static string INFO_HID_DESIGNATOR_MAXIMUM {
            get {
                return ResourceManager.GetString("INFO_HID_DESIGNATOR_MAXIMUM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Defines the index of the starting designator associated with an array or bitmap..
        /// </summary>
        internal static string INFO_HID_DESIGNATOR_MINIMUM {
            get {
                return ResourceManager.GetString("INFO_HID_DESIGNATOR_MINIMUM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to A Collection item identifies a relationship between two or more data (Input, Output, or Feature.) For example, a mouse could be described as a collection of two to four data (x, y, button 1, button 2). 
        ///The End Collection item closes a collection of data..
        /// </summary>
        internal static string INFO_HID_END_COLLECTION {
            get {
                return ResourceManager.GetString("INFO_HID_END_COLLECTION", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Input, Output, and Feature items are used to create data fields within a report.
        ///Feature items describe device configuration information that can be sent to the device..
        /// </summary>
        internal static string INFO_HID_FEATURE {
            get {
                return ResourceManager.GetString("INFO_HID_FEATURE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Input, Output, and Feature items are used to create data fields within a report.
        ///The Input item describes information about the data provided by one or more physical controls. An application can use this information to interpret the data provided by the device. All data fields defined in a single item share an identical data format..
        /// </summary>
        internal static string INFO_HID_INPUT {
            get {
                return ResourceManager.GetString("INFO_HID_INPUT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The extent value in logical units. This is the maximum value that a variable or array item reports. For example, a mouse reporting x position values from 0 to 128 would have a Logical Minimum of 0 and a Logical Maximum of 128..
        /// </summary>
        internal static string INFO_HID_LOGICAL_MAXIMUM {
            get {
                return ResourceManager.GetString("INFO_HID_LOGICAL_MAXIMUM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The extent value in logical units. This is the minimum value that a variable or array item reports. For example, a mouse reporting x position values from 0 to 128 would have a Logical Minimum of 0 and a Logical Maximum of 128..
        /// </summary>
        internal static string INFO_HID_LOGICAL_MINIMUM {
            get {
                return ResourceManager.GetString("INFO_HID_LOGICAL_MINIMUM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Input, Output, and Feature items are used to create data fields within a report.
        ///The Output item is used to define an output data field in a report. This item is similar to the Input item except it describes data sent to the device - for example, LED states..
        /// </summary>
        internal static string INFO_HID_OUTPUT {
            get {
                return ResourceManager.GetString("INFO_HID_OUTPUT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to While the Logical Minimum and Logical Maximum (extents) bound the values returned by a device, Physical Minimum and Physical Maximum give a meaning to those bounds by allowing the report value to be offset and scaled. For example, a thermometer might have logical extents of 0 and 999 but physical extents of 32 and 212 degrees..
        /// </summary>
        internal static string INFO_HID_PHYSICAL_MAXIMUM {
            get {
                return ResourceManager.GetString("INFO_HID_PHYSICAL_MAXIMUM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to While the Logical Minimum and Logical Maximum (extents) bound the values returned by a device, Physical Minimum and Physical Maximum give a meaning to those bounds by allowing the report value to be offset and scaled. For example, a thermometer might have logical extents of 0 and 999 but physical extents of 32 and 212 degrees..
        /// </summary>
        internal static string INFO_HID_PHYSICAL_MINIMUM {
            get {
                return ResourceManager.GetString("INFO_HID_PHYSICAL_MINIMUM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Replaces the item state table with the top structure from the stack..
        /// </summary>
        internal static string INFO_HID_POP {
            get {
                return ResourceManager.GetString("INFO_HID_POP", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Places a copy of the global item state table on the stack..
        /// </summary>
        internal static string INFO_HID_PUSH {
            get {
                return ResourceManager.GetString("INFO_HID_PUSH", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The number of data fields in an item can be determined by examining the Report Size and Report Count values.  The Report Count determines how many fields are included in the report for this particular item (and consequently how many bits are added to the report). For example an item with a Report Size of 8 bits and a Report Count of 3 has three 8-bit data fields..
        /// </summary>
        internal static string INFO_HID_REPORT_COUNT {
            get {
                return ResourceManager.GetString("INFO_HID_REPORT_COUNT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to This Report ID value indicates the prefix added to a particular report. For example, a Report descriptor can define a 3-byte report with a Report ID of 01. This device would generate a 4-byte data report in which the first byte is 01. The device may also generate other reports, each with a unique ID. This allows the host to distinguish different types of reports arriving over a single interrupt in pipe. And allows the device to distinguish different types of reports arriving over a single interrupt out pipe [rest of string was truncated]&quot;;.
        /// </summary>
        internal static string INFO_HID_REPORT_ID {
            get {
                return ResourceManager.GetString("INFO_HID_REPORT_ID", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The number of data fields in an item can be determined by examining the Report Size and Report Count values. The Report Size is an unsigned integer specifying the size of the report fields in bits. For example an item with a Report Size of 8 bits and a Report Count of 3 has three 8-bit data fields..
        /// </summary>
        internal static string INFO_HID_REPORT_SIZE {
            get {
                return ResourceManager.GetString("INFO_HID_REPORT_SIZE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The string index for a String descriptor. Allows a string to be associated with a particular item or control..
        /// </summary>
        internal static string INFO_HID_STRING_INDEX {
            get {
                return ResourceManager.GetString("INFO_HID_STRING_INDEX", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Specifies the last string index when assigning a group of sequential strings to controls in an array or bitmap..
        /// </summary>
        internal static string INFO_HID_STRING_MAXIMUM {
            get {
                return ResourceManager.GetString("INFO_HID_STRING_MAXIMUM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Specifies the first string index when assigning a group of sequential strings to controls in an array or bitmap..
        /// </summary>
        internal static string INFO_HID_STRING_MINIMUM {
            get {
                return ResourceManager.GetString("INFO_HID_STRING_MINIMUM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The unit values..
        /// </summary>
        internal static string INFO_HID_UNIT {
            get {
                return ResourceManager.GetString("INFO_HID_UNIT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value of the unit exponent in base 10..
        /// </summary>
        internal static string INFO_HID_UNIT_EXPONENT {
            get {
                return ResourceManager.GetString("INFO_HID_UNIT_EXPONENT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Local Usage item is the Usage ID that works together with Global Usage Page to describe the function of a control, data or collection.
        ///A report may assign one Usage to multiple items. If a report item is preceded by a single Usage, then Usage applies to all data of the items. If a report item is preceded by more than one Usage and the number of controls or data item equals the number of Usages, each Usage applies to one control or date item, with the Usages and controls/date items pairing in a sequence [rest of string was truncated]&quot;;.
        /// </summary>
        internal static string INFO_HID_USAGE {
            get {
                return ResourceManager.GetString("INFO_HID_USAGE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Defines the ending usage associated with an array or bitmap.
        ///If a Usage Minimum is declared as an extended usage, then the associated Usage Maximum must also be declared as an extended usage..
        /// </summary>
        internal static string INFO_HID_USAGE_MAXIMUM {
            get {
                return ResourceManager.GetString("INFO_HID_USAGE_MAXIMUM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Defines the starting usage associated with an array or bitmap.
        ///If a Usage Minimum is declared as an extended usage, then the associated Usage Maximum must also be declared as an extended usage..
        /// </summary>
        internal static string INFO_HID_USAGE_MINIMUM {
            get {
                return ResourceManager.GetString("INFO_HID_USAGE_MINIMUM", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to HID usages are organized into usage pages of related controls. A specific control usage is defined by its usage page and a usage ID. Examples of usage pages include Generic Desktop Controls, Game Controls, LEDs, Button, and so on. Examples of controls that are listed on the Generic Desktop Controls usage page include pointers, mouse and keyboard devices, joysticks, and so on..
        /// </summary>
        internal static string INFO_HID_USAGE_PAGE {
            get {
                return ResourceManager.GetString("INFO_HID_USAGE_PAGE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to MSC Interfaces.
        /// </summary>
        internal static string MSC_INTERFACES_HEADER_TEXT {
            get {
                return ResourceManager.GetString("MSC_INTERFACES_HEADER_TEXT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Current configuration cannot support a bootloader. The following configurations should be used: (1) Endpoint Number: EP1, Direction: OUT, Transfer Type: INT, Max Packet Size: 64; (2) Endpoint Number: EP2, Direction: IN, Transfer Type: INT, Max Packet Size: 64..
        /// </summary>
        internal static string MSG_BOOTLOADER_SUPPORT {
            get {
                return ResourceManager.GetString("MSG_BOOTLOADER_SUPPORT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The possible values for MaxPacketSize for Bulk endpoints are 8, 16, 32, and 64. This limitation comes from USB 2.0 specification..
        /// </summary>
        internal static string MSG_BULK_MAXPACKETSIZE {
            get {
                return ResourceManager.GetString("MSG_BULK_MAXPACKETSIZE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Selected endpoint memory management option &quot;{0}&quot; is not supported for current device..
        /// </summary>
        internal static string MSG_DRC_DMA_ERROR {
            get {
                return ResourceManager.GetString("MSG_DRC_DMA_ERROR", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The total sum of the MaxPacketSize for all endpoints in one interface cannot be greater than 1100 bytes..
        /// </summary>
        internal static string MSG_DRC_EP_SUM_AUTO {
            get {
                return ResourceManager.GetString("MSG_DRC_EP_SUM_AUTO", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The total sum of the MaxPacketSize for all endpoints in one interface cannot be greater than 512 bytes when Endpoint Memory Management parameter is not &quot;DMA with Automatic Buffer Management&quot;..
        /// </summary>
        internal static string MSG_DRC_EP_SUM_MANUAL {
            get {
                return ResourceManager.GetString("MSG_DRC_EP_SUM_MANUAL", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The total sum of the MaxPacketSize for all endpoints in one configuration cannot be greater than 512 bytes when Endpoint Buffer Management has static allocation..
        /// </summary>
        internal static string MSG_DRC_EP_SUM_STATT_ALLOC {
            get {
                return ResourceManager.GetString("MSG_DRC_EP_SUM_STATT_ALLOC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Descriptors are incompatible..
        /// </summary>
        internal static string MSG_ERR_DESC_INCOMPATIBLE {
            get {
                return ResourceManager.GetString("MSG_ERR_DESC_INCOMPATIBLE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Incorrect format of the Input Value..
        /// </summary>
        internal static string MSG_INCORRECT_VALUE {
            get {
                return ResourceManager.GetString("MSG_INCORRECT_VALUE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Input Value should be in range [0x{0:X}..0x{1:X}]..
        /// </summary>
        internal static string MSG_INCORRECT_VALUE_RANGE {
            get {
                return ResourceManager.GetString("MSG_INCORRECT_VALUE_RANGE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value {0} is too small for vendor-defined value. It will be automatically updated to 0xFF00..
        /// </summary>
        internal static string MSG_INCORRECT_VENDOR_VALUE {
            get {
                return ResourceManager.GetString("MSG_INCORRECT_VENDOR_VALUE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Interface class will be changed to Undefined. Do you want to continue?.
        /// </summary>
        internal static string MSG_INTERFACE_CHANGE {
            get {
                return ResourceManager.GetString("MSG_INTERFACE_CHANGE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The value range for {0} is [{1}, {2}].
        /// </summary>
        internal static string MSG_RANGE_ERROR {
            get {
                return ResourceManager.GetString("MSG_RANGE_ERROR", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to REPORT_ID value should be in range [1 to 255]..
        /// </summary>
        internal static string MSG_REPORTID_RANGE {
            get {
                return ResourceManager.GetString("MSG_REPORTID_RANGE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to END_COLLECTION could not be added at the beginning of the report..
        /// </summary>
        internal static string MSG_RPT_WARNING_1 {
            get {
                return ResourceManager.GetString("MSG_RPT_WARNING_1", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Error.
        /// </summary>
        internal static string MSG_TITLE_ERROR {
            get {
                return ResourceManager.GetString("MSG_TITLE_ERROR", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Information.
        /// </summary>
        internal static string MSG_TITLE_INFORMATION {
            get {
                return ResourceManager.GetString("MSG_TITLE_INFORMATION", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Question.
        /// </summary>
        internal static string MSG_TITLE_QUESTION {
            get {
                return ResourceManager.GetString("MSG_TITLE_QUESTION", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Warning.
        /// </summary>
        internal static string MSG_TITLE_WARNING {
            get {
                return ResourceManager.GetString("MSG_TITLE_WARNING", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Unable to load the Template..
        /// </summary>
        internal static string MSG_UNABLE_LOAD_TEMPLATE {
            get {
                return ResourceManager.GetString("MSG_UNABLE_LOAD_TEMPLATE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Unable to save the Template to the file..
        /// </summary>
        internal static string MSG_UNABLE_SAVE_TEMPLATE {
            get {
                return ResourceManager.GetString("MSG_UNABLE_SAVE_TEMPLATE", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Undefined HID Report for the HID Class Descriptor.
        ///To fix this problem you can: 
        ///(1) Configure the HID Class Descriptor to refer to a HID Report, or
        ///(2) Remove the HID Class Descriptor from the Configuration..
        /// </summary>
        internal static string MSG_UNDEFINED_HIDREPORT {
            get {
                return ResourceManager.GetString("MSG_UNDEFINED_HIDREPORT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Parameter {0} has incorrect value. The default value will be used..
        /// </summary>
        internal static string MSG_WRONG_PARAMETER {
            get {
                return ResourceManager.GetString("MSG_WRONG_PARAMETER", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Warning!.
        /// </summary>
        internal static string MSGBOX_TITLE_WRG {
            get {
                return ResourceManager.GetString("MSGBOX_TITLE_WRG", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Advanced.
        /// </summary>
        internal static string PAGE_TITLE_ADV {
            get {
                return ResourceManager.GetString("PAGE_TITLE_ADV", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Audio Descriptor.
        /// </summary>
        internal static string PAGE_TITLE_AUDIODESC {
            get {
                return ResourceManager.GetString("PAGE_TITLE_AUDIODESC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Built-in.
        /// </summary>
        internal static string PAGE_TITLE_BUILTIN {
            get {
                return ResourceManager.GetString("PAGE_TITLE_BUILTIN", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to CDC Descriptor.
        /// </summary>
        internal static string PAGE_TITLE_CDCDESC {
            get {
                return ResourceManager.GetString("PAGE_TITLE_CDCDESC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Device Descriptor.
        /// </summary>
        internal static string PAGE_TITLE_DEVDESC {
            get {
                return ResourceManager.GetString("PAGE_TITLE_DEVDESC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to HID Descriptor.
        /// </summary>
        internal static string PAGE_TITLE_HIDDESC {
            get {
                return ResourceManager.GetString("PAGE_TITLE_HIDDESC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Interrupts.
        /// </summary>
        internal static string PAGE_TITLE_INERRUPTS {
            get {
                return ResourceManager.GetString("PAGE_TITLE_INERRUPTS", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to MIDI Descriptor.
        /// </summary>
        internal static string PAGE_TITLE_MIDIDESC {
            get {
                return ResourceManager.GetString("PAGE_TITLE_MIDIDESC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to MSC Descriptor.
        /// </summary>
        internal static string PAGE_TITLE_MSCDESC {
            get {
                return ResourceManager.GetString("PAGE_TITLE_MSCDESC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to String Descriptor.
        /// </summary>
        internal static string PAGE_TITLE_STRDESC {
            get {
                return ResourceManager.GetString("PAGE_TITLE_STRDESC", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap warning {
            get {
                object obj = ResourceManager.GetObject("warning", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The VBUS Monitoring is not enabled on the Advanced Tab..
        /// </summary>
        internal static string WRG_DEVICE_SELF_POVERED_MONIT {
            get {
                return ResourceManager.GetString("WRG_DEVICE_SELF_POVERED_MONIT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to If the Device Class value is set to 0, the Device Subclass value should also be set to 0..
        /// </summary>
        internal static string WRG_DEVICE_SUBCLASS {
            get {
                return ResourceManager.GetString("WRG_DEVICE_SUBCLASS", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Battery charger detection functionality requires VBUS signal detection, but VBUS Monitoring is not enabled..
        /// </summary>
        internal static string WRG_DRC_BATT_CHARG_DETECT_CONFIG {
            get {
                return ResourceManager.GetString("WRG_DRC_BATT_CHARG_DETECT_CONFIG", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to The Max Packet Size value should not be 0..
        /// </summary>
        internal static string WRG_EP_MAX_PACKET_SIZE_0 {
            get {
                return ResourceManager.GetString("WRG_EP_MAX_PACKET_SIZE_0", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Device is bus powered, but the maximum current that will be drawn from the host is set to 0 mA..
        /// </summary>
        internal static string WRG_MAX_POWER {
            get {
                return ResourceManager.GetString("WRG_MAX_POWER", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to If multiple devices with the same VID, PID, and Serial Number string are connected to a single host some devices may not be recognized..
        /// </summary>
        internal static string WRG_USER_ENTERED_TEXT {
            get {
                return ResourceManager.GetString("WRG_USER_ENTERED_TEXT", resourceCulture);
            }
        }
    }
}