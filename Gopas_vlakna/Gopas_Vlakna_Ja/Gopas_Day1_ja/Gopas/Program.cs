using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace Gopas
{
    class Program
    {
        static void Main(string[] args)
        {
            //Operation();
            //OperationParalel2();
            //OperationParalel3();
            //Plinq();
            //ParallelFor();

            MapReduce();
        }

        static void MapReduce()
        {
            var sum = 0;
            var pole = Enumerable.Range(1, 128).ToArray();
            var sw = Stopwatch.StartNew();

            Parallel.For(0,pole.Length,()=>0,(i, pls, local) = LocalDataStoreSlot + pole[i]), 
                local => Interlocked.Add(ref sum, local));
            //local => sum = sum + local // ne thread safe operace.
        }

        static void ParallelFor()
        {
            var sum = 0;
            var pole = Enumerable.Range(1, 128).ToArray();
            var sw = Stopwatch.StartNew();

            var options = new ParallelOptions()
            {
                MaxDegreeOfParallelism = 4
            };
            Parallel.ForEach(pole /* sequence */, options,
            () => 0, // The local initial partial result
                     // The loop body
            (x, loopState, partialResult) => {
                return Sum(x, x) + partialResult;
            },
            // The final step of each local context
            (localPartialSum) => {
                // Protect access to shared result
                /*
                lock (lockObject)
                            {
                                
                            }
                */
                sum += localPartialSum;
            });

            Console.WriteLine(sw.ElapsedMilliseconds);
            Console.WriteLine(string.Join(", ", pole));
            Console.WriteLine("Sum all = " + sum);
            Console.ReadLine();
        }

        static void Plinq()
        {
            var pole = Enumerable.Range(1, 128).ToArray();
            var sw = Stopwatch.StartNew();
            pole = pole.AsParallel().Select(x => Sum(x,x)).ToArray();
        }

        static void OperationParalel3()
        {
            var pole = Enumerable.Range(1, 128).ToArray();
            var sw = Stopwatch.StartNew();

            using (var cts = new CancellationTokenSource())
            {
                var token = cts.Token;
                var tasks = new Task[pole.Length];
                for (int i = 0; i < pole.Length; i++)
                {
                    tasks[i] = Task.Factory.StartNew(o =>
                    {
                        if (token.IsCancellationRequested)
                            return;
                        var index = (int)o;
                        var sumPrev = 0;
                        if (index >= 1)
                        {
                            sumPrev = Sum(pole[index - 1], pole[index - 1]);
                        }
                        var sumIndex = Sum(pole[index], pole[index]);
                        /*
                        if (curSum > 40)
                        {
                            cts.Cancel();
                        }
                        */
                        pole[index] = sumPrev + sumIndex;
                    }, i, token);
                }
                Task.WaitAll(tasks);
                Console.WriteLine(sw.ElapsedMilliseconds);
                Console.WriteLine(string.Join(", ", pole));
                Console.WriteLine("Sum all = " + pole[pole.Length-1]);
                Console.ReadLine();
            }
        }

        public static void OperationParalel2()
        {
            var pole = Enumerable.Range(1, 128).ToArray();
            var sw = Stopwatch.StartNew();

            //using -> protoze je disposable musim ho ukoncit.
            //Task je take disposable ale 
            using (var cts = new CancellationTokenSource())
            {
                var token = cts.Token;
                var tasks = new Task[pole.Length];
                for (int i = 0; i < pole.Length; i++)
                {
                    //Factory -> nemusim resit pocet procesoru -> uz si to vyresi sam Task.Factory
                    tasks[i] = Task.Factory.StartNew(o =>
                    {
                            //token.ThrowIfCancellationRequested();
                            //jinak neskonci
                            if (token.IsCancellationRequested)
                            return;
                            //index -> odstraneni uzaveru - ArrayOutOfBoundException.
                            var index = (int)o;
                        var sum = Sum(pole[index], pole[index]);
                        if (sum > 40)
                        {
                            //cts.Cancel();
                        }
                        pole[index] = sum;
                    }, i, token);
                }
                
                Task.WaitAll(tasks);
            }

            /*
            foreach (var task in tasks)
            {
                task.Wait();
            }
            */

            /*
             * 
            for (int i = 0; i < sumList.Count; i++)
            {
                pole[i] = sumList[i];
            }
            */

            Console.WriteLine(sw.ElapsedMilliseconds);
            Console.WriteLine(string.Join(", ", pole));
            Console.WriteLine("Sum all = " + pole.Sum()); //16512 sum
            Console.ReadLine();
        }

        static void OperationParalel()
        {
            var pole = Enumerable.Range(1, 128).ToArray();
            List<int> sumList = new List<int>();
            var sw = Stopwatch.StartNew();

            for (int i = 0; i < pole.Length; i++)
            {
                var t = Task.Run(() =>
                {
                    return Sum(pole[i], pole[i]);
                });
                sumList.Add(t.Result);
            }
            for (int i = 0; i < sumList.Count; i++)
            {
                pole[i] = sumList[i];
            }

            Console.WriteLine(sw.ElapsedMilliseconds);
            Console.ReadLine();
        }


        static void Operation()
        {
            var pole = Enumerable.Range(1, 128).ToArray();
            var sw = Stopwatch.StartNew();

            for (int i = 0; i < pole.Length; i++)
            {
                pole[i] = Sum(pole[i], pole[i]);
            }
            Console.WriteLine(sw.ElapsedMilliseconds);
            Console.ReadLine();
        }

        static void Tasky()
        {
            var t = Task.Run(() =>
            {
                Console.WriteLine("Hello");
                return 1;
            }
            );

            var ret = t.Result;
            t.Wait();


            /*
            var t2 = Task.Factory.StartNew();
            var t3 = new Task<int>();
            t3.Start();
            */
        }

        static int Sum(int a, int b)
        {
            //Thread.Sleep(2000);
            //Thread.SpinWait(2000);
            Thread.SpinWait(100000);
            Thread.SpinWait(1000000); // 6407  / 2257
            return a + b;
        }

        static void Closures()
        {
            for (int i = 0; i < 10; i++)
            {
                ThreadPool.QueueUserWorkItem(o =>
                {
                    for (int j = 0; i < short.MaxValue; j++)
                    {

                    }
                    Console.WriteLine(i);
                }, null);
                Console.WriteLine(i);
            }

            Console.ReadLine();
        }


        /*
        for (int i = 0; i < 500; i++)
        {
            ThreadPool.QueueUserWorkItem(o =>
            Thread.Sleep(-1)  //nedela nic           
            , null);
        Console.WriteLine(i);
            ///t.Start(null);
        }
        */
    }
}

