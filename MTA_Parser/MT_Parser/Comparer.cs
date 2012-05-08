using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MT_Parser
{
    class Comparer : IEqualityComparer<Vertex>
    {
        public bool Equals(Vertex _v1, Vertex _v2)
        {
            if (_v1.VN[0] == _v2.VN[0] && _v1.VN[1] == _v2.VN[1] && _v1.VN[2] == _v2.VN[2] &&
                _v1.VP[0] == _v2.VP[0] && _v1.VP[1] == _v2.VP[1] && _v1.VP[2] == _v2.VP[2] &&
                _v1.VT[0] == _v2.VT[0] && _v1.VT[1] == _v2.VT[1])
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public int GetHashCode(Vertex v)
        {
            int res = (int)(v.VP[0] + v.VP[1] + v.VP[2] + v.VT[0] + v.VT[1] + v.VN[0] + v.VN[1] + v.VN[2]);
            return res.GetHashCode();
        }
    }
}
