//---------------------------------------------------------------------
//
// File: LiveImageAction.cs
//
// Description:
// The uploadAction class of LiveImage
//
// Author: Terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE;
using ProWrite.UI.Controls.Common;
using ProWrite.Entity.Dashboard;
using System.Windows.Forms;
using System.IO;
using System.Drawing;
using ProWrite.Core;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.Entity.Library;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    public class LiveImageAction : UFERequestActionBase
    {
        public override Commands Id
        {
            get { return Commands.LiveImage; }
        }
        private bool IsConfirm = false;
        private const string strNA = "N/A";
        public SignInfo Sign
        {
            get;
            set;
        }
        public LiveImageAction()
        {
            IsConfirm = false;
        }
        public LiveImageAction(bool isConfirm)
        {
            IsConfirm = isConfirm;
        }

        public override void Perform()
        {
            if (ServiceManager.Get<bool>())
            {
                ControlService.CurrentClip.SetPicImageNull();
                return;
            }
            if (Sign == null && ControlService.SignCombo.Current == null)
            {
                if (IsConfirm)
                    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.AddNewSignFirst));
                return;
            }

            SignInfo sign = ControlService.SignCombo.Current;
            if (Sign != null && Sign != sign)
                sign = Sign;
            Cursor.Current = Cursors.WaitCursor;

            sign.Controller.SendAsync(Id, p =>
            {
                Cursor.Current = Cursors.Default;
                if (!p.IsSuccessed)
                {
                    ControlService.CurrentClip.SetPicImageNull();
                   

                    if (p.Packet.HasError)
                        log.Error(p.Packet.ActionError.Message);
                    if (p.Exception != null)
                        log.Error(p.Exception.Message, p.Exception);

                    if (IsConfirm)
                        MsgBox.Error("Get live shape failed,please try again.");
                }
                else
                {
                    object[] content = p.Packet.Content.GetProperty<object[]>("StatusList");
                    //object[] content = p.Packet.Content as object[];
                    if (content != null && content.Length > 0)
                    {
                        try
                        {
                            string messageId = (content[0] as Dictionary<string, object>).Values.ToArray()[3].ToString();
                            string messageInfo = (content[0] as Dictionary<string, object>).Values.ToArray()[4].ToString();
                            string scheduleInfo = (content[0] as Dictionary<string, object>).Values.ToArray()[6].ToString();
                            string plsylistInfo = (content[0] as Dictionary<string, object>).Values.ToArray()[8].ToString();
                            string toFilePath = DataGate.Provider.Path + "\\Library\\Upload\\Message\\" + messageId + ".png";
                            string fromFilePath = "/mnt/sdcard/.ufe/data/messages/" + messageId + "/" + messageId + ".png";

                            ControlService.CurrentClip.UpdateMessageInfo = messageInfo;

                            sign.MessageIdInfo = messageInfo;
                            ControlService.CurrentClip.UpdateScheduleInfo = scheduleInfo;

                            ControlService.CurrentClip.UpdatePlaylist = plsylistInfo;
                            ControlService.CurrentClip.UpdateDate = DateTime.Now.GetDateTimeFormats()[69];
                            //MessageInfo msg = LibraryGroup.Current.Messages.GetById(messageId);

                            Image desImg = IOHelper.GetImageFromFile(toFilePath);
                            if (desImg != null)
                                ControlService.CurrentClip.PicCurrent.Image = desImg;
                            else
                            {
                                sign.Controller.Connection.FtpManager.DownLoad(fromFilePath, toFilePath);

                                desImg = IOHelper.GetImageFromFile(toFilePath);
                                ControlService.CurrentClip.PicCurrent.Image = desImg;
                            }
                        }
                        catch { }

                        //int length = content.Length;
                        //var byt = new byte[length];
                        //for (int i = 0; i < length; i++)
                        //    byt[i] = Convert.ToByte(content[i]);

                        //Image img = ToImage(byt);
                        ////ControlService.SignImage.PicLiveView.Image = img;
                        //ControlService.CurrentClip.PicCurrent.Image = img;
                        //string strLastUpdate = DateTime.Now.GetDateTimeFormats()[69];
                        ////ControlService.SignImage.UpdateDate = strLastUpdate;
                        //ControlService.CurrentClip.UpdateDate = strLastUpdate;
                        //sign.LastUpdateClip = strLastUpdate;
                        //string file = Guid.NewGuid().ToString() + ".jpg";
                        //string fileName = Constance.SignImageDir + file;
                        //try
                        //{
                        //    FileStream stream = new FileStream(fileName, FileMode.CreateNew);
                        //    stream.Write(byt, 0, length);
                        //}
                        //catch (Exception ex)
                        //{
                        //    log.Error(ex.Message);
                        //}
                        ////IOHelper.SaveImage(img.Clone() as Image, fileName);
                        //sign.ImageCurrentClip = file;
                    }
                    else if (IsConfirm)
                        MsgBox.Warning("Get live shape failed,please try again.");
                }
            });
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.Delete}    
                }));
        }

        public Image ToImage(Byte[] byt)
        {
            using (MemoryStream stream = new MemoryStream(byt))
            {
                Image image = Image.FromStream(stream);

                return image;
            }
        }
    }
}
