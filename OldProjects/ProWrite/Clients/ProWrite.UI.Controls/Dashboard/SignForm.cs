//---------------------------------------------------------------------
//
// File: SignForm.cs
//
// Description:
// The UI of add or edit sign 
//
// Author: terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
//
//Modify history:   
//  Terry  2008-6-23 修改内容：修改无法添加New Sign的bug
//  Terry  2008-6-25 修改内容：修改上传图片
//  Terry  2008-6-25 修改内容：添加Region和部分注释 
//  Terry  2008-7-14 修改内容：取消ddlSignParent和txtSignName的数据绑定
//---------------------------------------------------------------------
using System;
using System.ComponentModel;
using System.IO;
using System.Windows.Forms;
using DevExpress.Utils;

using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Settings;
using ProWrite.Resources;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Settings;
using ProWrite.Core;
using System.Drawing;
using DevExpress.XtraEditors;
using System.Text.RegularExpressions;
using System.Net;
using Org.Mentalis.Network.ProxySocket;
using ProWrite.UFE;
using System.Net.Tcp;
using ProWrite.UI.Controls.Common.Messages;
using System.Threading;
using System.Net.Sockets;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using ProWrite.UI.Controls.Actions.UFE.Responses;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// The UI of add or edit sign
    /// </summary>
    public partial class SignForm : DashboardForm<SignInfo>
    {
        #region Variant define

        private string creatGroup = "[Create Group]";
        private SignOld signOld = new SignOld();
        private string strImageFullName = "";
        private bool _isRefresh;
        private bool _showWebCam;
        bool isUseProxy = false;
        bool isLiveSign = false;
        bool isConnect = false;
        bool isOnline = false;
        bool isDisconnect = false;
        bool isSaveClose = false;
        private TemplateGroup _currentTemplateGroup = TemplateGroup.Default;
        private TemplateGroup CurrentTemplateGroup
        {
            get { return _currentTemplateGroup; }
            set { _currentTemplateGroup = value; }
        }
        #endregion

        #region Constructors

        /// <summary>
        /// Edit
        /// </summary>
        /// <param name="sign"></param>
        public SignForm(SignInfo sign, bool isAddToGroup)
            : base(sign, sign.Parent)
        {
            signOld.Name1 = sign.Name;
            signOld.Parent = sign.Parent;
            signOld.Width = sign.Width;
            signOld.Height = sign.Height;
            signOld.Type = sign.Type;
            signOld.SignInfomation = sign.SignInfomation;
            signOld.Template = sign.Template.Copy();
            _isAddToGroup = isAddToGroup;
            InitializeComponent();
            if (isAddToGroup)
            {
                this.Height = 140;
                signPanel.Height = 100;
                lblImage.Visible = false;
                btSignImage.Visible = false;
                lblTemplate.Visible = false;
                btnDeleteImage.Visible = false;
                btnMoreDetail.Visible = false;
                btnAddTemplate.Visible = false;
                lbnSignType.Visible = false;
                ddlSignType.Visible = false;
                lblHeight.Visible = false;
                txtHeight.Visible = false;
                lblWidth.Visible = false;
                txtWidth.Visible = false;
                ddlTemplate.Visible = false;
                lblPx1.Visible = false;
                lblPX.Visible = false;
                btnSave.Location = btSignImage.Location;
                btnCancel.Location = new Point(btSignImage.Location.X + btnSave.Width + 10, btSignImage.Location.Y);
            }
        }

        /// <summary>
        /// Add sign
        /// </summary>
        /// <param name="parent"></param>
        public SignForm(SignGroupInfo parent)
            : base(parent)
        {
            InitializeComponent();
            RegisterHelp();
        }

        /// <summary>
        /// Add sign to root
        /// </summary>
        public SignForm()
            : this(DataGate.Project.RootGroup)
        {
            RegisterHelp();
        }

        #endregion

        #region Initialization

        /// <summary>
        /// 初始化资源
        /// </summary>
        public override void InitializeResource()
        {
            base.InitializeResource();
            if (_IsEdit)
                this.Text = Resource.GetString(Resource.Strings.EditSign);
            else
                this.Text = Resource.GetString(Resource.Strings.AddSign);

            this.lblParentGroup.Text = Resource.GetString(Resource.Strings.DashboardForm_lblParent);
            this.lblSignName.Text = Resource.GetString(Resource.Strings.DashboardForm_lblSignName);
            this.lbnSignType.Text = Resource.GetString(Resource.Strings.DashboardForm_lbnSignType);
            this.lblPX.Text = Resource.GetString(Resource.Strings.DashboardForm_lblPX);
            this.lblWidth.Text = Resource.GetString(Resource.Strings.DashboardForm_lblWidth);
            this.lblPx1.Text = Resource.GetString(Resource.Strings.DashboardForm_lblPX);
            this.lblHeight.Text = Resource.GetString(Resource.Strings.DashboardForm_lblHeight);
            this.lblImage.Text = Resource.GetString(Resource.Strings.DashboardForm_lblImage);
            this.lblTemplate.Text = "Use Template:";
            btnMoreDetail.Visible = false;
            btnAddTemplate.Visible = false;
        }

        /// <summary>
        /// Initialization UI
        /// </summary>
        protected override void Init()
        {
            UFEResponseService.Init(Current);

            ddlProxyType.Properties.Items.Clear();
            ddlProxyType.Properties.Items.AddRange(Enum.GetValues(typeof(ProxyTypes)));
            //ddlSignParent.Properties.Items.Add(SignGroupInfo.Empty);
            ddlSignParent.Properties.Items.Add(new SignGroupInfo(true));

            SignGroupInfo[] groups = SignGroupTree.AllGroups;
            if (groups != null && groups.Length > 0)
                ddlSignParent.Properties.Items.AddRange(groups);

            ddlSignType.Properties.Items.AddRange(Enum.GetValues(typeof(SignType)));
            ddlSignParent.Properties.Items.Add(creatGroup);

            ddlSignParent.Text = _Parent.Name;
            ddlSignParent.SelectedItem = _Parent;

            //数据绑定
            this.txtHeight.Properties.EditFormat.FormatType = FormatType.Numeric;
            this.txtHeight.KeyPress += new KeyPressEventHandler(txtWidth_KeyPress);
            this.txtWidth.Properties.EditFormat.FormatType = FormatType.Numeric;

            this.txtWidth.KeyPress += new KeyPressEventHandler(txtWidth_KeyPress);
            bindingSource1.DataSource = Current;

            BindCombox();
            txtSignName.Text = Current.Name;
            if (!_IsEdit
                && (Current.Image == null || Current.Image == ""))
            {
                btSignImage.Text = TemplateGroup.Default.Sign.Image;
                strImageFullName = btSignImage.Text.Trim();
            }
            else
                btSignImage.Text = strImageFullName = Current.Image;
            if (string.IsNullOrEmpty(btSignImage.Text))
                btnDeleteImage.Enabled = false;
            txtConnectIpAddress.Text = "10.10.65.74";
            txtConnectPortNo.Text = "2011";
            txtConnectPWD.Text = "123456";
            txtServerName.Text = "root";

            //根据当前的操作状态，来设定ddlSignParent的默认选中项
            if (_IsEdit)
            {
                _showWebCam = !Current.IsWebCam;
                if (_Parent != null && !_Parent.IsRoot)
                    ddlSignParent.SelectedItem = Current.Parent;
                else
                    ddlSignParent.SelectedIndex = 0;
                txtHeight.Text = Current.Height.ToString();
                txtWidth.Text = Current.Width.ToString();
                rdbWebCam.Checked = Current.IsWebCam;
                rdbPhotograph.Checked = !Current.IsWebCam;
                ddlSignType.SelectedItem = Current.Type;
                chkStorePWD.Checked = Current.LoginInfomation.ConnectionPassword != null && Current.LoginInfomation.ConnectionPassword != "";
                isLiveSign = Current.DashboardType == DashboardType.Sign;
                if (isLiveSign)
                {
                    rdbDemoSign.Checked = false;
                    rdbLiveSign.Checked = true;
                    rdbDemoSign.Enabled = false;


                }
                else
                {
                    rdbDemoSign.Checked = true; ;
                    rdbLiveSign.Checked = false;
                    rdbLiveSign.Enabled = false;
                    rdbWebCam.Enabled = false;
                }
                grConncet.Visible = isLiveSign;
                grSign.Visible = !isLiveSign;
                if (isLiveSign && !_isAddToGroup)
                {
                    isConnect = Current.Controller.Connection.State == System.Communication.ConnectionState.Opened;
                    isOnline = Current.Controller.Connection.User.Status == UserStatus.Online;
                    if (isConnect)
                    {
                        this.btnSave.Location = new System.Drawing.Point(156, BtnSaveHeight(false));
                        btnSave.Width = 87;
                        btnSave.Text = "DisConnect";
                        btnSave.ToolTip = "DisConnect";
                        btnSave.Image = Resources.Resource.GetImage(Resources.Resource.Images.Disconnect16);
                    }
                    else
                    {
                        this.btnSave.Location = new System.Drawing.Point(166, BtnSaveHeight(false));
                        btnSave.Width = 77;
                        btnSave.Text = "Connect";
                        btnSave.ToolTip = "Connect";
                        btnSave.Image = Resources.Resource.GetImage(Resources.Resource.Images.Connect16);
                    }
                    txtConnectIpAddress.Text = Current.LoginInfomation.IpAddress;
                    txtConnectPortNo.Text = Current.LoginInfomation.Port.ToString();
                    txtConnectPWD.Text = Current.LoginInfomation.ConnectionPassword;//.Password;
                    txtServerName.Text = Current.LoginInfomation.ConnectionUserName;//.UserName;

                }
            }
            else
            {
                btnWebCam.Enabled = false;
                _showWebCam = true;
                if (!_Parent.IsRoot)
                {
                    ddlSignParent.Text = _Parent.Name;
                    ddlSignParent.SelectedItem = _Parent;
                }
                else
                    ddlSignParent.SelectedIndex = 0;

                string signName = "Sign1";
                int _autoId = 1;

                while (IsSameName(signName))
                {
                    _autoId++;
                    signName = "Sign" + _autoId.ToString();
                }


                txtSignName.Text = signName;
                Current.Name = signName;
                Current.DashboardType = DashboardType.DemoSign;
                ddlSignType.SelectedItem = TemplateGroup.Default.Sign.SignType;
                txtHeight.Text = TemplateGroup.Default.Sign.Height.ToString();
                txtWidth.Text = TemplateGroup.Default.Sign.Width.ToString();
                btSignImage.Text = TemplateGroup.Default.Sign.Image;
                //MessageBus.Subject<GetSignInfoMessage>().Observers += SignForm_Observers;
            }

            if (Current.RefernceCount > 0
                ||Current.Controller.Connection.State == System.Communication.ConnectionState.Opened)
            {
                ddlSignType.Enabled = false;
                ddlTemplate.Enabled = false;
                txtHeight.Enabled = false;
                txtWidth.Enabled = false;
                btnSignDetail.Enabled = false;
                btnUseProxy.Enabled = false;
                txtServerName.Enabled = false;
                txtConnectIpAddress.Enabled = false;
                txtConnectPortNo.Enabled = false;
                txtConnectPWD.Enabled = false;
                txtSignName.Enabled = false;
                rdbPhotograph.Enabled = false;
                rdbWebCam.Enabled = false;
                btnWebCam.Enabled = false;
                this.Text += "--Readonly:"+Current.Name+" has been used.";
            }
            //ddlTemplateSelect = ddlTemplate.SelectedItem as TemplateGroup;
            //Current.Controller.UserManager.GetSignInfoSuccessed += new ProWrite.UFE.ReceivedHandler(UserManager_GetSignInfoSuccessed);
            //Current.Controller.UserManager.GetSignInfoFailed += new ProWrite.UFE.ReceivedHandler(UserManager_GetSignInfoFailed);
            //Current.Controller.Connection.ExceptionFired -= Connection_ExceptionFired;
            //Current.Controller.Connection.ExceptionFired += new EventHandler<EventArgs<Exception>>(Connection_ExceptionFired);

        }

        private bool IsSameName(string name)
        {
            bool result = false;

            foreach (SignInfo item in DashboardItem.AllSigns)
            {
                if (item.Name == name)
                    result = true;
            }
            foreach (SignGroupInfo item in DashboardItem.AllGroups)
            {
                if (item.Name == name)
                    result = true;
            }

            return result;
        }
        void SignForm_Observers(object sender, GetSignInfoMessage msg)
        {
            //var sign = Current;
            //if (sign.Controller.Connection.State == System.Communication.ConnectionState.Opened)
            //{
            //    string signInfo = msg.Resp.GetProperty<string>("Info");
            //    int height = msg.Resp.GetProperty<int>("Hight");
            //    int width = msg.Resp.GetProperty<int>("Width");
            //    SignType signType = EnumHelper.Parse<SignType>(msg.Resp.GetProperty<int>("Type"));

            //    sign.Height = height;
            //    sign.SignInfomation = signInfo + "  :  " + height.ToString() + " x " + width.ToString() + "  :  " + signType.ToString();
            //    sign.Width = width;
            //    sign.Template.Sign.Width = width;
            //    sign.Template.Sign.Height = height;
            //    var message = sign.Template.Message;
            //    message.ImageLayer.Height = message.ImageLayer.FitToSign ? sign.Height : sign.Height / 2;
            //    message.ImageLayer.Width = message.ImageLayer.FitToSign ? sign.Width : sign.Width / 2;
            //    message.VideoLayer.Height = message.VideoLayer.FitToSign ? sign.Height : sign.Height / 2;
            //    message.VideoLayer.Width = message.VideoLayer.FitToSign ? sign.Width : sign.Width / 2;
            //    message.TextLayer.Height = message.TextLayer.FitToSign ? sign.Height : sign.Height / 2;
            //    message.TextLayer.Width = message.TextLayer.FitToSign ? sign.Width : sign.Width / 2;
            //    message.DynamicTextLayer.Height = message.DynamicTextLayer.FitToSign ? sign.Height : sign.Height / 2;
            //    message.DynamicTextLayer.Width = message.DynamicTextLayer.FitToSign ? sign.Width : sign.Width / 2;
            //    sign.Type = signType;
            //}
        }



        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
            ConnectionExceptionAction.IsCancel = true;
            if (!isSaveClose)
            {
                Current.Name = signOld.Name1;
                Current.Parent = signOld.Parent;

            }
            isSaveClose = false;
            //if(!_IsEdit)
            //    MessageBus.Subject<GetSignInfoMessage>().Observers -= SignForm_Observers;
            //Current.Controller.UserManager.GetSignInfoSuccessed -= UserManager_GetSignInfoSuccessed;
            //Current.Controller.UserManager.GetSignInfoFailed -= UserManager_GetSignInfoFailed;
            //Current.Controller.Connection.ExceptionFired -= Connection_ExceptionFired;
            if (Current.Parent == null)
                Current.Parent = _Parent;
        }



        private void BindCombox()
        {
            ddlTemplate.Properties.Items.Clear();
            TemplateGroups groups = DataGate.Project.Templates;
            if (groups != null && groups.Count > 0)
            {
                this.ddlTemplate.Properties.Items.AddRange(groups.ToArray());
                if (_IsEdit)
                {
                    if (Current.TemplateName != null)
                    {
                        for (int i = 0; i < groups.Count; i++)
                        {
                            if (groups[i].Name == Current.TemplateName)
                            {
                                ddlTemplate.SelectedItem = groups[i];
                                CurrentTemplateGroup = groups[i];
                                ddlSignType.SelectedItem = groups[i].Sign.SignType;
                                break;
                            }
                        }
                    }
                    else
                        ddlTemplate.SelectedItem = CurrentTemplateGroup = Current.Template != null ? groups.GetByName(Current.Template.Name) : TemplateGroup.Default;
                }
                else
                {
                    ddlTemplate.SelectedItem = TemplateGroup.Default;
                    CurrentTemplateGroup = TemplateGroup.Default;
                    Current.Template = TemplateGroup.Default.Copy();
                    Current.TemplateName = Current.Template.Name;
                }
            }
        }

        void txtWidth_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((Convert.ToInt32(e.KeyChar)) == 45)
            {
                e.Handled = true;
                return;
            }
            int v = e.KeyChar;
            TextEdit tb = (TextEdit)sender;
            if ((v >= 48 && v < 58) || v == 8)
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }

        private void txtPortNumber_KeyPress(object sender, KeyPressEventArgs e)
        {
            int v = e.KeyChar;
            TextEdit tb = (TextEdit)sender;
            if ((v >= 48 && v <= 59) || v == 8)
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }

        private void txtIpAddressUser_KeyPress(object sender, KeyPressEventArgs e)
        {
            int v = e.KeyChar;
            TextEdit tb = (TextEdit)sender;
            if ((v >= 48 && v <= 59) || v == 46 || v == 8)
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }

        private void ddlProxyType_SelectedIndexChanged(object sender, EventArgs e)
        {
            bool state = ddlProxyType.SelectedIndex != 0;
            SetProxyControlState(state);
            btnTestProxy.Enabled = state;
        }

        private void SetProxyControlState(bool state)
        {
            txtProxyPWD.Enabled = state;
            txtProxyUserName.Enabled = state;
            txtProxyPortNo.Enabled = state;
            txtProxyIpAdd.Enabled = state;
        }
        #endregion

        #region Function

        private void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resource.Helps.DashboardAddSign);
        }

        private bool CheckSignInfo()
        {
            if (txtSignName.Text == null || txtSignName.Text.Trim() == "")
            {
                MsgBox.Warning("Sign name can't be empty");
                return false;
            }
            if (txtHeight.Text == null || txtHeight.Text.Trim() == "")
            {
                MsgBox.Warning("Sign height can't be empty");
                return false;
            }
            if (txtWidth.Text.Trim() == null || txtWidth.Text.Trim() == "")
            {
                MsgBox.Warning("Sign width can't be empty");
                return false;
            }
            if (txtHeight.Text.Trim() == "0")
            {
                MsgBox.Warning("Sorry,the sign height can't be zero");
                return false;
            }
            if (txtWidth.Text.Trim() == "0")
            {
                MsgBox.Warning("Sorry,the sign width can't be zero");
                return false;
            }
            if (Convert.ToInt32(txtHeight.Text.Trim()) < 8
                || Convert.ToInt32(txtHeight.Text.Trim()) > 1000)
            {
                MsgBox.Error("Sorry,the sign height should be in range (8-1000).");
                return false;
            }
            if (Convert.ToInt32(txtWidth.Text.Trim()) < 8
                || Convert.ToInt32(txtWidth.Text.Trim()) > 1000)
            {
                MsgBox.Error("Sorry,the sign width should be in range (8-1000).");
                return false;
            }

            return true;
        }

        private void SetSignTemplateValue()
        {
            Current.Template.Message.ImageLayer.Height = Current.Height / 2;
            Current.Template.Message.ImageLayer.Width = Current.Width / 2;
            Current.Template.Message.VideoLayer.Height = Current.Height / 2;
            Current.Template.Message.VideoLayer.Width = Current.Width / 2;
            Current.Template.Message.TextLayer.Height = Current.Height / 2;
            Current.Template.Message.TextLayer.Width = Current.Width / 2;
            Current.Template.Message.DynamicTextLayer.Height = Current.Height / 2;
            Current.Template.Message.DynamicTextLayer.Width = Current.Width / 2;
        }
        /// <summary>
        /// Save data
        /// </summary>
        protected override void OnSave()
        {
            if (!CheckSignInfo())
                return;

            //判断是否选中了No Group
            Current.Name = txtSignName.Text.Trim();
            //SetTemplate();
            Current.Type = (SignType)Enum.Parse(typeof(SignType), ddlSignType.SelectedItem.ToString());
            Current.Height = Current.Template.Sign.Height = Convert.ToInt32(txtHeight.Text);
            Current.Width = Current.Template.Sign.Width = Convert.ToInt32(txtWidth.Text);
            //SetSignTemplateValue();
            Current.Active = true;
            Current.IsWebCam = rdbWebCam.Checked;
            if (Current.DashboardType != DashboardType.Sign)
                Current.SignInfomation = Current.Height.ToString() + " x " + Current.Width.ToString();
                //Current.SignInfomation = Current.Name + "  :  " + Current.Height.ToString() + " x " + Current.Width.ToString() + "  :  " + Current.Type.ToString();
            Current.Template.Sign.SignType = Current.Type;
            if (isLiveSign)
                Current.DashboardType = DashboardType.Sign;
            else
                Current.DashboardType = DashboardType.DemoSign;



            if (this.ddlSignParent.Text != SelectText)
            {
                //Current.Parent = ddlSignParent.SelectedItem as SignGroupInfo;
                _Parent = ddlSignParent.SelectedItem as SignGroupInfo;
                /////判断被拖入的Group的sign个数是否超过20
                if (SignGroupInfo.IsSignCountValid(_Parent))
                {
                    MsgBox.Warning(Resource.GetString(Resource.Strings.SignsCountMoreThanTwenty));
                    return;
                }
                if (!_Parent.IsSameSignType(Current, _Parent))
                {
                    MsgBox.Warning("Sign information is not equal");
                    return;
                }
            }
            //如果是，则将_Parent置为根
            else
                _Parent = DataGate.Project.RootGroup;

            #region Connection
            /*///////////////////////////////////
             * 
             * 
            */
            if (isLiveSign
                && Current.Controller.Connection.State != System.Communication.ConnectionState.Opened)
            {
                if (!CheckLiveInfo())
                    return;
                btnSave.Enabled = false;
                DoConnect();
                btnSave.Enabled = true;
                //ControlService.SignCombo.Current = Current;

                //LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.NewMessage));
                //LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.NewPlaylist));
                //LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.NewScheduler));
                return;
            }
            /*//////////////////////////
             * 
             * 
             * 
            //////////////////////////*/
            #endregion

            //判断是否添加新项成功
            if (!_Parent.AddSign(Current))
            {
                MsgBox.Error(Resource.GetString(Resource.Strings.DashBoard_SaveSignRepeat));
                return;
            }

            //判断是否需要上传图片
            if (btSignImage.Text.Length > 0)
            {

                //DataGate.Upload(btSignImage.Text);
                UpLoad();
                Current.Image = Current.Template.Sign.Image = strImageFullName;
            }
            DataGate.Update();
            this.IsRefresh = true;
            isSaveClose = true;
            this.Close();

            //LocalMessageBus.Send(this, MenuCommands.NewPlaylist);
            //LocalMessageBus.Send(this, MenuCommands.NewScheduler);

        }

        private void SetTemplate()
        {
            var templateGroup = ddlTemplate.SelectedItem as TemplateGroup;
            if (templateGroup != null)
            {
                Current.TemplateName = templateGroup.Name;
                Current.Template = templateGroup;
            }
        }

        protected override bool OnEdit()
        {
            if (!CheckSignInfo())
                return false;

            if (this.ddlSignParent.Text != SelectText
                && ddlSignParent.Text != Current.ParentName)
            {
                /////判断被拖入的Group的sign个数是否超过20

                if (!SignGroupInfo.IsTwoGroupSameRoot(Current.Parent as SignGroupInfo, ddlSignParent.SelectedItem as SignGroupInfo))
                {
                    var parent = ddlSignParent.SelectedItem as SignGroupInfo;
                    if (SignGroupInfo.IsSignCountValid(parent))
                    {
                        MsgBox.Warning(Resource.GetString(Resource.Strings.SignsCountMoreThanTwenty));
                        return false;
                    }
                   
                }
               
            }
            //如果SignParent选择的是“No Group”，则该Sign的Parent为树根
            if (Current.Name != txtSignName.Text.Trim())
            {
                if (DashboardItem._allSigns.Contains(txtSignName.Text.Trim()) || DashboardItem._allGroups.Contains(txtSignName.Text.Trim()))
                {
                    MsgBox.Error(Resource.GetString(Resource.Strings.DashBoard_SaveSignRepeat));
                    return false;
                }
            }

            #region About Connection
            /*///////////////////////////////////
             * 
             * 
            */
            if (isLiveSign && !_isAddToGroup)
            {
                //this.Enabled = false;
                this.btnSave.Enabled = false;

                if (isConnect)
                {
                    //if (isOnline)
                    //    OnLogoff();
                    //else
                    //    OnDisConncetion();

                    DoDisconnect();
                    this.btnSave.Enabled = true;
                }
                else
                {
                    if (!CheckLiveInfo())
                    {
                        this.btnSave.Enabled = true;
                        return false;
                    }
                    Current.Name = txtSignName.Text.Trim();
                    DoConnect();
                    this.btnSave.Enabled = true;
                }
                //return false;
            }
            /*//////////////////////////
             * 
             * 
             * 
            //////////////////////////*/
            #endregion
            if (!_isAddToGroup)
            {
                if (Current.Controller.Connection.State == System.Communication.ConnectionState.Opened)
                {
                    int h = Current.Height;
                    int w = Current.Width;
                    Current.Height = 10000;
                    Current.Width = 10000;
                    LocalMessageBus.Send(this, new DataChangedMessage(PWDataType.Dashboard));
                    LocalMessageBus.Send(this, new ActiveChange(Current, false));

                    Current.Height = h;
                    Current.Width = w;
                    return true;
                }
                Current.Name = txtSignName.Text.Trim();
                //SetTemplate();
                //SignType
                Current.Type = (SignType)Enum.Parse(typeof(SignType), ddlSignType.SelectedItem.ToString());
                Current.IsWebCam = rdbWebCam.Checked;
                Current.Height = 10000;
                Current.Width = 10000;
                LocalMessageBus.Send(this, new DataChangedMessage(PWDataType.Dashboard));
                LocalMessageBus.Send(this, new ActiveChange(Current, false));
                Current.Height = Current.Template.Sign.Height = Convert.ToInt32(txtHeight.Text);
                Current.Width = Current.Template.Sign.Width = Convert.ToInt32(txtWidth.Text);
                //SetSignTemplateValue();
                Current.Active = true;
                if (Current.DashboardType != DashboardType.Sign)
                    Current.SignInfomation = Current.Height.ToString() + " x " + Current.Width.ToString() ;
                    //Current.SignInfomation = Current.Name + "  :  " + Current.Height.ToString() + " x " + Current.Width.ToString() + "  :  " + Current.Type.ToString();
                Current.Template.Sign.SignType = Current.Type;
                if (btSignImage.Text.Trim() == "")
                    Current.Image = Current.Template.Sign.Image = "";
            }
            if (this.ddlSignParent.Text == SelectText)
                Current.Parent = DataGate.Project.RootGroup;
            else
            {
                var parent = ddlSignParent.SelectedItem as SignGroupInfo;
                if (!parent.IsSameSignType(Current, parent))
                {
                    MsgBox.Warning("Sign information is not equal");
                    return false;
                }
                Current.Parent = ddlSignParent.SelectedItem as SignGroupInfo;
            }
            isSaveClose = true;
            return true;
        }

        /// <summary>
        /// Upload the sign shape
        /// </summary>
        protected override void UpLoad()
        {
            if (btSignImage.Text.Length <= 0 || btSignImage.Text == TemplateGroup.Default.Sign.Image)
                return;
            //string path = AppDomain.CurrentDomain.BaseDirectory;
            string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\";
            //要保存图片的最终路径
            string urlString = path + "Image";
            if (!Directory.Exists(urlString))
            {
                Directory.CreateDirectory(urlString); // File.Create(urlString);
            }
            string[] arrery = Directory.GetFiles(urlString);
            if (strImageFullName == "")
                strImageFullName = btSignImage.Text;
            //判断要上传的图片是否存在，如果存在则不需要再上传
            foreach (string str in arrery)
            {
                if (str.Substring(str.LastIndexOf("\\") + 1) == strImageFullName)
                {
                    Current.Image = Current.Template.Sign.Image = strImageFullName;
                    return;
                }
            }
            DataGate.Upload(btSignImage.Text);
            Current.Image = Current.Template.Sign.Image = strImageFullName;
        }



        #endregion

        #region Event

        private void btSignImage_Click(object sender, EventArgs e)
        {
            openFileDialog.ShowModalDialog();
        }

        private void btnDeleteImage_Click(object sender, EventArgs e)
        {
            //openFileDialog.ShowModalDialog();
            if (MsgBox.Confirm(Resource.GetString(Resource.Strings.ConfirmDeleteImage)) == DialogResult.Yes)
            {
                btSignImage.Text = "";
                Current.Image = "";
                Current.Template.Sign.Image = "";
                btnDeleteImage.Enabled = false;
            }
        }

        private void openFileDialog_FileOk(object sender, CancelEventArgs e)
        {
            btSignImage.Text = openFileDialog.FileName;
            btnDeleteImage.Enabled = true;
            strImageFullName = btSignImage.Text.Substring(btSignImage.Text.LastIndexOf("\\") + 1);
            if (strImageFullName.Contains(".gif")
                || strImageFullName.Contains(".Gif")
                || strImageFullName.Contains(".GIF"))
            {
                strImageFullName = strImageFullName.Substring(0, strImageFullName.IndexOf(".")) + ".jpg";
            }
        }

        private void ddlSignParent_SelectedValueChanged(object sender, EventArgs e)
        {
            if (ddlSignParent.Text != creatGroup)
                return;
            //SignGroupInfo signGroupInfo = new SignGroupInfo();

            //if (_allSigns.Contains(Current))
            //{
            //    signGroupInfo.IsReapet = 2;
            //}
            //else
            //    signGroupInfo.IsReapet = 1;
            SignGroupForm group = new SignGroupForm();
            group.ShowModalDialog();
            if (group.IsRefresh)
            {
                if (group.Current == null)
                    return;
                ddlSignParent.Properties.Items.Add(group.Current);
                this.IsRefresh = true;
                ddlSignParent.SelectedItem = group.Current;
                this.isRefresh = true;
                //_allSigns.Remove(Current);
                //isReapet = true;
                //_IsEdit = true;
                //Current.Parent = group.Current;
            }
            else
            {
                if (_IsEdit)
                {
                    if (_Parent != null && !_Parent.IsRoot)
                        ddlSignParent.SelectedItem = Current.Parent;
                    else
                        ddlSignParent.SelectedIndex = 0;
                }
                else
                {
                    if (!_Parent.IsRoot)
                    {
                        ddlSignParent.Text = _Parent.Name;
                        ddlSignParent.SelectedItem = _Parent;
                    }
                    else
                        ddlSignParent.SelectedIndex = 0;
                }
            }
        }

        private void ddlSignType_SelectedValueChanged(object sender, EventArgs e)
        {
            ddlSignType.Text = ddlSignType.SelectedItem.ToString();
        }

        void btnSSHLogin_Click(object sender, System.EventArgs e)
        {
            SSHLogin ssh = new SSHLogin(Current);
            ssh.ShowModalDialog();
        }
        void btnMoreDetail_Click(object sender, System.EventArgs e)
        {
            TemplateGroup group = this.ddlTemplate.SelectedItem as TemplateGroup;
            if (group != null)
            {
                SettingDialog settingDialog = new SettingDialog();
                settingDialog.HaveParmeter = true;
                SettingDialog.Display(group, this);
                BindCombox();
                if (SettingDialog.CurrentGroup != null)
                {
                    ddlTemplate.SelectedItem = SettingDialog.CurrentGroup;
                    CurrentTemplateGroup = SettingDialog.CurrentGroup;
                    InitDefaultItem(SettingDialog.CurrentGroup);
                }
                else
                {
                    ddlTemplate.SelectedItem = group;
                    CurrentTemplateGroup = group;
                    InitDefaultItem(group);
                }
            }
        }

        void btnAddTemplate_Click(object sender, System.EventArgs e)
        {
            SettingDialog settingDialog = new SettingDialog();
            string name = InputDialog.GetInputValue("New Template");
            if (name != null)
            {
                TemplateGroup group = new TemplateGroup();
                group.Name = name;

                DataGate.Project.Templates.Add(group);
                SettingDialog.Display(group, this);
                BindCombox();
                if (SettingDialog.CurrentGroup != null)
                {
                    ddlTemplate.SelectedItem = SettingDialog.CurrentGroup;
                    CurrentTemplateGroup = SettingDialog.CurrentGroup;
                }
                else
                {
                    ddlTemplate.SelectedItem = group;
                    CurrentTemplateGroup = group;
                }
            }
        }


        void btnSignDetail_Click(object sender, System.EventArgs e)
        {

            SettingDialog settingDialog = new SettingDialog();
            settingDialog.HaveParmeter = true;
            if (Current.Name != txtSignName.Text.Trim())
            {
                if (DashboardItem._allSigns.Contains(txtSignName.Text.Trim())
                    || DashboardItem._allGroups.Contains(txtSignName.Text.Trim()))
                {
                    MsgBox.Error(Resource.GetString(Resource.Strings.DashBoard_SaveSignRepeat));
                    return;
                }
            }
            Current.Name = txtSignName.Text.Trim();
            Current.Type = Current.Template.Sign.SignType
                = (SignType)Enum.Parse(typeof(SignType), ddlSignType.SelectedItem.ToString());
            if (txtHeight.Text.Trim() != "")
                Current.Height = Current.Template.Sign.Height = Convert.ToInt32(txtHeight.Text);
            if (txtWidth.Text.Trim() != "")
                Current.Width = Current.Template.Sign.Width = Convert.ToInt32(txtWidth.Text);
            if (btSignImage.Text.Trim() == "")
            {
                Current.Image = Current.Template.Sign.Image = "";
            }
            else
                Current.Image = Current.Template.Sign.Image = strImageFullName;
            this.Hide();
            SettingDialog.DisplaySign(Current, this);
            this.Show();
            if (Current.DashboardType == DashboardType.Sign
                && Current.Controller.Connection.State == System.Communication.ConnectionState.Opened)
            {
                Current.Template.Sign.Height = Convert.ToInt32(txtHeight.Text);
                Current.Template.Sign.Width = Convert.ToInt32(txtWidth.Text);
            }
            else
            {
                txtHeight.Text = Current.Template.Sign.Height.ToString();
                txtWidth.Text = Current.Template.Sign.Width.ToString();
                Current.Height = 10000;
                Current.Width = 10000;
                LocalMessageBus.Send(this, new DataChangedMessage(PWDataType.Dashboard));
                LocalMessageBus.Send(this, new ActiveChange(Current, false));
                Current.Height = Current.Template.Sign.Height;
                Current.Width = Current.Template.Sign.Width;
                signOld.Height = Current.Template.Sign.Height;
                signOld.Width = Current.Template.Sign.Width;
            }

            btSignImage.Text = Current.Image = strImageFullName = Current.Template.Sign.Image;
            btnDeleteImage.Enabled = !string.IsNullOrEmpty(btSignImage.Text);
            ddlSignType.SelectedItem = Current.Template.Sign.SignType;
            //BindCombox();
            //if (SettingDialog.CurrentGroup != null)
            //{
            //    ddlTemplate.SelectedItem = SettingDialog.CurrentGroup;
            //    InitDefaultItem(SettingDialog.CurrentGroup);
            //}
            //else
            //{
            //    ddlTemplate.SelectedItem = group;
            //    InitDefaultItem(group);
            //}
            //}

        }

        void ddlTemplate_SelectedIndexChanged(object sender, System.EventArgs e)
        {

            if (_isRefresh
                && MsgBox.Confirm(Resources.Resource.GetString(Resources.Resource.Strings.DashboardTemplateChanged)) == DialogResult.No)
            {
                _isRefresh = false;
                ddlTemplate.SelectedItem = CurrentTemplateGroup;
                return;
            }
            TemplateGroup group = this.ddlTemplate.SelectedItem as TemplateGroup;
            if (_isRefresh && group != null)
            {
                InitDefaultItem(group);
                CurrentTemplateGroup = group;
                Current.Template = group;
                Current.TemplateName = Current.Template.Name;
            }

            _isRefresh = true;
        }
        void ddlSignParent_Popup(object sender, System.EventArgs e)
        {
            //txtWidth.Width = 11;
        }

        void ddlTemplate_TextChanged(object sender, System.EventArgs e)
        {
            if (ddlTemplate.Text == "")
            {
                txtHeight.Text = "";
                txtWidth.Text = "";
                ddlSignType.SelectedItem = SignType.RGB;
            }
        }

        private void InitDefaultItem(TemplateGroup group)
        {
            if (group != null)
            {
                txtHeight.Text = group.Sign.Height.ToString();
                txtWidth.Text = group.Sign.Width.ToString();
                ddlSignType.SelectedItem = group.Sign.SignType;
                btSignImage.Text = group.Sign.Image;
                Current.Image = group.Sign.Image;
                strImageFullName = group.Sign.Image;
            }
        }


        void rdbWebCam_CheckedChanged(object sender, System.EventArgs e)
        {
            btnWebCam.Enabled = rdbWebCam.Checked;
            if (_isAddToGroup)
                return;
            if (!_showWebCam)
            {
                _showWebCam = true;
                return;
            }
            this.btSignImage.Enabled = rdbPhotograph.Checked;
            
            btnDeleteImage.Enabled = !string.IsNullOrEmpty(btSignImage.Text);
            if (rdbWebCam.Checked)
            {
                rdbLiveSign.Checked = true;
                btnWebCam.Enabled = true;
                //if(rdbLiveSign.Checked)
                rdbDemoSign.Checked = false;
                ConnectWebCam cam = new ConnectWebCam(Current);
                cam.ShowModalDialog();
            }
        }


        void btnWebCam_Click(object sender, System.EventArgs e)
        {
            if (rdbWebCam.Checked)
            {
                //rdbLiveSign.Checked = true;
                ////if(rdbLiveSign.Checked)
                //rdbDemoSign.Checked = false;
                ConnectWebCam cam = new ConnectWebCam(Current);
                cam.ShowModalDialog();
            }
        }

        void rdbPhotograph_CheckedChanged(object sender, System.EventArgs e)
        {
            this.btSignImage.Enabled = rdbPhotograph.Checked;
            btnDeleteImage.Enabled = !string.IsNullOrEmpty(btSignImage.Text);
        }
        #endregion


        private void rdbDemoSign_CheckedChanged(object sender, EventArgs e)
        {
            if (_isAddToGroup)
                return;
            if (rdbDemoSign.Checked)
            {
                rdbWebCam.Checked = false;
                rdbPhotograph.Checked = true;
            }
            grConncet.Visible = rdbLiveSign.Checked;
            grSign.Visible = !rdbLiveSign.Checked;
            btnSave.Text = "Save";
            btnSave.Width = 67;
            //grConncet.Height = 123;
            this.Height = ClientHeight("1");
            btnSignDetail.Location = new Point(9, BtnSaveHeight(false));
            this.btnSave.Location = new Point(176, BtnSaveHeight(false));
            this.btnCancel.Location = new Point(249, BtnSaveHeight(false));
            isLiveSign = rdbLiveSign.Checked;
        }

        private int BtnSaveHeight(bool isProxy)
        {
            if (isProxy)
                return 483;
            else
                return 356;
        }

        private int ClientHeight(string type)
        {
            if (type == "0")
                return 382;
            else if (type == "1")
                return 416;
            else if (type == "2")//add to group
                return 140;
            else if (type == "3")
                return 542;
            else
                return 382;
        }
    }
}
