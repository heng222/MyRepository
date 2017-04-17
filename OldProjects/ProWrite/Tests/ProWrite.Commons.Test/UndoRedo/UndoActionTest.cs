using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using NUnit.Framework;

namespace ProWrite.Commons.Test.UndoRedo
{
    [TestFixture]
    public class UndoActionTest
    {
        public UndoActionTest()
        {
        }

        [SetUp]
        public void Setup()
        {
            //Check.ErrorMode = true;
        }

        [TearDown]
        public void CleanUp()
        {
            //Check.ErrorMode = false;
        }

        private class Counter
        {
            private int count = 0;

            public void Increase()
            {
                count++;
            }

            public void Decrease()
            {
                count--;
            }

            public int Count
            {
                get { return count; }
            }

            internal void Set(int count)
            {
                this.count = count;
            }
        }

        private class AddCountAction : UndoAction
        {
            private Counter owner;
            private int prev;
            public AddCountAction(Counter item)
            {
                this.owner = item;
                this.prev = item.Count - 1;
                Name = string.Format("{0}++", prev);
            }

            public override void Undo()
            {
                owner.Decrease();
            }

            public override void Redo()
            {
                owner.Increase();
            }
        }

        private class MinusCountAction : UndoAction
        {
            private Counter owner;
            private int prev;
            public MinusCountAction(Counter item)
            {
                this.owner = item;
                this.prev = item.Count + 1;
                Name = string.Format("{0}--", prev);
            }

            public override void Undo()
            {
                owner.Increase();
            }

            public override void Redo()
            {
                owner.Decrease();
            }
        }

        [Test]
        public void Test1()
        {
            Counter counter = new Counter();
            UndoManager undoMgr = new UndoManager();

            counter.Increase();
            undoMgr.AddAction(new AddCountAction(counter));
            counter.Increase();
            undoMgr.AddAction(new AddCountAction(counter));
            counter.Increase();
            undoMgr.AddAction(new AddCountAction(counter));

            Assert.IsTrue(counter.Count == 3);
            Assert.IsTrue(undoMgr.UndoStackCount == counter.Count);

            undoMgr.Undo();
            Assert.IsTrue(counter.Count == 2);
            Assert.IsTrue(undoMgr.UndoStackCount == 2);
            Assert.IsTrue(undoMgr.RedoStackCount == 1);
            undoMgr.Undo();
            Assert.IsTrue(counter.Count == 1);
            Assert.IsTrue(undoMgr.UndoStackCount == 1);
            Assert.IsTrue(undoMgr.RedoStackCount == 2);
            undoMgr.Undo();
            Assert.IsTrue(counter.Count == 0);
            Assert.IsTrue(undoMgr.UndoStackCount == 0);
            Assert.IsTrue(undoMgr.RedoStackCount == 3);

            undoMgr.Redo();
            Assert.IsTrue(counter.Count == 1);
            Assert.IsTrue(undoMgr.UndoStackCount == 1);
            Assert.IsTrue(undoMgr.RedoStackCount == 2);
            undoMgr.Redo();
            Assert.IsTrue(counter.Count == 2);
            Assert.IsTrue(undoMgr.UndoStackCount == 2);
            Assert.IsTrue(undoMgr.RedoStackCount == 1);
            undoMgr.Redo();
            Assert.IsTrue(counter.Count == 3);
            Assert.IsTrue(undoMgr.UndoStackCount == 3);
            Assert.IsTrue(undoMgr.RedoStackCount == 0);

        }

        /// <summary>
        /// 提交之后可以进行Undo/Redo或者再启动事务
        /// </summary>
        [Test]
        public void CommitTest()
        {
            Counter counter = new Counter();
            UndoManager undoMgr = new UndoManager();

            undoMgr.BeginTransaction("From 1 to 10");
            for (int i = 0; i < 10; i++)
            {
                counter.Increase();
                undoMgr.AddAction(new AddCountAction(counter));
            }
            undoMgr.Commit();
            Assert.IsTrue(counter.Count == 10);

            undoMgr.Undo();
            Assert.IsTrue(counter.Count == 0);

            undoMgr.Redo();
            Assert.IsTrue(counter.Count == 10);

            undoMgr.Undo();
            Assert.IsTrue(counter.Count == 0);

            undoMgr.Redo();
            Assert.IsTrue(counter.Count == 10);

            undoMgr.BeginTransaction("From 10 to 15");
            for (int i = 0; i < 5; i++)
            {
                counter.Increase();
                undoMgr.AddAction(new AddCountAction(counter));
            }
            undoMgr.Commit();
            Assert.IsTrue(counter.Count == 15);
        }


        /// <summary>
        /// 提交之后不能再提交
        /// </summary>
        [Test]
        //[ExpectedException(typeof(PreconditionException))]
        public void CommitTest2()
        {
            Counter counter = new Counter();
            UndoManager undoMgr = new UndoManager();

            undoMgr.BeginTransaction("From 1 to 10");
            for (int i = 0; i < 10; i++)
            {
                counter.Increase();
                undoMgr.AddAction(new AddCountAction(counter));
            }
            undoMgr.Commit();
            Assert.IsTrue(counter.Count == 10);

            undoMgr.Commit();
        }

        /// <summary>
        /// 提交之后不能再回滚
        /// </summary>
        [Test]
        //[ExpectedException(typeof(PreconditionException))]
        public void CommitTest3()
        {
            Counter counter = new Counter();
            UndoManager undoMgr = new UndoManager();

            undoMgr.BeginTransaction("From 1 to 10");
            for (int i = 0; i < 10; i++)
            {
                counter.Increase();
                undoMgr.AddAction(new AddCountAction(counter));
            }
            undoMgr.Commit();
            Assert.IsTrue(counter.Count == 10);

            undoMgr.Rollback();
        }

        [Test]
        public void RollbackTest()
        {
            Counter counter = new Counter();
            UndoManager undoMgr = new UndoManager();

            undoMgr.BeginTransaction("From 1 to 10");
            for (int i = 0; i < 10; i++)
            {
                counter.Increase();
                undoMgr.AddAction(new AddCountAction(counter));
            }
            undoMgr.Rollback();
            Assert.IsTrue(counter.Count == 0);
            Assert.IsTrue(undoMgr.UndoStackCount == 0);
        }

        [Test]
        //[ExpectedException(typeof(PreconditionException))]
        public void RollbackTest2()
        {
            Counter counter = new Counter();
            UndoManager undoMgr = new UndoManager();

            undoMgr.BeginTransaction("From 1 to 10");
            for (int i = 0; i < 10; i++)
            {
                counter.Increase();
                undoMgr.AddAction(new AddCountAction(counter));
            }
            undoMgr.Rollback();
            Assert.IsTrue(counter.Count == 0);
            Assert.IsTrue(undoMgr.UndoStackCount == 0);

            undoMgr.Commit();
        }

        [Test]
        //[ExpectedException(typeof(PreconditionException))]
        public void RollbackTest3()
        {
            Counter counter = new Counter();
            UndoManager undoMgr = new UndoManager();

            undoMgr.BeginTransaction("From 1 to 10");
            for (int i = 0; i < 10; i++)
            {
                counter.Increase();
                undoMgr.AddAction(new AddCountAction(counter));
            }
            undoMgr.Rollback();
            Assert.IsTrue(counter.Count == 0);
            Assert.IsTrue(undoMgr.UndoStackCount == 0);

            undoMgr.Rollback();
        }
    }
}
