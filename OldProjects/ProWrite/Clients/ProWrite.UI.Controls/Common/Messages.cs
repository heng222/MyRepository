using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.Entity.Dashboard;
using System.Drawing;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls.Common
{
    public class PropertySetMessage : PWMessage
    {
        public MenuCommands Command;
        public string PropertyName;
        public object PropertyValue;
    }

    /// <summary>
    /// 系统数据类型
    /// </summary>
    public enum PWDataType
    {
        Dashboard,
        Libray,
        PlayList,
        Video
    }

    /// <summary>
    /// 系统数据改变消息
    /// </summary>
    public class DataChangedMessage : PWMessage
    {
        /// <summary>
        /// 系统数据类型
        /// </summary>
        public readonly PWDataType DataType;
        public DataChangedMessage(PWDataType type)
        {
            DataType = type;
        }
    }

    /// <summary>
    /// 菜单消息
    /// </summary>
    public class MenuMessage : PWMessage
    {
        /// <summary>
        /// 命令
        /// </summary>
        public readonly MenuCommand[] Commands;

        public MenuMessage(MenuCommands command, bool enabled)
        {
            Commands = new MenuCommand[] { new MenuCommand(command, enabled) };
        }

        public MenuMessage(params MenuCommand[] commands)
        {
            Commands = commands;
        }
    }

    public enum ItemVisibility
    {
        Always = 0,
        Never = 1,
        OnlyInCustomizing = 2,
        OnlyInRuntime = 3,
    }

    public class MenuCommand
    {
        public MenuCommands Command { get; set; }
        public bool? Enabled { get; set; }
        public ItemVisibility? Visibility { get; set; }
        public string Caption { get; set; }
        public string PropertyName { get; set; }
        public object PropertyValue { get; set; }

        public object Tag { get; set; }

        public MenuCommand() { }

        public MenuCommand(MenuCommands command, bool? enabled)
        {
            Command = command;
            Enabled = enabled;
        }
    }

    /// <summary>
    /// 当TreeList的当前选中Sign改变后，Current Sign的选择项也应相应改变
    /// </summary>
    public class SelectedSignMessage : PWMessage
    {
        public readonly SignInfo CurrentSign;
        public SelectedSignMessage(SignInfo currentSign)
        {
            CurrentSign = currentSign;
        }
    }

    public class EditImage : PWMessage
    {
        //public readonly Image CurrentImage;
        public ShapeImage CurrentShapImage;
        public EditImage(ShapeImage currentImage)
        {
            CurrentShapImage = currentImage;
        }
    }

    public class IsSelectShapImage : PWMessage
    {
        public readonly bool BIsSelectShapImage;
        public IsSelectShapImage(bool bIsSelectShapImage)
        {
            BIsSelectShapImage = bIsSelectShapImage;
        }
    }

    /// <summary>
    /// 当TreeList的当前选中Sign改变后，Current Sign的选择项也应相应改变
    /// </summary>
    public class SetPWLogo : PWMessage
    {
        public readonly string LogoColor;
        public SetPWLogo(string logoColor)
        {
            LogoColor = logoColor;
        }
    }

    /// <summary>
    /// 当treeList中Sign的Active值改变后，Current Sign的项也应相应改变
    /// </summary>
    public class ActiveChange : PWMessage
    {
        public readonly SignInfo CurrentSign;
        public readonly bool IsSelect;
        public ActiveChange(SignInfo sign, bool isSelect)
        {
            CurrentSign = sign;
            IsSelect = isSelect;
        }
    }

    /// <summary>
    /// 双击Current Image，修改Current sign 图片
    /// </summary>
    public class DoubleClickCurrentImage : PWMessage
    {
        public readonly SignInfo CurrentSign;
        public DoubleClickCurrentImage(SignInfo sign)
        {
            CurrentSign = sign;
        }
    }

    public class ChangeConnectState : PWMessage
    {
        public readonly bool IsConnect;
        public readonly bool IsShow;
        public ChangeConnectState(bool isConnect, bool isShow)
        {
            IsConnect = isConnect;
            IsShow = isShow;
        }
    }
    /// <summary>
    /// InitSystemData
    /// </summary>
    public class InitSystemData : PWMessage
    {
        public InitSystemData()
        {
        }
    }

    public class SetDefaultDrawingIcon : PWMessage
    {
        public SetDefaultDrawingIcon()
        {
        }
    }

    public class LoginSuccessMessage : PWMessage
    {
    }
}
