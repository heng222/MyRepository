using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Text;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class PrivateFontSample : Form
    {
        public PrivateFontSample()
        {
            InitializeComponent();
        }

        //private void button1_Click(object sender, EventArgs e)
        //{
        //    CreatePrivateFont();
        //}


        private void CreatePrivateFont(PaintEventArgs e)
        {
            PointF pointF = new PointF(10, 0);
            SolidBrush solidBrush = new SolidBrush(Color.Black);

            int count = 0;
            string familyName = "";
            string familyNameAndStyle;
            FontFamily[] fontFamilies;
            PrivateFontCollection privateFontCollection = new PrivateFontCollection();

            // Add three font files to the private collection.

            privateFontCollection.AddFontFile("D:\\Fonts\\ANTQUAB.TTF");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL6CAPBD.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL6HVCAP.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL07BRND.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL7DNLE.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL07DONA.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL7DRCN.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL7HBLCP.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL7HVCAP.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL7MSCP.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL7NVNRW.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL7NVPRP.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL7NVRS.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL8DHLBD.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL8HLVNR.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL11DHVB.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PL11DMSP.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PLFIXED5.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\PLMNNB.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\TLXPICT1.FON");
            privateFontCollection.AddFontFile("D:\\Fonts\\TLXPICT2.FON");

            // Get the array of FontFamily objects.
            fontFamilies = privateFontCollection.Families;

            // How many objects in the fontFamilies array?
            count = fontFamilies.Length;

            // Display the name of each font family in the private collection
            // along with the available styles for that font family.
            for (int j = 0; j < count; ++j)
            {
                // Get the font family name.
                familyName = fontFamilies[j].Name;

                // Is the regular style available?
                if (fontFamilies[j].IsStyleAvailable(FontStyle.Regular))
                {
                    familyNameAndStyle = "";
                    familyNameAndStyle = familyNameAndStyle + familyName;
                    familyNameAndStyle = familyNameAndStyle + " Regular";

                    Font regFont = new Font(
                       familyName,
                       16,
                       FontStyle.Regular,
                       GraphicsUnit.Pixel);

                    e.Graphics.DrawString(
                       familyNameAndStyle,
                       regFont,
                       solidBrush,
                       pointF);

                    pointF.Y += regFont.Height;
                }

                // Is the bold style available?
                if (fontFamilies[j].IsStyleAvailable(FontStyle.Bold))
                {
                    familyNameAndStyle = "";
                    familyNameAndStyle = familyNameAndStyle + familyName;
                    familyNameAndStyle = familyNameAndStyle + " Bold";

                    Font boldFont = new Font(
                       familyName,
                       16,
                       FontStyle.Bold,
                       GraphicsUnit.Pixel);

                    e.Graphics.DrawString(familyNameAndStyle, boldFont, solidBrush, pointF);

                    pointF.Y += boldFont.Height;
                }
                // Is the italic style available?
                if (fontFamilies[j].IsStyleAvailable(FontStyle.Italic))
                {
                    familyNameAndStyle = "";
                    familyNameAndStyle = familyNameAndStyle + familyName;
                    familyNameAndStyle = familyNameAndStyle + " Italic";

                    Font italicFont = new Font(
                       familyName,
                       16,
                       FontStyle.Italic,
                       GraphicsUnit.Pixel);

                    e.Graphics.DrawString(
                       familyNameAndStyle,
                       italicFont,
                       solidBrush,
                       pointF);

                    pointF.Y += italicFont.Height;
                }

                // Is the bold italic style available?
                if (fontFamilies[j].IsStyleAvailable(FontStyle.Italic) &&
                fontFamilies[j].IsStyleAvailable(FontStyle.Bold))
                {
                    familyNameAndStyle = "";
                    familyNameAndStyle = familyNameAndStyle + familyName;
                    familyNameAndStyle = familyNameAndStyle + "BoldItalic";

                    Font italicFont = new Font(
                       familyName,
                       16,
                       FontStyle.Italic | FontStyle.Bold,
                       GraphicsUnit.Pixel);

                    e.Graphics.DrawString(
                       familyNameAndStyle,
                       italicFont,
                       solidBrush,
                       pointF);

                    pointF.Y += italicFont.Height;
                }
                // Is the underline style available?
                if (fontFamilies[j].IsStyleAvailable(FontStyle.Underline))
                {
                    familyNameAndStyle = "";
                    familyNameAndStyle = familyNameAndStyle + familyName;
                    familyNameAndStyle = familyNameAndStyle + " Underline";

                    Font underlineFont = new Font(
                       familyName,
                       16,
                       FontStyle.Underline,
                       GraphicsUnit.Pixel);

                    e.Graphics.DrawString(
                       familyNameAndStyle,
                       underlineFont,
                       solidBrush,
                       pointF);

                    pointF.Y += underlineFont.Height;
                }

                // Is the strikeout style available?
                if (fontFamilies[j].IsStyleAvailable(FontStyle.Strikeout))
                {
                    familyNameAndStyle = "";
                    familyNameAndStyle = familyNameAndStyle + familyName;
                    familyNameAndStyle = familyNameAndStyle + " Strikeout";

                    Font strikeFont = new Font(
                       familyName,
                       16,
                       FontStyle.Strikeout,
                       GraphicsUnit.Pixel);

                    e.Graphics.DrawString(
                       familyNameAndStyle,
                       strikeFont,
                       solidBrush,
                       pointF);

                    pointF.Y += strikeFont.Height;
                }

                // Separate the families with white space.
                pointF.Y += 10;

            } // for
        }

        private void DisplayInstalledFonts(PaintEventArgs e)
        {
            FontFamily fontFamily = new FontFamily("Arial");
            Font font = new Font(
               fontFamily,
               8,
               FontStyle.Regular,
               GraphicsUnit.Point);
            RectangleF rectF = new RectangleF(10, 10, 500, 500);
            SolidBrush solidBrush = new SolidBrush(Color.Black);

            string familyName;
            string familyList = "";
            FontFamily[] fontFamilies;

            InstalledFontCollection installedFontCollection = new InstalledFontCollection();

            // Get the array of FontFamily objects.
            fontFamilies = installedFontCollection.Families;

            // The loop below creates a large string that is a comma-separated
            // list of all font family names.

            int count = fontFamilies.Length;
            for (int j = 0; j < count; ++j)
            {
                familyName = "¡¾" + fontFamilies[j].Name;
                familyList = familyList + familyName;
                familyList = familyList + "¡¿" + ",  ";
            }

            // Draw the large string (list of all families) in a rectangle.
            e.Graphics.DrawString(familyList, font, solidBrush, rectF);
        }

        private void PrivateFontSample_Paint(object sender, PaintEventArgs e)
        {
            DisplayInstalledFonts(e);
        }
    }
}