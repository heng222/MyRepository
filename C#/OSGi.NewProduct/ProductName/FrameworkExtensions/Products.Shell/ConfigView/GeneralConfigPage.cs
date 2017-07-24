using System.Windows.Forms;
using Platform.Presentation;
using Platform.Presentation.Options;
using Products.Presentation;

namespace Products.Shell.ConfigView
{
    /// <summary>
    /// ����ȫ������ҳ��
    /// </summary>
    [Option(name: ConfigNodeNames.Environment.General, title: "����")]
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

        #region IOptionView ��Ա
        /// <summary>
        /// 
        /// </summary>
        public Control View 
        {
            get { return this; } 
        }
        /// <summary>
        /// ��ʼ������
        /// </summary>
        private void Initialize()
        {
            nudOptInterval.Value = Workbench.OptimizeInterval / 60;
        }
        /// <summary>
        /// Ӧ�ý����������޸�
        /// </summary>
        public void ApplyChanges()
        {
            Workbench.OptimizeInterval = (int)nudOptInterval.Value * 60;
        }
        #endregion
    }
}
