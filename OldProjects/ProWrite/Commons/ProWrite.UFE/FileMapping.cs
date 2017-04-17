using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE.Entity;
using System.IO;
using ProWrite.Core;

namespace ProWrite.UFE
{
    public class FilePathMapping
    {
        //private static readonly string Root = "UFE/Data/";
        private static readonly string Root = "/mnt/sdcard/.ufe/data/";
        private static readonly string[] Paths;
        private static readonly string[] Extensions;

        static FilePathMapping()
        {
            Paths = new string[(int)FileType.Log + 1]; 
            Paths[(int)FileType.Text] = Root + "messages/{0}/texts/";
            Paths[(int)FileType.Paint] = Root + "messages/{0}/paints/";
            Paths[(int)FileType.Image] = Root + "messages/{0}/images/";
            Paths[(int)FileType.Image_Meta] = Root + "messages/{0}/images/";
            Paths[(int)FileType.Video] = Root + "messages/{0}/videos/";
            Paths[(int)FileType.Video_Meta] = Root + "messages/{0}/videos/";
            Paths[(int)FileType.MessageNailImage] = Root + "messages/{0}/";
            Paths[(int)FileType.Message] =Root +  "messages/{0}/";
            Paths[(int)FileType.TimesliceGroup] = Root + "timeslicegroups/";
            Paths[(int)FileType.Playlist] = Root + "playlists/";
            Paths[(int)FileType.Schedule] = Root + "schedules/";
            Paths[(int)FileType.TemplateMessage] =Root + "m/";
            Paths[(int)FileType.Log] = Root + "logs/";


            Extensions = new string[(int)FileType.Log + 1];
            Extensions[(int)FileType.Text] = ".png";
            Extensions[(int)FileType.Paint] = ".png";
            Extensions[(int)FileType.Image] = ".png";
            Extensions[(int)FileType.Video] = ".mpg";
            Extensions[(int)FileType.Image_Meta] = ".xml";
            Extensions[(int)FileType.Video_Meta] = ".xml";
            Extensions[(int)FileType.MessageNailImage] = ".png";
            Extensions[(int)FileType.Message] = ".xml";
            Extensions[(int)FileType.TimesliceGroup] = ".xml";
            Extensions[(int)FileType.Playlist] = ".xml";
            Extensions[(int)FileType.TimesliceGroup] = ".xml";
            Extensions[(int)FileType.Schedule] = ".xml";
            Extensions[(int)FileType.TemplateMessage] = ".xml";
            Extensions[(int)FileType.Log] = ".txt";
            
        }

        public static string GetFormatPath(FileType type,string pathId)
        {
            int index = (int)type;
            return string.Format(Paths[index], pathId);
        }

        public static string GetPath(FileType type, string pathId)
        {
            int index = (int)type;
            return Paths[index] + pathId;
        }

        public static string GetFile(FileType type, string fileId)
        {
            int index = (int)type;
            return Paths[index] + fileId + Extensions[index];
        }

        public static string GetMessagePath(string fileId)
        {
            int index = (int)FileType.Message;
            return string.Format(Paths[index], fileId) + fileId + Extensions[index];
        }

        public static string GetNailImagePath(string fileId)
        {
            int index = (int)FileType.MessageNailImage;
            return string.Format(Paths[index], fileId) + fileId + Extensions[index];
        }

        public static string GetFile(FileType type, string fileId, string parentPath)
        {
            int index = (int)type;
            switch (type)
            {
                case FileType.Image:
                case FileType.Image_Meta:
                case FileType.Paint:
                case FileType.Text:
                case FileType.Video:
                case FileType.Video_Meta:
                    return string.Format(Paths[index],parentPath) + fileId + Extensions[index];
                default:
                    return Paths[index] + fileId + Extensions[index];
            }
            
        }

        public static string GetFile(ProWrite.Core.LibraryType type, string fileId)
        {
            FileType targetType;
            switch (type)
            {
                case ProWrite.Core.LibraryType.Message:
                    targetType = FileType.Message;
                    break;
                case ProWrite.Core.LibraryType.TimeSliceGroup:
                    targetType = FileType.TimesliceGroup;
                    break;
                case ProWrite.Core.LibraryType.Playlist:
                    targetType = FileType.Playlist;
                    break;
                case ProWrite.Core.LibraryType.Schedule:
                    targetType = FileType.Schedule;
                    break;
                default:
                    targetType = FileType.Message;
                    break;
            }
            return GetFile(targetType, fileId);
        }
    }

