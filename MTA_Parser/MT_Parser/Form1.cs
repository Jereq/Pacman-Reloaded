using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace MT_Parser
{
    public partial class MT_Parser : Form
    {
        string objFile = "";
        string texture = "";


        public MT_Parser()
        {
            InitializeComponent();
        }

        private void btn_browseObj_Click(object sender, EventArgs e)
        {
            DialogResult res = openFile.ShowDialog();

            if (res == DialogResult.OK)
            {
                objFile = openFile.FileName.ToString();
            }

            txb_objIn.Text = objFile;
        }

        private void btn_browseTex_Click(object sender, EventArgs e)
        {
            DialogResult res = openFile.ShowDialog();

            if (res == DialogResult.OK)
            {
                texture = openFile.FileName.ToString();
            }
        }

        private void btn_parseAndSave_Click(object sender, EventArgs e)
        {
            OBJFile obj = new OBJFile(objFile);

            saveFile.AddExtension = false;
            saveFile.DefaultExt = "mt";

            DialogResult res = saveFile.ShowDialog();

            if (res == DialogResult.OK)
            {
                Stream s = new FileStream(saveFile.FileName, FileMode.Create);
                var v = new BinaryWriter(s);

                v.Write(obj.getVertexCount);
                v.Write(obj.getIndexCount);
                v.Write(txb_texIn.Text.Length);
                v.Write(txb_texIn.Text);

                foreach (Vertex ve in obj.getVertices)
                {
                    for (int i = 0; i < 3; i++) //vertex coordinates
                    {
                        v.Write(ve.VP[i]);
                    }

                    for (int i = 0; i < 3; i++) //vertex normals
                    {
                        v.Write(ve.VN[i]);
                    }

                    for (int i = 0; i < 2; i++) //vertex texture coordinates
                    {
                        v.Write(ve.VT[i]);
                    }
                }

                foreach (int i in obj.getIndecies)
                {
                    v.Write(i);
                }

                v.Flush();
                s.Close();
            }
        }
    }
}
