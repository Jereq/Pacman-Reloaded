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
using System.Threading;
using System.Net;



namespace MovieBrowser
{
    public partial class Form1 : Form
    {
        SqlConnection cs = new SqlConnection("Data Source=SERVER-PC; Database=MovieDB; User id=ossian-pc; password=galenpannan87(/");
        SqlDataAdapter da = new SqlDataAdapter();
        SqlDataReader dr;
        Label[] labArr;
        string movieFolderLink, sampleFolderLink, hasSampleTex;
        BindingSource bs = new BindingSource();
        DataSet ds = new DataSet();        
        int ID = 0;
        Bitmap bitMap;
       
        

        public Form1()
        {            
            InitializeComponent();
            showAll();            
        }

        public void showAll()
        {
            da.SelectCommand = new SqlCommand("select ID, Title from MovieDB order by Title", cs);
            ds.Clear();
            da.Fill(ds);            
            dg.DataSource = ds.Tables[0];

            try
            {
                select(ID);                 
            }
            catch
            {
                cs.Close();
                select(Convert.ToInt32(dg[0, 0].Value.ToString())); 
            }           
            
        }

        private void select(int ID)
        {
            labArr = new Label[8] { MovNameLb, ReleaseLb, RatingLb, GenreLb, SubtitleLb, SourceLb, SoundLb, QualityLb};
            da.SelectCommand = new SqlCommand("SELECT * FROM MovieDB WHERE ID = @ID", cs);
            da.SelectCommand.Parameters.Add("@ID", SqlDbType.Int).Value = ID;
            cs.Open();
            dr = da.SelectCommand.ExecuteReader();
            dr.Read();

            ID = Convert.ToInt32(dr["ID"].ToString());
            MovNameLb.Text = dr["Title"].ToString();
            ReleaseLb.Text = "Released: " + dr["Released"].ToString();
            RatingLb.Text = "Rating: " + dr["Rating"].ToString();
            VotesLb.Text = "Votes: " + dr["Votes"].ToString();
            RunTimeLb.Text = "Run time: " + dr["Runtime"].ToString();
            GenreLb.Text = dr["Genre"].ToString();
            SubtitleLb.Text = "Subtitle: " + dr["Subtitle"].ToString();
            SourceLb.Text = "Source: " + dr["Source"].ToString();
            SoundLb.Text = "Sound: " + dr["Sound"].ToString();
            QualityLb.Text = "Quality: " + dr["Quality"].ToString();
            MovDescLb.Text = dr["Plot"].ToString();
            MiscLb.Text = dr["Misc"].ToString();
            movieFolderLink = dr["FolderPath"].ToString();
            sampleFolderLink = dr["SamplePath"].ToString();
            hasSampleTex = dr["HasSample"].ToString();
            DirectorLb.Text = dr["Director"].ToString();
            WriterLb.Text = dr["Writer"].ToString();
            ActorLb.Text = dr["Actor"].ToString();

            try
            {
                MovieCoverBox.Load(dr["Poster"].ToString());
            }
            catch
            {
                MovieCoverBox.Load("X:\\Moive covers\\noCover.png");
            }
            cs.Close();

            if (hasSampleTex == "True")
            {
                openSampleFolderToolStripMenuItem.Enabled = true;
            }
            else
            {
                openSampleFolderToolStripMenuItem.Enabled = false;
            }

            for (int i = 0; i < labArr.Length; i++)
            {
                if (labArr[i].Text == "")
                {
                    labArr[i].Text = "N/A";
                }
            }

        }

        private void editToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2.Show(Convert.ToInt32(dg.SelectedRows[0].Cells[0].Value.ToString()), this);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void openMovieToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DirectoryInfo di = new DirectoryInfo(movieFolderLink);
            FileInfo[] temp;
            temp = di.GetFiles();
            
            Process.Start(temp[10].FullName.ToString());
        }

        private void openSampleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DirectoryInfo di = new DirectoryInfo(sampleFolderLink);
            FileInfo[] temp;
            temp = di.GetFiles();

