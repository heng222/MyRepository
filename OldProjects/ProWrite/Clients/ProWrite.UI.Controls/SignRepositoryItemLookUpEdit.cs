using System;
using System.Collections.Generic;
using System.Communication;
using System.Communication.Messaging;
using System.Linq;
using System.Text;
using DevExpress.XtraBars;
using DevExpress.XtraEditors.Repository;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;
using ProWrite.UFE;
using ProWrite.UI.Controls.Actions.UFE;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;

namespace ProWrite.UI.Controls
{
    public class SignRepositoryItemLookUpEdit : RepositoryItemLookUpEdit
    {
        public SignRepositoryItemLookUpEdit()
        {
            Columns.AddRange(new DevExpress.XtraEditors.Controls.LookUpColumnInfo[] {
            new DevExpress.XtraEditors.Controls.LookUpColumnInfo("Name", "Sign Name", 20, DevExpress.Utils.FormatType.None, "", true, DevExpress.Utils.HorzAlignment.Default, DevExpress.Data.ColumnSortOrder.None),
            new DevExpress.XtraEditors.Controls.LookUpColumnInfo("Size", "Size", 20, DevExpress.Utils.FormatType.None, "", true, DevExpress.Utils.HorzAlignment.Default, DevExpress.Data.ColumnSortOrder.None),
            new DevExpress.XtraEditors.Controls.LookUpColumnInfo("Type", "Type", 20, DevExpress.Utils.FormatType.None, "", true, DevExpress.Utils.HorzAlignment.Default, DevExpress.Data.ColumnSortOrder.None)});
            DisplayMember = "SignInfo";
            DropDownRows = 11;
            PopupWidth = 300;
            ValueMember = "SignInfo";
            NullText = " [SignInfo is null] ";
            this.EditValueChanged += new EventHandler(SignRepositoryItemLookUpEdit_EditValueChanged);
            if (!DesignMode)
            {
                LocalMessageBus.Subject<DataChangedMessage>().Observers += OnSignChanged;
                LocalMessageBus.Subject<ActiveChange>().Observers += new ObserverHandler<ActiveChange>(SignRepositoryItemComboBox_Observers);
            }
        }

        void SignRepositoryItemLookUpEdit_EditValueChanged(object sender, EventArgs e)
        {
            //DevExpress.XtraEditors.LookUpEdit lookUpEdit = sender as DevExpress.XtraEditors.LookUpEdit;
            //if (lookUpEdit != null)
            //    SignInfo.Current = lookUpEdit.EditValue as SignInfo;
        }

        void SignRepositoryItemComboBox_Observers(object sender, ActiveChange msg)
        {
            Current = msg.CurrentSign;
            SignInfo.Current = msg.CurrentSign;
            Populate();
            
            this.BestFit();

        }

        //public override string NullText
        //{
        //    get
        //    {
        //        return base.NullText;
        //    }
        //    set
        //    {
        //        //base.NullText = value;
        //        //if (Editor != null)
        //        //    Editor.Refresh();
              
        //    }
        //}
        /// <summary>
        /// When add ,modify ,delete Sign data, refresh combo
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnSignChanged(object sender, DataChangedMessage e)
        {
            if (e.DataType == PWDataType.Dashboard)
                Populate();
            LocalMessageBus.Send(this, new MenuMessage(
                                new MenuCommand
                                {
                                    Command = MenuCommands.Connect,
                                    Caption = "Connect",
                                    Enabled = Current != null && Current.DashboardType == DashboardType.Sign
                                }));
        }

        /// <summary>
        /// Get the current selected Sign
        /// </summary>
        public SignInfo Current
        {
            get
            {

                if (_barItem != null && _barItem.EditValue as SignInfo != null)
                {
                    if (_barItem.EditValue.ToString() != "" && (_barItem.EditValue as SignInfo).Active)
                        return _barItem.EditValue as SignInfo;
                }
                return null;
            }
            set
            {
                if (value != null)
                {
                    if (_barItem != null && _barItem.EditValue != value)
                    {
                        _barItem.EditValue = value;
                        if(value.DashboardType == DashboardType.Sign
                            &&value.Controller.Connection.State!= ConnectionState.Opened)
                        ActionHelper.OnDisconnected(true);
                        if(value.DashboardType != DashboardType.Sign)
                            ActionHelper.OnDisconnected(false);
                    }
                }
                else
                    _barItem.EditValue = "";

            }
        }

