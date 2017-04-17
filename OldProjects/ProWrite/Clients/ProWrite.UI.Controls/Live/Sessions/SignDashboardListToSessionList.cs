//---------------------------------------------------------------------
//
// File: SignDashboardListToSessionList.cs
//
// Description:
// SignDashboardListToSessionList UserControl 
//
// Author: Jerry
// Date  : 2009-7-23
//
// Modify history:
//      
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Live;
using ProWrite.UI.Controls.Common;

using DevExpress.XtraEditors;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class SignDashboardListToSessionList : UserControl
    {
        LiveSign _liveSign = new LiveSign();
        SessionInfo _session = null;
        public SignDashboardListToSessionList()
        {
            InitializeComponent();
            //Init();
            //if(!DesignMode)
            //    New();
        }

        public List<LiveSign> SignListItems
        {
            get {
                return SaveSignList();
            }
        }

        public void LoadSession()
        {
            lbcSession.Items.Clear();
            lbcDashboard.Items.Clear();

            if (SessionInfo.Current != null)
                _session = SessionInfo.Current;

            LiveSign[] signs = SessionInfo.Current.SignItems;

            lbcDashboard.Items.AddRange(SignGroupInfo.AllSigns);
            lbcDashboard.Items.AddRange(SignGroupInfo.AllGroups);

            int count = 0;

            for (int dbItemIndex = 0; dbItemIndex < lbcDashboard.Items.Count; dbItemIndex++)
            {
                for (int i = 0; i < signs.Length; i++)
                {
                    DashboardItem dbItem = lbcDashboard.Items[dbItemIndex] as DashboardItem;
                    LiveSign signItem = signs[i] as LiveSign;

                    if (dbItem.Id == signs[i].Id)
                    {
                        lbcSession.Items.Add(dbItem);
                        lbcDashboard.Items.RemoveAt(dbItemIndex);
                        dbItemIndex--;
                        count++;
                        break;
                    }
                }

                if (count == signs.Length - 1)
                {
                    break;
                }
            }
        }

        private void lbcDashboard_DoubleClick(object sender, EventArgs e)
        {
            Add();
        }

        private List<LiveSign> SaveSignList()
        {
            List<LiveSign> listLiveSign = new List<LiveSign>();
            List<DashboardItem> list = new List<DashboardItem>();

            for (int i = 0; i < lbcSession.Items.Count; i++)
            {
                list.Add(lbcSession.Items[i] as DashboardItem);
            }

            listLiveSign.AddRange(list.ConvertAll<LiveSign>(p =>
            {
                return new LiveSign() { Id = p.Id };
            }));
            return listLiveSign;
        }

        public void New()
        {
            lbcSession.Items.Clear();
            lbcDashboard.Items.Clear();
            lbcDashboard.Items.AddRange(SignGroupInfo.AllSigns);
            lbcDashboard.Items.AddRange(SignGroupInfo.AllGroups);

            if (SessionInfo.Current != null)
                _session = SessionInfo.Current;
        }

        private void Add()
        {
            if (lbcDashboard.SelectedItems == null)
                return;

            DashboardItem dashboard;
            DashboardItem session = null;
            bool isContain = false;
            for (int i = 0; i < lbcDashboard.SelectedItems.Count; i++)
            {
                isContain = false;
                if (lbcSession.ItemCount > 0)
                    session = lbcSession.Items[0] as DashboardItem;
                dashboard = lbcDashboard.SelectedItems[i] as DashboardItem;
                for (int j = 0; j < lbcSession.Items.Count; j++)
                {
                    session = lbcSession.Items[j] as DashboardItem;
                    if (dashboard.Name == session.Name)
                        isContain = true;

                    if (!isContain && dashboard.DashboardType == ProWrite.Core.DashboardType.Group)
                    {

                        if (session.DashboardType == ProWrite.Core.DashboardType.Group)
                        {
                            foreach (SignGroupInfo item in SignGroupInfo.FindAllGroups(dashboard as SignGroupInfo))
                            {
                                if (item.Name == session.Name)
                                {
                                    MsgBox.Error("The group '" + item.Name + "' has contained the group '" + session.Name + "'");
                                    isContain = true;
                                }
                            }
                            if (!isContain)
                            {
                                foreach (SignGroupInfo item in SignGroupInfo.FindAllGroups(session as SignGroupInfo))
                                {
                                    if (item.Name == dashboard.Name)
                                    {
                                        MsgBox.Error("The group '" + session.Name + "' has contained the group '" + item.Name + "'");
                                        isContain = true;
                                    }
                                }
                            }
                        }
                        else
                        {
                            foreach (SignInfo item in SignGroupInfo.FindAllSigns(dashboard as SignGroupInfo))
                            {
                                if (item.Name == session.Name)
                                {
                                    MsgBox.Error("The group '" + item.Name + "' has contained the sign '" + session.Name + "'");
                                    isContain = true;
                                }
                            }
                        }
                    }
                    else if (!isContain)
                    {
                        if (session.DashboardType == ProWrite.Core.DashboardType.Group)
                        {
                            foreach (SignInfo item in SignGroupInfo.FindAllSigns(session as SignGroupInfo))
                            {
                                if (item.Name == dashboard.Name)
                                {
                                    MsgBox.Error("The group '" + session.Name + "' has contained the sign '" + item.Name + "'");
                                    isContain = true;
                                }
                            }
                        }
                    }
                }

                if (!isContain)
                {
                    lbcSession.Items.Add(lbcDashboard.SelectedItems[i]);
                    lbcSession.SelectedIndex = lbcSession.ItemCount - 1;
                    lbcDashboard.Items.Remove(lbcDashboard.SelectedItems[i]);
                }
            }
        }

        private void Remove()
        {
            if (lbcSession.SelectedItem == null)
                return;
            for (int i = lbcSession.SelectedItems.Count - 1; i >= 0; i--)
            {
                lbcDashboard.Items.Add(lbcSession.SelectedItems[i]);
                lbcSession.Items.Remove(lbcSession.SelectedItems[i]);
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            Add();
        }

        private void lbcSession_DoubleClick(object sender, EventArgs e)
        {
            Remove();
        }

        private void btnRemove_Click(object sender, EventArgs e)
        {
            Remove();
        }

        private void btnUp_Click(object sender, EventArgs e)
        {
            int index = 0;
            object item1 = null;
            if (lbcSession.SelectedItems != null)
            {
                for (int i = 0; i < lbcSession.SelectedItems.Count; i++)
                {
                    if (lbcSession.SelectedItems[i] != lbcSession.Items[0])
                    {
                        index = lbcSession.Items.IndexOf(lbcSession.SelectedItems[i]);

                        item1 = lbcSession.Items[index];
                        lbcSession.Items.Remove(item1);
                    }
                }
                if (item1 != null)
                {
                    lbcSession.Items.Insert(index - 1, item1);
                    lbcSession.SelectedIndex = index - 1;
                }
            }
        }

        private void btnDown_Click(object sender, EventArgs e)
        {
            int index = 0;
            object item1 = null;
            if (lbcSession.SelectedItems != null)
            {
                for (int i = 0; i < lbcSession.SelectedItems.Count; i++)
                {
                    if (lbcSession.SelectedItems[i] != lbcSession.Items[lbcSession.Items.Count - 1])
                    {
                        index = lbcSession.Items.IndexOf(lbcSession.SelectedItems[i]);

                        item1 = lbcSession.Items[index];
                        lbcSession.Items.Remove(item1);
                    }
                }
                if (item1 != null)
                {
                    lbcSession.Items.Insert(index + 1, item1);
                    lbcSession.SelectedIndex = index + 1;
                }
            }
        }

        private void lbcDashboard_SelectedIndexChanged(object sender, EventArgs e)
        {
            btnAdd.Enabled = lbcDashboard.SelectedItem != null;
        }

        private void lbcSession_SelectedIndexChanged(object sender, EventArgs e)
        {
            btnRemove.Enabled = lbcSession.SelectedItem != null;
            btnUp.Enabled = lbcSession.SelectedIndex != 0;
            btnDown.Enabled = lbcSession.SelectedIndex != lbcSession.ItemCount - 1;
        }

        public DashboardItem[] SignList
        {
            get
            {
                DashboardItem[] items = null;

                if (lbcSession.Items.Count > 0)
                {
                    items = new DashboardItem[lbcSession.Items.Count];

                    for (int i = 0; i < lbcSession.Items.Count; i++)
                        items[i] = lbcSession.Items[i] as DashboardItem;
                }

                return items;
            }
        }

    }
}
