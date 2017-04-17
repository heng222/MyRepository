using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public class PlayContent
    {
        /// <summary>
        /// Resource file id
        /// </summary>
        public string Id { get; set; }
        /// <summary>
        /// 
        /// </summary>
        public int Level { get; set; }

        public long RegionId { get; set; }

        public int Type { get; set; }
    }

}
