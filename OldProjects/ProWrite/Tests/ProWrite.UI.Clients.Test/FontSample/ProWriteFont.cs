using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public enum ProWriteFontType
    {
        //PL6CAPBD = 0,
        //PL6HVCAP = 1,
        //PL07BRND = 2,
        //PL7DNLE = 3,
        //PL07DONA = 4,
        //PL7DRCN = 5,
        //PL7HBLCP = 6,
        //PL7HVCAP = 7,
        //PL7MSCP = 8,
        //PL7NVNRW = 9,
        //PL7NVPRP = 10,
        //PL7NVRS = 11,
        //PL8DHLBD = 12,
        //PL8HLVNR = 13,
        //PL11DHVB = 14,
        //PL11DMSP = 15,
        //PLFIXED5 = 16,
        //PLMNNB = 17,
        //TLXPICT1 = 18,
        //TLXPICT2 = 19
        Private,
        Public
    }

    

    public partial class ProWriteFont : Form
    {
        private const int FontCount = 20;
        string[] PrivateFonts = new string[]
            {
                "PL 05 Helv Mono Numbers",
                "PL 06 CAPS BOLD",
                "PL 06 Helv CAPS",
                "PL 07 Bernard",
                "PL 07 Caps Monospaced",
                "PL 07 Danielle",
                "PL 07 Donna",
                "PL 07 Draconian",
                "PL 07 Helv Bold Caps",
                "PL 07 Helvetica CAPS",
                "PL 07 Sans",
                "PL 07 Sans FIxed Width",
                "PL 07 Sans Narrow",
                "PL 08 Helv Narrow",
                "PL 08d Helv Bold",
                "PL 11D Helv Bold",
                "PL 11D MonoSpaced",
                "PL Fixed 05 Helv CPS",
                "Trans-Lux Pictorials",
                "Trans-Lux Large Pictorials",
            };
        List<string> ListPrivateFonts = new List<string>();
        List<string> ListAllFonts = new List<string>();
            


        public ProWriteFont()
        {
            InitializeComponent();
            Init();
        }

        private void Init()
        {
            InitPrivateFonts();
            InitAllFonts();
            InitFontType();
            //LoadFont(ProWriteFontType.Public);
        }

        private void InitFontType()
        {
            cbxFontType.Items.Clear();
            cbxFontType.Items.AddRange(new string[] { "Private", "Public" });
            cbxFontType.SelectedIndex = 0;
        }

        private void InitPrivateFonts()
        {
            //FontFamily family;
            for (int i = 0; i < PrivateFonts.Length; i++)
            {
                //family = new FontFamily("Fixedsys");
                //family = new FontFamily(PrivateFonts[i]);
                ListPrivateFonts.Add(PrivateFonts[i]);
            }
            ListPrivateFonts.Sort();     
        }

        private void InitAllFonts()
        {
            string[] familyArray = new string[ListPrivateFonts.Count + FontFamily.Families.Length];
            
            ListPrivateFonts.CopyTo(familyArray);
            //FontFamily.Families.CopyTo(familyArray,20);
            Array.ConvertAll<FontFamily, string>(FontFamily.Families, delegate(FontFamily item) { return item.Name; }).CopyTo(familyArray,20);
            ListAllFonts.AddRange(familyArray);

            ListAllFonts.Sort();            
        }

        private void LoadFont(ProWriteFontType loadType)
        {
            cbxFont.Items.Clear();
            if (loadType == ProWriteFontType.Private)
                cbxFont.Items.AddRange(ListPrivateFonts.ToArray());
            else
                cbxFont.Items.AddRange(ListAllFonts.ToArray());
        }

        private void cbxFontType_SelectedIndexChanged(object sender, EventArgs e)
        {
            //LoadFont(Enum.Parse(typeof(ProWriteFontType),cbxFontType.SelectedText) as ProWriteFontType);
            LoadFont((ProWriteFontType)(Enum.Parse(typeof(ProWriteFontType), cbxFontType.Items[cbxFontType.SelectedIndex].ToString())));
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            byte oldFont = lblDisplayContent.Font.GdiCharSet;
            Font font = new Font(cbxFont.Items[cbxFont.SelectedIndex].ToString(), float.Parse(tbFontSize.Text), FontStyle.Regular, GraphicsUnit.Pixel, oldFont);

            bool b = Fonts.IsSymbolFont(font);
            //font = new Font(
            //font.ToLogFont(
            lblDisplayContent.Font = new Font(cbxFont.Items[cbxFont.SelectedIndex].ToString(), float.Parse(tbFontSize.Text), FontStyle.Regular, GraphicsUnit.Pixel, oldFont);

            //lblDisplayContent
            //lblDisplayContent.Font.FontFamily.Name = cbxFont.SelectedText;
            //lblDisplayContent.Font.Size = float.Parse(tbFontSize.Text);
        }
    }
}