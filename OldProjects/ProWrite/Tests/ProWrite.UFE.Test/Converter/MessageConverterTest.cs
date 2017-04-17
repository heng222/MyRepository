//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using NUnit.Framework;
//using ProWrite.DataProviders;
//using ProWrite.Entity;
//using ProWrite.Entity.Library;
//using ProWrite.UFE.Files;
//using ProWrite.UFE.Entity;
//using ProWrite.Core;
//using ProWrite.Entity.Dashboard;
//using System.Drawing;
//using ProWrite.DES;

//namespace ProWrite.UFE.Test.Converter
//{
//    [TestFixture]
//    public class MessageConverterTest
//    {
//        ProjectInfo project = null;

//        [SetUp]
//        public void Init()
//        {
//            project = new DataProvider().Get();
//        }

//        [Test]
//        public void Test()
//        {
//            //LocalFilePathMapping.DeleteFiles();
//            //* Image
//            //One image no effect
//            //Generate("Image");
//            ////One image include effect
//            //Generate("ImageEffect");
//            ////One image is background
//            //Generate("ImageEffectIsBackGroud");
//            ////Many images: some include effects and some no effects
//            //Generate("ImageMany");
//             //* *

//            //**Time
//            ////One time no effect
//            //Generate("Time");
//            //////One time include effect
//            //Generate("TimeEffect");
//            //////Many Times: some include effects and some no effects
//            //Generate("TimeMany");
//            // **

//            //*Temperature
//            ////One time no effect
//            //Generate("Temp");
//            ////One time include effect
//            //Generate("TempEffect");
//            ////Many Times: some include effects and some no effects
//            //Generate("TempMany");
//            // **

//            //*ScrollText
//            ////One text no effect
//            //Generate("ScrollText");
//            ////One text include effect
//            //Generate("ScrollTextEffect");
//            ////Many Texts: some include effects and some no effects
//            //Generate("ScrollTextMany");
//            // **

//            //*Text
//            //One text no effect
//            //Generate("ShapeText");
//            ////One text include effect
//            //Generate("ShapeTextEffect");
//            ////Many Texts: some include effects and some no effects
//            //Generate("ShapeTextMany");
//            // **

//            //*ShapePaint
//            //One shape no effect
//            //Generate("Paint");
//            ////One shape include effect
//            //Generate("PaintEffect");
//            ////Many shapes: some include effects and some no effects
//            //Generate("PaintMany");
//            // **
//        }

//        private void Generate(string name)
//        {
//            //Video Interface
//            IVideoGenerator _videoGenerator = new VideoGenerator();
//            //MessageInfo
//            var msg = project.LibraryGroups[0].Messages.GetByName(name);
//            //Sign
//            SignInfo sign = new SignInfo();
//            sign.Width = 200;
//            sign.Height = 100;
//            //New MessageInfo
//            msg = msg.CreateMessage(new Size(sign.Width, sign.Height), _videoGenerator);

//            //Serialiser object
//            Serialiser<FrameObjectType> _ser = Serialiser<FrameObjectType>.Xml;

//            //Message Converter
//            MessageConverter converter = new MessageConverter();
//            converter.Sign = sign;

//            //UFE message
//            FrameObjectType ufeMsg = converter.Convert(msg);

//            //Serialize message
//            _ser.Serialize(ufeMsg, LocalFilePathMapping.GetFile(FileType.Message, ufeMsg.Id));
//        }        
//    }
//}
