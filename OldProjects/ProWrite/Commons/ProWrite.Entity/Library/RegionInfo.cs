//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Xml.Serialization;
//using ProWrite.Core;
//using System.Drawing;


//namespace ProWrite.Entity.Library
//{
//    [Serializable]
//    public class RegionInfo:MemoryLibraryItem
//    {
//        public RegionInfo()
//        {
            
//        }

//        [XmlElement(IsNullable = false)]
//        public Rectangle Bounds;

//        public override LibraryType Type
//        {
//            get { return LibraryType.Template; }
//        }

//        public override MemoryLibraryItem NewInstance()
//        {
//            return new RegionInfo();
//            //throw new NotImplementedException();
//        }
//    }
//}
