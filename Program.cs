using System;
using System.Windows.Forms;
using System.IO;

namespace UnComenter
{
  static class Program
  {
    /// <summary>
    /// Главная точка входа для приложения.
    /// Если приложение не принимает аргументов то программа запускается в окне
    /// Если же принимает параметры то происходит проверка ключевых слов
    /// Если первое ключевое слово uncom то программа будет удалять комментарии в выбранной директории
    /// Если же первое ключевое слов replace то программа будет заменять входные (смотря какие параметры получит) 
    /// args[2] и args[3] это первоначальное значение и заменяемое значение соотевтсвенно
    /// </summary>
    enum KeyWord
    {
      exit = 0,
      uncom,          // для выполнения раскомментирования
      replace,        // для выполнения замены в файле
      replaceDir,     // для изменения пути к библиотекам #include "../ADOBO.h -> ../ABMFc_ADOBO.h"
      replaceAfter,   // Изменение имени после слова
      unRegistReplace // Изменение вне зависимости от регистра

    }
    [STAThread]
    static void Main(string[] args)
    {
      if (args.Length == 0)
      {
        Application.EnableVisualStyles();
        Application.SetCompatibleTextRenderingDefault(false);
        Application.Run(new Uncom());
      }
      else if (args.Length >= 2)
      {
        KeyWord key = KeyWord.exit;
        switch (args[0].ToLower())
        {
          case "uncom": key = KeyWord.uncom;
            break;
          case "replace": key = KeyWord.replace;
            break;
          case "replacedir": key = KeyWord.replaceDir;
            break;
          case "replaceafter": key = KeyWord.replaceAfter;
            break;
          case "unregistrepl": key = KeyWord.unRegistReplace;
            break;
        }

        if (key == KeyWord.exit)
          return;

        string pathToFile = null; // Путь к Каталогу
        int exp = -1;             // Расширение файла

        try
        {
          pathToFile = args[1];
          exp = args[1].IndexOf('*'); // Нахождение разделяющего знака для определения где находится путь к файлу, а где находится расширение
          if (exp == -1)
          {
            if (key == KeyWord.replaceDir) // Используется в bat файле для буферной директории где происходит замена пути расположения файлов
            {
              DirectoryInfo directoryInfo = new DirectoryInfo(args[1]);
              foreach (var file in directoryInfo.GetFiles("*.h"))
                foreach (var item in directoryInfo.GetFiles("*.*"))
                  if (args[2].ToLower() == "null")
                    Uncomenter.ReplaceDir(item.FullName, file.Name, args[3] + file.Name);
                  else
                    Uncomenter.ReplaceDir(item.FullName, file.Name, file.Name.Insert(file.Name.IndexOf(file.Extension), args[3]));
            } 
            else if (key == KeyWord.unRegistReplace)
            {
              DirectoryInfo directoryInfo = new DirectoryInfo(args[1]);
              foreach (var file in directoryInfo.GetFiles("*.h"))
                foreach (var item in directoryInfo.GetFiles("*.*"))
                    Uncomenter.ReplaceAfter(item.FullName, file.Name, args[2]);
            }
            else return;
          }
          if (key == KeyWord.replace && args.Length < 4)
            return;

          if (exp != -1)
          {
            DirectoryInfo directoryInfo = new DirectoryInfo(pathToFile.Substring(0, exp));
            string nameEXP = pathToFile.Substring(exp, pathToFile.Length - exp);

            if (key == KeyWord.uncom)
              foreach (var file in directoryInfo.GetFiles(nameEXP))         // Удаляем коменты 
                Uncomenter.doUncomment(file.FullName);

            else if (key == KeyWord.replace)
              foreach (var file in directoryInfo.GetFiles(nameEXP))         // Делаем реплейс
                Uncomenter.ReplaceDir(file.FullName, args[2], args[3]);

            else if (key == KeyWord.replaceAfter)
              foreach (var file in directoryInfo.GetFiles(nameEXP))
                Uncomenter.ReplaceAfter(file.FullName, args[2], args[3]);
          }
        }
        catch (IndexOutOfRangeException)
        { }

        catch (Exception)
        { }
      }
    }
  }
}
