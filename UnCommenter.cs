using System;
using System.IO;
using System.Text;

namespace UnComenter
{
  class Uncomenter
  {
    public enum status
    {
      SINGLE_LINE = 1,
      MUL_LINE = 2
    }

    static public void doUncomment(string path)
    {
      StreamReader reader = new StreamReader(path, Encoding.Default);
      string line = null;
      StringBuilder temp = new StringBuilder();

      StringBuilder buffer = new StringBuilder();

      status type = (status)0;

      long linenbr = 0;

      long spos = 0,
           mpos = 0;

      while ((line = reader.ReadLine()) != null)
      {
        linenbr++;

        spos = line.IndexOf("/*");
        mpos = line.IndexOf("//");

        // если коммертарий в кавычках
        int f_mark = line.IndexOf("\"");
        int l_mark = line.LastIndexOf("\"");

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
              if (!checkInStr(line, (int)spos))
              {
                if (line.Length > 1)
                  buffer.Append(line.Substring(0, (int)spos));
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
          {
            if (f_mark != l_mark) // Будет проверять есть ли в тексте кавычки и является ли кавычка закрывающей
            {
              if (mpos < f_mark || mpos > l_mark)
                buffer.Append(line.Substring(0, (int)mpos) + "\r\n");
              else
                buffer.Append(line + "\r\n");
            }
            else
              buffer.Append(line.Substring(0, (int)mpos) + "\r\n");
          }
          type = 0;
        }

        if (type == status.MUL_LINE)
        {
          int pos = line.IndexOf("*/");
          if (pos != -1)
          {
            pos += 2;
            if (pos < line.Length)
              buffer.Append(line.Substring(pos, line.Length - pos));
            buffer.Append("\r\n");
            type = 0;
          }
        }
      }

      reader.Close();

      StreamWriter writer = new StreamWriter(path, false, Encoding.Default);

      RemoveMultyCommentInLine(ref buffer);
      TrimEmptyLine(ref buffer);
      writer.WriteLine(buffer.ToString());
      writer.Close();
    }

    delegate void DelMultyComment(ref string line);
    public static void RemoveMultyCommentInLine(ref StringBuilder text)
    {
      try
      {
        if ((text.ToString().IndexOf("/*") == -1)) // если больше нет комментариев нет смысла идти дальше
          return;

        string[] lines = text.ToString().Split(new string[] { "\r\n" }, StringSplitOptions.RemoveEmptyEntries);
        text.Clear();

        DelMultyComment multiComment = (ref string line) => // Для более удобного и быстрого вызова была созданна данная конструкция
        {
          int sPos = line.IndexOf("/*");
          int fPos = line.IndexOf("*/");

          if (sPos == -1 || fPos == -1) // Если в строке уже нет комментариев
            return;

          fPos += 2 - sPos;

          if (fPos < line.Length)
            line = line.Replace(line.Substring(sPos, fPos), "");
        };

        for (int i = 0; i < lines.Length; i++)
        {
          // Чистим до момента когда точно в строке не будет комментов
          while ((lines[i].IndexOf("/*") != -1) && (lines[i].IndexOf("*/") != -1))
            multiComment(ref lines[i]);
          text.Append(lines[i] + "\r\n");
        }
      }
      catch { }
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

    // Чистит от лишних пустых строк
    public static void TrimEmptyLine(ref StringBuilder text)
    {
      string[] lines = text.ToString().Split(new string[] { "\r\n" }, StringSplitOptions.RemoveEmptyEntries);
      text.Clear();
      for (int i = 0; i < lines.Length; i++)
      {
        if (i != lines.Length)
          if (lines[i].Trim() == "" && lines[i + 1].Trim() == "")
            continue;
          else
            text.Append(lines[i] + "\r\n");
      }
    }

    public static void ReplaceDir(string path, string inp_D, string outp_D)
    {
      string buffer = null;
      Encoding en = Encoding.Default; //.GetEncoding("windows-1251");

      using (StreamReader sr = new StreamReader(path, en))  // читаем файл до конца и заносим всю информацию в буферную переменную
        buffer = sr.ReadToEnd();

      using (StreamWriter sw = new StreamWriter(path, false, en))
      {
        if (buffer.IndexOf(inp_D) != -1)  // Определяем необходимость проведения заменения
          buffer = outp_D == "null" ? buffer.Replace(inp_D, "") : buffer.Replace(inp_D, outp_D);

        sw.Write(buffer);
      }
    }

    public static void ReplaceAfter(string path, string inp_D, string outp_D)
    {
      string buf = "";
      string line = null;

      using (StreamReader reader = new StreamReader(path, Encoding.Default))
      {
        while ((line = reader.ReadLine()) != null)
        {
          if (line.ToLower().Contains(inp_D.ToLower()))
            if (line.Contains("#include"))
              line = line.Insert(line.ToLower().IndexOf(".h"), outp_D);
          buf += line + "\r\n";
        }
      }

      using (StreamWriter writer = new StreamWriter(path, false, Encoding.Default))
        writer.Write(buf);
    }

  }
}