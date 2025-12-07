using System;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;

namespace Gopsas_Day3
{

    class SimpleLock
    {
        public void Enter()
        {
            var tName = Task.CurrentId;
            string s = "Task nr. " + tName + " enter";
            Console.WriteLine(s);
            lock (this)
            {
                for (int i = 0; i < 100; i++)
                {                    
                    Console.WriteLine(tName + ", cycle: " + i);
                }
                Exit();
            }           
        }

        public void Exit()
        {
            var tName = Task.CurrentId;
            Console.WriteLine(tName + " done");
        }

    }

    class Program
    {
        static void Main(string[] args)
        {
            //volatileExample();
            //interlocaExample();    

            Parallel.For(0, 60000, i =>
            {
                CountdownSemaphore(i);                
            }); // Parallel.For            

            /*
            Task.Run(() => Countdown(0));
            Task.Run(() => Countdown(1));
            Task.Run(() => Countdown(2));
            Task.Run(() => Countdown(3));
            */

            Console.ReadLine();            
        }

        public static void CountdownSemaphore(int count)
        {
            var tName = Task.CurrentId;          
            //semaphore je plne otevreny!
            using (var sem = new Semaphore(10, 10))
            {
                //   Signal();                  
                Console.WriteLine(tName + " semaphore");
            }            
        }

        public static void Countdown(int count)
        {
            var tName = Task.CurrentId;
            Console.WriteLine(tName + " start countdown");
            using (var m = new Mutex(true, "@Global\test"))
            {
                Signal();
                if (count == 0)
                {
                    m.WaitOne();
                }
                if (count == 3)
                {
                    m.ReleaseMutex();
                }
            }
            Console.WriteLine(tName + " done countdown");
        }

        public static void Signal()
        {
            var tName = Task.CurrentId;
            Console.WriteLine(tName + " singal");
        }

        static void SimpleLockExample()
        {
            SimpleLock s1 = new SimpleLock();
            SimpleLock s2 = new SimpleLock();

            Task.Run(() => s1.Enter());
            Thread.Sleep(10);
            Task.Run(() => s1.Enter());
            Console.ReadLine();
        }

        static void interlocaExample()
        {
            Interlocked.CompareExchange(ref i, 10, 10);
            Debugger.Launch();
            Console.ReadLine();
        }

        /*volatile*/ static int i;
        static void volatileExample()
        {
            var local = Volatile.Read(ref i);
            Console.WriteLine(local);
        }
    }
}
