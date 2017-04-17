using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UFE;
using ProWrite.UFE.Entity;
using DevExpress.XtraBars;
using ProWrite.Entity.Dashboard;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Actions.UFE
{
    public sealed class ActionHelper
    {
        public static void OnDisconnected(bool connectState)
        {
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                                   new MenuCommand{ Command = MenuCommands.Connect,Caption ="Connect",Enabled = connectState}
                                    ,new MenuCommand{ Command = MenuCommands.UserManager,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.Dimming,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.TempOffset,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.ResetTime,Enabled = false}
                                    ,new MenuCommand { Command = MenuCommands.BlankSign,Caption = "Stop", Enabled = false}
                                     ,new MenuCommand { Command = MenuCommands.UnBlankSign,Caption = "Play", Enabled = false}
                                    ,new MenuCommand { Command = MenuCommands.TestPattern, Enabled = false}
                                    ,new MenuCommand { Command = MenuCommands.RebootCXC, Enabled = false}
                                    ,new MenuCommand { Command = MenuCommands.TimeZone, Enabled = false}
                                    ,new MenuCommand { Command = MenuCommands.LiveImage, Enabled = false}
                             }));

            if(ControlService.SignCombo.Current != null)
                ControlService.SignCombo.Current.IsConnected = "DisConnected";
            ControlService.SignImage.RefreshImage();
            ControlService.DashboardTree.PopulateTree();
            ControlService.CurrentClip.RefreshClip();
        }

        public static void OnCancelConnect()
        {
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                                   new MenuCommand{ Command = MenuCommands.CancelConnect,Caption ="Cancel",Enabled = true}
                                   //,new MenuCommand{ Command = MenuCommands.UserManager,Enabled = false}
                                   // ,new MenuCommand{ Command = MenuCommands.Dimming,Enabled = false}
                                   // ,new MenuCommand{ Command = MenuCommands.TempOffset,Enabled = false}
                                   // ,new MenuCommand{ Command = MenuCommands.ResetTime,Enabled = false}
                                   // ,new MenuCommand { Command = MenuCommands.BlankSign, Enabled = false}
                                   // ,new MenuCommand { Command = MenuCommands.TestPattern, Enabled = false}
                                   // ,new MenuCommand { Command = MenuCommands.RebootCXC, Enabled = true}
                                   // ,new MenuCommand { Command = MenuCommands.TimeZone, Enabled = false}
                                   // ,new MenuCommand { Command = MenuCommands.LiveImage, Enabled = false}
                             }));
        }
        public static void OnConnected()
        {
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                                   new MenuCommand{ Command = MenuCommands.Connect,Caption ="Connect",Enabled = true}
                                   ,new MenuCommand{ Command = MenuCommands.UserManager,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.Dimming,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.TempOffset,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.ResetTime,Enabled = false}
                                    ,new MenuCommand { Command = MenuCommands.BlankSign,Caption = "Stop", Enabled = false}
                                    ,new MenuCommand { Command = MenuCommands.UnBlankSign,Caption = "Play", Enabled = false}
                                    ,new MenuCommand { Command = MenuCommands.TestPattern}
                                    ,new MenuCommand { Command = MenuCommands.RebootCXC, Enabled = true}
                                    ,new MenuCommand { Command = MenuCommands.TimeZone, Enabled = false}
                                    ,new MenuCommand { Command = MenuCommands.LiveImage, Enabled = false}
                             }));
        }

        public static void OnAfterLogin(User user)
        {
            bool enableCommand = user.IsCommandRole;
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                                   new MenuCommand{ Command = MenuCommands.DisConnect,Caption ="Disconnect",Enabled = true}
                                    ,new MenuCommand{ Command = MenuCommands.UserManager,Enabled = true}
                                    ,new MenuCommand{ Command = MenuCommands.Dimming,Enabled = enableCommand}
                                    ,new MenuCommand{ Command = MenuCommands.TempOffset,Enabled = enableCommand}
                                    ,new MenuCommand{ Command = MenuCommands.ResetTime,Enabled = enableCommand}
                                    ,new MenuCommand { Command = MenuCommands.BlankSign,Caption = "Stop", Enabled = enableCommand}
                                    ,new MenuCommand { Command = MenuCommands.UnBlankSign,Caption = "Play", Enabled = enableCommand}
                                    ,new MenuCommand { Command = MenuCommands.TestPattern, Enabled = enableCommand}
                                    ,new MenuCommand { Command = MenuCommands.RebootCXC, Enabled = enableCommand}
                                    ,new MenuCommand { Command = MenuCommands.TimeZone, Enabled = enableCommand}
                                    ,new MenuCommand { Command = MenuCommands.LiveImage, Enabled = enableCommand}
                             }));
            OnBlankSign();
        }

        public static void OnAfterLogoff()
        {
            OnDisconnected(true);
        }

        public static void OnBlankSign()
        {
            SignInfo sign = ControlService.SignCombo.Current;
            BlankSign blankSign = new BlankSign();
            blankSign.Mode = 1;
            blankSign.Flag = -1;
            int flag = 0;

            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                                   new MenuCommand{ Command = MenuCommands.UnBlankSign,Caption ="Play",Enabled = false}
                                    ,new MenuCommand { Command = MenuCommands.BlankSign,Caption = "Stop", Enabled = false}
                                    }));
            DataGate.Log.Info("Start get the  Sign state.Content:blankSign.Mode=1,blankSign.Flag=-1");
            if (sign.Controller.Connection.State == System.Communication.ConnectionState.Opened
                || sign.Controller.Connection.User.Status == UserStatus.Online)
            {

                //Cursor.Current = Cursors.WaitCursor;

                sign.Controller.SendAsync(
                    Commands.BlankSign,
                    p =>
                    {
                        //Cursor.Current = Cursors.Default;
                        if (!p.IsSuccessed)
                        {
                            DataGate.Log.Error("Get sign state failed");
                            //if (p.Packet.HasError)
                            //    log.Error(p.Packet.ActionError.Message);
                            //if (p.Exception != null)
                            //    log.Error(p.Exception.Message, p.Exception);
                            string caption = "Stop";
                            MenuCommands command = MenuCommands.BlankSign;

                            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                                   new MenuCommand{ Command = command,Caption =caption,Enabled = true}
                             }));
                            //MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SetBlankSignFailed));//"Blank sign failed.");
                        }
                        else
                        {

                            flag = p.Packet.Content.GetProperty<int>("Mode");
                            DataGate.Log.Info("Get sign state successed.Content:flag=" + flag);
                            string caption = "Stop";
                            MenuCommands command = MenuCommands.BlankSign;
                            if (flag == 3 || flag == 4 || flag == 5)
                            {
                                sign.MessageStatus = "Stopped";
                                ControlService.CurrentClip.SetPicImageNull();
                                if (!ServiceManager.Get<bool>())
                                {
                                    ServiceManager.Remove<bool>();
                                    ServiceManager.Add<bool>(true);
                                }
                                caption = "Play";
                                command = MenuCommands.UnBlankSign;
                                LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                                   new MenuCommand{ Command = command,Caption =caption,Enabled = true}
                                    ,new MenuCommand { Command = MenuCommands.BlankSign,Caption = "Stop", Enabled = false}
                                    }));
                            }
                            else
                            {
                                if (ServiceManager.Get<bool>())
                                {
                                    ServiceManager.Remove<bool>();
                                    ServiceManager.Add<bool>(false);
                                }
                                switch (flag)
                                {
                                    case 0:
                                        sign.MessageStatus = "Playing";
                                        break;
                                    case 1:
                                        sign.MessageStatus = "Live mode";
                                        break;
                                    case 2:
                                        sign.MessageStatus = "Test Pattern";
                                        break;
                                }
                                LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                                   new MenuCommand{ Command = command,Caption =caption,Enabled = true}
                                    ,new MenuCommand { Command = MenuCommands.UnBlankSign,Caption = "Play", Enabled = false}
                                     }));
                            }
                            ControlService.DashboardTree.PopulateTree();
                            //sign.IsBlankSign = false;
                            //MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SetBlankSignSuccessed));//"Blank sign successed");
                            //ActionHelper.OnBlankSign(false);
                        }
                    },
                    blankSign);
            }
        }
    }
}
