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
            if (objFiles.Count == 0)
            {
                objFiles.Add(new OBJFile(txb_objIn.Text, 0));
            }
            else
            {
                objFiles.Add(new OBJFile(txb_objIn.Text, objFiles.Last().Index + 1));
            }            
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
            ((CurrencyManager)lb_objFiles.BindingContext[lb_objFiles.DataSource]).Refresh();
        }

        private void btn_createAnimation_Click(object sender, EventArgs e)
        {
            if (txb_animationName.Text != "" || Num_AnimationTime.Value != 0)
            {
                if (animations.Count == 0)
                {
                    animations.Add(new Animation(objFilesAnimation, (int)Num_AnimationTime.Value, txb_animationName.Text, 0));
                }
                else
                {
                    animations.Add(new Animation(objFilesAnimation, (int)Num_AnimationTime.Value, txb_animationName.Text, animations.Last().Index + 1));
                }
                ((CurrencyManager)lb_finishedAnimations.BindingContext[lb_finishedAnimations.DataSource]).Refresh();
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
            DialogResult res = saveFile.ShowDialog();             

            if (res == DialogResult.OK)
            {
                Stream s = new FileStream(saveFile.FileName + ".mta", FileMode.Create);
                var v = new BinaryWriter(s);
                //var v = new StreamWriter(s);
                v.Write(objFiles.Count);
                v.Write(objFiles[0].vertCount);
                v.Write(animations.Count);
                v.Write(txb_texture.Text.Length);
                v.Write(txb_texture.Text);

                //Animation time
                foreach (Animation a in animations)
                {
                    v.Write(a.Time);
                }

                //Animation sequence
                foreach (Animation a in animations)
                {
                    foreach (OBJFile o in a.ObjFiles)
                    {
                        v.Write(o.Index);
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
