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
            this.txb_objIn = new System.Windows.Forms.TextBox();
            this.btn_objAdd = new System.Windows.Forms.Button();
            this.lb_objFiles = new System.Windows.Forms.ListBox();
            this.btn_objRemove = new System.Windows.Forms.Button();
            this.btn_BrowseTexture = new System.Windows.Forms.Button();
            this.txb_texture = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.lb_Animation = new System.Windows.Forms.ListBox();
            this.btn_browseOBJ = new System.Windows.Forms.Button();
            this.shapeContainer1 = new Microsoft.VisualBasic.PowerPacks.ShapeContainer();
            this.lineShape2 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.lineShape1 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.btn_createAnimation = new System.Windows.Forms.Button();
            this.lb_finishedAnimations = new System.Windows.Forms.ListBox();
            this.label6 = new System.Windows.Forms.Label();
            this.Num_AnimationTime = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.txb_animationName = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.btn_AnimationRemove = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.Num_AnimationTime)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_parse
            // 
            this.btn_parse.Location = new System.Drawing.Point(169, 321);
            this.btn_parse.Name = "btn_parse";
            this.btn_parse.Size = new System.Drawing.Size(139, 23);
            this.btn_parse.TabIndex = 0;
            this.btn_parse.Text = "Save and create .mta file";
            this.btn_parse.UseVisualStyleBackColor = true;
            this.btn_parse.Click += new System.EventHandler(this.btn_parse_Click);
            // 
            // txb_objIn
            // 
            this.txb_objIn.Location = new System.Drawing.Point(12, 25);
            this.txb_objIn.Name = "txb_objIn";
            this.txb_objIn.Size = new System.Drawing.Size(299, 20);
            this.txb_objIn.TabIndex = 4;
            // 
            // btn_objAdd
            // 
            this.btn_objAdd.Location = new System.Drawing.Point(236, 51);
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
            this.lb_objFiles.Location = new System.Drawing.Point(339, 25);
            this.lb_objFiles.Name = "lb_objFiles";
            this.lb_objFiles.Size = new System.Drawing.Size(319, 95);
            this.lb_objFiles.TabIndex = 6;
            this.lb_objFiles.DoubleClick += new System.EventHandler(this.lb_objFiles_DoubleClick);
            // 
            // btn_objRemove
            // 
            this.btn_objRemove.Location = new System.Drawing.Point(339, 126);
            this.btn_objRemove.Name = "btn_objRemove";
            this.btn_objRemove.Size = new System.Drawing.Size(75, 23);
            this.btn_objRemove.TabIndex = 7;
            this.btn_objRemove.Text = "Remove";
            this.btn_objRemove.UseVisualStyleBackColor = true;
            this.btn_objRemove.Click += new System.EventHandler(this.btn_objRemove_Click);
            // 
            // btn_BrowseTexture
            // 
            this.btn_BrowseTexture.Location = new System.Drawing.Point(12, 126);
            this.btn_BrowseTexture.Name = "btn_BrowseTexture";
            this.btn_BrowseTexture.Size = new System.Drawing.Size(75, 23);
            this.btn_BrowseTexture.TabIndex = 9;
            this.btn_BrowseTexture.Text = "Browse";
            this.btn_BrowseTexture.UseVisualStyleBackColor = true;
            this.btn_BrowseTexture.Click += new System.EventHandler(this.btn_BrowseTexture_Click);
            // 
            // txb_texture
            // 
            this.txb_texture.Location = new System.Drawing.Point(15, 100);
            this.txb_texture.Name = "txb_texture";
            this.txb_texture.Size = new System.Drawing.Size(296, 20);
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
            this.label3.Location = new System.Drawing.Point(14, 82);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(91, 13);
            this.label3.TabIndex = 12;
            this.label3.Text = "Texture file name:";
            // 
            // lb_Animation
            // 
            this.lb_Animation.FormattingEnabled = true;
            this.lb_Animation.Location = new System.Drawing.Point(339, 189);
            this.lb_Animation.Name = "lb_Animation";
            this.lb_Animation.Size = new System.Drawing.Size(319, 95);
            this.lb_Animation.TabIndex = 13;
            this.lb_Animation.DoubleClick += new System.EventHandler(this.lb_Animation_DoubleClick);
            // 
            // btn_browseOBJ
            // 
            this.btn_browseOBJ.Location = new System.Drawing.Point(12, 51);
            this.btn_browseOBJ.Name = "btn_browseOBJ";
            this.btn_browseOBJ.Size = new System.Drawing.Size(75, 23);
            this.btn_browseOBJ.TabIndex = 14;
            this.btn_browseOBJ.Text = "Browse";
            this.btn_browseOBJ.UseVisualStyleBackColor = true;
            this.btn_browseOBJ.Click += new System.EventHandler(this.btn_browseOBJ_Click);
            // 
            // shapeContainer1
            // 
            this.shapeContainer1.Location = new System.Drawing.Point(0, 0);
            this.shapeContainer1.Margin = new System.Windows.Forms.Padding(0);
            this.shapeContainer1.Name = "shapeContainer1";
            this.shapeContainer1.Shapes.AddRange(new Microsoft.VisualBasic.PowerPacks.Shape[] {
            this.lineShape2,
            this.lineShape1});
            this.shapeContainer1.Size = new System.Drawing.Size(670, 352);
            this.shapeContainer1.TabIndex = 15;
            this.shapeContainer1.TabStop = false;
            // 
            // lineShape2
            // 
            this.lineShape2.Name = "lineShape2";
            this.lineShape2.X1 = 325;
            this.lineShape2.X2 = 325;
            this.lineShape2.Y1 = 0;
            this.lineShape2.Y2 = 350;
            // 
            // lineShape1
            // 
            this.lineShape1.Name = "lineShape1";
            this.lineShape1.X1 = 0;
            this.lineShape1.X2 = 676;
            this.lineShape1.Y1 = 160;
            this.lineShape1.Y2 = 160;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(336, 9);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(51, 13);
            this.label4.TabIndex = 16;
            this.label4.Text = "OBJ files:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(336, 171);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(114, 13);
            this.label5.TabIndex = 17;
            this.label5.Text = "OBJ files for animation:";
            // 
            // btn_createAnimation
            // 
            this.btn_createAnimation.Location = new System.Drawing.Point(339, 321);
            this.btn_createAnimation.Name = "btn_createAnimation";
            this.btn_createAnimation.Size = new System.Drawing.Size(103, 23);
            this.btn_createAnimation.TabIndex = 18;
            this.btn_createAnimation.Text = "Create animation";
            this.btn_createAnimation.UseVisualStyleBackColor = true;
            this.btn_createAnimation.Click += new System.EventHandler(this.btn_createAnimation_Click);
            // 
            // lb_finishedAnimations
            // 
            this.lb_finishedAnimations.FormattingEnabled = true;
            this.lb_finishedAnimations.Location = new System.Drawing.Point(12, 189);
            this.lb_finishedAnimations.Name = "lb_finishedAnimations";
            this.lb_finishedAnimations.Size = new System.Drawing.Size(296, 121);
            this.lb_finishedAnimations.TabIndex = 19;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(11, 171);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(102, 13);
            this.label6.TabIndex = 20;
            this.label6.Text = "Finished animations:";
            // 
            // Num_AnimationTime
            // 
            this.Num_AnimationTime.Location = new System.Drawing.Point(558, 324);
            this.Num_AnimationTime.Name = "Num_AnimationTime";
            this.Num_AnimationTime.Size = new System.Drawing.Size(100, 20);
            this.Num_AnimationTime.TabIndex = 21;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(448, 326);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(104, 13);
            this.label7.TabIndex = 22;
            this.label7.Text = "Animation time (sec):";
            // 
            // txb_animationName
            // 
            this.txb_animationName.Location = new System.Drawing.Point(427, 298);
            this.txb_animationName.Name = "txb_animationName";
            this.txb_animationName.Size = new System.Drawing.Size(231, 20);
            this.txb_animationName.TabIndex = 23;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(336, 298);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(85, 13);
            this.label8.TabIndex = 24;
            this.label8.Text = "Animation name:";
            // 
            // btn_AnimationRemove
            // 
            this.btn_AnimationRemove.Location = new System.Drawing.Point(12, 321);
            this.btn_AnimationRemove.Name = "btn_AnimationRemove";
            this.btn_AnimationRemove.Size = new System.Drawing.Size(75, 23);
            this.btn_AnimationRemove.TabIndex = 25;
            this.btn_AnimationRemove.Text = "Remove";
            this.btn_AnimationRemove.UseVisualStyleBackColor = true;
            this.btn_AnimationRemove.Click += new System.EventHandler(this.btn_AnimationRemove_Click);
            // 
            // MTA_Parser
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(670, 352);
            this.Controls.Add(this.btn_AnimationRemove);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.txb_animationName);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.Num_AnimationTime);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.lb_finishedAnimations);
            this.Controls.Add(this.btn_createAnimation);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.btn_browseOBJ);
            this.Controls.Add(this.lb_Animation);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txb_texture);
            this.Controls.Add(this.btn_BrowseTexture);
            this.Controls.Add(this.btn_objRemove);
            this.Controls.Add(this.lb_objFiles);
            this.Controls.Add(this.btn_objAdd);
            this.Controls.Add(this.txb_objIn);
            this.Controls.Add(this.btn_parse);
            this.Controls.Add(this.shapeContainer1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "MTA_Parser";
            this.Text = "MTA Parser";
            ((System.ComponentModel.ISupportInitialize)(this.Num_AnimationTime)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_parse;
        private System.Windows.Forms.TextBox txb_objIn;
        private System.Windows.Forms.Button btn_objAdd;
        private System.Windows.Forms.ListBox lb_objFiles;
        private System.Windows.Forms.Button btn_objRemove;
        private System.Windows.Forms.Button btn_BrowseTexture;
        private System.Windows.Forms.TextBox txb_texture;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ListBox lb_Animation;
        private System.Windows.Forms.Button btn_browseOBJ;
        private Microsoft.VisualBasic.PowerPacks.ShapeContainer shapeContainer1;
        private Microsoft.VisualBasic.PowerPacks.LineShape lineShape2;
        private Microsoft.VisualBasic.PowerPacks.LineShape lineShape1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button btn_createAnimation;
        private System.Windows.Forms.ListBox lb_finishedAnimations;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown Num_AnimationTime;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txb_animationName;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button btn_AnimationRemove;
    }
}

