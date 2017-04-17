using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.UFE.Entity;
using System.Communication;
using ProWrite.Core;

namespace ProWrite.UFE
{
    public partial class UFEFrontController<TConnection>
    {

        AsyncFuture<UFEPacket> IMAManager.GetStatus()
        {
            return SendAsync(Commands.GetStatus);
        }


        AsyncFuture<UFEPacket> IMAManager.SetDateTime(string time)
        {
            return SendAsync(Commands.SetDateTime, time);
        }

        AsyncFuture<UFEPacket> IMAManager.SetTempOffset(string temp)
        {
            return SendAsync(Commands.TempOffset, temp);
        }

        //void IMAManager.SetTempOffset(string temp, TempFormat fmt)
        //{
        //    DoSend(Commands.TempOffset, new { Format = fmt, Value = temp });
        //}

        AsyncFuture<UFEPacket> IMAManager.SetDimming(List<DimmingSet> list)
        {
            return SendAsync(Commands.Dimming, list);
        }


        AsyncFuture<UFEPacket> IMAManager.Play(string messageId, int level, int type, long playRegionId)
        {
            return SendAsync(Commands.Play, new PlayContent { Id = messageId, Level = level, Type = type, RegionId = playRegionId });
        }

        event ReceivedHandler IMAManager.PlayCompleted
        {
            add { ActionProcessor[Commands.PlayCompleted].SuccessHandler += value; }
            remove { ActionProcessor[Commands.PlayCompleted].SuccessHandler -= value; }
        }

        AsyncFuture<UFEPacket> IMAManager.SkipQueueMessage()
        {
            return SendAsync(Commands.SkipQueueMessage);
        }

        AsyncFuture<UFEPacket> IMAManager.ClearQueueMessage()
        {
            return SendAsync(Commands.ClearQueueMessage);
        }

        AsyncFuture<UFEPacket> IMAManager.StartRender()
        {
            return SendAsync(Commands.StartRender);
        }


        AsyncFuture<UFEPacket> IMAManager.StopRender()
        {
            return SendAsync(Commands.StopRender);
        }

        AsyncFuture<UFEPacket> IMAManager.LoadScheduler()
        {
            return SendAsync(Commands.LoadScheduler);
        }

        AsyncFuture<UFEPacket> IMAManager.Diagnostics()
        {
            return SendAsync(Commands.Diagnostics);
        }


        AsyncFuture<UFEPacket> IMAManager.BlankSign()
        {
            return SendAsync(Commands.BlankSign);
        }

        AsyncFuture<UFEPacket> IMAManager.TestPattern()
        {
            return SendAsync(Commands.TestPattern);
        }
    }
}
