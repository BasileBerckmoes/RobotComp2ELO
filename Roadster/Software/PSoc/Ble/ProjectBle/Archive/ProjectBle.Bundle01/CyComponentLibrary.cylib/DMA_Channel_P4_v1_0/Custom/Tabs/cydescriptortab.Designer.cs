/*******************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

namespace DMA_Channel_P4_v1_0.Tabs
{
    partial class CyDescriptorTab
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyDescriptorTab));
            this.m_groupBoxDataElementSize = new System.Windows.Forms.GroupBox();
            this.m_rbWord = new System.Windows.Forms.RadioButton();
            this.m_rbHalfword = new System.Windows.Forms.RadioButton();
            this.m_rbByte = new System.Windows.Forms.RadioButton();
            this.m_groupBoxSourceandDestinationTransferWidth = new System.Windows.Forms.GroupBox();
            this.m_rbWordToWord = new System.Windows.Forms.RadioButton();
            this.m_rbWordToElement = new System.Windows.Forms.RadioButton();
            this.m_rbElementToWord = new System.Windows.Forms.RadioButton();
            this.m_rbElementToElement = new System.Windows.Forms.RadioButton();
            this.m_cbIncDestinetionAddr = new System.Windows.Forms.CheckBox();
            this.m_cbIncSourceAddr = new System.Windows.Forms.CheckBox();
            this.m_pbSourceAndDestTransWidth = new System.Windows.Forms.PictureBox();
            this.m_groupBoxTriggerType = new System.Windows.Forms.GroupBox();
            this.m_rbPulseUnknown = new System.Windows.Forms.RadioButton();
            this.m_rbSensitiveWat8 = new System.Windows.Forms.RadioButton();
            this.m_rbSensitiveWat4 = new System.Windows.Forms.RadioButton();
            this.m_rbPulseStandart = new System.Windows.Forms.RadioButton();
            this.m_groupBoxTransferMode = new System.Windows.Forms.GroupBox();
            this.m_cbDescriptorIsPreemptable = new System.Windows.Forms.CheckBox();
            this.m_rbEntierDescriptorChain = new System.Windows.Forms.RadioButton();
            this.m_rbEntierDescriptor = new System.Windows.Forms.RadioButton();
            this.m_rbSingleDataElement = new System.Windows.Forms.RadioButton();
            this.m_groupBoxPostDescriptorActions = new System.Windows.Forms.GroupBox();
            this.m_cbGenerateInterruptRequest = new System.Windows.Forms.CheckBox();
            this.m_cbInvalidateDescriptor = new System.Windows.Forms.CheckBox();
            this.m_cbChainToDescriptor = new System.Windows.Forms.CheckBox();
            this.m_lblNumberOfDataElements = new System.Windows.Forms.Label();
            this.m_numOfDataElementsToTranfer = new System.Windows.Forms.NumericUpDown();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.m_groupBoxDataElementSize.SuspendLayout();
            this.m_groupBoxSourceandDestinationTransferWidth.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_pbSourceAndDestTransWidth)).BeginInit();
            this.m_groupBoxTriggerType.SuspendLayout();
            this.m_groupBoxTransferMode.SuspendLayout();
            this.m_groupBoxPostDescriptorActions.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOfDataElementsToTranfer)).BeginInit();
            this.flowLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_groupBoxDataElementSize
            // 
            this.m_groupBoxDataElementSize.Controls.Add(this.m_rbWord);
            this.m_groupBoxDataElementSize.Controls.Add(this.m_rbHalfword);
            this.m_groupBoxDataElementSize.Controls.Add(this.m_rbByte);
            resources.ApplyResources(this.m_groupBoxDataElementSize, "m_groupBoxDataElementSize");
            this.m_groupBoxDataElementSize.Name = "m_groupBoxDataElementSize";
            this.m_groupBoxDataElementSize.TabStop = false;
            // 
            // m_rbWord
            // 
            resources.ApplyResources(this.m_rbWord, "m_rbWord");
            this.m_rbWord.Name = "m_rbWord";
            this.m_rbWord.TabStop = true;
            this.m_rbWord.UseVisualStyleBackColor = true;
            // 
            // m_rbHalfword
            // 
            resources.ApplyResources(this.m_rbHalfword, "m_rbHalfword");
            this.m_rbHalfword.Name = "m_rbHalfword";
            this.m_rbHalfword.TabStop = true;
            this.m_rbHalfword.UseVisualStyleBackColor = true;
            // 
            // m_rbByte
            // 
            resources.ApplyResources(this.m_rbByte, "m_rbByte");
            this.m_rbByte.Name = "m_rbByte";
            this.m_rbByte.TabStop = true;
            this.m_rbByte.UseVisualStyleBackColor = true;
            // 
            // m_groupBoxSourceandDestinationTransferWidth
            // 
            this.m_groupBoxSourceandDestinationTransferWidth.Controls.Add(this.m_rbWordToWord);
            this.m_groupBoxSourceandDestinationTransferWidth.Controls.Add(this.m_rbWordToElement);
            this.m_groupBoxSourceandDestinationTransferWidth.Controls.Add(this.m_rbElementToWord);
            this.m_groupBoxSourceandDestinationTransferWidth.Controls.Add(this.m_rbElementToElement);
            this.m_groupBoxSourceandDestinationTransferWidth.Controls.Add(this.m_cbIncDestinetionAddr);
            this.m_groupBoxSourceandDestinationTransferWidth.Controls.Add(this.m_cbIncSourceAddr);
            this.m_groupBoxSourceandDestinationTransferWidth.Controls.Add(this.m_pbSourceAndDestTransWidth);
            resources.ApplyResources(this.m_groupBoxSourceandDestinationTransferWidth, "m_groupBoxSourceandDestinationTransferWidth");
            this.m_groupBoxSourceandDestinationTransferWidth.Name = "m_groupBoxSourceandDestinationTransferWidth";
            this.m_groupBoxSourceandDestinationTransferWidth.TabStop = false;
            // 
            // m_rbWordToWord
            // 
            resources.ApplyResources(this.m_rbWordToWord, "m_rbWordToWord");
            this.m_rbWordToWord.Name = "m_rbWordToWord";
            this.m_rbWordToWord.TabStop = true;
            this.m_rbWordToWord.UseVisualStyleBackColor = true;
            // 
            // m_rbWordToElement
            // 
            resources.ApplyResources(this.m_rbWordToElement, "m_rbWordToElement");
            this.m_rbWordToElement.Name = "m_rbWordToElement";
            this.m_rbWordToElement.TabStop = true;
            this.m_rbWordToElement.UseVisualStyleBackColor = true;
            // 
            // m_rbElementToWord
            // 
            resources.ApplyResources(this.m_rbElementToWord, "m_rbElementToWord");
            this.m_rbElementToWord.Name = "m_rbElementToWord";
            this.m_rbElementToWord.TabStop = true;
            this.m_rbElementToWord.UseVisualStyleBackColor = true;
            // 
            // m_rbElementToElement
            // 
            resources.ApplyResources(this.m_rbElementToElement, "m_rbElementToElement");
            this.m_rbElementToElement.Name = "m_rbElementToElement";
            this.m_rbElementToElement.TabStop = true;
            this.m_rbElementToElement.UseVisualStyleBackColor = true;
            // 
            // m_cbIncDestinetionAddr
            // 
            resources.ApplyResources(this.m_cbIncDestinetionAddr, "m_cbIncDestinetionAddr");
            this.m_cbIncDestinetionAddr.Name = "m_cbIncDestinetionAddr";
            this.m_cbIncDestinetionAddr.UseVisualStyleBackColor = true;
            // 
            // m_cbIncSourceAddr
            // 
            resources.ApplyResources(this.m_cbIncSourceAddr, "m_cbIncSourceAddr");
            this.m_cbIncSourceAddr.Name = "m_cbIncSourceAddr";
            this.m_cbIncSourceAddr.UseVisualStyleBackColor = true;
            // 
            // m_pbSourceAndDestTransWidth
            // 
            resources.ApplyResources(this.m_pbSourceAndDestTransWidth, "m_pbSourceAndDestTransWidth");
            this.m_pbSourceAndDestTransWidth.Name = "m_pbSourceAndDestTransWidth";
            this.m_pbSourceAndDestTransWidth.TabStop = false;
            // 
            // m_groupBoxTriggerType
            // 
            this.m_groupBoxTriggerType.Controls.Add(this.m_rbPulseUnknown);
            this.m_groupBoxTriggerType.Controls.Add(this.m_rbSensitiveWat8);
            this.m_groupBoxTriggerType.Controls.Add(this.m_rbSensitiveWat4);
            this.m_groupBoxTriggerType.Controls.Add(this.m_rbPulseStandart);
            resources.ApplyResources(this.m_groupBoxTriggerType, "m_groupBoxTriggerType");
            this.m_groupBoxTriggerType.Name = "m_groupBoxTriggerType";
            this.m_groupBoxTriggerType.TabStop = false;
            // 
            // m_rbPulseUnknown
            // 
            resources.ApplyResources(this.m_rbPulseUnknown, "m_rbPulseUnknown");
            this.m_rbPulseUnknown.Name = "m_rbPulseUnknown";
            this.m_rbPulseUnknown.TabStop = true;
            this.m_rbPulseUnknown.UseVisualStyleBackColor = true;
            // 
            // m_rbSensitiveWat8
            // 
            resources.ApplyResources(this.m_rbSensitiveWat8, "m_rbSensitiveWat8");
            this.m_rbSensitiveWat8.Name = "m_rbSensitiveWat8";
            this.m_rbSensitiveWat8.TabStop = true;
            this.m_rbSensitiveWat8.UseVisualStyleBackColor = true;
            // 
            // m_rbSensitiveWat4
            // 
            resources.ApplyResources(this.m_rbSensitiveWat4, "m_rbSensitiveWat4");
            this.m_rbSensitiveWat4.Name = "m_rbSensitiveWat4";
            this.m_rbSensitiveWat4.TabStop = true;
            this.m_rbSensitiveWat4.UseVisualStyleBackColor = true;
            // 
            // m_rbPulseStandart
            // 
            resources.ApplyResources(this.m_rbPulseStandart, "m_rbPulseStandart");
            this.m_rbPulseStandart.Name = "m_rbPulseStandart";
            this.m_rbPulseStandart.TabStop = true;
            this.m_rbPulseStandart.UseVisualStyleBackColor = true;
            // 
            // m_groupBoxTransferMode
            // 
            this.m_groupBoxTransferMode.Controls.Add(this.m_cbDescriptorIsPreemptable);
            this.m_groupBoxTransferMode.Controls.Add(this.m_rbEntierDescriptorChain);
            this.m_groupBoxTransferMode.Controls.Add(this.m_rbEntierDescriptor);
            this.m_groupBoxTransferMode.Controls.Add(this.m_rbSingleDataElement);
            resources.ApplyResources(this.m_groupBoxTransferMode, "m_groupBoxTransferMode");
            this.m_groupBoxTransferMode.Name = "m_groupBoxTransferMode";
            this.m_groupBoxTransferMode.TabStop = false;
            // 
            // m_cbDescriptorIsPreemptable
            // 
            resources.ApplyResources(this.m_cbDescriptorIsPreemptable, "m_cbDescriptorIsPreemptable");
            this.m_cbDescriptorIsPreemptable.Name = "m_cbDescriptorIsPreemptable";
            this.m_cbDescriptorIsPreemptable.UseVisualStyleBackColor = true;
            // 
            // m_rbEntierDescriptorChain
            // 
            resources.ApplyResources(this.m_rbEntierDescriptorChain, "m_rbEntierDescriptorChain");
            this.m_rbEntierDescriptorChain.Name = "m_rbEntierDescriptorChain";
            this.m_rbEntierDescriptorChain.TabStop = true;
            this.m_rbEntierDescriptorChain.UseVisualStyleBackColor = true;
            // 
            // m_rbEntierDescriptor
            // 
            resources.ApplyResources(this.m_rbEntierDescriptor, "m_rbEntierDescriptor");
            this.m_rbEntierDescriptor.Name = "m_rbEntierDescriptor";
            this.m_rbEntierDescriptor.TabStop = true;
            this.m_rbEntierDescriptor.UseVisualStyleBackColor = true;
            // 
            // m_rbSingleDataElement
            // 
            resources.ApplyResources(this.m_rbSingleDataElement, "m_rbSingleDataElement");
            this.m_rbSingleDataElement.Name = "m_rbSingleDataElement";
            this.m_rbSingleDataElement.TabStop = true;
            this.m_rbSingleDataElement.UseVisualStyleBackColor = true;
            // 
            // m_groupBoxPostDescriptorActions
            // 
            this.m_groupBoxPostDescriptorActions.Controls.Add(this.m_cbGenerateInterruptRequest);
            this.m_groupBoxPostDescriptorActions.Controls.Add(this.m_cbInvalidateDescriptor);
            this.m_groupBoxPostDescriptorActions.Controls.Add(this.m_cbChainToDescriptor);
            resources.ApplyResources(this.m_groupBoxPostDescriptorActions, "m_groupBoxPostDescriptorActions");
            this.m_groupBoxPostDescriptorActions.Name = "m_groupBoxPostDescriptorActions";
            this.m_groupBoxPostDescriptorActions.TabStop = false;
            // 
            // m_cbGenerateInterruptRequest
            // 
            resources.ApplyResources(this.m_cbGenerateInterruptRequest, "m_cbGenerateInterruptRequest");
            this.m_cbGenerateInterruptRequest.Name = "m_cbGenerateInterruptRequest";
            this.m_cbGenerateInterruptRequest.UseVisualStyleBackColor = true;
            // 
            // m_cbInvalidateDescriptor
            // 
            resources.ApplyResources(this.m_cbInvalidateDescriptor, "m_cbInvalidateDescriptor");
            this.m_cbInvalidateDescriptor.Name = "m_cbInvalidateDescriptor";
            this.m_cbInvalidateDescriptor.UseVisualStyleBackColor = true;
            // 
            // m_cbChainToDescriptor
            // 
            resources.ApplyResources(this.m_cbChainToDescriptor, "m_cbChainToDescriptor");
            this.m_cbChainToDescriptor.Name = "m_cbChainToDescriptor";
            this.m_cbChainToDescriptor.UseVisualStyleBackColor = true;
            // 
            // m_lblNumberOfDataElements
            // 
            resources.ApplyResources(this.m_lblNumberOfDataElements, "m_lblNumberOfDataElements");
            this.m_lblNumberOfDataElements.AutoEllipsis = true;
            this.m_lblNumberOfDataElements.Name = "m_lblNumberOfDataElements";
            // 
            // m_numOfDataElementsToTranfer
            // 
            resources.ApplyResources(this.m_numOfDataElementsToTranfer, "m_numOfDataElementsToTranfer");
            this.m_numOfDataElementsToTranfer.Maximum = new decimal(new int[] {
            1410065407,
            2,
            0,
            0});
            this.m_numOfDataElementsToTranfer.Name = "m_numOfDataElementsToTranfer";
            this.m_numOfDataElementsToTranfer.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Controls.Add(this.m_lblNumberOfDataElements);
            this.flowLayoutPanel1.Controls.Add(this.m_numOfDataElementsToTranfer);
            resources.ApplyResources(this.flowLayoutPanel1, "flowLayoutPanel1");
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            // 
            // CyDescriptorTab
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.flowLayoutPanel1);
            this.Controls.Add(this.m_groupBoxPostDescriptorActions);
            this.Controls.Add(this.m_groupBoxTriggerType);
            this.Controls.Add(this.m_groupBoxTransferMode);
            this.Controls.Add(this.m_groupBoxSourceandDestinationTransferWidth);
            this.Controls.Add(this.m_groupBoxDataElementSize);
            this.Name = "CyDescriptorTab";
            this.m_groupBoxDataElementSize.ResumeLayout(false);
            this.m_groupBoxDataElementSize.PerformLayout();
            this.m_groupBoxSourceandDestinationTransferWidth.ResumeLayout(false);
            this.m_groupBoxSourceandDestinationTransferWidth.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_pbSourceAndDestTransWidth)).EndInit();
            this.m_groupBoxTriggerType.ResumeLayout(false);
            this.m_groupBoxTriggerType.PerformLayout();
            this.m_groupBoxTransferMode.ResumeLayout(false);
            this.m_groupBoxTransferMode.PerformLayout();
            this.m_groupBoxPostDescriptorActions.ResumeLayout(false);
            this.m_groupBoxPostDescriptorActions.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOfDataElementsToTranfer)).EndInit();
            this.flowLayoutPanel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_groupBoxDataElementSize;
        private System.Windows.Forms.GroupBox m_groupBoxSourceandDestinationTransferWidth;
        private System.Windows.Forms.GroupBox m_groupBoxTriggerType;
        private System.Windows.Forms.GroupBox m_groupBoxTransferMode;
        private System.Windows.Forms.GroupBox m_groupBoxPostDescriptorActions;
        private System.Windows.Forms.RadioButton m_rbWord;
        private System.Windows.Forms.RadioButton m_rbHalfword;
        private System.Windows.Forms.RadioButton m_rbByte;
        private System.Windows.Forms.CheckBox m_cbIncDestinetionAddr;
        private System.Windows.Forms.CheckBox m_cbIncSourceAddr;
        private System.Windows.Forms.RadioButton m_rbWordToWord;
        private System.Windows.Forms.RadioButton m_rbWordToElement;
        private System.Windows.Forms.RadioButton m_rbElementToWord;
        private System.Windows.Forms.RadioButton m_rbElementToElement;
        private System.Windows.Forms.RadioButton m_rbPulseUnknown;
        private System.Windows.Forms.RadioButton m_rbSensitiveWat8;
        private System.Windows.Forms.RadioButton m_rbSensitiveWat4;
        private System.Windows.Forms.RadioButton m_rbPulseStandart;
        private System.Windows.Forms.RadioButton m_rbEntierDescriptorChain;
        private System.Windows.Forms.RadioButton m_rbEntierDescriptor;
        private System.Windows.Forms.RadioButton m_rbSingleDataElement;
        private System.Windows.Forms.CheckBox m_cbDescriptorIsPreemptable;
        private System.Windows.Forms.CheckBox m_cbGenerateInterruptRequest;
        private System.Windows.Forms.CheckBox m_cbInvalidateDescriptor;
        private System.Windows.Forms.CheckBox m_cbChainToDescriptor;
        private System.Windows.Forms.Label m_lblNumberOfDataElements;
        private System.Windows.Forms.NumericUpDown m_numOfDataElementsToTranfer;
        private System.Windows.Forms.PictureBox m_pbSourceAndDestTransWidth;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;

    }
}