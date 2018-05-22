/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 项目名称：经SIL2认证的标准版ATS
//
// 创 建 人：zhangheng
// 创建日期：2015-4-9 16:29:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using Acl.ServiceManagement;
using Platform.Presentation;
using Platform.Presentation.Framework;
using Products.Shell.Properties;

namespace Products.Shell
{
    /// <summary>
    /// 
    /// </summary>
    class SplashScrActivator : Platform.SplashScreen.Activator, IDisposable
    {
        private bool _disposed = false;
        private System.Timers.Timer _timer = new System.Timers.Timer();

        private ISplashScreenManagement _splashScreen;

        private List<Image> _images = new List<Image>();
        private Random _random = new Random(DateTime.Now.Millisecond);

        public SplashScrActivator()
        {
            InitializeImages();
           
            // 获取服务接口
            _splashScreen = ServiceManager.Current.Get<ISplashScreenManagement>();

            // 初始化窗体尺寸。
            var ownerScreen = Screen.AllScreens[0];
            _splashScreen.Size = new Size(ownerScreen.Bounds.Width / 2, ownerScreen.Bounds.Height / 2); 

            // 设置初始图片
            _splashScreen.SetIntroductionImage(_images[0]);
        }

        ~SplashScrActivator()
        {
            this.Dispose(false);
        }

        #region "override methods"
        protected override void OnStart()
        {
            _timer.Interval = 3500;
            _timer.Elapsed += timer_Elapsed;
            _timer.AutoReset = true;
            _timer.Start();
        }

        protected override void OnStop()
        {
        }

        protected override void OnFrameworkStarted()
        {
            if (Workbench.MainForm != null)
            {
                Workbench.MainForm.Shown += new EventHandler(MainForm_Shown);
            }
        }

        protected override void OnFrameworkStop()
        {

        }
        #endregion

        #region "private methods"
        private void InitializeImages()
        {
            _images.Add(Resources.SplashScreen1);
            //_images.Add(Resources.SplashScreen2);
            //_images.Add(Resources.SplashScreen3);
            //_images.Add(Resources.SplashScreen4);
            //_images.Add(Resources.SplashScreen5);
            //_images.Add(Resources.SplashScreen6);
            //_images.Add(Resources.SplashScreen7);
            //_images.Add(Resources.SplashScreen8);
            //_images.Add(Resources.SplashScreen9);
            //_images.Add(Resources.SplashScreen10);
            //_images.Add(Resources.SplashScreen11);
            //_images.Add(Resources.SplashScreen12);
            //_images.Add(Resources.SplashScreen13);
        }

        private void timer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            try
            {
                var index = _random.Next(1, _images.Count);

                _splashScreen.SetIntroductionImage(_images[index]);
            }
            catch (System.Exception /*ex*/)
            {
            }
        }

        private void MainForm_Shown(object sender, EventArgs e)
        {
            if (Workbench.MainForm != null)
            {
                Workbench.MainForm.Shown -= MainForm_Shown;
            }

            if (_timer != null)
            {
                _timer.Stop();
                _timer.Close();
                _timer = null;
            }

            // 框架启动后释放所有图片资源。
            _images.ForEach(p => p.Dispose());
            _images.Clear();
        }
        #endregion

        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    if (_timer != null)
                    {
                        _timer.Close();
                        _timer = null;
                    }
                }
                _disposed = true;
            }
        }

        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }
    }
}
