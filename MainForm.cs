using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;


namespace UnComenter
{
  public partial class Uncom : Form
  {
    public Uncom()
    {
      InitializeComponent();
      openFileDialog1.Filter = "All File (*.*)|*.*|C# Sourse Files|*.cs|C++ Sourse Files| *.cpp|Header Files| *.h|Java Script Files|*.js";
    }
    static string fileName = null;

    private void ButtonFileOpen_Click(object sender, EventArgs e)
    {
      openFileDialog1.FileName = null;
      if (openFileDialog1.ShowDialog() == DialogResult.Cancel)
        return;
      else
      {
        if (OneCheckFileName(Path.GetFileName(openFileDialog1.FileName)) == false)
        {
          string filename = openFileDialog1.FileName;
          StreamReader reader = new StreamReader(filename, Encoding.Default);
          //        string fileText = File.ReadAllText(filename, Encoding.UTF8);
          textBox1.Text = reader.ReadToEnd();
          fileName = filename;
          Tab1.TabPages.Add(Path.GetFileName(filename));
          multitude.Add(filename);
          CheckList.Items.Add(Path.GetFileName(filename));
          Tab1.Visible = true;

          for (int i = 0; i < Tab1.TabPages.Count; i++)
          {
            if (Tab1.TabPages[i].Text == Path.GetFileName(openFileDialog1.FileName))
            {
              Tab1.SelectedTab = Tab1.TabPages[i];
              Tab1_Click(sender, e);
              break;
            }
          }
          reader.Close();
        }
        else
        {
          string filename = openFileDialog1.FileName;
          StreamReader reader = new StreamReader(filename, Encoding.Default);
          // string fileText = File.ReadAllText(filename, Encoding.Unicode);
          textBox1.Text = reader.ReadToEnd();
          for (int i = 0; i < Tab1.TabPages.Count; i++)
          {
            if (Tab1.TabPages[i].Text == Path.GetFileName(openFileDialog1.FileName))
            {
              Tab1.SelectedTab = Tab1.TabPages[i];
              Tab1_Click(sender, e);
              break;
            }
          }
          reader.Close();
        }
      }
    }
    private void ButtonDeleteFileComments_Click(object sender, EventArgs e)
    {
      //проверка на наличие открытого файла
      bool firstInput = false;
      for (int i = 0; i < CheckList.Items.Count; i++)
      {
        if ((CheckList.GetItemChecked(i) == true) && firstInput == false)
        {
          OneCheckFileName((string)CheckList.Items[i]);
          Uncomenter.doUncomment(fileName);
          firstInput = true;
          if (Tab1.SelectedTab.Text == (string)CheckList.Items[i])
          {
            string fileText = File.ReadAllText(fileName, Encoding.Default);
            textBox1.Text = fileText;
          }
        }
        if ((CheckList.GetItemChecked(i) == true) && firstInput == true)
        {
          OneCheckFileName((string)CheckList.Items[i]);
          Uncomenter.doUncomment(fileName);
        }
      }
      if (firstInput == true)
        MessageBox.Show("Commenter deleted");
      else
        MessageBox.Show("Please open choose the file(s)");
    }

    private void ButtonSaveAs_Click(object sender, EventArgs e)
    {
      try
      {
        if (fileName == null)
        {
          saveFileDialog1.FileName = @"uncommenter.cpp";
        }
        else
          saveFileDialog1.FileName = Path.GetFileName(fileName);

        if (saveFileDialog1.ShowDialog() == DialogResult.Cancel)
          return;
        else
        {
          // получаем выбранный файл
          string filename = saveFileDialog1.FileName;
          fileName = filename;
          File.WriteAllText(filename, textBox1.Text, Encoding.Default);
        }
      }
      catch (Exception ex)
      {
        MessageBox.Show(ex.Message);
      }
    }


    private void ButtonSave_Click(object sender, EventArgs e)
    {
      if (fileName == null)
      {
        saveFileDialog1.FileName = @"uncommenter.cpp";
        if (saveFileDialog1.ShowDialog() == DialogResult.Cancel)
          return;
        else
        {
          // получаем выбранный файл
          File.WriteAllText(fileName, textBox1.Text, Encoding.Default);
        }
      }
      else
        File.WriteAllText(fileName, textBox1.Text, Encoding.Default);
    }

    //MenuStrip

    //Save As
    private void MenuItemSaveAs_Click(object sender, EventArgs e)
    {
      ButtonSaveAs_Click(sender, e);
    }

    //Save
    private void MenuItemSave_Click(object sender, EventArgs e)
    {
      ButtonSave_Click(sender, e);
    }

    //Delete Coments in File
    private void MenuItemDeletedFileComents_Click(object sender, EventArgs e)
    {
      ButtonDeleteFileComments_Click(sender, e);
    }

    //Open File

    private void OpenFile_Click(object sender, EventArgs e)
    {
      ButtonFileOpen_Click(sender, e);
    }
    //-----------------------------------------------------

    // Массив для сохранения пути к файлу
    public static List<string> multitude = new List<string>();
    // Массив для расширений файла
    private List<string> fileExtention = new List<string>() { ".cpp", ".c", ".cs", ".js" };

