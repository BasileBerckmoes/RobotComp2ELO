/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Serialization;

namespace DMA_PDL_v2_0.Utils
{
    public static class CySerializer
    {
        public static string Serialize<T>(T obj)
        {
            string serializedXml = String.Empty;

            //Custom namespaces for serialization
            XmlSerializerNamespaces customNamespace = new XmlSerializerNamespaces();
            string curNamespace = typeof(T).Namespace;
            string version = curNamespace.Substring(curNamespace.LastIndexOf("_v") + 2);
            customNamespace.Add("Version", version);

            using (StringWriter sw = new StringWriter(CultureInfo.InvariantCulture))
            {
                try
                {
                    // Not we do not use typeof(T) as XML serializer type
                    // because T might be an interface
                    Type type = obj.GetType();
                    XmlSerializer serializer = new XmlSerializer(type);
                    serializer.Serialize(sw, obj, customNamespace);
                }
                catch (InvalidOperationException e)
                {
                    Debug.Fail(String.Format(Resources.DeserializationErrorFmt,
                        typeof(T).Name, e.Message));
                }
                serializedXml = sw.ToString();
            }

            return serializedXml;
        }

        /// <summary>
        /// Deserializes XML into the object of the specified type.
        /// </summary>
        /// <typeparam name="T">Type of the object the string should be deserialized to.</typeparam>
        /// <param name="serializedXml">XML string.</param>
        /// <param name="showWarning">Indicates whether to show warning message box in case 
        /// of deserialization failure.</param>
        /// <returns>Object deserialized from the specified XML.</returns>
        public static T Deserialize<T>(string serializedXml, bool showWarning = true)
        {
            T res = default(T);

            if (String.IsNullOrEmpty(serializedXml))
            {
                res = (T)Activator.CreateInstance(typeof(T));
                return res;
            }

            using (StringReader sr = new StringReader(serializedXml.ToString(CultureInfo.InvariantCulture)))
            {
                try
                {
                    XmlReader tr = XmlReader.Create(sr);

                    //Remove header <?xml version="1.0" encoding="utf-16" ?>
                    tr.Read();
                    tr.Read();
                    //Go to first Node with attributes
                    while (tr.HasAttributes == false)
                    {
                        tr.Read();
                    }

                    // This version information is used to know XML of which component version is deserialized.
                    string ver_info = tr.GetAttribute(0);

                    XmlSerializer serializer = new XmlSerializer(typeof(T));
                    res = (T)serializer.Deserialize(tr);
                }
                catch
                {
                    Debug.Assert(showWarning, "Deserialization failed.");
                    if (showWarning)
                    {
                        // Set a breakpoint at the line below to catch deserialization exceptions
                        MessageBox.Show(Resources.DeserializationFailed, typeof(CyCustomizer).ToString(),
                            MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
                finally
                {
                    if (res == null)
                    {
                        res = (T)Activator.CreateInstance(typeof(T));
                    }
                }
            }
            return res;
        }
    }
}
