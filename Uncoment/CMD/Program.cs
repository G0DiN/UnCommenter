using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace CMD
{
    class Program
    {
        static void Main(string[] args)
        {
            //Путь к директории
            string pathToFile = null;            
            int exp = -1;
           
            try {
                pathToFile = args[0];
                exp = args[0].IndexOf('*');
                if (exp == -1)
                throw new IndexOutOfRangeException();
            }


            catch (IndexOutOfRangeException)
            { }

            
            finally {   
            if (exp != -1)
                {
                    DirectoryInfo directoryInfo = new DirectoryInfo(pathToFile.Substring(0,exp));
                    string nameEXP = pathToFile.Substring(exp, pathToFile.Length - exp);

                    foreach (var file in directoryInfo.GetFiles(nameEXP))
                        Uncomenter.doUncomment(file.FullName);
                }
            }
        }
    }
}
