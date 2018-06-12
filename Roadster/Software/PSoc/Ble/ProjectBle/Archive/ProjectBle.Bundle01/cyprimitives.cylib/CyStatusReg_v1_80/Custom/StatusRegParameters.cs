/*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/



using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;

namespace CyCustomizer.CyStatusReg_v1_80
{
    class StatusRegParameters
    {
        public CyCompDevParam NumInputs = null;
        public CyCompDevParam Bit0Mode = null;
        public CyCompDevParam Bit1Mode = null;
        public CyCompDevParam Bit2Mode = null;
        public CyCompDevParam Bit3Mode = null;
        public CyCompDevParam Bit4Mode = null;
        public CyCompDevParam Bit5Mode = null;
        public CyCompDevParam Bit6Mode = null;
        public CyCompDevParam Bit7Mode = null;
        public CyCompDevParam BusDisplay = null;
        public CyCompDevParam Interrupt = null;
        public CyCompDevParam MaskValue = null;

        public const string NUMINPUTS = "NumInputs";
        public const string BIT0MODE = "Bit0Mode";
        public const string BIT1MODE = "Bit1Mode";
        public const string BIT2MODE = "Bit2Mode";
        public const string BIT3MODE = "Bit3Mode";
        public const string BIT4MODE = "Bit4Mode";
        public const string BIT5MODE = "Bit5Mode";
        public const string BIT6MODE = "Bit6Mode";
        public const string BIT7MODE = "Bit7Mode";
        public const string BIT8MODE = "Bit8Mode";
        public const string BUS = "BusDisplay";
        public const string INTRR = "Interrupt";
        public const string MASKVALUE = "MaskValue";

        public StatusRegParameters(ICyInstEdit_v1 inst)
        {
            GetParams(inst);
        }

        private void GetParams(ICyInstEdit_v1 inst)
        {
            
            NumInputs  = inst.GetCommittedParam(NUMINPUTS);
            Bit0Mode = inst.GetCommittedParam(BIT0MODE);
            Bit1Mode = inst.GetCommittedParam(BIT1MODE);
            Bit2Mode = inst.GetCommittedParam(BIT2MODE);
            Bit3Mode = inst.GetCommittedParam(BIT3MODE);
            Bit4Mode = inst.GetCommittedParam(BIT4MODE);
            Bit5Mode = inst.GetCommittedParam(BIT5MODE);
            Bit6Mode = inst.GetCommittedParam(BIT6MODE);
            Bit7Mode = inst.GetCommittedParam(BIT7MODE);
            BusDisplay = inst.GetCommittedParam(BUS);
            Interrupt = inst.GetCommittedParam(INTRR);
            MaskValue = inst.GetCommittedParam(MASKVALUE);
        }

        private void SetParam(ICyInstEdit_v1 inst, string ParamName, string value)
        {

        }

        private void CommitParams(ICyInstEdit_v1 inst)
        {
            inst.CommitParamExprs();
        }
    }
}
