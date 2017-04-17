//---------------------------------------------------------------------
//
// File: DashboardModule.cs
//
// Description:
// Implements my Class. 
//
// Author: terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
//Modify history:   
// Terry  2008-6-19 修改内容：代码注释，国际化
// Terry  2008-6-26 代码国际化 
// Terry  2008-7-1  修改openFileDialog_FileOk方法
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls;
using System.IO;
using System.Reflection;
using ProWrite.Core;
using ProWrite.Entity.Settings;
using DevExpress.XtraEditors;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using System.Communication.Messaging;
using System.Communication;
using ProWrite.UFE;
using ProWrite.UI.Controls.Actions;
using ProWrite.Resources;
using DevExpress.LookAndFeel;

namespace ProWrite.UI.Controls.Modules
{
	/// <summary>
	/// 
	/// </summary>
    [PWModule(ModuleNames.Dashboard, IsDefault=true)]
	public partial class DashboardModule : ModuleControl
        //ControlBase
	{
		SignInfo signInsertPhoto;
		//private SignCombo _signCombo;
		public DashboardModule()
        {
            

            InitializeComponent();
            RegisterDockPanel(dockPanelSignImage, ControlService.SignImage, Docks.SignImage);
            RegisterDockPanel(dockPanelCurrentClip, ControlService.CurrentClip, Docks.CurrentClip);
            //DataGate.Log.Debug("RegisterDockPanel SignStatus.");
            //RegisterDockPanel(dockPanelSignStatus, ControlService.SignStatus, Docks.SignStatus);
            //DataGate.Log.Debug("RegisterDockPanel SignStorageIndicator.");
            //RegisterDockPanel(dockPanelSignStorageIndicator, ControlService.SignStorageIndicator, Docks.SignIndicator);
            RegisterHelp();

            ControlService.DashboardTree = dashboardTree1;

        }

        public override Dictionary<Docks, string> DockMap
        {
            get
            {
                return ProWrite.UI.Controls.DockMap.Dashboard;
            }
        }

        protected override DevExpress.XtraBars.Docking.DockManager DockManager
        {
            get
            {
                return this.dockManager1;
            }
        }

		protected override void Delete()
		{
            if (dashboardTree1.FocusedNode == null 
                || dashboardTree1.FocusedNode.Tag == null)
                return;
            DashboardItem item = (dashboardTree1.FocusedNode.Tag) as DashboardItem;
            string confirm = "";
            if (item.DashboardType == DashboardType.Sign)
                confirm = Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteSign);
            else
                confirm = Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteGroup);
            if (MsgBox.Confirm(confirm) == DialogResult.No)
            {
                return;
            }
            //if (MsgBox.Confirm(Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteItem)) != DialogResult.Yes)
            //    return;
			dashboardTree1.Delete();
		}

		protected override void New()
		{
			dashboardTree1.ShowSignEditor(DashboardType.Sign);
		}

        private new void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resource.Helps.Dashboard);
        }

	    /// <summary>
		/// 初始化资源
		/// </summary>
		public override void InitializeResource()
		{
			base.InitializeResource();
            if (ControlService.SignCombo.Current == null)
                SetPicImageNull();
            else
            {
                ControlService.SignImage.RefreshImage();
                ControlService.CurrentClip.RefreshClip();
            }
		}

		protected override void InitModule()
		{
			base.InitModule();
			ControlService.SignCombo.EditValueChanged += new System.EventHandler(this.ddlCurrentSign_SelectedIndexChanged);
			InitializeResource();

			//接收消息，当treeList选中节点改变后，Current Sign也随即改变
			LocalMessageBus.Subject<SelectedSignMessage>().Observers += new ObserverHandler<SelectedSignMessage>(DashboardTree_Observers);
			//接收消息，判断Active改变后
			LocalMessageBus.Subject<ActiveChange>().Observers += new ObserverHandler<ActiveChange>(DashboardModule_Observers);
			//接收菜单消息，判断当前点击的菜单项，以便相应不同的事件
			LocalMessageBus.Subject<DoubleClickCurrentImage>().Observers +=new ObserverHandler<DoubleClickCurrentImage>(DashboardTree_ObserversDoubleClick);

		}

		/// <summary>
		/// 当Current Sign改变后，相应改变图片的显示内容
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="msg"></param>
		void DashboardModule_Observers(object sender, ActiveChange msg)
		{
			if (msg.IsSelect)
			{
				try
				{
					if(msg.CurrentSign.Active)
						ControlService.SignCombo.SelectedItem = msg.CurrentSign;
				}
				catch
				{
					//ControlService.SignCombo.SelectedIndex = 0;
				}
				CurrentSignChanged();
			}
			else
			{
				//如果CurrentSign没有数据，则将图片置空
				if (ControlService.SignCombo.Items.Length <= 0)
				{
					SetPicImageNull();
				}
				else
				{
					//当编辑了Sign之后，当前Current Sign应该定位到该Sign，并显示其图片
                    if (msg.CurrentSign != null
                        &&msg.CurrentSign.Active)
                    {
                        ControlService.SignCombo.SelectedItem = msg.CurrentSign;
                        CurrentSignChanged();
                    }
                    else if(ControlService.SignCombo.Current!=null)
                    {
                        CurrentSignChanged();
                    }
				}
			}
		}

		/// <summary>
		/// 双击Current Sign当前选中的Sign，
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="msg"></param>
		void DashboardTree_ObserversDoubleClick(object sender, DoubleClickCurrentImage msg)
		{
			if (msg != null)
			{
				signInsertPhoto = msg.CurrentSign;
				ControlService.SignImage.SignInsertPhoto = signInsertPhoto;
				openFileDialog.ShowModalDialog();
				LocalMessageBus.Send(this, new ActiveChange(msg.CurrentSign,false));
				//EditDashboardItem(new SignForm(msg.CurrentSign), msg.CurrentSign as DashboardItem);
			}
		}
		/// <summary>
		/// treeList选中Sign改变后，Current Sign也随即改变
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="msg"></param>
		void DashboardTree_Observers(object sender, SelectedSignMessage msg)
		{
			if (sender != this)
			{
				try
				{
					if (msg.CurrentSign.Active)
					{
						ControlService.SignCombo.SelectedItem = msg.CurrentSign;
                        ControlService.SignCombo.NullText = msg.CurrentSign.ToString();
                        if (msg.CurrentSign.IsNew)
                        {
                            msg.CurrentSign.IsNew = false;
                            //LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.NewMessage));
                            //LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.NewPlaylist));
                            //LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.NewScheduler));
                        }
						CurrentSignChanged();
                        SignInfo sign = msg.CurrentSign;
                        var action = new SelectedSignAction(sign);
                        action.Perform();
					}
					else
					{
						//ControlService.SignCombo.
						ControlService.SignCombo.SelectedItem = null;
						//ControlService.SignCombo. = null;
					}
				}
				catch
				{
					SetPicImageNull();
				}
			}
		}

		/// <summary>
		/// Module Name
		/// </summary>
		public override string ModuleName
		{
			get { return ModuleNames.Dashboard; }
		}

		/// <summary>
		/// ddlCurrentSign改变后的事件
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void ddlCurrentSign_SelectedIndexChanged(object sender, EventArgs e)
		{
            LocalMessageBus.Send(this, new SelectedSignMessage((sender as LookUpEdit).EditValue as SignInfo));
			CurrentSignChanged();
		}

		/// <summary>
		/// Current Sign改变后的事件
		/// </summary>
		private void CurrentSignChanged()
		{

			ControlService.SignImage.RefreshImage();
            ControlService.CurrentClip.RefreshClip();
            ControlService.CurrentClip.RefreshStatus();
			#region old code
			//try
			//{
			//    string strImage = ControlService.SignCombo.Current.Image;
			//    if (string.IsNullOrEmpty(strImage))
			//    {
			//        if (ControlService.SignCombo.Current.Template == null)
			//        {
			//            SetPicImageNull();
			//            return;
			//        }
			//        strImage = ControlService.SignCombo.Current.Template.Sign.Image;

			//    }
			//    //获取当前程序运行目录，以便加载相关图片
			//    string assemblyFile = Assembly.GetExecutingAssembly().Location;
			//    string asssemblyPath = Path.GetDirectoryName(assemblyFile);
			//    string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\";
			//    this.picLiveView.Image = IOHelper.GetImageFromFile(path + "Image\\" + strImage);
			//    //this.picCurrent.Image = Resources.Resource.SignPhotoView;
			//    // updated to get shape using resource key by Louis
			//    this.picCurrent.Image = IOHelper.GetImageFromFile(path + "Image\\" + TemplateGroup.Default.Sign.Image); //Resources.Resource.GetImage(Resources.Resource.Images.Default);
			//    if (ControlService.SignCombo.SignName == null)
			//    {
			//        SetPicImageNull();
			//    }
			//}
			//catch
			//{
			//    SetPicImageNull();
			//}
			#endregion
		}

		/// <summary>
		/// 设置PicLiveView和picCurrent的初始图片
		/// </summary>
		private void SetPicImageNull()
		{
			ControlService.SignImage.SetPicImageNull();
            ControlService.SignImage.SetWebCamNull();
            ControlService.CurrentClip.SetPicImageNull();
			//string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\";
			//this.picLiveView.Image = IOHelper.GetImageFromFile(path + "Image\\" + TemplateGroup.Default.Sign.Image);
			//this.picCurrent.Image = IOHelper.GetImageFromFile(path + "Image\\" + TemplateGroup.Default.Sign.Image);
		}

		private void openFileDialog_FileOk(object sender, CancelEventArgs e)
		{
			string strImageFullName = openFileDialog.FileName;
			strImageFullName = strImageFullName.Substring(strImageFullName.LastIndexOf("\\") + 1);
			SignInfo sign = ControlService.SignCombo.Current;
			if (sign == null)
			{
				if (signInsertPhoto == null)
					return;
				sign = signInsertPhoto;
			}
			string path = AppDomain.CurrentDomain.BaseDirectory;
			////要保存图片的最终路径
			string urlString = path + "Image";
			if (!Directory.Exists(urlString))
			{
				Directory.CreateDirectory(urlString);// File.Create(urlString);
			}
			string[] arrery = Directory.GetFiles(urlString);
			///判断要上传的图片是否存在，如果存在则不需要再上传
			foreach (string str in arrery)
			{
				if (str.Substring(str.LastIndexOf("\\") + 1) == strImageFullName)
				{
                    if (strImageFullName.Contains(".gif")
                || strImageFullName.Contains(".Gif")
                || strImageFullName.Contains(".GIF"))
                    {
                        strImageFullName = strImageFullName.Substring(0, strImageFullName.IndexOf(".")) + ".jpg";
                    }
					sign.Image = strImageFullName;
					return;
				}
			}
            
			DataGate.Upload(strImageFullName);
            
			sign.Image = strImageFullName;
		}
	}
}