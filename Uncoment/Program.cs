using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Uncoment
{
  static class Program
  {
    /// <summary>
    /// Главная точка входа для приложения.
    /// </summary>
    [STAThread]
    static void Main(string [] args)
    {
      if (args.Length == 0)
      {
        Application.EnableVisualStyles();
        Application.SetCompatibleTextRenderingDefault(false);
        Application.Run(new Uncom());
      }
      else if (args.Length == 1)
      {
        string pathToFile = null;
        int    exp = -1;

        try
        {
          pathToFile = args[0];
          exp = args[0].IndexOf('*');
          if (exp == -1)
            throw new IndexOutOfRangeException();
        }
        catch (IndexOutOfRangeException)
        { }
        finally
        {
          if (exp != -1)
          {
            DirectoryInfo directoryInfo = new DirectoryInfo(pathToFile.Substring(0, exp));
            string nameEXP = pathToFile.Substring(exp, pathToFile.Length - exp);

            foreach (var file in directoryInfo.GetFiles(nameEXP))
                Uncomenter.doUncomment(file.FullName);
          }
        }
      }
    }
  }
}
