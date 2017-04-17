//---------------------------------------------------------------------
//
// File: MessageController.cs
//      
// Description:
//      Message conterller class
//
// Author: Kevin 2008-7-28
//
// Modify History:
//      Jerry Xu 2008-12-25 Import gif file:Add(FileLibraryItem item, int length,SignInfo sign)¡¢AddNoSave(FileLibraryItem item, int length,SignInfo sign)
//      Jerry Xu 2009-3-12   Update property:Generateor
//      Jerry Xu 2009-3-12   Update method:Add(FileLibraryItem item, SignInfo sign),Add(MessageInfo item),AddNoSave(FileLibraryItem item, int length, SignInfo sign),AddNoSave(FileLibraryItem item, SignInfo sign)
//      Jerry Xu 2009-3-12   Add method:GenerateNailImage(MessageInfo message),GenerateNailImageNoSave(MessageInfo message)
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using System.IO;
using System.Xml.Serialization;
using ProWrite.Entity.Library.Controller;
using ProWrite.Entity.Shape;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library.ImportExport;
using System.Drawing;

namespace ProWrite.Entity.Library.Controller
{
	/// <summary>
	/// Message controller class
	/// </summary>
	[Serializable]
	public class MessageController : FileController<MessageInfo>
	{
        [NonSerialized]
        private static Serialiser<MessageWrapper> _ser = Serialiser<MessageWrapper>.Binaray;

        public static void Save(string file, MessageInfo message)
        {
            _ser.Serialize(new MessageWrapper(message), file);
        }

        public static MessageWrapper Load(string file)
        {
            return _ser.Deserialise(file);
        }

        public static MessageInfo Load1(string file)
        {
            return _ser.Deserialise(file);
        }

        public List<IFileHandle> GetFileHandle(string handle, ShapeType type)
        {
            List<IFileHandle> result = new List<IFileHandle>();
            foreach (MessageInfo item in this)
            {
                if (item == null)
                    continue;
                result.AddRange(item.GetFileHandle(handle, type));
            }
            return result;
        }

        public override LibraryItem AddFile(string file)
        {
            MessageInfo item = Load1(file);
            if (item != null)
            {
                item.Name = AllocateMessageName(item.Name);
                Add(item);
                OnAddCompleted(item);
            }
            return item;
        }

        private string AllocateMessageName(string name)
        {
            if (Contains(name))
            {
                name = name + "_";
                return AllocateMessageName(name);
            }

            return name;
        }

        public bool Add(FileLibraryItem item, SignInfo sign)
        {
            if (item==null || sign == null)
                return false;
            MessageInfo msg = new MessageInfo();
            msg.Size = new Size(sign.Width, sign.Height);

            msg.Name = Path.GetFileNameWithoutExtension(item.Name);
            msg.BackColor = sign.Template.Message.BackGroundColor;
            msg.Length = sign.Template.Message.DisplayTime;

            if (msg.Add(item, sign))
            {
                if (Add(msg))
                {
                    OnAddCompleted(msg);
                    GenerateNailImage(msg);
                    return true;
                }
            }
            return false;
        }

        public void GenerateNailImage(MessageInfo message)
        {
            if (_generator == null)
                return;
            
            MessageInfo tempMessage = (message as MemoryLibraryItem).Copy() as MessageInfo;
            _generator.GenerateNailImageBatchLoad(tempMessage);
            message.ImagePath = tempMessage.ImagePath;
            LibraryGroup.Current.Messages.Update(message);
        }

        public void GenerateNailImageNoSave(MessageInfo message)
        {
            if (_generator == null)
                return;
            MessageInfo tempMessage = (message as MemoryLibraryItem).Copy() as MessageInfo;
            
            _generator.GenerateNailImageBatchLoad(tempMessage);
            message.ImagePath = tempMessage.ImagePath;
            //LibraryGroup.Current.Messages.Update(message);
        }

        [NonSerialized]
        private IBatchLoadGenerator _generator = null;
        public IBatchLoadGenerator Generateor
        {
            set { _generator = value; }
        }

        public bool Add(FileLibraryItem item, int length, SignInfo sign)
        {
            if (item == null || sign == null)
                return false;
            MessageInfo msg = new MessageInfo();
            msg.Size = new Size(sign.Width, sign.Height);
            
            msg.Name = Path.GetFileNameWithoutExtension(item.Name);
            msg.BackColor = sign.Template.Message.BackGroundColor;
            if (length != -1)
                msg.Length = length;//sign.Template.Message.DefaultLength;
            else
                msg.Length = sign.Template.Message.DisplayTime;

            if (msg.Add(item, length,sign))
            {
                if (Add(msg))
                {
                    OnAddCompleted(msg);
                    GenerateNailImage(msg);
                    return true;
                }
            }
            return false;
        }

        public MessageInfo AddNoSave(FileLibraryItem item, SignInfo sign)
        {
            if (item == null || sign == null)
                return null;
            MessageInfo msg = new MessageInfo();
            msg.Size = new Size(sign.Width, sign.Height);

            msg.Name = Path.GetFileNameWithoutExtension(item.Name);
            msg.BackColor = sign.Template.Message.BackGroundColor;
            msg.Length = sign.Template.Message.DisplayTime;

            if (msg.Add(item, sign))
            {
                GenerateNailImageNoSave(msg);
                return msg;
            }
            return null;
        }

        public MessageInfo AddNoSave(FileLibraryItem item, int length, SignInfo sign)
        {
            if (item == null || sign == null)
                return null;
            MessageInfo msg = new MessageInfo();
            msg.Size = new Size(sign.Width,sign.Height);

            msg.Name = Path.GetFileNameWithoutExtension(item.Name);
            msg.BackColor = sign.Template.Message.BackGroundColor;
            if (length != -1)
                msg.Length = length;
            else
                msg.Length = sign.Template.Message.DisplayTime;

            
            if (msg.Add(item, length, sign))
            {
                GenerateNailImageNoSave(msg);   
                    
                return msg;
            }
            return null;
        }

		/// <summary>
		/// add message item
		/// </summary>
		/// <param name="item"></param>
		public override bool Add(MessageInfo item)
		{
			if (item == null || Contains(item.Name))
				return false;

			bool flag = base.Add(item);
            if (flag)
            {
                foreach (ShapeLayer layer in item.Items)
                    CheckFileLibrary(layer.Shape);
            }
            OnAddCompleted(item);
            GenerateNailImage(item);
            return flag;
		}


		/// <summary>
		/// update message item
		/// </summary>
		/// <param name="item"></param>
		public override bool Update(MessageInfo item)
		{
			if (item == null )
				return false;

			bool flag = base.Update(item);

            if (flag)
            {
                foreach (ShapeLayer layer in item.Items)
                    CheckFileLibrary(layer.Shape);
            }
            return flag;
		}

		/// <summary>
		/// check file library item by shape 
		/// </summary>
		/// <param name="shape"></param>
        private void CheckFileLibrary(ShapeBase shape)
        {
            if (shape == null)
                return;
            //if (shape.Type == ShapeType.Image)
            //    LibraryGroup.Images.AddFile(shape);
            //else if (shape.Type == ShapeType.Video)
            //    LibraryGroup.Videos.AddFile(shape);
        }
    }
}