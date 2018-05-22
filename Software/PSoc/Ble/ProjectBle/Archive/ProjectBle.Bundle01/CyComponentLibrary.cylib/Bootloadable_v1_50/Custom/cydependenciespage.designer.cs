namespace Bootloadable_v1_50
{
    partial class CyDependenciesPage
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyDependenciesPage));
            this.labelInfo = new System.Windows.Forms.Label();
            this.labelHexFile = new System.Windows.Forms.Label();
            this.textBoxHexFilePath = new System.Windows.Forms.TextBox();
            this.buttonBrowseHex = new System.Windows.Forms.Button();
            this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.buttonBrowseElf = new System.Windows.Forms.Button();
            this.textBoxElfFilePath = new System.Windows.Forms.TextBox();
            this.labelElfFile = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // labelInfo
            // 
            resources.ApplyResources(this.labelInfo, "labelInfo");
            this.labelInfo.Name = "labelInfo";
            // 
            // labelHexFile
            // 
            resources.ApplyResources(this.labelHexFile, "labelHexFile");
            this.labelHexFile.Name = "labelHexFile";
            // 
            // textBoxHexFilePath
            // 
            resources.ApplyResources(this.textBoxHexFilePath, "textBoxHexFilePath");
            this.textBoxHexFilePath.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Suggest;
            this.textBoxHexFilePath.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.FileSystem;
            this.textBoxHexFilePath.Name = "textBoxHexFilePath";
            this.textBoxHexFilePath.TextChanged += new System.EventHandler(this.textBoxHexFilePath_TextChanged);
            // 
            // buttonBrowseHex
            // 
            resources.ApplyResources(this.buttonBrowseHex, "buttonBrowseHex");
            this.buttonBrowseHex.Name = "buttonBrowseHex";
            this.buttonBrowseHex.UseVisualStyleBackColor = true;
            this.buttonBrowseHex.Click += new System.EventHandler(this.buttonBrowse_Click);
            // 
            // errorProvider
            // 
            this.errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errorProvider.ContainerControl = this;
            // 
            // buttonBrowseElf
            // 
            resources.ApplyResources(this.buttonBrowseElf, "buttonBrowseElf");
            this.buttonBrowseElf.Name = "buttonBrowseElf";
            this.buttonBrowseElf.UseVisualStyleBackColor = true;
            this.buttonBrowseElf.Click += new System.EventHandler(this.buttonBrowse_Click);
            // 
            // textBoxElfFilePath
            // 
            resources.ApplyResources(this.textBoxElfFilePath, "textBoxElfFilePath");
            this.textBoxElfFilePath.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Suggest;
            this.textBoxElfFilePath.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.FileSystem;
            this.textBoxElfFilePath.Name = "textBoxElfFilePath";
            this.textBoxElfFilePath.TextChanged += new System.EventHandler(this.textBoxElfFilePath_TextChanged);
            // 
            // labelElfFile
            // 
            resources.ApplyResources(this.labelElfFile, "labelElfFile");
            this.labelElfFile.Name = "labelElfFile";
            // 
            // CyDependenciesPage
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.buttonBrowseElf);
            this.Controls.Add(this.textBoxElfFilePath);
            this.Controls.Add(this.labelElfFile);
            this.Controls.Add(this.buttonBrowseHex);
            this.Controls.Add(this.textBoxHexFilePath);
            this.Controls.Add(this.labelHexFile);
            this.Controls.Add(this.labelInfo);
            this.Name = "CyDependenciesPage";
            this.Load += new System.EventHandler(this.CyDependenciesPage_Load);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelInfo;
        private System.Windows.Forms.Label labelHexFile;
        private System.Windows.Forms.TextBox textBoxHexFilePath;
        private System.Windows.Forms.Button buttonBrowseHex;
        private System.Windows.Forms.ErrorProvider errorProvider;
        private System.Windows.Forms.Button buttonBrowseElf;
        private System.Windows.Forms.TextBox textBoxElfFilePath;
        private System.Windows.Forms.Label labelElfFile;
    }
}
