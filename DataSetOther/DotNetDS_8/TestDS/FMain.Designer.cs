namespace TestDS
{
    partial class frmMain
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
            this.tblFiles = new TestDS.tblFiles();
            this.btnDatasetModify = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.tblFiles)).BeginInit();
            this.SuspendLayout();
            // 
            // tblFiles
            // 
            this.tblFiles.DataSetName = "tblFiles";
            this.tblFiles.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // btnDatasetModify
            // 
            this.btnDatasetModify.Location = new System.Drawing.Point(12, 12);
            this.btnDatasetModify.Name = "btnDatasetModify";
            this.btnDatasetModify.Size = new System.Drawing.Size(143, 23);
            this.btnDatasetModify.TabIndex = 0;
            this.btnDatasetModify.Text = "Dataset Modify";
            this.btnDatasetModify.UseVisualStyleBackColor = true;
            this.btnDatasetModify.Click += new System.EventHandler(this.btnDatasetModify_Click);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(537, 195);
            this.Controls.Add(this.btnDatasetModify);
            this.Name = "frmMain";
            this.Text = "Main form";
            ((System.ComponentModel.ISupportInitialize)(this.tblFiles)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private tblFiles tblFiles;
        private System.Windows.Forms.Button btnDatasetModify;
    }
}

