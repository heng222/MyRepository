//---------------------------------------------------------------------
//
// File: SchedulerConverter.cs
//      
// Description:
//      LibraryFileItem control
//
// Author: Jerry Xu 2008-12-11
//
// Modify History:
//      Jerry Xu 2009-1-14 Update method:ConvertRecurrence(PWRecurrenceInfo recurrence)
//      Jerry Xu 2009-1-21 Update method:ConvertRecurrence(PWRecurrenceInfo recurrence),ConvertWeeklyPattern(PWRecurrenceInfo recurrence)
//      Jerry Xu 2009-1-25 Update method:ConvertWeeklyPattern(PWRecurrenceInfo recurrence)
// Copyright (C) 2008 by Trans-Lux All rights reserved.ConvertRecurrence:(PWRecurrenceInfo recurrence)
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using ProWrite.UFE.Entity;
using ProWrite.Entity.Library;

namespace ProWrite.UFE.Files
{
    public class SchedulerConverter : MemoryLibraryItemConverterBase<SchedulerInfo, ScheduleType>
    {

        public override ScheduleType Convert(SchedulerInfo schedule)
        {
            ScheduleType ufeSchedule = new ScheduleType();
            List<ScheduleItem> items = new List<ScheduleItem>();

#if VERSION_1
            ufeSchedule.Id = schedule.Id;
#else
            ConvertId(schedule, ref ufeSchedule.ContentID);
#endif
            if (schedule.Items != null && schedule.Items.Length > 0)
            {
                foreach (AppointmentInfo item in schedule.Items)
                {
                    if (item.Target != null)
                        items.Add(ConvertScheduleItem(item));
                }
                ufeSchedule.ScheduleItems = items;
            }


            return ufeSchedule;
        }

        /// <summary>
        /// Function: Convert AppointmentInfo to ScheduleItem
        /// Author  : Jerry Xu
        /// Date    : 2008-12-6
        /// </summary>
        /// <param name="appointment">AppointmentInfo</param>
        /// <returns>ScheduleItem</returns>
        private ScheduleItem ConvertScheduleItem(AppointmentInfo appointment)
        {
            ScheduleItem item = new ScheduleItem();

            item.DisplayContent = ConvertLibrary(appointment.Target);
            item.Timing = ConvertAppointmentInfo(appointment);
            return item;
        }

        private ScheduleItemType ConvertType(ProWrite.Core.LibraryType type)
        {
            if (type == ProWrite.Core.LibraryType.Message)
                return ScheduleItemType.FrameObject;
            if (type == ProWrite.Core.LibraryType.TimeSliceGroup)
                return ScheduleItemType.TimeSliceGroup;
            if (type == ProWrite.Core.LibraryType.Playlist)
                return ScheduleItemType.Playlist;
            return ScheduleItemType.FrameObject;
        }

        /// <summary>
        /// Function: Convert MemoryLibraryItem to IncludeFileItem
        /// Author  : Jerry Xu
        /// Date    : 2008-12-6
        /// </summary>
        /// <param name="memory">MemoryLibraryItem</param>
        /// <returns>IncludeFileItem</returns>
        private ScheduleIncludeItem ConvertLibrary(MemoryLibraryItem memory)
        {
            ScheduleIncludeItem item = new ScheduleIncludeItem();

            item.Id = memory.Id;
            item.Type = ConvertType(memory.Type);
            return item;
        }

