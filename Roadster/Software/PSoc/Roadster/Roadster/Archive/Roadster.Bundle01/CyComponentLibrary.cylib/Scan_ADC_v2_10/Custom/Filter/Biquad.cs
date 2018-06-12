using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;

namespace Scan_ADC_v2_10
{
    /// <summary>
    /// Stores Biquadratic transfer function coefficients.
    /// 
    /// The biquad can be converted from powers of z to powers of 1/z
    /// and vice versa using the Reverse method.  This class does not
    /// keep track whether powers of z or 1/z are used.
    /// </summary>
    public class Biquad
    {
        public double Num0 { get; set; }
        public double Num1 { get; set; }
        public double Num2 { get; set; }
        public double Den0 { get; set; }
        public double Den1 { get; set; }
        public double Den2 { get; set; }

        public Biquad(double num0, double num1, double num2, double den0, double den1, double den2)
        {
            this.Num0 = num0;
            this.Num1 = num1;
            this.Num2 = num2;
            this.Den0 = den0;
            this.Den1 = den1;
            this.Den2 = den2;
        }

        /// <summary>
        /// Biquad copy constructor.
        /// </summary>
        /// <param name="original">Original Biquad for copy</param>
        public Biquad(Biquad original)
        {
            this.Num0 = original.Num0;
            this.Num1 = original.Num1;
            this.Num2 = original.Num2;
            this.Den0 = original.Den0;
            this.Den1 = original.Den1;
            this.Den2 = original.Den2;
        }

        /// <summary>
        /// Default constructor.  All coefficients are zero.
        /// </summary>
        public Biquad()
        {
        }

        /// <summary>
        /// Normalize a biquad in z so that the denominator square coefficient is 1.
        /// 
        /// Reversing a normalized biquad will make the denominator constant
        /// coefficient 1.
        /// </summary>
        public void Normalize()
        {
            this.Num0 /= this.Den2;
            this.Num1 /= this.Den2;
            this.Num2 /= this.Den2;
            this.Den0 /= this.Den2;
            this.Den1 /= this.Den2;
            this.Den2 = 1.0;
        }

        /// Reverse a biquad's coefficients.
        /// 
        /// This converts a biquad in z to one in 1/z and vice versa.
        /// </summary>
        public void Reverse()
        {
            double numSwap = this.Num2;
            this.Num2 = this.Num0;
            this.Num0 = numSwap;

            double denSwap = this.Den2;
            this.Den2 = this.Den0;
            this.Den0 = denSwap;
        }

        /// <summary>
        /// Calculate biquad value for complex z.
        /// </summary>
        /// <param name="z">Input parameter z</param>
        /// <returns></returns>
        public Complex EvaluateZ(Complex z)
        {
            Complex num = this.Num0 + this.Num1 * z + this.Num2 * z * z;
            Complex den = this.Den0 + this.Den1 * z + this.Den2 * z * z;
            Complex val = num / den;

            return val;
        }

        /// <summary>
        /// Produce textual description of a biquad.
        /// 
        /// Lists numerator square coefficient first, denominator constant
        /// coefficient last.
        /// </summary>
        /// <returns>Text description</returns>
        public override string ToString()
        {
            string text = String.Format(
                "Num2 = {0}\r\nNum1 = {1}\r\nNum0 = {2}\r\n"
                + "Den2 = {3}\r\nDen1 = {4}\r\nDen0 = {5}\r\n",
                this.Num2, this.Num1, this.Num0,
                this.Den2, this.Den1, this.Den0);

            return text;
        }
    }
}
