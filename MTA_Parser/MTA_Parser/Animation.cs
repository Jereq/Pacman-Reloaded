using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MTA_Parser
{
    class Animation
    {
        private List<OBJFile> objFiles;
        private int index;
        private float time;
        private string name;

        public Animation(List<OBJFile> _obj, float _time, string _name, int _index)
        {
            objFiles = _obj;
            time = _time;
            name = _name;
            index = _index;
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

        public List<OBJFile> ObjFiles
        {
            get { return objFiles; }
        }

        public float Time
        {
            get { return time; }
        }
        #endregion
    }
}
