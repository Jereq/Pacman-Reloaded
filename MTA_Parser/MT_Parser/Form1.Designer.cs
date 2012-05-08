namespace MT_Parser
{
    partial class MT_Parser
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
            this.txb_objIn = new System.Windows.Forms.TextBox();
            this.txb_texIn = new System.Windows.Forms.TextBox();
            this.btn_browseObj = new System.Windows.Forms.Button();
            this.btn_parseAndSave = new System.Windows.Forms.Button();
            this.btn_browseTex = new System.Windows.Forms.Button();
            this.openFile = new System.Windows.Forms.OpenFileDialog();
            this.saveFile = new System.Windows.Forms.SaveFileDialog();
            this.SuspendLayout();
            // 
            // txb_objIn
            // 
            this.txb_objIn.Location = new System.Drawing.Point(12, 12);
            this.txb_objIn.Name = "txb_objIn";
            this.txb_objIn.Size = new System.Drawing.Size(260, 20);
            this.txb_objIn.TabIndex = 0;
            // 
            // txb_texIn
            // 
            this.txb_texIn.Location = new System.Drawing.Point(12, 67);
            this.txb_texIn.Name = "txb_texIn";
            this.txb_texIn.Size = new System.Drawing.Size(260, 20);
            this.txb_texIn.TabIndex = 1;
            // 
            // btn_browseObj
            // 
            this.btn_browseObj.Location = new System.Drawing.Point(12, 38);
            this.btn_browseObj.Name = "btn_browseObj";
            this.btn_browseObj.Size = new System.Drawing.Size(123, 23);
            this.btn_browseObj.TabIndex = 2;
            this.btn_browseObj.Text = "Browse OBJ";
            this.btn_browseObj.UseVisualStyleBackColor = true;
            this.btn_browseObj.Click += new System.EventHandler(this.btn_browseObj_Click);
            // 
            // btn_parseAndSave
            // 
            this.btn_parseAndSave.Location = new System.Drawing.Point(12, 125);
            this.btn_parseAndSave.Name = "btn_parseAndSave";
            this.btn_parseAndSave.Size = new System.Drawing.Size(123, 23);
            this.btn_parseAndSave.TabIndex = 3;
            this.btn_parseAndSave.Text = "Parse and save";
            this.btn_parseAndSave.UseVisualStyleBackColor = true;
            this.btn_parseAndSave.Click += new System.EventHandler(this.btn_parseAndSave_Click);
            // 
            // btn_browseTex
            // 
            this.btn_browseTex.Location = new System.Drawing.Point(12, 96);
            this.btn_browseTex.Name = "btn_browseTex";
            this.btn_browseTex.Size = new System.Drawing.Size(123, 23);
            this.btn_browseTex.TabIndex = 4;
            this.btn_browseTex.Text = "Browse Texture";
            this.btn_browseTex.UseVisualStyleBackColor = true;
            this.btn_browseTex.Click += new System.EventHandler(this.btn_browseTex_Click);
            // 
            // MT_Parser
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 161);
            this.Controls.Add(this.btn_browseTex);
            this.Controls.Add(this.btn_parseAndSave);
            this.Controls.Add(this.btn_browseObj);
            this.Controls.Add(this.txb_texIn);
            this.Controls.Add(this.txb_objIn);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "MT_Parser";
            this.Text = "MT Parser";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txb_objIn;
        private System.Windows.Forms.TextBox txb_texIn;
        private System.Windows.Forms.Button btn_browseObj;
        private System.Windows.Forms.Button btn_parseAndSave;
        private System.Windows.Forms.Button btn_browseTex;
        private System.Windows.Forms.OpenFileDialog openFile;
        private System.Windows.Forms.SaveFileDialog saveFile;
    }
}

