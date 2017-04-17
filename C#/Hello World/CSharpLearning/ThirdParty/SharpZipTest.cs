using System;
using System.IO;
using ICSharpCode.SharpZipLib.Zip;
using NUnit.Framework;

namespace CSharpLearning
{
    [TestFixture]
    class SharpZipTest
    {
        [Test]
        public void Test_ZipFile()
        {
            var zipClass = new ZipClass();

            zipClass.ZipFile(@"1.txt");
        }

        [Test]
        public void Test_UnZip()
        {
            var zipClass = new ZipClass();

            zipClass.UnZipFile(@"F:\1.zip", @"F:\1unzip");
        }
    }

    class ZipClass
    {
        /// <summary>
        /// 压缩指定的文件。
        /// </summary>
        /// <param name="sourceFilePathName">将要被压缩的文件。</param>
        /// <param name="zipFilePath">目标文件名。如果为空引用，则目标名称默认为在被压缩的文件名后加zip。</param>
        public void ZipFile(string sourceFilePathName, string zipFilePath = null)
        {
            if (string.IsNullOrWhiteSpace(sourceFilePathName)) throw new ArgumentException("要压缩的文件不能为空！"); 

            if (!File.Exists(sourceFilePathName)) throw new ArgumentException("要压缩的文件不存在！"); 

            // 
            if (string.IsNullOrWhiteSpace(zipFilePath))
            {
                zipFilePath = Path.GetFullPath(sourceFilePathName).Trim() + Path.GetFileNameWithoutExtension(sourceFilePathName) + ".zip";
            }

            using (var zipOStream = new ZipOutputStream(File.Create(zipFilePath)))
            {
                zipOStream.SetLevel(9);

                var buffer = new byte[4096];                
                var file = sourceFilePathName;

                var entry = new ZipEntry(Path.GetFileName(file)) { DateTime = DateTime.Now};

                zipOStream.PutNextEntry(entry);

                using (FileStream fs = File.OpenRead(file))
                {
                    int sourceBytes = 0;
                    do
                    {
                        sourceBytes = fs.Read(buffer, 0, buffer.Length);
                        zipOStream.Write(buffer, 0, sourceBytes);
                    } while (sourceBytes > 0);
                }

                zipOStream.Finish();
            }
        }

        /// <summary>
        /// 解压zip格式的文件。
        /// </summary>
        /// <param name="zipFilePath">压缩文件路径</param>
        /// <param name="unZipDir">解压文件存放路径,为空时默认与压缩文件同一级目录下，跟压缩文件同名的文件夹</param>
        public void UnZipFile(string zipFilePath, string unZipDir)
        {
            if (string.IsNullOrWhiteSpace(zipFilePath)) throw new ArgumentException("压缩文件不能为空！");

            if (!File.Exists(zipFilePath)) throw new ArgumentException("压缩文件不存在！");             

            //解压文件夹为空时默认与压缩文件同一级目录下，跟压缩文件同名的文件夹
            if (string.IsNullOrWhiteSpace(unZipDir))
                unZipDir = zipFilePath.Replace(Path.GetFileName(zipFilePath), Path.GetFileNameWithoutExtension(zipFilePath));
            
            if (!unZipDir.EndsWith("\\")) unZipDir += "\\";

            if (!Directory.Exists(unZipDir)) Directory.CreateDirectory(unZipDir);

            using (var zipIStream = new ZipInputStream(File.OpenRead(zipFilePath)))
            {
                ZipEntry theEntry;

                while ((theEntry = zipIStream.GetNextEntry()) != null)
                {
                    string directoryName = Path.GetDirectoryName(theEntry.Name);
                    string fileName = Path.GetFileName(theEntry.Name);

                    if (directoryName.Length > 0)
                    {
                        Directory.CreateDirectory(unZipDir + directoryName);
                    }

                    if (!directoryName.EndsWith("\\")) directoryName += "\\";

                    if (!string.IsNullOrWhiteSpace(fileName))
                    {
                        using (FileStream streamWriter = File.Create(unZipDir + theEntry.Name))
                        {

                            int size = 2048;
                            byte[] data = new byte[2048];
                            while (true)
                            {
                                size = zipIStream.Read(data, 0, data.Length);
                                if (size > 0)
                                {
                                    streamWriter.Write(data, 0, size);
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        /// <summary>
        /// 压缩指定的目录（只压缩文件夹下一级目录中的文件，文件夹及其子级被忽略）
        /// </summary>
        /// <param name="dirPath">被压缩的文件夹夹路径</param>
        /// <param name="zipFilePath">生成压缩文件的路径，为空则默认与被压缩文件夹同一级目录，名称为：文件夹名+.zip</param>
        /// <param name="err">出错信息</param>
        /// <returns>是否压缩成功</returns>
        public bool ZipDirectory(string dirPath, string zipFilePath, out string err)
        {
            err = "";

            if (dirPath == string.Empty)
            {
                err = "要压缩的文件夹不能为空！";
                return false;
            }

            if (!Directory.Exists(dirPath))
            {
                err = "要压缩的文件夹不存在！";
                return false;
            }

            //压缩文件名为空时使用文件夹名＋.zip
            if (zipFilePath == string.Empty)
            {
                if (dirPath.EndsWith("\\"))
                {
                    dirPath = dirPath.Substring(0, dirPath.Length - 1);
                }
                zipFilePath = dirPath + ".zip";
            }

            try
            {
                string[] filenames = Directory.GetFiles(dirPath);
                using (ZipOutputStream s = new ZipOutputStream(File.Create(zipFilePath)))
                {
                    s.SetLevel(9);
                    byte[] buffer = new byte[4096];
                    foreach (string file in filenames)
                    {
                        ZipEntry entry = new ZipEntry(Path.GetFileName(file));
                        entry.DateTime = DateTime.Now;
                        s.PutNextEntry(entry);
                        using (FileStream fs = File.OpenRead(file))
                        {
                            int sourceBytes;
                            do
                            {
                                sourceBytes = fs.Read(buffer, 0, buffer.Length);
                                s.Write(buffer, 0, sourceBytes);
                            } while (sourceBytes > 0);
                        }
                    }
                    s.Finish();
                    s.Close();
                }
            }
            catch (Exception ex)
            {
                err = ex.Message;
                return false;
            }

            return true;
        }

    }
}
