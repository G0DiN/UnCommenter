using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace UnComenter
{
    public partial class ReplacerTable : Form
    {
        string defName = "inc";

        public ReplacerTable()
        {
            InitializeComponent();
            table.RowCount = 1;
            table.ColumnCount = 2;
            float withTable = table.Width;


            table.Columns[0].HeaderText = "Первоначальное значение";
            table.Columns[1].HeaderText = "Заменить на";

            table.Columns[0].Width = (int)Math.Round(withTable / 2);
            table.Columns[1].Width = (int)Math.Round(withTable / 2);

            openFileDialog.Filter = "Only *.txt|*.txt";
        }

        private void ReplacerTable_Load(object sender, EventArgs e)
        {
            ReplacerDir.Do_Read_File(true);

            WriteRecordIntable();
        }

        private void WriteRecordIntable()
        {
            int i_line = 0;
            foreach (string line in ReplacerDir.all_Lines_File)
            {
                table.RowCount++;
                string[] words_File = line.Split(new char[] { '|' }, StringSplitOptions.RemoveEmptyEntries);
                string first_Path = words_File[0];

                table[0, i_line].Value = words_File[0].Trim();
                table[1, i_line].Value = (words_File.Length == 1) ?
                    (first_Path.Substring(0, first_Path.LastIndexOf('\\') + 1) + defName + $"{i_line}") :
                    (words_File[1]);

                i_line++;
            }
        }

        private void table_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            int item_Index = table.SelectedCells[0].RowIndex;

            if (item_Index != table.RowCount)
            {
                column1.Text =(table[0,item_Index].Value != null) ? table[0, item_Index].Value.ToString() : "";
                column2.Text =(table[1, item_Index].Value != null) ? table[1, item_Index].Value.ToString() : "";   
            }
        }

        private string dirNotFound = null;
        bool Checking()
        {
            for (int i = 0; i < table.RowCount - 1; i++)
                if (table[0, i].Value == null || table[1, i].Value == null)
                {
                    dirNotFound = $"Директории под номером {i} не существует";
                    return false;
                }

            return true;
        }    


        private void exetenciveBox_TextChanged(object sender, EventArgs e)
        {
            defName = exetenciveBox.Text;
        }

        private void openButton_Click(object sender, EventArgs e)
        {

        }

        private void replaceButton_Click(object sender, EventArgs e)
        {

            for (int i = 0; i < table.RowCount - 1; i++)
            {
                if (table[0, i].Value != null)
                    ReplacerDir.Do_Replace(table[0, i].Value.ToString(), table[1, i].Value.ToString());
            }
        }

        private void replaceOneButton_Click(object sender, EventArgs e)
        {
            if (Checking())
            {
                int item_Index = table.SelectedCells[0].RowIndex;
                if (item_Index != table.RowCount)
                    ReplacerDir.Do_Replace(table[0, item_Index].Value.ToString(), table[1, item_Index].Value.ToString());
            }
            else MessageBox.Show(dirNotFound);
        }

        private void ReplaceNameTwo_Click(object sender, EventArgs e)
        {
                for (int i = 0; i < table.RowCount - 1; i++)
                {
                    if (table[0, i].Value != null)
                    {
                    if (defName == "")  {
                        defName            = "inc";
                        exetenciveBox.Text = "inc";
                    }
                    string row_table = table[0, i].Value.ToString();
                    int l_index = table[0, i].Value.ToString().LastIndexOf('\\') + 1;
                    table[1, i].Value = row_table.Substring(0, l_index) + defName + i.ToString();
                    }
                }
        
        }

        private void OpenFileMenu_Click(object sender, EventArgs e)
        {
            table.RowCount = 1;
            openFileDialog.FileName = null;
            if (openFileDialog.ShowDialog() == DialogResult.Cancel)
                return;
            else {
                string filename = openFileDialog.FileName;
                ReplacerDir.g_fileName = filename;
                ReplacerDir.Do_Read_File(true);

                if (ReplacerDir.s_Message != null)
                    MessageBox.Show(ReplacerDir.s_Message);
                else
                    WriteRecordIntable();
            }
            
        }

        private void OpenFolderMenu_Click(object sender, EventArgs e)
        {
            table.RowCount = 1;
            if (openFolderDialog.ShowDialog() == DialogResult.Cancel)
                return;
            else
            {
                if (Directory.Exists(openFolderDialog.SelectedPath)) {
                    int row_count = 0;
                    foreach (string dir in Directory.GetDirectories(openFolderDialog.SelectedPath))
                    {
                        table.RowCount++;
                        table[0, row_count].Value = dir;
                        row_count++;
                        ReplaceNameTwo_Click(sender, e);
                    }
                }
            }
        }
    }
}
