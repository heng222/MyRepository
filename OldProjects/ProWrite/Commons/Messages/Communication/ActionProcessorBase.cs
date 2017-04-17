using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public abstract class ActionProcessorBase<TAction, TPacket> : IActionProcessor<TAction, TPacket>
        where TPacket : IPacket
        where TAction : IAction<TPacket>
    {
        public ActionProcessorBase()
        {
            Actions = new List<TAction>();
        }

        public virtual void Init() { }
        public virtual void Destroy() { }
        public List<TAction> Actions { get; private set; }
        public abstract void Process(TPacket packet);

        List<IAction> IActionProcessor.Actions
        {
            get { return new List<IAction>(Actions.Cast<IAction>()); }
        }

        void IActionProcessor.Process(IPacket packet)
        {
            Process((TPacket)packet);
        }
    }

}
