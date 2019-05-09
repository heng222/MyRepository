using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Media;
using System.ComponentModel;

namespace WpfApplication
{
    class ManulCodeXmalWindow : Window
    {
        public ManulCodeXmalWindow()
        {
            var theBrush = TypeDescriptor.GetConverter(typeof(Brush)).ConvertFromInvariantString("red") as Brush;

            Console.WriteLine("Xmal Window");

            Height = 200;
            Width = 500;

            var grid = new Grid()
            {
                Background = Brushes.Gray
            };
            this.Content = grid;

            var coldef = new ColumnDefinition();
            coldef.Width = new GridLength(100);
            grid.ColumnDefinitions.Add(coldef);
            grid.ColumnDefinitions.Add(new ColumnDefinition());
            grid.ColumnDefinitions.Add(new ColumnDefinition());

            grid.RowDefinitions.Add(new RowDefinition());
            grid.RowDefinitions.Add(new RowDefinition());
            grid.RowDefinitions.Add(new RowDefinition());

            var txtBlock = new TextBlock(new Run("书名：")) { HorizontalAlignment = HorizontalAlignment.Right };
            grid.Children.Add(txtBlock);
            Grid.SetColumn(txtBlock, 0);
            Grid.SetRow(txtBlock, 0);
            txtBlock = new TextBlock(new Run("学习WPF")) { HorizontalAlignment = HorizontalAlignment.Left };
            grid.Children.Add(txtBlock);
            Grid.SetColumn(txtBlock, 1);

            txtBlock = new TextBlock(new Run("类型：")) { HorizontalAlignment = HorizontalAlignment.Right };
            grid.Children.Add(txtBlock);
            Grid.SetColumn(txtBlock, 0);
            Grid.SetRow(txtBlock, 1);
            txtBlock = new TextBlock(new Run("原创书籍")) { HorizontalAlignment = HorizontalAlignment.Left };
            grid.Children.Add(txtBlock);
            Grid.SetColumn(txtBlock, 1);
            Grid.SetRow(txtBlock, 1);

            txtBlock = new TextBlock(new Run("内容：")) { HorizontalAlignment = HorizontalAlignment.Right };
            grid.Children.Add(txtBlock);
            Grid.SetColumn(txtBlock, 0);
            Grid.SetRow(txtBlock, 2);
            txtBlock = new TextBlock(new Run("从集成到应用")) { HorizontalAlignment = HorizontalAlignment.Left };
            grid.Children.Add(txtBlock);
            Grid.SetColumn(txtBlock, 1);
            Grid.SetRow(txtBlock, 2);

        }
    }
}
