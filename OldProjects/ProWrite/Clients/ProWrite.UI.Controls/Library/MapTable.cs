//---------------------------------------------------------------------
//
// File: MapTable.cs
//      
// Description:
//      Type map table class
//
// Author: Kevin 2008-7-28
//
// Modify History:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;


namespace ProWrite.UI.Controls.Library
{
    /// <summary>
    /// Type map table class
    /// </summary>
    internal class MapTable
    {
        private static readonly Dictionary<LibraryType, NodeType> _lib2Node;
        private static readonly Dictionary<NodeType, LibraryType> _node2Lib;
        private static readonly Dictionary<LibraryType, int> _lib2ImageIndex;

        private class ImageIndex
        {
            public const int 
                Image = 0
                ,Video = 1
                ,Message = 2
                ,TimeSliceGroup = 3
                ,Playlist = 4
                , Scheduler = 5
                ,MLPlaylist = 4
                ;
        }

        static MapTable()
        {
            _lib2Node = new Dictionary<LibraryType,NodeType>();
            _node2Lib = new Dictionary<NodeType, LibraryType>();
            _lib2ImageIndex = new Dictionary<LibraryType, int>();

            _lib2Node[LibraryType.Image] = NodeType.Image;
            _lib2Node[LibraryType.Video] = NodeType.Video;
            _lib2Node[LibraryType.Message] = NodeType.Message;
            _lib2Node[LibraryType.TimeSliceGroup] = NodeType.TimeSliceGroup;
            _lib2Node[LibraryType.Playlist] = NodeType.Playlist;
            _lib2Node[LibraryType.Schedule] = NodeType.Scheduler;
            _lib2Node[LibraryType.MLPlaylist] = NodeType.MLPlaylist;

            _node2Lib[NodeType.Images] = LibraryType.Image;
            _node2Lib[NodeType.Videos] = LibraryType.Video;
            _node2Lib[NodeType.Messages] = LibraryType.Message;
            _node2Lib[NodeType.TimeSliceGroups] = LibraryType.TimeSliceGroup;
            _node2Lib[NodeType.Playlists] = LibraryType.Playlist;
            _node2Lib[NodeType.Schedulers] = LibraryType.Schedule;
            _node2Lib[NodeType.MLPlaylist] = LibraryType.MLPlaylist;

            _lib2ImageIndex[LibraryType.Image] = ImageIndex.Image;
            _lib2ImageIndex[LibraryType.Video] = ImageIndex.Video;
            _lib2ImageIndex[LibraryType.Message] = ImageIndex.Message;
            _lib2ImageIndex[LibraryType.TimeSliceGroup] = ImageIndex.TimeSliceGroup;
            _lib2ImageIndex[LibraryType.Playlist] = ImageIndex.Playlist;
            _lib2ImageIndex[LibraryType.Schedule] = ImageIndex.Scheduler;
            _lib2ImageIndex[LibraryType.MLPlaylist] = ImageIndex.MLPlaylist;
        }

        public static NodeType GetNodeType(LibraryType type)
        {
            if (_lib2Node.ContainsKey(type))
                return _lib2Node[type];
            return NodeType.None;
        }

        public static int GetImageIndex(LibraryType type)
        {
            if (_lib2ImageIndex.ContainsKey(type))
                return _lib2ImageIndex[type];
            return 0;
        }

        public static LibraryType GetLibraryType(NodeType type)
        {
            if (_node2Lib.ContainsKey(type))
                return _node2Lib[type];
            return LibraryType.None;
        }
    }
}
