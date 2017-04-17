using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using ProWrite.UFE.Files;
using ProWrite.Entity.Library;
using ProWrite.Entity.Dashboard;
using log4net.Config;

namespace ProWrite.UFE.Test.Saver
{
    [TestFixture]
    public class TestBase
    {
        protected ScheduleSaver Saver { get; private set; }
        protected SchedulerInfo Scheduler { get; private set; }
        protected SignInfo Sign { get; private set; }
        protected int Count { get; set; }

        public TestBase()
        {
            
            Scheduler = new SchedulerInfo();
            Sign = new SignInfo { Name = "Demo Sign", Width = 64, Height = 32 };
            Saver = new ScheduleSaver { Item = Scheduler, Sign = Sign };
            Count = 1;
        }

        [SetUp]
        public void Init()
        {
            BasicConfigurator.Configure();
            LocalFilePathMapping.DeleteFiles();
        }

        protected  void DoPerform()
        {
            Scheduler.Items.Clear();

            OnPeforming();
            Saver.Populate();
            Assert.IsTrue(Saver.Files.Count > 0);
            Saver.Save();
            OnPerformed();

        }

        protected virtual void OnPeforming()
        {
        }

        protected virtual void OnPerformed()
        {
            Assert.IsTrue(Saver.IsSaveSucessed);
        }

       
    }
}
