using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Scan_ADC_v2_0
{
    /// <summary>
    /// This class maps biquad cascade sections to capacitor values.
    /// 
    /// The algorithm is adapted from KVCP-335's BBC Basic program
    /// for capacitor mapping.
    /// 
    /// For now, the BBC Basic code is left inline as comments.
    /// </summary>
    public class CapacitorMapper
    {
        //DIM coeff(125)
        //DIM realized(125)
        //REM this is the maximum function length Creator could provide
        const int m_coeff_limit = 125;
        List<double> coeff
            = new List<double>(Enumerable.Repeat<double>(0.0, m_coeff_limit));
        List<double> realized =
            new List<double>(Enumerable.Repeat<double>(0.0, m_coeff_limit));

        //DIM cname$(5)
        //cname$(1)="num0"
        //cname$(2)="num1"
        //cname$(3)="num2"
        //cname$(4)="den1"
        //cname$(5)="den2"
        List<string> cname = new List<string> { "num0", "num1", "num2", "den1", "den2" };

        //capindex%=10
        //DIM cap(25,capindex%)
        const int m_cap_limit = 10;
        List<GTCaps> cap = new List<GTCaps>();

        //DIM cmin(9),cmax(9),cstep(9)
        GTCaps cmin = new GTCaps();
        GTCaps cmax = new GTCaps();
        GTCaps cstep = new GTCaps();

        //dim lgain(25), hgain(25), mgain(25), Q(25), osr(25)
        //dim rlgain(25), rhgain(25), rmgain(25), rQ(25), rosr(25)

        List<double> lowq_lgain = new List<double>();
        List<double> lowq_hgain = new List<double>();
        List<double> lowq_mgain = new List<double>();
        List<double> lowq_Q = new List<double>();
        List<double> lowq_osr = new List<double>();
        List<double> lowq_rlgain = new List<double>();
        List<double> lowq_rhgain = new List<double>();
        List<double> lowq_rmgain = new List<double>();
        List<double> lowq_rQ = new List<double>();
        List<double> lowq_rosr = new List<double>();

        //fthresh=1E-2
        //fclose=1.05
        //gtol=0.89125 REM 1dB

        double fthresh = 1E-2;

        // These tweaks allow lower and higer values of c3,
        // which could cause poorer dynamic range
        //jambigc3%=FALSE
        //jamlimc3%=FALSE
        bool jambigc3 = false;
        bool jamlimc3 = false;

        // These tweaks widen the search range for ca and cb caps.
        // Could lead to noisier filters.
        //overridecb%=FALSE
        //overrideca%=FALSE
        bool overridecb = false;
        bool overrideca = false;

        //gain_all=1
        //REM extrac2=cmax(9)
        //extrac2=0
        //extrac1=0
        static double gain_all = 1;
        float extrac2 = 0;

        //gain_target=gain_all
        double gain_target = gain_all;

        int sects;
        double osr;

        public CapacitorMapper()
        {
        }

        //REM for r23 and beyond, get gain to work for the highpass and bp blin sections

        public List<GTCaps> MapCapacitorsHighQ(List<double> coefficients)
        {
            set_family_limits_high_q();

            coeff = new List<double>(coefficients);
            if (coeff.Count % 5 > 0)
            {
                throw new CapacitorMapperException(
                    "Internal error: filter coefficient count is not a multiple of 5"); //E009
            }
            sects = coeff.Count / 5;

            realized =
                new List<double>(Enumerable.Repeat<double>(0.0, coeff.Count));

            for (int section = 0; section < sects; section++)
            {
                cap.Add(new GTCaps());
            }

            osr = estimate_osr();

            for (int j = 0; j < sects; j++)
            {
                int num_type = assess_numerator(j);
                //Console.WriteLine("numerator type = " + num_type.ToString());

                if (num_type == 1)
                {
                    do_denominator(j);
                    bilinear_notch_highres_c1_r5(j);
                }
                else if (num_type == 2)
                {
                    do_denominator(j);
                    bilinear_bandpass(j);
                }
                else
                {
                    throw new CapacitorMapperException(
                        "Internal error: unsupported filter biquad numerator type"); //E010
                }

                gain_target /= cap[j].Gain;
                //REM still to do: check each section implementation gain and reloop if needed.
                check_denominator(j);
                check_numerator2(j);
            }

            return cap;
        }

        //procset_family_limits
        //mode 22

        //fthresh=1E-2
        //fclose=1.05
        //gtol = 0.988553 : rem -0.1 dB
        //f%=0  : rem 0 for PSoC 4 cap table

        //gain_all=1
        //file$=@dir$+file$+".coz"

        //c%=fncoz_file_open
        //if c% mod 5 > 0 print "coeff count isn't a multiple of 5" : end
        //sects%=c%/5

        //gain_target=gain_all

        //for j%=1 to sects%
        //cap(j%,0)=1 rem just to head off error while debugging, think this through
        //num_type%=fnassess_poly(j%)
        //print "numerator type= ";num_type%
  
        //do_lgain%=false
        //if num_type%=1 then
        //    procdo_denominator_lq(j%,6)
        //    procbilinear_notch_lq(j%)
    
        //endif
  
        //rem check this still allows gain
        //gain_target /= cap(j%,0)
        //proccheck_results_lq(j%)
  
        //next j%

        //procwrite_html
        //procwrite_clipboard

        //end

        public List<GTCaps> MapCapacitorsLowQ(List<double> coefficients)
        {
            set_family_limits_low_q();

            coeff = new List<double>(coefficients);
            if (coeff.Count % 5 > 0)
            {
                throw new CapacitorMapperException(
                    "Internal error: filter coefficient count is not a multiple of 5"); //E011
            }
            sects = coeff.Count / 5;

            realized =
                new List<double>(Enumerable.Repeat<double>(0.0, coeff.Count));

            var sect_count_zeros
                = new List<double>(Enumerable.Repeat<double>(0.0, sects));
            lowq_lgain = new List<double>(sect_count_zeros);
            lowq_hgain = new List<double>(sect_count_zeros);
            lowq_mgain = new List<double>(sect_count_zeros);
            lowq_Q = new List<double>(sect_count_zeros);
            lowq_osr = new List<double>(sect_count_zeros);
            lowq_rlgain = new List<double>(sect_count_zeros);
            lowq_rhgain = new List<double>(sect_count_zeros);
            lowq_rmgain = new List<double>(sect_count_zeros);
            lowq_rQ = new List<double>(sect_count_zeros);
            lowq_rosr = new List<double>(sect_count_zeros);

            for (int section = 0; section < sects; section++)
            {
                cap.Add(new GTCaps());
            }

            osr = estimate_osr();

            for (int j = 0; j < sects; j++)
            {
                int num_type = assess_poly_low_q(j);

                if (num_type == 1)
                {
                    do_denominator_lq(j);
                    bilinear_notch_lq(j);
                }

                // check this still allows gain
                gain_target /= cap[j].Gain;
                check_results_lq(j);
            }

            if (cap[0].C1 < cmin.C1 || cap[0].C1 > cmax.C1
                || cap[0].C2 < cmin.C2 || cap[0].C2 > cmax.C2
                || cap[0].C3 < cmin.C3 || cap[0].C3 > cmax.C3
                || cap[0].C4 < cmin.C4 || cap[0].C4 > cmax.C4
                || cap[0].CA < cmin.CA || cap[0].CA > cmax.CA
                || cap[0].CB < cmin.CB || cap[0].CB > cmax.CB
                || cap[0].CP < cmin.CP || cap[0].CP > cmax.CP
                || cap[0].CPP < cmin.CPP || cap[0].CPP > cmax.CPP
                || cap[0].CPPP < cmin.CPPP || cap[0].CPPP > cmax.CPPP)
                throw new CapacitorMapperException("Filter not realizable."); //E012
            return cap;
        }


        //END

        //REM -------------------------------------

        //DEFPROCsummary_print
        //FOR j%=1 TO sects%
        //PRINT '"section:   ";j%
        //PRINT "additional gain: ";cap(j%,0)
        //FOR k%=1 TO 4
        //    PRINT "c";k%;":   ";cap(j%,k%)
        //NEXT k%
        //PRINT "ca:   ";cap(j%,5)
        //PRINT "cb:   ";cap(j%,6)
        //PRINT "cp:   ";cap(j%,7)
        //PRINT "cpp:  ";cap(j%,8)
        //PRINT "cppp: ";cap(j%,9)
        //NEXT j%
        //ENDPROC

        public static void summary_print(List<GTCaps> my_caps)
        {
            for (int j = 0; j < my_caps.Count; j++)
            {
                Console.WriteLine("section:   " + j.ToString());
                Console.WriteLine("additional gain: " + my_caps[j].Gain.ToString());
                Console.WriteLine("c1:   " + my_caps[j].C1.ToString());
                Console.WriteLine("c2:   " + my_caps[j].C2.ToString());
                Console.WriteLine("c3:   " + my_caps[j].C3.ToString());
                Console.WriteLine("c4:   " + my_caps[j].C4.ToString());
                Console.WriteLine("ca:   " + my_caps[j].CA.ToString());
                Console.WriteLine("cb:   " + my_caps[j].CB.ToString());
                Console.WriteLine("cp:   " + my_caps[j].CP.ToString());
                Console.WriteLine("cpp:  " + my_caps[j].CPP.ToString());
                Console.WriteLine("cppp: " + my_caps[j].CPPP.ToString());
            }
        }

        //DEF FNgetc2_u(c)
        //REM changed for r27
        //REM PSoC1 can't do this
        //IF c>=1 =INT(0.5+c)
        //IF c>1/64 = INT(64*c+0.5)/64
        //=1/64

        private double getc2_u(double c)
        {
            // Changed for r27
            if (c >= 1.0)
            {
                return (int)(0.5 + c);
            }
            if (c > 1.0 / 64.0)
            {
                return (int)(64.0 * c + 0.5) / 64.0;
            }
            return 1.0 / 64.0;
        }

        //DEF FNgetcpp_u(c)
        //REM PSoC1 can't do this
        //IF c>=1 =INT(0.5+c)
        //IF c>1/64 = INT(64*c+0.5)/64
        //=1/64

        private double getcpp_u(double c)
        {
            if (c >= 1.0)
            {
                return (int)(0.5 + c);
            }
            if (c > 1.0 / 64.0)
            {
                return (int)(64.0 * c + 0.5) / 64.0;
            }
            return 1.0 / 64.0;
        }

        private static void StabilityTest(double den1, double den2)
        {
            //Triangle of stability test
            if (Math.Abs(den2) > 1 || Math.Abs(den1) > (1 + den2))
            {
                throw new CapacitorMapperException("Filter is unstable (failed triangle of stability test)"); //E013
            }
        }

        //DEFFNestimate_osr
        //minosr=1E6
        //FOR j%=1 TO sects%
        //offset%=5*(j%-1)
        //den1=coeff(4+offset%)
        //den2=coeff(5+offset%)
        //osr=PI/ATN(SQR((1+den1+den2)/(1-den1+den2)))
        //IF osr<minosr minosr=osr
        //NEXT j%
        //PRINT '"minosr= ";minosr
        //=minosr

        private double estimate_osr()
        {
            double minosr = 1E6;

            for (int j = 0; j < sects; j++)
            {
                int offset = 5 * j;
                double den1 = coeff[3 + offset];
                double den2 = coeff[4 + offset];

                StabilityTest(den1, den2);

                double osr = Math.PI / Math.Atan(Math.Sqrt(
                    (1 + den1 + den2) / (1 - den1 + den2)));
                if (osr < minosr)
                {
                    minosr = osr;
                }
            }

            //Console.WriteLine("minosr = " + minosr, ToString());
            //Console.WriteLine();

            return minosr;
        }


        //DEFFNfp_equal(a,b)
        //IF a=0 AND b=0 THEN =TRUE
        //IF b=0 THEN fcomp=ABS(a) ELSE fcomp=ABS(a/b-1)
        //IF fcomp<fthresh THEN =TRUE ELSE =FALSE

        private bool fp_equal(double a,double b)
        {
            if (a==0 && b==0)
            {
                return true;
            }
            double fcomp = (b == 0) ? Math.Abs(a) : Math.Abs(a / b - 1);
            if (fcomp < fthresh)
            {
                return true;
            }
            return false;
        }

        //DEFPROCdo_denominator(s%)
        //REM new test
        //offset%=5*(s%-1)
        //den1=coeff(4+offset%)
        //den2=coeff(5+offset%)
        //IF ABS(den2)<1E-9 PRINT "whoa! not ready for first order sections yet!" : j%+=1
        //factor=1-den2
        //minerr=1E6
        //bestc3=0 : bestc4=0 : bestca=0 : bestcb=0 : bestc2=0 : bestlimc3=0
        //IF overridecb%=TRUE THEN limcb=cstep(6) ELSE limcb=cmin(6)
        //IF overrideca%=TRUE THEN limca=cstep(5) ELSE limca=cmin(5)
        //
        //FOR cb=limcb TO cmax(6) STEP cstep(6)
        //limc3=INT(0.5+6*cb/osr): IF limc3<cmin(3) limc3=cmin(3) : IF limc3>cmax(3) limc3=cmax(3)
        //IF jamlimc3%=TRUE THEN limc3=cmin(3)
        //bigc3=2*limc3 : IF bigc3>cmax(3) bigc3=cmax(3)
        //IF jambigc3%=TRUE THEN bigc3=cmax(3)
        //
        //FOR ca=limca TO cmax(5) STEP cstep(5)
        //    product=ca*cb*factor
        //
        //    FOR c3=limc3 TO bigc3 STEP cstep(3)
        //    success%=FALSE
        //    c4=INT(0.5+product/c3)
        //    calcden2=1-c3*c4/ca/cb
        //    den2err = ABS( (1-calcden2)/(1-den2) - 1 )
        //    rawc2=(2+den1)*ca*cb/c3-c4
        //
        //    c2=FNgetc2_u(rawc2)
        //    IF c2<=cmax(2) THEN putbackc2=0  ELSE c2-=extrac2 : putbackc2=extrac2
        //    IF c2>cmax(2) THEN c2=cmax(2)
        //    REM calcden1=(c2+c4)*c3/ca/cb-2
        //    calcden1=(c2+putbackc2+c4)*c3/ca/cb-2
        //    den1err = ABS( (2+calcden1)/(2+den1) - 1 )
        //    IF c4<=cmax(4) AND c2<=cmax(2) THEN success%=TRUE
        //    REM if c4<=cmax(4) and c2<=cmax(2)+cmax(9) then success%=true
        //    IF den1err>den2err  worsterr=den1err ELSE worsterr=den2err
        //    IF worsterr<minerr AND success%=TRUE THEN minerr=worsterr : bestc3=c3 : bestc4=c4: bestca=ca: bestcb=cb : bestc2=c2+putbackc2 : bestlimc3=limc3
        //    NEXT c3
        //NEXT ca
        //NEXT cb
        //IF success%=FALSE PRINT "could not find a solution! ";c4;"  "c2 : END : REM this is rather brutal
        //
        //cap(s%,2)=bestc2 : cap(s%,3)=bestc3 : cap(s%,4)=bestc4 : cap(s%,5)=bestca : cap(s%,6)=bestcb
        //REM print "minerr=";minerr
        //ENDPROC

        private void do_denominator(int s)
        {
            // New test
            int offset = 5 * s;
            double den1 = coeff[3 + offset];
            double den2 = coeff[4 + offset];

            StabilityTest(den1, den2);

            bool success = false;
            double factor = 1 - den2;
            double minerr = 1E6;
            double bestc3 = 0;
            double bestc4 = 0;
            double bestca = 0;
            double bestcb = 0;
            double bestc2 = 0;

            double limca = (overrideca) ? cstep.CA : cmin.CA;
            double limcb = (overridecb) ? cstep.CB : cmin.CB;

            //FOR cb=limcb TO cmax(6) STEP cstep(6)
            for (double cb = limcb; cb < cmax.CB + cstep.CB / 2; cb += cstep.CB)
            {
                double limc3 = (jamlimc3) ? cmin.C3 : (int)(0.5 + 6 * cb / osr);
                limc3 = Math.Max(limc3, cmin.C3);
                limc3 = Math.Min(limc3, cmax.C3);

                double bigc3 = (jambigc3) ? cmax.C3 : 2 * limc3;
                bigc3 = Math.Min(bigc3, cmax.C3);

                //FOR ca=limca TO cmax(5) STEP cstep(5)
                for (double ca = limca; ca < cmax.CA + cstep.CA / 2; ca += cstep.CA)
                {
                    double product = ca * cb * factor;

                    // FOR c3=limc3 TO bigc3 STEP cstep(3)
                    for (double c3 = limc3; c3 < bigc3 + cstep.C3 / 2; c3 += cstep.C3)
                    {
                        bool validSolution = false;
                        int c4 = (int)(0.5 + product / c3);

                        double calcden2 = 1 - c3 * c4 / ca / cb;
                        double den2err = Math.Abs((1 - calcden2) / (1 - den2) - 1);

                        double rawc2 = (2 + den1) * ca * cb / c3 - c4;
                        double c2 = getc2_u(rawc2);
                        double putbackc2 = (c2 <= cmax.C2) ? 0 : extrac2;
                        c2 -= putbackc2;
                        c2 = Math.Min(c2, cmax.C2);

                        // Commented-out version: calcden1=(c2+c4)*c3/ca/cb-2
                        double calcden1 = (c2 + putbackc2 + c4) * c3 / ca / cb - 2;
                        double den1err = Math.Abs((2 + calcden1) / (2 + den1) - 1);

                        if (cmin.C4 <= c4 && c4 <= cmax.C4)
                        {
                            validSolution = true;
                        }

                        // Commented-out version: if c4<=cmax(4) and c2<=cmax(2)+cmax(9) then success%=true
                        double worsterr = Math.Max(den1err, den2err);
                        if (worsterr < minerr && validSolution)
                        {
                            success = true;
                            minerr = worsterr;
                            bestc3 = c3;
                            bestc4 = c4;
                            bestca = ca;
                            bestcb = cb;
                            bestc2 = c2 + putbackc2;
                        }
                    }
                }
            }

            if (success == false)
            {
                // This is rather brutal.
                throw new CapacitorMapperException(
                    "Internal error: could not map filter biquad to UAB capacitor values"); //E014
            }

            cap[s].C2 = bestc2;
            cap[s].C3 = bestc3;
            cap[s].C4 = bestc4;
            cap[s].CA = bestca;
            cap[s].CB = bestcb;
        }

        //DEFFNassess_numerator(s%)
        //REM 0 means unimplemented
        //offset%=5*(s%-1)
        //num0=coeff(1+offset%)
        //num1=coeff(2+offset%)
        //num2=coeff(3+offset%)
        //den1=coeff(4+offset%)
        //den2=coeff(5+offset%)
        //
        //REM case 1 is bilinear notch somewhere valid
        //IF ABS(num0)>1E-8 AND FNfp_equal(num0,num2) THEN =1
        //
        //REM case 2 is bilinear bandpass with positive num0 term
        //IF ABS(num1)<1E-8 AND FNfp_equal(num2,-num0) AND SGN(num0)>0 THEN =2
        //
        //REM unsupported numerator
        //=0
        //ENDPROC

        private int assess_numerator(int s)
        {
            // 0 means unimplemented

            int offset = 5 * s;
            double num0 = coeff[0 + offset];
            double num1 = coeff[1 + offset];
            double num2 = coeff[2 + offset];
            double den1 = coeff[3 + offset];
            double den2 = coeff[4 + offset];

            StabilityTest(den1, den2);

            // Case 1 is bilinear notch somewhere valid
            if (Math.Abs(num0) > 1E-8 && fp_equal(num0, num2))
            {
                return 1;
            }

            // Case 2 is bilinear bandpass with positive num0 term
            if (Math.Abs(num1) < 1E-8 && fp_equal(num2, -num0) && num0 > 0)
            {
                return 2;
            }

            // Unsupported numerator
            return 0;
        }

        //DEFPROCbilinear_notch_highres_c1(s%)
        //REM rewritten assuming highres c1 with same fn as cpp
        //cap(s%,10)=2
        //cap(s%,7)=0
        //cap(s%,9)=0
        //
        //offset%=5*(s%-1)
        //num0=coeff(1+offset%)
        //num1=coeff(2+offset%)
        //
        //actualcpp=num0*cap(s%,6)
        //cap(s%,8)=FNgetcpp_u(actualcpp)
        //
        // begin changed lines in bilinear_notch_highres_c1_r5
        //cap(s%,0)=cap(s%,8)/cap(s%,6)/num0
        //
        //actualc1=cap(s%,5)*cap(s%,6)/cap(s%,3)*(num1*cap(s%,0)+2*cap(s%,8)/cap(s%,6))
        // end changed lines in bilinear_notch_highres_c1_r5
        //
        //cap(s%,1)=FNgetcpp_u(actualc1)
        //ENDPROC

        private void bilinear_notch_highres_c1(int s)
        {
            //REM rewritten assuming highres c1 with same fn as cpp
            cap[s].CP = 0;
            cap[s].CPPP = 0;

            int offset = 5 * s;
            double num0 = coeff[0 + offset];
            double num1 = coeff[1 + offset];

            double actualcpp = num0 * cap[s].CB;
            cap[s].CPP = getcpp_u(actualcpp);
            cap[s].Gain = cap[s].CPP / cap[s].CB / num0;

            double actualc1 = cap[s].CA * cap[s].CB / cap[s].C3
                * (num1 * cap[s].Gain + 2 * cap[s].CPP / cap[s].CB);
            cap[s].C1 = getcpp_u(actualc1);
        }

        //defprocbilinear_notch_highres_c1_r5(s%)
        //cap(s%,10)=2
        //cap(s%,7)=0
        //cap(s%,9)=0
        //
        //offset%=5*(s%-1)
        //num0=coeff(1+offset%)
        //num1=coeff(2+offset%)
        //
        //actualcpp=num0*cap(s%,6)
        //cap(s%,8)=fngetcpp_u(actualcpp)
        //
        //rem begin changed lines from bilinear_notch_highres_c1
        //cap(s%,0)=1
        //num2=coeff(3+offset%)
        //den1=coeff(4+offset%)
        //den2=coeff(5+offset%)
        //sgain = abs((num0+num1+num2)/(1+den1+den2))
        //actualc1 = cap(s%,2)*sgain
        //rem end changed lines from bilinear_notch_highres_c1
        //
        //cap(s%,1)=fngetcpp_u(actualc1)
        //endproc

        private void bilinear_notch_highres_c1_r5(int s)
        {
            //REM rewritten assuming highres c1 with same fn as cpp
            cap[s].CP = 0;
            cap[s].CPPP = 0;

            int offset = 5 * s;
            double num0 = coeff[0 + offset];
            double num1 = coeff[1 + offset];

            double actualcpp = num0 * cap[s].CB;
            cap[s].CPP = getcpp_u(actualcpp);

            // begin changed lines from bilinear_notch_highres_c1
            cap[s].Gain = 1;

            double num2 = coeff[2 + offset];
            double den1 = coeff[3 + offset];
            double den2 = coeff[4 + offset];
            double sgain = Math.Abs((num0 + num1 + num2) / (1 + den1 + den2));
            double actualc1 = cap[s].C2 * sgain;
            // end changed lines from bilinear_notch_highres_c1

            cap[s].C1 = getcpp_u(actualc1);
        }

        //DEFPROCbilinear_bandpass(s%)
        //REM current value of gain_target how much to change the section gain
        //REM added amplifier output statement in r19 with value in cap(s%,10)
        //REM this works the same with highres c1
        //cap(s%,10)=2
        //
        //offset%=5*(s%-1)
        //num0=coeff(1+offset%)
        //
        //cap(s%,1)=0
        //cap(s%,9)=0
        //actualcpp=num0*cap(s%,6)
        //cpp=FNgetcpp_u(actualcpp)
        //IF cpp>cmax(8) THEN PRINT "can't do this bilinear bandpass function" : ENDPROC
        //cap(s%,8)=cpp
        //cap(s%,0)=cap(s%,8)/actualcpp
        //actualcp=2*cap(s%,5)*cap(s%,8)/cap(s%,3)
        //IF actualcp>cmax(7)+cmax(9) PRINT "can't do this!" : END
        //cap(s%,7)=INT(0.5+actualcp)
        //ENDPROC

        private void bilinear_bandpass(int s)
        {
            // Current value of gain_target how much to change the section gain
            // Added amplifier output statement in r19 with value in cap(s%,10)
            // This works the same with highres c1

            int offset = 5 * s;
            double num0 = coeff[0 + offset];

            cap[s].C1 = 0;
            cap[s].CPPP = 0;
            double actualcpp = num0 * cap[s].CB;
            double cpp = getcpp_u(actualcpp);
            if (cpp > cmax.CPP)
            {
                throw new CapacitorMapperException(
                    "Internal error: filter bilinear bandpass capacitor values out of range"); //E015
            }
            cap[s].CPP = cpp;
            cap[s].Gain = cap[s].CPP / actualcpp;
            double actualcp = 2 * cap[s].CA * cap[s].CPP / cap[s].C3;
            if (actualcp > cmax.CP + cmax.CPP)
            {
                throw new CapacitorMapperException(
                    "Internal error: filter capacitor mapping overflow"); //E016
            }
            cap[s].CP = (int)(0.5 + actualcp);
        }

        //DEFPROCcheck_denominator(s%)
        //offset%=5*(s%-1)
        //REM realized(1...5 plus offset%)
        //realized(4+offset%) = cap(s%,3)*(cap(s%,2)+cap(s%,4))/cap(s%,5)/cap(s%,6)-2
        //realized(5+offset%) = 1-cap(s%,3)*cap(s%,4)/cap(s%,5)/cap(s%,6)
        //ENDPROC

        private void check_denominator(int s)
        {
            int offset = 5 * s;
            realized[3 + offset] = cap[s].C3 
                * (cap[s].C2 + cap[s].C4) / cap[s].CA / cap[s].CB - 2;
            realized[4 + offset] 
                = 1 - cap[s].C3 * cap[s].C4 / cap[s].CA / cap[s].CB;
        }

        //DEFPROCcheck_numerator2(s%)
        //offset%=5*(s%-1)
        //realized(1+offset%) = cap(s%,8)/cap(s%,6)
        //realized(2+offset%) = cap(s%,3)*(cap(s%,1)+cap(s%,7))/cap(s%,5)/cap(s%,6)-(2*cap(s%,8)+cap(s%,9))/cap(s%,6)
        //realized(3+offset%) = (cap(s%,8)+cap(s%,9))/cap(s%,6)-cap(s%,3)*cap(s%,7)/cap(s%,5)/cap(s%,6)
        //ENDPROC

        private void check_numerator2(int s)
        {
            int offset = 5 * s;
            realized[0 + offset] = cap[s].CPP / cap[s].CB;
            realized[1 + offset]
                = cap[s].C3 * (cap[s].C1 + cap[s].CP) / cap[s].CA / cap[s].CB
                - (2 * cap[s].CPP + cap[s].CPPP) / cap[s].CB;
            realized[2 + offset] =
                (cap[s].CPP + cap[s].CPPP) / cap[s].CB 
                - cap[s].C3 * cap[s].CP / cap[s].CA / cap[s].CB;
        }

        //deffnassess_poly(s%)
        //rem 0 means unimplemented
        //offset%=5*(s%-1)
        //num0=coeff(1+offset%)
        //num1=coeff(2+offset%)
        //num2=coeff(3+offset%)
        //den1=coeff(4+offset%)
        //den2=coeff(5+offset%)
        //lgain(s%) = abs((num0+num1+num2)/(1+den1+den2))
        //hgain(s%) = abs((num0-num1+num2)/(1-den1+den2))
        //Q(s%) = sqr((1-den1+den2)*(1+den1+den2)) /2/(1-den2)
        //osr(s%) = pi/atn(sqr((1+den1+den2)/(1-den1+den2)))

        //if lgain(s%)>hgain(s%) then mgain(s%)=lgain(s%) else mgain(s%)=hgain(s%)
        //rem case 1 is bilinear notch somewhere valid
        //if abs(num0)>1E-8 and fnfp_equal(num0,num2) then =1

        //rem case -1 is when there's an inversion
        //if abs(num0)<-1E-8 and fnfp_equal(num0,num2) then =-1

        //rem case 2 is bilinear bandpass with positive num0 term
        //if abs(num1)<1E-8 and fnfp_equal(num2,-num0) and sgn(num0)>0 then =2

        //rem case -2 is bilinear bandpass with negative num0 term
        //if abs(num1)<1E-8 and fnfp_equal(num2,-num0) and sgn(num0)<0 then =-2

        //rem case 3 is single input BP with lower order num term positive
        //if (abs(num0)<1E-8 and fnfp_equal(num1,-num2) and sgn(num0)>0) or (abs(num2)<1E-8 and fnfp_equal(num0,-num1) and sgn(num0)>0) then =3

        //rem case -3 is single input BP with lower order num term negative
        //if (abs(num0)<1E-8 and fnfp_equal(num1,-num2) and sgn(num0)<0) or (abs(num2)<1E-8 and fnfp_equal(num0,-num1) and sgn(num0)<0) then =-3

        //rem case 4 is simple pole with only num1 non-zero and positive
        //if fnfp_equal(num0/num1,0) and fnfp_equal(num2/num1,0)and sgn(num1)>0 then =4

        //rem case -4 is simple pole with only num1 non-zero and negative
        //if fnfp_equal(num0/num1,0) and fnfp_equal(num2/num1,0)and sgn(num1)<0 then =-4
        //=0

        private int assess_poly_low_q(int s)
        {
            int offset = 5 * s;
            double num0 = coeff[0 + offset];
            double num1 = coeff[1 + offset];
            double num2 = coeff[2 + offset];
            double den1 = coeff[3 + offset];
            double den2 = coeff[4 + offset];

            lowq_lgain[s] = Math.Abs((num0 + num1 + num2) / (1 + den1 + den2));
            lowq_hgain[s] = Math.Abs((num0 - num1 + num2) / (1 - den1 + den2));
            lowq_Q[s] = Math.Sqrt((1 - den1 + den2) * (1 + den1 + den2)) / 2 / (1 - den2);
            lowq_osr[s] = Math.PI / Math.Atan(Math.Sqrt((1 + den1 + den2) / (1 - den1 + den2)));

            if (lowq_lgain[s] > lowq_hgain[s])
            {
                lowq_mgain[s] = lowq_lgain[s];
            }
            else
            {
                lowq_mgain[s] = lowq_hgain[s];
            }

            // case 1 is bilinear notch somewhere valid
            if ((Math.Abs(num0) > 1E-8) && fp_equal(num0, num2))
            {
                return 1;
            }

            return 0;
        }

      //defprocdo_denominator_lq(s%, c3factor)
      //offset%=5*(s%-1)
      //den1=coeff(4+offset%)
      //den2=coeff(5+offset%)
      //num2=coeff(3+offset%) rem added to ver 1.4
      //c46 = cmax(f%,8)/num2 rem added to ver 1.4

      //if abs(den2)>1 print "no solution - |den2| too big!" : end
      //if abs(den1) > 1+den2 print "no solution - |den1| outside valid range for given den2" : end
      //if abs(den2)<1E-9 print "whoa! not ready for first order sections yet!"
      //minerr=1E6
      //bestc3=0 : bestca=0 : bestc2=0

      //rem loop to get CB and C4
      //mina2err=1E6
      //bestc4=0 : bestcb=0
      //for cb=cmax(f%,6) to cmin(f%,6) step -cstep(f%,6)
      //  c4 = int(0.5+cb*(1-den2)/den2)
      //  if c4>cmax(f%,4) then c4=cmax(f%,4)
      //  if c4<cmin(f%,4) then c4=cmin(f%,4)
      //  calca2 = cb/(cb+c4)
      //  a2err=abs(1-calca2/den2)
      //  if a2err<mina2err and c4+cb <= c46 then mina2err=a2err : bestc4=c4 : bestcb = cb rem added to ver 1.4
      //  removed from ver 1.4 if a2err<mina2err then mina2err=a2err : bestc4=c4 : bestcb = cb
      //next cb

      //cap(s%,4)=bestc4
      //cap(s%,6)=bestcb
      //print "c4: ";cap(s%,4)
      //print "cb: ";cap(s%,6)
      //removed from ver 1.4 this just double-checks we didn't miss a larger set
      //removed from ver 1.4  scalec4 = int(cmax(f%,4)/bestc4)
      //removed from ver 1.4 scalecb = int(cmax(f%,6)/bestcb)
      //removed from ver 1.4 if scalec4<scalecb then minscale=scalec4 else minscale=scalecb
      //removed from ver 1.4 cap(s%,4)=bestc4 * minscale
      //removed from ver 1.4 cap(s%,6)=bestcb * minscale

      //rem k is the  factor we use to calc c2 and c5
      //k = den1*(cap(s%,6)+cap(s%,4))+2*cap(s%,6)+cap(s%,4)

      //cap(s%,3) = int(0.5 + cap(s%,4) * Q(s%))
      //rem make sure we clamp DC gain if Q<1
      //if cap(s%,3)<cap(s%,4) cap(s%,3) = cap(s%,4)

      //cap(s%,2) = fngetc2_u( int( cmax(f%,2)/mgain(s%) ) )
      //rem c2 can't be bigger than this if there's gain
      //rem check this works OK for highpass - rules may be different

      //rem set c3, step c2 down
      //cap(s%,2) += cstep(f%,2) rem added to ver 1.4

      //done%=false
      //while done%=false
      //  cap(s%,2) -= cstep(f%,2)
      //  cap(s%,5) = int(0.5+cap(s%,2)*cap(s%,3)/k)
      //  if cap(s%,5) <= cmax(f%,5) or cap(s%,2)<=cmin(f%,2) then done%=true
      //endwhile

      //print "c2= ";cap(s%,2)
      //print "c3= ";cap(s%,3)
      //print "ca= ";cap(s%,5)

      //if done%=false then print "denominator fail" : end
      //rem brute force looping not done here
      //endproc

        void do_denominator_lq(int s)
        {
            int offset = 5 * s;
            double den1 = coeff[3 + offset];
            double den2 = coeff[4 + offset];
            double num2 = coeff[2 + offset];
            double c46 = cmax.CPP / num2;

            if (Math.Abs(den2) > 1)
            {
                throw new CapacitorMapperException(
                    "Internal error: no solution - |den2| too big!"); //E017
            }
            if (Math.Abs(den1) > 1 + den2)
            {
                throw new CapacitorMapperException(
                    "Internal error: no solution - |den1| outside valid range for given den2"); //E018
            }

            // loop to get CB and C4
            double mina2err = 1E6;
            double bestc4 = 0;
            double bestcb = 0;

            // for cb=cmax(f%,6) to cmin(f%,6) step -cstep(f%,6)
            for (double cb = cmax.CB; cb > cmin.CB - cstep.CB / 2; cb -= cstep.CB)
            {
                double c4 = (int)(0.5 + cb * (1 - den2) / den2);

                // New and changed lines from CDT 245005 and CDT 245011
                // Mapped Capacitor C3 is larger than the maximum allowed value
                double limc4 = (int)(cmax.C4 / lowq_Q[s]);
                if (c4 > limc4)
                {
                    c4 = limc4;
                }
                if (c4 > cmax.C4)
                {
                    c4 = cmax.C4;
                }
                if (c4 < cmin.C4)
                {
                    c4 = cmin.C4;
                }

                double calca2 = cb / (cb + c4);
                double a2err = Math.Abs(1 - calca2 / den2);
                if ((a2err < mina2err)
                 && (c4 + cb <= c46))
                {
                    mina2err = a2err;
                    bestc4 = c4;
                    bestcb = cb;
                }
            }
            //cap(s%,4)=bestc4
            //cap(s%,6)=bestcb
            //print "c4: ";cap(s%,4)
            //print "cb: ";cap(s%,6)
            cap[s].C4 = bestc4;
            cap[s].CB = bestcb;
            // this just double-checks we didn't miss a larger set
            //int scalec4 = (int)(cmax.C4 / bestc4);
            //int scalecb = (int)(cmax.CB / bestcb);
            //int minscale;
            //if (scalec4 < scalecb)
            //{
            //    minscale = scalec4;
            //}
            //else
            //{
            //    minscale = scalecb;
            //}
            //cap[s].C4 = bestc4 * minscale;
            //cap[s].CB = bestcb * minscale;

            // k is the  factor we use to calc c2 and c5
            double k = den1 * (cap[s].CB + cap[s].C4) + 2 * cap[s].CB + cap[s].C4;

            cap[s].C3 = (int)(0.5 + cap[s].C4 * lowq_Q[s]);
            // make sure we clamp DC gain if Q<1
            if (cap[s].C3 < cap[s].C4)
            {
                cap[s].C3 = cap[s].C4;
            }

            cap[s].C2 = getc2_u((int)(cmax.C2 / lowq_mgain[s]));
            // c2 can't be bigger than this if there's gain
            // check this works OK for highpass - rules may be different

            // set c3, step c2 down
            cap[s].C2 += cstep.C2;
            bool done = false;
            while (done == false)
            {
                cap[s].C2 -= cstep.C2;
                cap[s].CA = (int)(0.5 + cap[s].C2 * cap[s].C3 / k);
                if ((cap[s].CA <= cmax.CA) || (cap[s].C2 <= cmin.C2))
                {
                    done = true;
                }
            }
        }

      //defprocbilinear_notch_lq(s%)
      //offset%=5*(s%-1)
      //num2=coeff(3+offset%)
      //cap(s%,7)=0
      //cap(s%,9)=0
      //cap(s%,10)=2

      //cap(s%,8)=fngetcpp_u(num2*(cap(s%,4)+cap(s%,6)))
      //print "cpp: ";cap(s%,8)
      //cap(s%,1) = fngetc2_u(cap(s%,2) * lgain(s%))
      //print "c1= ";cap(s%,1)
      //endproc

        void bilinear_notch_lq(int s)
        {
            int offset = 5 * s; ;
            double num2 = coeff[2 + offset];

            cap[s].CP = 0;
            cap[s].CPPP = 0;

            cap[s].CPP = getcpp_u(num2 * (cap[s].C4 + cap[s].CB));
            cap[s].C1 = getc2_u(cap[s].C2 * lowq_lgain[s]);
        }

        //defproccheck_results_lq(s%)
        //offset%=5*(s%-1)
        //cb4=cap(s%,6)+cap(s%,4)
        //realized(1+offset%) = (cap(s%,7)+cap(s%,8)) / cb4
        //realized(2+offset%) = cap(s%,1)*cap(s%,3)/cap(s%,5)/cb4 - (cap(s%,7)+2*cap(s%,8))/cb4
        //realized(3+offset%) = cap(s%,8)/cb4
        //realized(4+offset%) =  cap(s%,2)*cap(s%,3)/cap(s%,5)/cb4 - 1 -cap(s%,6)/cb4
        //realized(5+offset%) = cap(s%,6)/cb4
        //rnum0=realized(1+offset%)
        //rnum1=realized(2+offset%)
        //rnum2=realized(3+offset%)
        //rden1=realized(4+offset%)
        //rden2=realized(5+offset%)
        //rlgain(s%) = abs((rnum0+rnum1+rnum2)/(1+rden1+rden2))
        //rhgain(s%) = abs((rnum0-rnum1+rnum2)/(1-rden1+rden2))
        //rQ(s%) = sqr((1-rden1+rden2)*(1+rden1+rden2)) /2/(1-rden2)
        //rosr(s%) = pi/atn(sqr((1+rden1+rden2)/(1-rden1+rden2)))
        //endproc

        void check_results_lq(int s)
        {
            int offset = 5 * s;
            double cb4 = cap[s].CB + cap[s].C4;
            realized[0 + offset] = (cap[s].CP + cap[s].CPP) / cb4;
            realized[1 + offset] = cap[s].C1 * cap[s].C3 / cap[s].CA / cb4 - (cap[s].CP + 2 * cap[s].CPP) / cb4;
            realized[2 + offset] = cap[s].CPP / cb4;
            realized[3 + offset] = cap[s].C2 * cap[s].C3 / cap[s].CA / cb4 - 1 - cap[s].CB / cb4;
            realized[4 + offset] = cap[s].CB / cb4;
            double rnum0 = realized[0 + offset];
            double rnum1 = realized[1 + offset];
            double rnum2 = realized[2 + offset];
            double rden1 = realized[3 + offset];
            double rden2 = realized[4 + offset];
            lowq_rlgain[s] = Math.Abs((rnum0 + rnum1 + rnum2) / (1 + rden1 + rden2));
            lowq_rhgain[s] = Math.Abs((rnum0 - rnum1 + rnum2) / (1 - rden1 + rden2));
            lowq_rQ[s] = Math.Sqrt((1 - rden1 + rden2) * (1 + rden1 + rden2)) / 2 / (1 - rden2);
            lowq_rosr[s] = Math.PI / Math.Atan(Math.Sqrt((1 + rden1 + rden2) / (1 - rden1 + rden2)));
        }

        //DEFPROCset_family_limits
        //REM PSoC 4 -----------------------------------
        //i%=1
        //cmin(i%)=1
        //cmax(i%)=63
        //cstep(i%)=1
        //i%=2
        //cmin(i%)=0
        //cmax(i%)=63
        //cstep(i%)=0
        //i%=3
        //cmin(i%)=1
        //cmax(i%)=63
        //cstep(i%)=1
        //i%=4
        //cmin(i%)=1
        //cmax(i%)=63
        //cstep(i%)=1
        //i%=5
        //cmin(i%)=40
        //cmax(i%)=64
        //cstep(i%)=4
        //i%=6
        //cmin(i%)=40
        //cmax(i%)=64
        //cstep(i%)=4
        //i%=7
        //cmin(i%)=0
        //cmax(i%)=63
        //cstep(i%)=1
        //i%=8
        //cmin(i%)=0
        //cmax(i%)=63
        //cstep(i%)=0
        //i%=9
        //cmin(i%)=0
        //cmax(i%)=63
        //cstep(i%)=1
        //REM end of PSoC 4 ------------------------------------
        //ENDPROC

        /// <summary>
        /// Set PSoC4 family High Q filter capacitor limits.
        /// </summary>
        private void set_family_limits_high_q()
        {
            cmin.Gain = 1;
            cmax.Gain = 6;
            cstep.Gain = 1;

            cmin.C1 = 1;
            cmax.C1 = 63;
            cstep.C1 = 1;

            cmin.C2 = 0;
            cmax.C2 = 63;
            cstep.C2 = 0;

            cmin.C3 = 1;
            cmax.C3 = 63;
            cstep.C3 = 1;

            cmin.C4 = 1;
            cmax.C4 = 63;
            cstep.C4 = 1;

            cmin.CA = 40;
            cmax.CA = 64;
            cstep.CA = 2;

            cmin.CB = 40;
            cmax.CB = 64;
            cstep.CB = 2;

            cmin.CP = 0;
            cmax.CP = 63;
            cstep.CP = 1;

            cmin.CPP = 0;
            cmax.CPP = 63;
            cstep.CPP = 0;

            cmin.CPPP = 0;
            cmax.CPPP = 63;
            cstep.CPPP = 1;
        }

          //defprocset_family_limits
          //rem PSoC 4 updated 4/12/16 -----------------------------------
          //family%=0
          //i%=1
          //cmin(family%,i%)=0
          //cmax(family%,i%)=63
          //cstep(family%,i%)=1
          //i%=2
          //cmin(family%,i%)=0
          //cmax(family%,i%)=64
          //cstep(family%,i%)=1
          //i%=3
          //cmin(family%,i%)=1
          //cmax(family%,i%)=63
          //cstep(family%,i%)=1
          //i%=4
          //cmin(family%,i%)=1
          //cmax(family%,i%)=63
          //cstep(family%,i%)=1
          //i%=5 rem adding 63 from a CC
          //cmin(family%,i%)=2
          //cmax(family%,i%)=127
          //cstep(family%,i%)=1
          //i%=6
          //cmin(family%,i%)=2
          //cmax(family%,i%)=64
          //cstep(family%,i%)=2
          //i%=7
          //cmin(family%,i%)=0
          //cmax(family%,i%)=63
          //cstep(family%,i%)=1
          //i%=8
          //cmin(family%,i%)=0
          //cmax(family%,i%)=64
          //cstep(family%,i%)=1
          //i%=9
          //cmin(family%,i%)=0
          //cmax(family%,i%)=63
          //cstep(family%,i%)=1
          //rem end of PSoC 4 ------------------------------------
          //endproc

        /// <summary>
        /// Set PSoC4 family Low Q filter capacitor limits.
        /// </summary>
        private void set_family_limits_low_q()
        {
            cmin.Gain = 1;
            cmax.Gain = 6;
            cstep.Gain = 1;

            //Minimums are algorithmic minimums
            //Maximums and steps are physical limits

            //C1 is CB0
            cmin.C1 = 0;
            cmax.C1 = 64; 
            cstep.C1 = 1;

            //C2 is CC0
            cmin.C2 = 0;
            cmax.C2 = 63;
            cstep.C2 = 1;

            //C3 is CB1
            cmin.C3 = 1;
            cmax.C3 = 64;
            cstep.C3 = 1;

            //C4 is CA1
            cmin.C4 = 1;
            cmax.C4 = 63;
            cstep.C4 = 1;

            // CA is CF0 + CA0
            cmin.CA = 2;
            cmax.CA = 127;
            cstep.CA = 1;

            //CB is CF1
            cmin.CB = 2;
            cmax.CB = 64;
            cstep.CB = 2;

            //CP is CB0
            cmin.CP = 0;
            cmax.CP = 64;
            cstep.CP = 1;

            //Cpp is CC1
            cmin.CPP = 0;
            cmax.CPP = 63;
            cstep.CPP = 1;

            //Cppp is unused
            cmin.CPPP = 0;
            cmax.CPPP = 63;
            cstep.CPPP = 1;
        }
    }
}
