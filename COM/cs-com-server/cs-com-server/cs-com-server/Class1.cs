using System;
using System.Runtime.InteropServices;

namespace cs_com_server
{
    [ComVisible(true)]
    [Guid("73258AA8-B977-4929-8B2B-2D01C5BFE7FF")]
    [ProgId("cs_com_server.Test")]
    [ClassInterface(ClassInterfaceType.None)]

    public class Test : ITest
    {
        public string ToUpper(string str)
        {
            return str.ToUpper();
        }
    }
}