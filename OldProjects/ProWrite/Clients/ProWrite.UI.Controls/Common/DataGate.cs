//---------------------------------------------------------------------
//
// File: DataGate.cs
//
// Description:
// Data Gate，the class is gate of UI operate data 
//
// Author: Kevin
//
// Modify history:
//      Jerry Xu 2008-6-20 add GetPlayListsByName
//      Jerry Xu 2008-6-26 PlayList and PlayLists to PlayListsInfo
//      Jerry Xu 2008-6-30 PlayListInfo add fields and change data type
//      Jerry Xu 2008-6-30 DsLibrary to DsLibraries
//      Jerry Xu 2008-6-30 Library to LibraryInfo
//      Jerry Xu 2008-6-30 Method's parameters's type is the same to their fields's type
//      Jerry Xu 2008-6-30 if the Method's return value is array then list
//      Jerry Xu 2008-7-2  Add methods:GetLibraryByNameAndType,ToLibrary
//      Jerry Xu 2008-7-4  rename PlayList's L to l
//      Jerry Xu 2008-7-7  Add the property of CurrentLibraryGroup.
//      Jerry Xu 2008-7-7  Add the method of SetCurrentLibraryGroup.
//      Jerry Xu 2008-7-17 Add the method:ToArrayTimeSliceGroupItem
//      Jerry Xu 2008-7-17 Add the method:SetCurrentPlayMessageAdapterName
//      Jerry Xu 2008-7-17 Add the method:SetPlaylistTimeSlieceGroupCurrentMessageAdapterName
//      Jerry Xu 2008-7-18 Update method:ToArrayTimeSliceGroupItem
//      Jerry Xu 2008-7-21 Update method:SetCurrentPlayMessageAdapterName
//      Jerry Xu 2008-7-24 Update method:SetCurrentPlayMessageAdapterName(Delete IsEmpty in if)
//      Jerry Xu 2008-7-25 Add method:CreateDefaultTimeSliceGroup
//      Jerry Xu 2008-7-25 Update method:SetCurrentLibraryGroup(Add CreateDefaultTimeSliceGroup)
//      Jerry Xu 2009-7-27 Update method:AddSession
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Reflection;
using System.Text;
using log4net;
using System.IO;
using System.Net;
using System.Data;
using ProWrite.Entity;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library;
using ProWrite.Core;
using System.Windows.Forms;
using ProWrite.UI.Controls.Common.Messages;
using System.Drawing.Imaging;
using ProWrite.Resources;
using ProWrite.Entity.Live;
using ProWrite.DataProviders;

namespace ProWrite.UI.Controls.Common
{
    /// <summary>
    /// Data agent
    /// </summary>
    public class DataGate
    {
        public static readonly DataProvider Provider;
        static DataGate()
        {
            IOHelper.CreateSystemDirectory(false);
            Log.Info("DataProvider Start.");
            Provider = new DataProvider();
            ServiceManager.Add<IDataProvider>(Provider);
            Log.Info("DataProvider Done.");
            if (Provider.Get().LibraryGroups.Count == 0)
                AddLibraryGroup("Library Group 1");
            if (LibraryGroup.Current == null)
                LibraryGroup.Current = Provider.Get().LibraryGroups[0];
        }

        public static readonly ILog Log = LogManager.GetLogger("ProWrite");
        /// <summary>
        /// Get entity gather
        /// </summary>
        public static ProjectInfo Project
        {
            get { return Provider.Get(); }
        }

        /// <summary>
        /// Get entity gather
        /// </summary>
        public static List<SessionInfo> SessionInfos
        {
            get { return Project.SessionInfos; }
        }


        /// <summary>
        /// Function:Set current library group.
        /// Author:Jerry
        /// Crate DateTime:2008-7-7
        /// </summary>
        /// <param name="pName">string:LibraryGroupName</param>
        public static bool AddLibraryGroup(string pName)
        {
            bool flag = false;
            if (pName != string.Empty)
            {
                LibraryGroup group = Project.LibraryGroups.GetByName(pName);
                if (group != null)
                {
                    LibraryGroup.Current = group;
                    flag = true;
                }
                else
                {                    
                    flag = Provider.Get().LibraryGroups.Add(new LibraryGroup(pName));
                    LibraryGroup.Current = Provider.Get().LibraryGroups.GetByName(pName);
                }

                if (flag)
                    Update();
            }

            return flag;
        }

        /// <summary>
        /// Function:Create default time slice group
        /// Author: Jerry Xu
        /// Date:2008-7-25        
        /// </summary>
        /// <returns>TimeSliceGroupInfo</returns>
        private static TimeSliceGroupInfo CreateDefaultTimeSliceGroup()
        {
            TimeSliceGroupInfo defaultGroup = new TimeSliceGroupInfo();
            defaultGroup.Length = 8;
            defaultGroup.Name = Resource.GetString(Resource.Strings.PlayListDefaultTimeSliceGroupName);
            defaultGroup.IsRandom = false;
            return defaultGroup;
        }

