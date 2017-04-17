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
    public class ScheduleConverterTest
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
            //*Schedule
            //One message
            Generate("SheduleMessage");
            //One TimeSliceGroup
            Generate("ScheduleTimeSliceGroup");
            //One Playlist
            Generate("SchedulePlaylist");
            //Many: some Messages and some TimeSliceGroups and some Playlists
            Generate("ScheduleMany");
            //**
        }

        private void Generate(string name)
        {
            //ScheduleInfo
            var item = project.LibraryGroups[0].Schedulers.GetByName(name);

            //Serialiser object
            Serialiser<ScheduleType> _ser = Serialiser<ScheduleType>.Xml;

            //Schedule Converter
            SchedulerConverter converter = new SchedulerConverter();

            //UFE Schedule
            ScheduleType ufeItem = converter.Convert(item);

            //Serialize schedule
            _ser.Serialize(ufeItem, LocalFilePathMapping.GetFile(FileType.Schedule, ufeItem.Id));
        }
    }
}
