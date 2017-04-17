//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using ProWrite.Core;
//using System.Xml.Serialization;

//namespace ProWrite.Entity.Library
//{
//    [Serializable]
//    public class TemplateInfo:MemoryLibraryItem
//    {
//        public TemplateInfo()
//        {
            
//        }

//        public override LibraryType Type
//        {
//            get { return LibraryType.Template; }
//        }

//        [XmlElement(IsNullable = false)]
//        public List<RegionInfo> Regions;

//        public override MemoryLibraryItem NewInstance()
//        {
//            return new TemplateInfo();
//            //throw new NotImplementedException();
//        }
//    }
//}
