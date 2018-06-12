/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.Reflection;
using System.Xml.Serialization;

namespace DMA_PDL_v2_0.Utils
{
    public delegate void DescriptorNameEventHandler(string oldName, string newName);
    [TypeConverter(typeof(PropertySorter))]
    [Serializable()]
    public class CyDmaDescriptionProperties : CyProperties
    {
        public event DescriptorNameEventHandler DescriptorNameChange;
        public CyDmaDescriptionProperties()
        {
            TriggerOutput = CyConst.C_TRIGGER_OUTPUT_DEF;
            Interrupt = CyConst.C_INTERRUPT_DEF;
            TriggerInputType = CyConst.C_TRIGGER_INPUT_TYPE_DEF;
            TriggerDeactivationAndRetriggering = CyConst.C_TRIGGER_DEACTIVATION_AND_RETRIGGERING_DEF;
            DataElementSize = CyConst.C_DATA_ELEMENT_SIZE_DEF;
            SourceAndDestinationTransferWidth = CyConst.C_SOURCE_AND_DESTINATION_TRANSFER_WIDTH_DEF;
            NumberOfDataElementsToTransfer = CyConst.C_CATEGORY_LOOP_TRANSFER_DEF;
            SourceIncrementEveryCycleByX = CyConst.C_CATEGORY_LOOP_TRANSFER_DEF;
            DestinationIncrementEveryCycleByX = CyConst.C_CATEGORY_LOOP_TRANSFER_DEF;
            NumberOfXLoopsToExecute = CyConst.C_CATEGORY_LOOP_TRANSFER_DEF;
            SourceIncrementEveryCycleByY = CyConst.C_CATEGORY_LOOP_TRANSFER_DEF;
            DestinationIncrementEveryCycleByY = CyConst.C_CATEGORY_LOOP_TRANSFER_DEF;
            ChainToDescriptor = CyConst.C_CHAIN_TO_DESCRIPTOR_DEF;
            ChannelStateOnCompletion = CyConst.C_CHANNEL_STATE_ON_COMPLETION_DEF;
        }

        #region Descriptor properties
        [XmlIgnore]
        public static List<CyDmaDescriptionProperties> Descriptors
        {
            set { m_descriptors = value; }
        }

