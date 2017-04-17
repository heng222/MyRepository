using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using ProWrite.Core;
using System.Windows.Forms;
using System.Xml.Serialization;
using System.IO;
using System.Configuration;

namespace ProWrite.UI.Controls
{

    public class StringList : List<string>
    {
        public StringList()
        {
        }

        protected static void LoadStringListFromFile<TStringList>(string fileName) where TStringList : StringList, new()
        {
            var result = new TStringList();
            try
            {
                using (var sr = new StreamReader(fileName))
                {

                    bool b = true;
                    string item = "";
                    while (b)
                    {
                        item = sr.ReadLine();
                        if (item != null)
                            result.Add(item);
                        else
                            b = false;
                    }
                }
                ServiceManager.Add<TStringList>(result);
            }
            catch { }
        }

       

        public override string ToString()
        {
            var sb = new StringBuilder();
            ForEach(item => sb.Append(item).AppendLine());
            return sb.ToString();
        }
    }

   

    [Serializable]
    [XmlRoot("DirtyWords")]
    public class DirtyWordList:StringList
    {
        public static void Load()
        {
            LoadStringListFromFile<DirtyWordList>(Constance.AppPath + ConfigurationManager.AppSettings["ProfaneWordList"]);
        }
    }

    public interface ITextBox:System.ComponentModel.ISynchronizeInvoke
    {
        string Text { get; set; }
    }

   

    public class DirtyWordChecker
    {
        public void Check(ITextBox editor)
        {
            var dirtyWords = ServiceManager.Get<DirtyWordList>();
            if (dirtyWords == null || dirtyWords.Count < 1)
                return;

            ThreadPool.QueueUserWorkItem(p =>
            {
                foreach (var item in dirtyWords)
                {
                    var txt = editor.GetProperty<string>("Text");
                    var index = txt.IndexOf(item);
                    if (index != -1)
                    {
                        editor.InvokeProperty("Text",txt.Replace(item,"".PadRight(item.Length,'*')));
                        
                    }
                }
            });
        }

       
    }
}
