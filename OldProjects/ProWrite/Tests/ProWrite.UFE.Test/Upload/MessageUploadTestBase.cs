using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Library;
using ProWrite.Entity.Shape;
using ProWrite.Core;

namespace ProWrite.UFE.Test.Upload
{
    public class MessageUploadTestBase:UploadBaseTest
    {
        protected override ProWrite.Entity.Library.SchedulerInfo Scheduler
        {
            get
            {
                SchedulerInfo scheduler = new SchedulerInfo();
                AppointmentInfo appointment = new AppointmentInfo();
                scheduler.Add(appointment);

                MessageInfo item = new MessageInfo();
                ShapeLabel label = new ShapeLabel();
                ShapeLayer layer = new ShapeLayer(label);
                item.Add(layer);

                appointment.Target = item;
                appointment.AllDay = true;
                appointment.Subject = item.Name;
                appointment.StatusId = 0;
                double length = Convert.ToDouble(item.Length) / 3600;

                appointment.Duration = TimeSpan.FromHours(length);
                appointment.End = appointment.Start.AddSeconds(item.Length);
                appointment.Description = item.Type.ToString();

                return scheduler;
            }
        }


    }
}
