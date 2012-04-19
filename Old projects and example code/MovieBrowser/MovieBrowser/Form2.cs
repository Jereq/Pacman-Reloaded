using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Diagnostics;
using System.IO;

namespace MovieBrowser
{
    public partial class Form2 : Form
    {
        static Form2 edit, addMov;
        Form1 origin;
        private OpenFileDialog fileBrowse;
        public SqlConnection cs = new SqlConnection("Data Source=SERVER-PC; Database=MovieDB; User id=ossian-pc; password=galenpannan87(/");
        public SqlDataAdapter da = new SqlDataAdapter();
        int ID;
        bool sampleToggle;
        public bool addMovie = false;

        public Form2( Form1 origin)
        {
            InitializeComponent();
            fileBrowse = new OpenFileDialog();            
            this.origin = origin;
        }        

        public static void Show(int temp, Form1 origin)
        {
            edit = new Form2(origin);
            string tempSample;
            edit.ID = temp;

            SqlDataReader dr;

            edit.da.SelectCommand = new SqlCommand("SELECT * FROM MovieDB WHERE ID = @id", edit.cs);
            edit.da.SelectCommand.Parameters.Add("@id", SqlDbType.Int).Value = temp;
            edit.cs.Open();
            dr = edit.da.SelectCommand.ExecuteReader();
            dr.Read();

            edit.MovieNameTb.Text = dr["Title"].ToString();
            edit.ReleasedTb.Text = dr["Released"].ToString();
            edit.RatingTb.Text = dr["Rating"].ToString();
            edit.GenreTb.Text = dr["Genre"].ToString();
            edit.SubtitleTb.Text = dr["Subtitle"].ToString();
            edit.SourceTb.Text = dr["Source"].ToString();
            edit.SoundTb.Text = dr["Sound"].ToString();
            edit.QualityTb.Text = dr["Quality"].ToString();
            edit.CoverTb.Text = dr["Poster"].ToString();
            edit.DescriptionTb.Text = dr["Plot"].ToString();
            edit.MiscTb.Text = dr["Misc"].ToString();
            edit.RatedTb.Text = dr["Rated"].ToString();
            edit.RunTimeTb.Text = dr["Runtime"].ToString();
            edit.VotesTb.Text = dr["Votes"].ToString();
            edit.FolderTb.Text = dr["FolderPath"].ToString();
            tempSample = dr["SamplePath"].ToString();
            tempSample = tempSample.ToLower();
            edit.SampleTb.Text = tempSample;
            edit.DirectorsTb.Text = dr["Director"].ToString();
            edit.WritersTb.Text = dr["Writer"].ToString();
            edit.ActorsTb.Text = dr["Actor"].ToString();


            if (dr["HasSample"].ToString() == "True")
            {
                edit.SampleTogleBtn.Text = "YES";
                edit.sampleToggle = true;
            }
            else
            {
                edit.SampleTogleBtn.Text = "NO";
                edit.sampleToggle = false;
            }

            edit.cs.Close();
            edit.ShowDialog();
        }

        public static void AddMovie(Form1 origin, bool add)
        {
            addMov = new Form2(origin);
            addMov.sampleToggle = false;
            addMov.SampleTogleBtn.Text = "N/A";
            addMov.addMovie = true;
            addMov.ShowDialog();
        }

        private void BrowseBtn_Click(object sender, EventArgs e)
        {
            DialogResult result = fileBrowse.ShowDialog();

            if (result == DialogResult.OK)
            {
                edit.CoverTb.Text = fileBrowse.FileName.ToString();
            }

        }

        private void SaveBtn_Click(object sender, EventArgs e)
        {
            if (this.addMovie == false)
            {
                editSql();
            }
            else
            {
                addSql();
            }

            this.origin.showAll();
            this.Close();
        }

