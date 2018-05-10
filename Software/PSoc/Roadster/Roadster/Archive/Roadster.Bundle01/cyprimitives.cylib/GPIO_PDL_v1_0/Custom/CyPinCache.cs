/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using CyDesigner.Common.Base;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using CyDesigner.Toolkit.TerminalControl_v1;

namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    /// <summary>
    /// Track the state of each pin of a CyPinData instance by creating a dictionary, keyed by formal parameter name,
    /// of string arrays, handling Get and Set methods for each value, and propagating index updates.
    /// Validation is also called after PropagateNewIndex and RestoreFormals.  It is not called after Set,
    /// because that is done in the pin data class itself, after setting the local values.
    /// </summary>
    public class CyPinCache
    {
        private readonly Dictionary<string, Cache> m_property = new Dictionary<string, Cache>();
        private CyPinData m_data;
        private Func<string, CyCompDevParam> m_query;
        private Action m_validate;

        // Optionally allow for edits; Set will be a NOP if this is null
        private ICyInstEdit_v1 m_edit = null;

        /// <summary>
        /// Construct an unitialized cache.  Call Initialize() before using it.
        /// </summary>
        internal CyPinCache()
        {
        }

        /// <summary>
        /// Set a reference to the data instance, query, and validator.
        /// The cache is useless until this is called.
        /// </summary>
        /// <param name="data">The CyPinData instance.</param>
        /// <param name="query">The query function from Creator.</param>
        /// <param name="validate">A validation action.</param>
        internal void Initialize(CyPinData data, Func<string, CyCompDevParam> query, Action validate)
        {
            m_data = data;
            m_query = query;
            m_validate = validate;
        }

        /// <summary>
        /// The editor is not set when the class is created, and must be set later.
        /// </summary>
        /// <param name="edit">The edit interface.</param>
        public void SetEditor(ICyInstEdit_v1 edit)
        {
            m_edit = edit;
        }

        // Return the dictionary so calls can be chained.
        internal CyPinCache Add(string formal, bool? usePrevious = null, string defaultValue = null)
        {
            m_property.Add(formal, new Cache(usePrevious, defaultValue, null));
            return this;
        }

        internal CyPinCache Add(string formal, string defaultValue)
        {
            m_property.Add(formal, new Cache(null, defaultValue, null));
            return this;
        }

        internal CyPinCache Add(string formal, bool? usePrevious, string defaultValue, Action<string, int, CyPinData> sideEffect)
        {
            m_property.Add(formal, new Cache(usePrevious, defaultValue, sideEffect));
            return this;
        }

        internal CyPinCache Add(string formal, string defaultValue, Action<string, int, CyPinData> sideEffect)
        {
            m_property.Add(formal, new Cache(null, defaultValue, sideEffect));
            return this;
        }

        /// <summary>
        /// Hand a Get request off to the appropriate cache instance.
        /// </summary>
        /// <param name="key">The formal parameter name.</param>
        /// <param name="index">The pin index.</param>
        /// <param name="pinType">The type of pin.</param>
        /// <returns>The cached pin value at the given index.</returns>
        internal string Get(string key, int index, CyPinType pinType)
        {
            Cache pinTypes;
            bool cacheExists = m_property.TryGetValue(Formal.Param.PinTypes, out pinTypes);
            Debug.Assert(cacheExists);
            int priorIdx = pinTypes.PriorIndex(index);
            bool pinTypeMatch = priorIdx >= 0 && Formal.GetPinType(pinTypes.Value(priorIdx)) == pinType;

            Cache cache;
            if (!m_property.TryGetValue(key, out cache))
            {
                Debug.Fail("Unhandled parameter in Get: " + key);
                return string.Empty;
            }

            switch (key)
            {
                case Formal.Param.DriveMode:
                    cache.EnsureValidIndex(key, index, pinTypeMatch, CyPinData.GetDefaultDriveMode(pinType), m_query);
                    break;
                case Formal.Param.InitialDriveStates:
                    cache.EnsureValidIndex(key, index, false, m_data.GetDefaultDriveState(index), m_query);
                    break;
                case Formal.Param.InputBuffersEnabled:
                    cache.EnsureValidIndex(key, index, pinTypeMatch, CyPinData.GetDefaultInputBuffersEnabled(pinType), m_query);
                    break;
                default:
                    cache.EnsureValidIndex(key, index, pinTypeMatch, m_query);
                    break;
            }

            return cache.Get(index);
        }

        /// <summary>
        /// Hand a Get request off to the appropriate cache instance.
        /// </summary>
        /// <param name="key">The formal parameter name.</param>
        /// <param name="index">The pin index.</param>
        /// <param name="pinType">The type of pin.</param>
        /// <returns>The cached pin value of the right type at the given index.</returns>
        internal T Get<T>(string key, int index, CyPinType pinType)
        {
            return Formal.GetValue<T>(Get(key, index, pinType));
        }

        /// <summary>
        /// Hand a Set request off to the appropriate cache instance.
        /// </summary>
        /// <param name="key">The formal parameter name.</param>
        /// <param name="value">The new value, as a string..</param>
        /// <param name="index">The pin index.</param>
        /// <returns>True on success.</returns>
        internal bool Set(string key, string value, int index)
        {
            // Preview mode, no setting needed
            if (null == m_edit)
                return false;

            Cache cache;
            if (!m_property.TryGetValue(key, out cache))
            {
                Debug.Fail("Unhandled parameter in Set: " + key);
                return false;
            }

            // Ensure there is a valid index (through the back door to avoid duplicating the machinery).
            // Note: not cache.Get; we need the logic in the Get method above
            if (!cache.HasIndex(index))
                Get(key, index, m_data.Pins[index].Type);

            cache.Set(value, index, m_data);
            return m_edit.SetParamExpr(key, cache.ToString());
        }

        internal void Validate()
        {
            Action validate = m_validate;
            if (null != validate)
                validate();
        }

        /// <summary>
        /// If a pin index changes, it does so for all the fields.  Let them know.
        /// </summary>
        /// <param name="oldIndex">The old index.</param>
        /// <param name="newIndex">The new index.</param>
        /// <param name="type">The pin type.</param>
        /// <remarks>The value at the old index will be cleared afterward.</remarks>
        internal void PropagateNewIndex(int oldIndex, int newIndex, CyPinType type)
        {
            // Doesn't make sense to propagate when we're in a preview context
            if (m_edit != null)
            {
                foreach (string formal in m_property.Keys)
                {
                    // Move the old setting to our new position.
                    string oldSetting = Get(formal, oldIndex, type);
                    Set(formal, oldSetting, newIndex);
                    // Clear the old data to avoid problems with "leftovers" later
                    Set(formal, string.Empty, oldIndex);
                }
                Validate(); // Also commits changes
            }
        }

        /// <summary>
        /// List all formal parameter values
        /// </summary>
        /// <returns>A list of formal parameter names.</returns>
        internal IList<string> FormalParameters { get { return m_property.Keys.ToList(); } }

        /// <summary>
        /// Export all values for this pin and index.
        /// </summary>
        /// <param name="index">The pin index.</param>
        /// <param name="type">The pin type.</param>
        /// <returns>A list of key-value pairs, including each field's value.</returns>
        internal IList<KeyValuePair<string, string>> ExportFormals(int index, CyPinType type)
        {
            List<KeyValuePair<string, string>> result = new List<KeyValuePair<string, string>>();
            foreach (string formal in m_property.Keys)
                result.Add(new KeyValuePair<string, string>(formal, Get(formal, index, type)));
            return result;
        }

        /// <summary>
        /// Set all values from the given key-value pair list.
        /// </summary>
        /// <param name="exprs">The list of keys and values.</param>
        /// <param name="index">The pin index.</param>
        internal void RestoreFormals(IList<KeyValuePair<string, string>> exprs, int index)
        {
            Debug.Assert(null != m_edit);
            if (null != m_edit) // Could I get here in "preview context"?  Don't do anything in that case.
            {
                foreach (KeyValuePair<string, string> kvp in exprs)
                {
                    string formal = kvp.Key;
                    string value = kvp.Value;
                    Set(formal, value, index);
                }
                Validate();
            }
        }

        /// <summary>
        /// Use the query interface to set a value after ensuring we will not overwrite a user's selection.
        /// </summary>
        /// <param name="key">The formal parameter name.</param>
        /// <param name="index">The pin index.</param>
        /// <param name="newValue">The new value.</param>
        internal void UpdateIfNotSetByUser(string key, int index, string newValue)
        {
            Cache cache;
            bool cacheExists = m_property.TryGetValue(key, out cache);
            Debug.Assert(cacheExists);
            cache.UpdateIfNotSetByUser(m_query, key, index, newValue);
        }

        // One cache instance per formal parameter.
        private class Cache
        {
            // The cache, one string per pin
            protected string[] m_cache;
            protected bool? m_usePrevious = null;   // Get a default value from the prior pin? Null if it depends on the pin type
            protected string m_defaultValue;    // The default value (see CyPinCache.Get for special cases)
            internal Action<string, int, CyPinData> m_sideEffect;   // Do this after setting a value.

            internal Cache(bool? usePrevious, string defaultValue, Action<string, int, CyPinData> sideEffect)
            {
                m_cache = null;
                m_usePrevious = usePrevious;
                m_defaultValue = defaultValue;
                m_sideEffect = sideEffect;
            }

            // The index prior to a given one may contain the default value I want.
            internal int PriorIndex(int index)
            {
                if (null == m_cache)
                    return -1;
                int priorIdx = Math.Min(m_cache.Length, index) - 1;
                return priorIdx;
            }

            // The value at this index may not exist, but give it to me if so. See Get(), EnsureValidIndex().
            internal string Value(int index)
            {
                return HasIndex(index) ? m_cache[index] : string.Empty;
            }

            // True if there is already a cached value at this index. Call EnsureValidIndex() to make sure there is.
            internal bool HasIndex(int index)
            {
                return null != m_cache && 0 <= index && index < m_cache.Length;
            }

            // By the time I get here, I should have been given a value.  See Value(), EnsureValidIndex().
            internal string Get(int index)
            {
                return m_cache[index];
            }

            // By the time I get here, I should have a value; now change it.  See Value(), EnsureValidIndex().
            internal void Set(string value, int index, CyPinData data)
            {
                m_cache[index] = value.Trim();

                // If there is a side-effect,  calculate it before returning
                var sideEffect = m_sideEffect;
                if (null != sideEffect)
                    sideEffect(value, index, data);
            }

            public override string ToString()
            {
                return string.Join(",", m_cache);
            }

            internal void UpdateIfNotSetByUser(Func<string, CyCompDevParam> query, string key, int index, string newValue)
            {
                // Update our cached value if both of the following are true:
                // * We have a cached value in the first place
                // * There is no value saved to the parameter (meaning the user never explicitly set it)
                if (m_cache != null && index < m_cache.Length)
                {
                    Debug.Assert(null != query);
                    string value = query(key).Value;
                    if (string.IsNullOrEmpty(value))
                        m_cache[index] = newValue;
                }
            }

            internal void EnsureValidIndex(string key, int index, bool pinTypeMatch,
                                Func<string, CyCompDevParam> query)
            {
                EnsureValidIndex(key, index, pinTypeMatch, m_defaultValue, query);
            }

            // If there is not yet a value at this index, create a default value here.
            internal void EnsureValidIndex(string key, int index, bool pinTypeMatch, string defaultValue,
                                           Func<string, CyCompDevParam> query)
            {
                if (null == m_cache)
                {
                    Debug.Assert(null != query);
                    string value = query(key).Value;
                    m_cache = string.IsNullOrEmpty(value) ? new string[0] : value.Split(',');
                    for (int i = 0; i < m_cache.Length; ++i)
                        m_cache[i] = m_cache[i].Trim();
                }
                Debug.Assert(null != defaultValue);

                bool usePrevious = m_usePrevious ?? pinTypeMatch;
                int requiredSize = index + 1;
                if (requiredSize > m_cache.Length)
                {
                    int oldSize = m_cache.Length;
                    Array.Resize(ref m_cache, requiredSize);

                    // Pick the previous pin to copy or use default
                    for (int i = oldSize; i < m_cache.Length; i++)
                        m_cache[i] = (usePrevious && i > 0) ? m_cache[i - 1] : defaultValue;
                }

                // Always use default here - for some settings (like minimum supply) the default value is the empty
                // string, and we don't want to end up copying previous here
                if (string.IsNullOrEmpty(m_cache[index]))
                    m_cache[index] = defaultValue;
            }
        }
    }
}
