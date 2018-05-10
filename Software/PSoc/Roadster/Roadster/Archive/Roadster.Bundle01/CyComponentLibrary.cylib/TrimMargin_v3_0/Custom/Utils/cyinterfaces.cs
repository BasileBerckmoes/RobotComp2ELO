/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

namespace TrimMargin_v3_0
{
    internal interface ICyIntTable
    {
        void CreateTable(int count);
    }

    internal interface ICyTab
    {
        /// <summary>
        /// Canonical name of the tab.
        /// </summary>
        string TabName { get; }

        /// <summary>
        /// Updates GUI controls with the values from the parameters.
        /// </summary>
        void UpdateUI();
    }
}