        public static void Load()
        {
            Provider.Get();
        }

        /// <summary>
        /// Get sign group tree
        /// </summary>
        public static SignGroupTree GroupTree
        {
            get { return Provider.Get().RootGroup; }
        }


        public static string GetMsgById(string id)
        {
            return Resource.GetString(id);
        }


        /// <summary>
        /// Update entity gather
        /// </summary>
        public static bool Update()
        {
            bool flag = Provider.Update();
            KeyGenerator.Save();
            return flag;
        }

        /// <summary>
        /// 
        /// </summary>
        public static void InitializeSystemData()
        {
            Provider.Update(new ProjectInfo());
            LocalMessageBus.Send(null, new InitSystemData());
            LocalMessageBus.Send(null, new DataChangedMessage(PWDataType.Dashboard));
            LocalMessageBus.Send(null, new ActiveChange(null, false));
            IOHelper.DeleteAllFiles(Constance.DataPath);
        }

        public static bool DeleteUserData()
        {
            return true;
        }

        public static void Dispose()
        {
            Provider.Dispose();
        }



        /// <summary>
        /// upload shape
        /// </summary>
        public static void Upload(string url)
        {
            string filePath = "";
            //openFileDialog.ShowDialog();
            filePath = url;
            //string urlString = "..//ProWrite//UControl//Resources";
            //string path = AppDomain.CurrentDomain.BaseDirectory;
            string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\";
            string urlString = path + "Image";

            if (!Directory.Exists(urlString))
            {
                Directory.CreateDirectory(urlString);// File.Create(urlString);
            }
            UpLoadFile(filePath, urlString);
        }


        public void GetFrames(string pPath, string pSavedPath)
        {
            Image gif = Image.FromFile(pPath);
            FrameDimension fd = new FrameDimension(gif.FrameDimensionsList[0]);

            //获取帧数(gif图片可能包含多帧，其它格式图片一般仅一帧)
            int count = gif.GetFrameCount(fd);

            //以Jpeg格式保存各帧
            for (int i = 0; i < count; i++)
            {
                gif.SelectActiveFrame(fd, i);
                gif.Save(pSavedPath + "\\frame_" + i + ".jpg", ImageFormat.Jpeg);
            }
        }



        /// <summary>
        /// upload shape
        /// </summary>
        /// <param name="fileNamePath">The file's full path</param>
        /// <param name="uriString">Save url</param>
        private static void UpLoadFile(string fileNamePath, string uriString)
        {
            string NewFileName = fileNamePath.Substring(fileNamePath.LastIndexOf("\\") + 1);
            string fileNameExt = NewFileName.Substring(NewFileName.LastIndexOf(".") + 1);
            if (uriString.EndsWith("/") == false) uriString = uriString + "/";



            if (NewFileName.Contains(".gif")
                || NewFileName.Contains(".Gif")
                || NewFileName.Contains(".GIF"))
            {
                try
                {
                    Image gif = Image.FromFile(fileNamePath);
                    FrameDimension fd = new FrameDimension(gif.FrameDimensionsList[0]);

                    //获取帧数(gif图片可能包含多帧，其它格式图片一般仅一帧)
                    int count = gif.GetFrameCount(fd);

                    //以Jpeg格式保存各帧

                    gif.SelectActiveFrame(fd, 0);
                    gif.Save(uriString + NewFileName.Substring(0, NewFileName.IndexOf(".")) + ".jpg", ImageFormat.Jpeg);
                    return;
                }
                catch
                {
                    return;
                }
            }
            try
            {
                uriString = uriString + NewFileName;
                WebClient myWebClient = new WebClient();
                myWebClient.Credentials = CredentialCache.DefaultCredentials;
                FileStream fs = new FileStream(fileNamePath, FileMode.Open, FileAccess.Read);
                //FileStream fs = OpenFile();
                BinaryReader r = new BinaryReader(fs);

                byte[] postArray = r.ReadBytes((int)fs.Length);
                Stream postStream = myWebClient.OpenWrite(uriString, "PUT");
                if (postStream.CanWrite)
                {
                    postStream.Write(postArray, 0, postArray.Length);
                }
                else
                {
                    MsgBox.Warning("At present can't be written documents ！");
                }
                postStream.Close();
            }
            catch
            {
                //MsgBox.Warning("Document failed to upload, please try again later!");
            }
        }

        private static List<LibraryItemColor> _libraryItemColors;
        public static List<LibraryItemColor> LibraryItemColors
        {
            get
            {
                if (_libraryItemColors == null || _libraryItemColors.Count < 1)
                {
                    _libraryItemColors = new List<LibraryItemColor>();
                    Type t = typeof(System.Drawing.Color);
                    PropertyInfo[] properties = t.GetProperties(BindingFlags.Static | BindingFlags.Public);
                    foreach (PropertyInfo p in properties)
                    {
                        Color c = (Color)t.InvokeMember(p.Name, BindingFlags.GetProperty, null, typeof(Color), null);

                        LibraryItemColor itemColor = new LibraryItemColor(c.Name, c);
                        _libraryItemColors.Add(itemColor);
                    }
                }
                return _libraryItemColors;
            }
        }