        private void addSql()
        {
            DialogResult dr = MessageBox.Show("Are you shore you want to add this moive to the database?", "Save changes?", MessageBoxButtons.YesNo);

            if (dr == DialogResult.Yes)
            {
                da.InsertCommand = new SqlCommand("insert into MovieDB(Title, Released, Source, Quality, Subtitle, Sound, Plot, Rating, Misc, Poster, Genre, Rated, Runtime, Votes, FolderPath, SamplePath, Director, Writer, Actor, HasSample) values(@Title, @Released, @Source, @Quality, @Subtitle, @Sound, @Plot, @Rating, @Misc, @Poster, @Genre, @Rated, @Runtime, @Votes, @FolderPath, @SamplePath, @Director, @Writer, @Actor, @HasSample)", cs);

                if (addMov.MovieNameTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Title", SqlDbType.NVarChar).Value = addMov.MovieNameTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Title", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.ReleasedTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Released", SqlDbType.NVarChar).Value = addMov.ReleasedTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Released", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.SourceTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Source", SqlDbType.NVarChar).Value = addMov.SourceTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Source", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.QualityTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Quality", SqlDbType.NVarChar).Value = addMov.QualityTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Quality", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.SubtitleTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Subtitle", SqlDbType.NVarChar).Value = addMov.SubtitleTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Subtitle", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.SoundTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Sound", SqlDbType.NVarChar).Value = addMov.SoundTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Sound", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.DescriptionTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Plot", SqlDbType.NVarChar).Value = addMov.DescriptionTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Plot", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.RatingTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Rating", SqlDbType.Char).Value = addMov.RatingTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Rating", SqlDbType.Char).Value = "N/A";
                }

                if (addMov.MiscTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Misc", SqlDbType.NVarChar).Value = addMov.MiscTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Misc", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.CoverTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Poster", SqlDbType.NVarChar).Value = addMov.CoverTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Poster", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.GenreTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Genre", SqlDbType.NVarChar).Value = addMov.GenreTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Genre", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.RatedTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Rated", SqlDbType.NVarChar).Value = addMov.RatedTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Rated", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.RunTimeTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Runtime", SqlDbType.NVarChar).Value = addMov.RunTimeTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Runtime", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.VotesTb.Text != "")                    
                {
                    int temp = Convert.ToInt32(addMov.VotesTb.Text);
                    da.InsertCommand.Parameters.Add("@Votes", SqlDbType.Int).Value = temp;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Votes", SqlDbType.Int).Value = 0;
                }

                if (addMov.FolderTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@FolderPath", SqlDbType.NVarChar).Value = addMov.FolderTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@FolderPath", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.SampleTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@SamplePath", SqlDbType.NVarChar).Value = addMov.SampleTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@SamplePath", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.DirectorsTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Director", SqlDbType.NVarChar).Value = addMov.DirectorsTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Director", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.WritersTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Writer", SqlDbType.NVarChar).Value = addMov.WritersTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Writer", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.ActorsTb.Text != "")
                {
                    da.InsertCommand.Parameters.Add("@Actor", SqlDbType.NVarChar).Value = addMov.ActorsTb.Text;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@Actor", SqlDbType.NVarChar).Value = "N/A";
                }

                if (addMov.sampleToggle == true)
                {
                    da.InsertCommand.Parameters.Add("@HasSample", SqlDbType.Bit).Value = 1;
                }
                else
                {
                    da.InsertCommand.Parameters.Add("@HasSample", SqlDbType.Bit).Value = 0;
                }

                cs.Open();
                da.InsertCommand.ExecuteNonQuery();
                cs.Close();   
            }
        }

