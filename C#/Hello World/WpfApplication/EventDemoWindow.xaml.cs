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
using System.Windows.Shapes;

namespace WpfApplication
{
    /// <summary>
    /// EventDemoWindow.xaml 的交互逻辑
    /// </summary>
    public partial class EventDemoWindow : Window
    {
        private int _index = 0;

        public EventDemoWindow()
        {
            InitializeComponent();
        }

        private void MakeButton(object sender, RoutedEventArgs e)
        {
            var newBtn = new Button();
            newBtn.Content = string.Format("Button {0}", ++_index);
            newBtn.Click += OnButtonClick;

            root.Children.Add(newBtn);
            DockPanel.SetDock(newBtn, Dock.Bottom);
        }

        void OnButtonClick(object sender, RoutedEventArgs e)
        {
            text1.Text = string.Format("{0} has been clicked!", ((ContentControl)sender).Content);
        }
    }
}
