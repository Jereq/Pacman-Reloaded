using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MTA_Parser
{
    class Animation
    {
        private int index;
        private float time;
        private string name;
        private int[] sequence;
        private int objCount;

        public Animation(List<OBJFile> _obj, float _time, string _name, int _index)
        {
            time = _time;
            name = _name;
            index = _index;
            objCount = _obj.Count;
            sequence = new int[_obj.Count];

            for (int i = 0; i < sequence.Length; i++ )
            {
                sequence[i] = _obj[i].Index;
            }
        }
        #region getters

        public string Name
        {
            get { return name; }
        }

        public int Index
        {
            get { return index; }
        }

        public int ObjCount
        {
            get { return objCount; }
        }

        public int[] Sequence
        {
            get { return sequence; }
        }

        public float Time
        {
            get { return time; }
        }

        #endregion
    }
}
