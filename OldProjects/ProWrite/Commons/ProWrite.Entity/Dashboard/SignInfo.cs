//---------------------------------------------------------------------
//
// File: SignInfo.cs
//
// Description:
// 
//
// Author: Kevin
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
//Modify history:   
//  terry  2008-6-19 修改内容：MergeName中_height和_width的顺序
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Settings;
using ProWrite.Core.Validation;
using ProWrite.UFE;
using System.ComponentModel;
using System.Xml.Serialization;
using ProWrite.UFE.Entity;
using Org.Mentalis.Network.ProxySocket;
using System.Drawing;

namespace ProWrite.Entity.Dashboard
{
    [Serializable]
    public class SignInfo : DashboardItem, ISignInfo, IEquatable<SignInfo>
    {
        public SignInfo()
        {
            //_refernceCount = 0;
        }

        #region Non Serialized Fields
        [NonSerialized]
        private IUFEFrontController _singController;
        [NonSerialized]
        private ConnectionMode _connMode;
        [NonSerialized]
        private LiveInfo _live;
        [NonSerialized]
        public bool HasFireConnectionExceptionEvent;
        //[NonSerialized]
        public int RefernceCount
        {
            get { return _refernceCount; }
            set { _refernceCount = value; }
        }

        public bool IsBlankSign
        {
            get { return _isBlankSign; }
            set { _isBlankSign = value; }
        }
        #endregion

        #region Serialized Fields
        private DashboardType _dashboardType = DashboardType.Sign;
        //private SignType _type;
        private int _width = 200;

        private int _height = 100;
        [NonSerialized]
        private int _refernceCount = 0;
        private bool _isBlankSign = true;
        private string image;
        private string _templateName = "Default";
        private TemplateGroup _template;
        private LoginInfo _loginInfomation;
        #endregion

        public static SignInfo Current { get; set; }

        [Browsable(false)]
        public IUFEFrontController Controller
        {
            get
            {
                if (_singController == null)
                    ConnectionMode = ConnectionMode.Tcp;
                return _singController;
            }
        }

        public ConnectionMode ConnectionMode
        {
            get { return _connMode; }
            set
            {
                if (_connMode != value)
                {
                    if (_singController != null)
                        _singController.Dispose();
                    _connMode = value;
                    switch (value)
                    {
                        //case ConnectionMode.Mock:
                        //    _singController = new UFEFrontController<MockConnection>(this);
                        //    break;
                        case ConnectionMode.Tcp:
                            _singController = new UFEFrontController<TcpUFEConnection>(this);
                            break;
                        case ConnectionMode.RS232:
                            // _singController = new UFEFrontController<RS232Connection>(this);
                            break;
                        case ConnectionMode.Modem:
                            // _singController = new UFEFrontController<ModemConnection>(this);
                            break;
                    }
                }
            }
        }

        public LiveInfo Live
        {
            get
            {
                if (_live == null)
                    _live = new LiveInfo();
                return _live;
            }
        }

       

        public override DashboardType DashboardType
        {
            get { return _dashboardType; }
            set
            {
                if (value != _dashboardType)
                {
                    OnPropertyChanged("DashboardType");
                    _dashboardType = value;
                }
            }
        }

        //public SignType Type
        //{
        //    get { return _type; }
        //    set
        //    {
        //        if (value != _type)
        //        {
        //            OnPropertyChanged("Type");
        //            _type = value;
        //        }
        //    }
        //}

        private string _lastUpdate = "N/A";
        public string LastUpdate
        {
            get { return _lastUpdate; }
            set { _lastUpdate = value; }

        }

        private string _lastUpdateClip = "N/A";
        public string LastUpdateClip
        {
            get { return _lastUpdateClip; }
            set { _lastUpdateClip = value; }
        }

        //[RangeValidator(8, 608)]
        public int Width
        {
            get { return _width; }
            set
            {
                Check.Assert(_width > 0 && _width < 10001, "width > 0 && width < 10001");
                if (value != _width)
                {
                    OnPropertyChanged("Width");
                    _width = value;
                }
            }
        }

        public string TemplateName
        {
            get { return _templateName; }
            set
            {
                if (value != _templateName)
                {
                    OnPropertyChanged("TemplateName");
                    _templateName = value;
                }
            }
        }