            Process.Start(temp[0].FullName.ToString());
        }

        private void SearchTb_TextChanged(object sender, EventArgs e)
        {
            da.SelectCommand = new SqlCommand("select ID, Title from MovieDB where Title like @movie order by Title", cs);
            da.SelectCommand.Parameters.Add("@movie", SqlDbType.NVarChar).Value = SearchTb.Text + "%";
            ds.Clear();
            da.Fill(ds);
            dg.DataSource = ds.Tables[0];
        }

        private void dg_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            select(Convert.ToInt32(dg.SelectedRows[0].Cells[0].Value.ToString()));            
        }

        private void dg_CellContentDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            Form2.Show(Convert.ToInt32(dg.SelectedRows[0].Cells[0].Value.ToString()), this);
        }

        private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult dr = MessageBox.Show("Are you shore you want to Delete all data of this movie?", "Delete?", MessageBoxButtons.YesNo);

            if (dr == DialogResult.Yes)
            {
                int ID = Convert.ToInt32(dg.SelectedRows[0].Cells[0].Value);
                da.DeleteCommand = new SqlCommand("delete from MovieDB where ID = @ID", cs);
                da.DeleteCommand.Parameters.Add("@ID", SqlDbType.Int).Value = ID;
                cs.Open();
                da.DeleteCommand.ExecuteNonQuery();
                cs.Close();
                showAll();
            }
        }

        private void fetchIMDBDataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string url = "http://www.imdbapi.com/?t=" + MovNameLb.Text;

            bgWorker.RunWorkerAsync(url);
        }

        private void bgWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            char[] charArr = new char[2] { ',', ':' };
            object[] objArr = new object[2];
            string[] stringArr = new string[30];
            string sourceCode = "";
            Bitmap bitMap;
            bool error = false;

            try
            {
                HttpWebRequest req = (HttpWebRequest)WebRequest.Create(e.Argument.ToString());
                HttpWebResponse resp = (HttpWebResponse)req.GetResponse();
                StreamReader sr = new StreamReader(resp.GetResponseStream());
                sourceCode = sr.ReadToEnd();
                sr.Close();
                resp.Close();

                stringArr = sourceCode.Split(charArr);

                for (int i = 0; i < stringArr.Length; i++)
                {
                    stringArr[i] = stringArr[i].Replace('"', ' ');
                    stringArr[i] = stringArr[i].Replace('{', ' ');
                    stringArr[i] = stringArr[i].Replace('}', ' ');
                    stringArr[i] = stringArr[i].Trim();
                }

                for(int i = 0; i < stringArr.Length; i++)
                {
                    if (stringArr[i] == "Parse Error")
                    {
                        error = true;
                    }
                }

                if (!error)
                {
                    stringArr[0] = mergeStr(stringArr, "Title", "Year", " ");
                    stringArr[1] = mergeStr(stringArr, "Year", "Rated", " ");
                    stringArr[2] = mergeStr(stringArr, "Rated", "Released", " ");
                    stringArr[3] = mergeStr(stringArr, "Released", "Genre", " ");
                    stringArr[4] = mergeStr(stringArr, "Director", "Writer", ", ");
                    stringArr[5] = mergeStr(stringArr, "Genre", "Director", " | ");
                    stringArr[6] = mergeStr(stringArr, "Writer", "Actors", ", ");
                    stringArr[7] = mergeStr(stringArr, "Actors", "Plot", ", ");
                    stringArr[8] = mergeStr(stringArr, "Plot", "Poster", " ");
                    stringArr[9] = mergeStr(stringArr, "Poster", "Runtime", ":");
                    stringArr[10] = mergeStr(stringArr, "Runtime", "Rating", ":");
                    stringArr[11] = mergeStr(stringArr, "Votes", "ID", "");
                    stringArr[12] = mergeStr(stringArr, "Rating", "Votes", "");
                    stringArr[13] = mergeStr(stringArr, "Poster", "Runtime", ":");

                    WebClient client = new WebClient();
                    Stream stream = client.OpenRead(mergeStr(stringArr, "Poster", "Runtime", ":"));
                    bitMap = new Bitmap(stream);
                    stream.Flush();
                    stream.Close();
                    objArr[0] = stringArr;
                    objArr[1] = bitMap;
                    bgWorker.ReportProgress(100, objArr);
                }
                else
                {
                    MessageBox.Show("Parse error! \n Please provide a valid title", "Y U NO WORK!? ლ(ಠ益ಠლ)");
                }

            }
            catch(Exception err)
            {
                MessageBox.Show(err.Message, "Y U NO WORK!? ლ(ಠ益ಠლ)");

                bgWorker.CancelAsync();
            }            
        }

        private void bgWorker_InProgress(object sender, ProgressChangedEventArgs e)
        {


            int i = e.ProgressPercentage;
            int temp = Convert.ToInt32(dg.SelectedRows[0].Cells[0].Value.ToString());
            object[] objArr = (object[])e.UserState;
            string[] strArr;
            strArr = (string[])objArr[0];
            bitMap = (Bitmap)objArr[1];
            bitMap.Save("X:\\Moive covers\\" + strArr[0] + ".jpeg");

            DirectoryInfo di = new DirectoryInfo("X:\\Moive covers\\");
            FileInfo[] fi = di.GetFiles(strArr[0] + ".jpeg");
            string posterName = fi[0].FullName.ToString();

            da.UpdateCommand = new SqlCommand("update MovieDB set Released = @Rel, Director = @Dir, Actor = @Act, Writer = @Wri, Poster = @Pos, Plot = @Plo, Genre = @Gen, Rating = @Rat, Votes = @Vot, Runtime = @Run, Year =  @Yea, Rated = @Rated where ID = @ID", cs);
            da.UpdateCommand.Parameters.Add("@Rel", SqlDbType.NVarChar).Value = strArr[3];
            da.UpdateCommand.Parameters.Add("@Dir", SqlDbType.NVarChar).Value = strArr[4];
            da.UpdateCommand.Parameters.Add("@Act", SqlDbType.NVarChar).Value = strArr[7];
            da.UpdateCommand.Parameters.Add("@Wri", SqlDbType.NVarChar).Value = strArr[6];
            da.UpdateCommand.Parameters.Add("@Pos", SqlDbType.NVarChar).Value = posterName;
            da.UpdateCommand.Parameters.Add("@Plo", SqlDbType.NVarChar).Value = strArr[8];
            da.UpdateCommand.Parameters.Add("@Gen", SqlDbType.NVarChar).Value = strArr[5];
            da.UpdateCommand.Parameters.Add("@Rat", SqlDbType.Char).Value = strArr[12];
            da.UpdateCommand.Parameters.Add("@Vot", SqlDbType.Int).Value = strArr[11];
            da.UpdateCommand.Parameters.Add("@Run", SqlDbType.NVarChar).Value = strArr[10];
            da.UpdateCommand.Parameters.Add("@Yea", SqlDbType.Int).Value = Convert.ToInt32(strArr[1]);
            da.UpdateCommand.Parameters.Add("@ID", SqlDbType.Int).Value = temp;
            da.UpdateCommand.Parameters.Add("@Rated", SqlDbType.NVarChar).Value = strArr[2];

            cs.Open();
            da.UpdateCommand.ExecuteNonQuery();
            cs.Close();

            select(temp);           
        }

        private string mergeStr(string[] arr, string startStr, string stopStr, string spaceStr)
        {
            string returnStr = "";

            for (int i = 0; i < arr.Length; i++)
            {
                if (arr[i] == startStr)
                {
                    int j = i;

                    while (arr[j] != stopStr)
                    {
                        if (arr[j] != startStr)
                        {
                            if (returnStr == "")
                            {
                                returnStr = arr[j];
                            }
                            else
                            {
                                returnStr = returnStr + spaceStr + arr[j];
                            }
                        }
                        j++;
                    }
                    break;
                }
            }
            return returnStr;
        }

        private void addMovieToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2.AddMovie(this, true);
        }
    }
}
