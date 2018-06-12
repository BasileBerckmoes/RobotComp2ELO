/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;

namespace TrimMargin_v3_0.Utils
{
    internal static class CyErrors
    {
        public static string GetImplementationError(CyParameters parameters)
        {
            string message = String.Empty;
            if (!parameters.UdbBlockExists && parameters.PwmImplementation == CyEImplementation.UDB)
            {
                message = String.Format(Resources.ImplementationNotSupported,
                    CyEnumExtensions.ToDisplayName(CyEImplementation.UDB), 
                    CyEnumExtensions.ToDisplayName(CyEImplementation.FixedFunction));
            }
            else if (!parameters.TcpwmBlockExists && parameters.PwmImplementation == CyEImplementation.FixedFunction)
            {
                message = String.Format(Resources.ImplementationNotSupported,
                    CyEnumExtensions.ToDisplayName(CyEImplementation.FixedFunction), 
                    CyEnumExtensions.ToDisplayName(CyEImplementation.UDB));
            }
            return message;
        }
    }
}