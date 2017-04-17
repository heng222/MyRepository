//---------------------------------------------------------------------
//
// File: LibraryTreeControl.cs
//      
// Description:
//      Library tree control class
//
// Author: Kevin 2008-7-28
//
// Modify History:
//      Jerry Xu 2008-12-25 Import gif file:AddFiles
//      Jerry Xu 2008-12-25 Function:RenameLibraryItem
//      Jerry Xu 2008-12-29 Event:LibraryTreeControl_CustomNodeCellEdit
//      Jerry Xu 2008-12-31 Update functions:AddFiles(string[] files)
//      Jerry Xu 2009-1-4   Add method:FileIsValid,BatchLoadFilesResultInfo(List<string> listFilesFailure, List<string> listFilesSuccess)
//      Jerry Xu 2009-1-4   Update method:AddFiles(string[] files)
//      Jerry Xu 2009-1-10  Update method:RemoveLibraryItem()
//      Jerry Xu 2009-1-19  Update method:RenameLibraryItem()
//      Jerry Xu 2009-2-5   Update method:AddFiles(string[] files)
//      Jerry Xu 2009-2-19  Update method:private void RemoveLibraryItem()
//      Jerry Xu 2009-2-24  Update method:private bool Remove(LibraryNode node)
//      Jerry Xu 2009-2-25  Update event: OnMouseMove(MouseEventArgs e)
//                          Update method:RemoveLibraryItemNew(),RemoveNew(LibraryNode node)
//      Jerry Xu 2009-2-26  Update method:InitRootNodes()
//      Jerry Xu 2009-2-26  Update method:RemoveLibraryItemNew()
//      Jerry Xu 2009-2-26  Update method:RemoveLibraryItemNew,
//                          Update event :OnMouseMove(MouseEventArgs e)
//      Jerry Xu 2009-3-9   Update method:AddFiles(string[] files)
//      Jerry Xu 2009-3-12  Update method:AddFiles(string[] files)
//      Jerry Xu 2009-3-18  Update method:RemoveLibraryItemNew()
//      Jerry Xu 2009-3-18  Update method:Remove(LibraryNode node)
//      Jerry Xu 2009-3-18  Update method:BatchLoad()
//      Jerry Xu 2009-3-18  Update method:AddFiles(string[] files)
//      Jerry Xu 2009-3-23  Update method:AddFiles(string[] files),BatchLoadFileRename(List<LibraryFile> listFiles, List<MessageInfo> listMessages, List<int> listLengths, List<MessageReplaceItem> listReplaceMessages)
//      Jerry Xu 2009-3-25  Update method:RemoveLibraryItemNew(),OnOpenLibraryItem(LibraryItem item)
//      Jerry Xu 2009-3-25  Update method:InitMenu()
//      Jerry Xu 2009-3-25  Add new event:LibraryTreeControl_Observers(object sender, PWMessage<MenuCommands> msg),protected override void Dispose(bool disposing)
//      Jerry Xu 2009-4-23  Update method:LibraryTreeControl()
//      Jerry Xu 2009-4-29  Update method:OnOpenLibraryItem(LibraryItem item)
//      Jerry Xu 2009-6-16  Add method:OnLibraryDialogMouseDown(MouseEventArgs e),SetCheckedNode(LibraryNode node, object check)
//      Jerry Xu 2009-6-19  Insert method:LibraryTreeControl(bool isInsert)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraEditors;
using DevExpress.XtraEditors.Controls;
using DevExpress.XtraEditors.Repository;
using DevExpress.XtraTreeList;
using ProWrite.Entity.Library;
using ProWrite.Entity.Library.Controller;
using DevExpress.XtraTreeList.Nodes;
using DevExpress.Utils;
using ProWrite.Resources;
using System.Windows.Forms;
using System.Drawing;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using System.IO;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.Entity.Shape;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Settings;
using ProWrite.DES;
using ProWrite.Entity.Library.ImportExport;
using ProWrite.Entity;

namespace ProWrite.UI.Controls.Library
{
    /// <summary>
    /// Library tree control class
    /// </summary>
    [Serializable]
    public partial class LibraryTreeControl : TreeList//,ILibraryTreeController
    {
        [NonSerialized]
        private Dictionary<LibraryType, LibraryNode> _rootNodes;
        private Rectangle dragBoxFromMouseDown = Rectangle.Empty;

        public LibraryTreeControl()
        {
            if (!DesignMode)
            {
                InitComponent();
                OptionsSelection.EnableAppearanceFocusedCell = false;
                //OptionsSelection.EnableAppearanceFocusedRow = false;

                InitRootNodes();
                _currentGroup.PopulateController();
                Populate();
                this.OptionsView.ShowIndicator = false;
                LibraryGroup.Images.AddCompleted += new EventHandler<LibraryEventArgs>(OnLibrartyItemAddCompleted);
                LibraryGroup.Videos.AddCompleted += new EventHandler<LibraryEventArgs>(OnLibrartyItemAddCompleted);
                _currentGroup.Messages.AddCompleted += new EventHandler<LibraryEventArgs>(OnLibrartyItemAddCompleted);
                _currentGroup.TimeSliceGroups.AddCompleted += new EventHandler<LibraryEventArgs>(OnLibrartyItemAddCompleted);
                _currentGroup.Playlists.AddCompleted += new EventHandler<LibraryEventArgs>(OnLibrartyItemAddCompleted);
                _currentGroup.MLPlaylists.AddCompleted += OnLibrartyItemAddCompleted;

                CustomNodeCellEdit += new GetCustomNodeCellEditEventHandler(LibraryTreeControl_CustomNodeCellEdit);
                repositoryItemColorEdit.ColorChanged += new EventHandler(repositoryItemColorEdit_ColorChanged);
                repositoryItemCheckEdit.CheckedChanged += new EventHandler(repositoryItemCheckEdit_CheckedChanged);
                InitMenu();

                DragObjectStart += new DragObjectStartEventHandler(LibraryTreeControl_DragObjectStart);
            }
            RegisterHelp();
        }