    public class LocalFilePathMapping
    {
        private static readonly string Root = Constance.LibraryUploadDir;
        private static readonly string[] Paths;
        private static readonly string[] Extensions;

        static LocalFilePathMapping()
        {

            Paths = new string[(int)FileType.Log + 1];
            Paths[(int)FileType.Text] = Root + "Message" + Constance.DirectorySeparator + "Text" + Constance.DirectorySeparator;
            Paths[(int)FileType.Paint] = Root + "Message" + Constance.DirectorySeparator + "Paint" + Constance.DirectorySeparator;
            Paths[(int)FileType.Image] = Root + "Message" + Constance.DirectorySeparator + "Image" + Constance.DirectorySeparator;
            Paths[(int)FileType.Image_Meta] = Root + "Message" + Constance.DirectorySeparator + "Image" + Constance.DirectorySeparator;
            Paths[(int)FileType.Video] = Root + "Message" + Constance.DirectorySeparator + "Video" + Constance.DirectorySeparator;
            Paths[(int)FileType.Video_Meta] = Root + "Message" + Constance.DirectorySeparator + "Video" + Constance.DirectorySeparator;
            Paths[(int)FileType.Message] = Root + "Message" + Constance.DirectorySeparator;
            Paths[(int)FileType.TimesliceGroup] = Root + "TimesliceGroup" + Constance.DirectorySeparator;
            Paths[(int)FileType.Playlist] = Root + "Playlist" + Constance.DirectorySeparator;
            Paths[(int)FileType.Schedule] = Root + "Schedule" + Constance.DirectorySeparator;
            Paths[(int)FileType.TemplateMessage] = Root + "TemplateMessage" + Constance.DirectorySeparator;
            Paths[(int)FileType.Log] = Root + "Log" + Constance.DirectorySeparator;

            Extensions = new string[(int)FileType.Log + 1];
            Extensions[(int)FileType.Text] = ".png";
            Extensions[(int)FileType.Paint] = ".png";
            Extensions[(int)FileType.Image] = ".png";
            Extensions[(int)FileType.Video] = ".mpg";
            Extensions[(int)FileType.Image_Meta] = ".xml";
            Extensions[(int)FileType.Video_Meta] = ".xml";
            Extensions[(int)FileType.MessageNailImage] = ".png";
            Extensions[(int)FileType.Message] = ".xml";
            Extensions[(int)FileType.TimesliceGroup] = ".xml";
            Extensions[(int)FileType.Playlist] = ".xml";
            Extensions[(int)FileType.TimesliceGroup] = ".xml";
            Extensions[(int)FileType.Schedule] = ".xml";
            Extensions[(int)FileType.TemplateMessage] = ".xml";
            Extensions[(int)FileType.Log] = ".txt";

        }

        public static string GetPath(FileType type)
        {
            return Paths[(int)type];
        }

        public static string GetExtension(FileType type)
        {
            return Extensions[(int)type];
        }

        public static string GetFile(FileType type, string fileId)
        {
            int index = (int)type;
            return Paths[index] + fileId + Extensions[index];
        }

        public static string GetFile(FileType type, string fileId, string parentPath)
        {
            int index = (int)type;
            switch (type)
            {
                case FileType.Image:
                case FileType.Image_Meta:
                case FileType.Paint:
                case FileType.Text:
                case FileType.Video:
                case FileType.Video_Meta:
                    return string.Format(Paths[index], parentPath) + fileId + Extensions[index];
                default:
                    return Paths[index] + fileId + Extensions[index];
            }

        }

