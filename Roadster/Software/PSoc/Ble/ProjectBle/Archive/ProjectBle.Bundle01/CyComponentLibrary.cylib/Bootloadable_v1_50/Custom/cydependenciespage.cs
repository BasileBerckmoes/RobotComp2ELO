/*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.IO;
using System.Windows.Forms;

namespace Bootloadable_v1_50
{
    public partial class CyDependenciesPage : CyEditingWrapperControl
    {
        #region Const
        private const string HEX_FILE_FILTER = "Hex Files (*.hex)|*.hex";
        private const string ELF_FILE_FILTER = "Elf Files (*.elf, .axf, .out)|*.elf;*.axf;*.out|All files (*.*)|*.*";
        private const string ELF_FILE_EXT = ".elf";
        #endregion Const

        #region Constructors
        public CyDependenciesPage()
        {
            InitializeComponent();
        }

        public CyDependenciesPage(CyParameters parameters)
        {
            InitializeComponent();
            m_parameters = parameters;
            InitFields();
        }
        #endregion Constructors

        #region Initialization
        public void InitFields()
        {
            textBoxHexFilePath.Text = m_parameters.HexFilePath;
            textBoxElfFilePath.Text = m_parameters.ElfFilePath;
        }
        #endregion Initialization

        #region TabName override
        public override string TabName
        {
            get { return "Dependencies"; }
        }
        #endregion TabName override

        #region Event handlers
        private void textBoxHexFilePath_TextChanged(object sender, EventArgs e)
        {
            m_parameters.HexFilePath = m_parameters.CreateDesignPersistantPath(textBoxHexFilePath.Text);
        }


        private void textBoxElfFilePath_TextChanged(object sender, EventArgs e)
        {
            m_parameters.ElfFilePath = m_parameters.CreateDesignPersistantPath(textBoxElfFilePath.Text);
        }

        private void buttonBrowse_Click(object sender, EventArgs e)
        {
            bool browseHex = (sender == buttonBrowseHex);
            using (OpenFileDialog openFileDialog1 = new OpenFileDialog())
            {
                string dir = "";
                string activeFileLocation = browseHex ? m_parameters.HexFilePath : m_parameters.ElfFilePath;
                if (!String.IsNullOrEmpty(activeFileLocation) && File.Exists(activeFileLocation))
                {
                    dir = Path.GetDirectoryName(activeFileLocation);
                }
                if (!String.IsNullOrEmpty(dir))
                {
                    openFileDialog1.InitialDirectory = dir;
                }
                if (browseHex)
                {
                    openFileDialog1.Filter = HEX_FILE_FILTER;
                }
                else
                {
                    openFileDialog1.Filter = ELF_FILE_FILTER;
                }
                openFileDialog1.Title = Properties.Resources.OpenFileDialogTitle;
                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    if (browseHex)
                    {
                        textBoxHexFilePath.Text = openFileDialog1.FileName;
                        // If elf file exists in the same folder with hex, automatically fill the elf text box
                        string elfFilePath = Path.ChangeExtension(textBoxHexFilePath.Text, ELF_FILE_EXT);
                        if (File.Exists(elfFilePath))
                        {
                            textBoxElfFilePath.Text = elfFilePath;
                        }
                    }
                    else
                    {
                        textBoxElfFilePath.Text = openFileDialog1.FileName;
                    }
                }
            }
        }

        private void CyDependenciesPage_Load(object sender, EventArgs e)
        {
            // BWC
            if (!String.IsNullOrEmpty(m_parameters.HexFilePath) &&
                (m_parameters.CreateDesignPersistantPath(textBoxHexFilePath.Text) != m_parameters.HexFilePath))
            {
                textBoxHexFilePath_TextChanged(textBoxHexFilePath, EventArgs.Empty);
                textBoxElfFilePath_TextChanged(textBoxElfFilePath, EventArgs.Empty);
            }
        }
        #endregion Event handlers
    }
}
