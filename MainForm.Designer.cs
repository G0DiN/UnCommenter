namespace UnComenter
{
    partial class Uncom
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
      this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
      this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
      this.menuStrip1 = new System.Windows.Forms.MenuStrip();
      this.MenuItemFile = new System.Windows.Forms.ToolStripMenuItem();
      this.MenuItemOpen = new System.Windows.Forms.ToolStripMenuItem();
      this.OpenFile = new System.Windows.Forms.ToolStripMenuItem();
      this.OpenFolder = new System.Windows.Forms.ToolStripMenuItem();
      this.папкаhToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.MenuItemSave = new System.Windows.Forms.ToolStripMenuItem();
      this.MenuItemSaveAs = new System.Windows.Forms.ToolStripMenuItem();
      this.menu_Delete = new System.Windows.Forms.ToolStripMenuItem();
      this.DeleteComInOneFile = new System.Windows.Forms.ToolStripMenuItem();
      this.DeletedInfoInFiles = new System.Windows.Forms.ToolStripMenuItem();
      this.menuDirectory = new System.Windows.Forms.ToolStripMenuItem();
      this.DirectoryReplace = new System.Windows.Forms.ToolStripMenuItem();
      this.openFold = new System.Windows.Forms.FolderBrowserDialog();
      this.Tab1 = new System.Windows.Forms.TabControl();
      this.label1 = new System.Windows.Forms.Label();
      this.ButtonFileOpen = new System.Windows.Forms.Button();
      this.ButtonDeleteFileComments = new System.Windows.Forms.Button();
      this.ButtonSaveAs = new System.Windows.Forms.Button();
      this.ButtonSave = new System.Windows.Forms.Button();
      this.CheckList = new System.Windows.Forms.CheckedListBox();
      this.SelectedRemove = new System.Windows.Forms.Button();
      this.ChooseALL = new System.Windows.Forms.Button();
      this.textBox1 = new System.Windows.Forms.TextBox();
      this.menuStrip1.SuspendLayout();
      this.SuspendLayout();
      // 
      // openFileDialog1
      // 
      this.openFileDialog1.FileName = "openFileDialog1";
      // 
      // menuStrip1
      // 
      this.menuStrip1.BackColor = System.Drawing.SystemColors.ButtonHighlight;
      this.menuStrip1.Font = new System.Drawing.Font("Constantia", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
      this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuItemFile,
            this.menu_Delete,
            this.menuDirectory});
      this.menuStrip1.Location = new System.Drawing.Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Padding = new System.Windows.Forms.Padding(5, 2, 0, 2);
      this.menuStrip1.Size = new System.Drawing.Size(1692, 31);
      this.menuStrip1.TabIndex = 2;
      this.menuStrip1.Text = "menuStrip1";
      // 
      // MenuItemFile
      // 
      this.MenuItemFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuItemOpen,
            this.MenuItemSave,
            this.MenuItemSaveAs});
      this.MenuItemFile.Font = new System.Drawing.Font("Verdana", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.MenuItemFile.ForeColor = System.Drawing.Color.Black;
      this.MenuItemFile.Name = "MenuItemFile";
      this.MenuItemFile.Size = new System.Drawing.Size(75, 27);
      this.MenuItemFile.Text = "Файл";
      // 
      // MenuItemOpen
      // 
      this.MenuItemOpen.BackColor = System.Drawing.SystemColors.Control;
      this.MenuItemOpen.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.OpenFile,
            this.OpenFolder,
            this.папкаhToolStripMenuItem});
      this.MenuItemOpen.ForeColor = System.Drawing.Color.Black;
      this.MenuItemOpen.Name = "MenuItemOpen";
      this.MenuItemOpen.Size = new System.Drawing.Size(237, 28);
      this.MenuItemOpen.Text = "Открыть";
      // 
      // OpenFile
      // 
      this.OpenFile.BackColor = System.Drawing.SystemColors.Control;
      this.OpenFile.ForeColor = System.Drawing.Color.Black;
      this.OpenFile.Name = "OpenFile";
      this.OpenFile.Size = new System.Drawing.Size(213, 28);
      this.OpenFile.Text = "Файл";
      this.OpenFile.Click += new System.EventHandler(this.OpenFile_Click);
      // 
      // OpenFolder
      // 
      this.OpenFolder.BackColor = System.Drawing.SystemColors.Control;
      this.OpenFolder.ForeColor = System.Drawing.Color.Black;
      this.OpenFolder.Name = "OpenFolder";
      this.OpenFolder.Size = new System.Drawing.Size(213, 28);
      this.OpenFolder.Text = "Папка *.cpp";
      this.OpenFolder.Click += new System.EventHandler(this.OpenFolder_Click);
      // 
      // папкаhToolStripMenuItem
      // 
      this.папкаhToolStripMenuItem.Name = "папкаhToolStripMenuItem";
      this.папкаhToolStripMenuItem.Size = new System.Drawing.Size(213, 28);
      this.папкаhToolStripMenuItem.Text = "Папка *.h";
      this.папкаhToolStripMenuItem.Click += new System.EventHandler(this.папкаhToolStripMenuItem_Click);
      // 
      // MenuItemSave
      // 
      this.MenuItemSave.BackColor = System.Drawing.SystemColors.Control;
      this.MenuItemSave.ForeColor = System.Drawing.Color.Black;
      this.MenuItemSave.Name = "MenuItemSave";
      this.MenuItemSave.Size = new System.Drawing.Size(237, 28);
      this.MenuItemSave.Text = "Сохранить";
      this.MenuItemSave.Click += new System.EventHandler(this.MenuItemSave_Click);
      // 
      // MenuItemSaveAs
      // 
      this.MenuItemSaveAs.BackColor = System.Drawing.SystemColors.Control;
      this.MenuItemSaveAs.ForeColor = System.Drawing.Color.Black;
      this.MenuItemSaveAs.Name = "MenuItemSaveAs";
      this.MenuItemSaveAs.Size = new System.Drawing.Size(237, 28);
      this.MenuItemSaveAs.Text = "Сохранить как";
      this.MenuItemSaveAs.Click += new System.EventHandler(this.MenuItemSaveAs_Click);
      // 
      // menu_Delete
      // 
      this.menu_Delete.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.DeleteComInOneFile,
            this.DeletedInfoInFiles});
      this.menu_Delete.Font = new System.Drawing.Font("Verdana", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.menu_Delete.ForeColor = System.Drawing.Color.Black;
      this.menu_Delete.Name = "menu_Delete";
      this.menu_Delete.Size = new System.Drawing.Size(103, 27);
      this.menu_Delete.Text = "Удалить";
      // 
      // DeleteComInOneFile
      // 
      this.DeleteComInOneFile.ForeColor = System.Drawing.Color.Black;
      this.DeleteComInOneFile.Name = "DeleteComInOneFile";
      this.DeleteComInOneFile.Size = new System.Drawing.Size(524, 28);
      this.DeleteComInOneFile.Text = "Удалить комментарии в файле";
      this.DeleteComInOneFile.Click += new System.EventHandler(this.DeleteComInOneFile_Click);
      // 
      // DeletedInfoInFiles
      // 
      this.DeletedInfoInFiles.ForeColor = System.Drawing.Color.Black;
      this.DeletedInfoInFiles.Name = "DeletedInfoInFiles";
      this.DeletedInfoInFiles.Size = new System.Drawing.Size(524, 28);
      this.DeletedInfoInFiles.Text = "Удалить комментарии в выбранных файлах";
      this.DeletedInfoInFiles.Click += new System.EventHandler(this.DeletedInfoInFiles_Click);
      // 
      // menuDirectory
      // 
      this.menuDirectory.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.DirectoryReplace});
      this.menuDirectory.Font = new System.Drawing.Font("Verdana", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.menuDirectory.Name = "menuDirectory";
      this.menuDirectory.Size = new System.Drawing.Size(140, 27);
      this.menuDirectory.Text = "Директория";
      // 
      // DirectoryReplace
      // 
      this.DirectoryReplace.Name = "DirectoryReplace";
      this.DirectoryReplace.Size = new System.Drawing.Size(224, 28);
      this.DirectoryReplace.Text = "Заменить";
      this.DirectoryReplace.Click += new System.EventHandler(this.DirectoryReplace_Click);
      // 
      // openFold
      // 
      this.openFold.ShowNewFolderButton = false;
      // 
      // Tab1
      // 
      this.Tab1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.Tab1.Cursor = System.Windows.Forms.Cursors.Default;
      this.Tab1.Font = new System.Drawing.Font("Tahoma", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.Tab1.ItemSize = new System.Drawing.Size(50, 30);
      this.Tab1.Location = new System.Drawing.Point(347, 36);
      this.Tab1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
      this.Tab1.Name = "Tab1";
      this.Tab1.SelectedIndex = 0;
      this.Tab1.Size = new System.Drawing.Size(1155, 32);
      this.Tab1.TabIndex = 5;
      this.Tab1.Visible = false;
      this.Tab1.Click += new System.EventHandler(this.Tab1_Click);
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Font = new System.Drawing.Font("Tahoma", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.label1.ForeColor = System.Drawing.SystemColors.Window;
      this.label1.Location = new System.Drawing.Point(61, 44);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(167, 23);
      this.label1.TabIndex = 6;
      this.label1.Text = "Перечень файлов";
      // 
      // ButtonFileOpen
      // 
      this.ButtonFileOpen.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(45)))), ((int)(((byte)(45)))), ((int)(((byte)(48)))));
      this.ButtonFileOpen.Cursor = System.Windows.Forms.Cursors.Hand;
      this.ButtonFileOpen.FlatAppearance.BorderSize = 0;
      this.ButtonFileOpen.FlatAppearance.MouseOverBackColor = System.Drawing.Color.DarkSlateGray;
      this.ButtonFileOpen.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.ButtonFileOpen.Font = new System.Drawing.Font("Georgia", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.ButtonFileOpen.ForeColor = System.Drawing.Color.LightCyan;
      this.ButtonFileOpen.Location = new System.Drawing.Point(15, 390);
      this.ButtonFileOpen.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
      this.ButtonFileOpen.Name = "ButtonFileOpen";
      this.ButtonFileOpen.Size = new System.Drawing.Size(325, 50);
      this.ButtonFileOpen.TabIndex = 0;
      this.ButtonFileOpen.Text = "Открыть";
      this.ButtonFileOpen.UseVisualStyleBackColor = false;
      this.ButtonFileOpen.Click += new System.EventHandler(this.ButtonFileOpen_Click);
      // 
      // ButtonDeleteFileComments
      // 
      this.ButtonDeleteFileComments.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(45)))), ((int)(((byte)(45)))), ((int)(((byte)(48)))));
      this.ButtonDeleteFileComments.Cursor = System.Windows.Forms.Cursors.Hand;
      this.ButtonDeleteFileComments.FlatAppearance.BorderSize = 0;
      this.ButtonDeleteFileComments.FlatAppearance.MouseOverBackColor = System.Drawing.Color.DarkSlateGray;
      this.ButtonDeleteFileComments.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.ButtonDeleteFileComments.Font = new System.Drawing.Font("Georgia", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.ButtonDeleteFileComments.ForeColor = System.Drawing.Color.LightCyan;
      this.ButtonDeleteFileComments.Location = new System.Drawing.Point(15, 546);
      this.ButtonDeleteFileComments.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
      this.ButtonDeleteFileComments.Name = "ButtonDeleteFileComments";
      this.ButtonDeleteFileComments.Size = new System.Drawing.Size(325, 50);
      this.ButtonDeleteFileComments.TabIndex = 1;
      this.ButtonDeleteFileComments.Text = "Удалить коментарии";
      this.ButtonDeleteFileComments.UseVisualStyleBackColor = false;
      this.ButtonDeleteFileComments.Click += new System.EventHandler(this.ButtonDeleteFileComments_Click);
      // 
      // ButtonSaveAs
      // 
      this.ButtonSaveAs.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(45)))), ((int)(((byte)(45)))), ((int)(((byte)(48)))));
      this.ButtonSaveAs.Cursor = System.Windows.Forms.Cursors.Hand;
      this.ButtonSaveAs.FlatAppearance.BorderSize = 0;
      this.ButtonSaveAs.FlatAppearance.MouseOverBackColor = System.Drawing.Color.DarkSlateGray;
      this.ButtonSaveAs.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.ButtonSaveAs.Font = new System.Drawing.Font("Georgia", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.ButtonSaveAs.ForeColor = System.Drawing.Color.LightCyan;
      this.ButtonSaveAs.Location = new System.Drawing.Point(15, 494);
      this.ButtonSaveAs.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
      this.ButtonSaveAs.Name = "ButtonSaveAs";
      this.ButtonSaveAs.Size = new System.Drawing.Size(325, 50);
      this.ButtonSaveAs.TabIndex = 2;
      this.ButtonSaveAs.Text = "Сохранить Как";
      this.ButtonSaveAs.UseVisualStyleBackColor = false;
      this.ButtonSaveAs.Click += new System.EventHandler(this.ButtonSaveAs_Click);
      // 
      // ButtonSave
      // 
      this.ButtonSave.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(45)))), ((int)(((byte)(45)))), ((int)(((byte)(48)))));
      this.ButtonSave.Cursor = System.Windows.Forms.Cursors.Hand;
      this.ButtonSave.FlatAppearance.BorderSize = 0;
      this.ButtonSave.FlatAppearance.MouseOverBackColor = System.Drawing.Color.DarkSlateGray;
      this.ButtonSave.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.ButtonSave.Font = new System.Drawing.Font("Georgia", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.ButtonSave.ForeColor = System.Drawing.Color.LightCyan;
      this.ButtonSave.Location = new System.Drawing.Point(15, 442);
      this.ButtonSave.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
      this.ButtonSave.Name = "ButtonSave";
      this.ButtonSave.Size = new System.Drawing.Size(325, 50);
      this.ButtonSave.TabIndex = 3;
      this.ButtonSave.Text = "Сохранить";
      this.ButtonSave.UseVisualStyleBackColor = false;
      this.ButtonSave.Click += new System.EventHandler(this.ButtonSave_Click);
      // 
      // CheckList
      // 
      this.CheckList.AccessibleName = "";
      this.CheckList.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(45)))), ((int)(((byte)(45)))), ((int)(((byte)(48)))));
      this.CheckList.CheckOnClick = true;
      this.CheckList.Cursor = System.Windows.Forms.Cursors.Hand;
      this.CheckList.Font = new System.Drawing.Font("Tahoma", 7.8F);
      this.CheckList.ForeColor = System.Drawing.SystemColors.InactiveBorder;
      this.CheckList.FormattingEnabled = true;
      this.CheckList.Location = new System.Drawing.Point(15, 70);
      this.CheckList.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
      this.CheckList.Name = "CheckList";
      this.CheckList.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
      this.CheckList.Size = new System.Drawing.Size(324, 184);
      this.CheckList.TabIndex = 5;
      // 
      // SelectedRemove
      // 
      this.SelectedRemove.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(45)))), ((int)(((byte)(45)))), ((int)(((byte)(48)))));
      this.SelectedRemove.Cursor = System.Windows.Forms.Cursors.Hand;
      this.SelectedRemove.FlatAppearance.BorderSize = 0;
      this.SelectedRemove.FlatAppearance.MouseOverBackColor = System.Drawing.Color.DarkSlateGray;
      this.SelectedRemove.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.SelectedRemove.Font = new System.Drawing.Font("Georgia", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.SelectedRemove.ForeColor = System.Drawing.Color.LightCyan;
      this.SelectedRemove.Location = new System.Drawing.Point(15, 316);
      this.SelectedRemove.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
      this.SelectedRemove.Name = "SelectedRemove";
      this.SelectedRemove.Size = new System.Drawing.Size(325, 50);
      this.SelectedRemove.TabIndex = 7;
      this.SelectedRemove.Text = "убрать выбранное";
      this.SelectedRemove.UseVisualStyleBackColor = false;
      this.SelectedRemove.Click += new System.EventHandler(this.SelectedRemove_Click);
      // 
      // ChooseALL
      // 
      this.ChooseALL.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(45)))), ((int)(((byte)(45)))), ((int)(((byte)(48)))));
      this.ChooseALL.Cursor = System.Windows.Forms.Cursors.Hand;
      this.ChooseALL.FlatAppearance.BorderSize = 0;
      this.ChooseALL.FlatAppearance.MouseOverBackColor = System.Drawing.Color.DarkSlateGray;
      this.ChooseALL.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.ChooseALL.Font = new System.Drawing.Font("Georgia", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.ChooseALL.ForeColor = System.Drawing.Color.LightCyan;
      this.ChooseALL.Location = new System.Drawing.Point(15, 265);
      this.ChooseALL.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
      this.ChooseALL.Name = "ChooseALL";
      this.ChooseALL.Size = new System.Drawing.Size(325, 50);
      this.ChooseALL.TabIndex = 6;
      this.ChooseALL.Text = "Выбрать все";
      this.ChooseALL.UseVisualStyleBackColor = false;
      this.ChooseALL.Click += new System.EventHandler(this.ChooseALL_Click);
      // 
      // textBox1
      // 
      this.textBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.textBox1.BackColor = System.Drawing.SystemColors.ControlLight;
      this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.None;
      this.textBox1.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.textBox1.Location = new System.Drawing.Point(347, 70);
      this.textBox1.Margin = new System.Windows.Forms.Padding(4);
      this.textBox1.Multiline = true;
      this.textBox1.Name = "textBox1";
      this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
      this.textBox1.Size = new System.Drawing.Size(1155, 497);
      this.textBox1.TabIndex = 8;
      // 
      // Uncom
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.Color.DarkSlateGray;
      this.ClientSize = new System.Drawing.Size(1692, 624);
      this.Controls.Add(this.textBox1);
      this.Controls.Add(this.SelectedRemove);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.ChooseALL);
      this.Controls.Add(this.CheckList);
      this.Controls.Add(this.ButtonSave);
      this.Controls.Add(this.Tab1);
      this.Controls.Add(this.ButtonSaveAs);
      this.Controls.Add(this.ButtonDeleteFileComments);
      this.Controls.Add(this.menuStrip1);
      this.Controls.Add(this.ButtonFileOpen);
      this.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
      this.MainMenuStrip = this.menuStrip1;
      this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
      this.Name = "Uncom";
      this.Text = " Uncommenter";
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem MenuItemFile;
        private System.Windows.Forms.ToolStripMenuItem MenuItemOpen;
        private System.Windows.Forms.ToolStripMenuItem MenuItemSave;
        //private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1; - не используется
        private System.Windows.Forms.ToolStripMenuItem MenuItemSaveAs;
        private System.Windows.Forms.FolderBrowserDialog openFold;
        private System.Windows.Forms.ToolStripMenuItem OpenFile;
        private System.Windows.Forms.ToolStripMenuItem OpenFolder;
        private System.Windows.Forms.TabControl Tab1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ToolStripMenuItem menu_Delete;
        private System.Windows.Forms.ToolStripMenuItem DeleteComInOneFile;
        private System.Windows.Forms.ToolStripMenuItem DeletedInfoInFiles;
        private System.Windows.Forms.Button ButtonFileOpen;
        private System.Windows.Forms.Button ButtonDeleteFileComments;
        private System.Windows.Forms.Button ButtonSaveAs;
        private System.Windows.Forms.Button ButtonSave;
        private System.Windows.Forms.CheckedListBox CheckList;
        private System.Windows.Forms.Button SelectedRemove;
        private System.Windows.Forms.Button ChooseALL;
        private System.Windows.Forms.TextBox textBox1;
    private System.Windows.Forms.ToolStripMenuItem папкаhToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuDirectory;
        private System.Windows.Forms.ToolStripMenuItem DirectoryReplace;
  }
}

