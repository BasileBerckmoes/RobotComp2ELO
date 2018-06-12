/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Bootloadable_v1_60
{
    public class CyParameters
    {
        #region Constants
        public const string PARAM_APPVERSION = "appVersion";
        public const string PARAM_APPID = "appID";
        public const string PARAM_APPCUSTOMID = "appCustomID";
        public const string PARAM_AUTOPLACEMENT = "autoPlacement";
        public const string PARAM_PLACEMENTADDRESS = "placementAddress";
        public const string PARAM_CHECKSUMEXCLUDESIZE = "checksumExcludeSize";
        public const string PARAM_HEXFILEPATH = "hexFilePath";
        public const string PARAM_ELFFILEPATH = "elfFilePath";

        private const string CPUSS_V2 = "m0s8cpussv2";
        private const string CPUSS_V3 = "m0s8cpussv3";
        private const string FLASE_PAGE_SIZE = "SPCIF.FLASH_PAGE_SIZE";

        // Flash Row Size
        const int FLASH_ROW_LENGTH_PSOC4 = 128;
        const int FLASH_ROW_LENGTH_PSOC3_5 = 256;
        #endregion Constants

        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        public bool m_globalEditMode = false;

        #region Properties, Fields
        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }
        public UInt16 AppVersion
        {
            get { return GetValue<UInt16>(PARAM_APPVERSION); }
            set { SetValue(PARAM_APPVERSION, value); }
        }
        public UInt16 AppID
        {
            get { return GetValue<UInt16>(PARAM_APPID); }
            set { SetValue(PARAM_APPID, value); }
        }
        public UInt32 AppCustomID
        {
            get { return GetValue<UInt32>(PARAM_APPCUSTOMID); }
            set { SetValue(PARAM_APPCUSTOMID, value); }
        }
        public bool AutoPlacement
        {
            get { return GetValue<bool>(PARAM_AUTOPLACEMENT); }
            set { SetValue(PARAM_AUTOPLACEMENT, value); }
        }
        public UInt32 PlacementAddress
        {
            get { return GetValue<UInt32>(PARAM_PLACEMENTADDRESS); }
            set { SetValue(PARAM_PLACEMENTADDRESS, value); }
        }
        public UInt32 ChecksumExcludeSize
        {
            get { return GetValue<UInt32>(PARAM_CHECKSUMEXCLUDESIZE); }
            set { SetValue(PARAM_CHECKSUMEXCLUDESIZE, value); }
        }

        public string HexFilePath
        {
            get { return GetValue<string>(PARAM_HEXFILEPATH); }
            set { SetValue(PARAM_HEXFILEPATH, value); }
        }

        public string ElfFilePath
        {
            get { return GetValue<string>(PARAM_ELFFILEPATH); }
            set { SetValue(PARAM_ELFFILEPATH, value); }
        }

        public int FlashRowLength
        {
            get 
            {
                if (m_instQuery.DeviceQuery.IsPSoC4)
                {
                    int flashPgSizeParam = -1;

                    if (m_instQuery.DeviceQuery.GetFeatureCount(CPUSS_V2) > 0)
                    {
                        flashPgSizeParam = m_instQuery.DeviceQuery.GetFeatureParameter(CPUSS_V2, FLASE_PAGE_SIZE);
                    }
                    else if (m_instQuery.DeviceQuery.GetFeatureCount(CPUSS_V3) > 0)
                    {
                        flashPgSizeParam = m_instQuery.DeviceQuery.GetFeatureParameter(CPUSS_V3, FLASE_PAGE_SIZE);
                    }

                    switch (flashPgSizeParam)
                    {
                        case 0:
                            return 64;
                        case 1:
                            return 128;
                        case 3:
                            return 256;

                        // not m0s8cpussv2 and not m0s8cpussv3 
                        default:
                            return FLASH_ROW_LENGTH_PSOC4;
                    }
                }
                else
                {
                    return FLASH_ROW_LENGTH_PSOC3_5;
                }
            }
        }        
        #endregion Properties, Fields

        #region Common
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;
        }

        public CyParameters(ICyInstQuery_v1 instQuery)
            : this(instQuery, null)
        {
        }

        public CyParameters(ICyInstEdit_v1 instEdit)
            : this(instEdit, instEdit)
        {
        }

        private T GetValue<T>(string paramName)
        {
            return GetValue<T>(paramName, m_instQuery);
        }

        public static T GetValue<T>(string paramName, ICyInstQuery_v1 instQuery)
        {
            if (instQuery == null) return default(T);
            T value;
            CyCustErr err = instQuery.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            return (err != null && err.IsOK) ? value : default(T);
        }

        private void SetValue<T>(string paramName, T value)
        {
            if (m_instEdit != null && m_globalEditMode)
            {
                string valueToSet = (value == null) ? String.Empty : value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if ((value is byte) || (value is UInt16) || (value is UInt32) || (value is UInt64))
                    valueToSet += "u";
                if (m_instEdit.SetParamExpr(paramName, valueToSet))
                {
                    m_instEdit.CommitParamExprs();
                }
            }
        }
        #endregion Common

        #region Public functions
        public string CreateDesignPersistantPath(string filePath)
        {
            string newFilePath = filePath;
            if (m_instEdit != null)
            {
                newFilePath = m_instEdit.CreateDesignPersistantPath(filePath);
            }
            else
            {
                Debug.Assert(false);
            }
            return newFilePath;
        }
        #endregion
    }
}
