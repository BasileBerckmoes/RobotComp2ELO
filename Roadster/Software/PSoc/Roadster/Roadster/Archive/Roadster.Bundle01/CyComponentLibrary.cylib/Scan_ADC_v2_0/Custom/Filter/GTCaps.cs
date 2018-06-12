using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Scan_ADC_v2_0
{
    public class GTCaps
    {
        static private double m_precision = 0.000001;
        private int Count { get; set; }
        private List<double> m_caps;

        public GTCaps(GTCaps orig)
            : this(orig.m_caps)
        {
        }

        public GTCaps(List<double> caps)
            : this()
        {
            for (int index = 0; index < caps.Count; index++)
            {
                m_caps[index] = caps[index];
            }
        }

        public GTCaps()
        {
            Count = 10;
            m_caps = Enumerable.Repeat(0.0, Count).ToList();
        }

        private double this[int index]
        {
            get
            {
                return m_caps[index];
            }
            set
            {
                m_caps[index] = value;
            }
        }

        public double Gain
        {
            get { return m_caps[0]; }
            set { m_caps[0] = value; }
        }

        public double C1
        {
            get { return m_caps[1]; }
            set { m_caps[1] = value; }
        }

        public double C2
        {
            get { return m_caps[2]; }
            set { m_caps[2] = value; }
        }

        public double C3
        {
            get { return m_caps[3]; }
            set { m_caps[3] = value; }
        }

        public double C4
        {
            get { return m_caps[4]; }
            set { m_caps[4] = value; }
        }

        public double CA
        {
            get { return m_caps[5]; }
            set { m_caps[5] = value; }
        }

        public double CB
        {
            get { return m_caps[6]; }
            set { m_caps[6] = value; }
        }

        public double CP
        {
            get { return m_caps[7]; }
            set { m_caps[7] = value; }
        }

        public double CPP
        {
            get { return m_caps[8]; }
            set { m_caps[8] = value; }
        }

        public double CPPP
        {
            get { return m_caps[9]; }
            set { m_caps[9] = value; }
        }

        public List<double> XferCoeffsHighQ()
        {
            // From KVCP-335 page 2 equation [1]
            double num0 = this.CA * this.CPP;
            double num1 = this.C3 * (this.C1 + this.CP) - this.CA * (2 * this.CPP + this.CPPP);
            double num2 = this.CA * (this.CPP + this.CPPP) - this.C3 * this.CP;
            double den0 = this.CA * this.CB;
            double den1 = this.C3 * (this.C4 + this.C2) - 2 * this.CA * this.CB;
            double den2 = this.CA * this.CB - this.C3 * this.C4;

            num0 /= den0;
            num1 /= den0;
            num2 /= den0;
            den1 /= den0;
            den2 /= den0;

            return new List<double> { num0, num1, num2, den1, den2 };
        }

        public List<double> XferCoeffsLowQ()
        {
            // From KVCP BBC Basic procedure check_results_lq
            double cb4 = this.CB + this.C4;
            double num0 = (this.CP + this.CPP) / cb4;
            double num1 = this.C1 * this.C3 / this.CA / cb4 - (this.CP + 2 * this.CPP) / cb4;
            double num2 = this.CPP / cb4;
            double den1 = this.C2 * this.C3 / this.CA / cb4 - 1 - this.CB / cb4;
            double den2 = this.CB / cb4;

            return new List<double> { num0, num1, num2, den1, den2 };
        }

        public override string ToString()
        {
            StringBuilder builder = new StringBuilder();
            builder.Append("{ ");
            foreach (double val in m_caps)
            {
                builder.Append(val);
                builder.Append(" ");
            }
            builder.Append("}");
            return builder.ToString();
        }

        public override bool Equals(object obj)
        {
            bool result = false;
            if (obj is GTCaps)
            {
                result = Equals( (GTCaps) obj);
            }
            return result;
        }

        public override int GetHashCode()
        {
            return m_caps[0].GetHashCode();
        }

        public bool Equals(GTCaps rhs)
        {
            bool result = true;
            for (int index = 0; index < Count; index++)
            {
                if (Math.Abs(m_caps[index] - rhs[index]) > m_precision)
                {
                    result = false;
                    break;
                }
            }
            return result;
        }

        public static bool operator==(GTCaps lhs, GTCaps rhs)
        {
            // If both are null, or both are same instance, return true.
            if (System.Object.ReferenceEquals(lhs, rhs))
            {
                return true;
            }

            // If one is null, but not both, return false.
            if (((object)lhs == null) || ((object)rhs == null))
            {
                return false;
            }

            return lhs.Equals(rhs);
        }

        public static bool operator!=(GTCaps lhs, GTCaps rhs)
        {
            return !(lhs == rhs);
        }
    }
}
