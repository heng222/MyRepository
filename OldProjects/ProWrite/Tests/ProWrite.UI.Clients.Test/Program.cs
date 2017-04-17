using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using ProWrite.Core;
using ProWrite.UI.Clients.Test.FontSample;
using ProWrite.UI.Controls.Editor;

namespace ProWrite.UI.Clients.Test
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

			//Louis: test TextEffectForm
			//TextEffect textEffect = new TextEffect();
			//textEffect.EffectColor = Color.Black;
			//textEffect.Effect = OutlineShadowType.None;

			//Application.Run(new TextEffectForm(null));
			//Application.Run(new MyControlsTestForm());

			// ZhangHeng: test frame
            //Application.Run(new CreateVideoMessage());
            Application.Run(new frmCLIForm());

			//Application.Run(new frmButtonBackColor());

	        //Application.Run(new LibraryControlsTest());

			//Application.Run(new PlayerPanelTest());

            //Application.Run(new CreateVideoMessage());

            //Application.Run(new FrmLayerName());

            //SerializeTest.Test();
            //SerializeTest.TemplateTest();
            //Application.Run(new FrmWorkerThreadTest());

            //DelegateManager.Default.Dispose();
            //Application.Run(new FrmHelpTest());

            //Application.Run(new FrmImageTest());
		}
    }
}
