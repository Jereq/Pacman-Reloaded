using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace MTA_Parser
{
    public partial class MTA_Parser : Form
    {
        List<OBJFile> objFiles = new List<OBJFile>();
        List<OBJFile> objFilesAnimation = new List<OBJFile>();
        List<Animation> animations = new List<Animation>();
        OpenFileDialog fileBrowser = new OpenFileDialog();
        SaveFileDialog saveFile = new SaveFileDialog();
        List<Vertex> globalVertices = new List<Vertex>();
        Dictionary<Vertex, int> globalDictionary = new Dictionary<Vertex, int>(new Comparer());

        public MTA_Parser()
        {
            InitializeComponent();

            lb_objFiles.DataSource = objFiles;
            lb_objFiles.DisplayMember = "Name";
            lb_objFiles.ValueMember = "Index";

            lb_Animation.DataSource = objFilesAnimation;
            lb_Animation.DisplayMember = "Name";
            lb_Animation.ValueMember = "Index";

            lb_finishedAnimations.DataSource = animations;
            lb_finishedAnimations.DisplayMember = "Name";
            lb_finishedAnimations.ValueMember = "Index";
        }

        private void lb_objFiles_DoubleClick(object sender, EventArgs e)
        {
            objFilesAnimation.Add(objFiles[lb_objFiles.SelectedIndex]);

            ((CurrencyManager)lb_Animation.BindingContext[lb_Animation.DataSource]).Refresh();
        }

        private void lb_Animation_DoubleClick(object sender, EventArgs e)
        {
            if (objFilesAnimation.Count == 0)
            {
                return;
            }

            objFilesAnimation.RemoveAt(lb_Animation.SelectedIndex);

            ((CurrencyManager)lb_Animation.BindingContext[lb_Animation.DataSource]).Refresh();
        }

        private void btn_objAdd_Click(object sender, EventArgs e)
        {
            objFiles.Add(new OBJFile(txb_objIn.Text, objFiles.Count, globalVertices, globalDictionary));
           ((CurrencyManager)lb_objFiles.BindingContext[lb_objFiles.DataSource]).Refresh();
        }

        private void btn_browseOBJ_Click(object sender, EventArgs e)
        {
            txb_objIn.Text = browse();
        }

        private void btn_BrowseTexture_Click(object sender, EventArgs e)
        {
            txb_texture.Text = browse();
        }

        private void btn_objRemove_Click(object sender, EventArgs e)
        {
            objFiles.RemoveAt(lb_objFiles.SelectedIndex);

            for (int i = lb_objFiles.SelectedIndex; i < objFiles.Count; i++)
            {
                objFiles[i].Index = i;
            }
            
            ((CurrencyManager)lb_objFiles.BindingContext[lb_objFiles.DataSource]).Refresh();
        }

        private void btn_createAnimation_Click(object sender, EventArgs e)
        {
            if (txb_animationName.Text != "" || Convert.ToSingle(txb_animationTime.Text) != 0.0f)
            {
                if (animations.Count == 0)
                {
                    animations.Add(new Animation(objFilesAnimation, Convert.ToSingle(txb_animationTime.Text), txb_animationName.Text, 0));
                }
                else
                {
                    animations.Add(new Animation(objFilesAnimation, Convert.ToSingle(txb_animationTime.Text), txb_animationName.Text, animations.Last().Index + 1));
                }

                objFilesAnimation.Clear();
                ((CurrencyManager)lb_finishedAnimations.BindingContext[lb_finishedAnimations.DataSource]).Refresh();                
                ((CurrencyManager)lb_Animation.BindingContext[lb_Animation.DataSource]).Refresh();
                txb_animationName.Text = "";
                txb_animationTime.Text = "";
            }
            else
            {
                MessageBox.Show("You have to specify a name and animation time", "ERROR!");
            }
        }

        private void btn_AnimationRemove_Click(object sender, EventArgs e)
        {
            animations.RemoveAt(lb_finishedAnimations.SelectedIndex);
            ((CurrencyManager)lb_finishedAnimations.BindingContext[lb_finishedAnimations.DataSource]).Refresh();
        }

        private void btn_parse_Click(object sender, EventArgs e)
        {
            saveFile.AddExtension = true;
            saveFile.DefaultExt = "mta";
            DialogResult res = saveFile.ShowDialog();             

            if (res == DialogResult.OK)
            {
                Stream s = new FileStream(saveFile.FileName, FileMode.Create);
                //var v = new BinaryWriter(s);
                var v = new StreamWriter(s);

                v.Write(objFiles.Count); // num of index buffers
                v.Write(objFiles[0].getIndices.Count); // size of index buffers   
                v.Write(globalVertices.Count); //size of global vertex buffer
                v.Write(txb_texture.Text.Length); //length of texture file string
                v.Write(txb_texture.Text); // texture file string
                v.Write(animations.Count); //Animation count

                foreach (Animation a in animations) //Animation sets
                {
                    v.Write(a.Name.Length);
                    v.Write(a.Name);
                    v.Write(a.Time);
                    v.Write(a.ObjCount);

                    foreach (int i in a.Sequence)
                    {
                        v.Write(i);
                    }
                }

                foreach (OBJFile o in objFiles) // index buffers of eash obj file
                {
                    foreach (int i in o.getIndices)
                    {
                        v.Write(i);
                    }
                }

                foreach (Vertex ve in globalVertices) //Global list of vertices
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

                v.Flush();
                s.Close();
            }
        }

        private string browse()
        {
            string result = "";

                DialogResult res = fileBrowser.ShowDialog();

                if (res == DialogResult.OK)
                {
                    result = fileBrowser.FileName.ToString();
                }

            return result;
        }
    }
}
