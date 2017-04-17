using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using ProWrite.Entity.Shape;
using ProWrite.UFE.Entity;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library;
using ProWrite.Entity;
using log4net;

namespace ProWrite.UFE.Files
{
    public class ShapePair:IGenerator
    {
        public ShapeBase Shape { get; set; }
        public UfeFile File { get; set; }
        public SignInfo Sign { get; set; }

        private static readonly ILog log = LogManager.GetLogger("ShapeGenerator");
        public void Generate()
        {
            //TODO:Generate
            string fileName = File.FromFilePath;
            //TODO:Generate
            
            switch (Shape.LayerType)
            {                 
                case ProWrite.Core.LayerType.Image:
                case ProWrite.Core.LayerType.Text:
                case ProWrite.Core.LayerType.Paint:
                    log.Debug("Begin Generate " + Shape.LayerType.ToString() + ".");
                    UFEPaintVisitor.Instance.ImageFile = fileName;
                    Shape.Accept(UFEPaintVisitor.Instance);
                    if (fileName == null)
                        throw new Exception("Generate shape file is failure!");  
                    if (!System.IO.File.Exists(fileName))
                        throw new Exception("Generate shape file is failure!");
                    log.Debug("End Generate " + Shape.LayerType.ToString() + ".");
                    break;
                case ProWrite.Core.LayerType.Video:
                case ProWrite.Core.LayerType.DynamicText:
                case ProWrite.Core.LayerType.DynamicVideo:
                    break;
            }

            if (Sign.Controller.Connection.Mode != ProWrite.UFE.ConnectionMode.Tcp)
                File.Content = IOHelper.ReadAllBytes(File.FromFilePath);            
            File.Size = IOHelper.GetFileLength(File.FromFilePath);
        }

        
    }

    class ShapeConverter : ConverterBase<ShapeBase, ShapePair>
    {

        private SignInfo _sign;
        /// <summary>
        /// Function: Upload target sign info
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
        /// </summary>
        public SignInfo Sign
        {
            get
            {
                return _sign;
            }
            set
            {
                if (value != _sign)
                    _sign = value;
            }
        }

        /// <summary>
        /// Function: Get uploaded filename by Shape
        /// Author  : Jerry Xu
        /// Date    : 2008-12-2
        /// </summary>
        /// <param name="shape">ShapeBase</param>
        /// <returns>FileName:string</returns>
        private FileType ConvertFileType(LayerType type)
        {
            switch (type)
            {
                case ProWrite.Core.LayerType.Image:
                    return FileType.Image;
                case ProWrite.Core.LayerType.Text:                
                    return FileType.Text;
                case ProWrite.Core.LayerType.Paint:
                    return FileType.Paint;
                case ProWrite.Core.LayerType.Video:
                    return FileType.Video;
                default:
                    return FileType.None;
             }
        }



        /// <summary>
        /// Function: Convert ShapeBase(ShapeBase) to UfeFile(Need uploaded files)
        /// Author  : Jerry Xu
        /// Date    : 2008-12-8
        /// </summary>
        /// <param name="item">ShapeBase</param>
        /// <returns>UfeFile</returns>
        public override ShapePair Convert(ShapeBase item)
        {            
            var type = ConvertFileType(item.LayerType);
            if (type == FileType.None)
                return null;
            UfeFile file = new UfeFile();            
            
            file.Type =type;
            if (item.Type == ShapeType.Video)
            {
                if (string.IsNullOrEmpty(item.VideoFileID))
                    file.FromFilePath = (item as ShapeVideo).VideoUrl;
                else
                    file.FromFilePath = LocalFilePathMapping.GetFile(file.Type, item.VideoFileID);
            }
            else
            {
                file.Id = Guid.NewGuid().ToString().Replace("-", "");

                if (file.Type != FileType.None)
                    file.FromFilePath = LocalFilePathMapping.GetFile(file.Type, file.Id);
            }

            if (file.Type != FileType.None)
            {
                
                file.ToFilePath = FilePathMapping.GetFile(file.Type, file.Id);                
            }
           
            return new ShapePair { Shape = item, File = file, Sign = this.Sign };
        }
    }
}
