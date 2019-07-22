using System;
using System.Linq;
using NetAnalyzer.API;
using NetAnalyzer.Core;
using TACS.CommLogParser.Plugin4NetAnalyzer.Controls;
using TACS.CommLogParser.Plugin4NetAnalyzer.Forms;
using TACS.CommLogParser.Plugin4NetAnalyzer.Properties;

namespace TACS.CommLogParser.Plugin4NetAnalyzer
{
    class CommLogParserPlugin : NetAnalyzer.API.ExBase, NetAnalyzer.API.IPlugins
    {
        #region "Field"
        private FormDemo _formDemo = new FormDemo();
        private CtrlProtocolParsed _ctrlProtocolParsed = new CtrlProtocolParsed(Ex.HexEditor);
        #endregion

        #region IPlugins 成员

        public System.Windows.Media.Imaging.BitmapSource Icon
        {
            get { return ExTools.BitmapToBitmapSource(Resources.TACS); }
        }

        public string PluginAuthor { get { return "泰可斯"; } }

        public string PluginDescription { get { return "铁路信号通信协议解析器，支持RSSP-1/RSSP-II，CBTC互联互通，FAO互联互通等协议的解析。"; } }

        public string PluginName { get { return "协议解析"; } }

        public string PluginUrl { get { return "http://www.tacs.com"; } }

        public string Version { get { return "1.0"; } }

        public override void OnInite()
        {
            //Ex.HexShowOutput(true);
            PacketCaptureManager.grdProtocol.SelectionChanged += grdProtocol_SelectionChanged;

            // 
            _formDemo.Controls.Add(_ctrlProtocolParsed);

            //var userCtrl = new UserControlParser();
            //var children = (Ex.HextxtOutput.Parent as System.Windows.Controls.Grid).Children;
            //children.Add(userCtrl);
            //Ex.HextxtOutput.Visibility = System.Windows.Visibility.Hidden;

            base.OnInite();
        }
        #endregion

        #region "Private methods"
        #endregion

        #region "Override methods"
        public override Fluent.Button[] GetPluginsButton()
        {
            var btn = ExTools.CreatRibbonButton("信号协议解析", this.Icon);
            btn.Click += btn_Click;

            return new Fluent.Button[] { btn };
        }

        void btn_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            try
            {
                _formDemo.Show(null);
                // 
            }
            catch (System.Exception ex)
            {
                Ex.Log(ex.ToString());
            }
        }

        void btn_Click2(object sender, System.Windows.RoutedEventArgs e)
        {
            try
            {                
            }
            catch (System.Exception ex)
            {
                Ex.Log(ex.ToString());
            }
        }

        void grdProtocol_SelectionChanged(object sender, EventArgs e)
        {
            if (PacketCaptureManager.CurrSelectedPacket != null)
            {
                _ctrlProtocolParsed.SetUserData(PacketCaptureManager.CurrSelectedPacket);
                //Ex.HextxtOutput.Document.Blocks.Clear();
                //Ex.HextxtOutput.AppendText(string.Join(" ", data.Select(p => string.Format("{0:X2}", p))));
            }
        }
        #endregion

    }
}
