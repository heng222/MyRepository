using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Settings;
using System.Reflection;
using System.Linq;

namespace ProWrite.UI.Controls.Options
{
    public interface IView
    {
        Control Panel { get; }

        void UpdateData();
        void Cancel();

        bool HasCanceled { get; }
        
    }

    public interface IView<TData>:IView
    {
        void Bind(TData data);
    }


    public class ViewBase : UserControl,IView
    {
        public Control Panel { get { return this; } }


        protected virtual bool ValidateData()
        {
            return true;
        }

        public void UpdateData()
        {
            if (!HasCanceled 
                && ValidateData())
                DoUpdateData();
        }

        protected virtual void DoUpdateData() { }
        public bool HasCanceled { get; private set; }

        public virtual void Cancel()
        {
            HasCanceled = true;
        }
    }

    public class ViewBase<TData> : ViewBase, IView<TData>
    {
        protected TData _data;

        public void Bind(TData data)
        {
            _data = data;
        }

        protected virtual void DoBind() { }
    }
}
