using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Library;
using ProWrite.Entity.Shape;
using NUnit.Framework;

namespace ProWrite.UFE.Test.Saver
{
    public class LabelTest:TestBase
    {
        public LabelTest()
        {
            Count = 2;
        }

        protected override void OnPeforming()
        {
            base.OnPeforming();

            AppointmentInfo appointment = new AppointmentInfo();
            Scheduler.Add(appointment);

            MessageInfo item = new MessageInfo();
            ShapeLabel label = new ShapeLabel();

            ShapeLayer layer = new ShapeLayer(label);
            layer.EmphasisEffect.StartTime = 0;
            layer.EmphasisEffect.EndTime = 8;

            item.Add(layer);
            item.Length = 8;
            
            appointment.Target = item;
            appointment.AllDay = true;
            appointment.Subject = item.Name;
            appointment.StatusId = 0;
            double length = Convert.ToDouble(item.Length) / 3600;

            appointment.Duration = TimeSpan.FromHours(length);
            appointment.End = appointment.Start.AddSeconds(item.Length);
            appointment.Description = item.Type.ToString();
        }


        [Test]
        public void Perform()
        {
            OnPeforming();
            Saver.Populate();
            Assert.IsTrue(Saver.Files.Count == 3);
            Saver.Save();
            OnPerformed();
        }
    }
}
