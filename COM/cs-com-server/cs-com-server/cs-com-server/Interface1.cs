using System;
using System.Runtime.InteropServices;

namespace cs_com_server
{
    [ComVisible(true)]
    [Guid("C8B90512-3FB3-4971-B321-D42A162CF195")]
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    public interface ITest
    {
        string ToUpper(string str);
    }
}

// https://qiita.com/EvilSpirit39/items/c959fc990d1660b77180
// https://codezine.jp/article/detail/424