        /// <summary>
        /// Function: Convert AppointmentInfo to ScheduleInfoType
        /// Author  : Jerry Xu
        /// Date    : 2008-12-6
        /// </summary>
        /// <param name="appointment">AppointmentInfo</param>
        /// <returns>ScheduleInfoType</returns>
        private ScheduleInfoType ConvertAppointmentInfo(AppointmentInfo appointment)
        {
            ScheduleInfoType item = new ScheduleInfoType();
            if (appointment.RecurrenceInfo != null)
            {
                item.Recurrence = ConvertRecurrence(appointment.RecurrenceInfo);
            }

            item.IsAllDayEvent = appointment.AllDay;
            item.IsExact = appointment.ExactTiming;
            item.IsPlayMessageOnce = appointment.PlayMessageOnce;
            item.IsScheduled = true;
            item.StartDay = appointment.Start.ToString("yyyy-MM-dd");
            item.StartTime = appointment.Start.ToString("HH:mm:ss");
            item.StopDay = appointment.End.ToString("yyyy-MM-dd");
            item.StopTime = appointment.End.ToString("HH:mm:ss");


            return item;
        }

        /// <summary>
        /// Function: Convert ScheduleRecurrenceType to PWRecurrenceInfo
        /// Author  : Jerry Xu
        /// Date    : 2008-12-6
        /// </summary>
        /// <param name="recurrence">PWRecurrenceInfo</param>
        /// <returns>ScheduleRecurrenceType</returns>
        private ScheduleRecurrenceType ConvertRecurrence(PWRecurrenceInfo recurrence)
        {
            ScheduleRecurrenceType item = new ScheduleRecurrenceType();
            //TODO:
            if (recurrence.Type == PWRecurrenceType.Daily)
                item.DailyPattern = recurrence.Periodicity;
            if (recurrence.Type == PWRecurrenceType.Weekly)
                item.WeeklyPattern = ConvertWeeklyPattern(recurrence);
            if (recurrence.Range == PWRecurrenceRange.NoEndDate)
                item.NoEndDateRange = true;
            if (recurrence.Range == PWRecurrenceRange.EndByDate)
                item.EndByDateRange = recurrence.End.ToString("yyyy-MM-dd");
            if (recurrence.Range == PWRecurrenceRange.OccurrenceCount)
                item.EndAfterByOccurenceRange = recurrence.OccurrenceCount;

            //item.Pattern = null;
            //item.Range = recurrence.Range;

            return item;
        }

        /// Function: Convert PWRecurrenceInfo... to WeeklyRecurrence
        /// Author  : Jerry Xu
        /// Date    : 2008-12-6
        /// </summary>
        /// <param name="recurrence">PWRecurrenceInfo</param>
        /// <returns>WeeklyRecurrence</returns>
        private WeeklyRecurrence ConvertWeeklyPattern(PWRecurrenceInfo recurrence)
        {
            WeeklyRecurrence item = new WeeklyRecurrence();
            //if(recurrence.w

            int target = 0;
            if ((recurrence.WeekDays & PWWeekDays.Monday) == PWWeekDays.Monday)
                target = (int)WeeklyChoiceType.M;
            if ((recurrence.WeekDays & PWWeekDays.Tuesday) == PWWeekDays.Tuesday)
                target = target | (int)WeeklyChoiceType.T;
            if ((recurrence.WeekDays & PWWeekDays.Wednesday) == PWWeekDays.Wednesday)
                target = target | (int)WeeklyChoiceType.W;
            if ((recurrence.WeekDays & PWWeekDays.Thursday) == PWWeekDays.Thursday)
                target = target | (int)WeeklyChoiceType.TH;
            if ((recurrence.WeekDays & PWWeekDays.Friday) == PWWeekDays.Friday)
                target = target | (int)WeeklyChoiceType.F;
            if ((recurrence.WeekDays & PWWeekDays.Saturday) == PWWeekDays.Saturday)
                target = target | (int)WeeklyChoiceType.S;
            if ((recurrence.WeekDays & PWWeekDays.Sunday) == PWWeekDays.Sunday)
                target = target | (int)WeeklyChoiceType.SU;
            if (target != 0)
                item.DaysChoice = (WeeklyChoiceType)target;
            //item.DaysChoice = (WeeklyChoiceType)Enum.Parse(typeof(WeeklyChoiceType), ((int)recurrence.WeekDays).ToString());
            item.RecurCycle = recurrence.Periodicity;
            return item;
        }

    }
}
