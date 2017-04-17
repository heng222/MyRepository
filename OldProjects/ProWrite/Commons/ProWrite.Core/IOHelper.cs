//---------------------------------------------------------------------
//
// File: IOHelper.cs
//
// Description:
// IO Helper class
//
// Author: Kevin 2008-7-1
//
// Modification History
//			Louis 2008-7-04 add create library, image, video folder
//          Jerry Xu 2009-1-4 Add method:IsImageFile(string imagePath)
//          Jerry Xu 2009-5-12 Update method"GetLibraryFileName(string fileName, string libraryFileName, LibraryType type)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.IO;
using log4net;
using System.Drawing.Imaging;
using ProWrite.Core;

namespace ProWrite.Core
{
    /// <summary>
    /// IO helper class
    /// </summary>
    public abstract class IOHelper
    {
        private static readonly ILog _log = LogManager.GetLogger(typeof(IOHelper));
        /// <summary>
        /// save temp image
        /// </summary>
        /// <param name="image"></param>
        /// <returns></returns>
        public static string SaveTempImage(Image image, string imageName)
        {
            return SaveTempImage(image, imageName, false);
        }

        /// <summary>
        /// save temp image
        /// </summary>
        /// <param name="image"></param>
        /// <returns></returns>
        public static string SaveTextImage(Image image, string imageName)
        {
            return SaveTextImage(image, imageName, false);
        }

        public static string GenerateTempImagePath()
        {
            CreateImageTempDirectory(false);
            return Constance.ImageTempDir + DateTime.Now.Ticks.ToString() + ".jpg";
        }
        /// <summary>
        /// save temp image
        /// </summary>
        /// <param name="image"></param>
        /// <param name="imageName"></param>
        /// <param name="isDeleteOldImages"></param>
        /// <returns></returns>
        public static string SaveTempImage(Image image, string imageName, bool isDeleteOldImages)
        {
            if (image == null)
                return null;

            string strDir = Constance.ImageTempDir;
            string imageUrl = null;

            try
            {
                CreateDirectory(strDir, isDeleteOldImages);

                imageUrl = strDir + imageName + System.DateTime.Now.Ticks.ToString() + ".bmp";

                image.Save(imageUrl, ImageFormat.Bmp);
            }
            catch (IOException ex)
            {
                _log.Debug("SaveTempImage Error.ImageName<" + imageName + ">");
                _log.Error(ex.Message, ex);
            }
            return imageUrl;
        }


        /// <summary>
        /// save temp image
        /// </summary>
        /// <param name="image"></param>
        /// <param name="imageName"></param>
        /// <param name="isDeleteOldImages"></param>
        /// <returns></returns>
        public static string SaveTextImage(Image image, string imageName, bool isDeleteOldImages)
        {
            if (image == null)
                return null;

            string strDir = Constance.LibraryTextDir;
            string imageUrl = null;

            try
            {
                CreateDirectory(strDir, isDeleteOldImages);

                imageUrl = strDir + imageName + System.DateTime.Now.Ticks.ToString() + ".gif";

                image.Save(imageUrl, ImageFormat.Gif);
            }
            catch (IOException ex)
            {
                _log.Error("SaveTextImageError.ImageName<" + imageName);
                _log.Error(ex.Message, ex);
            }
            return imageUrl;
        }

        /// <summary>
        /// Function: Delete files in directory 
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
        /// </summary>
        /// <param name="path">directory</param>
        public static void DeleteFiles(string path)
        {
            if (!Directory.Exists(path))
                return;
            DirectoryInfo dir = new DirectoryInfo(path);
            FileInfo[] files = dir.GetFiles();
            if (files != null && files.Length > 0)
            {
                foreach (FileInfo file in files)
                {
                    RemoveFile(path + Constance.DirectorySeparator + file.Name);
                }
            }

        }


