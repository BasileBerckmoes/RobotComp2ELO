/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Xml.Serialization;

namespace DMA_PDL_v2_0.Utils
{
    public abstract class CyProperties : IDataErrorInfo
    {
        public static readonly Attribute[] ATTRS_BROWSABLE = new Attribute[] { BrowsableAttribute.Yes };

        protected CyParameters m_parameters;

        [XmlIgnore]
        [Browsable(false)]
        public abstract string ObjectName { get; }

        #region ICustomTypeDescriptor
        public PropertyDescriptorCollection GetProperties(Attribute[] attributes)
        {
            // Create a collection object to hold property descriptors
            PropertyDescriptorCollection pds = TypeDescriptor.GetProperties(this.GetType(), attributes);

            // Filter out properties
            pds = FilterProperties(pds);
            return pds;
        }

        public PropertyDescriptorCollection GetProperties()
        {
            return GetProperties(ATTRS_BROWSABLE);
        }

        public object GetPropertyOwner(PropertyDescriptor pd)
        {
            return this;
        }
        #endregion

        #region IDataErrorInfo
        [XmlIgnore]
        [Browsable(false)]
        public string Error
        {
            get { return String.Empty; }
        }

        public string this[string columnName]
        {
            get
            {
                PropertyDescriptor pd = GetPropertyDescriptor(columnName);
                return GetError(pd);
            }
        }
        #endregion

        #region Methods
        protected abstract PropertyDescriptorCollection FilterProperties(PropertyDescriptorCollection properties);
        protected abstract CyRange GetPropertyRange(CyEPropertyIdEnum propId);

        protected PropertyDescriptor GetPropertyDescriptor(string propertyName)
        {
            foreach (PropertyDescriptor pd in GetProperties())
            {
                if (pd.Name == propertyName)
                {
                    return pd;
                }
            }
            return null;
        }

        protected PropertyDescriptor GetPropertyDescriptor(CyEPropertyIdEnum propId)
        {
            foreach (PropertyDescriptor pd in TypeDescriptor.GetProperties(this, ATTRS_BROWSABLE))
            {
                Attribute attrib = pd.Attributes[typeof(CyPropertyIdAttribute)];
                if (attrib != null)
                {
                    CyEPropertyIdEnum id = ((CyPropertyIdAttribute)attrib).Id;
                    if (id == propId)
                    {
                        return pd;
                    }
                }
            }
            return null;
        }

        public string GetPropertyDisplayName(CyEPropertyIdEnum propId)
        {
            PropertyDescriptor pd = GetPropertyDescriptor(propId);
            if (pd != null)
            {
                return pd.DisplayName;
            }
            else
            {
                return null;
            }
        }

        protected PropertyDescriptor ApplyAttributes(PropertyDescriptor pd,
            string displayName = null)
        {
            CyEPropertyIdEnum propId = CyPropertyIdAttribute.GetPropertyId(pd);

            List<Attribute> attrs = new List<Attribute>();

            if (displayName != null)
            {
                DisplayNameAttribute dnAttr = new DisplayNameAttribute(displayName);
                attrs.Add(dnAttr);
            }

            CyCustomPropertyDescriptor customPd = new CyCustomPropertyDescriptor(pd, attrs.ToArray());
            return customPd;
        }
        #endregion

        #region Error checking
        protected virtual IEnumerable<string> GetErrors(CyEPropertyIdEnum propId)
        {
            yield break;
        }

        public IEnumerable<string> GetErrors()
        {
            PropertyDescriptorCollection pdc = GetProperties();
            foreach (PropertyDescriptor pd in pdc)
            {
                string error = GetFullError(pd);
                if (!String.IsNullOrEmpty(error))
                {
                    yield return error;
                }
            }
        }

        public IEnumerable<CyEPropertyIdEnum> GetErrorIDs()
        {
            PropertyDescriptorCollection pdc = GetProperties();
            foreach (PropertyDescriptor pd in pdc)
            {
                CyEPropertyIdEnum propId = CyPropertyIdAttribute.GetPropertyId(pd);
                string error = GetError(pd);
                if (!String.IsNullOrEmpty(error))
                {
                    yield return propId;
                }
            }
        }

        public string GetError(CyEPropertyIdEnum propId)
        {
            PropertyDescriptor pd = GetPropertyDescriptor(propId);
            return GetError(pd);
        }

        public string GetFullError(PropertyDescriptor pd)
        {
            string propErr = GetError(pd);
            if (String.IsNullOrEmpty(propErr)) return null;

            return String.Format("{0}: {1}", ObjectName, propErr);
        }

        private string GetError(PropertyDescriptor pd)
        {
            if (pd == null) return null;

            StringBuilder err = null;
            object propValue = pd.GetValue(this);
            CyEPropertyIdEnum propId = CyPropertyIdAttribute.GetPropertyId(pd);
            CyRange range = GetPropertyRange(propId);

            // Do not report any errors for read-only properties
            if (pd.IsReadOnly) return null;

            if ((range != null) && (range.CheckRange(propValue) == false))
            {
                CyPropertySite.AddError(ref err, range.GetErrorMessage(pd.DisplayName));
            }

            foreach (string errMsg in GetErrors(propId))
            {
                CyPropertySite.AddError(ref err, errMsg);
            }

            return (err == null) ? null : err.ToString();
        }
        #endregion
    }

    #region CyCustomPropertyDescriptor
    class CyCustomPropertyDescriptor : PropertyDescriptor
    {
        private readonly PropertyDescriptor m_pd;
        private readonly bool m_isReadOnly = false;

        public CyCustomPropertyDescriptor(PropertyDescriptor pd, Attribute[] attrs)
            : base(pd, attrs)
        {
            m_pd = pd;

        }

        public override Type PropertyType
        {
            get { return m_pd.PropertyType; }
        }

        public override Type ComponentType
        {
            get { return m_pd.ComponentType; }
        }

        public override object GetValue(object component)
        {
            return m_pd.GetValue(component);
        }

        public override void SetValue(object component, object value)
        {
            m_pd.SetValue(component, value);
        }

        public override bool CanResetValue(object component)
        {
            return m_pd.CanResetValue(component);
        }

        public override void ResetValue(object component)
        {
            m_pd.ResetValue(component);
        }

        public override bool IsReadOnly
        {
            get { return m_isReadOnly; }
        }

        public override bool ShouldSerializeValue(object component)
        {
            return m_pd.ShouldSerializeValue(component);
        }
    }
    #endregion

    #region CyPropertyIdAttribute
    public sealed class CyPropertyIdAttribute : Attribute
    {
        private readonly CyEPropertyIdEnum m_id;

        public CyPropertyIdAttribute(CyEPropertyIdEnum id)
        {
            m_id = id;
        }

        public CyEPropertyIdEnum Id
        {
            get { return m_id; }
        }

        public static CyEPropertyIdEnum GetPropertyId(PropertyDescriptor pd)
        {
            CyPropertyIdAttribute attrib = pd.Attributes[typeof(CyPropertyIdAttribute)] as CyPropertyIdAttribute;
            if (attrib != null)
            {
                return attrib.Id;
            }
            else
            {
                return CyEPropertyIdEnum.None;
            }
        }
    }
    #endregion
}
