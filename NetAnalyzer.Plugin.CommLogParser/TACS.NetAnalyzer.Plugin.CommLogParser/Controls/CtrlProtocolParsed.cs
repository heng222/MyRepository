using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using NetAnalyzer.Protocol;
using NetAnalyzer.Pcap;

namespace TACS.CommLogParser.Plugin4NetAnalyzer.Controls
{
    partial class CtrlProtocolParsed : UserControl
    {
        public CtrlProtocolParsed(Control hexEditor)
        {
            this.Dock = DockStyle.Fill;
            InitializeComponent();

            // 
            hexEditor.Dock = DockStyle.Fill;
            this.splitContainer1.Panel1.Controls.Add(hexEditor);
        }

        public void SetUserData(RawCapture rawPacket)
        {            
            var packet = Packet.ParsePacket(rawPacket.LinkLayerType, rawPacket.Data);

            // EthernetPacket
            var ep = EthernetPacket.GetEncapsulated(packet);
            if (ep == null) return;

            // IP 
            var ip = IpPacket.GetEncapsulated(packet);
            if (ip == null) return;

            // TCP
            var tcp = TcpPacket.GetEncapsulated(packet);
            if (tcp != null)
            {
                this.txtDescription.Text = string.Join(" ", tcp.PayloadData.Select(p => string.Format("{0:X2}", p)));
                return;
            }

            // UDP
            var udp = UdpPacket.GetEncapsulated(packet);
            if (udp != null)
            {
                this.txtDescription.Text = string.Join(" ", udp.PayloadData.Select(p => string.Format("{0:X2}", p)));
            }            
        }
    }
}
