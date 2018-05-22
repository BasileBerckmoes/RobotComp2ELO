/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Diagnostics;

namespace TrimMargin_v3_0.Utils
{
    [DebuggerDisplay("MajorVersion = {MajorVersion}, MinorVersion = {MinorVersion}, IsValid = {IsValid}")]
    internal class CyComponentVersion : IComparable<CyComponentVersion>, IEquatable<CyComponentVersion>
    {
        #region Constructor(s)
        public CyComponentVersion(int majorVersion, int minorVersion)
        {
            MajorVersion = majorVersion;
            MinorVersion = minorVersion;
            IsValid = true;
        }

        public CyComponentVersion(string versionStr)
        {
            IsValid = false;
            if (versionStr.Length >= 3)
            {
                string[] numbers = versionStr.Split('_');
                if (numbers.Length == 2)
                {
                    int major, minor;
                    if (Int32.TryParse(numbers[0], out major) && Int32.TryParse(numbers[1], out minor))
                    {
                        MajorVersion = major;
                        MinorVersion = minor;
                        IsValid = true;
                    }
                }
            }
        }
        #endregion

        #region Properties
        public int MajorVersion { get; private set; }
        public int MinorVersion { get; private set; }
        public bool IsValid { get; private set; }
        #endregion

        #region Interfaces implementation
        public int CompareTo(CyComponentVersion other)
        {
            const int LESS = -1;
            const int EQUAL = 0;
            const int GREATER = 1;

            if (MajorVersion == other.MajorVersion && MinorVersion == other.MinorVersion)
            {
                return EQUAL;
            }
            if (MajorVersion > other.MajorVersion ||
                (MajorVersion == other.MajorVersion && MinorVersion > other.MinorVersion))
            {
                return GREATER;
            }
            return LESS;
        }

        public bool Equals(CyComponentVersion other)
        {
            return CompareTo(other) == 0;
        }
        #endregion

        #region Overrides
        public override bool Equals(object obj)
        {
            CyComponentVersion other = obj as CyComponentVersion;
            return (other == null) ? false : this.Equals(other);
        }

        public override int GetHashCode()
        {
            unchecked
            {
                int hash = 17;
                hash = hash * 23 + MajorVersion.GetHashCode();
                hash = hash * 23 + MinorVersion.GetHashCode();
                return hash;
            }
        }
        #endregion
    }
}