//using System;
//using System.Text;
//using System.Collections.Generic;
//using System.Linq;
//using NUnit.Framework;
//using ProWrite.UFE.Entity;
//using System.IO;

//namespace ProWrite.UFE.Test
//{
//    /// <summary>
//    /// Summary description for UFEEntityTest
//    /// </summary>
//    [TestFixture]
//    public class UFEEntityTest
//    {

//        [Test]
//        public void Test1()
//        {
//            GenerateMessage();
//            GenerateTimesliceGroup();
//            GeneratePlaylist();
//            GenerateSchedule();
//        }

//        private void GenerateMessage()
//        {
//            var msg = new FrameObjectType
//            {
//                Length = 60,
//                EmphasisEffect = new EmphasisEffectType
//                {
//                    Name = EmphasisType.BIJOU,
//                    Length = 60,
//                    EffectSpeed = 0,
//                },
//            };

//            msg.Contents = new List<FrameContentType>();

//            for (int i = 1; i < 6; i++)
//            {
//                var layer = new FrameContentType
//                {
//                    Type = ContentType.JPEG,
//                    Bounds = new Rectangle { TopLeft = new Point { X = 0, Y = 0 }, BottomRight = new Point { X = 50, Y = 50 } },
//                    StartTime = 3,
//                    Length = 4,
//                    FileName = "Test" + i.ToString() + ".jpg",

//                    EntryEffect = new TransitionEffectType
//                    {
//                        Name = TransitionType.FILTER,
//                        Length = 3,
//                        Params = new Parameter[]
//                        {
//                            new Parameter{
//                                 Name = "Width",
//                                 Value = "10",
//                            },

//                            new Parameter{
//                                 Name = "Hight",
//                                 Value = "10",
//                            },
//                        },
//                    },
//                    EmphasisEffect = new EmphasisEffectType
//                    {
//                        Name = EmphasisType.SNOW,
//                        Length = 12,
//                        Params = new Parameter[]{
//                            new Parameter{
//                                 Name = "Color",
//                                 Value = "0xFFFFFF",
//                            },

//                            new Parameter{
//                                 Name = "Rate",
//                                 Value = "12",
//                            },

//                             new Parameter{
//                                 Name = "Amount",
//                                 Value = "0.15",
//                            },
//                        },
//                    },
//                    ExitEffect = new TransitionEffectType
//                    {
//                        Name = TransitionType.BLACKHOLE,
//                        Length = 4,
//                    },
//                    ScrollEffect = new ScrollEffectType
//                    {
//                        IsScrolling = true,
//                        Direction = ScrollDirectionType.UP,
//                        Speed = 12,
//                        Content = new ScrollContentType
//                        {
//                            Item = new TextType
//                            {
//                                DisplayText = "Hello ProWrite",
//                                FontInfo = new FontInfoType
//                                {
//                                     Font = "PL6CAPBD",
//                                     //FontColor = 255,
//                                     FontKerning = 1,
//                                     FontLead = 3,
//                                     FontSize = 12,
//                                },
//                            },
//                        },
//                    },
//                };

//                msg.Contents.Add(layer);
//            }

//            ProWrite.Core.Serialiser<FrameObjectType> ser = ProWrite.Core.Serialiser<FrameObjectType>.Xml;

//            using (MemoryStream stream = new MemoryStream())
//            {
//                ser.Serialize(msg, stream);
//                stream.Position = 0;
//                using (StreamReader reader = new StreamReader(stream))
//                {
//                    Console.WriteLine(reader.ReadToEnd());
//                }
//            }
//            ser.Serialize(msg, "d:\\FO_Test.xml");

//        }

//        private void GenerateTimesliceGroup()
//        {
//            var sliceGroup = new TimeSliceGroupType
//            {
//               Duration = 12,
//            };

//            sliceGroup.Contents = new List<TimeSliceGroupIncludeItem>();

//            //var array = Enum.GetValues(typeof(IncludeFileType));
//            for (int i = 1; i < 6; i++)
//            {
//                var msg = new TimeSliceGroupIncludeItem
//                {
//                    Type = TimeSliceGroupItemType.FrameObject,
//                };

//                sliceGroup.Contents.Add(msg);
//            }

//            ProWrite.Core.Serialiser<TimeSliceGroupType> ser = ProWrite.Core.Serialiser<TimeSliceGroupType>.Xml;

            
//            ser.Serialize(sliceGroup, "d:\\TSG_Test.xml");

