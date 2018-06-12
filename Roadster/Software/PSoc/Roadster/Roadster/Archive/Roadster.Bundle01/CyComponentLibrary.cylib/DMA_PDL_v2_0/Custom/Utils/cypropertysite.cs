/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing.Design;
using System.Text;

namespace DMA_PDL_v2_0.Utils
{
    public sealed class CyPropertySite : ISite, IPropertyValueUIService, IDisposable
    {
        #region VerifyDataErrorInfo
        // Used to show error notifications.
        static readonly PropertyValueUIItemInvokeHandler UIItemNullHandler = delegate { };
        static readonly System.Drawing.Image UIItemErrorImage = Resources.ErrorProviderIcon;

        static void VerifyDataErrorInfo(ITypeDescriptorContext context, PropertyDescriptor propDesc,
            ArrayList valueUIItemList)
        {
            IDataErrorInfo errInfo = (context == null) ? null : context.Instance as IDataErrorInfo;
            string propName = propDesc == null ? null : propDesc.Name;

            if (errInfo != null && String.IsNullOrEmpty(propName) == false)
            {
                string errMsg = errInfo[propName];
                if (string.IsNullOrEmpty(errMsg) == false)
                {
                    valueUIItemList.Add(new PropertyValueUIItem(UIItemErrorImage, UIItemNullHandler, errMsg));
                }
            }
        }
        #endregion

        private readonly IContainer m_container = new Container();
        private readonly Dictionary<Type, object> m_services;
        private readonly IComponent m_component = null;
        private bool m_designMode = false;

        IComponent ISite.Component { get { return m_component; } }
        IContainer ISite.Container { get { return m_container; } }
        bool ISite.DesignMode { get { return m_designMode; } }
        string ISite.Name { get; set; }

        public CyPropertySite()
        {
            QueryPropertyUIValueItems += VerifyDataErrorInfo;

            m_services = new Dictionary<Type, object>();
            m_services[typeof(IPropertyValueUIService)] = this;
        }

        object IServiceProvider.GetService(Type serviceType)
        {
            object service;
            if (m_services != null && m_services.TryGetValue(serviceType, out service))
            {
                return service;
            }
            return null;
        }

        #region IPropertyValueUIService
        public event EventHandler PropertyUIValueItemsChanged;
        public event PropertyValueUIHandler QueryPropertyUIValueItems;

        PropertyValueUIItem[] IPropertyValueUIService.GetPropertyUIValueItems(ITypeDescriptorContext context,
            PropertyDescriptor propDesc)
        {
            ArrayList list = null;
            if (QueryPropertyUIValueItems != null)
            {
                list = new ArrayList();
                QueryPropertyUIValueItems(context, propDesc, list);
            }
            if (list == null || list.Count == 0)
            {
                return new PropertyValueUIItem[0];
            }
            PropertyValueUIItem[] result = new PropertyValueUIItem[list.Count];
            list.CopyTo(result);
            return result;
        }

        void IPropertyValueUIService.NotifyPropertyValueUIItemsChanged()
        {
            if (PropertyUIValueItemsChanged != null)
            {
                PropertyUIValueItemsChanged(this, EventArgs.Empty);
            }
        }

        void IPropertyValueUIService.RemovePropertyValueUIHandler(PropertyValueUIHandler newHandler)
        {
            QueryPropertyUIValueItems -= newHandler;
        }

        void IPropertyValueUIService.AddPropertyValueUIHandler(PropertyValueUIHandler newHandler)
        {
            QueryPropertyUIValueItems += newHandler;
        }
        #endregion

        public void Dispose()
        {
            m_container.Dispose();
        }

        public static void AddError(ref StringBuilder sb, string message)
        {
            if (string.IsNullOrEmpty(message) == false)
            {
                if (sb == null) sb = new StringBuilder();
                if (sb.Length > 0)
                    sb.AppendLine();
                sb.Append(message);
            }
        }
    }
}
