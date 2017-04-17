//---------------------------------------------------------------------
//
// File: SignCombo.cs
//
// Description:
// Sign Combo, support automatically complete£¬Lookup, automatically refresh 
//
// Author: Kevin
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraEditors;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using ProWrite.Entity.Dashboard;
using DevExpress.XtraEditors.Controls;
using DevExpress.XtraBars;
using DevExpress.XtraEditors.Repository;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using System.Communication.Messaging;
using System.Communication;
using ProWrite.UFE;
using ProWrite.UI.Controls.Actions.UFE;

namespace ProWrite.UI.Controls
{

    public class SignRepositoryItemComboBox : RepositoryItemComboBox
    {
        public SignRepositoryItemComboBox()
        {
            //AutoComplete = true;

        //    if (!DesignMode)
        //    {
        //        LocalMessageBus.Subject<DataChangedMessage>().Observers += OnSignChanged;
        //        LocalMessageBus.Subject<ActiveChange>().Observers += new ObserverHandler<ActiveChange>(SignRepositoryItemComboBox_Observers);
        //    }
        }

        void SignRepositoryItemComboBox_Observers(object sender, ActiveChange msg)
        {
            //Populate();

        }

        /// <summary>
        /// Get the current selected Sign
        /// </summary>
        //public SignInfo Current
        //{
        //    get
        //    {

        //        if (_barItem != null && _barItem.EditValue as SignInfo != null)
        //        {
        //            if (_barItem.EditValue.ToString() != "" && (_barItem.EditValue as SignInfo).Active)
        //                return _barItem.EditValue as SignInfo;
        //        }
        //        return null;
        //    }
        //    set
        //    {
        //        if (value != null)
        //        {
        //            if (_barItem != null && _barItem.EditValue != value)
        //                _barItem.EditValue = value;
        //        }
        //        else
        //            _barItem.EditValue = "";

        //    }
        //}

        //private BarEditItem _barItem;
        //public BarEditItem Editor
        //{
        //    get { return _barItem; }
        //    set
        //    {
        //        _barItem = value;
        //        if (value != null)
        //            Populate();
        //    }
        //}



        //public string Type
        //{
        //    get
        //    {
        //        return Current == null ? null : Current.Type.ToString();
        //    }
        //}

        //public object SelectedItem
        //{
        //    get
        //    {
        //        if (_barItem == null)
        //            return null;
        //        return _barItem.EditValue;
        //    }
        //    set
        //    {
        //        if (_barItem != null && _barItem.EditValue != value)
        //            _barItem.EditValue = value;
        //    }
        //}

        ///// <summary>
        ///// Get the current selected Sign'name
        ///// </summary>
        //public string SignName
        //{
        //    get { return Current == null ? null : Current.Name; }
        //    //set
        //    //{
        //    //    if (!string.IsNullOrEmpty(value) && value != SignName)
        //    //    {
        //    //        SignInfo selected = null;
        //    //        foreach (SignInfo item in Items)
        //    //        {
        //    //            if (item.Name == value)
        //    //            {
        //    //                selected = item;
        //    //                break;
        //    //            }
        //    //        }

        //    //        SelectedItem = selected;
        //    //    }
        //    //}
        //}

        ///// <summary>
        ///// Get the current selected Sign's merge name
        ///// </summary>
        //public string SignNameMerge
        //{
        //    get { return Current == null ? null : Current.SignNameMerge; }
        //}

        ///// <summary>
        ///// Get the current selected Sign's Size
        ///// </summary>
        //public Size SignSize
        //{
        //    get { return Current == null ? Size.Empty : new Size(Current.Width, Current.Height); }
        //}

        ///// <summary>
        ///// Get the current selected Sign's type
        ///// </summary>
        //public SignType SignType
        //{
        //    get { return Current == null ? SignType.RGB : Current.Type; }
        //}

        ///// <summary>
        ///// Load data
        ///// </summary>
        //private void Populate()
        //{
        //    //Items.Clear();
        //    //_barItem.EditValue = "";
        //    //SignInfo[] signs = SignInfo.ActiveSigns;
        //    ////Graphics g = ControlService.LibraryTree.CreateGraphics();

