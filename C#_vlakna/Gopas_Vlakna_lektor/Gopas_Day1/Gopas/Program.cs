using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Gopas
{
    class Program
    {
        static void Main(string[] args)
        {
            //for (var i = 0; i < 10; i++)
            //{
            //    ThreadPool.QueueUserWorkItem(o =>
            //    {
            //        //Thread.Sleep();
            //        for (int j = 0; j < short.MaxValue; j++)
            //        {

            //        }
            //        Console.WriteLine(i);
            //    }, null);
            //    Console.WriteLine(i);
            //}

            //var t = Task.Run(() => { Console.WriteLine("Hello"); return 1; });
            var pole = Enumerable.Range(1, 128).ToArray();
            var sw = Stopwatch.StartNew();
            //for (var i = 0; i < pole.Length; i++)
            //{
            //    pole[i] = Sum(pole[i], pole[i]);
            //}
            //pole = pole.AsParallel()
            //    //.WithCancellation()
            //    .WithDegreeOfParallelism(3)
            //    .WithExecutionMode(ParallelExecutionMode.ForceParallelism)
            //    .WithMergeOptions(ParallelMergeOptions.FullyBuffered)
            //    .Select(x => Sum(x, x))
            //    .ToArray();

            //Parallel.Invoke(
            //    () => Console.WriteLine("1"),
            //    () => Console.WriteLine("2"),
            //    () => Console.WriteLine("3"),
            //    () => Console.WriteLine("4"));

            Parallel.For(0, 256, (i, pls) =>
            //for (var i = 0; i < 10; i++)
            {
                Console.WriteLine(i);
            });

            var sum = 0;
            Parallel.For(0, pole.Length,
                () => 0,
                (i, pls, local) => local + pole[i],
                local => Interlocked.Add(ref sum, local));
            Console.WriteLine(sum);
            return;
            //    i =>
            //{
            //    sum = sum + pole[i];
            //});
            //Console.WriteLine(sum);

            //using (var cts = new CancellationTokenSource())
            //{
            //    var token = cts.Token;
            //    var tasks = new Task[pole.Length];
            //    for (var i = 0; i < pole.Length; i++)
            //    {
            //        tasks[i] = Task.Factory.StartNew(o =>
            //        {
            //            //token.ThrowIfCancellationRequested();
            //            if (token.IsCancellationRequested)
            //                return;
            //            var index = (int)o;
            //            var sum = Sum(pole[index], pole[index]);
            //            if (sum > 40)
            //            {
            //                cts.Cancel();
            //            }
            //            pole[index] = sum;
            //        }, i, token);
            //    }
            //    Task.WaitAll(tasks);
            //    Console.WriteLine(string.Join(", ", pole));
            //}
            Console.WriteLine(SumArray(pole));
            Console.WriteLine(sw.Elapsed);
            //var t2 = Task.Factory.StartNew();
            //var t3 = new Task<int>();
            //t3.Start();

            Console.ReadLine();
        }

        static int SumArray(int[] arr)
        {
            switch (arr.Length)
            {
                case 1:
                    return arr[0];
                case 2:
                    return Sum(arr[0], arr[1]);
                default:
                    var left = arr.Take(arr.Length / 2).ToArray();
                    var right = arr.Skip(arr.Length / 2).ToArray();
                    var leftTask = Task.Run(() => SumArray(left));
                    var rightTask = Task.Run(() => SumArray(right));
                    Task.WaitAll(leftTask, rightTask);
                    return Sum(leftTask.Result, rightTask.Result);
            }
        }

        static int Sum(int a, int b)
        {
            Thread.SpinWait(39999999);
            return a + b;
        }
    }
}
