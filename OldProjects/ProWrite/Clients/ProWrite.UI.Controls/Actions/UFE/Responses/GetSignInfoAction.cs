using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;

namespace ProWrite.UI.Controls.Actions.UFE.Responses
{
    class GetSignInfoAction : ProxyAction
    {
        public override Commands Id
        {
            get { return Commands.GetSignInfo; }
        }

        protected override void HandleResponseSuccess(UFEPacket resp)
        {
            var sign = Controller.Sign as SignInfo;
            string signInfo = resp.Content.GetProperty<string>("Info");
            int height = resp.Content.GetProperty<int>("Hight");
            int width = resp.Content.GetProperty<int>("Width");
            SignType signType = EnumHelper.Parse<SignType>(resp.Content.GetProperty<int>("Type"));
            //sign.Height = 10000;
            //sign.Width = 10000;
            //LocalMessageBus.Send(this, new DataChangedMessage(PWDataType.Dashboard));
            //LocalMessageBus.Send(this, new ActiveChange(sign, false));

            sign.Height = height;
            //sign.SignInfomation = signInfo + "  :  " + height.ToString() + " x " + width.ToString() + "  :  " + signType.ToString();
            sign.SignInfomation = height.ToString() + " x " + width.ToString();
            sign.Width = width;
            sign.Type = signType;
            sign.Template.Sign.Width = width;
            sign.Template.Sign.Height = height;
            sign.Template.Sign.SignType = signType;
            var message = sign.Template.Message;
            message.ImageLayer.Height = message.ImageLayer.FitToSign ? sign.Height : sign.Height / 2;
            message.ImageLayer.Width = message.ImageLayer.FitToSign ? sign.Width : sign.Width / 2;
            message.VideoLayer.Height = message.VideoLayer.FitToSign ? sign.Height : sign.Height / 2;
            message.VideoLayer.Width = message.VideoLayer.FitToSign ? sign.Width : sign.Width / 2;
            message.TextLayer.Height = message.TextLayer.FitToSign ? sign.Height : sign.Height / 2;
            message.TextLayer.Width = message.TextLayer.FitToSign ? sign.Width : sign.Width / 2;
            message.DynamicTextLayer.Height = message.DynamicTextLayer.FitToSign ? sign.Height : sign.Height / 2;
            message.DynamicTextLayer.Width = message.DynamicTextLayer.FitToSign ? sign.Width : sign.Width / 2;
            sign.Type = signType;

            ActionHelper.OnConnected();
        }
    }
}
