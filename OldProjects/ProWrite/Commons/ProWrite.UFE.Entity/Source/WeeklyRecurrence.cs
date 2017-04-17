using System;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public struct WeeklyRecurrence
    {
        public WeeklyChoiceType DaysChoice;
        public int RecurCycle;
    }
}
