using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Library;

namespace ProWrite.Entity
{
    public interface IGenerator
    {
        void Generate();
    }

    public interface IBatchLoadGenerator
    {
        void Generate();
        void GenerateNailImageBatchLoad(MessageInfo message);
    }

    public interface IVideoGenerator
    {
        bool CreateVideo(MessageInfo mes, string fileurl);
    }
}