        private BarEditItem _barItem;
        public BarEditItem Editor
        {
            get { return _barItem; }
            set
            {
                _barItem = value;
                if (value != null)
                    Populate();
            }
        }

        List<SignRepositoryItem> _items = new List<SignRepositoryItem>();

        /// <summary>
        /// Load data
        /// </summary>
        private void Populate()
        {
            SignInfo[] signs = DashboardItem.ActiveSigns;

            if (signs != null && signs.Length > 0)
            {
                _items.Clear();
                foreach (SignInfo signInfo in signs)
                {
                    SignRepositoryItem item = new SignRepositoryItem(signInfo);
                    _items.Add(item);
                }
                DataSource = null;
                DataSource = _items;
                NullText = _items[0].ToString();

                if (_barItem != null)
                    _barItem.EditValue = signs[0];
                SignInfo sign = Current;
                SignInfo.Current = sign;
                bool state = sign.Controller == null || sign.Controller.Connection == null
                            || sign.Controller.Connection.State != ConnectionState.Opened;
                if (state)
                {
                    Current.IsBlankSign = true;
                    LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                                   new MenuCommand{ Command = MenuCommands.Connect,Caption ="Connect",Enabled = sign.DashboardType== DashboardType.Sign}
                                    ,new MenuCommand{ Command = MenuCommands.UserManager,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.Dimming,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.TempOffset,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.ResetTime,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.BatchLoad,Enabled = true}
                             }));
                }
                else
                {
                    if (Current.Controller.Connection.User.Status == UserStatus.Online)
                    {
                        LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                                    new MenuCommand{ Command = MenuCommands.DisConnect,Caption ="DisConnect",Enabled = true}
                                    ,new MenuCommand{ Command = MenuCommands.UserManager,Enabled = true}
                                    , new MenuCommand { Command = MenuCommands.Dimming, Enabled = true }
                                    ,new MenuCommand{ Command = MenuCommands.TempOffset,Enabled = true}
                                    ,new MenuCommand{ Command = MenuCommands.BatchLoad,Enabled = true}
                                    , new MenuCommand { Command = MenuCommands.TestPattern, Enabled = true }
                             }));
                    }
                    else
                    {
                        Current.IsBlankSign = true;
                        LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                                    new MenuCommand{ Command = MenuCommands.DisConnect,Caption ="Connect",Enabled = true}
                                    ,new MenuCommand{ Command = MenuCommands.UserManager,Enabled = false}
                                    , new MenuCommand { Command = MenuCommands.Dimming, Enabled = false }
                                    ,new MenuCommand{ Command = MenuCommands.TempOffset,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.ResetTime,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.BatchLoad,Enabled = true}
                             }));
                    }
                }
            }
            else
            {
                NullText = " [SignInfo is null] ";
                DataSource = null;
                SelectedItem = null;
                LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                                   new MenuCommand{ Command = MenuCommands.Connect,Caption ="Connect",Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.UserManager,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.Dimming,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.TempOffset,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.ResetTime,Enabled = false}
                                    ,new MenuCommand{ Command = MenuCommands.BatchLoad,Enabled = false}
                             }));
            }
        }

        void Connection_ExceptionFired(object sender, EventArgs<Exception> e)
        {
            ActionHelper.OnDisconnected(Current.DashboardType == DashboardType.Sign);
        }

        /// <summary>
        /// Get the current selected Sign'name
        /// </summary>
        public string SignName
        {
            get { return Current == null ? null : Current.Name; }

        }

        /// <summary>
        /// Get the current selected Sign's type
        /// </summary>
        public SignType SignType
        {
            get { return Current == null ? SignType.RGB : Current.Type; }
        }

        public object SelectedItem
        {
            get { return Current; }
            set { Current = value as SignInfo; }
        }

        public SignInfo[] Items
        {
            get { return DashboardItem.ActiveSigns; }
        }

    }

    public class SignRepositoryItem
    {
        private SignInfo _signInfo;
        public SignRepositoryItem(SignInfo signInfo)
        {
            this._signInfo = signInfo;
        }

        public SignInfo SignInfo
        {
            get { return _signInfo; }
        }

        public string Name
        {
            get { return _signInfo.Name; }
        }

        public string Size
        {
            get { return _signInfo.Height + " x " + _signInfo.Width; }
        }

        public SignType Type
        {
            get { return _signInfo.Type; }
        }

        public override string ToString()
        {
            return _signInfo.ToString();
        }
    }
}
