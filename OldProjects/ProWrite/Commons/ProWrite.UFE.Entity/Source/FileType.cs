using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// File type
    /// </summary>
    public enum FileType
    {
        None = -1,
        Text,
        Paint,
        Image,
        Image_Meta,
        Video,
        Video_Meta,
        MessageNailImage,
        Message,
        TimesliceGroup,
        Playlist,
        Schedule,
        TemplateMessage,
        Log,
        
    }
}
