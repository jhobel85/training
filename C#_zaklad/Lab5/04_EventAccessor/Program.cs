using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _04_EventAccessor
{
    class Program
    {
        static void Main(string[] args)
        {
            /*
            Worker worker = new Worker();
            worker.WorkDone += worker_WorkDone;
            worker.WorkDone += worker_WorkDone;
            worker.WorkDone += worker_WorkDone;
            worker.DoWork();
            */
            ExtendedWorker exWorker = new ExtendedWorker();
            exWorker.WorkDone += worker_WorkDone;
            exWorker.DoWork();
        }

        static void worker_WorkDone(object sender, EventArgs e)
        {
            Console.WriteLine("Done");
        }
    }
}
