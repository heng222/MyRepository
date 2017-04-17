using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Core;
using DevExpress.XtraEditors.Controls;
using ProWrite.UI.Controls.Common;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls.Editor
{
    /// <summary>
    /// add by Terry
    /// </summary>
    public partial class DynamicLayerFormatSelectionForm : DevExpress.XtraEditors.XtraForm
    {
        private bool IsTime;
        private ProWrite.Core.TimeFormat _oldSelectTimeFormat;
        private string _oldStrFormat;
        private TempFormat _oldSelectTempFormat;

        public delegate void SetShapeTimeText(string text, ProWrite.Core.TimeFormat timeFormat);
        public event SetShapeTimeText UpdateShapeText;

        public delegate void SetShapeTempText(string text, TempFormat tempFormat);
        public event SetShapeTempText UpdateShapeTempText;

        public DynamicLayerFormatSelectionForm(bool isTime, string strFormat, ProWrite.Core.TimeFormat timeformat)
        {
            InitializeComponent();
            IsTime = isTime;

            _oldSelectTimeFormat = timeformat;
            _oldStrFormat = strFormat;

            if (IsTime)
                this.Text = "Time Date Format";
            else
                this.Text = "Temperature Format";
            Init();
        }

        public DynamicLayerFormatSelectionForm(bool isTime, string strFormat, TempFormat format)
        {
            InitializeComponent();
            IsTime = isTime;

            _oldStrFormat = strFormat;
            _oldSelectTempFormat = format;

            if (IsTime)
                this.Text = "Time Date Format";
            else
                this.Text = "Temperature Format";
            Init();
        }

        private void Init()
        {
            rdogrpFormat.Properties.Items.Clear();
            List<RadioGroupItem> obj = new List<RadioGroupItem>();
            if (IsTime)
            {
                string[] str = Enum.GetNames(typeof(ProWrite.Core.TimeFormat));
                for (int i = 0; i < str.Length; i++)
                {
                    obj.Add(new RadioGroupItem(str[i],
                        EnumHelper.GetEnumDescription(
                            (ProWrite.Core.TimeFormat)Enum.ToObject(typeof(ProWrite.Core.TimeFormat), i + 1)).ToString()));
                }
            }
            else
            {
                string[] str = Enum.GetNames(typeof(TempFormat));
                for (int i = 0; i < str.Length; i++)
                {
                    obj.Add(new RadioGroupItem(str[i],
                        EnumHelper.GetEnumDescription(
                            (TempFormat)Enum.ToObject(typeof(TempFormat), i)).ToString()));
                }
            }
            //string [] ss= Enum.getv(typeof(ProWrite.Core.TimeFormat));

            this.rdogrpFormat.Properties.Items.AddRange(obj.ToArray());
            if (IsTime)
                this.rdogrpFormat.SelectedIndex = Convert.ToInt32(_oldSelectTimeFormat-1);
            else
                this.rdogrpFormat.SelectedIndex = Convert.ToInt32(_oldSelectTempFormat);
            //SetFormat();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (rdogrpFormat.SelectedIndex < 0)
            {
                string str = "";
                if (IsTime)
                    str = Resources.Resource.GetFormatString(Resources.Resource.Strings.ShapSelectFormatFirst, "time");
                else
                    str = Resources.Resource.GetFormatString(Resources.Resource.Strings.ShapSelectFormatFirst, "temperature");
                MsgBox.Warning(str);
                return;
            }
            SetFormat();
            this.Close();
        }

        private ProWrite.Core.TimeFormat _selectTimeFormat;
        public ProWrite.Core.TimeFormat SelectTimeFormat
        {
            get { return _selectTimeFormat; }
            set { _selectTimeFormat = value; }
        }

        private string _strTime;
        public string StrTime
        {
            get { return _strTime; }
            set { _strTime = value; }
        }

        private TempFormat _selectTempeFormat;
        public TempFormat SelectTempeFormat
        {
            get { return _selectTempeFormat; }
            set { _selectTempeFormat = value; }
        }

        private string _strTemp;
        public string StrTemp
        {
            get { return _strTemp; }
            set { _strTemp = value; }
        }

        private void rdogrpFormat_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetFormat();
        }

        private void SetFormat()
        {
            if (rdogrpFormat.SelectedIndex < 0)
                return;
            string selectItem = rdogrpFormat.Properties.Items[rdogrpFormat.SelectedIndex].Value.ToString();

            if (IsTime)
            {
                SelectTimeFormat = (ProWrite.Core.TimeFormat)Enum.Parse(typeof(ProWrite.Core.TimeFormat), selectItem);
                StrTime = ShapeTime.GetTimeByTimeFormat(SelectTimeFormat);
                //MsgBox.Warning(StrTime);
            }
            else
            {
                SelectTempeFormat = (TempFormat)Enum.Parse(typeof(TempFormat), selectItem);
                StrTemp = ShapeTemp.GetTempByFormat(SelectTempeFormat);
                //MsgBox.Warning(StrTemp);
            }
            if (IsTime && UpdateShapeText != null)
                UpdateShapeText(StrTime, SelectTimeFormat);
            if (!IsTime && UpdateShapeTempText != null)
                UpdateShapeTempText(StrTemp, SelectTempeFormat);
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            if (IsTime)
                UpdateShapeText(_oldStrFormat, _oldSelectTimeFormat);
            else
                UpdateShapeTempText(_oldStrFormat, _oldSelectTempFormat);
            DialogResult = DialogResult.Cancel;
            Close();
        }
    }
}