        /// <summary>
        /// Function: Delete files in directory 
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
        /// </summary>
        /// <param name="path">directory</param>
        public static void DeleteAllFiles(string path)
        {
            if (!Directory.Exists(path))
                return;
            DirectoryInfo dir = new DirectoryInfo(path);

            Action<DirectoryInfo[]> onDeleteAllFilesByDirs = null;
            Action<DirectoryInfo> onDeleteAllFiles = p =>
            {
                FileInfo[] files = p.GetFiles();
                if (files != null && files.Length > 0)
                {
                    foreach (FileInfo file in files)
                    {
                        RemoveFile(p.FullName + Constance.DirectorySeparator + file.Name);
                    }
                }

                var dirs = p.GetDirectories();
                if (dirs != null && dirs.Length > 0)
                    onDeleteAllFilesByDirs(dirs);
            };

            onDeleteAllFilesByDirs = p =>
            {
                foreach (var item in p)
                    onDeleteAllFiles(item);
            };

            onDeleteAllFiles(dir);
        }


        /// <summary>
        /// Remove file
        /// </summary>
        /// <param name="fileName">file name</param>
        /// <returns>success return true, fail return false</returns>
        public static bool RemoveFile(string fileName)
        {
            try
            {
                if (File.Exists(fileName) && SetFileAttribute(fileName, FileAttributes.Normal))
                {
                    //FileInfo file = new FileInfo(fileName);
                    //file.Open(FileMode.Truncate);
                    //file.Delete();
                    //file = null;
                    File.Delete(fileName);
                }
                else
                    return false;
            }
            catch (IOException ex)
            {
                _log.Error("RemoveFile Error. FileName<" + fileName + ">");
                _log.Error(ex.Message, ex);
                return false;
            }
            return true;
        }

        public static Image GetImageFromFile(string imagePath)
        {
            try
            {
                if (File.Exists(imagePath))
                {
                    IOHelper.SetFileAttribute(imagePath, FileAttributes.Normal);
                    using (FileStream stream = new FileStream(imagePath, FileMode.Open, FileAccess.Read, FileShare.Read))
                    {
                        Image image = Image.FromStream(stream);
                        stream.Dispose();
                        IOHelper.SetFileAttribute(imagePath, FileAttributes.ReadOnly);
                        return image;
                    }
                }
            }
            catch (Exception ex)
            {
                _log.Error("Get ImageFromFile Error.imagePath<" + imagePath + ">");
                _log.Error(ex.Message, ex);
            }

            return null;
        }

