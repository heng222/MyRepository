using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE.Entity;

namespace ProWrite.UFE
{
    public interface IFtpManager
    {
        void Open();
        bool? IsConnected { get; set; }
        void Put(string fromFilePath, string toFilePath);
        void DownLoad(string fromFilePath, string toFilePath);
        void Cancel();
        void Close();
    }
}
