using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace WpfApplication
{
    /// <summary>
    /// 列车动态信息类
    /// </summary>
    public class TrainInfo : INotifyPropertyChanged
    {
        /// <summary>
        /// 内容变更通知事件
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;
        private void OnPropertyChanged(string name)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
        }

        private string _trainSetId;
        /// <summary>
        /// 车组号
        /// </summary>
        public string TrainSetId
        {
            get { return _trainSetId; }
            set
            {
                if (_trainSetId != value)
                {
                    _trainSetId = value;
                    OnPropertyChanged("TrainSetId");
                }
            }
        }

        private UInt16 _tableId;
        /// <summary>
        /// 表号
        /// </summary>
        public UInt16 TableId
        {
            get { return _tableId; }
            set
            {
                if (_tableId != value)
                {
                    _tableId = value;
                    OnPropertyChanged("TableId");
                }
            }
        }

        private UInt16 _tripNo;
        /// <summary>
        /// 车次号
        /// </summary>
        public UInt16 TripNo
        {
            get { return _tripNo; }
            set
            {
                if (_tripNo != value)
                {
                    _tripNo = value;
                    OnPropertyChanged("TripNo");
                }
            }
        }

        private TimeSpan _earlyTime;
        /// <summary>
        /// 计划偏离
        /// </summary>
        public TimeSpan EarlyTime
        {
            get { return _earlyTime; }
            set
            {
                if (_earlyTime != value)
                {
                    _earlyTime = value;
                    OnPropertyChanged("EarlyTime");
                }
            }
        }

        private DateTime _startTime;
        /// <summary>
        /// 计划发点
        /// </summary>
        public DateTime StartTime
        {
            get { return _startTime; }
            set
            {
                if (_startTime != value)
                {
                    _startTime = value;
                    OnPropertyChanged("StartTime");
                }
            }
        }

        private DateTime _arriveTime;
        /// <summary>
        /// 计划到点
        /// </summary>
        public DateTime ArriveTime
        {
            get { return _arriveTime; }
            set
            {
                if (_arriveTime != value)
                {
                    _arriveTime = value;
                    OnPropertyChanged("ArriveTime");
                }
            }
        }

        private string _platName;
        /// <summary>
        /// 站台名称
        /// </summary>
        public string PlatName
        {
            get { return _platName; }
            set
            {
                if (_platName != value)
                {
                    _platName = value;
                    OnPropertyChanged("PlatName");
                }
            }
        }

        private string _sectionName;
        /// <summary>
        /// 区段名称
        /// </summary>
        public string SectionName
        {
            get { return _sectionName; }
            set
            {
                if (_sectionName != value)
                {
                    _sectionName = value;
                    OnPropertyChanged("SectionName");
                }
            }
        }

        private string _driverMode;
        /// <summary>
        /// 驾驶模式
        /// </summary>
        public string DriverMode
        {
            get { return _driverMode; }
            set
            {
                if (_driverMode != value)
                {
                    _driverMode = value;
                    OnPropertyChanged("DriverMode");
                }
            }
        }

        private string _runGrade;
        /// <summary>
        /// 运行等级
        /// </summary>
        public string RunGrade
        {
            get { return _runGrade; }
            set
            {
                if (_runGrade != value)
                {
                    _runGrade = value;
                    OnPropertyChanged("RunGrade");
                }
            }
        }

        private UInt16 _driverId;
        /// <summary>
        /// 司机编号
        /// </summary>
        public UInt16 DriverId
        {
            get { return _driverId; }
            set
            {
                if (_driverId != value)
                {
                    _driverId = value;
                    OnPropertyChanged("DriverId");
                }
            }
        }

        private string _serverType;
        /// <summary>
        /// 运营类型
        /// </summary>
        public string ServerType
        {
            get { return _serverType; }
            set
            {
                if (_serverType != value)
                {
                    _serverType = value;
                    OnPropertyChanged("ServerType");
                }
            }
        }

        private PostionType _trainPostion;
        /// <summary>
        /// 列车运行类型：上行，下行，未知方向，车辆段
        /// </summary>
        public PostionType TrainPostion
        {
            get { return _trainPostion; }
            set
            {
                if (_trainPostion != value)
                {
                    _trainPostion = value;
                    OnPropertyChanged("TrainPostion");
                }
            }
        }

        private bool _isStopped;
        /// <summary>
        /// 是否停准
        /// </summary>
        public bool IsStopped
        {
            get { return _isStopped; }
            set
            {
                if (_isStopped != value)
                {
                    _isStopped = value;
                    OnPropertyChanged("IsStopped");
                }
            }
        }

        private bool _isSkiped;
        /// <summary>
        /// 跳停状态
        /// </summary>        
        public bool IsSkiped
        {
            get { return _isSkiped; }
            set
            {
                if (_isSkiped != value)
                {
                    _isSkiped = value;
                    OnPropertyChanged("IsSkiped");
                }
            }
        }

        private double _relativeLoc;
        /// <summary>
        /// 公里标
        /// </summary>
        public double RelativeLoc
        {
            get { return _relativeLoc; }
            set
            {
                if (_relativeLoc != value)
                {
                    _relativeLoc = value;
                    //OnPropertyChanged("RelativeLoc");
                }
            }
        }
    }
}
