using System;
using System.Collections.Generic;
using System.Text;
using NUnit.Framework;
using ProWrite.Core;

namespace ProWrite.Commons.Test.UndoRedo
{
    [TestFixture]
    public class UndoActionTest2
    {
        public UndoActionTest2()
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

            UndoManager undoManager;
            public Counter(UndoManager undoMgr)
            {
                undoManager = undoMgr;
            }
            public void Increase()
            {
                count++;
                undoManager.AddAction(new AddCountAction(this));
            }

            public void Decrease()
            {
                count--;
                undoManager.AddAction(new MinusCountAction(this));
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

            UndoManager undoMgr = new UndoManager();
            Counter counter = new Counter(undoMgr);

            counter.Increase();
            counter.Increase();
            counter.Increase();

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
            UndoManager undoMgr = new UndoManager();
            Counter counter = new Counter(undoMgr);

            undoMgr.BeginTransaction("From 1 to 10");
            for (int i = 0; i < 10; i++)
            {
                counter.Increase();
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
            UndoManager undoMgr = new UndoManager();
            Counter counter = new Counter(undoMgr);


            undoMgr.BeginTransaction("From 1 to 10");
            for (int i = 0; i < 10; i++)
            {
                counter.Increase();
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
            UndoManager undoMgr = new UndoManager();
            Counter counter = new Counter(undoMgr);


            undoMgr.BeginTransaction("From 1 to 10");
            for (int i = 0; i < 10; i++)
            {
                counter.Increase();
            }
            undoMgr.Commit();
            Assert.IsTrue(counter.Count == 10);

            undoMgr.Rollback();
        }

        [Test]
        public void RollbackTest()
        {
            UndoManager undoMgr = new UndoManager();
            Counter counter = new Counter(undoMgr);

            undoMgr.BeginTransaction("From 1 to 10");
            for (int i = 0; i < 10; i++)
            {
                counter.Increase();
            }
            undoMgr.Rollback();
            Assert.IsTrue(counter.Count == 0);
            Assert.IsTrue(undoMgr.UndoStackCount == 0);
        }

        [Test]
        //[ExpectedException(typeof(PreconditionException))]
        public void RollbackTest2()
        {
            UndoManager undoMgr = new UndoManager();
            Counter counter = new Counter(undoMgr);

            undoMgr.BeginTransaction("From 1 to 10");
            for (int i = 0; i < 10; i++)
            {
                counter.Increase();
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
            UndoManager undoMgr = new UndoManager();
            Counter counter = new Counter(undoMgr);

            undoMgr.BeginTransaction("From 1 to 10");
            for (int i = 0; i < 10; i++)
            {
                counter.Increase();
            }
            undoMgr.Rollback();
            Assert.IsTrue(counter.Count == 0);
            Assert.IsTrue(undoMgr.UndoStackCount == 0);

            undoMgr.Rollback();
        }
    }
}