        //    ////var center = new MenuCommand(MenuCommands.Connect, Caption = "Connect", Enabled = true);
        //    ////var left = new MenuCommand(MenuCommands.TextAlignLeft, isText || isDynamicText);
        //    ////var right = new MenuCommand(MenuCommands.TextAlignRight, isText || isDynamicText);
        //    ////var textBackGroundColor = new MenuCommand(MenuCommands.TextBackgroundColor, isText || isDynamicText);
        //    ////var textForeColor = new MenuCommand(MenuCommands.TextFontColor, isText || isDynamicText);
        //    ////var textBold = new MenuCommand(MenuCommands.TextBold, isText || isDynamicText);
        //    //if (signs != null && signs.Length > 0)
        //    //{
        //    //    foreach (SignInfo item in signs)
        //    //    {
        //    //        if (item.HasFireConnectionExceptionEvent)
        //    //        {
        //    //            item.Controller.Connection.ExceptionFired += new EventHandler<EventArgs<Exception>>(Connection_ExceptionFired);
        //    //            item.HasFireConnectionExceptionEvent = true;
        //    //        }
        //    //    }
        //    //    Items.AddRange(signs);
        //    //    if (_barItem != null)
        //    //        _barItem.EditValue = signs[0];
        //    //    SignInfo sign = Current;
        //    //    bool state = sign.Controller == null ||  sign.Controller.Connection == null
        //    //                || sign.Controller.Connection.State != ConnectionState.Opened;
        //    //    if (state)
        //    //    {
        //    //        LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
        //    //                       new MenuCommand{ Command = MenuCommands.Connect,Caption ="Connect",Enabled = sign.DashboardType== DashboardType.Sign}
        //    //                        ,new MenuCommand{ Command = MenuCommands.UserManager,Enabled = false}
        //    //                        ,new MenuCommand{ Command = MenuCommands.Dimming,Enabled = false}
        //    //                        ,new MenuCommand{ Command = MenuCommands.TempOffset,Enabled = false}
        //    //                        ,new MenuCommand{ Command = MenuCommands.ResetTime,Enabled = false}
        //    //                 }));
        //    //    }
        //    //    else
        //    //    {
        //    //        if (Current.Controller.Connection.User.Status == UserStatus.Online)
        //    //        {
        //    //            LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
        //    //                        new MenuCommand{ Command = MenuCommands.DisConnect,Caption ="DisConnect",Enabled = true}
        //    //                        ,new MenuCommand{ Command = MenuCommands.UserManager,Enabled = true}
        //    //                        , new MenuCommand { Command = MenuCommands.Dimming, Enabled = true }
        //    //                        ,new MenuCommand{ Command = MenuCommands.TempOffset,Enabled = true}
        //    //                        ,new MenuCommand{ Command = MenuCommands.ResetTime,Enabled = true}
        //    //                 }));
        //    //        }
        //    //        else
        //    //        {
        //    //            LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
        //    //                        new MenuCommand{ Command = MenuCommands.DisConnect,Caption ="Connect",Enabled = true}
        //    //                        ,new MenuCommand{ Command = MenuCommands.UserManager,Enabled = false}
        //    //                        , new MenuCommand { Command = MenuCommands.Dimming, Enabled = false }
        //    //                        ,new MenuCommand{ Command = MenuCommands.TempOffset,Enabled = false}
        //    //                        ,new MenuCommand{ Command = MenuCommands.ResetTime,Enabled = false}
        //    //                 }));
        //    //        }
        //    //    }
        //    //}
        //    //else
        //    //{
        //    //    LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
        //    //                       new MenuCommand{ Command = MenuCommands.Connect,Caption ="Connect",Enabled=Current.DashboardType== DashboardType.Sign}
        //    //                        ,new MenuCommand{ Command = MenuCommands.UserManager,Enabled = false}
        //    //                        ,new MenuCommand{ Command = MenuCommands.Dimming,Enabled = false}
        //    //                        ,new MenuCommand{ Command = MenuCommands.TempOffset,Enabled = false}
        //    //                        ,new MenuCommand{ Command = MenuCommands.ResetTime,Enabled = false}
        //    //                 }));
        //    //}
        //}

        //void Connection_ExceptionFired(object sender, EventArgs<Exception> e)
        //{
        //    ActionHelper.OnDisconnected(Current.DashboardType== DashboardType.Sign);
        //}

        

        private void TestForm_Paint(object sender, PaintEventArgs e)
        {
            //Graphics g = e.Graphics;
            //string text = "Hello,   world...   Showing   MeasureString   and   MeasureDisplayStringWidth";

            //PointF pf = new PointF(10f, 10f);
            //StringFormat format = new StringFormat();//   StringFormat.GenericTypographic;   
            //SizeF sf = g.MeasureString(text, this.Font, pf, format);

            //g.DrawRectangle(SystemPens.ActiveCaption,
            //(int)pf.X, (int)pf.Y, (int)sf.Width, (int)sf.Height);

            //g.DrawString(text, this.Font, SystemBrushes.ActiveCaptionText, pf, format);
        }
        /// <summary>
        /// When add ,modify ,delete Sign data, refresh combo
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnSignChanged(object sender, DataChangedMessage e)
        {
            //if (e.DataType == PWDataType.Dashboard)
            //    Populate();
            //LocalMessageBus.Send(this, new MenuMessage(
            //                    new MenuCommand
            //                    {
            //                        Command = MenuCommands.Connect,
            //                        Caption = "Connect",
            //                        Enabled = Current != null&&Current.DashboardType==DashboardType.Sign
            //                    }));
        }

        private void InitializeComponent()
        {
            //((System.ComponentModel.ISupportInitialize)(this)).BeginInit();
            //((System.ComponentModel.ISupportInitialize)(this)).EndInit();

        }

    }
}
