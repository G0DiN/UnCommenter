using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Uncoment
{
    class Uncomenter
    {
        public enum status
        {
            SINGLE_LINE = 1,
            MUL_LINE = 2
        }

        static public void doUncomment(string file)
        {
            StreamReader reader = new StreamReader(file, Encoding.Default);
            string line = null;
            StringBuilder temp = new StringBuilder();

            StringBuilder buffer = new StringBuilder();

            status type = (status)0;

            int linenbr = 0;

            while ((line = reader.ReadLine()) != null)
            {
                linenbr++;

                int spos = line.IndexOf("/*");
                int mpos = line.IndexOf("//");

                if (type != status.MUL_LINE)
                {
                    if (spos != -1)
                    {
                        type = status.MUL_LINE;

                        if (mpos != -1)
                            if (mpos < spos)
                                type = status.SINGLE_LINE;

                        if (type == status.MUL_LINE)
                        {
                            if (!checkInStr(line, spos))
                            {
                                if (line.Length > 1)
                                    buffer.Append(line.Substring(0, spos) + "\r\n");
                            }
                            else
                            {
                                buffer.Append(line + "\r\n");
                                type = 0;
                            }
                        }
                    }
                    else if (mpos != -1)
                        type = status.SINGLE_LINE;
                    else
                        buffer.Append(line + "\r\n");
                }

                if (type == status.SINGLE_LINE)
                {
                    if (line.Length > 1)
                        buffer.Append(line.Substring(0, mpos) + "\r\n");
                    type = 0;
                }

                if (type == status.MUL_LINE)
                {
                    int pos = line.IndexOf("*/");
                    if (pos != -1)
                    {
                        pos += 2;
                        if (pos < line.Length)
                            buffer.Append(line.Substring(pos, line.Length - pos) + "\r\n");

                        type = 0;
                    }
                }

            }

            reader.Close();

            StreamWriter writer = new StreamWriter(file, false, Encoding.Default);

            writer.WriteLine(buffer.ToString());
            writer.Close();
        }

        static bool checkInStr(string lineb, int compos)
        {
            bool sflag = false;

            for (int i = 0; i < lineb.Length; i++)
            {
                if (lineb[i] == '\x22')
                    sflag = !sflag;

                if ((sflag == false) && i == compos)
                    return false;
            }

            return true;
        }
    }
}