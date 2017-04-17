using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using ProWrite.Core;
using ProWrite.UFE.Entity;
using ProWrite.Entity.Dashboard;
using System.Drawing;
using ProWrite.Entity.Library;
using ProWrite.Entity;
using ProWrite.DES;
using log4net;

namespace ProWrite.UFE.Files
{
    public interface IUfeFileLibraryConverter : IConverter, IGenerator
    {
        SignInfo Sign { get; set; }
    }

    public class UfeFileConverter<TLibrary,TUFELibrary, TConverter> : ConverterBase<TLibrary, UfeFile>, IUfeFileLibraryConverter
        where TLibrary:MemoryLibraryItem
        where TConverter:IConverter<TLibrary,TUFELibrary>,new()
        where TUFELibrary:class
    {
        public SignInfo Sign { get; set; }
        protected TLibrary Item;
        protected string LocalPath;
        protected TConverter Converter = new TConverter();
        protected XmlSerialiser<TUFELibrary> _ser = new XmlSerialiser<TUFELibrary>();
        protected UfeFile File;
        private static readonly ILog log = LogManager.GetLogger(typeof(TLibrary));

        public override UfeFile Convert(TLibrary item)
        {
            Item = item;
            LocalPath = LocalFilePathMapping.GetFile(item.Type, item.Id.ToString());

            File = new UfeFile();
            File.Id = item.Id.ToString();
            File.Name = item.Name;
            File.CreateTime = item.CreateTime.ToString();
            File.ModifyTime = item.ModifyTime.ToString();
            File.Length = float.Parse(item.Length.ToString());
            File.FromFilePath = LocalPath;
            File.ToFilePath = FilePathMapping.GetFile(item.Type, item.Id.ToString());
            File.Type = LocalFilePathMapping.ConvertType(item.Type); ;
            return File;
        }


        public virtual void Generate()
        {
            log.Info("Begin Generate.");
            _ser.Serialize(Converter.Convert(Item), LocalPath);
            if (Sign.Controller.Connection.Mode != ProWrite.UFE.ConnectionMode.Tcp)
                File.Content = IOHelper.ReadAllBytes(File.FromFilePath);
            File.Size = IOHelper.GetFileLength(File.FromFilePath);
            log.Info("End Generate.");
        }
    }

    public class UfeFileScheduleConverter : UfeFileConverter<SchedulerInfo,ScheduleType, SchedulerConverter>
    {
        public UfeFileScheduleConverter()
        {
            XmlSerializerNamespaces ns = new XmlSerializerNamespaces();
            ns.Add("xsi", "http://www.w3.org/2001/XMLSchema-instance" );
            ns.Add("xsd", "http://www.w3.org/2001/XMLSchema");
            ns.Add("tns", "http://xml.netbeans.org/schema/ProWriteSchedule");
            _ser.Namespaces = ns;
        }
    }

    public class UfeFilePlaylistConverter : UfeFileConverter<PlaylistInfo, PlaylistType, PlaylistConverter>
    {
        public UfeFilePlaylistConverter()
        {
            XmlSerializerNamespaces ns = new XmlSerializerNamespaces();
            ns.Add("xsi", "http://www.w3.org/2001/XMLSchema-instance");
            ns.Add("xsd", "http://www.w3.org/2001/XMLSchema");
            ns.Add("tnp", "http://xml.netbeans.org/schema/ProWritePlaylist");
            _ser.Namespaces = ns;
        }
    }

    public class UfeFileTimeSliceGroupConverter : UfeFileConverter<TimeSliceGroupInfo, TimeSliceGroupType, TimeSliceGroupConverter>
    {
        public UfeFileTimeSliceGroupConverter()
        {
            XmlSerializerNamespaces ns = new XmlSerializerNamespaces();
            ns.Add("xsi", "http://www.w3.org/2001/XMLSchema-instance");
            ns.Add("xsd", "http://www.w3.org/2001/XMLSchema");
            ns.Add("tnt", "http://xml.netbeans.org/schema/ProWriteTimeSliceGroup");
            _ser.Namespaces = ns;
        }
    }

    public class UfeFileMessageConverter : ConverterBase<MessageInfo, List<UfeFile>>, IUfeFileLibraryConverter
    {
        private MessageConverter _messageConverter = new MessageConverter();
        private List<UfeFile> _files = new List<UfeFile>();
        public SignInfo Sign { get; set; }
        private MessageInfo _item;
        private FrameObjectType _message;
        private XmlSerialiser<FrameObjectType> _ser = new XmlSerialiser<FrameObjectType>();
        private IVideoGenerator _videoGenerator = new VideoGenerator();
        private static readonly ILog log = LogManager.GetLogger(typeof(UfeFileMessageConverter));

        public UfeFileMessageConverter()
        {
            XmlSerializerNamespaces ns = new XmlSerializerNamespaces();
            ns.Add("xsi", "http://www.w3.org/2001/XMLSchema-instance");
            ns.Add("xsd", "http://www.w3.org/2001/XMLSchema");
            ns.Add("tnf", "http://xml.netbeans.org/schema/ProWriteFrameObject");
            _ser.Namespaces = ns;
        }

        public override List<UfeFile> Convert(MessageInfo item)
        {
            _files.Clear();

            _item = VideoInspector.Instance.Convert(new KeyValuePair<SignInfo, MessageInfo>(Sign, item));
            //_item = item.CreateMessage(Sign, _videoGenerator); 

            _messageConverter.Sign = Sign;
            _message =_messageConverter.Convert(_item);
            _files.Add(_messageConverter.File);
            _files.Add(_messageConverter.NailImageFile);

            if (_messageConverter.Shapes != null && _messageConverter.Shapes.Count > 0)
            {
                foreach (ShapePair pair in _messageConverter.Shapes)
                {
                    pair.Sign = Sign;
                    pair.File.ToFilePath = string.Format(pair.File.ToFilePath, _item.Id);
                    _files.Add(pair.File);
                }
            }
            return _files;
        }

        public void Generate()
        {
            //TODO: Generate FrameObjectType.File
            log.Debug("Begin Message Generate.");
            _ser.Serialize(_message, _messageConverter.File.FromFilePath);
            if (Sign.Controller.Connection.Mode != ProWrite.UFE.ConnectionMode.Tcp)
                _messageConverter.File.Content = IOHelper.ReadAllBytes(_messageConverter.File.FromFilePath);
            _messageConverter.File.Size = IOHelper.GetFileLength(_messageConverter.File.FromFilePath);
            log.Debug("End Message Generate.");

            log.Debug("Begin All Shapes Generate.");
            foreach (var item in _messageConverter.Shapes)
                item.Generate();
            log.Debug("Begin All Shapes Generate.");
        }

    }
}
