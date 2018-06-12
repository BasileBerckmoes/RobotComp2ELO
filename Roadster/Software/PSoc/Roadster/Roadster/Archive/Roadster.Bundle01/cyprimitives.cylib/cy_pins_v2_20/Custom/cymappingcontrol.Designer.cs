namespace Cypress.Comps.PinsAndPorts.cy_pins_v2_20
{
    partial class CyMappingControl
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyMappingControl));
            this.m_displayAsBusCheckBox = new System.Windows.Forms.CheckBox();
            this.m_contCheckBox = new System.Windows.Forms.CheckBox();
            this.m_spanningCheckBox = new System.Windows.Forms.CheckBox();
            this.m_displayAsBusDescriptionTxtBox = new System.Windows.Forms.TextBox();
            this.m_contiguousDescriptionTxtBox = new System.Windows.Forms.TextBox();
            this.m_spanningDescriptionTxtBox = new System.Windows.Forms.TextBox();
            this.m_errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_displayAsBusCheckBox
            // 
            this.m_displayAsBusCheckBox.AutoSize = true;
            this.m_displayAsBusCheckBox.Location = new System.Drawing.Point(3, 3);
            this.m_displayAsBusCheckBox.Name = "m_displayAsBusCheckBox";
            this.m_displayAsBusCheckBox.Size = new System.Drawing.Size(122, 21);
            this.m_displayAsBusCheckBox.TabIndex = 0;
            this.m_displayAsBusCheckBox.Text = "Display as bus";
            this.m_displayAsBusCheckBox.UseVisualStyleBackColor = true;
            // 
            // m_contCheckBox
            // 
            this.m_contCheckBox.AutoSize = true;
            this.m_contCheckBox.Location = new System.Drawing.Point(3, 104);
            this.m_contCheckBox.Name = "m_contCheckBox";
            this.m_contCheckBox.Size = new System.Drawing.Size(101, 21);
            this.m_contCheckBox.TabIndex = 1;
            this.m_contCheckBox.Text = "Contiguous";
            this.m_contCheckBox.UseVisualStyleBackColor = true;
            // 
            // m_spanningCheckBox
            // 
            this.m_spanningCheckBox.AutoSize = true;
            this.m_spanningCheckBox.Location = new System.Drawing.Point(3, 186);
            this.m_spanningCheckBox.Name = "m_spanningCheckBox";
            this.m_spanningCheckBox.Size = new System.Drawing.Size(90, 21);
            this.m_spanningCheckBox.TabIndex = 2;
            this.m_spanningCheckBox.Text = "Spanning";
            this.m_spanningCheckBox.UseVisualStyleBackColor = true;
            // 
            // m_displayAsBusDescriptionTxtBox
            // 
            this.m_displayAsBusDescriptionTxtBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_displayAsBusDescriptionTxtBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.m_displayAsBusDescriptionTxtBox.Location = new System.Drawing.Point(25, 30);
            this.m_displayAsBusDescriptionTxtBox.Margin = new System.Windows.Forms.Padding(25, 3, 3, 3);
            this.m_displayAsBusDescriptionTxtBox.Multiline = true;
            this.m_displayAsBusDescriptionTxtBox.Name = "m_displayAsBusDescriptionTxtBox";
            this.m_displayAsBusDescriptionTxtBox.ReadOnly = true;
            this.m_displayAsBusDescriptionTxtBox.Size = new System.Drawing.Size(534, 68);
            this.m_displayAsBusDescriptionTxtBox.TabIndex = 2;
            this.m_displayAsBusDescriptionTxtBox.TabStop = false;
            this.m_displayAsBusDescriptionTxtBox.Text = resources.GetString("m_displayAsBusDescriptionTxtBox.Text");
            // 
            // m_contiguousDescriptionTxtBox
            // 
            this.m_contiguousDescriptionTxtBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_contiguousDescriptionTxtBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.m_contiguousDescriptionTxtBox.Location = new System.Drawing.Point(25, 131);
            this.m_contiguousDescriptionTxtBox.Margin = new System.Windows.Forms.Padding(25, 3, 3, 3);
            this.m_contiguousDescriptionTxtBox.Multiline = true;
            this.m_contiguousDescriptionTxtBox.Name = "m_contiguousDescriptionTxtBox";
            this.m_contiguousDescriptionTxtBox.ReadOnly = true;
            this.m_contiguousDescriptionTxtBox.Size = new System.Drawing.Size(534, 49);
            this.m_contiguousDescriptionTxtBox.TabIndex = 4;
            this.m_contiguousDescriptionTxtBox.TabStop = false;
            this.m_contiguousDescriptionTxtBox.Text = "Forces placement in adjacent physical pins.\r\nPort-level APIs will only be generat" +
                "ed for this instance if it is set to be Contiguous. Per-pin APIs will be globall" +
                "y available either way.";
            // 
            // m_spanningDescriptionTxtBox
            // 
            this.m_spanningDescriptionTxtBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_spanningDescriptionTxtBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.m_spanningDescriptionTxtBox.Location = new System.Drawing.Point(25, 213);
            this.m_spanningDescriptionTxtBox.Margin = new System.Windows.Forms.Padding(25, 3, 3, 3);
            this.m_spanningDescriptionTxtBox.Multiline = true;
            this.m_spanningDescriptionTxtBox.Name = "m_spanningDescriptionTxtBox";
            this.m_spanningDescriptionTxtBox.ReadOnly = true;
            this.m_spanningDescriptionTxtBox.Size = new System.Drawing.Size(534, 53);
            this.m_spanningDescriptionTxtBox.TabIndex = 5;
            this.m_spanningDescriptionTxtBox.TabStop = false;
            this.m_spanningDescriptionTxtBox.Text = "Allows placement in multiple physical ports.\r\nNote: Spanning is currently configu" +
                "red based on the Contiguous setting. This will not be the case in the future.";
            // 
            // m_errorProvider
            // 
            this.m_errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.m_errorProvider.ContainerControl = this;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.AutoScroll = true;
            this.tableLayoutPanel1.AutoSize = true;
            this.tableLayoutPanel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.Controls.Add(this.m_spanningDescriptionTxtBox, 0, 5);
            this.tableLayoutPanel1.Controls.Add(this.m_displayAsBusDescriptionTxtBox, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_spanningCheckBox, 0, 4);
            this.tableLayoutPanel1.Controls.Add(this.m_contiguousDescriptionTxtBox, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.m_contCheckBox, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.m_displayAsBusCheckBox, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 6;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.Size = new System.Drawing.Size(562, 271);
            this.tableLayoutPanel1.TabIndex = 6;
            // 
            // CyMappingControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "CyMappingControl";
            this.Size = new System.Drawing.Size(562, 271);
            ((System.ComponentModel.ISupportInitialize)(this.m_errorProvider)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox m_displayAsBusCheckBox;
        private System.Windows.Forms.CheckBox m_contCheckBox;
        private System.Windows.Forms.CheckBox m_spanningCheckBox;
        private System.Windows.Forms.TextBox m_displayAsBusDescriptionTxtBox;
        private System.Windows.Forms.TextBox m_contiguousDescriptionTxtBox;
        private System.Windows.Forms.TextBox m_spanningDescriptionTxtBox;
        private System.Windows.Forms.ErrorProvider m_errorProvider;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
    }
}