        public static int FindColorIndex(Color color)
        {
            return LibraryItemColors.FindIndex(delegate(LibraryItemColor itemColor)
                                                {
                                                    return color == itemColor.Color;
                                                });
        }

        public static Color FindColorByIndex(int lableId)
        {
            if (lableId != -1)
                return LibraryItemColors[lableId].Color;
            return Color.Empty;
        }

        #region Set current play message adapter name
        /// <summary>
        /// Function:Set current play message adapter name
        /// Author:Jerry Xu
        /// Date:2008-7-17
        /// </summary>
        /// <param name="adapter">TimeSliceGroupAdapterInfo</param>
        /// <param name="flag">bool</param>
        /// <returns>Message adapter name:string</returns>
        private static string SetCurrentPlayMessageAdapterName(TimeSliceGroupAdapterInfo adapter, bool flag)
        {
            string messageAdapterName = string.Empty;
            if (adapter != null)
            {
                if (adapter.Target != null)
                {
                    TimeSliceGroupInfo group = adapter.Target as TimeSliceGroupInfo;
                    List<MessageAdapterInfo> messages;
                    int currentIndex = 0;//Current play message adapter index

                    messages = new List<MessageAdapterInfo>();
                    for (int i = 0; i < group.Items.Length; i++)
                    {
                        if (group.Items[i].IsActive)
                            messages.Add(group.Items[i]);
                    }
                    //Set random message adapter
                    if (group.IsRandom && messages.Count > 2)
                    {

                        //Set current play message name
                        if (group.Items.Length == 1)
                            currentIndex = 0;
                        else
                        {

                            //Set random message adapter index
                            if (messages != null && messages.Count > 1)
                            {
                                int max = messages.Count;
                                if (max == 1)
                                    currentIndex = 0;
                                else
                                {
                                    Random ran = new Random();
                                    currentIndex = ran.Next(max);
                                }
                                return messages[currentIndex].Name;
                            }
                        }
                        messageAdapterName = group.Items[currentIndex].Name;
                    }
                    else//Set no random message adapter
                    {
                        //Set current play message name
                        if (group.Items.Length > 0)
                        {
                            //Re make a current message adapter name
                            if (flag)
                                messageAdapterName = group.Items[0].Name;
                            else
                            {
                                //Continue make a current message adapter name
                                int lastIndex = 0;//Last play message adapter index
                                //Get last play message adapter index
                                for (int i = 0; i < group.Items.Length; i++)
                                {
                                    if (group.Items[i].Name == adapter.CurrentMessageAdapterName)
                                        lastIndex = i;
                                }
                                //Set current play message adapter index
                                if (lastIndex == group.Items.Length - 1)
                                    currentIndex = 0;
                                else
                                {
                                    if (group.Items.Length == 1)
                                        currentIndex = 0;
                                    else
                                    {
                                        bool curFlag = true;
                                        for (int i = lastIndex + 1; i < group.Items.Length; i++)
                                        {
                                            if (group.Items[i].IsActive && curFlag)
                                            {
                                                currentIndex = i;
                                                curFlag = false;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        messageAdapterName = group.Items[currentIndex].Name;
                    }

                }
            }
            return messageAdapterName;
        }
        #endregion

        #region Set current play list info:time slice group current play message adapter name
        /// <summary>
        /// Function:Set current play list info:time slice group current play message adapter name
        /// Author:Jerry Xu
        /// Date:2008-7-17
        /// </summary>
        /// <param name="playlist">PlaylistInfo:ref</param>
        /// <param name="flag">bool</param>
        public static void SetPlaylistTimeSlieceGroupCurrentMessageAdapterName(PlaylistInfo playlist, bool flag)
        {
            if (playlist == null || playlist.Items.Length == 0)
                return;
            int count = playlist.Items.Length;
            for (int i = 0; i < count; i++)
            {
                if (playlist.Items[i].Type == LibraryType.TimeSliceGroupProxy)
                {
                    ((TimeSliceGroupAdapterInfo)(playlist.Items[i])).CurrentMessageAdapterName = SetCurrentPlayMessageAdapterName((TimeSliceGroupAdapterInfo)(playlist.Items[i]), flag);
                }
            }
        }
        #endregion

        #region Sessions
        /// <summary>
        /// Function:Add SessionInfo.
        /// Author:Jerry
        /// Crate DateTime:2009-7-27
        /// </summary>
        /// <param name="session">SessionInfo</param>
        public static bool AddSession(SessionInfo session)
        {
            bool flag = false;
            if (session == null)
                return false;

            Provider.Get().SessionInfos.Add(session);



            if (session != null)
            {
                SessionInfo.Current = session;
                flag = true;
            }            

            if (flag)
                Update();

            return flag;
        }        
        #endregion
    }
}