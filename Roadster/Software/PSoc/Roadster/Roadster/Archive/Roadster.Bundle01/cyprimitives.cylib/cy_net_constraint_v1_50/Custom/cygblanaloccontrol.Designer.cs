namespace Cypress.Components.Primitives.cy_net_constraint_v1_50
{
    partial class CyGlobalAnalogLocationControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private global::System.ComponentModel.IContainer components = null;

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
            this.m_gblAnaLocComboBox = new global::System.Windows.Forms.ComboBox();
            this.label1 = new global::System.Windows.Forms.Label();
            this.m_exclusiveUseChkBx = new global::System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // m_gblAnaLocComboBox
            // 
            this.m_gblAnaLocComboBox.Anchor = ((global::System.Windows.Forms.AnchorStyles)(((global::System.Windows.Forms.AnchorStyles.Top | global::System.Windows.Forms.AnchorStyles.Left)
                        | global::System.Windows.Forms.AnchorStyles.Right)));
            this.m_gblAnaLocComboBox.FormattingEnabled = true;
            this.m_gblAnaLocComboBox.Location = new global::System.Drawing.Point(129, 7);
            this.m_gblAnaLocComboBox.Margin = new global::System.Windows.Forms.Padding(2);
            this.m_gblAnaLocComboBox.Name = "m_gblAnaLocComboBox";
            this.m_gblAnaLocComboBox.Size = new global::System.Drawing.Size(239, 21);
            this.m_gblAnaLocComboBox.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new global::System.Drawing.Point(2, 10);
            this.label1.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new global::System.Drawing.Size(123, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Analog Resource Name:";
            // 
            // m_exclusiveUseChkBx
            // 
            this.m_exclusiveUseChkBx.AutoSize = true;
            this.m_exclusiveUseChkBx.Location = new global::System.Drawing.Point(5, 44);
            this.m_exclusiveUseChkBx.Name = "m_exclusiveUseChkBx";
            this.m_exclusiveUseChkBx.Size = new global::System.Drawing.Size(354, 17);
            this.m_exclusiveUseChkBx.TabIndex = 2;
            this.m_exclusiveUseChkBx.Text = "Reserve resource exclusively. Ensure no other nets use this resource.";
            this.m_exclusiveUseChkBx.UseVisualStyleBackColor = true;
            // 
            // CyGlobalAnalogLocationControl
            // 
            this.AutoScaleDimensions = new global::System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = global::System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_exclusiveUseChkBx);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.m_gblAnaLocComboBox);
            this.Margin = new global::System.Windows.Forms.Padding(2);
            this.Name = "CyGlobalAnalogLocationControl";
            this.Size = new global::System.Drawing.Size(371, 64);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private global::System.Windows.Forms.ComboBox m_gblAnaLocComboBox;
        private global::System.Windows.Forms.Label label1;
        private global::System.Windows.Forms.CheckBox m_exclusiveUseChkBx;
    }
}
