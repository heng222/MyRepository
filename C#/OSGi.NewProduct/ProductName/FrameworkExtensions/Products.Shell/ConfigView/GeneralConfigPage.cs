using System.Windows.Forms;
using Platform.Presentation;
using Platform.Presentation.Options;
using Products.Presentation;

namespace Products.Shell.ConfigView
{
    /// <summary>
    /// 程序全局设置页面
    /// </summary>
    [Option(name: ConfigNodeNames.Environment.General, title: "常规")]
    public partial class GeneralConfigPage : UserControl, IOptionControl
    {
        /// <summary>
        /// 
        /// </summary>
        public GeneralConfigPage()
        {
            InitializeComponent();

            Initialize();
        }

        #region IOptionView 成员
        /// <summary>
        /// 
        /// </summary>
        public Control View 
        {
            get { return this; } 
        }
        /// <summary>
        /// 初始化界面
        /// </summary>
        private void Initialize()
        {
            nudOptInterval.Value = Workbench.OptimizeInterval / 60;
        }
        /// <summary>
        /// 应用界面所做的修改
        /// </summary>
        public void ApplyChanges()
        {
            Workbench.OptimizeInterval = (int)nudOptInterval.Value * 60;
        }
        #endregion
    }
}
