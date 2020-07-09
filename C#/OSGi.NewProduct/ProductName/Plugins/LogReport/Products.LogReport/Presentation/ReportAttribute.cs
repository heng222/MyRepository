using System;

namespace Products.LogReport
{
    [AttributeUsage(AttributeTargets.Class, Inherited = false, AllowMultiple = false)]
    class ReportAttribute : Attribute
    {
        public string DisplayName { get; private set; }
        public string ReportName { get; private set; }
        public string ReportURL { get; private set; }

        public int Order { get; set; }

        public ReportAttribute(string displayName, string reportName, string reportUrl)
        {
            this.DisplayName = displayName;
            this.ReportName = reportName;
            this.ReportURL = reportUrl;
        }
    }
}