        /// <summary>
        /// Function: This image file is valid.
        /// Author  : Jerry Xu
        /// Date    : 2009-1-4
        /// </summary>
        /// <param name="imagePath">Image file path</param>
        /// <returns>bool</returns>
        public static bool IsImageFile(string imagePath)
        {
            try
            {
                if (File.Exists(imagePath))
                {
                    IOHelper.SetFileAttribute(imagePath, FileAttributes.Normal);
                    using (FileStream stream = new FileStream(imagePath, FileMode.Open))
                    {
                        Image image = Image.FromStream(stream);
                        stream.Dispose();
                        IOHelper.SetFileAttribute(imagePath, FileAttributes.ReadOnly);
                        if (image != null)
                        {
                            image.Dispose();
                            image = null;
                            return true;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                _log.Error("Get ImageFromFile Error.imagePath<" + imagePath + ">");
                _log.Error(ex.Message, ex);
            }

            return false;
        }

        /// <summary>
        /// Create directory
        /// </summary>
        /// <param name="strDir"></param>
        /// <param name="isDeleteOldFiles"></param>
        public static void CreateDirectory(string strDir, bool isDeleteOldFiles)
        {
            try
            {
                if (!Directory.Exists(strDir))
                {
                    Directory.CreateDirectory(strDir);
                }
                else
                {
                    //Delete files in dir
                    if (isDeleteOldFiles)
                        DeleteFiles(strDir);
                }
            }
            catch (IOException ex)
            {
                _log.Error("Create Directory <" + strDir + "> Error.");
                _log.Error(ex.Message, ex);
            }
        }

        /// <summary>
        /// Create Image temp directory
        /// </summary>
        /// <param name="isDeletedOldFiles"></param>
        public static void CreateImageTempDirectory(bool isDeletedOldFiles)
        {
            CreateDirectory(Constance.ImageTempDir, isDeletedOldFiles);
        }

        /// <summary>
        /// Create System directory
        /// </summary>
        /// <param name="isDeletedOldFiles"></param>
        public static void CreateSystemDirectory(bool isDeletedOldFiles)
        {
            CreateDirectory(Constance.DataPath, isDeletedOldFiles);
            CreateDirectory(Constance.LibraryDir, isDeletedOldFiles);
            CreateDirectory(Constance.LibraryImageDir, isDeletedOldFiles);
            CreateDirectory(Constance.LibraryVideoDir, isDeletedOldFiles);
            CreateDirectory(Constance.LibraryNailImageDir, isDeletedOldFiles);
            //CreateDirectory(Constance.EffectDataDir, isDeletedOldFiles);
            CreateDirectory(Constance.LibraryTextDir, true);
            CreateDirectory(Constance.LayoutDir, isDeletedOldFiles);
            CreateDirectory(Constance.SignImageDir, false);
            CreateImageTempDirectory(true);
        }

        public static bool CopyLibraryFile(string sourceFile, string libraryName, LibraryType type)
        {

            if (string.IsNullOrEmpty(sourceFile))
                return false;

            try
            {
                if (!File.Exists(sourceFile))
                    return false;

                if (string.IsNullOrEmpty(libraryName))
                    libraryName = Path.GetFileName(sourceFile);

                string targetName = libraryName;
                if (type == LibraryType.Image)
                    targetName = Constance.LibraryImageDir + libraryName;
                else if (type == LibraryType.Video)
                    targetName = Constance.LibraryVideoDir + libraryName;
                else
                    return false;

                if (File.Exists(targetName))
                    return false;

                File.Copy(sourceFile, targetName, false);
                return true;

            }
            catch (Exception ex)
            {
                _log.Error("Copy library file error: SourceFile<" + sourceFile + ">; LibraryName<" + libraryName + ">.Type<" + type.ToString() + ">");
                _log.Error(ex.Message, ex);
                return false;
            }

        }

        public static bool CopyLibraryFile(string sourceFile, string libraryName)
        {

            if (string.IsNullOrEmpty(sourceFile))
                return false;

            try
            {
                if (!File.Exists(sourceFile))
                    return false;

                if (File.Exists(libraryName))
                    return false;

                SetFileAttribute(sourceFile, FileAttributes.Normal);
                File.Copy(sourceFile, libraryName, false);
                SetFileAttribute(libraryName, FileAttributes.ReadOnly);

                return true;

            }
            catch (Exception ex)
            {
                _log.Error("Copy library file error: SourceFile<" + sourceFile + ">; LibraryName<" + libraryName + ">");
                _log.Error(ex.Message, ex);
                return false;
            }

        }

        public static string[] ImageFiles
        {
            get
            {
                string[] imagFiles = null;
                string[] tempFiles = null;

                List<string> allFiles = null;
                if (!Directory.Exists(Constance.LibraryImageDir))
                    return null;

                try
                {
                    allFiles = new List<string>();
                    string[] filesType = new string[] { Constance.FileExtensionName.Bmp_All, Constance.FileExtensionName.Gif_All, Constance.FileExtensionName.Jpeg_All, Constance.FileExtensionName.Jpg_All, Constance.FileExtensionName.Png_All, Constance.FileExtensionName.Tif_All, Constance.FileExtensionName.Tiff_All };
                    allFiles = new List<string>();

                    foreach (string filetype in filesType)
                    {
                        tempFiles = Directory.GetFiles(Constance.LibraryImageDir, filetype);
                        if (tempFiles.Length > 0)
                        {
                            for (int i = 0; i < tempFiles.Length; i++)
                            {
                                allFiles.Add(tempFiles[i]);
                            }
                        }
                    }

                    imagFiles = allFiles.ToArray();
                    //Directory.GetFiles(Constance.LibraryImageDir, Constance.FileExtensionName.Bmp_All).CopyTo(imagFiles, 0);
                    //Directory.GetFiles(Constance.LibraryImageDir, Constance.FileExtensionName.Gif_All).CopyTo(imagFiles, 0);
                    //Directory.GetFiles(Constance.LibraryImageDir, Constance.FileExtensionName.Jpeg_All).CopyTo(imagFiles, 0);
                    //Directory.GetFiles(Constance.LibraryImageDir, Constance.FileExtensionName.Jpg_All).CopyTo(imagFiles, 0);
                    //imagFiles = Directory.GetFiles(Constance.LibraryImageDir, Constance.FileFilter.ImagePoint|Constance.FileExtensionName.Bmp);
                }
                catch (Exception ex)
                {
                    _log.Error("Picture Files Error");
                    _log.Error(ex.Message, ex);
                }
                return imagFiles;

            }
        }

        public static string[] VideoFiles
        {
            get
            {
                string[] files = null;
                string[] tempFiles = null;

                List<string> allFiles = null;
                if (!Directory.Exists(Constance.LibraryVideoDir))
                    return null;

                try
                {
                    string[] filesType = new string[] { Constance.FileExtensionName.AVI_All, Constance.FileExtensionName.Mpeg_2_All, Constance.FileExtensionName.Wmv_All };
                    allFiles = new List<string>();

                    foreach (string filetype in filesType)
                    {
                        tempFiles = Directory.GetFiles(Constance.LibraryVideoDir, filetype);
                        if (tempFiles.Length > 0)
                        {
                            for (int i = 0; i < tempFiles.Length; i++)
                            {
                                allFiles.Add(tempFiles[i]);
                            }
                        }
                    }

                    files = allFiles.ToArray();
                    //files = Directory.GetFiles(Constance.LibraryVideoDir);
                }
                catch (Exception ex)
                {
                    _log.Error("VideoFile Error");
                    _log.Error(ex.Message, ex);
                }
                return files;

            }
        }

        public static void RemoveNailImage(string file)
        {
            if (string.IsNullOrEmpty(file))
                return;
            // file = Constance.LibraryNailImageDir + file;
            RemoveFile(file);
        }

        public static void SaveImage(Image image, string file)
        {
            SaveImage(image, file, ImageFormat.Bmp);
        }

        public static void SaveImage(Image image, string file, ImageFormat fmt)
        {
            Check.Assert(image != null);
            Check.Assert(!string.IsNullOrEmpty(file));

            try
            {
                image.Save(file, fmt);
                //SetFileAttribute(file, FileAttributes.Normal);

                SetFileAttribute(file, FileAttributes.ReadOnly);
                
            }
            catch (Exception ex)
            {
                _log.Error("Save Image Error, file <" + file + ">");
                _log.Error(ex.Message, ex);
            }
        }

        public static bool SetFileAttribute(string fileName, FileAttributes at)
        {
            try
            {

                if (File.GetAttributes(fileName) != at)
                    File.SetAttributes(fileName, at);


            }
            catch (Exception ex)
            {
                _log.Error("Set FileAttribute Error. FileName<" + fileName + ">");
                _log.Error(ex.Message, ex);
                return false;
            }
            return true;
        }

        public static long GetFileLength(string file)
        {
            Check.Assert(!string.IsNullOrEmpty(file));

            try
            {
                if (!File.Exists(file))
                    return 0;
                return new FileInfo(file).Length;
            }
            catch (Exception ex)
            {
                _log.Error("GetFileLength Error.File<" + file + ">");
                _log.Error(ex.Message, ex);
            }

            return 0;
        }

        public static byte[] ReadAllBytes(string file)
        {
            Check.Assert(!string.IsNullOrEmpty(file));

            try
            {
                if (!File.Exists(file))
                    return null;
                return File.ReadAllBytes(file);
            }
            catch (Exception ex)
            {
                _log.Error("ReadAllBytes Error.file<" + file + ">");
                _log.Error(ex.Message, ex);
            }

            return null;
        }

        public static void WriteAllBytes(string file, byte[] bytes)
        {
            Check.Require(file, "file", Check.NotNullOrEmpty);
            Check.Require(bytes, "bytes", Check.NotNull);

            try
            {
                if (!File.Exists(file))
                    File.WriteAllBytes(file, bytes);
            }
            catch (Exception ex)
            {
                _log.Error("WriteAllbytes Error.File<" + file + ">");
                _log.Error(ex.Message, ex);
            }

        }

        public static bool RenameFile(string newName, string oldName)
        {
            try
            {
                if (File.Exists(oldName))
                {
                    SetFileAttribute(oldName, FileAttributes.Normal);
                    File.Move(oldName, newName);
                    SetFileAttribute(newName, FileAttributes.ReadOnly);
                    return true;
                }
                return false;
            }
            catch (Exception ex)
            {
                _log.Error("RenameFile Erorr. newName<" + newName + ">;oldName<" + oldName + ">");
                _log.Error(ex.Message, ex);
                return false;
            }

        }

        public static LibraryType GetLibraryType(string fileType)
        {
            if (string.IsNullOrEmpty(fileType))
                return LibraryType.Image;
            switch (fileType)
            {
                case Constance.FileExtensionName.AVI:
                case Constance.FileExtensionName.Mpeg_2:
                case Constance.FileExtensionName.Wmv:
                    return LibraryType.Video;
                case Constance.FileExtensionName.Bmp:
                case Constance.FileExtensionName.Jpeg:
                case Constance.FileExtensionName.Jpg:
                case Constance.FileExtensionName.Gif:
                default:
                    return LibraryType.Image;

            }
        }

        public static FileExistType IsExist1(string fileName, string libraryFileName, LibraryType type)
        {
            if (string.IsNullOrEmpty(fileName) || !File.Exists(fileName))
                return FileExistType.No;
            fileName = fileName.ToLower();

            //target file
            string libraryName;

            string extName = Path.GetExtension(fileName);
            if (string.IsNullOrEmpty(libraryFileName))
                libraryName = Path.GetFileName(fileName);
            else
            {
                string tempLibraryFileName = null;
                tempLibraryFileName = libraryFileName.ToLower();
                if (tempLibraryFileName.Length <= extName.Length)
                    libraryName = libraryFileName + extName;
                else
                    if (!tempLibraryFileName.Substring(tempLibraryFileName.Length - extName.Length - 1, extName.Length).Equals(extName))
                        libraryName = libraryFileName + extName;
                    else
                        libraryName = libraryFileName;

            }
            string libraryPath = Constance.LibraryImageDir;
            if (type == LibraryType.Image)
                libraryPath = Constance.LibraryImageDir;
            else if (type == LibraryType.Video)
                libraryPath = Constance.LibraryVideoDir;
            string targetFileName = libraryPath + libraryName;

            //judge
            if (File.Exists(targetFileName))
            {
                SetFileAttribute(fileName, FileAttributes.Normal);
                SetFileAttribute(targetFileName, FileAttributes.Normal);
                if (FileCompare(fileName, targetFileName))
                {
                    SetFileAttribute(fileName, FileAttributes.ReadOnly);
                    SetFileAttribute(targetFileName, FileAttributes.ReadOnly);
                    return FileExistType.Yes;
                }
                SetFileAttribute(fileName, FileAttributes.ReadOnly);
                SetFileAttribute(targetFileName, FileAttributes.ReadOnly);
                return FileExistType.SizeNoEqual;
            }
            else
                return FileExistType.No;
        }

        public static FileExistType IsExist(string fileName, string libraryFileName, LibraryType type)
        {
            if (string.IsNullOrEmpty(fileName) || !File.Exists(fileName))
                return FileExistType.No;
            //fileName = fileName.ToLower();

            //target file
            string libraryName;

            string extName = Path.GetExtension(fileName);
            if (string.IsNullOrEmpty(libraryFileName))
                libraryName = Path.GetFileName(fileName);
            else
            {
                string tempLibraryFileName = null;
                tempLibraryFileName = libraryFileName;
                if (tempLibraryFileName.Length <= extName.Length)
                    libraryName = libraryFileName + extName;
                else
                    if (!tempLibraryFileName.Substring(tempLibraryFileName.Length - extName.Length - 1, extName.Length).Equals(extName))
                        libraryName = libraryFileName + extName;
                    else
                        libraryName = libraryFileName;

            }
            string libraryPath = Constance.LibraryImageDir;
            if (type == LibraryType.Image)
                libraryPath = Constance.LibraryImageDir;
            else if (type == LibraryType.Video)
                libraryPath = Constance.LibraryVideoDir;
            string targetFileName = libraryPath + libraryName;

            //judge
            if (File.Exists(targetFileName))
                return FileExistType.Yes;
            //{
            //SetFileAttribute(fileName, FileAttributes.Normal);
            //SetFileAttribute(targetFileName, FileAttributes.Normal);
            //if (FileCompare(fileName, targetFileName))
            //{
            //    SetFileAttribute(fileName, FileAttributes.ReadOnly);
            //    SetFileAttribute(targetFileName, FileAttributes.ReadOnly);
            //    return FileExistType.Yes;
            //}
            //SetFileAttribute(fileName, FileAttributes.ReadOnly);
            //SetFileAttribute(targetFileName, FileAttributes.ReadOnly);
            //return FileExistType.SizeNoEqual;
            //}
            else
                return FileExistType.No;
        }

        public static string GetLibraryFileName(string fileName, string libraryFileName, LibraryType type)
        {
            try
            {
                //target file
                string libraryName;
                string extName = Path.GetExtension(fileName);
                //libraryFileName = Path.GetFileNameWithoutExtension(libraryFileName);
                if (string.IsNullOrEmpty(libraryFileName))
                    libraryName = Path.GetFileName(fileName);
                else
                {
                    string tempLibraryFileName = null;
                    tempLibraryFileName = libraryFileName;
                    if (tempLibraryFileName.Length <= extName.Length)
                        libraryName = libraryFileName + extName;
                    else
                        if (!tempLibraryFileName.Substring(tempLibraryFileName.Length - extName.Length - 1, extName.Length).Equals(extName))
                            libraryName = libraryFileName + extName;
                        else
                            libraryName = libraryFileName;
                }
                string libraryPath = Constance.LibraryImageDir;
                if (type == LibraryType.Image)
                    libraryPath = Constance.LibraryImageDir;
                else if (type == LibraryType.Video)
                    libraryPath = Constance.LibraryVideoDir;
                return libraryPath + libraryName;

            }
            catch (Exception ex)
            {
                _log.Error("GetLibraryFileName Error. fileName<" + fileName + ">; librarfilename<" + libraryFileName + ">");
                _log.Error(ex.Message, ex);
                return string.Empty;
            }

        }

        private static bool FileCompare(string sourcePath, string destPath)
        {
            try
            {
                if (sourcePath.ToLower() == destPath.ToLower())
                    return true;

                int file1byte = 0;
                int file2byte = 0;

                using (FileStream sourceStream = new FileStream(sourcePath, FileMode.Open))
                using (FileStream destStream = new FileStream(destPath, FileMode.Open))
                {
                    if (sourceStream.Length != destStream.Length)
                    {
                        sourceStream.Close();
                        destStream.Close();
                        return false;
                    }

                    while (file1byte == file2byte && file1byte != -1)
                    {
                        file1byte = sourceStream.ReadByte();
                        file2byte = destStream.ReadByte();
                    }
                }

                return file1byte == file2byte;

            }

            catch (Exception ex)
            {
                _log.Error("FileCompare Error.sourcePath<" + sourcePath + ">;destPath<" + destPath + ">");
                _log.Error(ex.Message, ex);
                return false;
            }
        }

        public static bool FileContentCompare(byte[] source, byte[] dest)
        {
            try
            {
                if (source == null || dest == null)
                    return false;
                if (source.Length != dest.Length)
                    return false;

                for (int i = 0; i < source.Length; i++)
                {
                    if (source[i] != dest[i])
                        return false;
                }
                return true;
            }

            catch (Exception ex)
            {
                _log.Error("FileContentCompare Error.");
                _log.Error(ex.Message, ex);
                return false;
            }
        }

        public static bool FileIsUsed(string fileName)
        {
            bool inUse = true;
            FileStream fs = null;
            fs = new FileStream(fileName, FileMode.Open);
            if (fs == null)
                inUse = false;
            else
            {
                if (fs.CanWrite)
                    inUse = false;
                else
                    inUse = true;
            }
            fs.Close();
            fs.Dispose();
            return inUse;
        }        
        
    }

}