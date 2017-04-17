using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE;

namespace TestSSHLogin
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                //SFtpManager ftpMgr = new SFtpManager("10.10.65.96", "root", "123456");
                //ftpMgr.Open();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            Console.ReadLine();
        }
    }
}
