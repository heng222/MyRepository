using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Windows.Markup;

namespace WpfApplication
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void OnBtnCloseClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void OnBtnXamlReaderClick(object sender, RoutedEventArgs e)
        {
            try
            {
                this.Title = "动态加载XAML文档实例";

                using (var fs = new FileStream("XmlReaderDemo.xaml", FileMode.Open))
                {
                    var rootElement = (DependencyObject)XamlReader.Load(fs);
                    this.Content = rootElement;

                    var btn = LogicalTreeHelper.FindLogicalNode(rootElement, "b1") as Button;
                    btn.Click += btn_Click;
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        void btn_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("此按钮来自一个单独的XAML文件");
        }

        private void OnNoXamlDemoClick(object sender, RoutedEventArgs e)
        {
            this.Title = "没有XAML文件的WPF实例";

            var wnd = new ManulCodeXmalWindow();
            wnd.Show();
        }

        private void OnEventDemoClick(object sender, RoutedEventArgs e)
        {
            this.Title = "WPF事件演示";

            var window = new EventDemoWindow();
            window.Show();
        }

    }
}
