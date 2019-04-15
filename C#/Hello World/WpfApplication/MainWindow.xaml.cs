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

        private void dataGrid1_ContextMenuOpening(object sender, ContextMenuEventArgs e)
        {
            var grid = (DataGrid)sender;
            if (grid.ContextMenu != null) return;

            grid.ContextMenu = new ContextMenu();
            foreach (var column in grid.Columns)
            {
                var menuItem = new MenuItem() { Header = column.Header, IsChecked = column.Visibility == Visibility.Visible };
                menuItem.Click += new RoutedEventHandler(menuItem_Click);
                menuItem.Tag = column;
                grid.ContextMenu.Items.Add(menuItem);
            }
        }

        private void menuItem_Click(object sender, RoutedEventArgs e)
        {
            var menuItem = (MenuItem)sender;
            var column = menuItem.Tag as DataGridColumn;
            if (column != null)
            {
                if (menuItem.IsChecked)
                {
                    column.Visibility = Visibility.Hidden;
                    menuItem.IsChecked = false;
                }
                else
                {
                    column.Visibility = Visibility.Visible;
                    menuItem.IsChecked = true;
                }
            }
        }
    }
}
