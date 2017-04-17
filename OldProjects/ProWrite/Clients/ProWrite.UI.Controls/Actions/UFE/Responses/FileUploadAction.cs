//---------------------------------------------------------------------
//
// File: FileUploadAction.cs
//      
// Description:
//      
//
// Author: 
//
// Modify History:
//      Jerry Xu 2009-3-6 Update method:HandleResponseSuccess(UFEPacket resp)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE.Entity;
using ProWrite.UFE;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Actions.UFE.Responses
{
    class UploadFileCompletedAction : ProxyAction
    {
        public override Commands Id
        {
            get { return Commands.UploadFileCompleted; }
        }

        private void HandleResponseSuccess1(UFEPacket resp)
        {
            var fileList = resp.Content.GetProperty<object[]>("FileList");
            if (fileList != null && fileList.Length > 0 )
            {
                List<ServerLibraryItem> libraries = Controller.Connection.ServerLibraries;
                if (libraries == null)
                    libraries = new List<ServerLibraryItem>();

                foreach (var o in fileList)
                {
                    var item = serializer.ConvertToType<UfeFile>(o);
                    var type = ConvertLibraryType(item.Type);
                    if (type != ServerLibraryType.None)
                    {
                        if (item.IsUpdate)
                        {
                            var old = libraries.Find(p => { return p.Id == item.Id; });
                            if (old != null)
                                libraries.Remove(old);
                        }

                        libraries.Add(new ServerLibraryItem
                        {
                            Id = item.Id,
                            Name = item.Name,
                            Length = item.Length,
                            Type = type,
                            CreateTime = item.CreateTime,
                            ModifyTime = item.ModifyTime,
                        });
                    }
                }
            }
                
            
            base.HandleResponseSuccess(resp);
        }

        protected override void HandleResponseSuccess(UFEPacket resp)
        {
            var fileList = resp.Content.GetProperty<object[]>("FileList");
            if (fileList != null && fileList.Length > 0)
            {
                List<ServerLibraryItem> libraries = new List<ServerLibraryItem>();

                foreach (var o in fileList)
                {
                    var item = serializer.ConvertToType<UfeFile>(o);
                    var type = ConvertLibraryType(item.Type);
                    

                    libraries.Add(new ServerLibraryItem
                    {
                        Id = item.Id,
                        Name = item.Name,
                        Length = item.Length,
                        Type = type,
                        CreateTime = item.CreateTime,
                        ModifyTime = item.ModifyTime,
                    });
                    
                }
                Controller.Connection.ServerLibraries = libraries;
                //Controller.Connection.ServerLibraries = libraries;
            }


            base.HandleResponseSuccess(resp);
        }

        private ServerLibraryType ConvertLibraryType(FileType type)
        {
            switch (type)
            {
                case FileType.Message:
                    return ServerLibraryType.Message;
                case FileType.Playlist:
                    return ServerLibraryType.Playlist;
                case FileType.TimesliceGroup:
                    return ServerLibraryType.TimesliceGroup;
                case FileType.Schedule:
                    return ServerLibraryType.Schedule;
                case FileType.TemplateMessage:
                    return ServerLibraryType.None;
                default:
                    return ServerLibraryType.None;
            }
        }
    }
}
