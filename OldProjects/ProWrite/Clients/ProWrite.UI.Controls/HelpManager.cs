using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Configuration;
using ProWrite.Resources;
using System.Diagnostics;

namespace ProWrite.UI.Controls
{
    public static class HelpManager
    {
        private static HelpProvider provider = new HelpProvider();
        private static string helpFile;

        static HelpManager()
        {
            helpFile = ConfigurationManager.AppSettings["HelpFile"];
            if (string.IsNullOrEmpty(helpFile))
            {
#if DEBUG
            	helpFile = Resources.Resource.GetHelpString(Resources.Resource.Helps.HelpFileName);
#else
                helpFile = Resources.Resource.GetHelpString(Resources.Resource.Helps.HelpFileNameRelease);

#endif
                }

            provider.HelpNamespace = helpFile;
        }

        
        public static void SetShowHelp(this Control control, HelpNavigator navigator, string helpfilePath)
        {
            //provider = new HelpProvider { HelpNamespace = helpFile };
            provider.SetShowHelp(control, true);
            provider.SetHelpNavigator(control, navigator);
            provider.SetHelpKeyword(control, Resource.GetHelpString(helpfilePath));
        }

        public static void SetRibbonShowHelp(this Control control, HelpNavigator navigator, string helpfilePath)
        {
            Help.ShowHelp(control, helpFile, navigator, Resource.GetHelpString(helpfilePath));
        }

        public static void SendEmail(string address, string subject, string body)
        {
            if (string.IsNullOrEmpty(address))
                address = "registration@tlxcommercial.com";
            if (string.IsNullOrEmpty(subject))
                subject = "Subject";
            Process.Start("mailto:" + address + "?Subject=" + subject + "&body=" + body);
        }

        public static void ResetShowHelp(this Control control)
        {
            provider.ResetShowHelp(control);
        }

        public static void Dispose()
        {
            if (provider != null)
                provider.Dispose();
            provider = null;
        }

    }
}
