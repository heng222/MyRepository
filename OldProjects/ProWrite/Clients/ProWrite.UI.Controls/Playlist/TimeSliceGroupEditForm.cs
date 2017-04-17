//---------------------------------------------------------------------
//
// File: TimeSliceGroupEditForm.cs
//
// Description:
// RibbonForm Control of TimeSliceGroupEditForm 
//
// Author: Jerry Xu
//
// DateTime:2008-7-9
//
// Modify history:
//      Jerry Xu 2008-7-9  Add resources and ISupportGlobalization
//      Jerry Xu 2008-7-13 Add the function:Save time slice group
//      Jerry Xu 2008-7-24 Delete IsEmpty in if
//      Jerry Xu 2009-2-5  Update method:Save()
//      Jerry Xu 2009-2-26 Update method:Save()
//      Jerry Xu 2009-3-20 Update method:InitializeResource()
//      Jerry Xu 2009-3-26 Update method:TimeSliceGroupEditForm(string name)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using DevExpress.XtraEditors.Controls;
using DevExpress.XtraBars.Ribbon;
using ProWrite.Core;
using ProWrite.Entity.Library;
using ProWrite.Resources;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Playlist
{
    /// <summary>
    /// Time slice group edit form.
    /// </summary>
    public partial class TimeSliceGroupEditForm : XtraForm, ISupportGlobalization
    {
        #region Variant define
        #endregion

        public TimeSliceGroupEditForm(string name)
        {
            InitializeComponent();
            if (!DesignMode)
            {
                _groupName = name;
                InitializeResource();
                Init();
            }
        }

        #region Properties define
        //private bool _isEdit = false;
        //public bool IsEdit 
        //{
        //    get { return _isEdit; }
        //    set { _isEdit = value; }
        //}
        private string _groupName = string.Empty;
        public string GroupName
        {
            get { return _groupName; }
            set { _groupName = value; }
        }

        private int _grouplength = 0;
        public int GroupLength
        {
            get { return _grouplength; }
            set { _grouplength = value; }
        }

        private bool _isRefresh = false;
        public bool IsRefresh
        {
            get { return _isRefresh; }
            set { _isRefresh = value; }
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
            teLength.Properties.Mask.EditMask = "f0";
            teLength.Properties.MaxValue = int.MaxValue;
            teLength.Properties.MinValue = 1;
            teLength.Properties.NullText = "1";
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
            //Validate the playlistname,the playlistname must not null
            if (teName.Text.Trim() == string.Empty)
            {
                MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupEditFormNameEmpty));
                teName.Focus();
                return false;
            }
            //Validate the playlistname,the playlistname must not null
            if (teLength.Text == "0")
            {
                MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupEditFormLengthZero));
                teLength.Focus();
                return false;
            }

            //if (!Resource.CheckName(teName.Text))
            //{
            //    MsgBox.Warning(Resource.GetFormatString(Resource.Strings.NameError, teName.Text));
            //    teName.Focus();
            //    return false;
            //}
            return true;
        }
        #endregion
        #region Load time slice group info
        /// <summary>
        /// Function:Load time slice group info
        /// Author: Jerry Xu
        /// Date:2008-7-9
        /// </summary>
        /// <param name="pGroupName">TimeSliceGroupInfo Name</param>
        private void LoadGroupInfo(string pGroupName)
        {
            TimeSliceGroupInfo group = LibraryGroup.Current.TimeSliceGroups.GetByName(pGroupName);
            if (group != null)
            {
                teName.Text = group.Name;
                _grouplength = group.Length;
                teLength.Text = group.Length.ToString(); // Common.Helper.ConvertTimeToLengthText(group.Length, Constance.TrackBar.Tick);
                rgIsRandom.EditValue = group.IsRandom;
                group = null;
            }
        }
        #endregion
        #region Save time slice group
        /// <summary>
        /// Function:Save time slice group
        /// Author: Jerry Xu
        /// Date:2008-7-13
        /// </summary>
        /// <returns></returns>
        private void Save()
        {
            try
            {
                //Check the input value
                if (Check())
                {
                    TimeSliceGroupInfo group;
                    if (_groupName!=string.Empty)
                    {
                        //Update a exist time slice group info
                        if (teName.Text.Trim() != _groupName)
                        {
                            if (LibraryGroup.Current.TimeSliceGroups.GetByName(teName.Text.Trim())!=null)
                            {
                                MsgBox.Error(Resource.GetFormatString(Resource.Strings.NameAlreadyExist,"time slice group",teName.Text.Trim()));
                                teName.Focus();
                                return;
                            }
                        }
                        group = LibraryGroup.Current.TimeSliceGroups.GetByName(_groupName);
                        _groupName = teName.Text.Trim();
                        _grouplength = int.Parse(teLength.Text);
                        group.Name = _groupName;
                        group.Length = int.Parse(teLength.Text); //ProWrite.UI.Controls.Common.Helper.ConvertTimeToSecond(teLength.Text);
                        group.IsRandom = (bool)(rgIsRandom.EditValue);
                        group.ModifyTime = DateTime.Now;
                        ControlService.LibraryTree.Update(group);
                    }
                    else
                    {
                        //Add a new time slice group info
                        group = LibraryGroup.Current.TimeSliceGroups.GetByName(teName.Text.Trim());
                        if (group != null)
                        {
                            MsgBox.Error(Resource.GetFormatString(Resource.Strings.NameAlreadyExist, "time slice group", teName.Text.Trim()));
                            teName.Focus();
                            return;
                        }
                        group = new TimeSliceGroupInfo();
                        _groupName = teName.Text.Trim();
                        group.Name = _groupName;
                        group.Length = int.Parse(teLength.Text);// ProWrite.UI.Controls.Common.Helper.ConvertTimeToSecond(teLength.Text);
                        group.IsRandom = (bool)(rgIsRandom.EditValue);
                        group.CreateTime = DateTime.Now;
                        ControlService.LibraryTree.Add(group);
                    }
                    group = null;
                    MsgBox.Information("Time Slice Group was " + Resource.GetString(Resource.Strings.Savesuccess));
                    //Refresh the TimeSliceGroupControl 
                    this.Close(); 
                    _isRefresh = true;                    
                }
                else
                {
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
            //Init is random group
            //RadioGroupItem item;
            //item = new RadioGroupItem(true,Resource.GetString(Resource.Strings.OptionButtonTextYes));
            //rgIsRandom.Properties.Items.Add(item);
            //item = new RadioGroupItem(false, Resource.GetString(Resource.Strings.OptionButtonTextNo));
            //rgIsRandom.Properties.Items.Add(item);
            //rgIsRandom.EditValue = item;
            
            //item = null;       
            if (string.IsNullOrEmpty(_groupName))
                this.Text = Resource.GetString(Resource.Strings.TimesliceGroupEditFormTitleAdd);
            else
                this.Text = Resource.GetString(Resource.Strings.TimesliceGroupEditFormTitleEdit);

            lcName.Text = Resource.GetString(Resource.Strings.PlayListTimeSliceGroupEditFormNameTitle);
            lcLength.Text = Resource.GetString(Resource.Strings.PlayListTimeSliceGroupEditFormLengthTitle);
            lcIsRandom.Text = Resource.GetString(Resource.Strings.PlayListTimeSliceGroupEditFormRandomTitle);
            //teLength.Properties.Mask.EditMask = Resource.GetString(Resource.Strings.PlayListTimeSliceGroupEditFormTimeFormat);

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

        #region Events define
        private void sbtnSave_Click(object sender, EventArgs e)
        {
            try
            {
                //if (_playlistInfo != null)
                Save();                
            }
            catch
            {
            }
        }
        private void sbtnCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            this.Close();
        }

        private void TimeSliceGroupEditForm_Load(object sender, EventArgs e)
        {
            //Load time slice group info
            if (_groupName != string.Empty)
            {
                LoadGroupInfo(_groupName);
            }
        }
        #endregion
    }
}