//---------------------------------------------------------------------
//
// File: TabControlBase.cs
//
// Description:
//      MessageSave Form
//
// Author: Jerry Xu
// Date  : 2008-10-22
//
//Modify History:
//      Jerry Xu 2009-2-12 Update methods:MessageSaveForm(LibraryType libraryType)
//      Jerry Xu 2009-3-19 Update event:txtModelName_KeyUp(object sender, KeyEventArgs e)
//      Jerry Xu 2009-3-19 Update method:Check()
//      Jerry Xu 2009-3-23 Update method:OnSave()
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Core;
using ProWrite.Resources;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls
{
    public partial class MessageSaveForm : XtraForm, ISupportGlobalization
    {
        private LibraryType _libraryType = LibraryType.Message;
        private bool _keyFlag = true;
        //private string _caption;
        public MessageSaveForm(LibraryType libraryType)
        {
            InitializeComponent();
            if (!DesignMode)
            {
                InitializeResource();
                Image image = null;
                try
                {
                    System.IO.MemoryStream mStream = new System.IO.MemoryStream();

                    if (libraryType == LibraryType.Message)
                        image = Resources.Resource.GetImage(Resources.Resource.Images.MessageIcon16x16);// Resource.GetIcon(Resource.Icons.Message);
                    if (libraryType == LibraryType.Playlist)
                        image = Resources.Resource.GetImage(Resources.Resource.Images.PlaylistIcon16x16);// Resource.GetIcon(Resource.Icons.Message);
                    if (libraryType == LibraryType.Schedule)
                        image = Resources.Resource.GetImage(Resources.Resource.Images.SchedulerIcon16x16);// Resource.GetIcon(Resource.Icons.Message);

                    image.Save(mStream, System.Drawing.Imaging.ImageFormat.Jpeg);
                    this.Icon = Icon.FromHandle(new Bitmap(mStream).GetHicon());
                    mStream.Close();
                }
                catch
                { }

                this.Text = libraryType.ToString() + " " + "Save"; //Resource.GetString(Resource.Strings.Save).ToLower();
                lblTitle.Text = Resource.GetFormatString(Resource.Strings.InputName, libraryType.ToString());
                _libraryType = libraryType;
                Init();
            }
        }

        #region Properties define
        private string _modelName = string.Empty;
        public string ModelName
        {
            get { return _modelName; }
            set { _modelName = value; }
        }

        private bool _isUpdate = false;
        public bool IsUpdate
        {
            get { return _isUpdate; }
            set { _isUpdate = value; }
        }
        #endregion


        #region Functions define
        #region Init
        /// <summary>
        /// Function:Init playlistssave control info
        /// Author: Jerry Xu
        /// Date:2008-7-9
        /// </summary>
        private void Init()
        {
            
        }
        #endregion

        #region Check
        /// <summary>
        /// Function:Check the inputed data
        /// Author: Jerry Xu
        /// Date:2008-7-9
        /// </summary>
        /// <returns>bool</returns>
        private bool Check()
        {
            //Validate the item name
            txtModelName.Text = txtModelName.Text.Trim();
            _keyFlag = false;
            if (txtModelName.Text == string.Empty)
            {
                MsgBox.Warning(Resource.GetString(Resource.Strings.NameEmpty));
                txtModelName.Focus();                
                return false;
            }
            if (txtModelName.Text.Length > 30)
            {
                MsgBox.Warning(Resource.GetString(Resource.Strings.NameLengthLimit));
                txtModelName.Focus();                
                return false;
            }
            //if (!Resource.CheckName(txtModelName.Text))
            //{
            //    MsgBox.Warning(Resource.GetFormatString(Resource.Strings.NameError, txtModelName.Text));
            //    txtModelName.Focus();
            //    return false;
            //}
            _keyFlag = true;
            return true;
        }

        #endregion

        private void OnCancel()
        {
            _modelName = string.Empty;
            this.Close();
        }

        #region Save         
        /// <summary>
        /// Function:Save 
        /// Author: Jerry Xu
        /// Date:2008-7-13
        /// </summary>
        /// <returns></returns>
        private void OnSave()
        {
            try
            {
                //Check the input value
                if (Check())
                {
                    _modelName = txtModelName.Text;
                    if (LibraryGroup.Current.Contains(_modelName, _libraryType))
                    {
                        if (MsgBox.Warning(Resource.GetFormatString(Resource.Strings.LibrarySaveFormNameExists, new object[] { _libraryType.ToString().ToLower(), _modelName }),Resource.GetString(Resource.Strings.SaveAs),MessageBoxButtons.YesNo) == DialogResult.Yes)
                        {
                            _isUpdate = true;
                            _keyFlag = false;
                            this.Close();
                        }
                        else
                        {
                            _isUpdate = false;
                            _keyFlag = false;
                            _modelName = string.Empty;
                            txtModelName.Focus();
                            return;
                        }
                        return;
                    }
                    else
                    {
                        _isUpdate = false;
                        this.Close();
                    }
                }
                    
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupEditFormSaveException), ex);
            }
        }
        #endregion

        #region ISupportGlobalization Members
        private bool _isSupportGlobalization;

        /// <summary>
        /// Get or set whether it support internationalization function
        /// </summary>
        public bool IsSupportGlobalization
        {
            get
            {
                return _isSupportGlobalization;
            }
            set
            {
                _isSupportGlobalization = value;
            }
        }

        /// <summary>
        /// Initialize resource information
        /// </summary>
        public void InitializeResource()
        {
            sbtnSave.Text = Resource.GetString(Resource.Strings.Save);
            sbtnCancel.Text = Resource.GetString(Resource.Strings.Cancel);
            sbtnSave.Image = Resource.GetImage(Resource.Images.Save16);
            sbtnCancel.Image = Resource.GetImage(Resource.Images.Cancel16);
        }

        /// <summary>
        /// Refresh the resource if it support internationalization ,otherwise don't refresh
        /// </summary>
        public void RefreshResource()
        {
            if (IsSupportGlobalization)
                InitializeResource();
        }
        #endregion //ISupportGlobalization Members
        #endregion

        private void sbtnSave_Click(object sender, EventArgs e)
        {
            OnSave();
        }

        private void sbtnCancel_Click(object sender, EventArgs e)
        {
            OnCancel();
        }

        private void txtModelName_KeyUp(object sender, KeyEventArgs e)
        {            
            if (e.KeyCode == Keys.Enter)
            {
                if (_keyFlag)
                    OnSave();
                else
                    _keyFlag = true;

            }
            if (e.KeyCode == Keys.Escape)
            {
                OnCancel();
            }
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);

        }

        private void txtModelName_KeyPress(object sender, KeyPressEventArgs e)
        {
            //txtModelName.
            //if(txtModelName.Text.Length>64)

        }
    }
}
