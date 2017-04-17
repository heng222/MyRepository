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

namespace ProWrite.UFE.Test.Converter
{
    [TestFixture]
    public class TimeSliceGroupConverterTest
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
            //*TimeSliceGroup
            //One message no used
            Generate("GroupNoUsed");
            //One message
            Generate("Group");
            //Many messages
            Generate("GroupMany");
            ////Many messages: some be used and some be no used
            Generate("GroupManyNoUsed");
            //**
        }

        private void Generate(string name)
        {
            //TimeSliceGroupInfo
            var item = project.LibraryGroups[0].TimeSliceGroups.GetByName(name);

            //Serialiser object
            Serialiser<TimeSliceGroupType> _ser = Serialiser<TimeSliceGroupType>.Xml;

            //TimeSliceGroup Converter
            TimeSliceGroupConverter converter = new TimeSliceGroupConverter();

            //UFE TimeSliceGroup
            TimeSliceGroupType ufeItem = converter.Convert(item);

            //Serialize timeslicegroup
            _ser.Serialize(ufeItem, LocalFilePathMapping.GetFile(FileType.TimesliceGroup, ufeItem.Id));
        }
    }

    
}
