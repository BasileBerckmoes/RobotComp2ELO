using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace Scan_ADC_v2_0
{
    /// <summary>
    /// Capacitor mapping exception class.
    /// </summary>
    [Serializable]
    public class CapacitorMapperException : System.Exception, ISerializable
    {
        public CapacitorMapperException() :
            base()
        {
        }

        public CapacitorMapperException(string message) :
            base(message)
        {
        }

        protected CapacitorMapperException(SerializationInfo info, StreamingContext context) :
            base(info, context)
        {
        }
    }
}
