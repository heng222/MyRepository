//---------------------------------------------------------------------
//
// File: UndoManager.cs
//
// Description:
// 
//
// Author: Kevin
//
// Modify history:
//      Kevin  2008-6-19 Kevin Ç¨ÒÆ
//      Kevin  2008-6-30 Add comments
//      Kevin  2008-6-30 Add max stack deep
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using log4net;

namespace ProWrite.Core
{
    /// <summary>
    /// undo redo action
    /// </summary>
    public interface IUndoAction
    {
        /// <summary>
        /// perform undo action
        /// </summary>
        void Undo();
        /// <summary>
        /// perform redo action
        /// </summary>
        void Redo();

        string Name { get;set;}
    }

    public interface ITransaction : IDisposable
    {
        TransactionStatus Status { get;}
        void Commit();
        void Rollback();
        void Enlist();
    }

    public enum TransactionStatus
    {
        Init,
        Commited,
        Rollbacked,
        Unkown,
    }

    public abstract class UndoAction : DisposableObject, IUndoAction
    {
        public abstract void Undo();
        public abstract void Redo();

        private string name;
        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public override string ToString()
        {
            return name;
        }
    }

    public class StackList<T> : IEnumerable<T>
    {
        private List<T> stack = null;
        private readonly int maxCapacity = 100;

        public StackList(int capacity)
        {
            maxCapacity = capacity;
            stack = new List<T>(maxCapacity);
        }

        public void Push(T item)
        {
            if(stack.Count >= maxCapacity - 1)
                stack.RemoveAt(0);
            stack.Add(item);
        }

        public T Pop()
        {
            T t= default(T);

            if (stack.Count >= 1)
            {
                t = stack[stack.Count - 1];
                stack.RemoveAt(stack.Count - 1);
            }
            return t;
        }

        public int Count
        {
            get { return stack.Count; }
        }

        public void Clear()
        {
            stack.Clear();
        }

        #region IEnumerable<T> Members

        public IEnumerator<T> GetEnumerator()
        {
            return stack.GetEnumerator();
        }

        #endregion

        #region IEnumerable Members

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return stack.GetEnumerator();
        }

