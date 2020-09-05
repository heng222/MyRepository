using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

using Acl.ServiceManagement;

using Platform.Presentation.Framework;

using Products.Shell.Properties;

namespace Products.Shell
{
    /// <summary>
    /// 
    /// </summary>
    [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1001:TypesThatOwnDisposableFieldsShouldBeDisposable")]
    class SplashScreenManager
    {
        private System.Timers.Timer _timer = new System.Timers.Timer();

        private ISplashScreenManagement _splashScreen;

        private List<Image> _images = new List<Image>();
        private Random _random = new Random(DateTime.Now.Millisecond);

        public SplashScreenManager()
        {
            InitializeImages();

            // 创建“初始屏幕”
            _splashScreen = new SplashScreenManagement();

            // 注册服务
            ServiceManager.Current.RegisterInstance(_splashScreen, typeof(ISplashScreenManagement));

            // 初始化窗体尺寸。
            var ownerScreen = Screen.AllScreens[0];
            _splashScreen.Size = new Size(ownerScreen.Bounds.Width / 2, ownerScreen.Bounds.Height / 2);

            // 设置初始图片
            _splashScreen.SetIntroductionImage(_images[0]);
        }

        #region "override methods"
        internal void OpenSplashScreen()
        {
            _splashScreen.OpenSplashScreen();

            if (_images.Count > 1)
            {
                _timer.Interval = 1000;
                _timer.Elapsed += timer_Elapsed;
                _timer.AutoReset = true;
                _timer.Start();
            }
        }

        internal void CloseSplashScreen()
        {
            if (_timer != null)
            {
                var tmpTimer = _timer;
                _timer = null;
                tmpTimer.Close();
            }

            // 关闭闪屏。
            _splashScreen.CloseSplashScreen();

            // 释放所有图片资源。
            _images.ForEach(p => p.Dispose());
            _images.Clear();
        }


        #endregion

        #region "private methods"
        private void InitializeImages()
        {
            _images.Add(Resources.SplashScreen1);
        }

        private void timer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            try
            {
                if (_timer == null) return;

                var index = _random.Next(1, _images.Count);
                _splashScreen.SetIntroductionImage(_images[index]);
            }
            catch (Exception /*ex*/)
            {
            }
        }


        #endregion
    }
}
