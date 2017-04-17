//---------------------------------------------------------------------
//
// File: FileLibraryItem.cs
//
// Description:
// The abstract class of FileLibraryItem
//
// Author: Kevin
//
// Date:
//
// Modify history:
//      Jerry Xu 2008-9-11 Add method:GetByPath
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using ProWrite.Entity.Shape;
using ProWrite.Core;
using ProWrite.Entity.Library.ImportExport;

namespace ProWrite.Entity.Library.Controller
{
    [Serializable]
    public abstract class FileLibraryController<T>:FileController<T> where T:FileLibraryItem,new ()
    {

        protected class Pair
        {
            public readonly T Item;
            public readonly string TargetFile;
            public Pair(string targetFile, T item)
            {
                Item = item;
                TargetFile = targetFile;
            }
        }

        protected abstract string LibraryDir
        {
            get;
        }

        protected bool Rename(string newName, string oldName,ShapeType type)
        {
            if (string.IsNullOrEmpty(newName) || newName == oldName)
                return false;

            LibraryGroup group = LibraryGroup.Current;
            if (group == null)
                return false;

            T item = GetByName(oldName);
            if (item == null)
                return false;

            string newFile = LibraryDir + newName;
            if (!IOHelper.RenameFile(newFile, item.Path))
                return false;

            item.Name = newName;
            item.Path = newFile;
            if (group.Messages != null)
            {
                List<IFileHandle> handles = group.Messages.GetFileHandle(item.Id, type);
                foreach (var h in handles)
                {
                    h.FileUrl = item.Path;
                }
            }

            MessageBus.Send(this, new FileLibraryRenameMessage(item));
            return true;
        }

        protected T InternalAppendFile(string file)
        {
            if (string.IsNullOrEmpty(file) || !File.Exists(file))
                return null;

            string libraryName = Path.GetFileName(file);
            string targetFile = LibraryDir + libraryName;

            T item = null;
            if (File.Exists(targetFile))
            {
                item = GetByName(targetFile);
                if (item != null)
                    return item;

                item = new T();
                item.Name = libraryName;
                item.Path = targetFile;
                Add(item);
                OnAddCompleted(item);
                return item;
            }

            File.Copy(file, targetFile, false);
            IOHelper.SetFileAttribute(targetFile, FileAttributes.Normal);

            item = GetByName(libraryName);
            if (item != null)
                return item;
            
            item =  new T();
            item.Name = libraryName;
            item.Path = targetFile;
            Add(item);
            OnAddCompleted(item);
            return item;
        }

        protected T InternalAppendFile(FileItem fileItem)
        {
            if (fileItem ==null || File.Exists(fileItem.Path))
                return null;

            IOHelper.WriteAllBytes(fileItem.Path, fileItem.Content);

            T item = GetByName(fileItem.Name);
            if (item != null)
                return item;

            item = new T();
            item.Id = fileItem.Id;
            item.Name = fileItem.Name;
            item.Path = fileItem.Path;
            Add(item);
            OnAddCompleted(item);
            return item;
        }

        protected T InternalAppendFile(string file,string libraryFile)
        {
            if (string.IsNullOrEmpty(file) || !File.Exists(file))
                return null;
            string libraryName = Path.GetFileName(libraryFile);
            string targetFile = libraryFile;

            File.Copy(file, libraryFile, false);
            IOHelper.SetFileAttribute(libraryFile, FileAttributes.Normal);

            T item = GetByName(libraryName);
            if (item != null)
                return item;

            item = new T();
            item.Name = libraryName;
            item.Path = targetFile;
            Add(item);
            OnAddCompleted(item);
            return item;
        }

        protected T InternalAppendFile(string file, byte[] content)
        {
            if (string.IsNullOrEmpty(file) || File.Exists(file))
                return null;
            string libraryName = Path.GetFileName(file);

            IOHelper.WriteAllBytes(file, content);
            
            T item = GetByName(libraryName);
            if (item != null)
                return item;

            item = new T();
            item.Name = libraryName;
            item.Path = file;
            Add(item);
            OnAddCompleted(item);
            return item;
        }


        public virtual void AddFile(IFileHandle shape)
        {
            if (shape == null)
                return;

            T item = InternalAppendFile(shape.FileUrl);
            if (item != null)
            {
                shape.FileHandle = item.Id;
                shape.FileUrl = item.Path;
            }
        }

        public virtual void AddFile(IFileHandle shape, bool isLock)
        {
            if (shape == null)
                return;

            T item = InternalAppendFile(shape.FileUrl);
            if (item != null)
            {
                shape.FileHandle = item.Id;
                shape.FileUrl = item.Path;
                item.IsLock = isLock;
            }
        }

        public virtual void AddFile(IFileHandle shape,string targetFile, bool isLock)
        {
            if (shape == null)
                return;

            T item = InternalAppendFile(shape.FileUrl,targetFile);
            if (item != null)
            {
                shape.FileHandle = item.Id;
                shape.FileUrl = item.Path;
                item.IsLock = isLock;
            }
        }

        public override LibraryItem AddFile(string file)
        {
            return InternalAppendFile(file);
        }

        public LibraryItem AddFile(FileItem item)
        {
            return InternalAppendFile(item);
        }


        public LibraryItem AddFile(string file,byte[] content)
        {
            return InternalAppendFile(file,content);
        }

        public LibraryItem AddFile(string file, string libraryFile)
        {
            return InternalAppendFile(file, libraryFile);
        }


        public override bool Remove(T item)
        {
            IOHelper.RemoveFile(item.Path);
            return base.Remove(item);
        }

        public T GetByPath(string path)
        {
            string libraryName = Path.GetFileName(path);
            foreach (T item in this)
            {
                if (string.Equals(item.Name, libraryName, StringComparison.OrdinalIgnoreCase))
                    return item;
            }
            return null;
        }
    }
}
