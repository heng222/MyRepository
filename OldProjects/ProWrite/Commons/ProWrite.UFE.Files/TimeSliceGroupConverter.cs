using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE.Entity;
using ProWrite.Core;
using ProWrite.Entity.Library;

namespace ProWrite.UFE.Files
{
    public class TimeSliceGroupConverter : MemoryLibraryItemConverterBase<TimeSliceGroupInfo, TimeSliceGroupType>
    {
        public override TimeSliceGroupType Convert(TimeSliceGroupInfo group)
        {
            TimeSliceGroupType ufeGroup = new TimeSliceGroupType();
            List<ProWrite.UFE.Entity.FrameObjectType> messages = new List<ProWrite.UFE.Entity.FrameObjectType>();
#if VERSION_1
            ufeGroup.Id = group.Id.ToString();
#else
            ConvertId(group, ref ufeGroup.ContentID);
#endif
            ufeGroup.Duration = float.Parse(group.Length.ToString());
            ufeGroup.IsRandom = group.IsRandom;

            if (group.Items != null && group.Items.Length > 0)
            {
                ufeGroup.Contents = ConvertMessages(group);
            }

            return ufeGroup;
        }

        /// <summary>
        /// Function: Convert Messages to IncludeFileItems
        /// Author  : Jerry Xu
        /// Date    : 2008-12-5
        /// </summary>
        /// <param name="group">TimeSliceGroupInfo</param>
        /// <returns>List<IncludeFileItem></returns>
        private List<TimeSliceGroupIncludeItem> ConvertMessages(TimeSliceGroupInfo group)
        {
            List<TimeSliceGroupIncludeItem> fileItems = new List<TimeSliceGroupIncludeItem>();
            TimeSliceGroupIncludeItem fileItem;

            foreach (MessageAdapterInfo item in group.Items)
            {
                if (item.Target != null && item.IsActive)
                {
                    fileItem = new TimeSliceGroupIncludeItem();
                    fileItem.Id = item.Target.Id.ToString();
                    fileItem.Type = TimeSliceGroupItemType.FrameObject;

                    fileItems.Add(fileItem);
                }
            }

            return fileItems;
        }
    }
}
