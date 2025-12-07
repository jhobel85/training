using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _03_UsingEvents
{
    public enum IntListWIthChangedEventState
    {
        Added555,
        Changed,
        Cleared
    }
    public class ChangedEventArgs: EventArgs
    {
        public IntListWIthChangedEventState ChangedState { get; set; }

        public ChangedEventArgs(IntListWIthChangedEventState changedState)
        {
            this.ChangedState = changedState;
        }


    }
}
