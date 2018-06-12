/*******************************************************************************
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;

namespace DMA_PDL_v2_0.Utils
{
    //This class is used for holding default properties
    [DebuggerDisplay("Default={Default} Min={Min} Max={Max}")]
    public class CyRange : IEnumerable<int>
    {
        private readonly int m_default;
        private readonly int m_min;
        private readonly int m_max;

        public CyRange(int defaultValue, int min, int max)
        {
            m_default = defaultValue;
            m_min = min;
            m_max = max;
            Debug.Assert((min <= m_default) && (m_default <= max));
        }

        public int Default
        {
            get { return m_default; }
        }

        public int Min
        {
            get { return m_min; }
        }

        public int Max
        {
            get { return m_max; }
        }

        public bool CheckRange(object val)
        {
            int value = 0;
            if (!int.TryParse(val.ToString(), out value))
                return false;

            if ((m_min > value) || (m_max < value))
                return false;

            return true;
        }

        public string GetErrorMessage(string propertyDisplayName)
        {
            return String.Format(Resources.RangeErrorFmt,
                    propertyDisplayName, m_min, m_max);
        }

        public static void MakeValidValue(ref int value, int min, int max)
        {
            if (value < min)
                value = min;
            else if (value > max)
                value = max;
        }

        #region IEnumerable<int>
        public IEnumerator<int> GetEnumerator()
        {
            for (int value = m_min; value <= m_max; value++)
            {
                yield return value;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
        #endregion
    }
}
