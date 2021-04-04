using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace UnComenter
{
  class ReplacerDir
  {

    public static string g_fileName = "Replace.txt";
    public static List<string> all_Lines_File = new List<string>();
    public static string s_Message = null;

    //Замена строк и занесения каталога файлов в таблицу
    //---------------------------------------------------------
    //Разделить на метод обчного считывания и метод считывания отдельной строки
    public static void Do_Read_File(bool is_clear)
    {
      if (!File.Exists(g_fileName))
        return;

      if (is_clear)
        all_Lines_File.Clear();

      StreamReader reader = new StreamReader(g_fileName, Encoding.Default);
      string line = null;

      while ((line = reader.ReadLine()) != null)
      {
        string[] path_Word_InLine = line.Split(new char[] { '|' }, StringSplitOptions.RemoveEmptyEntries);

        int i = path_Word_InLine.Length;
        if (i != 2)
        {
          s_Message = (i == 1) ? null : "Файл не соотвестствует требованиям \n (Директория1 | Директория2)";
          if (s_Message != null)
            return;
        }
        else s_Message = null;

        all_Lines_File.Add(line);
      }
    }

    public static void Do_Replace(string path_one, string path_two)
    {
      if (Directory.Exists(path_one))
        Directory.Move(path_one, path_two);
    }



  }
}