        //[NonSerialized]
        public TemplateGroup Template
        {
            get
            {
                if (_template != null)
                    return _template;
                _template = TemplateGroup.Default.Copy();
                return _template;
            }
            set
            {
                if (value != null)
                    _template = value.Copy();
            }
        }

        public Image ImageTest
        {
            get
            {
                try
                {
                    string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\";

                    return IOHelper.GetImageFromFile(path + "Image\\" + Image);
                }
                catch
                { return null; }
            }
        }
        public LoginInfo LoginInfomation
        {
            get { return _loginInfomation ?? new LoginInfo(); }
            set { _loginInfomation = value; }
        }

        //[RangeValidator(8, 608)]
        public int Height
        {
            get { return _height; }
            set
            {
                if (value != _height)
                {
                    Check.Assert(_height > 0 && _height < 10001, "height > 0 && height < 10001");
                    OnPropertyChanged("Height");
                    _height = value;
                }
            }
        }
        private bool _isNew = true;
        public bool IsNew
        {
            get { return _isNew; }
            set { _isNew = value; }
        }
        public string Image
        {
            get { return image; }
            set
            {
                if (value != image)
                {
                    OnPropertyChanged("Image");
                    image = value;
                }
            }
        }

        private string _imageWebCam;
        public string ImageWebCam
        {
            get { return _imageWebCam; }
            set 
            {
                if (value != _imageWebCam)
                {
                    OnPropertyChanged("ImageWebCam");
                    _imageWebCam = value;
                }
            }
        }

        private string _imageCurrentClip;
        public string ImageCurrentClip
        {
            get { return _imageCurrentClip; }
            set
            {
                if (value != _imageCurrentClip)
                {
                    OnPropertyChanged("ImageCurrentClip");
                    _imageCurrentClip = value;
                }
            }
        }


        private System.Drawing.Point _location;
        public System.Drawing.Point Location
        {
            get { return _location; }
            set
            {
                if (value != _location)
                {
                    OnPropertyChanged("Location");
                    _location = value;
                }
            }
        }

        private bool _isWebCam;
        public bool IsWebCam
        {
            get { return _isWebCam; }
            set
            {
                if (value != _isWebCam)
                    _isWebCam = value;
            }
        }

        private string _webCamAddress ="10.10.65.72";
        public string WebCamAddress
        {
            get { return _webCamAddress; }
            set { _webCamAddress = value; }
        }

        private string _webCamPortNum = "";
        public string WebPortNum
        {
            get { return _webCamPortNum; }
            set { _webCamPortNum = value; }
        }

        private string _webCamUserName ="root";
        public string WebCamUserName
        {
            get { return _webCamUserName; }
            set { _webCamUserName = value; }
        }

        private string _webCamPwd ="root";
        public string WebCamPwd
        {
            get { return _webCamPwd; }
            set { _webCamPwd = value; }
        }

        public string SignNameMerge
        {
            get
            {
                if (!string.IsNullOrEmpty(Name))
                {
                    if (Name.Length > 8)
                    {
                        return string.Format("{0} {1} {2} x {3} {4}", Name.Substring(0, 8) + "...", " ", _height, _width, _type);
                    }
                    else
                    {
                        int length = 8 - Name.Length + 3;
                        string empty = "";
                        for (int i = 0; i < length; i++)
                        {
                            empty += " ";
                        }
                        return string.Format("{0} {1} {2} x {3} {4}", Name + empty, " ", _height, _width, _type);
                    }
                }

                return null;
            }
        }

        public override string ToString()
        {
            return SignNameMerge;
        }

        public override bool IsEmpty
        {
            get
            {
                return string.IsNullOrEmpty(SignNameMerge) || _height < 0 || _height > 10000 || _width < 0 || _width > 10000;
            }
        }


        #region IEquatable<SignInfo> Members

        public bool Equals(SignInfo other)
        {
            //Todo: 对照DashboardItem ,type,width,heignt,shape
            if (other == null)
                return false;
            if (_type != other._type)
                return false;
            if (_width != other._width)
                return false;
            if (_height != other._height)
                return false;
            if (image != other.image)
                return false;
            return base.Equals(other);
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as SignInfo);
        }

        #endregion

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }




}