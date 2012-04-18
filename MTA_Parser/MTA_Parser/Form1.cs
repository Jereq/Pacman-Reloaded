using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MTA_Parser
{
    public partial class MTA_Parser : Form
    {
        List<objFile> objFiles = new List<objFile>();
        List<objFile> objFilesAnimation = new List<objFile>();

        public MTA_Parser()
        {
            InitializeComponent();

            for (int i = 0; i < 5; i++ )
            {
                objFiles.Add(new objFile("obj" + i.ToString(), i));
            }

            lb_objFiles.DataSource = objFiles;
            lb_objFiles.DisplayMember = "Name";
            lb_objFiles.ValueMember = "Index";

            lb_Animation.DataSource = objFilesAnimation;
            lb_Animation.DisplayMember = "Name";
            lb_Animation.ValueMember = "Index";
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

        }
    }

    public class objFile
    {
        private string filePath;
        private string name;
        private int index;

        public objFile(string _filePath, int _index)
        {
            filePath = _filePath;
            name = _filePath;
            index = _index;
        }

        public string Name
        {
            get { return name; }
        }

        public int Index
        {
            get { return index; }
        }
    }
}
