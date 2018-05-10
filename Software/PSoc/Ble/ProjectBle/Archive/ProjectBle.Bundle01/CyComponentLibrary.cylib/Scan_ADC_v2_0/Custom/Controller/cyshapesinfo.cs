/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Scan_ADC_v2_0
{
    public class CyShapesInfo
    {
        #region Class enums
        public enum VnegSel { Vss, Vref, Terminal };
        public enum VrefSel { Vdda, Vdda_div_2, Vbgr, Terminal };
        #endregion

        #region Class members
        List<int> m_ChannelCounts = new List<int>(new int[]
            //{ 4, 1, 2, 1});
             { 16, 16, 16, 16 });

        List<uint> m_ChannelDiffMasks = new List<uint>(new uint[] { 4u, 1u, 2u, 0u });
        List<uint> m_ChannelSingleMasks = new List<uint>(new uint[] { 2u, 6u, 4u, 0u });
        List<uint> m_ChannelFilterMasks = new List<uint>(new uint[] { 1u, 0u, 1u, 0u });
        #endregion
        
        #region Constructors

        public CyShapesInfo()
        {
            this.ConfigCount = 2;
        }
        #endregion

        #region Properties
        public List<CyEVnegSource> ConfigVnegSource { get; set; }
        public List<CyEVrefSource> ConfigVrefSource { get; set; }

        public bool ShowSocTerm { get; set ; }
        public bool ShowClkTerm { get; set; }
        public UInt32 ConfigFilterMask { get; set; }
        public string[] ConfigFilterAliases { get; set; }
        public int ConfigCount { get; set; }
        public long ConfigSpace { get; set; }
        public bool ExposeTestTerminals { get; set; }

        public List<bool> ConfigVnegTerms { get; set; }
        public List<bool> ConfigVrefTerms { get; set; }

        public List<int> ChannelCounts
        {
            get { return m_ChannelCounts; }
            set { m_ChannelCounts = value; }
        }

        public List<uint> ChannelDiffMasks
        {
            get { return m_ChannelDiffMasks; }
            set { m_ChannelDiffMasks = value; }
        }

        public List<uint> ChannelSingleMasks
        {
            get { return m_ChannelSingleMasks; }
            set { m_ChannelSingleMasks = value; }
        }

        public List<uint> ChannelFilterMasks
        {
            get { return m_ChannelFilterMasks; }
            set { m_ChannelFilterMasks = value; }
        }

        public uint GetConfigDiffMask(int configNum)
        {
            int channelCount = m_ChannelCounts[configNum];
            uint channelMask = (1u << channelCount) - 1;
            uint diffMask = m_ChannelDiffMasks[configNum] & channelMask;
            return diffMask;
        }

        public uint GetConfigSingleMask(int configNum)
        {
            int channelCount = m_ChannelCounts[configNum];
            uint channelMask = (1u << channelCount) - 1;
            uint singleMask = (~m_ChannelDiffMasks[configNum]) & channelMask;
            return singleMask;
        }

        #endregion
    }
}

//[] END OF FILE
