//---------------------------------------------------------------------
//
// File: LibraryNode.cs
//      
// Description:
//      Library node class
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
using DevExpress.XtraTreeList.Nodes;

using ProWrite.Entity.Library;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Library
{
    /// <summary>
    /// Library node class
    /// </summary>
    public class LibraryNode : TreeListNode
    {
        public LibraryNode(int id, TreeListNodes owner)
            : base(id, owner)
        {
        }

        private static Dictionary<NodeType, NodeType> _typeMap;
        static LibraryNode()
        {
            _typeMap = new Dictionary<NodeType, NodeType>(6);
            _typeMap[NodeType.Images] = NodeType.Image;
            //_typeMap[NodeType.Videos] = NodeType.Video;
            _typeMap[NodeType.Messages] = NodeType.Message;
            _typeMap[NodeType.TimeSliceGroups] = NodeType.TimeSliceGroup;
            _typeMap[NodeType.Playlists] = NodeType.Playlist;
            _typeMap[NodeType.Schedulers] = NodeType.Scheduler;
        }

        private NodeType _categoryMode= NodeType.None;
        private NodeType _subNodeType = NodeType.None;

        /// <summary>
        /// get or set node type
        /// </summary>
        public NodeType NodeType
        {
            get { return _categoryMode; }
            set
            {
                _categoryMode = value;
                if (_typeMap.ContainsKey(value))
                    _subNodeType = _typeMap[value];
                else
                    _subNodeType = NodeType.None;
            }
        }

        /// <summary>
        /// get sub node type
        /// </summary>
        public NodeType SubType
        {
            get { return _subNodeType; }
        }

        private LibraryType _libraryType;
        /// <summary>
        /// get or set library type
        /// </summary>
        public LibraryType LibraryType
        {
            get { return _libraryType; }
            set { _libraryType = value; }
        }

        /// <summary>
        /// get or set library
        /// </summary>
        public LibraryItem Library
        {
            get { return Tag as LibraryItem; }
            set { Tag = value; }
        }

        /// <summary>
        /// get sub node by library item
        /// </summary>
        /// <param name="item"></param>
        /// <returns></returns>
        public LibraryNode GetSubNode(LibraryItem item)
        {
            if (_subNodeType == NodeType.None)
                return null;

            if (Nodes.Count < 1)
                return null;
            foreach (LibraryNode node in Nodes)
                if (node.Library.Name == item.Name)
                    return node;
            return null;
        }
    }

    /// <summary>
    /// node type
    /// </summary>
    public enum NodeType
    {
        Images,
        Videos,
        Messages,
        TimeSliceGroups,
        Playlists,
        Schedulers,
        Separator,
        Image,
        Video,
        Message,
        TimeSliceGroup,
        Playlist,
        Scheduler,
        MLPlaylist,
        None,
    }
}