        public LibraryTreeControl(bool isInsert)
        {
            if (!DesignMode)
            {
                InitComponent(isInsert);
                OptionsSelection.EnableAppearanceFocusedCell = false;
                //OptionsSelection.EnableAppearanceFocusedRow = false;

                InitRootNodes();
                _currentGroup.PopulateController();
                Populate();
                this.OptionsView.ShowIndicator = false;
                LibraryGroup.Images.AddCompleted += new EventHandler<LibraryEventArgs>(OnLibrartyItemAddCompleted);
                LibraryGroup.Videos.AddCompleted += new EventHandler<LibraryEventArgs>(OnLibrartyItemAddCompleted);
                _currentGroup.Messages.AddCompleted += new EventHandler<LibraryEventArgs>(OnLibrartyItemAddCompleted);
                _currentGroup.TimeSliceGroups.AddCompleted += new EventHandler<LibraryEventArgs>(OnLibrartyItemAddCompleted);
                _currentGroup.Playlists.AddCompleted += new EventHandler<LibraryEventArgs>(OnLibrartyItemAddCompleted);
                _currentGroup.MLPlaylists.AddCompleted += OnLibrartyItemAddCompleted;

                CustomNodeCellEdit += new GetCustomNodeCellEditEventHandler(LibraryTreeControl_CustomNodeCellEdit);
                repositoryItemColorEdit.ColorChanged += new EventHandler(repositoryItemColorEdit_ColorChanged);
                repositoryItemCheckEdit.CheckedChanged += new EventHandler(repositoryItemCheckEdit_CheckedChanged);
                InitMenu();

                DragObjectStart += new DragObjectStartEventHandler(LibraryTreeControl_DragObjectStart);
            }
            RegisterHelp();
        }

        void repositoryItemCheckEdit_CheckedChanged(object sender, EventArgs e)
        {
            CheckEdit checkEdit = sender as CheckEdit;
            if (checkEdit != null)
            {
                switch (checkEdit.Properties.CheckStyle)
                {
                    case CheckStyles.Standard:
                        //checkEdit.Checked = !checkEdit.Checked;
                        break;
                    case CheckStyles.Radio:
                        SetNodeUnChecked(_rootNodes[LibraryType.Message]);
                        SetNodeUnChecked(_rootNodes[LibraryType.TimeSliceGroup]);
                        SetNodeUnChecked(_rootNodes[LibraryType.Playlist]);
                        SetNodeUnChecked(_rootNodes[LibraryType.Schedule]);
                        break;
                }
                //if (checkEdit.Checked)
                //{
                //    if (FocusedNode.Library == null)
                //    {
                //        checkEdit.Checked = false;
                //    }
                //    else
                //    {
                //        SetNodeUnChecked(_rootNodes[LibraryType.Message]);
                //        SetNodeUnChecked(_rootNodes[LibraryType.TimeSliceGroup]);
                //        SetNodeUnChecked(_rootNodes[LibraryType.Playlist]);
                //        SetNodeUnChecked(_rootNodes[LibraryType.Scheduler]);
                //    }
                //}
            }
        }

