/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace Bootloader_v1_60
{
    public class CyParameters
    {
        #region Const
        public const string PARAM_WAIT_TIME = "waitForCommandTime";
        public const string PARAM_WAIT_ENABLE = "waitForCommand";
        public const string PARAM_PACKET_CHECKSUM_TYPE = "packetChecksumCrc";
        public const string PARAM_VERSION = "bootloaderAppVersion";
        public const string PARAM_FAST_VALIDATION = "fastAppValidation";
        public const string PARAM_FAST_BR_VALIDATION = "bootloaderAppValidation";
        public const string PARAM_CMD_FLASHSIZE = "cmdGetFlashSizeAvail";
        public const string PARAM_CMD_VERIFYROWINFLASH = "cmdVerifyRowInFlashAvail";
        public const string PARAM_CMD_ERASEROW = "cmdEraseRowAvail";
        public const string PARAM_CMD_VERIFYROW = "cmdVerifyRowAvail";
        public const string PARAM_CMD_VERIFYAPPCHKSUM = "cmdVerifyAppChksumAvail";
        public const string PARAM_CMD_SENDDATA = "cmdSendDataAvail";
        public const string PARAM_CMD_SYNCBOOTLOADER = "cmdSyncBootloaderAvail";
        public const string PARAM_CMD_GETAPPSTATUS = "cmdGetAppStatusAvail";
        public const string PARAM_CMD_GETMETADATA = "cmdGetMetadataAvail";
        public const string PARAM_MULTI_APP = "multiAppBootloader";
        public const string PARAM_AUTO_APP_SWITCHING = "autoAppSwitchingAvail";
        public const string PARAM_GOLDEN_IMAGE_SUPPORT = "goldenImageSupportAvail";
        public const string PARAM_SECURITY_KEY = "securityKey";
        public const string PARAM_SECURITY_KEY_AVAIL = "securityKeyAvail";
        public const string PARAM_SECURITY_KEY_LENGTH = "securityKeyLength";
        public const string PARAM_LAUNCHER = "launcher";
        public const string PARAM_COPIER = "copier";
        public const string PARAM_IO_COMPONENT = "ioComponent";

        public const string CUSTOM_INTERFACE = "Custom interface";
        public const string LAUNCHER_ONLY = "None, launcher only";

        public const UInt16 MAX_WAIT_TIME = 25500;
        #endregion Const

        #region Properties, Fields

        private readonly ICyInstQuery_v1 m_instQuery;
        private readonly ICyInstEdit_v1 m_instEdit;
        public bool m_globalEditMode = false;

        public ICyInstQuery_v1 InstQuery
        {
            get { return m_instQuery; }
        }
        public byte WaitTime
        {
            get { return GetValue<byte>(PARAM_WAIT_TIME); }
            set { SetValue(PARAM_WAIT_TIME, value); }
        }
        public bool WaitEnable
        {
            get { return GetValue<bool>(PARAM_WAIT_ENABLE); }
            set { SetValue(PARAM_WAIT_ENABLE, value); }
        }
        public bool PacketChecksumType
        {
            get { return GetValue<bool>(PARAM_PACKET_CHECKSUM_TYPE); }
            set { SetValue(PARAM_PACKET_CHECKSUM_TYPE, value); }
        }
        public UInt16 Version
        {
            get { return GetValue<UInt16>(PARAM_VERSION); }
            set { SetValue(PARAM_VERSION, value); }
        }
        public bool FastValidation
        {
            get { return GetValue<bool>(PARAM_FAST_VALIDATION); }
            set { SetValue(PARAM_FAST_VALIDATION, value); }
        }
        public bool FastBrValidation
        {
            get { return GetValue<bool>(PARAM_FAST_BR_VALIDATION); }
            set { SetValue(PARAM_FAST_BR_VALIDATION, value); }
        }
        public bool CmdFlashSize
        {
            get { return GetValue<bool>(PARAM_CMD_FLASHSIZE); }
            set { SetValue(PARAM_CMD_FLASHSIZE, value); }
        }
        public bool CmdVerifyRowInFlash
        {
            get { return GetValue<bool>(PARAM_CMD_VERIFYROWINFLASH); }
            set { SetValue(PARAM_CMD_VERIFYROWINFLASH, value); }
        }
        public bool CmdEraseRow
        {
            get { return GetValue<bool>(PARAM_CMD_ERASEROW); }
            set { SetValue(PARAM_CMD_ERASEROW, value); }
        }
        public bool CmdVerifyRow
        {
            get { return GetValue<bool>(PARAM_CMD_VERIFYROW); }
            set { SetValue(PARAM_CMD_VERIFYROW, value); }
        }
        public bool CmdVerifyAppChksum
        {
            get { return GetValue<bool>(PARAM_CMD_VERIFYAPPCHKSUM); }
            set { SetValue(PARAM_CMD_VERIFYAPPCHKSUM, value); }
        }
        public bool CmdSendData
        {
            get { return GetValue<bool>(PARAM_CMD_SENDDATA); }
            set { SetValue(PARAM_CMD_SENDDATA, value); }
        }
        public bool CmdSyncBootloader
        {
            get { return GetValue<bool>(PARAM_CMD_SYNCBOOTLOADER); }
            set { SetValue(PARAM_CMD_SYNCBOOTLOADER, value); }
        }
        public bool CmdGetAppStatus
        {
            get { return GetValue<bool>(PARAM_CMD_GETAPPSTATUS); }
            set { SetValue(PARAM_CMD_GETAPPSTATUS, value); }
        }
        public bool CmdGetMetadata
        {
            get { return GetValue<bool>(PARAM_CMD_GETMETADATA); }
            set { SetValue(PARAM_CMD_GETMETADATA, value); }
        }
        public bool MultiAppBootloader
        {
            get { return GetValue<bool>(PARAM_MULTI_APP); }
            set { SetValue(PARAM_MULTI_APP, value); }
        }
        public bool AutoAppSwitching
        {
            get { return GetValue<bool>(PARAM_AUTO_APP_SWITCHING); }
            set { SetValue(PARAM_AUTO_APP_SWITCHING, value); }
        }
        public bool GoldenImageSupport
        {
            get { return GetValue<bool>(PARAM_GOLDEN_IMAGE_SUPPORT); }
            set { SetValue(PARAM_GOLDEN_IMAGE_SUPPORT, value); }
        }
        public string SecurityKey
        {
            get { return GetValue<string>(PARAM_SECURITY_KEY); }
            set { SetValue(PARAM_SECURITY_KEY, value); }
        }
        public bool SecurityKeyAvail
        {
            get { return GetValue<bool>(PARAM_SECURITY_KEY_AVAIL); }
            set { SetValue(PARAM_SECURITY_KEY_AVAIL, value); }
        }
        public byte SecurityKeyLength
        {
            get { return GetValue<byte>(PARAM_SECURITY_KEY_LENGTH); }
            set { SetValue(PARAM_SECURITY_KEY_LENGTH, value); }
        }
        public bool Launcher
        {
            get { return GetValue<bool>(PARAM_LAUNCHER); }
            set { SetValue(PARAM_LAUNCHER, value); }
        }
        public bool Copier
        {
            get { return GetValue<bool>(PARAM_COPIER); }
            set { SetValue(PARAM_COPIER, value); }
        }

        public string IOComponent
        {
            get
            {
                string val = GetValue<string>(PARAM_IO_COMPONENT);
                if (val.ToLower() == CUSTOM_INTERFACE.ToLower())
                    val = CUSTOM_INTERFACE;
                return val;
            }
            set
            {
                if (value.ToLower() == CUSTOM_INTERFACE.ToLower())
                    value = CUSTOM_INTERFACE;
                SetValue(PARAM_IO_COMPONENT, value);
            }
        }

        private List<string> m_ioComponentList;
        public List<string> IOComponentList
        {
            get { return m_ioComponentList; }
        }

        private CyKeyArray m_keyArray;
        public CyKeyArray KeyArray
        {
            get { return m_keyArray; }
        }

        public bool IsLauncherSupported
        {
            get
            {
                Debug.Assert(InstQuery != null);
                // Launcher architecture is not supported for PSoC3 device family
                return !InstQuery.DeviceQuery.IsPSoC3;
            }
        }
        #endregion Properties, Fields

        #region Common
        private CyParameters(ICyInstQuery_v1 instQuery, ICyInstEdit_v1 instEdit)
        {
            m_instQuery = instQuery;
            m_instEdit = instEdit;

            m_ioComponentList = new List<string>();
            m_keyArray = new CyKeyArray(this);
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
    }

    public class CyKeyArray
    {
        CyParameters m_parameters;
        byte[] m_key;
        string m_keyStr;
        int m_keyLength;
        bool m_keyAvail;

        public CyKeyArray(CyParameters parameters)
        {
            m_parameters = parameters;
            m_keyStr = parameters.SecurityKey;
            m_keyLength = parameters.SecurityKeyLength;
            m_keyAvail = parameters.SecurityKeyAvail;
            m_key = new byte[m_keyLength];
        }

        public void SerializeKey()
        {
            StringBuilder keyWriter = new StringBuilder();
            for (int i = 0; i < m_keyLength; i++)
            {
                keyWriter.AppendFormat("0x{0:X2}u, ", m_key[i]);
            }
            string keyStr = keyWriter.ToString().TrimEnd(',', ' ');
            m_parameters.SecurityKey = keyStr;
        }

        public bool DeserializeKey()
        {
            string[] keyStrArr = m_keyStr.Split(' ', ',');
            int byteIndex = 0;
            Array.Clear(m_key, 0, m_keyLength);
            foreach (string keyStrPart in keyStrArr)
            {
                if (String.IsNullOrEmpty(keyStrPart))
                    continue;

                Byte byteVal;
                if (CyUtils.TryParseHexByte(keyStrPart, out byteVal))
                {
                    m_key[byteIndex++] = byteVal;
                    if (byteIndex >= m_keyLength)
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        public byte this[int index]
        {
            get
            {
                if ((index >= 0) && (index < m_keyLength))
                {
                    return m_key[index];
                }
                else
                {
                    return 0;
                }
            }
            set
            {
                if ((index >= 0) && (index < m_keyLength))
                {
                    m_key[index] = value;
                    SerializeKey();
                }
            }
        }

        public int Length
        {
            get { return m_key.Length; }
        }
    }
}
