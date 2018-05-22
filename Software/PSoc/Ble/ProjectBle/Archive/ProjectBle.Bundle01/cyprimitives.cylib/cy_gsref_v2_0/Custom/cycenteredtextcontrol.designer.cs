namespace Cypress.Components.System.cy_gsref_v2_0
{
    partial class CyCenteredTextControl
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
            this.tableLayoutPanel1 = new global::System.Windows.Forms.TableLayoutPanel();
            this.m_messageLabel = new global::System.Windows.Forms.Label();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 3;
            this.tableLayoutPanel1.ColumnStyles.Add(new global::System.Windows.Forms.ColumnStyle(global::System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new global::System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new global::System.Windows.Forms.ColumnStyle(global::System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.m_messageLabel, 1, 1);
            this.tableLayoutPanel1.Dock = global::System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new global::System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new global::System.Windows.Forms.Padding(0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new global::System.Windows.Forms.RowStyle(global::System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new global::System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new global::System.Windows.Forms.RowStyle(global::System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Size = new global::System.Drawing.Size(304, 253);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // m_messageLabel
            // 
            this.m_messageLabel.Anchor = global::System.Windows.Forms.AnchorStyles.None;
            this.m_messageLabel.AutoEllipsis = true;
            this.m_messageLabel.AutoSize = true;
            this.m_messageLabel.BackColor = global::System.Drawing.Color.Transparent;
            this.m_messageLabel.Font = new global::System.Drawing.Font("Microsoft Sans Serif", 12F, global::System.Drawing.FontStyle.Regular, global::System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_messageLabel.Location = new global::System.Drawing.Point(120, 114);
            this.m_messageLabel.Name = "m_messageLabel";
            this.m_messageLabel.Size = new global::System.Drawing.Size(64, 25);
            this.m_messageLabel.TabIndex = 0;
            this.m_messageLabel.Text = "label1";
            this.m_messageLabel.TextAlign = global::System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // CyCenteredTextControl
            // 
            this.AutoScaleDimensions = new global::System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = global::System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "CyCenteredTextControl";
            this.Size = new global::System.Drawing.Size(304, 253);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private global::System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private global::System.Windows.Forms.Label m_messageLabel;
    }
}
