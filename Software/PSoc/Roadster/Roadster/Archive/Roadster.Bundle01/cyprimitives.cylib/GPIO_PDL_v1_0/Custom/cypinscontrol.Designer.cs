namespace Cypress.Comps.PinsAndPorts.GPIO_PDL_v1_0
{
    partial class CyPinsControl
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
            if (disposing)
            {
                PerformDispose();
            }

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
            this.m_toolStrip = new System.Windows.Forms.ToolStrip();
            this.m_splitContainer = new System.Windows.Forms.SplitContainer();
            this.m_splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.m_errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.m_splitContainer)).BeginInit();
            this.m_splitContainer.Panel1.SuspendLayout();
            this.m_splitContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_splitContainer1)).BeginInit();
            this.m_splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // m_toolStrip
            // 
            this.m_toolStrip.Location = new System.Drawing.Point(0, 0);
            this.m_toolStrip.Name = "m_toolStrip";
            this.m_toolStrip.Size = new System.Drawing.Size(621, 25);
            this.m_toolStrip.TabIndex = 1;
            this.m_toolStrip.Text = "toolStrip1";
            // 
            // m_splitContainer
            // 
            this.m_splitContainer.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_splitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_splitContainer.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.m_splitContainer.IsSplitterFixed = true;
            this.m_splitContainer.Location = new System.Drawing.Point(0, 25);
            this.m_splitContainer.MinimumSize = new System.Drawing.Size(0, 270);
            this.m_splitContainer.Name = "m_splitContainer";
            // 
            // m_splitContainer.Panel1
            // 
            this.m_splitContainer.Panel1.Controls.Add(this.m_splitContainer1);
            this.m_splitContainer.Size = new System.Drawing.Size(621, 356);
            this.m_splitContainer.SplitterDistance = 180;
            this.m_splitContainer.TabIndex = 2;
            // 
            // m_splitContainer1
            // 
            this.m_splitContainer1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.m_splitContainer1.IsSplitterFixed = true;
            this.m_splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.m_splitContainer1.Name = "m_splitContainer1";
            this.m_splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.m_splitContainer1.Size = new System.Drawing.Size(180, 356);
            this.m_splitContainer1.SplitterDistance = 261;
            this.m_splitContainer1.TabIndex = 0;
            // 
            // m_errorProvider
            // 
            this.m_errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.m_errorProvider.ContainerControl = this;
            // 
            // CyPinsControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(120F, 120F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.AutoScroll = true;
            this.AutoSize = true;
            this.Controls.Add(this.m_splitContainer);
            this.Controls.Add(this.m_toolStrip);
            this.Name = "CyPinsControl";
            this.Size = new System.Drawing.Size(621, 381);
            this.m_splitContainer.Panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.m_splitContainer)).EndInit();
            this.m_splitContainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.m_splitContainer1)).EndInit();
            this.m_splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }


        #endregion

        private System.Windows.Forms.ToolStrip m_toolStrip;
        private System.Windows.Forms.SplitContainer m_splitContainer;
        private System.Windows.Forms.SplitContainer m_splitContainer1;
        private System.Windows.Forms.ErrorProvider m_errorProvider;


    }
}

