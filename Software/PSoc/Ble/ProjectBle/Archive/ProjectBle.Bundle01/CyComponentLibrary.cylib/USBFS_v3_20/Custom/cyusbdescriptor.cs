/*******************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Xml.Serialization;

namespace USBFS_v3_20
{
    [Serializable()]
    [XmlInclude(typeof(CyDeviceDescriptor))]
    [XmlInclude(typeof(CyConfigDescriptor))]
    [XmlInclude(typeof(CyBosDescriptor))]
    [XmlInclude(typeof(CyUsb20ExtensionDeviceCapabilityDescriptor))]
    [XmlInclude(typeof(CyContainerIdDescriptor))]
    [XmlInclude(typeof(CyEndpointDescriptor))]
    [XmlInclude(typeof(CyInterfaceDescriptor))]
    [XmlInclude(typeof(CyInterfaceGeneralDescriptor))]
    [XmlInclude(typeof(CyInterfaceAssociationDescriptor))]
    [XmlInclude(typeof(CyStringDescriptor))]
    [XmlInclude(typeof(CyStringZeroDescriptor))]
    [XmlInclude(typeof(CyHIDDescriptor))]
    [XmlInclude(typeof(CyHIDReportDescriptor))]
    [XmlInclude(typeof(CyHIDReportItemDescriptor))]

    [XmlInclude(typeof(CyAudioInterfaceDescriptor))]
    [XmlInclude(typeof(CyACInputTerminalDescriptor))]
    [XmlInclude(typeof(CyACOutputTerminalDescriptor))]
    [XmlInclude(typeof(CyACHeaderDescriptor))]
    [XmlInclude(typeof(CyACMixerUnitDescriptor))]
    [XmlInclude(typeof(CyACSelectorUnitDescriptor))]
    [XmlInclude(typeof(CyACFeatureUnitDescriptor))]
    [XmlInclude(typeof(CyACProcessingUnitDescriptor))]
    [XmlInclude(typeof(CyACExtensionDescriptor))]
    [XmlInclude(typeof(CyASGeneralDescriptor))]
    [XmlInclude(typeof(CyASFormatTypeBaseDescriptor))]
    [XmlInclude(typeof(CyASFormatType1Descriptor))]
    [XmlInclude(typeof(CyASFormatType2Descriptor))]
    [XmlInclude(typeof(CyAudioEndpointDescriptor))]
    [XmlInclude(typeof(CyASEndpointDescriptor))]

    [XmlInclude(typeof(CyACHeaderDescriptor_v2))]
    [XmlInclude(typeof(CyACInputTerminalDescriptor_v2))]
    [XmlInclude(typeof(CyACOutputTerminalDescriptor_v2))]
    [XmlInclude(typeof(CyACClockSourceDescriptor_v2))]
    [XmlInclude(typeof(CyACClockSelectorDescriptor_v2))]
    [XmlInclude(typeof(CyACClockMultiplierDescriptor_v2))]
    [XmlInclude(typeof(CyACMixerUnitDescriptor_v2))]
    [XmlInclude(typeof(CyACSelectorUnitDescriptor_v2))]
    [XmlInclude(typeof(CyACFeatureUnitDescriptor_v2))]
    [XmlInclude(typeof(CyACProcessingUnitDescriptor_v2))]
    [XmlInclude(typeof(CyACExtensionDescriptor_v2))]
    [XmlInclude(typeof(CyACEffectUnitDescriptor_v2))]
    [XmlInclude(typeof(CyACSamplingRateConverterDescriptor_v2))]
    [XmlInclude(typeof(CyASGeneralDescriptor_v2))]

    [XmlInclude(typeof(CyMSHeaderDescriptor))]
    [XmlInclude(typeof(CyMSInJackDescriptor))]
    [XmlInclude(typeof(CyMSOutJackDescriptor))]
    [XmlInclude(typeof(CyMSElementDescriptor))]
    [XmlInclude(typeof(CyMSEndpointDescriptor))]

    [XmlInclude(typeof(CyCDCInterfaceDescriptor))]
    [XmlInclude(typeof(CyCommunicationsInterfaceDescriptor))]
    [XmlInclude(typeof(CyDataInterfaceDescriptor))]
    [XmlInclude(typeof(CyCDCClassDescriptor))]
    [XmlInclude(typeof(CyCDCHeaderDescriptor))]
    [XmlInclude(typeof(CyCDCUnionDescriptor))]
    [XmlInclude(typeof(CyCDCCountrySelectionDescriptor))]
    [XmlInclude(typeof(CyCDCCallManagementDescriptor))]
    [XmlInclude(typeof(CyCDCAbstractControlMgmtDescriptor))]

    [XmlInclude(typeof(CyMscInterfaceDescriptor))]

    [XmlType("USBDescriptor")]
    public abstract class CyUSBDescriptor : ICloneable, ICustomTypeDescriptor
    {
        public const int NONE_LEVEL = 0;
        public const int DEVICE_LEVEL = 1;
        public const int CONFIG_LEVEL = 2;
        public const int INTERFACE_LEVEL = 3;
        public const int BOS_LEVEL = 2;
        public const int USB20_EXTENSION_DEVICE_CAPABILITY_LEVEL = 3;
        public const int CONTAINER_ID_LEVEL = 3;
        public const int ENDPOINT_LEVEL = 4;
        public const int CS_ENDPOINT_LEVEL = 5;
        public const int HID_CLASS_LEVEL = 4;
        public const int AUDIO_LEVEL = 4;
        public const int CDC_LEVEL = 4;
        public const int STRING_LEVEL = 10;

        private CyUSBDescriptorType m_bDescriptorType;
        private byte m_bLength;

        [ReadOnly(true)]
        [Category(CyUSBOtherTypes.CATEGORY_COMMON)]
        public CyUSBDescriptorType bDescriptorType
        {
            get
            {
                return m_bDescriptorType;
            }
            set
            {
                m_bDescriptorType = value;
            }
        }

        [Browsable(false)]
        public byte bLength
        {
            get
            {
                return m_bLength;
            }
            set
            {
                m_bLength = value;
            }
        }

        public abstract int GetLevel();
        public virtual void UpdateLength()
        {
        }

        #region ICloneable Members

        public object Clone()
        {
            return this.MemberwiseClone();
        }

        #endregion

        #region ICustomTypeDescriptor members
        public AttributeCollection GetAttributes()
        {
            return TypeDescriptor.GetAttributes(this, true);
        }

        public string GetClassName()
        {
            return TypeDescriptor.GetClassName(this, true);
        }

        public string GetComponentName()
        {
            return TypeDescriptor.GetComponentName(this, true);
        }

        public TypeConverter GetConverter()
        {
            return TypeDescriptor.GetConverter(this, true);
        }

        public EventDescriptor GetDefaultEvent()
        {
            return TypeDescriptor.GetDefaultEvent(this, true);
        }

        public PropertyDescriptor GetDefaultProperty()
        {
            return TypeDescriptor.GetDefaultProperty(this, true);
        }

        public object GetEditor(Type editorBaseType)
        {
            return TypeDescriptor.GetEditor(this, editorBaseType, true);
        }

        public EventDescriptorCollection GetEvents()
        {
            return TypeDescriptor.GetEvents(this, true);
        }

        public EventDescriptorCollection GetEvents(Attribute[] attributes)
        {
            return TypeDescriptor.GetEvents(this, attributes, true);
        }

        public virtual PropertyDescriptorCollection GetProperties()
        {
            return TypeDescriptor.GetProperties(this, true);
        }

        public virtual PropertyDescriptorCollection GetProperties(Attribute[] attributes)
        {
            return TypeDescriptor.GetProperties(this, attributes, true);
        }

        public object GetPropertyOwner(PropertyDescriptor pd)
        {
            return this;
        }
        #endregion ICustomTypeDescriptor members
    }
}