        public static string GetFile(ProWrite.Core.LibraryType type, string fileId)
        {
            FileType targetType;
            switch (type)
            {
                case ProWrite.Core.LibraryType.Message:
                    targetType = FileType.Message;
                    break;
                case ProWrite.Core.LibraryType.TimeSliceGroup:
                    targetType = FileType.TimesliceGroup;
                    break;
                case ProWrite.Core.LibraryType.Playlist:
                    targetType = FileType.Playlist;
                    break;
                case ProWrite.Core.LibraryType.Schedule:
                    targetType = FileType.Schedule;
                    break;
                default:
                    targetType = FileType.Message;
                    break;
            }
            return GetFile(targetType, fileId);
        }

        public static FileType ConvertType(ProWrite.Core.LibraryType type)
        {
            FileType targetType;
            switch (type)
            {
                case ProWrite.Core.LibraryType.Message:
                    targetType = FileType.Message;
                    break;
                case ProWrite.Core.LibraryType.TimeSliceGroup:
                    targetType = FileType.TimesliceGroup;
                    break;
                case ProWrite.Core.LibraryType.Playlist:
                    targetType = FileType.Playlist;
                    break;
                case ProWrite.Core.LibraryType.Schedule:
                    targetType = FileType.Schedule;
                    break;
                default:
                    targetType = FileType.Message;
                    break;
            }
            return targetType;
        }

        /// <summary>
        /// Function: Create local directories(delete files:when true)
        /// Author  : Jerry Xu
        /// Date    : 2008-12-2
        /// </summary>
        /// <param name="isDeletedOldFiles">bool</param>
        public static void CreateDirectories(bool isDeletedOldFiles)
        {
            if (!Directory.Exists(Paths[(int)FileType.Message]))
                IOHelper.CreateDirectory(Paths[(int)FileType.Message], isDeletedOldFiles);
            if (!Directory.Exists(Paths[(int)FileType.Image]))
                IOHelper.CreateDirectory(Paths[(int)FileType.Image], isDeletedOldFiles);
            if (!Directory.Exists(Paths[(int)FileType.Video]))
                IOHelper.CreateDirectory(Paths[(int)FileType.Video], isDeletedOldFiles);
            if (!Directory.Exists(Paths[(int)FileType.Text]))
                IOHelper.CreateDirectory(Paths[(int)FileType.Text], isDeletedOldFiles);
            if (!Directory.Exists(Paths[(int)FileType.Paint]))
                IOHelper.CreateDirectory(Paths[(int)FileType.Paint], isDeletedOldFiles);

            if (!Directory.Exists(Paths[(int)FileType.TimesliceGroup]))
                IOHelper.CreateDirectory(Paths[(int)FileType.TimesliceGroup], isDeletedOldFiles);
            if (!Directory.Exists(Paths[(int)FileType.Playlist]))
                IOHelper.CreateDirectory(Paths[(int)FileType.Playlist], isDeletedOldFiles);
            if (!Directory.Exists(Paths[(int)FileType.Schedule]))
                IOHelper.CreateDirectory(Paths[(int)FileType.Schedule], isDeletedOldFiles);

        }



        public static void DeleteFiles()
        {
            if (Directory.Exists(Paths[(int)FileType.Message]))
                IOHelper.DeleteFiles(Paths[(int)FileType.Message]);
            if (Directory.Exists(Paths[(int)FileType.Image]))
                IOHelper.DeleteFiles(Paths[(int)FileType.Image]);
            if (Directory.Exists(Paths[(int)FileType.Video]))
                IOHelper.DeleteFiles(Paths[(int)FileType.Video]);
            if (Directory.Exists(Paths[(int)FileType.Text]))
                IOHelper.DeleteFiles(Paths[(int)FileType.Text]);
            if (Directory.Exists(Paths[(int)FileType.Paint]))
                IOHelper.DeleteFiles(Paths[(int)FileType.Paint]);


            if (Directory.Exists(Paths[(int)FileType.TimesliceGroup]))
                IOHelper.DeleteFiles(Paths[(int)FileType.TimesliceGroup]);
            if (Directory.Exists(Paths[(int)FileType.Playlist]))
                IOHelper.DeleteFiles(Paths[(int)FileType.Playlist]);
            if (Directory.Exists(Paths[(int)FileType.Schedule]))
                IOHelper.DeleteFiles(Paths[(int)FileType.Schedule]);

        }
    }
}
