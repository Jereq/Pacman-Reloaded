namespace MovieBrowser
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.MovieCoverBox = new System.Windows.Forms.PictureBox();
            this.MovNameLb = new System.Windows.Forms.Label();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.Menu1 = new System.Windows.Forms.ToolStripMenuItem();
            this.openMovieFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openSampleFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fetchIMDBDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addMovieToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.GenreLb = new System.Windows.Forms.Label();
            this.RatingLb = new System.Windows.Forms.Label();
            this.SourceLb = new System.Windows.Forms.Label();
            this.QualityLb = new System.Windows.Forms.Label();
            this.SubtitleLb = new System.Windows.Forms.Label();
            this.SoundLb = new System.Windows.Forms.Label();
            this.dg = new System.Windows.Forms.DataGridView();
            this.SearchTb = new System.Windows.Forms.TextBox();
            this.MovDescLb = new System.Windows.Forms.Label();
            this.MiscLb = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.ReleaseLb = new System.Windows.Forms.Label();
            this.VotesLb = new System.Windows.Forms.Label();
            this.DirectorLb = new System.Windows.Forms.Label();
            this.WriterLb = new System.Windows.Forms.Label();
            this.RatedLb = new System.Windows.Forms.Label();
            this.ActorLb = new System.Windows.Forms.Label();
            this.RunTimeLb = new System.Windows.Forms.Label();
            this.bgWorker = new System.ComponentModel.BackgroundWorker();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.MovieCoverBox)).BeginInit();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dg)).BeginInit();
            this.SuspendLayout();
            // 
            // MovieCoverBox
            // 
            this.MovieCoverBox.Location = new System.Drawing.Point(672, 27);
            this.MovieCoverBox.Name = "MovieCoverBox";
            this.MovieCoverBox.Size = new System.Drawing.Size(310, 460);
            this.MovieCoverBox.TabIndex = 0;
            this.MovieCoverBox.TabStop = false;
            // 
            // MovNameLb
            // 
            this.MovNameLb.AutoSize = true;
            this.MovNameLb.Font = new System.Drawing.Font("Calibri", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MovNameLb.Location = new System.Drawing.Point(366, 24);
            this.MovNameLb.Name = "MovNameLb";
            this.MovNameLb.Size = new System.Drawing.Size(141, 29);
            this.MovNameLb.TabIndex = 4;
            this.MovNameLb.Text = "Movie Name";
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Menu1});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(994, 24);
            this.menuStrip1.TabIndex = 5;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // Menu1
            // 
            this.Menu1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openMovieFolderToolStripMenuItem,
            this.openSampleFolderToolStripMenuItem,
            this.fetchIMDBDataToolStripMenuItem,
            this.addMovieToolStripMenuItem,
            this.editToolStripMenuItem,
            this.deleteToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.Menu1.Name = "Menu1";
            this.Menu1.Size = new System.Drawing.Size(50, 20);
            this.Menu1.Text = "Menu";
            // 
            // openMovieFolderToolStripMenuItem
            // 
            this.openMovieFolderToolStripMenuItem.Name = "openMovieFolderToolStripMenuItem";
            this.openMovieFolderToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.openMovieFolderToolStripMenuItem.Text = "Unpack movie";
            this.openMovieFolderToolStripMenuItem.Click += new System.EventHandler(this.openMovieToolStripMenuItem_Click);
            // 
            // openSampleFolderToolStripMenuItem
            // 
            this.openSampleFolderToolStripMenuItem.Name = "openSampleFolderToolStripMenuItem";
            this.openSampleFolderToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.openSampleFolderToolStripMenuItem.Text = "View sample";
            this.openSampleFolderToolStripMenuItem.Click += new System.EventHandler(this.openSampleToolStripMenuItem_Click);
            // 
            // fetchIMDBDataToolStripMenuItem
            // 
            this.fetchIMDBDataToolStripMenuItem.Name = "fetchIMDBDataToolStripMenuItem";
            this.fetchIMDBDataToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.fetchIMDBDataToolStripMenuItem.Text = "Fetch IMDB data";
            this.fetchIMDBDataToolStripMenuItem.Click += new System.EventHandler(this.fetchIMDBDataToolStripMenuItem_Click);
            // 
            // addMovieToolStripMenuItem
            // 
            this.addMovieToolStripMenuItem.Name = "addMovieToolStripMenuItem";
            this.addMovieToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.addMovieToolStripMenuItem.Text = "Add movie";
            this.addMovieToolStripMenuItem.Click += new System.EventHandler(this.addMovieToolStripMenuItem_Click);
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.editToolStripMenuItem.Text = "Edit";
            this.editToolStripMenuItem.Click += new System.EventHandler(this.editToolStripMenuItem_Click);
            // 
            // deleteToolStripMenuItem
            // 
            this.deleteToolStripMenuItem.Name = "deleteToolStripMenuItem";
            this.deleteToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.deleteToolStripMenuItem.Text = "Delete";
            this.deleteToolStripMenuItem.Click += new System.EventHandler(this.deleteToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // GenreLb
            // 
            this.GenreLb.AutoEllipsis = true;
            this.GenreLb.AutoSize = true;
            this.GenreLb.Font = new System.Drawing.Font("Calibri", 9.75F);
            this.GenreLb.Location = new System.Drawing.Point(368, 129);
            this.GenreLb.MaximumSize = new System.Drawing.Size(300, 30);
            this.GenreLb.Name = "GenreLb";
            this.GenreLb.Size = new System.Drawing.Size(39, 15);
            this.GenreLb.TabIndex = 7;
            this.GenreLb.Text = "Genre";
            // 
            // RatingLb
            // 
            this.RatingLb.AutoSize = true;
            this.RatingLb.Font = new System.Drawing.Font("Calibri", 12F);
            this.RatingLb.Location = new System.Drawing.Point(367, 91);
            this.RatingLb.Name = "RatingLb";
            this.RatingLb.Size = new System.Drawing.Size(51, 19);
            this.RatingLb.TabIndex = 8;
            this.RatingLb.Text = "Rating";
            // 
            // SourceLb
            // 
            this.SourceLb.AutoSize = true;
            this.SourceLb.Font = new System.Drawing.Font("Calibri", 12F);
            this.SourceLb.Location = new System.Drawing.Point(367, 410);
            this.SourceLb.Name = "SourceLb";
            this.SourceLb.Size = new System.Drawing.Size(52, 19);
            this.SourceLb.TabIndex = 9;
            this.SourceLb.Text = "Source";
            // 
            // QualityLb
            // 
            this.QualityLb.AutoSize = true;
            this.QualityLb.Font = new System.Drawing.Font("Calibri", 12F);
            this.QualityLb.Location = new System.Drawing.Point(367, 429);
            this.QualityLb.Name = "QualityLb";
            this.QualityLb.Size = new System.Drawing.Size(56, 19);
            this.QualityLb.TabIndex = 10;
            this.QualityLb.Text = "Quality";
            // 
            // SubtitleLb
            // 
            this.SubtitleLb.AutoSize = true;
            this.SubtitleLb.Font = new System.Drawing.Font("Calibri", 12F);
            this.SubtitleLb.Location = new System.Drawing.Point(532, 410);
            this.SubtitleLb.Name = "SubtitleLb";
            this.SubtitleLb.Size = new System.Drawing.Size(58, 19);
            this.SubtitleLb.TabIndex = 11;
            this.SubtitleLb.Text = "Subtitle";
            // 
            // SoundLb
            // 
            this.SoundLb.AutoSize = true;
            this.SoundLb.Font = new System.Drawing.Font("Calibri", 12F);
            this.SoundLb.Location = new System.Drawing.Point(532, 429);
            this.SoundLb.Name = "SoundLb";
            this.SoundLb.Size = new System.Drawing.Size(48, 19);
            this.SoundLb.TabIndex = 12;
            this.SoundLb.Text = "Sound";
            // 
            // dg
            // 
            this.dg.AllowUserToAddRows = false;
            this.dg.AllowUserToDeleteRows = false;
            this.dg.AllowUserToResizeRows = false;
            this.dg.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dg.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dg.ColumnHeadersVisible = false;
            this.dg.Location = new System.Drawing.Point(13, 63);
            this.dg.Name = "dg";
            this.dg.ReadOnly = true;
            this.dg.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.dg.RowHeadersVisible = false;
            this.dg.RowHeadersWidth = 10;
            this.dg.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.dg.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.dg.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dg.ShowCellErrors = false;
            this.dg.ShowCellToolTips = false;
            this.dg.ShowEditingIcon = false;
            this.dg.Size = new System.Drawing.Size(340, 426);
            this.dg.TabIndex = 15;
            this.dg.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dg_CellContentClick);
            this.dg.CellContentDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dg_CellContentDoubleClick);
            // 
            // SearchTb
            // 
            this.SearchTb.Location = new System.Drawing.Point(13, 37);
            this.SearchTb.Name = "SearchTb";
            this.SearchTb.Size = new System.Drawing.Size(340, 20);
            this.SearchTb.TabIndex = 16;
            this.SearchTb.TextChanged += new System.EventHandler(this.SearchTb_TextChanged);
            // 
            // MovDescLb
            // 
            this.MovDescLb.AutoEllipsis = true;
            this.MovDescLb.AutoSize = true;
            this.MovDescLb.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MovDescLb.Location = new System.Drawing.Point(368, 186);
            this.MovDescLb.MaximumSize = new System.Drawing.Size(300, 100);
            this.MovDescLb.Name = "MovDescLb";
            this.MovDescLb.Size = new System.Drawing.Size(106, 15);
            this.MovDescLb.TabIndex = 17;
            this.MovDescLb.Text = "Movie description";
            // 
            // MiscLb
            // 
            this.MiscLb.AutoEllipsis = true;
            this.MiscLb.AutoSize = true;
            this.MiscLb.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MiscLb.Location = new System.Drawing.Point(368, 467);
            this.MiscLb.MaximumSize = new System.Drawing.Size(300, 30);
            this.MiscLb.Name = "MiscLb";
            this.MiscLb.Size = new System.Drawing.Size(34, 15);
            this.MiscLb.TabIndex = 18;
            this.MiscLb.Text = "Misc";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(367, 167);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(129, 19);
            this.label1.TabIndex = 19;
            this.label1.Text = "Movie description:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(367, 448);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(44, 19);
            this.label2.TabIndex = 20;
            this.label2.Text = "Misc:";
            // 
            // ReleaseLb
            // 
            this.ReleaseLb.AutoSize = true;
            this.ReleaseLb.Font = new System.Drawing.Font("Calibri", 12F);
            this.ReleaseLb.Location = new System.Drawing.Point(367, 53);
            this.ReleaseLb.Name = "ReleaseLb";
            this.ReleaseLb.Size = new System.Drawing.Size(61, 19);
            this.ReleaseLb.TabIndex = 21;
            this.ReleaseLb.Text = "Release";
            // 
            // VotesLb
            // 
            this.VotesLb.AutoSize = true;
            this.VotesLb.Font = new System.Drawing.Font("Calibri", 12F);
            this.VotesLb.Location = new System.Drawing.Point(462, 91);
            this.VotesLb.Name = "VotesLb";
            this.VotesLb.Size = new System.Drawing.Size(45, 19);
            this.VotesLb.TabIndex = 22;
            this.VotesLb.Text = "Votes";
            // 
            // DirectorLb
            // 
            this.DirectorLb.AutoEllipsis = true;
            this.DirectorLb.AutoSize = true;
            this.DirectorLb.Font = new System.Drawing.Font("Calibri", 9.75F);
            this.DirectorLb.Location = new System.Drawing.Point(368, 280);
            this.DirectorLb.MaximumSize = new System.Drawing.Size(300, 30);
            this.DirectorLb.Name = "DirectorLb";
            this.DirectorLb.Size = new System.Drawing.Size(52, 15);
            this.DirectorLb.TabIndex = 23;
            this.DirectorLb.Text = "Director";
            // 
            // WriterLb
            // 
            this.WriterLb.AutoEllipsis = true;
            this.WriterLb.AutoSize = true;
            this.WriterLb.Font = new System.Drawing.Font("Calibri", 9.75F);
            this.WriterLb.Location = new System.Drawing.Point(368, 331);
            this.WriterLb.MaximumSize = new System.Drawing.Size(300, 30);
            this.WriterLb.Name = "WriterLb";
            this.WriterLb.Size = new System.Drawing.Size(43, 15);
            this.WriterLb.TabIndex = 24;
            this.WriterLb.Text = "Writer";
            // 
            // RatedLb
            // 
            this.RatedLb.AutoSize = true;
            this.RatedLb.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RatedLb.Location = new System.Drawing.Point(367, 72);
            this.RatedLb.Name = "RatedLb";
            this.RatedLb.Size = new System.Drawing.Size(47, 19);
            this.RatedLb.TabIndex = 25;
            this.RatedLb.Text = "Rated";
            // 
            // ActorLb
            // 
            this.ActorLb.AutoEllipsis = true;
            this.ActorLb.AutoSize = true;
            this.ActorLb.Font = new System.Drawing.Font("Calibri", 9.75F);
            this.ActorLb.Location = new System.Drawing.Point(368, 378);
            this.ActorLb.MaximumSize = new System.Drawing.Size(300, 30);
            this.ActorLb.Name = "ActorLb";
            this.ActorLb.Size = new System.Drawing.Size(36, 15);
            this.ActorLb.TabIndex = 26;
            this.ActorLb.Text = "Actor";
            // 
            // RunTimeLb
            // 
            this.RunTimeLb.AutoSize = true;
            this.RunTimeLb.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RunTimeLb.Location = new System.Drawing.Point(367, 148);
            this.RunTimeLb.Name = "RunTimeLb";
            this.RunTimeLb.Size = new System.Drawing.Size(66, 19);
            this.RunTimeLb.TabIndex = 27;
            this.RunTimeLb.Text = "RunTime";
            // 
            // bgWorker
            // 
            this.bgWorker.WorkerReportsProgress = true;
            this.bgWorker.WorkerSupportsCancellation = true;
            this.bgWorker.DoWork += new System.ComponentModel.DoWorkEventHandler(this.bgWorker_DoWork);
            this.bgWorker.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.bgWorker_InProgress);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(367, 359);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(54, 19);
            this.label3.TabIndex = 28;
            this.label3.Text = "Actors:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(367, 110);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(52, 19);
            this.label4.TabIndex = 29;
            this.label4.Text = "Genre:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(367, 312);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(71, 19);
            this.label5.TabIndex = 30;
            this.label5.Text = "Writer(s):";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(367, 261);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(82, 19);
            this.label6.TabIndex = 31;
            this.label6.Text = "Director(s):";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(994, 499);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.RunTimeLb);
            this.Controls.Add(this.ActorLb);
            this.Controls.Add(this.RatedLb);
            this.Controls.Add(this.WriterLb);
            this.Controls.Add(this.DirectorLb);
            this.Controls.Add(this.VotesLb);
            this.Controls.Add(this.ReleaseLb);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.MiscLb);
            this.Controls.Add(this.MovDescLb);
            this.Controls.Add(this.SearchTb);
            this.Controls.Add(this.dg);
            this.Controls.Add(this.SoundLb);
            this.Controls.Add(this.SubtitleLb);
            this.Controls.Add(this.QualityLb);
            this.Controls.Add(this.SourceLb);
            this.Controls.Add(this.RatingLb);
            this.Controls.Add(this.GenreLb);
            this.Controls.Add(this.MovNameLb);
            this.Controls.Add(this.MovieCoverBox);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Movie browser";
            ((System.ComponentModel.ISupportInitialize)(this.MovieCoverBox)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dg)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox MovieCoverBox;
        private System.Windows.Forms.Label MovNameLb;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem Menu1;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.Label GenreLb;
        private System.Windows.Forms.Label RatingLb;
        private System.Windows.Forms.Label SourceLb;
        private System.Windows.Forms.ToolStripMenuItem openMovieFolderToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openSampleFolderToolStripMenuItem;
        private System.Windows.Forms.Label QualityLb;
        private System.Windows.Forms.Label SubtitleLb;
        private System.Windows.Forms.Label SoundLb;
        private System.Windows.Forms.DataGridView dg;
        private System.Windows.Forms.TextBox SearchTb;
        private System.Windows.Forms.Label MovDescLb;
        private System.Windows.Forms.Label MiscLb;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fetchIMDBDataToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addMovieToolStripMenuItem;
        private System.Windows.Forms.Label ReleaseLb;
        private System.Windows.Forms.Label VotesLb;
        private System.Windows.Forms.Label DirectorLb;
        private System.Windows.Forms.Label WriterLb;
        private System.Windows.Forms.Label RatedLb;
        private System.Windows.Forms.Label ActorLb;
        private System.Windows.Forms.Label RunTimeLb;
        private System.ComponentModel.BackgroundWorker bgWorker;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
    }
}