        private void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resource.Helps.EditorLibrary);
        }

        public void SetCurrentGroupEvent()
        {
            _currentGroup.Messages.AddCompleted += new EventHandler<LibraryEventArgs>(OnLibrartyItemAddCompleted);
            _currentGroup.TimeSliceGroups.AddCompleted += new EventHandler<LibraryEventArgs>(OnLibrartyItemAddCompleted);
            _currentGroup.MLPlaylists.AddCompleted += OnLibrartyItemAddCompleted;
        }

        void LibraryTreeControl_DragObjectStart(object sender, DragObjectStartEventArgs e)
        {
            e.Allow = false;

        }

        #region Menu event
        //[NonSerialized]
        //private EventHandler<PWMessage<MenuCommands>> _batchLoadEvent;
        //public event EventHandler<PWMessage<MenuCommands>> BatchLoadEvent
        //{
        //    add { _batchLoadEvent += value; }
        //    remove { _batchLoadEvent -= value; }
        //}

        /// <summary>
        /// init menu event
        /// </summary>
        private void InitMenu()
        {

            LocalMessageBus.Subject<PWMessage<MenuCommands>>().Observers += new System.Communication.Messaging.ObserverHandler<PWMessage<MenuCommands>>(LibraryTreeControl_Observers);
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            LocalMessageBus.Subject<PWMessage<MenuCommands>>().Observers -= new System.Communication.Messaging.ObserverHandler<PWMessage<MenuCommands>>(LibraryTreeControl_Observers);
        }

        void LibraryTreeControl_Observers(object sender, PWMessage<MenuCommands> msg)
        {


            switch (msg.Content)
            {
                case MenuCommands.BatchLoad:
                    BatchLoad();
                    break;
            }

            //_batchLoadEvent(this, new RemoveLibraryEventArgs(msg));
        }


        #region Batch Load file
        private void BatchLoad()
        {
            string[] files = null;
            using (OpenFileDialog dlg = new OpenFileDialog())
            {
                dlg.Filter = Constance.FileFilter.BatchLoad;
                dlg.Title = "Batch Load Files";
                dlg.Multiselect = true;
                dlg.InitialDirectory = Directory.GetCurrentDirectory();
                DialogResult result = dlg.ShowModalDialog();
                if (result == DialogResult.OK || result == DialogResult.Yes)
                    files = dlg.FileNames;
                else
                    return;
            }

            AddFiles(files);
            LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                new MenuCommand(MenuCommands.InsertMessage, LibraryGroup.Current.Messages.Count > 0),
                new MenuCommand(MenuCommands.InsertTimeSlice, LibraryGroup.Current.TimeSliceGroups.Count > 0),
                new MenuCommand(MenuCommands.InsertPlaylist, LibraryGroup.Current.Playlists.Count > 0),
            }));
        }

        /// <summary>
        /// Function: File is valid.
        /// Author  : Jerry Xu
        /// Date    : 2009-1-4
        /// </summary>
        /// <param name="path">file path</param>
        /// <returns>bool</returns>
        private bool FileIsValid(string path)
        {
            switch (Path.GetExtension(path).ToLower())
            {
                case Constance.FileExtensionName.AVI:
                case Constance.FileExtensionName.Mpeg_2:
                case Constance.FileExtensionName.Wmv:
                    return Common.CommonHelper.IsVideoFile(path);
                case Constance.FileExtensionName.Bmp:
                case Constance.FileExtensionName.Jpeg:
                case Constance.FileExtensionName.Jpg:
                case Constance.FileExtensionName.Gif:
                case Constance.FileExtensionName.Png:
                    return IOHelper.IsImageFile(path);
            }
            return true;
        }

        private void AddFiles(string[] files)
        {
            if (files != null && files.Length > 0)
            {
                List<string> listFilesFailure = new List<string>();
                List<string> listFilesSuccess = new List<string>();
                List<string> listNoFiles = new List<string>();
                List<LibraryFile> listFiles = new List<LibraryFile>();
                List<int> listLengths = new List<int>();
                List<MessageInfo> listMessages = new List<MessageInfo>();
                List<MessageInfo> listNoMessasges = new List<MessageInfo>();
                List<MessageReplaceItem> listReplaceMessages = new List<MessageReplaceItem>();
                LibraryFile libraryFile = null;
                MessageInfo message = null;
                MessageReplaceItem replaceMessage = null;

                int length = 0;
                IBatchLoadGenerator generator = new NailImageGenerator();
                LibraryGroup.Current.Messages.Generateor = generator;
                int fileIndex = 0;
                int messageIndex = 0;
                foreach (string file in files)
                {
                    string fileType = Path.GetExtension(file);
                    if (string.IsNullOrEmpty(fileType))
                        continue;

                    if (!FileIsValid(file))
                    {
                        listFilesFailure.Add(file);
                        continue;
                    }

                    listFilesSuccess.Add(file);
                    fileType = fileType.ToLower();

                    LibraryType libraryType = IOHelper.GetLibraryType(fileType);
                    FileExistType type = IOHelper.IsExist(file, "", libraryType);

                    length = ControlService.SignCombo.Current.Template.Message.DisplayTime;
                    if (libraryType == LibraryType.Video)
                        length = int.Parse((CommonHelper.GetMediaLength(file) / DESConsts.UNITS).ToString());
                    if (libraryType == LibraryType.Image && Path.GetExtension(file).ToLower() == ".gif")
                    {
                        double length1 = double.Parse((CommonHelper.GetMediaLength(file) * 1.0 / DESConsts.UNITS).ToString());
                        if (length1 > 0)
                            length = -1;
                        else
                            length = ControlService.SignCombo.Current.Template.Message.DisplayTime;
                    }
                    //add file
                    if (type == FileExistType.No)
                    {
                        string libraryFileName = IOHelper.GetLibraryFileName(file, string.Empty, libraryType);

                        listNoFiles.Add(file);
                        message = LibraryGroup.Current.AddFile(file, libraryFileName, fileType, length, ControlService.SignCombo.Current);

                        if (message != null)
                        {
                            MessageInfo mes = message.Copy() as MessageInfo;
                            listMessages.Add(mes);
                            replaceMessage = new MessageReplaceItem();
                            replaceMessage.Message = mes;
                            replaceMessage.IsReplace = false;
                            replaceMessage.FileIndex = -1;
                            replaceMessage.MessageIndex = messageIndex++;
                            listReplaceMessages.Add(replaceMessage);
                        }
                        //else
                        //{
                        //    message = LibraryGroup.Current.Messages.GetByName(Path.GetFileNameWithoutExtension(libraryFileName));

                        //    MessageInfo tempMessage = (message as MemoryLibraryItem).Copy() as MessageInfo;
                        //    message.ImagePath = tempMessage.ImagePath;
                        //    LibraryGroup.Current.Messages.Update(message);
                        //    message = null;
                        //}

                    }
                    else if (type == FileExistType.Yes)
                    {
                        //rename file
                        libraryFile = new LibraryFile();
                        libraryFile.Type = libraryType;
                        libraryFile.FileName = file;
                        libraryFile.IsValid = false;
                        listFiles.Add(libraryFile);


                        listLengths.Add(length);

                        message = LibraryGroup.Current.Messages.GetByName(Path.GetFileNameWithoutExtension(file));

                        MessageInfo mes = null;
                        replaceMessage = new MessageReplaceItem();
                        replaceMessage.Message = mes;
                        replaceMessage.IsReplace = true;
                        replaceMessage.FileIndex = fileIndex++;

                        if (message != null)
                        {
                            mes = message.Copy() as MessageInfo;
                            listMessages.Add(mes);
                            replaceMessage.Message = mes;
                            replaceMessage.MessageIndex = messageIndex++;
                        }


                        listReplaceMessages.Add(replaceMessage);

                        //    message.Size = new Size(ControlService.SignCombo.Current.Width, ControlService.SignCombo.Current.Height);
                        //    //MessageInfo tempMessage = (message as MemoryLibraryItem).Copy() as MessageInfo;
                        //    //message.ImagePath = tempMessage.ImagePath;
                        //    LibraryGroup.Current.Messages.Add(message);
                        //}
                    }
                }


                //Batch load file :rename file and message
                if (BatchLoadFileRename(listFiles, listMessages, listLengths, listReplaceMessages))
                {
                    //Batch load files result info
                    BatchLoadFilesResultInfo(listFilesFailure, listFilesSuccess);
                }
                else
                {
                    foreach (LibraryFile file in listFiles)
                    {
                        listFilesFailure.Add(file.FileName);
                    }
                    BatchLoadFilesResultInfo(listFilesFailure, listNoFiles);
                }

            }
            LibraryGroup.Current.Messages.Generateor = null;
        }

        private void AddFiles1(string[] files)
        {
            if (files != null && files.Length > 0)
            {
                List<string> listFilesFailure = new List<string>();
                List<string> listFilesSuccess = new List<string>();
                List<string> listNoFiles = new List<string>();
                List<LibraryFile> listFiles = new List<LibraryFile>();
                List<int> listLengths = new List<int>();
                List<MessageInfo> listMessages = new List<MessageInfo>();
                List<MessageInfo> listNoMessasges = new List<MessageInfo>();
                LibraryFile libraryFile = null;
                MessageInfo message = null;
                int length = 0;
                foreach (string file in files)
                {
                    string fileType = Path.GetExtension(file);
                    if (string.IsNullOrEmpty(fileType))
                        continue;

                    if (!FileIsValid(file))
                    {
                        listFilesFailure.Add(file);
                        continue;
                    }

                    listFilesSuccess.Add(file);
                    fileType = fileType.ToLower();

                    LibraryType libraryType = IOHelper.GetLibraryType(fileType);
                    FileExistType type = IOHelper.IsExist(file, "", libraryType);

                    length = ControlService.SignCombo.Current.Template.Message.DisplayTime;
                    if (libraryType == LibraryType.Video)
                        length = int.Parse((CommonHelper.GetMediaLength(file) / DESConsts.UNITS).ToString());
                    if (libraryType == LibraryType.Image && Path.GetExtension(file).ToLower() == ".gif")
                    {
                        length = int.Parse((CommonHelper.GetMediaLength(file) / DESConsts.UNITS).ToString());
                        if (length > 0)
                            length = -1;
                        else
                            length = ControlService.SignCombo.Current.Template.Message.DisplayTime;
                    }
                    //add file
                    if (type == FileExistType.No)
                    {
                        string libraryFileName = IOHelper.GetLibraryFileName(file, string.Empty, libraryType);

                        message = LibraryGroup.Current.AddFile(file, libraryFileName, fileType, length, ControlService.SignCombo.Current);

                        if (message != null)
                            listMessages.Add(message.Copy() as MessageInfo);
                    }
                    else if (type == FileExistType.Yes)
                    {
                        //rename file
                        libraryFile = new LibraryFile();
                        libraryFile.Type = libraryType;
                        libraryFile.FileName = file;
                        libraryFile.IsValid = false;
                        listFiles.Add(libraryFile);

                        listLengths.Add(length);

                        message = LibraryGroup.Current.Messages.GetByName(Path.GetFileNameWithoutExtension(file));

                        if (message != null)
                            listMessages.Add(message.Copy() as MessageInfo);
                        else
                        {
                            listNoMessasges.Add(message);
                            LibraryGroup.Current.Messages.Add(message);
                        }
                    }
                }
                //Batch load file :rename file and message
                //BatchLoadFileRename(listFiles, listMessages, listLengths, listNoMessasges);
                //Batch load files result info
                BatchLoadFilesResultInfo(listFilesFailure, listFilesSuccess);

            }
        }

        /// <summary>
        /// Function: Batch load files result info
        /// Author  : Jerry Xu
        /// Date    : 2009-1-4        
        /// </summary>
        /// <param name="listFilesFailure">List<string>:Failure files list</param>
        /// <param name="listFilesSuccess">List<string>:Success files list</param>
        private static void BatchLoadFilesResultInfo(List<string> listFilesFailure, List<string> listFilesSuccess)
        {
            //Batch load files Info
            string strFile;
            if (listFilesSuccess.Count > 0 || listFilesFailure.Count > 0)
            {

                strFile = Resource.GetString(Resource.Strings.BatchLoadResultInfoStart) + "\n";
                if (listFilesSuccess.Count > 0)
                {
                    for (int i = 0; i < listFilesSuccess.Count; i++)
                    {
                        if (i == listFilesSuccess.Count - 1)
                            strFile += String.Format("'{0}'\n", listFilesSuccess[i]);
                        else
                            strFile += String.Format("'{0}',\n", listFilesSuccess[i]);
                    }

                    strFile += Resource.GetString(Resource.Strings.BatchLoadResultInfoSuccess);
                }
                if (listFilesFailure.Count > 0)
                {
                    if (listFilesSuccess.Count > 0)
                        strFile += "\n";
                    for (int i = 0; i < listFilesFailure.Count; i++)
                    {
                        if (i == listFilesFailure.Count - 1)
                            strFile += String.Format("'{0}'\n", listFilesFailure[i]);
                        else
                            strFile += String.Format("'{0}',\n", listFilesFailure[i]);
                    }
                    strFile += Resource.GetString(Resource.Strings.BatchLoadResultInfoFailure);

                }
                MsgBox.Information(strFile, Resource.GetString(Resource.Strings.BatchLoadResultInfoTitle));
            }
        }

        /// <summary>
        /// Function: Update file handle of import message files
        /// Author  : Jerry Xu
        /// Date    : 2008-12-29
        /// </summary>
        /// <param name="message">MessageInfo</param>
        /// <param name="files">List<FileItem></param>
        private void UpdateFiles(MessageInfo message, List<LibraryFile> files)
        {
            if (message == null || message.Items == null || message.Items.Length == 0 || files == null || files.Count == 0)
                return;

            //string filepath = null;
            //foreach (LibraryFile file in files)
            //{
            //    filepath = IOHelper.GetLibraryFileName(file.Name, string.Empty, file.Type);
            //    file.LibraryFileName = filepath;
            //}
            foreach (ShapeLayer layer in message.Items)
            {
                if (layer.Shape != null && (((layer.Shape.Type == ShapeType.Image) && !string.IsNullOrEmpty((layer.Shape as ShapeImage).ImageUrl)) || ((layer.Shape.Type == ShapeType.Video) && !string.IsNullOrEmpty((layer.Shape as ShapeVideo).VideoUrl))))
                    SetHandleID(layer.Shape, files);
            }
        }

        /// <summary>
        /// Function: Update shape file handle 
        /// Author  : Jerry Xu
        /// Date    : 2008-12-29
        /// </summary>
        /// <param name="shape">ShapeBase</param>
        /// <param name="files">List<FileItem></param>
        private void SetHandleID(ShapeBase shape, List<LibraryFile> files)
        {
            ShapeImage image = null;
            ShapeVideo video = null;
            //string libraryFileName = null;
            if (shape.Type == ShapeType.Image)
                image = shape as ShapeImage;
            if (shape.Type == ShapeType.Video)
                video = shape as ShapeVideo;
            foreach (LibraryFile item in files)
            {
                if (!string.IsNullOrEmpty(item.Id))
                    item.Id = Guid.NewGuid().ToString().Replace("-", "");
                //libraryFileName = IOHelper.GetLibraryFileName(item.FileName, item.LibraryFileName string.Empty, LibraryType.Image);
                if (!string.IsNullOrEmpty(item.FileName))
                {
                    if (shape.Type == ShapeType.Image)
                    {
                        if (Path.GetFileName(item.FileName) == Path.GetFileName(image.ImageUrl))
                        {
                            image.FileHandle = item.Id;
                            //libraryFileName = IOHelper.GetLibraryFileName(item.Name, string.Empty, LibraryType.Image);
                            image.ImageUrl = item.LibraryFileName; //libraryFileName;
                        }
                    }
                    if (shape.Type == ShapeType.Video)
                    {
                        if (Path.GetFileName(item.FileName) == Path.GetFileName(video.VideoUrl))
                        {
                            video.FileHandle = item.Id;
                            //libraryFileName = IOHelper.GetLibraryFileName(item.Name, string.Empty, LibraryType.Video);
                            video.VideoUrl = item.LibraryFileName;// libraryFileName;
                        }
                    }
                }
            }

        }

        private void SetMessageInfoFiles(List<LibraryFile> listFiles, List<MessageInfo> listMessages, List<MessageInfo> listNoMessages)
        {
            foreach (MessageInfo message in listMessages)
            {
                UpdateFiles(message, listFiles);
            }
            foreach (MessageInfo message in listNoMessages)
            {
                UpdateFiles(message, listFiles);
            }
        }

        private bool BatchLoadFileRename(List<LibraryFile> listFiles, List<MessageInfo> listMessages, List<int> listLengths, List<MessageReplaceItem> listReplaceMessages)
        {
            if (listFiles.Count > 0 || listMessages.Count > 0)
            {
                FilesRenameForm frm = new FilesRenameForm(listFiles, listMessages);
                frm.ShowModalDialog();
                if (frm.IsRefresh)
                {
                    //TODO:  

                    LibraryGroup.Current.BatchLoadFile(frm.Files, frm.Messages, listReplaceMessages, listLengths, ControlService.SignCombo.Current);
                    return true;
                }
                return false;
            }
            return true;
        }

        private void BatchLoadFileRename(List<LibraryFile> listFiles, List<MessageInfo> listMessages)
        {
            if (listFiles.Count > 0 || listMessages.Count > 0)
            {
                FilesRenameForm frm = new FilesRenameForm(listFiles, listMessages);
                frm.ShowModalDialog();
                if (frm.IsRefresh)
                {
                    LibraryGroup.Current.BatchLoadFile(frm.Files, frm.Messages, ControlService.SignCombo.Current);
                }
            }
        }

        #endregion
        #endregion

        [NonSerialized]
        private EventHandler<LibraryColorChangedEventArgs> _libraryColorChanged;
        public event EventHandler<LibraryColorChangedEventArgs> LibraryColorChanged
        {
            add { _libraryColorChanged += value; }
            remove { _libraryColorChanged -= value; }
        }



        private void OnLibraryColorChanged(string libraryName, int colorId, LibraryType type)
        {
            if (_libraryColorChanged != null)
                _libraryColorChanged(this, new LibraryColorChangedEventArgs(libraryName, colorId, type));
        }
        void repositoryItemColorEdit_ColorChanged(object sender, EventArgs e)
        {
            MemoryLibraryItem item = FocusedNode.Tag as MemoryLibraryItem;
            ColorEdit colorEdit = sender as ColorEdit;
            if (item != null && colorEdit != null)
            {
                //update items' color
                item.Color = colorEdit.Color;
                //foreach appointment in sessionInfo will change color
                int colorIndex = DataGate.FindColorIndex(colorEdit.Color);
                OnLibraryColorChanged(item.Name, colorIndex, item.Type);
            }
        }

        void LibraryTreeControl_CustomNodeCellEdit(object sender, GetCustomNodeCellEditEventArgs e)
        {
            //if(!colorColumn.Visible || e.Column.FieldName != "Color")
            //    return;
            LibraryItem item = e.Node.Tag as LibraryItem;

            if (item != null
                && (item.Type == LibraryType.Message
                    || item.Type == LibraryType.Playlist
                    || item.Type == LibraryType.TimeSliceGroup
                    || item.Type == LibraryType.Schedule))
            {
                if (e.Column.FieldName == "Color")
                {
                    e.RepositoryItem = repositoryItemColorEdit;
                }
                else if (e.Column.FieldName == "Checked")
                {
                    e.RepositoryItem = repositoryItemCheckEdit;
                }

            }
        }

        void OnLibrartyItemAddCompleted(object sender, LibraryEventArgs e)
        {
            InternalAdd(e.Item);
            UpdateDatabase();
            ExpandAll();
        }

        public Color GetLibraryItemColorByName(string libraryItemName)
        {
            LibraryNode node = FindNodeByFieldValue("Name", libraryItemName) as LibraryNode;
            if (node != null)
            {
                MemoryLibraryItem item = node.Tag as MemoryLibraryItem;
                if (item != null)
                    return item.Color;
            }
            return Color.Empty;
        }

        public void SetColor(MemoryLibraryItem memoryItem, Color color)
        {
            LibraryNode node = null;
            //LibraryNode rootnode = GetNode(memoryItem);
            //_rootNodes = new Dictionary<LibraryType, LibraryNode>();
            foreach (LibraryNode libraryNode in _rootNodes[memoryItem.Type].Nodes)
            {
                if (libraryNode[0].ToString() == memoryItem.Name)
                    node = libraryNode;
            }
            if (node != null)
            {
                MemoryLibraryItem item = node.Tag as MemoryLibraryItem;
                if (item != null)
                {
                    node[3] = color;
                    item.Color = color;
                }
            }
        }

        /// <summary>
        /// get or set library type
        /// </summary>
        public LibraryType Type
        {
            get { return _currentGroup.TypeFilter; }
            set
            {
                if (!DesignMode)
                {
                    _currentGroup.TypeFilter = value;

                    if (_currentGroup.TypeFilter == LibraryGroup.SchedulerFilter)
                        colorColumn.Visible = true;
                    else
                        colorColumn.Visible = false;

                    foreach (LibraryNode item in _rootNodes.Values)
                    {
                        if ((value & item.LibraryType) == item.LibraryType)
                            item.Visible = true;
                        else
                            item.Visible = false;
                    }
                }
            }
        }

        /// <summary>
        /// get current library group
        /// </summary>
        private LibraryGroup _currentGroup
        {
            get { return LibraryGroup.Current; }
        }

        /// <summary>
        /// get or set focused node
        /// </summary>
        public new LibraryNode FocusedNode
        {
            get { return base.FocusedNode as LibraryNode; }
            set { base.FocusedNode = value; }
        }

        /// <summary>
        /// init root nodes
        /// </summary>
        private void InitRootNodes()
        {
            _rootNodes = new Dictionary<LibraryType, LibraryNode>();

            LibraryNode node = null;
            NodeType[] rootType = new NodeType[] {
                NodeType.Images
                ,NodeType.Videos
                ,NodeType.Messages
                ,NodeType.TimeSliceGroups
                ,NodeType.Playlists
                //,NodeType.MLPlaylist
                ,NodeType.Schedulers
            };

            foreach (NodeType item in rootType)
            {
                if (MapTable.GetLibraryType(item) != null &&
                     MapTable.GetLibraryType(item).ToString() == "Image")
                    node = AppendNode(
                        new object[] { "Picture", null, null, null, null }, null) as LibraryNode;
                else
                    node = AppendNode(
                            new object[] { MapTable.GetLibraryType(item).ToString(), null, null, null, null }, null) as LibraryNode;
                node.NodeType = item;
                node.LibraryType = MapTable.GetLibraryType(item);
                node.ImageIndex = MapTable.GetImageIndex(node.LibraryType);
                node.SelectImageIndex = node.ImageIndex;
                node.StateImageIndex = node.ImageIndex;
                _rootNodes[node.LibraryType] = node;
            }
        }

        /// <summary>
        /// clear all child nodes in root nodes
        /// </summary>
        private void ClearChildNodes()
        {
            foreach (LibraryNode item in _rootNodes.Values)
                item.Nodes.Clear();
        }

        /// <summary>
        /// load tree nodes
        /// </summary>
        public void Populate()
        {
            ClearChildNodes();
            foreach (LibraryItem item in _currentGroup)
            {
                InternalAdd(item);
                SetFocusedNode(GetNode(item));
            }
            ExpandAll();
        }

        /// <summary>
        /// add library node
        /// </summary>
        /// <param name="item"></param>
        private void InternalAdd(LibraryItem item)
        {
            if (item != null && item.Type != LibraryType.None)
            {
                if (GetNode(item) != null)
                    return;
                try
                {
                    LibraryNode node = AppendNode(item.ToArray(), _rootNodes[item.Type], item) as LibraryNode;
                    node.NodeType = MapTable.GetNodeType(item.Type);
                    node.LibraryType = item.Type;
                    node.ImageIndex = MapTable.GetImageIndex(item.Type);
                    node.SelectImageIndex = node.ImageIndex;
                    node.StateImageIndex = node.ImageIndex;
                }
                catch { }
            }
        }

        /// <summary>
        /// add library and library node
        /// </summary>
        /// <param name="item"></param>
        public bool Add(LibraryItem item)
        {
            if (item == null || _currentGroup.Contains(item))
                return false;

            bool flag = _currentGroup.Add(item);

            if (flag)
            {
                UpdateDatabase();
                InternalAdd(item);
                ExpandAll();
            }

            return flag;
        }

        private void UpdateDatabase()
        {
            DataGate.Update();
        }

        /// <summary>
        /// is contains library item
        /// </summary>
        /// <param name="item"></param>
        /// <returns></returns>
        public bool Contains(LibraryItem item)
        {
            return _currentGroup.Contains(item);
        }

        /// <summary>
        /// remove active library item
        /// </summary>
        private void RemoveLibraryItem()
        {
            if (FocusedNode != null
                && FocusedNode.Library != null)
            {
                if (MsgBox.Confirm(Resource.GetFormatString(Resources.Resource.Strings.LibraryTreeControlDeleteConfirmDeleteItem, FocusedNode.Library.Type.ToString().ToLower(), FocusedNode.Library.Name)) == DialogResult.Yes)
                {
                    if (!Remove(FocusedNode))
                    {
                        MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryTreeDeleteFailed, new object[] { (FocusedNode.Tag as LibraryItem).Type.ToString().ToLower(), (FocusedNode.Tag as LibraryItem).Name }));
                    }
                }
            }
        }

        /// <summary>
        /// remove active library item
        /// </summary>
        private void RemoveLibraryItemNew()
        {
            MemoryLibraryItem memory = FocusedNode.Library as MemoryLibraryItem;
            if (memory != null && memory.IsOpen)
            {
                MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryTreeDeleteFailedIsOpen, new object[] { memory.Type.ToString().ToLower(), memory.Name }));
                return;
            }

            if (FocusedNode != null
                && FocusedNode.Library != null)
            {
                string libraryType = FocusedNode.Library.Type.ToString().ToLower();
                string libraryName = FocusedNode.Library.Name;
                if (MsgBox.Confirm(Resource.GetFormatString(Resources.Resource.Strings.LibraryTreeControlDeleteConfirmDeleteItem, FocusedNode.Library.Type.ToString().ToLower(), FocusedNode.Library.Name)) == DialogResult.Yes)
                {
                    LibraryDeleteItem deleteItem = new LibraryDeleteItem();

                    deleteItem = RemoveNew(FocusedNode);

                    if (string.IsNullOrEmpty(deleteItem.GroupName))
                        deleteItem.GroupName = LibraryGroup.Current.Name;
                    if (deleteItem.State == LibraryState.Referrence)
                    {
                        if (deleteItem.GroupName != _currentGroup.Name)
                            MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryTreeDeleteFailed, new object[] { (FocusedNode.Tag as LibraryItem).Type.ToString().ToLower(), (FocusedNode.Tag as LibraryItem).Name, deleteItem.ReferrenceItem.Type.ToString().ToLower(), deleteItem.ReferrenceItem.Name, " of " + deleteItem.GroupName + " " }));
                        else
                            MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryTreeDeleteFailed, new object[] { (FocusedNode.Tag as LibraryItem).Type.ToString().ToLower(), (FocusedNode.Tag as LibraryItem).Name, deleteItem.ReferrenceItem.Type.ToString().ToLower(), deleteItem.ReferrenceItem.Name, "" }));
                    }
                    else if (deleteItem.State == LibraryState.Lock)
                    {
                        if (FocusedNode.Library.Type == LibraryType.Video || FocusedNode.Library.Type == LibraryType.Image)
                            MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryTreeDeleteFailedFileIsLock, new object[] { (FocusedNode.Tag as LibraryItem).Type.ToString().ToLower(), (FocusedNode.Tag as LibraryItem).Name }));
                        else
                            MsgBox.Error(Resource.GetFormatString(Resource.Strings.LibraryTreeDeleteFailedIsLock, new object[] { (FocusedNode.Tag as LibraryItem).Type.ToString().ToLower(), (FocusedNode.Tag as LibraryItem).Name }));
                    }
                    else
                    {
                        MsgBox.Information(Resource.GetFormatString(Resource.Strings.LibraryTreeDeleteSuccess, new object[] { libraryType, libraryName }));

                        if (!string.IsNullOrEmpty(ModuleManager.CurrentModuleName))
                        {

                            bool canOpen = CommonHelper.IsShowOpenDialog(ModuleManager.CurrentModuleName);
                            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                                 new MenuCommand{ Command =  MenuCommands.Open,Enabled = canOpen}
                ,new MenuCommand { Command = MenuCommands.InsertMessage,  Enabled = LibraryGroup.Current.Messages.Count > 0}
                            ,new MenuCommand { Command = MenuCommands.InsertTimeSlice,  Enabled = LibraryGroup.Current.TimeSliceGroups.Count > 0}
                            ,new MenuCommand { Command = MenuCommands.InsertPlaylist,  Enabled = LibraryGroup.Current.Playlists.Count > 0}
                            }));
                            //return true;
                        }

                        //LocalMessageBus.Send(this, new MenuMessage(MenuCommands.InsertMessage, LibraryGroup.Current.Messages.Count > 0));
                        //LocalMessageBus.Send(this, new MenuMessage(MenuCommands.InsertTimeSlice, LibraryGroup.Current.TimeSliceGroups.Count > 0));
                        //LocalMessageBus.Send(this, new MenuMessage(MenuCommands.InsertPlaylist, LibraryGroup.Current.Playlists.Count > 0));
                    }
                }
            }
        }

        /// <summary>
        /// rename active library item
        /// </summary>
        private bool RenameLibraryItem()
        {
            if (FocusedNode == null || FocusedNode.Library == null)
                return false;

            LibraryItem item = FocusedNode.Library;

            string libraryName = null;
            if ((item as FileLibraryItem) != null)
                libraryName = InputDialog.GetInputValue(Resource.GetFormatString(Resource.Strings.NewLibraryName, new object[] { FocusedNode.Library.Type.ToString() }), Path.GetFileNameWithoutExtension(item.Name));
            else
                libraryName = InputDialog.GetInputValue(Resource.GetFormatString(Resource.Strings.NewLibraryName, new object[] { FocusedNode.Library.Type.ToString() }), item.Name);

            if (InputDialog.Result == DialogResult.Cancel)
                return false;
            if (string.IsNullOrEmpty(libraryName))
            {
                MsgBox.Warning(Resource.GetString(Resource.Strings.NameEmpty));
                return false;
            }


            FileLibraryItem fileLib = item as FileLibraryItem;
            if (fileLib != null)
            {

                string fileSuffix = Path.GetExtension(fileLib.Path);
                if (!string.IsNullOrEmpty(fileSuffix)
                    && !libraryName.Contains(fileSuffix))
                    libraryName = libraryName + fileSuffix;
            }

            if (LibraryGroup.Current.Contains(libraryName, item.Type))
            {
                MsgBox.Error(Resource.GetFormatString(Resource.Strings.NameAlreadyExist,item.Type.ToString().ToLower(),libraryName));
                return false;
            }

            string oldName = item.Name;
            if (LibraryGroup.Current.Rename(libraryName, item.Name, item.Type))
            {
                FocusedNode.SetValue(this.nameColumn.FieldName, libraryName);
                LocalMessageBus.Send(this, new LibraryRenameMessage(libraryName, oldName, item.Type));
                Refresh();
                //if (fileLib == null)
                UpdateDatabase();
                return true;
            }

            return false;
        }

        /// <summary>
        /// update library item
        /// </summary>
        /// <param name="item"></param>
        public bool Update(LibraryItem item)
        {
            if (item == null)
                return false;

            //MemoryLibraryItem
            bool flag = _currentGroup.Update(item);
            if (flag)
            {
                UpdateDatabase();
                Populate();
            }
            return flag;
        }

        /// <summary>
        /// get library node by library item
        /// </summary>
        /// <param name="item"></param>
        /// <returns></returns>
        public LibraryNode GetNode(LibraryItem item)
        {
            if (item == null)
                return null;
            if (!_rootNodes.ContainsKey(item.Type))
                return null;

            return _rootNodes[item.Type].GetSubNode(item);
        }

        /// <summary>
        /// remove library item and library node
        /// </summary>
        /// <param name="item"></param>
        /// <returns></returns>
        public bool Remove(LibraryItem item)
        {
            return Remove(GetNode(item));
        }

        /// <summary>
        /// remove library item and library node
        /// </summary>
        /// <param name="node"></param>
        /// <returns></returns>
        private bool Remove(LibraryNode node)
        {
            if (node == null || node.Library == null)
                return false;

            LibraryItem item = node.Library;
            ILockLibraryItem locker = item as ILockLibraryItem;
            if (locker != null && locker.IsLock)
            {
                return false;
            }
            bool isCanDeleted = false;
            if (item.Type == LibraryType.Image || item.Type == LibraryType.Video)
                isCanDeleted = DataGate.Project.LibraryGroups.CanDeleteFileLibrary(node.Library as FileLibraryItem);
            else
                isCanDeleted = _currentGroup.CanDeleteLibrary(item);
            if (isCanDeleted)
            {

                if (_currentGroup.Remove(item))
                {
                    UpdateDatabase();
                    Nodes.Remove(node);
                    ExpandAll();
                    if (item.Type == LibraryType.TimeSliceGroup)
                        OnRemoveLibraryItem(item.Type);

                    if (!string.IsNullOrEmpty(ModuleManager.CurrentModuleName))
                    {

                        bool canOpen = CommonHelper.IsShowOpenDialog(ModuleManager.CurrentModuleName);
                        LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                                 new MenuCommand{ Command =  MenuCommands.Open,Enabled = canOpen}
                ,new MenuCommand { Command = MenuCommands.InsertMessage,  Enabled = LibraryGroup.Current.Messages.Count > 0}
                            ,new MenuCommand { Command = MenuCommands.InsertTimeSlice,  Enabled = LibraryGroup.Current.TimeSliceGroups.Count > 0}
                            ,new MenuCommand { Command = MenuCommands.InsertPlaylist,  Enabled = LibraryGroup.Current.Playlists.Count > 0}
                            }));
                        return true;
                    }
                }
            }

            return false;
        }

        /// <summary>
        /// remove library item and library node
        /// </summary>
        /// <param name="node"></param>
        /// <returns></returns>
        private LibraryDeleteItem RemoveNew(LibraryNode node)
        {
            LibraryDeleteItem deleteItem = new LibraryDeleteItem();

            if (node == null || node.Library == null)
                return deleteItem;

            LibraryItem item = node.Library;
            ILockLibraryItem locker = item as ILockLibraryItem;
            if (locker != null && locker.IsLock)
            {
                deleteItem.State = LibraryState.Lock;
                return deleteItem;
            }

            if (item.Type == LibraryType.Image || item.Type == LibraryType.Video)
                deleteItem = DataGate.Project.LibraryGroups.CanDeleteFileLibraryNew(node.Library as FileLibraryItem);
            else
                deleteItem = _currentGroup.CanDeleteLibraryNew(item);
            if (deleteItem.State == LibraryState.None)
            {
                if (_currentGroup.Remove(item))
                {
                    UpdateDatabase();
                    Nodes.Remove(node);
                    ExpandAll();
                    if (item.Type == LibraryType.TimeSliceGroup)
                        OnRemoveLibraryItem(item.Type);
                    return deleteItem;
                }
            }

            return deleteItem;
        }

        [NonSerialized]
        private EventHandler<OpenLibraryEventArgs> _openLibraryItem;
        public event EventHandler<OpenLibraryEventArgs> OpenLibraryItem
        {
            add { _openLibraryItem += value; }
            remove { _openLibraryItem -= value; }
        }

        public void OnOpenLibraryItem(LibraryItem item)
        {
            if (item == null)
                return;

            if (_openLibraryItem != null)
            {
                ILockLibraryItem locker = item as ILockLibraryItem;
                MemoryLibraryItem memory = item as MemoryLibraryItem;
                if (memory != null)
                {
                    if (memory.Type == LibraryType.TimeSliceGroup)
                        return;
                    if (memory.IsOpen)
                    {
                        if (memory.Type == LibraryType.Message)
                        {
                            ModuleManager.DisplayModule(ModuleNames.Editor);

                        }
                        else if (memory.Type == LibraryType.Playlist)
                            ModuleManager.DisplayModule(ModuleNames.Playlists);

                        ModuleControl mc = ModuleManager.CurrentModuleControl as ModuleControl;
                        if (mc != null)
                        {
                            var editor = mc as ProWrite.UI.Controls.Modules.EditorModuleNew;
                            if (editor != null)
                            {
            
                                editor.TabControl.ActivePageByModel(memory as MessageInfo);
                            }

                            var plsylist = mc as ProWrite.UI.Controls.Modules.PlaylistModuleNew;
                            if (plsylist != null)
                            {
                                plsylist.TabControl.ActivePageByModel(memory as PlaylistInfo);
                            }

                            var scheduler = mc as ProWrite.UI.Controls.Modules.SchedulerModule;
                            if (scheduler != null)
                            {
                                scheduler.TabControl.ActivePageByModel(memory as SchedulerInfo);
                            }
                        }
                        return;
                    }
                    else
                        memory.IsOpen = true;
                    bool canOpen = CommonHelper.IsShowOpenDialog(memory.Type);
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                             new MenuCommand{ Command =  MenuCommands.Open,Enabled = canOpen}
                        }));
                }
                if (locker != null)
                    locker.IsLock = true;


                //return true;
                _openLibraryItem(this, new OpenLibraryEventArgs(item));
            }
        }

        [NonSerialized]
        private EventHandler<RemoveLibraryEventArgs> _removeLibraryItem;
        public event EventHandler<RemoveLibraryEventArgs> RemoveLibraryItemEvent
        {
            add { _removeLibraryItem += value; }
            remove { _removeLibraryItem -= value; }
        }

        private void OnRemoveLibraryItem(LibraryType type)
        {

            _removeLibraryItem(this, new RemoveLibraryEventArgs(type));

        }


        protected override void OnKeyUp(KeyEventArgs e)
        {
            base.OnKeyUp(e);

            if (e.KeyCode == Keys.Delete)
                RemoveLibraryItemNew();
            //RemoveLibraryItem();
        }

        protected override void OnMouseDoubleClick(MouseEventArgs e)
        {
            base.OnMouseDoubleClick(e);

            if (FocusedNode != null
                && FocusedNode.Library != null)
            {
                //switch (FocusedNode.Library.Type)
                //{
                //    case LibraryType.Message:
                //        LocalMessageBus.Send(FocusedNode.Library, new PWMessage<MenuCommands>(MenuCommands.OpenMessage));
                //        break;
                //    case LibraryType.Playlist:
                //        LocalMessageBus.Send(FocusedNode.Library, new PWMessage<MenuCommands>(MenuCommands.OpenPlaylist));
                //        break;
                //    case LibraryType.Schedule:
                //        LocalMessageBus.Send(FocusedNode.Library, new PWMessage<MenuCommands>(MenuCommands.OpenScheduler));
                //        break;
                //    default:
                //        return;
                //}
                ControlService.CancelPoistions();
                OnOpenLibraryItem(FocusedNode.Library);
                ControlService.RestorePoistions();
            }
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            LocalMessageBus.Send(this, new MenuMessage(MenuCommands.Delete, false));
            base.OnMouseDown(e);
            SetFocusedNode(CalcHitInfo(new Point(e.X, e.Y)).Node);

            if (FocusedNode != null)
            {
                MemoryLibraryItem item = FocusedNode.Tag as MemoryLibraryItem;
                if (item != null && item.Image != null)
                {
                    ControlService.NailImageBox.Image = item.Image;
                    ControlService.RefreshPropertyGrid(new LibraryPropertys(item));
                }
                else
                {
                    ControlService.RefreshPropertyGrid(FocusedNode.Tag);
                }
            }

            if (e.Button == MouseButtons.Left)
            {
                Size dragSize = SystemInformation.DragSize;
                dragBoxFromMouseDown = new Rectangle(new Point(e.X - (dragSize.Width / 2),
                                                               e.Y - (dragSize.Height / 2)), dragSize);
            }
        }

        public void OnLibraryDialogMouseDown(object sender,MouseEventArgs e)
        {
            TreeListNode treeNode = CalcHitInfo(new Point(e.X, e.Y)).Node;
            SetFocusedNode(treeNode);

            TreeListHitInfo hInfo = CalcHitInfo(new Point(e.X, e.Y));
            if (e.Button == MouseButtons.Left)
            {
                //When click the active column£¬change active state
                if (hInfo.HitInfoType == HitInfoType.Cell && hInfo.Column.Caption.ToLower() == "checked")
                {
                    TreeListNode node = hInfo.Node;
                    SetCheckedNode(treeNode as LibraryNode, node["Checked"]);
                }
                else
                {
                    return;
                }
                
            }
            
        }

        /// <summary>
        /// Function: Set current node state
        /// Author  : Jerry Xu
        /// Date    : 2008-9-16
        /// </summary>
        /// <param name="node">TreeListNode:library info</param>
        /// <param name="check">bool</param>
        private void SetCheckedNode(LibraryNode node, object check)
        {
            FocusedNode = node;
            BeginUpdate();
            bool flag = (bool)check;
            node["Checked"] = !flag;
            EndUpdate();
            
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);

            if ((e.Button & MouseButtons.Left) == MouseButtons.Left)
            {
                if (dragBoxFromMouseDown != Rectangle.Empty
                    && !dragBoxFromMouseDown.Contains(e.X, e.Y)
                    && FocusedNode != null
                    && FocusedNode.Library != null)
                {
                    LibraryItem item = FocusedNode.Tag as LibraryItem;
                    if (item == null || item.Type == LibraryType.Schedule)
                        return;

                    //ILockLibraryItem locker = FocusedNode.Library as ILockLibraryItem;
                    //if (locker != null)
                    //    locker.IsLock = true;

                    DoDragDrop(FocusedNode, DragDropEffects.Copy);
                }
            }
        }
    }
}
