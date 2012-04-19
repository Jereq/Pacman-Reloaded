using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Globalization;

namespace MTA_Parser
{
    class OBJFile
    {
        private string filePath;
        private string name;
        private int index;
        private List<float[]> verticeCord = new List<float[]>();
        private List<float[]> textureCord = new List<float[]>();
        private List<float[]> normalCord = new List<float[]>();
        private List<int[,]> faces = new List<int[,]>();
        private List<Vertice> vertices = new List<Vertice>();

        public OBJFile(string _filePath, int _index)
        {
            filePath = _filePath;
            index = _index;

            char[] ch = new char[] { '\\' };
            string[] tmp = _filePath.Split(ch);

            name = tmp.Last();

            readFile(filePath);
            makeVertices();
        }

        public string Name
        {
            get { return name; }
        }

        public int Index
        {
            get { return index; }
        }

        public int vertCount
        {
            get { return verticeCord.Count; }
        }

        private void readFile(string _file)
        {
            StreamReader sr = new StreamReader(_file);
            string line = "";
            char[] ch = new char[] { ' ', '/' };
            string[] s;

            CultureInfo ci = CultureInfo.InvariantCulture;
            
            while((line = sr.ReadLine()) != null)
            {
                s = line.Split(ch);                

                if (s[0] == "v")
                {
                    verticeCord.Add(new float[] { Convert.ToSingle(s[1], ci), Convert.ToSingle(s[2], ci), Convert.ToSingle(s[3], ci) }); 
                }
                else if (s[0] == "vt")
                {
                    textureCord.Add(new float[] { Convert.ToSingle(s[1], ci), Convert.ToSingle(s[2], ci) });
                }
                else if (s[0] == "vn")
                {
                    normalCord.Add(new float[] { Convert.ToSingle(s[1], ci), Convert.ToSingle(s[2], ci), Convert.ToSingle(s[3], ci) }); 
                }
                else if (s[0] == "f")
                {
                    faces.Add(new int[,] { { Convert.ToInt32(s[1], ci), Convert.ToInt32(s[2], ci), Convert.ToInt32(s[3], ci) }, 
                                           { Convert.ToInt32(s[4], ci), Convert.ToInt32(s[5], ci), Convert.ToInt32(s[6], ci) }, 
                                           { Convert.ToInt32(s[7], ci), Convert.ToInt32(s[8], ci), Convert.ToInt32(s[9], ci) } });
                }
            }
        }

        public void makeVertices()
        {
            for(int i = 0; i < faces.Count; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    float[] vp = verticeCord[faces[i][j, 0] - 1];
                    float[] vt = textureCord[faces[i][j, 1] - 1];
                    float[] vn = normalCord[faces[i][j, 2] - 1];

                    Vertice v = new Vertice(vp, vt, vn);
                    vertices.Add(v);
                }
            }
        }
    }

    struct Vertice
    {
        float[] vp, vt, vn;

        public Vertice(float[] _vp, float[] _vt, float[] _vn)
        {
            vp = _vp;
            vt = _vt;
            vn = _vn;
        }
    }
}
