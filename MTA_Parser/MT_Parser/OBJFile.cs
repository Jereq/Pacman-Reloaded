using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Globalization;

namespace MT_Parser
{
    class OBJFile
    {
        private List<float[]> vertexCord = new List<float[]>();
        private List<float[]> textureCord = new List<float[]>();
        private List<float[]> normalCord = new List<float[]>();
        private List<int[,]> faces = new List<int[,]>();
        private List<Vertex> tempVertices = new List<Vertex>();
        private List<Vertex> finalVertices = new List<Vertex>();
        private List<int> indices = new List<int>();
        Dictionary<Vertex, int> dictionary = new Dictionary<Vertex, int>(new Comparer());

        public OBJFile(string _filePath)
        {
            char[] ch = new char[] { '\\' };
            string[] tmp = _filePath.Split(ch);

            readFile(_filePath);
            makeVertices();
            makeIndices();
        }

        public int getVertexCount
        {
            get { return finalVertices.Count; }
        }

        public int getIndexCount
        {
            get { return indices.Count; }
        }

        public List<Vertex> getVertices
        {
            get { return finalVertices; }
        }

        public List<int> getIndecies
        {
            get { return indices; }
        }

        private void readFile(string _file)
        {
            StreamReader sr = new StreamReader(_file);
            string line = "";
            char[] ch = new char[] { ' ', '/' };
            string[] s;

            CultureInfo ci = CultureInfo.InvariantCulture;

            while ((line = sr.ReadLine()) != null)
            {
                s = line.Split(ch);

                if (s[0] == "v")
                {
                    vertexCord.Add(new float[] { Convert.ToSingle(s[1], ci), Convert.ToSingle(s[2], ci), -Convert.ToSingle(s[3], ci) });
                }
                else if (s[0] == "vt")
                {
                    textureCord.Add(new float[] { Convert.ToSingle(s[1], ci), Convert.ToSingle(s[2], ci) });
                }
                else if (s[0] == "vn")
                {
                    normalCord.Add(new float[] { Convert.ToSingle(s[1], ci), Convert.ToSingle(s[2], ci), -Convert.ToSingle(s[3], ci) });
                }
                else if (s[0] == "f")
                {
                    faces.Add(new int[,] { { Convert.ToInt32(s[1], ci), Convert.ToInt32(s[2], ci), Convert.ToInt32(s[3], ci) }, 
                                           { Convert.ToInt32(s[4], ci), Convert.ToInt32(s[5], ci), Convert.ToInt32(s[6], ci) }, 
                                           { Convert.ToInt32(s[7], ci), Convert.ToInt32(s[8], ci), Convert.ToInt32(s[9], ci) } });
                }
            }
        }

        private void makeVertices()
        {
            for (int i = 0; i < faces.Count; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    float[] vp = vertexCord[faces[i][j, 0] - 1];
                    float[] vt = textureCord[faces[i][j, 1] - 1];
                    float[] vn = normalCord[faces[i][j, 2] - 1];

                    Vertex v = new Vertex(vp, vt, vn);
                    tempVertices.Add(v);
                }
            }
        }

        private void makeIndices()
        {
            foreach (Vertex v in tempVertices)
            {
                int t;

                if (dictionary.TryGetValue(v, out t))
                {
                    indices.Add(t);
                }
                else
                {
                    dictionary.Add(v, finalVertices.Count);
                    indices.Add(finalVertices.Count);
                    finalVertices.Add(v);
                }
            }
        }
    }

    struct Vertex
    {
        float[] vp, vt, vn;

        public Vertex(float[] _vp, float[] _vt, float[] _vn)
        {
            vp = _vp;
            vt = _vt;
            vn = _vn;
        }

        public float[] VP
        {
            get { return vp; }
        }

        public float[] VT
        {
            get { return vt; }
        }

        public float[] VN
        {
            get { return vn; }
        }
    }
}
