using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading.Tasks;

namespace _04_EventAccessor
{
    

    class Worker
    {
        private EventHandler _handler;
        public event EventHandler WorkDone
        {
            add
            {
                if (_handler == null)
                {
                    _handler += value;
                }
                else
                {
                    Console.WriteLine("Duplicate registration, skipped.");
                }              
            }
            remove { _handler -= value; }
        }

        public virtual void DoWork()
        {
            Console.WriteLine("Work");
            /*
            if (WorkDone != null)
            {
                WorkDone(this, EventArgs.Empty);
            }
            */
            OnWorkDone(EventArgs.Empty);
        }

        protected void OnWorkDone(EventArgs e)
        {
            Console.WriteLine("Work");
            if (_handler != null)
            {
                _handler(this, EventArgs.Empty);
            }
        }
    }
}