        private string m_descriptorName;
        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(1)]
        [XmlElement("DescriptorName")]
        [DisplayName(CyTextConst.DESCRIPTOR_NAME)]
        [Description(CyTextConst.DESCRIPTION_DESCRIPTOR_NAME)]
        [Category(CyTextConst.CATEGORY_DESCRIPTOR)]
        [CyPropertyId(CyEPropertyIdEnum.DescriptorName)]
        public string DescriptorName
        {
            get
            {
                return m_descriptorName;
            }
            set
            {
                string oldName = m_descriptorName;
                string newName = value;
                m_descriptorName = newName;
                if (!String.IsNullOrEmpty(oldName))
                {
                    DescriptorNameChange(oldName, newName);
                }

            }
        }

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(2)]
        [Description(CyTextConst.DESCRIPTION_TRIGGER_OUTPUT)]
        [DefaultValue(CyConst.C_TRIGGER_OUTPUT_DEF)]
        [Category(CyTextConst.CATEGORY_DESCRIPTOR)]
        [DisplayName(CyTextConst.TRIGGER_OUTPUT)]
        [CyPropertyId(CyEPropertyIdEnum.TriggerOutput)]
        [TypeConverter(typeof(EnumTypeConverter))]
        public CyInterruptOrTriggerOutputEnum TriggerOutput
        { get; set; }

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(3)]
        [Description(CyTextConst.DESCRIPTION_INTERRUPT)]
        [DefaultValue(CyConst.C_INTERRUPT_DEF)]
        [Category(CyTextConst.CATEGORY_DESCRIPTOR)]
        [DisplayName(CyTextConst.INTERRUPT)]
        [CyPropertyId(CyEPropertyIdEnum.Interrupt)]
        [TypeConverter(typeof(EnumTypeConverter))]
        public CyInterruptOrTriggerOutputEnum Interrupt
        { get; set; }

        private string m_chainToDescriptor;

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(4)]
        [XmlElement("ChainToDescriptor")]
        [Description(CyTextConst.DESCRIPTION_CHAIN_TO_DESCRIPTOR)]
        [DisplayName(CyTextConst.CHAIN_TO_DESCRIPTOR)]
        [DefaultValue(CyConst.C_CHAIN_TO_DESCRIPTOR_DEF)]
        [Category(CyTextConst.CATEGORY_DESCRIPTOR)]
        [CyPropertyId(CyEPropertyIdEnum.ChainToDescriptor)]
        [TypeConverter(typeof(PostTypeConverter))]
        public string ChainToDescriptor
        {
            get
            {
                return m_chainToDescriptor;
            }
            set
            {
                m_chainToDescriptor = value;
            }
        }

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(5)]
        [XmlElement("ChannelStateOnCompletion")]
        [Description(CyTextConst.DESCRIPTION_CHANNEL_STATE_ON_COMPLETION)]
        [DisplayName(CyTextConst.CHANNEL_STATE_ON_COMPLETION)]
        [DefaultValue(CyConst.C_CHANNEL_STATE_ON_COMPLETION_DEF)]
        [Category(CyTextConst.CATEGORY_DESCRIPTOR)]
        [CyPropertyId(CyEPropertyIdEnum.ChannelStateOnCompletion)]
        //[TypeConverter(typeof(PostTypeConverter))]
        public CyEnDisEnum ChannelStateOnCompletion
        { get; set; }

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(1)]
        [XmlElement("TriggerInputType")]
        [Description(CyTextConst.DESCRIPTION_TRIGGER_INPUT_TYPE)]
        [DisplayName(CyTextConst.TRIGGER_INPUT_TYPE)]
        [DefaultValue(CyConst.C_TRIGGER_INPUT_TYPE_DEF)]
        [Category(CyTextConst.CATEGORY_TRIGGER_INPUT_TYPE)]
        [CyPropertyId(CyEPropertyIdEnum.TriggerInputType)]
        [TypeConverter(typeof(EnumTypeConverter))]
        public CyTriggerInputTypesEnum TriggerInputType
        { get; set; }

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(2)]
        [XmlElement("TriggerDeactivationAndRetriggering")]
        [Description(CyTextConst.DESCRIPTION_TRIGGER_DEACTIVATION_AND_RETRIGGERING)]
        [DisplayName(CyTextConst.TRIGGER_DEACTIVATION_AND_RETRIGGERING)]
        [DefaultValue(CyConst.C_TRIGGER_DEACTIVATION_AND_RETRIGGERING_DEF)]
        [Category(CyTextConst.CATEGORY_TRIGGER_INPUT_TYPE)]
        [CyPropertyId(CyEPropertyIdEnum.TriggerDeactivationAndRetriggering)]
        [TypeConverter(typeof(EnumTypeConverter))]
        public CyTriggerDeactivationAndRetriggeringEnum TriggerDeactivationAndRetriggering
        { get; set; }

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(1)]
        [XmlElement("DataElementSize")]
        [Description(CyTextConst.DESCRIPTION_DATA_ELEMENT_SIZE)]
        [DefaultValue(CyConst.C_DATA_ELEMENT_SIZE_DEF)]
        [DisplayName(CyTextConst.DATA_ELEMENT_SIZE)]
        [Category(CyTextConst.CATEGORY_TRANSFER_SETTING)]
        [CyPropertyId(CyEPropertyIdEnum.DataElementSize)]
        [TypeConverter(typeof(EnumTypeConverter))]
        public CyDataElementSizeEnum DataElementSize
        { get; set; }

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(2)]
        [DefaultValue(CyConst.C_SOURCE_AND_DESTINATION_TRANSFER_WIDTH_DEF)]
        [XmlElement("SourceAndDestinationTransferWidth")]
        [Description(CyTextConst.DESCRIPTION_SOURCE_AND_DESTINATION_TRANSFER_WIDTH)]
        [DisplayName(CyTextConst.SOURCE_AND_DESTINATION_TRANSFER_WIDTH)]
        [Category(CyTextConst.CATEGORY_TRANSFER_SETTING)]
        [CyPropertyId(CyEPropertyIdEnum.SourceAndDestinationTransferWidth)]
        [TypeConverter(typeof(EnumTypeConverter))]
        public CySourceAndDestinationTransferWidthEnum SourceAndDestinationTransferWidth
        { get; set; }

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(1)]
        [XmlElement("NumberOfDataElementsToTransfer")]
        [Description(CyTextConst.DESCRIPTION_NUMBER_OF_DATA_ELEMENTS_TO_TRANSFER)]
        [DefaultValue(CyConst.C_CATEGORY_LOOP_TRANSFER_DEF)]
        [Category(CyTextConst.CATEGORY_X_LOOP_TRANSFER)]
        [DisplayName(CyTextConst.NUMBER_OF_DATA_ELEMENTS_TO_TRANSFER)]
        [CyPropertyId(CyEPropertyIdEnum.NumberOfDataElementsToTransfer)]
        public UInt16 NumberOfDataElementsToTransfer
        { get; set; }

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(2)]
        [XmlElement("SourceIncrementEveryCycleByX")]
        [Description(CyTextConst.DESCRIPTION_SOURCE_INCREMENT_EVERY_CYCLE_BY)]
        [DefaultValue(CyConst.C_CATEGORY_LOOP_TRANSFER_DEF)]
        [Category(CyTextConst.CATEGORY_X_LOOP_TRANSFER)]
        [DisplayName(CyTextConst.SOURCE_INCREMENT_EVERY_CYCLE_BY)]
        [CyPropertyId(CyEPropertyIdEnum.SourceIncrementEveryCycleByX)]
        public int SourceIncrementEveryCycleByX
        { get; set; }

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(3)]
        [XmlElement("DestinationIncrementEveryCycleByX")]
        [Description(CyTextConst.DESCRIPTION_DESTINATION_INCREMENT_EVERY_CYCLE_BY)]
        [DefaultValue(CyConst.C_CATEGORY_LOOP_TRANSFER_DEF)]
        [Category(CyTextConst.CATEGORY_X_LOOP_TRANSFER)]
        [DisplayName(CyTextConst.DESTINATION_INCREMENT_EVERY_CYCLE_BY)]
        [CyPropertyId(CyEPropertyIdEnum.DestinationIncrementEveryCycleByX)]
        public int DestinationIncrementEveryCycleByX
        { get; set; }

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(1)]
        [XmlElement("NumberOfXLoopsToExecute")]
        [Description(CyTextConst.DESCRIPTION_NUMBER_OF_X_LOOPS_TO_EXECUTE)]
        [DefaultValue(CyConst.C_CATEGORY_LOOP_TRANSFER_DEF)]
        [Category(CyTextConst.CATEGORY_Y_LOOP_TRANSFER)]
        [DisplayName(CyTextConst.NUMBER_OF_X_LOOPS_TO_EXECUTE)]
        [CyPropertyId(CyEPropertyIdEnum.NumberOfXLoopsToExecute)]
        public UInt16 NumberOfXLoopsToExecute
        { get; set; }

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(2)]
        [XmlElement("SourceIncrementEveryCycleByY")]
        [Description(CyTextConst.DESCRIPTION_SOURCE_INCREMENT_EVERY_CYCLE_BY)]
        [DefaultValue(CyConst.C_CATEGORY_LOOP_TRANSFER_DEF)]
        [Category(CyTextConst.CATEGORY_Y_LOOP_TRANSFER)]
        [DisplayName(CyTextConst.SOURCE_INCREMENT_EVERY_CYCLE_BY)]
        [CyPropertyId(CyEPropertyIdEnum.SourceIncrementEveryCycleByY)]
        public int SourceIncrementEveryCycleByY
        { get; set; }

        [Browsable(true)]
        [ReadOnly(false)]
        [PropertyOrder(3)]
        [XmlElement("DestinationIncrementEveryCycleByY")]
        [Description(CyTextConst.DESCRIPTION_DESTINATION_INCREMENT_EVERY_CYCLE_BY)]
        [DefaultValue(CyConst.C_CATEGORY_LOOP_TRANSFER_DEF)]
        [Category(CyTextConst.CATEGORY_Y_LOOP_TRANSFER)]
        [DisplayName(CyTextConst.DESTINATION_INCREMENT_EVERY_CYCLE_BY)]
        [CyPropertyId(CyEPropertyIdEnum.DestinationIncrementEveryCycleByY)]
        public int DestinationIncrementEveryCycleByY
        { get; set; }
        #endregion

        public override string ObjectName
        {
            get
            {
                return DescriptorName;
            }
        }

        private static List<CyDmaDescriptionProperties> m_descriptors = new List<CyDmaDescriptionProperties>();
        private static List<String> m_dmaDescriptorsNameList = new List<string>();

        public void FillDescriptorsNameList()
        {
            m_dmaDescriptorsNameList.Clear();
            m_dmaDescriptorsNameList.Add(CyConst.C_CHAIN_TO_DESCRIPTOR_DEF);
            foreach (CyDmaDescriptionProperties dmaDescriptor in m_descriptors)
            {
                String descriptorName = dmaDescriptor.DescriptorName;
                m_dmaDescriptorsNameList.Add(descriptorName);
            }
        }

        public void CopyValuesTo(CyDmaDescriptionProperties destination)
        {
            foreach (PropertyDescriptor item in TypeDescriptor.GetProperties(this))
            {
                if (item.IsBrowsable)
                {
                    // Do not copy the Descriptor Name and Chain to Descriptor properties
                    if (item.Name == "DescriptorName" || item.Name == "ChainToDescriptor")
                        continue;

                    var val = item.GetValue(this);
                    if (val == null)
                    {
                        continue;
                    }
                    item.SetValue(destination, val);
                }
            }
        }

        #region Overrides
        protected override PropertyDescriptorCollection FilterProperties(PropertyDescriptorCollection properties)
        {
            // Do not perform any filtering while deserializing
            PropertyDescriptorCollection output = new PropertyDescriptorCollection(null);
            foreach (PropertyDescriptor property in properties)
            {
                string displayName = null;

                CyEPropertyIdEnum propId = CyPropertyIdAttribute.GetPropertyId(property);
                switch (propId)
                {
                    case CyEPropertyIdEnum.DescriptorName:
                    case CyEPropertyIdEnum.DataElementSize:
                    case CyEPropertyIdEnum.Interrupt:
                    case CyEPropertyIdEnum.SourceAndDestinationTransferWidth:
                    case CyEPropertyIdEnum.TriggerDeactivationAndRetriggering:
                    case CyEPropertyIdEnum.TriggerInputType:
                    case CyEPropertyIdEnum.TriggerOutput:
                    case CyEPropertyIdEnum.NumberOfDataElementsToTransfer:
                    case CyEPropertyIdEnum.ChainToDescriptor:
                    case CyEPropertyIdEnum.ChannelStateOnCompletion:
                        break;
                    case CyEPropertyIdEnum.SourceIncrementEveryCycleByX:
                        displayName = AddSourceUnit();
                        break;
                    case CyEPropertyIdEnum.DestinationIncrementEveryCycleByX:
                        displayName = AddDestinationUnit();
                        break;
                    case CyEPropertyIdEnum.NumberOfXLoopsToExecute:
                        break;
                    case CyEPropertyIdEnum.SourceIncrementEveryCycleByY:
                        displayName = AddSourceUnit();
                        break;
                    case CyEPropertyIdEnum.DestinationIncrementEveryCycleByY:
                        displayName = AddDestinationUnit();
                        break;
                    default:
                        Debug.Assert(false);
                        return null;
                }

                PropertyDescriptor pd = ApplyAttributes(property, displayName);
                output.Add(pd);
            }

            return output;
        }

        private string AddDestinationUnit()
        {
            string displayName = null;
            if ((SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.ByteToByte) ||
                                        (SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.WordToByte))
            {
                displayName += CyTextConst.DESTINATION_INCREMENT_EVERY_CYCLE_BY +
                              CyTextConst.UNIT_BYTES;
            }
            else if ((SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.HalfwordToHalfword) ||
                                        (SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.WordToHalfword))
            {
                displayName += CyTextConst.DESTINATION_INCREMENT_EVERY_CYCLE_BY +
                              CyTextConst.UNIT_HALFWORDS;
            }
            else if ((SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.ByteToWord) ||
                                        (SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.HalfwordToWord) ||
                                        (SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.WordToWord))
            {
                displayName += CyTextConst.DESTINATION_INCREMENT_EVERY_CYCLE_BY +
                              CyTextConst.UNIT_WORDS;
            }

            return displayName;
        }

        private string AddSourceUnit()
        {
            string displayName = null;
            if ((SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.ByteToByte) ||
                                        (SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.ByteToWord))
            {
                displayName = CyTextConst.SOURCE_INCREMENT_EVERY_CYCLE_BY +
                              CyTextConst.UNIT_BYTES;
            }
            else if ((SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.HalfwordToHalfword) ||
                                        (SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.HalfwordToWord))
            {
                displayName = CyTextConst.SOURCE_INCREMENT_EVERY_CYCLE_BY +
                              CyTextConst.UNIT_HALFWORDS;
            }

            else if ((SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.WordToByte) ||
                                        (SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.WordToHalfword) ||
                                        (SourceAndDestinationTransferWidth ==
                                        CySourceAndDestinationTransferWidthEnum.WordToWord))
            {
                displayName = CyTextConst.SOURCE_INCREMENT_EVERY_CYCLE_BY +
                              CyTextConst.UNIT_WORDS;
            }

            return displayName;
        }

        protected override CyRange GetPropertyRange(CyEPropertyIdEnum propId)
        {
            switch (propId)
            {
                case CyEPropertyIdEnum.DescriptorName:
                case CyEPropertyIdEnum.DataElementSize:
                case CyEPropertyIdEnum.Interrupt:
                case CyEPropertyIdEnum.SourceAndDestinationTransferWidth:
                case CyEPropertyIdEnum.TriggerDeactivationAndRetriggering:
                case CyEPropertyIdEnum.TriggerInputType:
                case CyEPropertyIdEnum.TriggerOutput:
                case CyEPropertyIdEnum.ChainToDescriptor:
                case CyEPropertyIdEnum.ChannelStateOnCompletion:
                    return null;
                case CyEPropertyIdEnum.NumberOfDataElementsToTransfer:
                    return CyConst.R_NUMBER_OF_DATA_ELEMENTS_TO_TRANSFER;
                case CyEPropertyIdEnum.SourceIncrementEveryCycleByX:
                    return CyConst.R_SOURCE_INCREMENT_EVERY_CYCLE_BY_X;
                case CyEPropertyIdEnum.DestinationIncrementEveryCycleByX:
                    return CyConst.R_DESTINATION_INCREMENT_EVERY_CYCLE_BY_X;
                case CyEPropertyIdEnum.NumberOfXLoopsToExecute:
                    return CyConst.R_NUMBER_OF_X_LOOPS_TO_EXECUTE;
                case CyEPropertyIdEnum.SourceIncrementEveryCycleByY:
                    return CyConst.R_SOURCE_INCREMENT_EVERY_CYCLE_BY_Y;
                case CyEPropertyIdEnum.DestinationIncrementEveryCycleByY:
                    return CyConst.R_DESTINATION_INCREMENT_EVERY_CYCLE_BY_Y;
                default:
                    Debug.Assert(false);
                    return null;
            }
        }

        protected override IEnumerable<string> GetErrors(CyEPropertyIdEnum propId)
        {
            switch (propId)
            {
                case CyEPropertyIdEnum.DescriptorName:
                    foreach (CyDmaDescriptionProperties descriptor in m_descriptors)
                    {
                        if ((descriptor != this) && (descriptor.DescriptorName == DescriptorName))
                        {
                            yield return Resources.ErrorDescriptorName;
                        }
                    }
                    yield break;

                case CyEPropertyIdEnum.DataElementSize:
                    yield break;

                case CyEPropertyIdEnum.Interrupt:
                    yield break;

                case CyEPropertyIdEnum.SourceAndDestinationTransferWidth:
                    if (DataElementSize == CyDataElementSizeEnum.CY_DMA_WORD)
                    {
                        if (SourceAndDestinationTransferWidth != CySourceAndDestinationTransferWidthEnum.WordToWord)
                        {
                            string widthListStr = "\"" + Resources.WordToWord + "\"";
                            yield return String.Format(Resources.ErrorDestinationTransferWidth, Resources.Word, widthListStr);
                        }
                    }
                    if (DataElementSize == CyDataElementSizeEnum.CY_DMA_BYTE)
                    {
                        if ((SourceAndDestinationTransferWidth != CySourceAndDestinationTransferWidthEnum.ByteToByte)
                            && (SourceAndDestinationTransferWidth != CySourceAndDestinationTransferWidthEnum.ByteToWord)
                            && (SourceAndDestinationTransferWidth != CySourceAndDestinationTransferWidthEnum.WordToByte))
                        {
                            string widthListStr = "\"" + Resources.ByteToByte + "\", " + Resources.ByteToWord + "\", " + Resources.WordToByte + "\"";
                            yield return String.Format(Resources.ErrorDestinationTransferWidth, Resources.Byte, widthListStr);
                        }
                    }

                    if (DataElementSize == CyDataElementSizeEnum.CY_DMA_HALFWORD)
                    {
                        if ((SourceAndDestinationTransferWidth != CySourceAndDestinationTransferWidthEnum.HalfwordToHalfword)
                            && (SourceAndDestinationTransferWidth != CySourceAndDestinationTransferWidthEnum.HalfwordToWord)
                            && (SourceAndDestinationTransferWidth != CySourceAndDestinationTransferWidthEnum.WordToHalfword))
                        {
                            string widthListStr = "\"" + Resources.HalfwordToHalfword + "\", " + Resources.HalfwordToWord + "\", " + Resources.WordToHalfword + "\"";
                            yield return String.Format(Resources.ErrorDestinationTransferWidth, Resources.Halfword, widthListStr);
                        }
                    }
                    yield break;

                case CyEPropertyIdEnum.TriggerDeactivationAndRetriggering:
                    yield break;

                case CyEPropertyIdEnum.TriggerInputType:
                    yield break;

                case CyEPropertyIdEnum.TriggerOutput:
                    yield break;

            }
        }
        #endregion

        internal class EnumTypeConverter : EnumConverter
        {
            private Type m_enumType;

            public EnumTypeConverter(Type enumType)
                : base(enumType)
            {
                this.m_enumType = enumType;
            }

            public override bool CanConvertTo(ITypeDescriptorContext context,
                                               Type destType)
            {
                return destType == typeof(string);
            }

            public override object ConvertTo(ITypeDescriptorContext context,
                                              CultureInfo culture,
                                              object value, Type destType)
            {

                FieldInfo fi = m_enumType.GetField(Enum.GetName(m_enumType, value));
                DescriptionAttribute da =
                   (DescriptionAttribute)Attribute.GetCustomAttribute(
                      fi, typeof(DescriptionAttribute));

                if (da != null)
                    return da.Description;
                else
                    return value.ToString();
            }

            public override bool CanConvertFrom(ITypeDescriptorContext context,
                                                 Type srcType)
            {
                return srcType == typeof(string);
            }

            public override object ConvertFrom(ITypeDescriptorContext context,
                                                CultureInfo culture,
                                                object value)
            {
                foreach (FieldInfo fi in m_enumType.GetFields())
                {
                    DescriptionAttribute da =
                       (DescriptionAttribute)Attribute.GetCustomAttribute(
                          fi, typeof(DescriptionAttribute));

                    if ((da != null) && ((string)value == da.Description))
                        return Enum.Parse(m_enumType, fi.Name);
                }

                return Enum.Parse(m_enumType, (string)value);
            }

        }

        internal class PostTypeConverter : StringConverter
        {
            public override bool GetStandardValuesSupported(
              ITypeDescriptorContext context)
            {
                return true;
            }

            public override bool GetStandardValuesExclusive(
              ITypeDescriptorContext context)
            {
                return true;
            }

            public override StandardValuesCollection GetStandardValues(
              ITypeDescriptorContext context)
            {
                return new StandardValuesCollection(m_dmaDescriptorsNameList);
            }

        }

        #region PropertySorter
        internal class PropertySorter : ExpandableObjectConverter
        {
            #region Methods

            public override bool GetPropertiesSupported(ITypeDescriptorContext context)
            {
                return true;
            }

            public override PropertyDescriptorCollection GetProperties(
              ITypeDescriptorContext context, object value, Attribute[] attributes)
            {
                PropertyDescriptorCollection pdc =
                  TypeDescriptor.GetProperties(value, attributes);

                ArrayList orderedProperties = new ArrayList();

                foreach (PropertyDescriptor pd in pdc)
                {
                    Attribute attribute = pd.Attributes[typeof(PropertyOrderAttribute)];

                    if (attribute != null)
                    {
                        PropertyOrderAttribute poa = (PropertyOrderAttribute)attribute;
                        orderedProperties.Add(new PropertyOrderPair(pd.Name, poa.Order));
                    }
                    else
                    {
                        orderedProperties.Add(new PropertyOrderPair(pd.Name, 0));
                    }
                }
                orderedProperties.Sort();
                ArrayList propertyNames = new ArrayList();

                foreach (PropertyOrderPair pop in orderedProperties)
                {
                    propertyNames.Add(pop.Name);
                }

                return pdc.Sort((string[])propertyNames.ToArray(typeof(string)));
            }

            #endregion
        }

        #region PropertyOrder Attribute

        [AttributeUsage(AttributeTargets.Property)]
        internal class PropertyOrderAttribute : Attribute
        {
            private int m_order;
            public PropertyOrderAttribute(int order)
            {
                m_order = order;
            }

            public int Order
            {
                get { return m_order; }
            }
        }

        #endregion

        #region PropertyOrderPair
        internal class PropertyOrderPair : IComparable
        {
            private int m_order;
            private string m_name;

            public string Name
            {
                get { return m_name; }
            }

            public PropertyOrderPair(string name, int order)
            {
                m_order = order;
                m_name = name;
            }

            public int CompareTo(object obj)
            {
                int otherOrder = ((PropertyOrderPair)obj).m_order;

                if (otherOrder == m_order)
                {
                    string otherName = ((PropertyOrderPair)obj).m_name;
                    return string.Compare(m_name, otherName);
                }
                else if (otherOrder > m_order)
                    return -1;

                return 1;
            }
        }
        #endregion
        #endregion
    }
}
