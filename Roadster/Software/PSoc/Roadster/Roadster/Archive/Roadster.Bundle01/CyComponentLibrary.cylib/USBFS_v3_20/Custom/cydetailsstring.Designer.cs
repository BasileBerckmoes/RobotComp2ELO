namespace USBFS_v3_20
{
    partial class CyDetailsString
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyDetailsString));
            this.groupBoxParams = new System.Windows.Forms.GroupBox();
            this.textBoxString = new System.Windows.Forms.TextBox();
            this.groupBoxOption = new System.Windows.Forms.GroupBox();
            this.wrgUserEnteredTextImg = new System.Windows.Forms.PictureBox();
            this.radioButtonSilicon = new System.Windows.Forms.RadioButton();
            this.radioButtonCallback = new System.Windows.Forms.RadioButton();
            this.radioButtonUser = new System.Windows.Forms.RadioButton();
            this.wrgProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.groupBoxParams.SuspendLayout();
            this.groupBoxOption.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.wrgUserEnteredTextImg)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.wrgProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxParams
            // 
            this.groupBoxParams.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxParams.Controls.Add(this.textBoxString);
            this.groupBoxParams.Location = new System.Drawing.Point(4, 11);
            this.groupBoxParams.Margin = new System.Windows.Forms.Padding(4);
            this.groupBoxParams.Name = "groupBoxParams";
            this.groupBoxParams.Padding = new System.Windows.Forms.Padding(4);
            this.groupBoxParams.Size = new System.Drawing.Size(439, 78);
            this.groupBoxParams.TabIndex = 3;
            this.groupBoxParams.TabStop = false;
            this.groupBoxParams.Text = "String";
            // 
            // textBoxString
            // 
            this.textBoxString.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxString.Location = new System.Drawing.Point(20, 31);
            this.textBoxString.Margin = new System.Windows.Forms.Padding(4);
            this.textBoxString.MaxLength = 253;
            this.textBoxString.Name = "textBoxString";
            this.textBoxString.Size = new System.Drawing.Size(405, 22);
            this.textBoxString.TabIndex = 12;
            this.textBoxString.Validated += new System.EventHandler(this.textBoxString_Validated);
            // 
            // groupBoxOption
            // 
            this.groupBoxOption.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxOption.Controls.Add(this.wrgUserEnteredTextImg);
            this.groupBoxOption.Controls.Add(this.radioButtonSilicon);
            this.groupBoxOption.Controls.Add(this.radioButtonCallback);
            this.groupBoxOption.Controls.Add(this.radioButtonUser);
            this.groupBoxOption.Location = new System.Drawing.Point(4, 96);
            this.groupBoxOption.Margin = new System.Windows.Forms.Padding(4);
            this.groupBoxOption.Name = "groupBoxOption";
            this.groupBoxOption.Padding = new System.Windows.Forms.Padding(4);
            this.groupBoxOption.Size = new System.Drawing.Size(439, 123);
            this.groupBoxOption.TabIndex = 6;
            this.groupBoxOption.TabStop = false;
            this.groupBoxOption.Text = "Type";
            this.groupBoxOption.Visible = false;
            // 
            // wrgUserEnteredTextImg
            // 
            this.wrgUserEnteredTextImg.Image = global::USBFS_v3_20.Properties.Resources.warning;
            this.wrgUserEnteredTextImg.Location = new System.Drawing.Point(152, 23);
            this.wrgUserEnteredTextImg.Margin = new System.Windows.Forms.Padding(0);
            this.wrgUserEnteredTextImg.Name = "wrgUserEnteredTextImg";
            this.wrgUserEnteredTextImg.Size = new System.Drawing.Size(20, 20);
            this.wrgUserEnteredTextImg.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.wrgUserEnteredTextImg.TabIndex = 3;
            this.wrgUserEnteredTextImg.TabStop = false;
            // 
            // radioButtonSilicon
            // 
            this.radioButtonSilicon.AutoSize = true;
            this.radioButtonSilicon.Location = new System.Drawing.Point(8, 80);
            this.radioButtonSilicon.Margin = new System.Windows.Forms.Padding(4);
            this.radioButtonSilicon.Name = "radioButtonSilicon";
            this.radioButtonSilicon.Size = new System.Drawing.Size(236, 21);
            this.radioButtonSilicon.TabIndex = 2;
            this.radioButtonSilicon.Text = "Silicon Generated Serial Number";
            this.radioButtonSilicon.UseVisualStyleBackColor = true;
            this.radioButtonSilicon.CheckedChanged += new System.EventHandler(this.radioButtonUser_CheckedChanged);
            // 
            // radioButtonCallback
            // 
            this.radioButtonCallback.AutoSize = true;
            this.radioButtonCallback.Location = new System.Drawing.Point(8, 52);
            this.radioButtonCallback.Margin = new System.Windows.Forms.Padding(4);
            this.radioButtonCallback.Name = "radioButtonCallback";
            this.radioButtonCallback.Size = new System.Drawing.Size(121, 21);
            this.radioButtonCallback.TabIndex = 1;
            this.radioButtonCallback.Text = "User Call Back";
            this.radioButtonCallback.UseVisualStyleBackColor = true;
            this.radioButtonCallback.CheckedChanged += new System.EventHandler(this.radioButtonUser_CheckedChanged);
            // 
            // radioButtonUser
            // 
            this.radioButtonUser.AutoSize = true;
            this.radioButtonUser.Checked = true;
            this.radioButtonUser.Location = new System.Drawing.Point(8, 23);
            this.radioButtonUser.Margin = new System.Windows.Forms.Padding(4, 4, 0, 4);
            this.radioButtonUser.Name = "radioButtonUser";
            this.radioButtonUser.Size = new System.Drawing.Size(144, 21);
            this.radioButtonUser.TabIndex = 0;
            this.radioButtonUser.TabStop = true;
            this.radioButtonUser.Text = "User Entered Text";
            this.radioButtonUser.UseVisualStyleBackColor = true;
            this.radioButtonUser.CheckedChanged += new System.EventHandler(this.radioButtonUser_CheckedChanged);
            // 
            // wrgProvider
            // 
            this.wrgProvider.BlinkRate = 500;
            this.wrgProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.wrgProvider.ContainerControl = this;
            this.wrgProvider.Icon = ((System.Drawing.Icon)(resources.GetObject("wrgProvider.Icon")));
            // 
            // CyDetailsString
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.groupBoxOption);
            this.Controls.Add(this.groupBoxParams);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "CyDetailsString";
            this.Size = new System.Drawing.Size(447, 229);
            this.Load += new System.EventHandler(this.CyDetailsString_Load);
            this.groupBoxParams.ResumeLayout(false);
            this.groupBoxParams.PerformLayout();
            this.groupBoxOption.ResumeLayout(false);
            this.groupBoxOption.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.wrgUserEnteredTextImg)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.wrgProvider)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxParams;
        private System.Windows.Forms.TextBox textBoxString;
        private System.Windows.Forms.GroupBox groupBoxOption;
        private System.Windows.Forms.RadioButton radioButtonSilicon;
        private System.Windows.Forms.RadioButton radioButtonCallback;
        private System.Windows.Forms.RadioButton radioButtonUser;
        private System.Windows.Forms.ErrorProvider wrgProvider;
        private System.Windows.Forms.PictureBox wrgUserEnteredTextImg;
    }
}
