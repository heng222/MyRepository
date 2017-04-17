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
    public class PlaylistConverterTest
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
            //*Playlist
            //One message
            Generate("PlaylistMessage");
            //One TimeSliceGroup
            Generate("PlaylistTimeSliceGroup");
            //One Playlist
            Generate("Playlist");
            //Many library items
            Generate("PlaylistMany");
            //**
        }

        private void Generate(string name)
        {
            //PlaylistInfo
            var item = project.LibraryGroups[0].Playlists.GetByName(name);

            //Serialiser object
            Serialiser<PlaylistType> _ser = Serialiser<PlaylistType>.Xml;

            //Playlist Converter
            PlaylistConverter converter = new PlaylistConverter();

            //UFE Playlist
            PlaylistType ufeItem = converter.Convert(item);

            //Serialize playlist
            _ser.Serialize(ufeItem, LocalFilePathMapping.GetFile(FileType.Playlist, ufeItem.Id));
        }
    }
}
