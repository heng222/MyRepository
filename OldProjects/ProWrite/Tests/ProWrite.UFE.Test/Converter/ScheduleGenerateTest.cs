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
    public class ScheduleGenerateTest
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
            LocalFilePathMapping.DeleteFiles();
            //*Schedule
            //One message
            //Generate("SheduleMessage");
            ////One TimeSliceGroup
            //Generate("ScheduleTimeSliceGroup");
            ////One Playlist
            //Generate("SchedulePlaylist");
            ////Many: some Messages and some TimeSliceGroups and some Playlists
            //Generate("ScheduleMany");
            //**
            Generate("s11111");
        }

        private void Generate(string name)
        {
            //MessageInfo
            var item = project.LibraryGroups[0].Schedulers.GetByName(name);
            //Sign
            SignInfo sign = new SignInfo();
            sign.Width = 200;
            sign.Height = 100;

            //UfeFileScheduleConverter 
            UfeFileScheduleConverter converter = new UfeFileScheduleConverter();
            converter.Sign = sign;

            //UFE convert schedule
            converter.Convert(item);
            //UFE generate schedule
            converter.Generate();
        }
    }
}
