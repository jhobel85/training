using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _04_EventAccessor
{
    class ExtendedWorker : Worker
    {

        //z potomka mohu volat delegata definovaneho v materske tride
        public override void DoWork()
        {
            Console.WriteLine("My Extended Work");
            base.OnWorkDone(EventArgs.Empty);
        }

        
    }
}
