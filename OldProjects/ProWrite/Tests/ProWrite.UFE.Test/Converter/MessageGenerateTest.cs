using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using ProWrite.DataProviders;
using ProWrite.Entity;
using ProWrite.Entity.Library;
using ProWrite.UFE.Files;
using ProWrite.UFE.Entity;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;
using System.Drawing;
using ProWrite.DES;

namespace ProWrite.UFE.Test.Converter
{
    [TestFixture]
    public class MessageGenerateTest
    {
        ProjectInfo project = null;

        [SetUp]
        public void Init()
        {
            project = new DataProvider().Get();
        }

        [Test]
        public void Test()
        {
            //LocalFilePathMapping.DeleteFiles();
            //* Image
            //One image no effect
            //Generate("Image");
            ////One image include effect
            //Generate("ImageEffect");
            ////One image is background
            //Generate("ImageEffectIsBackGroud");
            ////Many images: some include effects and some no effects
            //Generate("ImageMany");
            //* *

            //**Time
            ////One time no effect
            //Generate("Time");
            //////One time include effect
            //Generate("TimeEffect");
            //////Many Times: some include effects and some no effects
            //Generate("TimeMany");
            // **

            //*Temperature
            ////One time no effect
            //Generate("Temp");
            ////One time include effect
            //Generate("TempEffect");
            ////Many Times: some include effects and some no effects
            //Generate("TempMany");
            // **

            //*ScrollText
            ////One text no effect
            //Generate("ScrollText");
            ////One text include effect
            //Generate("ScrollTextEffect");
            ////Many Texts: some include effects and some no effects
            //Generate("ScrollTextMany");
            // **

            //*Text
            //One text no effect
            //Generate("ShapeText");
            ////One text include effect
            //Generate("ShapeTextEffect");
            ////Many Texts: some include effects and some no effects
            //Generate("ShapeTextMany");
            // **

            //*ShapePaint
            //One shape no effect
            //Generate("Paint");
            ////One shape include effect
            //Generate("PaintEffect");
            ////Many shapes: some include effects and some no effects
            //Generate("PaintMany");
            // **

            //*ShapeVideo
            //One shape no effect
            //Generate("Video");
            ////One shape include effect
            //Generate("VideoEffect");
            ////Many shapes: some include effects and some no effects
            //Generate("VideoMany");
            ////Many shapes: some include effects and some no effects and some is not ShapeVideo
            Generate("VideoOtherMany");
            // **
        }

        private void Generate(string name)
        {
            //MessageInfo
            var msg = project.LibraryGroups[0].Messages.GetByName(name);
            //Sign
            SignInfo sign = new SignInfo();
            sign.Width = 96;
            sign.Height = 32;

            //UfeFileMessageConverter 
            UfeFileMessageConverter converter = new UfeFileMessageConverter();
            converter.Sign = sign;

            //UFE convert message
            converter.Convert(msg);
            //UFE generate message
            converter.Generate();
        }
    }
}