        private void editSql()
        {
            DialogResult dr = MessageBox.Show("Are you shore you want to save these changes?", "Save changes?", MessageBoxButtons.YesNo);

            if (dr == DialogResult.Yes)
            {
                da.UpdateCommand = new SqlCommand("update MovieDB set Title = @MovieName, Released = @Rel, Source = @Source, Quality = @Quality, Subtitle = @Subtitle, Sound = @Sound, Plot = @Description, Rating = @Rating, Misc = @Misc, Poster = @Cover, Genre = @Genre, Rated = @Rated, Runtime = @Run, Votes = @Vote, FolderPath = @FolderP, SamplePath = @SampleP, Director = @Dir, Writer = @Wir, Actor = @Act, HasSample = @HSample where ID = @ID", cs);

                if (edit.MovieNameTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@MovieName", SqlDbType.NVarChar).Value = edit.MovieNameTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@MovieName", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.ReleasedTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Rel", SqlDbType.NVarChar).Value = edit.ReleasedTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Rel", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.SourceTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Source", SqlDbType.NVarChar).Value = edit.SourceTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Source", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.QualityTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Quality", SqlDbType.NVarChar).Value = edit.QualityTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Quality", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.SubtitleTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Subtitle", SqlDbType.NVarChar).Value = edit.SubtitleTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Subtitle", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.SoundTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Sound", SqlDbType.NVarChar).Value = edit.SoundTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Sound", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.DescriptionTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Description", SqlDbType.NVarChar).Value = edit.DescriptionTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Description", SqlDbType.NVarChar).Value = "No description avalible";
                }

                if (edit.RatingTb.Text != "")
                {
                    string temp = edit.RatingTb.Text;
                    temp = temp.Trim();
                    da.UpdateCommand.Parameters.Add("@Rating", SqlDbType.Char).Value = temp;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Rating", SqlDbType.Decimal).Value = 0;
                }

                if (edit.MiscTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Misc", SqlDbType.NVarChar).Value = edit.MiscTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Misc", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.GenreTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Genre", SqlDbType.NVarChar).Value = edit.GenreTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Genre", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.RatedTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Rated", SqlDbType.NVarChar).Value = edit.RatedTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Rated", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.RunTimeTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Run", SqlDbType.NVarChar).Value = edit.RunTimeTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Run", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.VotesTb.Text != "")
                {
                    int temp = Convert.ToInt32(edit.VotesTb.Text);
                    da.UpdateCommand.Parameters.Add("@Vote", SqlDbType.Int).Value = temp;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Vote", SqlDbType.Int).Value = 0;
                }

                if (edit.FolderTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@FolderP", SqlDbType.NVarChar).Value = edit.FolderTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@FolderP", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.SampleTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@SampleP", SqlDbType.NVarChar).Value = edit.SampleTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@SampleP", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.DirectorsTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Dir", SqlDbType.NVarChar).Value = edit.DirectorsTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Dir", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.WritersTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Wir", SqlDbType.NVarChar).Value = edit.WritersTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Wir", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.ActorsTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Act", SqlDbType.NVarChar).Value = edit.ActorsTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Act", SqlDbType.NVarChar).Value = "N/A";
                }

                if (edit.CoverTb.Text != "")
                {
                    da.UpdateCommand.Parameters.Add("@Cover", SqlDbType.NVarChar).Value = edit.CoverTb.Text;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@Cover", SqlDbType.NVarChar).Value = "N/A";
                }

                if (sampleToggle == true)
                {
                    da.UpdateCommand.Parameters.Add("@HSample", SqlDbType.Bit).Value = 1;
                }
                else
                {
                    da.UpdateCommand.Parameters.Add("@HSample", SqlDbType.Bit).Value = 0;
                }


                da.UpdateCommand.Parameters.Add("@ID", SqlDbType.Int).Value = ID;

                cs.Open();
                da.UpdateCommand.ExecuteNonQuery();
                cs.Close();

            }
        }

        private void OpenFolderBtn_Click(object sender, EventArgs e)
        {
            Process.Start(edit.FolderTb.Text);
        }

        private void SampleTogleBtn_Click(object sender, EventArgs e)
        {
            if (this.addMovie == false)
            {
                if (edit.sampleToggle == false)
                {
                    edit.SampleTogleBtn.Text = "YES";
                    edit.sampleToggle = true;
                }
                else
                {
                    edit.SampleTogleBtn.Text = "NO";
                    edit.sampleToggle = false;
                }
            }

            else
            {
                if (addMov.sampleToggle == false)
                {
                    addMov.SampleTogleBtn.Text = "YES";
                    addMov.sampleToggle = true;
                }
                else
                {
                    addMov.SampleTogleBtn.Text = "NO";
                    addMov.sampleToggle = false;
                }
            }
        }
    }
}