        #endregion
    }
    public class SimpleUndoAction : UndoAction
    {
        public Action UndoHandler { get; set; }
        public Action RedoHandler { get; set; }

        public override void Undo()
        {
            if (UndoHandler != null)
                UndoHandler();
        }

        public override void Redo()
        {
            if (RedoHandler !=null)
                RedoHandler();
        }

        protected override void Dispose(bool disposing)
        {
            UndoHandler = null;
            RedoHandler = null;
            base.Dispose(disposing);
        }
    }

    public class UndoManager : DisposableObject
    {
        /// <summary>
        /// Changed event
        /// </summary>
        [NonSerialized]
        private  EventHandler changed;
        public event EventHandler Changed
        {
            add { changed += value; }
            remove { changed -= value; }
        }

        [NonSerialized]
        private EventHandler _UndoAllCompleted;
        public event EventHandler UndoAllComleted
        {
            add
            {
                if (_UndoAllCompleted == null || _UndoAllCompleted.GetInvocationList().Length <= 0)
                    _UndoAllCompleted += value;
            }
            remove { _UndoAllCompleted -= value; }
        }

        private static long seed = 0;
        public long Id
        {
            get;
            private set;
        }

        protected virtual void OnChanged()
        {
            if (changed != null)
                changed(null, null);
        }

        [NonSerialized]
        private Transaction _tx;
        ActionStack actionStack;
        bool canAddAction = true;
        private int suspendCounter=0; 

        /// <summary>
        /// Action stack
        /// </summary>
        class ActionStack
        {
            private const int DefaultMaxCount = 20;
            internal static readonly ILog _log = LogManager.GetLogger("Undo Manager");

            //internal Stack<IUndoAction> undoStack;
            //internal Stack<IUndoAction> redoStack;
            internal StackList<IUndoAction> undoStack;
            internal StackList<IUndoAction> redoStack;

            public ActionStack()
                : this(DefaultMaxCount)
            {
            }

            public ActionStack(int size)
            {
                //undoStack = new Stack<IUndoAction>(size);
                //redoStack = new Stack<IUndoAction>(size);

                undoStack = new StackList<IUndoAction>(size);
                redoStack = new StackList<IUndoAction>(size);
            }

            /// <summary>
            /// can undo 
            /// </summary>
            public bool CanUndo
            {
                get { return undoStack.Count > 0; }
            }

            /// <summary>
            /// can redo
            /// </summary>
            public bool CanRedo
            {
                get { return redoStack.Count > 0; }
            }

            public void Undo()
            {
                try
                {
                    if (undoStack.Count > 0)
                    {
                        IUndoAction action = undoStack.Pop();
                        redoStack.Push(action);
                        action.Undo();
                    }
                }
                catch (Exception ex)
                {
                    _log.Error(ex.Message, ex);
                }
            }

            public void Redo()
            {
                try
                {
                    if (redoStack.Count > 0)
                    {
                        IUndoAction action = (IUndoAction)redoStack.Pop();
                        undoStack.Push(action);
                        action.Redo();
                    }
                }
                catch (Exception ex)
                {
                    _log.Error(ex.Message, ex);
                }
            }

            public void Push(IUndoAction action)
            {
                Debug.Assert(action != null);
                
                try
                {
                    undoStack.Push(action);
                    //redoStack.Clear();
                }
                catch (Exception ex)
                {
                    _log.Error(ex.Message, ex);
                }
            }

            public void ClearAll()
            {
                undoStack.Clear();
                redoStack.Clear();
            }

            public StackList<IUndoAction> UndoStack
            {
                get { return undoStack; }
            }
        }

        class Transaction : UndoAction, ITransaction
        {
            private List<IUndoAction> actions;
            private ActionStack actionStack;
            private TransactionStatus status;
            internal int transactionCount = 1;

            internal Transaction(string name, ActionStack actionStack)
            {
                Name = name;
                this.actionStack = actionStack;
                actions = new List<IUndoAction>();
                status = TransactionStatus.Unkown;
            }

            public TransactionStatus Status
            {
                get { return status; }
            }

            public void Commit()
            {
                transactionCount--;
                
                if (transactionCount == 0 
                    && status == TransactionStatus.Init
                    && actions.Count > 0)
                {
                    actionStack.Push(this);
                    status = TransactionStatus.Commited;
                }
            }

            public void Rollback()
            {
                transactionCount = 0;

                Undo();
                Clear();
                status = TransactionStatus.Rollbacked;
            }

            public void Enlist()
            {
                transactionCount++;
            }


            public void AddAction(IUndoAction action)
            {
                Check.Require(action, "action", Check.NotNull);
                Check.Require(status == TransactionStatus.Unkown
                    || status == TransactionStatus.Init);

                if (!actions.Contains(action))
                {
                    actions.Add(action);
                    status = TransactionStatus.Init;
                }
            }

            public override void Undo()
            {
                for(int i = actions.Count -1; i>=0;i--)
                {
                    try
                    {
                        actions[i].Undo();
                    }
                    catch (Exception ex)
                    {
                        ActionStack._log.Error(ex.Message, ex);
                    }
                }
            }

            public override void Redo()
            {
                foreach(IUndoAction action in actions)
                {
                    try
                    {
                        action.Redo();
                    }
                    catch (Exception ex)
                    {
                        ActionStack._log.Error(ex.Message, ex);
                    }
                }
            }

            public int Count
            {
                get { return actions.Count; }
            }

            public void Clear()
            {
                foreach (IUndoAction item in actions)
                {
                    if (item is IDisposable)
                        ((IDisposable)item).Dispose();
                }
                actions.Clear();
            }

            public void Dispose()
            {
                //Clear();
            }
        }
        
        //int actionCount;
        /// <summary>
        /// can undo
        /// </summary>
        public bool CanUndo
        {
            get { return canAddAction && actionStack.CanUndo; }
        }

        public void Resume()
        {
            suspendCounter--;
        }

        public void Suspend()
        {
            suspendCounter++;
        }

        public bool CanAddAction
        {
            get { return suspendCounter == 0 && actionStack.undoStack.Count < MaxCount; }
        }
        /// <summary>
        /// can redo
        /// </summary>
        public bool CanRedo
        {
            get { return suspendCounter==0 && actionStack.CanRedo; }
        }

        public int UndoStackCount
        {
            get { return actionStack.undoStack.Count; }
        }

        public int RedoStackCount
        {
            get { return actionStack.redoStack.Count; }
        }
        /// <summary>
        /// push action
        /// </summary>
        /// <param name="action"></param>
        public void AddAction(IUndoAction action)
        {
            if (!CanAddAction)
                return;

            Check.Require(action, "action", Check.NotNull);

            if (_tx != null)
                _tx.AddAction(action);
            else
            {
                actionStack.Push(action);
                OnChanged();
            }
        }

        public void AddAction(string actionName, Action undoAction, Action redoAction)
        {
            AddAction(new SimpleUndoAction { Name = actionName, UndoHandler = undoAction, RedoHandler = redoAction });
        }

        public bool BeginTransaction(string transactionName)
        {
            if (!CanAddAction)
                return false;
            if (_tx == null)
                _tx = new Transaction(transactionName, actionStack);
            else
                _tx.Enlist();
            return true;
        }

        public void Commit()
        {
            if (suspendCounter >0 || _tx == null)
                return;
            _tx.Commit();
            if (_tx.Status == TransactionStatus.Commited)
                OnChanged();
            if (_tx.transactionCount == 0)
                _tx = null;
        }

        public void Rollback()
        {
            if (suspendCounter > 0 || _tx == null)
                return;
            Suspend();
            _tx.Rollback();
            Resume();
            _tx = null;
        }

        private readonly int MaxCount;
        public UndoManager():this(20)
        {
        }

        public UndoManager(int stackSize)
        {
            Id = ++seed;
            MaxCount = stackSize;
            actionStack = new ActionStack(stackSize);
        }

        static UndoManager _current;
        /// <summary>
        /// current service
        /// </summary>
        public static UndoManager Current
        {
            get{ return _current;}
            set
            {
                if (_current != value)
                    _current = value;
            }
        }

        /// <summary>
        /// clear
        /// </summary>
        public void Clear()
        {
            actionStack.ClearAll();
            OnChanged();
        }

        /// <summary>
        /// perform undo action
        /// </summary>
        public void Undo()
        {
            Suspend();
            actionStack.Undo();
            Resume();
            OnChanged();
            if (UndoStackCount <= 0 && _UndoAllCompleted != null)
               _UndoAllCompleted(null, EventArgs.Empty);
        }

        /// <summary>
        /// perform redo action
        /// </summary>
        public void Redo()
        {
            Suspend();
            actionStack.Redo();
            Resume();
            OnChanged();
        }

        public IEnumerator<string> GetUndoEnumerator()
        {
            foreach (IUndoAction item in actionStack.undoStack)
                yield return item.Name;
        }

        public IEnumerator<string> GetRedoEnumerator()
        {
            foreach (IUndoAction item in actionStack.redoStack)
                yield return item.Name;
        }

        protected override void Dispose(bool disposing)
        {
            //if (_UndoAllCompleted != null)
            //    _UndoAllCompleted.GetInvocationList().Clear();
            //_UndoAllCompleted = null;
            base.Dispose(disposing);
        }
    }
}
