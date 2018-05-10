/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.ComponentModel;
using System.Xml.Serialization;

namespace USBFS_v3_20
{
    #region Interface Descriptors
    public class CyMscInterfaceDescriptor : CyInterfaceDescriptor
    {
        #region Constructors
        public CyMscInterfaceDescriptor()
        {
            bInterfaceClass = (byte)CyUSBOtherTypes.CyInterfaceClassCodes.CLASS_MASS_STORAGE;
            bInterfaceSubClassWrapper = CyUSBOtherTypes.CyMassStorageSubclassCodes.SCSI_TRANSPAREN_COMMAND_SET;
            bInterfaceProtocolWrapper = CyUSBOtherTypes.CyMassStorageProtocolCodes.BBB;
        }
        #endregion Constructors

        #region Properties

        /// <summary>
        /// This property is used in property grid to display enum values list
        /// </summary>
        [Category(CyUSBOtherTypes.CATEGORY_SPECIFIC)]
        [DisplayName("bInterfaceSubClass")]
        [TypeConverter(typeof(CyEnumConverter))]
        [DefaultValue(typeof(CyUSBOtherTypes.CyMassStorageSubclassCodes), "6")]
        [XmlIgnore]
        public CyUSBOtherTypes.CyMassStorageSubclassCodes bInterfaceSubClassWrapper
        {
            get { return (CyUSBOtherTypes.CyMassStorageSubclassCodes)bInterfaceSubClass; }
            set { bInterfaceSubClass = (byte)value; }
        }

        /// <summary>
        /// This property is used in property grid to display enum values list
        /// </summary>
        [Category(CyUSBOtherTypes.CATEGORY_SPECIFIC)]
        [DisplayName("bInterfaceProtocol")]
        [TypeConverter(typeof(CyEnumConverter))]
        [DefaultValue(typeof(CyUSBOtherTypes.CyMassStorageProtocolCodes), "80")]
        [XmlIgnore]
        public CyUSBOtherTypes.CyMassStorageProtocolCodes bInterfaceProtocolWrapper
        {
            get { return (CyUSBOtherTypes.CyMassStorageProtocolCodes)this.bInterfaceProtocol; }
            set { this.bInterfaceProtocol = (byte)value; }
        }
        #endregion Properties


        public override string ToString()
        {
            return string.Format("MSC Alternate Settings {0}", bAlternateSetting);
        }
    }
    #endregion Interface Descriptors
}
