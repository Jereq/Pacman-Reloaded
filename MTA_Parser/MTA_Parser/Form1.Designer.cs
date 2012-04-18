namespace MTA_Parser
{
    partial class MTA_Parser
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
            this.btn_parse = new System.Windows.Forms.Button();
            this.txb_outDest = new System.Windows.Forms.TextBox();
            this.btn_browseOut = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.txb_objIn = new System.Windows.Forms.TextBox();
            this.btn_objAdd = new System.Windows.Forms.Button();
            this.lb_objFiles = new System.Windows.Forms.ListBox();
            this.btn_objRemove = new System.Windows.Forms.Button();
            this.btn_BrowseTexture = new System.Windows.Forms.Button();
            this.txb_texture = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.lb_Animation = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // btn_parse
            // 
            this.btn_parse.Location = new System.Drawing.Point(519, 502);
            this.btn_parse.Name = "btn_parse";
            this.btn_parse.Size = new System.Drawing.Size(139, 23);
            this.btn_parse.TabIndex = 0;
            this.btn_parse.Text = "Parse and create .mta file";
            this.btn_parse.UseVisualStyleBackColor = true;
            // 
            // txb_outDest
            // 
            this.txb_outDest.Location = new System.Drawing.Point(12, 140);
            this.txb_outDest.Name = "txb_outDest";
            this.txb_outDest.Size = new System.Drawing.Size(227, 20);
            this.txb_outDest.TabIndex = 1;
            // 
            // btn_browseOut
            // 
            this.btn_browseOut.Location = new System.Drawing.Point(245, 138);
            this.btn_browseOut.Name = "btn_browseOut";
            this.btn_browseOut.Size = new System.Drawing.Size(75, 23);
            this.btn_browseOut.TabIndex = 2;
            this.btn_browseOut.Text = "Browse";
            this.btn_browseOut.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 115);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(96, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Output destination:";
            // 
            // txb_objIn
            // 
            this.txb_objIn.Location = new System.Drawing.Point(12, 25);
            this.txb_objIn.Name = "txb_objIn";
            this.txb_objIn.Size = new System.Drawing.Size(227, 20);
            this.txb_objIn.TabIndex = 4;
            // 
            // btn_objAdd
            // 
            this.btn_objAdd.Location = new System.Drawing.Point(245, 22);
            this.btn_objAdd.Name = "btn_objAdd";
            this.btn_objAdd.Size = new System.Drawing.Size(75, 23);
            this.btn_objAdd.TabIndex = 5;
            this.btn_objAdd.Text = "Add";
            this.btn_objAdd.UseVisualStyleBackColor = true;
            this.btn_objAdd.Click += new System.EventHandler(this.btn_objAdd_Click);
            // 
            // lb_objFiles
            // 
            this.lb_objFiles.FormattingEnabled = true;
            this.lb_objFiles.Location = new System.Drawing.Point(326, 22);
            this.lb_objFiles.Name = "lb_objFiles";
            this.lb_objFiles.Size = new System.Drawing.Size(332, 134);
            this.lb_objFiles.TabIndex = 6;
            this.lb_objFiles.DoubleClick += new System.EventHandler(this.lb_objFiles_DoubleClick);
            // 
            // btn_objRemove
            // 
            this.btn_objRemove.Location = new System.Drawing.Point(245, 51);
            this.btn_objRemove.Name = "btn_objRemove";
            this.btn_objRemove.Size = new System.Drawing.Size(75, 23);
            this.btn_objRemove.TabIndex = 7;
            this.btn_objRemove.Text = "Remove";
            this.btn_objRemove.UseVisualStyleBackColor = true;
            // 
            // btn_BrowseTexture
            // 
            this.btn_BrowseTexture.Location = new System.Drawing.Point(245, 80);
            this.btn_BrowseTexture.Name = "btn_BrowseTexture";
            this.btn_BrowseTexture.Size = new System.Drawing.Size(75, 23);
            this.btn_BrowseTexture.TabIndex = 9;
            this.btn_BrowseTexture.Text = "Browse";
            this.btn_BrowseTexture.UseVisualStyleBackColor = true;
            // 
            // txb_texture
            // 
            this.txb_texture.Location = new System.Drawing.Point(12, 82);
            this.txb_texture.Name = "txb_texture";
            this.txb_texture.Size = new System.Drawing.Size(227, 20);
            this.txb_texture.TabIndex = 10;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(46, 13);
            this.label2.TabIndex = 11;
            this.label2.Text = "OBJ file:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 64);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(62, 13);
            this.label3.TabIndex = 12;
            this.label3.Text = "Texture file:";
            // 
            // lb_Animation
            // 
            this.lb_Animation.FormattingEnabled = true;
            this.lb_Animation.Location = new System.Drawing.Point(326, 162);
            this.lb_Animation.Name = "lb_Animation";
            this.lb_Animation.Size = new System.Drawing.Size(332, 82);
            this.lb_Animation.TabIndex = 13;
            this.lb_Animation.DoubleClick += new System.EventHandler(this.lb_Animation_DoubleClick);
            // 
            // MTA_Parser
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(670, 537);
            this.Controls.Add(this.lb_Animation);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txb_texture);
            this.Controls.Add(this.btn_BrowseTexture);
            this.Controls.Add(this.btn_objRemove);
            this.Controls.Add(this.lb_objFiles);
            this.Controls.Add(this.btn_objAdd);
            this.Controls.Add(this.txb_objIn);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btn_browseOut);
            this.Controls.Add(this.txb_outDest);
            this.Controls.Add(this.btn_parse);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "MTA_Parser";
            this.Text = "MTA Parser";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_parse;
        private System.Windows.Forms.TextBox txb_outDest;
        private System.Windows.Forms.Button btn_browseOut;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txb_objIn;
        private System.Windows.Forms.Button btn_objAdd;
        private System.Windows.Forms.ListBox lb_objFiles;
        private System.Windows.Forms.Button btn_objRemove;
        private System.Windows.Forms.Button btn_BrowseTexture;
        private System.Windows.Forms.TextBox txb_texture;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ListBox lb_Animation;
    }
}