    private void UnCommentFolder(List<string> FileExt)
    {
      if (openFold.ShowDialog() == DialogResult.Cancel)
        return;
      else
      {
        CheckList.Items.Clear();
        Tab1.TabPages.Clear();
        multitude.Clear();

        // получаем выбранный каталог
        if (Directory.Exists(openFold.SelectedPath))
        {
          int kolFile = 0;
          string[] dirs = Directory.GetFiles(openFold.SelectedPath);

          foreach (string d in dirs)
          {
            string filepath = d;
            string extension = Path.GetExtension(filepath);

            foreach (string ex in FileExt)
            {
              if (extension == ex)
              {
                kolFile++;
                CheckList.Items.Add(Path.GetFileName(d));
                Tab1.TabPages.Add(Path.GetFileName(d));
                // помещаем путь к файлу в массив
                multitude.Add(d);
                if (kolFile == 1)
                {
                  fileName = d;
                  string fileText = File.ReadAllText(d, Encoding.Default);
                  textBox1.Text = fileText;
                }
                break;
              }
              else continue;
            } // проход по всем рассширениям
          }
          if (kolFile > 0)
          {
            MessageBox.Show($"Найдено: {kolFile} файлов");
            Tab1.Visible = true;
          }
          else
          {
            MessageBox.Show($"Файлы не найдены");
            Tab1.Visible = false;
          }
        }
      }
    }
    private void OpenFolder_Click(object sender, EventArgs e)
    {
      if (openFold.ShowDialog() == DialogResult.Cancel)
        return;
      else
      {
        CheckList.Items.Clear();
        Tab1.TabPages.Clear();
        multitude.Clear();

        // получаем выбранный каталог
        if (Directory.Exists(openFold.SelectedPath))
        {
          int kolFile = 0;
          string[] dirs = Directory.GetFiles(openFold.SelectedPath);

          foreach (string d in dirs)
          {
            string filepath = d;
            string extension = Path.GetExtension(filepath);

            foreach (string ex in fileExtention)
            {
              if (extension == ex)
              {
                kolFile++;
                CheckList.Items.Add(Path.GetFileName(d));
                Tab1.TabPages.Add(Path.GetFileName(d));
                //помещаем путь к файлу в массив
                multitude.Add(d);
                if (kolFile == 1)
                {
                  fileName = d;
                  string fileText = File.ReadAllText(d, Encoding.Default);
                  textBox1.Text = fileText;
                }
                break;
              }
              else continue;
            } // проход по всем рассширениям
          }
          if (kolFile > 0)
          {
            MessageBox.Show($"Найдено: {kolFile} файлов");
            Tab1.Visible = true;
          }
          else
          {
            MessageBox.Show($"Файлы не найдены");
            Tab1.Visible = false;
          }
        }
      }
    }

    private void SelectedRemove_Click(object sender, EventArgs e)
    {
      for (int i = 0; i < CheckList.Items.Count; i++)
        CheckList.SetItemChecked(i, false);
    }

    private void ChooseALL_Click(object sender, EventArgs e)
    {

      for (int i = 0; i < CheckList.Items.Count; i++)
        CheckList.SetItemChecked(i, true);
    }

    private void Tab1_Click(object sender, EventArgs e)
    {
      try
      {
        foreach (var item in multitude)
        {
          if (Path.GetFileName(item) == Tab1.SelectedTab.Text)
          {
            string fileText = File.ReadAllText(item, Encoding.Default);
            textBox1.Text = fileText;
            fileName = item;
            break;
          }
        }
      }
      catch (Exception ex)
      {
        MessageBox.Show(ex.Message);
      }
    }
    //----------------------------------------------------------

    public bool OneCheckFileName(string name)
    {
      try
      {
        foreach (var item in multitude)
        {
          if (Path.GetFileName(item) == name)
          {
            string fileText = File.ReadAllText(item, Encoding.Default);
            fileName = item;
            return true;
          }
        }
      }
      catch (Exception ex)
      {
        MessageBox.Show(ex.Message);
      }
      return false;
    }

    private void DeleteComInOneFile_Click(object sender, EventArgs e)
    {
      if (fileName != null)
      {
        Uncomenter.doUncomment(fileName);
        string fileText = File.ReadAllText(fileName, Encoding.Default);
        textBox1.Text = fileText;
        MessageBox.Show("Commenter deleted");
      }
      else
        MessageBox.Show("Please open choose the file(s)");
    }

    private void DeletedInfoInFiles_Click(object sender, EventArgs e)
    {
      ButtonDeleteFileComments_Click(sender, e);
    }

    private void папкаhToolStripMenuItem_Click(object sender, EventArgs e)
    {
      // Выбрать *.h файлы
      List<string> FileExt = new List<string>() { ".h", ".H" };
      UnCommentFolder(FileExt);
    }

    //-------------------------------------------------------------
    //REPLACE 
    private void DirectoryReplace_Click(object sender, EventArgs e)
    {
      ReplacerTable replacerTable = new ReplacerTable();
      replacerTable.Show();

      if (ReplacerDir.s_Message != null)
        MessageBox.Show(ReplacerDir.s_Message);
      //ReplacerDir.Do_Replace();
    }
  }
}
