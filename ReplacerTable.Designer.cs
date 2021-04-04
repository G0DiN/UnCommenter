namespace UnComenter
{
    partial class ReplacerTable
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
            this.table = new System.Windows.Forms.DataGridView();
            this.column1 = new System.Windows.Forms.TextBox();
            this.column2 = new System.Windows.Forms.TextBox();
            this.Col1 = new System.Windows.Forms.Label();
            this.Col2 = new System.Windows.Forms.Label();
            this.replaceButton = new System.Windows.Forms.Button();
            this.replaceOneButton = new System.Windows.Forms.Button();
            this.exetenciveBox = new System.Windows.Forms.TextBox();
            this.lab_Default_name = new System.Windows.Forms.Label();
            this.ReplaceNameTwo = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.файлToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFile = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.openFolderMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.openFolderDialog = new System.Windows.Forms.FolderBrowserDialog();
            ((System.ComponentModel.ISupportInitialize)(this.table)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // table
            // 
            this.table.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.table.Location = new System.Drawing.Point(187, 77);
            this.table.Name = "table";
            this.table.Size = new System.Drawing.Size(840, 399);
            this.table.TabIndex = 0;
            this.table.CellMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.table_CellMouseClick);
            // 
            // column1
            // 
            this.column1.Location = new System.Drawing.Point(187, 496);
            this.column1.Multiline = true;
            this.column1.Name = "column1";
            this.column1.Size = new System.Drawing.Size(420, 74);
            this.column1.TabIndex = 1;
            // 
            // column2
            // 
            this.column2.Location = new System.Drawing.Point(606, 496);
            this.column2.Multiline = true;
            this.column2.Name = "column2";
            this.column2.Size = new System.Drawing.Size(420, 74);
            this.column2.TabIndex = 2;
            // 
            // Col1
            // 
            this.Col1.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.Col1.Location = new System.Drawing.Point(187, 478);
            this.Col1.Name = "Col1";
            this.Col1.Size = new System.Drawing.Size(420, 19);
            this.Col1.TabIndex = 3;
            this.Col1.Text = "Столбец 1";
            // 
            // Col2
            // 
            this.Col2.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.Col2.Location = new System.Drawing.Point(606, 478);
            this.Col2.Name = "Col2";
            this.Col2.Size = new System.Drawing.Size(420, 19);
            this.Col2.TabIndex = 4;
            this.Col2.Text = "Столбец 2";
            // 
            // replaceButton
            // 
            this.replaceButton.BackColor = System.Drawing.SystemColors.Window;
            this.replaceButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.replaceButton.FlatAppearance.BorderColor = System.Drawing.Color.DarkSlateGray;
            this.replaceButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.replaceButton.Font = new System.Drawing.Font("Verdana", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.replaceButton.ForeColor = System.Drawing.Color.Black;
            this.replaceButton.Location = new System.Drawing.Point(-1, 77);
            this.replaceButton.Margin = new System.Windows.Forms.Padding(2);
            this.replaceButton.Name = "replaceButton";
            this.replaceButton.Size = new System.Drawing.Size(189, 61);
            this.replaceButton.TabIndex = 7;
            this.replaceButton.Text = "Заменить все";
            this.replaceButton.UseVisualStyleBackColor = false;
            this.replaceButton.Click += new System.EventHandler(this.replaceButton_Click);
            // 
            // replaceOneButton
            // 
            this.replaceOneButton.BackColor = System.Drawing.SystemColors.Window;
            this.replaceOneButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.replaceOneButton.FlatAppearance.BorderColor = System.Drawing.Color.DarkSlateGray;
            this.replaceOneButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.replaceOneButton.Font = new System.Drawing.Font("Verdana", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.replaceOneButton.ForeColor = System.Drawing.Color.Black;
            this.replaceOneButton.Location = new System.Drawing.Point(-1, 137);
            this.replaceOneButton.Margin = new System.Windows.Forms.Padding(2);
            this.replaceOneButton.Name = "replaceOneButton";
            this.replaceOneButton.Size = new System.Drawing.Size(189, 61);
            this.replaceOneButton.TabIndex = 8;
            this.replaceOneButton.Text = "Заменить выбранную строку";
            this.replaceOneButton.UseVisualStyleBackColor = false;
            this.replaceOneButton.Click += new System.EventHandler(this.replaceOneButton_Click);
            // 
            // exetenciveBox
            // 
            this.exetenciveBox.Font = new System.Drawing.Font("Verdana", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.exetenciveBox.Location = new System.Drawing.Point(733, 43);
            this.exetenciveBox.MaxLength = 20;
            this.exetenciveBox.Multiline = true;
            this.exetenciveBox.Name = "exetenciveBox";
            this.exetenciveBox.Size = new System.Drawing.Size(200, 32);
            this.exetenciveBox.TabIndex = 10;
            this.exetenciveBox.Text = "inc";
            this.exetenciveBox.TextChanged += new System.EventHandler(this.exetenciveBox_TextChanged);
            // 
            // lab_Default_name
            // 
            this.lab_Default_name.BackColor = System.Drawing.Color.DarkSlateGray;
            this.lab_Default_name.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lab_Default_name.ForeColor = System.Drawing.Color.White;
            this.lab_Default_name.Location = new System.Drawing.Point(730, 25);
            this.lab_Default_name.Name = "lab_Default_name";
            this.lab_Default_name.Size = new System.Drawing.Size(122, 18);
            this.lab_Default_name.TabIndex = 11;
            this.lab_Default_name.Text = "Имя по умолчанию";
            // 
            // ReplaceNameTwo
            // 
            this.ReplaceNameTwo.BackColor = System.Drawing.SystemColors.Menu;
            this.ReplaceNameTwo.Cursor = System.Windows.Forms.Cursors.Hand;
            this.ReplaceNameTwo.FlatAppearance.BorderColor = System.Drawing.Color.DarkSlateGray;
            this.ReplaceNameTwo.FlatAppearance.BorderSize = 0;
            this.ReplaceNameTwo.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.ReplaceNameTwo.Font = new System.Drawing.Font("Verdana", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ReplaceNameTwo.ForeColor = System.Drawing.Color.Black;
            this.ReplaceNameTwo.Location = new System.Drawing.Point(932, 44);
            this.ReplaceNameTwo.Margin = new System.Windows.Forms.Padding(2);
            this.ReplaceNameTwo.Name = "ReplaceNameTwo";
            this.ReplaceNameTwo.Size = new System.Drawing.Size(82, 30);
            this.ReplaceNameTwo.TabIndex = 12;
            this.ReplaceNameTwo.Text = "замена";
            this.ReplaceNameTwo.UseVisualStyleBackColor = false;
            this.ReplaceNameTwo.Click += new System.EventHandler(this.ReplaceNameTwo_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.файлToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1025, 24);
            this.menuStrip1.TabIndex = 13;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // файлToolStripMenuItem
            // 
            this.файлToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openFile});
            this.файлToolStripMenuItem.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.файлToolStripMenuItem.Name = "файлToolStripMenuItem";
            this.файлToolStripMenuItem.Size = new System.Drawing.Size(53, 20);
            this.файлToolStripMenuItem.Text = "Файл";
            // 
            // openFile
            // 
            this.openFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openFileMenu,
            this.openFolderMenu});
            this.openFile.Name = "openFile";
            this.openFile.Size = new System.Drawing.Size(180, 22);
            this.openFile.Text = "Открыть";
            // 
            // openFileMenu
            // 
            this.openFileMenu.Name = "openFileMenu";
            this.openFileMenu.Size = new System.Drawing.Size(180, 22);
            this.openFileMenu.Text = "Файл";
            this.openFileMenu.Click += new System.EventHandler(this.OpenFileMenu_Click);
            // 
            // openFolderMenu
            // 
            this.openFolderMenu.Name = "openFolderMenu";
            this.openFolderMenu.Size = new System.Drawing.Size(180, 22);
            this.openFolderMenu.Text = "Папку";
            this.openFolderMenu.Click += new System.EventHandler(this.OpenFolderMenu_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog1";
            // 
            // ReplacerTable
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.BackColor = System.Drawing.Color.DarkSlateGray;
            this.ClientSize = new System.Drawing.Size(1025, 570);
            this.Controls.Add(this.ReplaceNameTwo);
            this.Controls.Add(this.lab_Default_name);
            this.Controls.Add(this.exetenciveBox);
            this.Controls.Add(this.replaceOneButton);
            this.Controls.Add(this.replaceButton);
            this.Controls.Add(this.Col2);
            this.Controls.Add(this.Col1);
            this.Controls.Add(this.column2);
            this.Controls.Add(this.column1);
            this.Controls.Add(this.table);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "ReplacerTable";
            this.Text = "ReplacerTable";
            this.Load += new System.EventHandler(this.ReplacerTable_Load);
            ((System.ComponentModel.ISupportInitialize)(this.table)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView table;
        private System.Windows.Forms.TextBox column1;
        private System.Windows.Forms.TextBox column2;
        private System.Windows.Forms.Label Col1;
        private System.Windows.Forms.Label Col2;
        private System.Windows.Forms.Button replaceButton;
        private System.Windows.Forms.Button replaceOneButton;
        private System.Windows.Forms.TextBox exetenciveBox;
        private System.Windows.Forms.Label lab_Default_name;
        private System.Windows.Forms.Button ReplaceNameTwo;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem файлToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.ToolStripMenuItem openFile;
        private System.Windows.Forms.ToolStripMenuItem openFileMenu;
        private System.Windows.Forms.ToolStripMenuItem openFolderMenu;
        private System.Windows.Forms.FolderBrowserDialog openFolderDialog;
    }
}