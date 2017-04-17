//---------------------------------------------------------------------
//
// File: PWMessage.cs
//
// Description:
// ProWrite message class
//
// Author: Kevin
//
// Modify histories:
//      Jerry Xu 2009-1-14 Add message:LibraryGroupActionStateMessage
//      Jerry Xu 2009-3-19 Add message:LibraryImageChangeMessage
//      Jerry Xu 2009-4-20 Add message:LibraryImportTimeSliceGroupMessage
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Communication;

namespace ProWrite.Core
{
    public interface IPWAction
    {
        void Perform(IPacket req);
    }

    public interface IUIAction : IPWAction
    {
        void Perform(PWMessage req);
    }

    /// <summary>
    /// ProWrite Message class
    /// </summary>
    [Serializable]
    public class PWMessage : IComparable<PWMessage>
    {
        public PWMessage() { }
        /// <summary>
        /// Get or set Message send time
        /// </summary>
        public DateTime? Time = DateTime.Now;

        private object sender;
        /// <summary>
        /// Get or set message sender
        /// </summary>
        public object Sender
        {
            get { return sender; }
            set
            {
                sender = value;
            }
        }

        public virtual int CompareTo(PWMessage other)
        {
            if (other == null || !other.Time.HasValue || !Time.HasValue)
                return 1;
            if (Time == other.Time)
                return 0;

            return Time.Value.CompareTo(other.Time.Value);
        }
    }

    /// <summary>
    /// Generic ProWrite message class
    /// </summary>
    /// <typeparam name="TContent"></typeparam>
    [Serializable]
    public class PWMessage<TContent> : PWMessage
    {
        private readonly TContent content;

        public TContent Content { get { return content; } }

        public PWMessage(TContent content)
        {
            this.content = content;
        }
    }

    /// <summary>
    /// Rename library message
    /// </summary>
    public class LibraryRenameMessage : PWMessage
    {
        public readonly string NewName;
        public readonly string OldName;
        public readonly LibraryType Type;
        public LibraryRenameMessage(string newName, string oldName, LibraryType type)
        {
            NewName = newName;
            OldName = oldName;
            Type = type;
        }
    }

    /// <summary>
    /// Rename library message
    /// </summary>
    public class LibraryLenghtChangedMessage : PWMessage
    {
        public readonly string Name;
        public readonly int Length;
        public readonly LibraryType Type;
        public LibraryLenghtChangedMessage(string newName, int length, LibraryType type)
        {
            Name = newName;
            Length = length;
            Type = type;
        }
    }


    /// <summary>
    /// Rename library message
    /// </summary>
    public class LibraryImportTimeSliceGroupMessage : PWMessage
    {
        public readonly string Name;
        public readonly LibraryType Type;
        public LibraryImportTimeSliceGroupMessage(string name, LibraryType type)
        {
            Name = name;
            Type = type;
        }
    }


    /// <summary>
    /// Rename library message
    /// </summary>
    //public class LibraryImageChangeMessage : PWMessage
    //{
    //    public readonly string Name;
    //    public readonly LibraryType Type;
    //    public LibraryImageChangeMessage(string name, LibraryType type)
    //    {
    //        Name = name;
    //        Type = type;
    //    }
    //}

    public class GetSignInfoMessage : PWMessage
    {
        public object Resp;
        public GetSignInfoMessage(object resp)
        {
            Resp = resp;
        }
    }

    public class PlayComplete : PWMessage
    {
        public string MessageId;

        public string MessageInfo;
        public string ScheduleInfo;
        public string PlsylistInfo;
        public string EndTime;
        public PlayComplete(string messageId, string messageInfo, string scheduleInfo
                               , string plsylistInfo, string endTime)
        {
            MessageId = messageId;
            MessageInfo = messageInfo;
            ScheduleInfo = scheduleInfo;
            PlsylistInfo = plsylistInfo;
            EndTime = endTime;
        }
    }
    /// <summary>
    /// LibraryGroup edit state
    /// </summary>
    public class LibraryGroupActionStateMessage : PWMessage
    {
        public readonly bool CanEdit;

        public LibraryGroupActionStateMessage(bool canEdit)
        {
            CanEdit = canEdit;
        }
    }


    /// <summary>
    /// LibraryGroup edit state
    /// </summary>
    public class InsertMenuActionStateMessage : PWMessage
    {

        public InsertMenuActionStateMessage()
        {
        }
    }


    /// <summary>
    /// Live session change
    /// </summary>
    public class SessionChangeMessage : PWMessage
    {
        public SessionChangeMessage()
        {
        }
    }

    /// <summary>
    /// Live session change
    /// </summary>
    public class SessionNameChangeMessage : PWMessage
    {
        public readonly string Name;
        public readonly bool IsChange;
        public SessionNameChangeMessage(string name, bool isChange)
        {
            Name = name;
            IsChange = isChange;
        }
    }
}
