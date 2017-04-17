using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using ProWrite.UFE.Entity;
using ProWrite.Entity.Library;

namespace ProWrite.UFE.Files
{
    public class PlaylistConverter : MemoryLibraryItemConverterBase<PlaylistInfo, PlaylistType>
    {
        public override PlaylistType Convert(PlaylistInfo playlist)
        {
            PlaylistType ufePlaylist = new PlaylistType();

            //Base info
#if VERSION_1
            ufePlaylist.Id = playlist.Id.ToString();
#else
            ConvertId(playlist, ref ufePlaylist.ContentID);
#endif
            ufePlaylist.Duration = playlist.Length;


            //Items
            if (playlist.Items != null && playlist.Items.Length > 0)
                ufePlaylist.Contents = ConvertFileItems(playlist);

            return ufePlaylist;
        }

        /// <summary>
        /// Function: Convert LibraryItems to IncludeFileItems
        /// Author  : Jerry Xu
        /// Date    : 2008-12-5
        /// </summary>
        /// <param name="playlist">PlaylistInfo</param>
        /// <returns>List<IncludeFileItem></returns>
        private List<PlaylistIncludeItem> ConvertFileItems(PlaylistInfo playlist)
        {

            List<PlaylistIncludeItem> fileItems = new List<PlaylistIncludeItem>();
            PlaylistIncludeItem fileItem;

            if (playlist.Items != null && playlist.Items.Length > 0)
            {
                foreach (LibraryAdapter adapter in playlist.Items)
                {
                    if (adapter.Target != null && adapter.Target.Length > 0)
                    {
                        fileItem = new PlaylistIncludeItem();
                        fileItem.Id = adapter.Target.Id.ToString();
                        if (adapter.Target.Type == LibraryType.Message)
                            fileItem.Type = PlaylistItemType.FrameObject;
                        if (adapter.Target.Type == LibraryType.TimeSliceGroup)
                            fileItem.Type = PlaylistItemType.TimeSliceGroup;
                        if (adapter.Target.Type == LibraryType.Playlist)
                            fileItem.Type = PlaylistItemType.Playlist;

                        fileItems.Add(fileItem);
                    }
                }
            }
            return fileItems;
        }
    }
}
