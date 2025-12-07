using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _03_UsingEvents
{
    class IntListWithChangedEvent: List<int>
    {
        public event ChangeEventHandler2 Changed;

        protected virtual void OnChanged(ChangedEventArgs e)
        {
            if (Changed != null)
            {
                Changed(this);
                //Changed(this,e);
            }
        }

        new public void Add(int value)
        {
            base.Add(value);
            //OnChanged(EventArgs.Empty);
            OnChanged(new ChangedEventArgs(IntListWIthChangedEventState.Added555));
        }

        new public void Clear()
        {
            base.Clear();
            // OnChanged(EventArgs.Empty);
            OnChanged(new ChangedEventArgs(IntListWIthChangedEventState.Cleared));
        }

        // indexer, pouziti this je zde standardni konvence...
        new public int this[int index]
        {
            set
            {
                base[index] = value;
                //OnChanged(EventArgs.Empty);
                OnChanged(new ChangedEventArgs(IntListWIthChangedEventState.Changed));
            }
        }
    }
}