//        }

//        private void GeneratePlaylist()
//        {
//            var sliceGroup = new PlaylistType
//            {
//                Duration = 60,
//            };

//            sliceGroup.Contents = new List<PlaylistIncludeItem>();

//            var array = new PlaylistItemType[]
//            {
//                PlaylistItemType.FrameObject,
//                PlaylistItemType.TimeSliceGroup,
//                PlaylistItemType.Playlist,
//            };
//            foreach(var type in array)
//            {
//                var item = new PlaylistIncludeItem
//                {
//                    Type = type,
//                };

//                sliceGroup.Contents.Add(item);
//            }

//            ProWrite.Core.Serialiser<PlaylistType> ser = ProWrite.Core.Serialiser<PlaylistType>.Xml;

//            ser.Serialize(sliceGroup, "d:\\Playlist_Test.xml");

//        }

//        private void GenerateSchedule()
//        {
//            var schedule = new ScheduleType();

//            schedule.ScheduleItems = new List<ScheduleItem>();

//            var file = new ScheduleIncludeItem
//            {
//                Type = ScheduleItemType.FrameObject,
//            };

//            var recurrence = new ScheduleRecurrenceType 
//            {
//                DailyPattern = 1,
//                NoEndDateRange = true,
//            };

//            var timing = new ScheduleInfoType
//            {
//                StartDay = "2008-12-5",
//                StopDay = "2008-12-6",
//                StartTime = "08:30:00",
//                StopTime = "09:00:00",
//                IsExact = true,
//                IsScheduled = true,
//                  //= WeeklyChoiceType.F | WeeklyChoiceType.M,
//                 IsAllDayEvent = false,
//                  Recurrence = recurrence,
//            };

//            var item = new ScheduleItem
//            {
//                 Timing = timing,
//                 DisplayContent = file,
//            };

//            schedule.ScheduleItems.Add(item);


//            file = new ScheduleIncludeItem
//            {
//                Type = ScheduleItemType.TimeSliceGroup,
//            };

//            var weeklyRecurrence = new WeeklyRecurrence
//            {
//                DaysChoice = WeeklyChoiceType.F | WeeklyChoiceType.M | WeeklyChoiceType.S,
//                RecurCycle = 1,
//            };

//            recurrence = new ScheduleRecurrenceType
//            {
//                WeeklyPattern = weeklyRecurrence,
//                EndByDateRange = "2008-12-14",
//            };

//            timing = new ScheduleInfoType
//            {
//                StartDay = "2008-12-5",
//                StopDay = "2008-12-6",
//                StartTime = "08:30:00",
//                StopTime = "09:00:00",
//                IsExact = true,
//                IsScheduled = true,
//                IsAllDayEvent = false,
//                Recurrence = recurrence,
//                //DaysChoice = WeeklyChoiceType.F | WeeklyChoiceType.M | WeeklyChoiceType.S,
//            };

//            item = new ScheduleItem
//            {
//                Timing = timing,
//                DisplayContent = file,
//            };

//            schedule.ScheduleItems.Add(item);


//            file = new ScheduleIncludeItem
//            {
//                Type = ScheduleItemType.Playlist,
//            };

//            weeklyRecurrence = new WeeklyRecurrence
//            {
//                DaysChoice = WeeklyChoiceType.MTWTHFSSU,
//                RecurCycle = 1,
//            };

//            recurrence = new ScheduleRecurrenceType
//            {
//                WeeklyPattern = weeklyRecurrence,
//                EndAfterByOccurenceRange = 5,
//            };

//            timing = new ScheduleInfoType
//            {
//                StartDay = "2008-12-5",
//                StopDay = "2008-12-6",
//                StartTime = "08:30:00",
//                StopTime = "09:00:00",
//                IsExact = true,
//                IsScheduled = true,
//                Recurrence = recurrence,
//            };

//            item = new ScheduleItem
//            {
//                Timing = timing,
//                DisplayContent = file,
//            };

//            schedule.ScheduleItems.Add(item);


//            ProWrite.Core.Serialiser<ScheduleType> ser = ProWrite.Core.Serialiser<ScheduleType>.Xml;

//            ser.Serialize(schedule, "d:\\Schedule_Test.xml");
//        }

//    }
//}
