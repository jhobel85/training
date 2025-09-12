using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Management.Instrumentation;
using System.Net;
using System.Net.Http.Headers;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices.ComTypes;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Gopas
{
    class Program
    {
        static async Task Main(string[] args)
        {
#if false

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

            //Parallel.For(0, 256, (i, pls) =>
            ////for (var i = 0; i < 10; i++)
            //{
            //    Console.WriteLine(i);
            //});

            //var sum = 0;
            //Parallel.For(0, pole.Length,
            //    () => 0,
            //    (i, pls, local) => local + pole[i],
            //    // local => sum = sum + local
            //    local => Interlocked.Add(ref sum, local));
            //Console.WriteLine(sum);
            //Debugger.Launch()
            //return;
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
            //Console.WriteLine(SumArray(pole));
            //Console.WriteLine(sw.Elapsed);
            //var t2 = Task.Factory.StartNew();
            //var t3 = new Task<int>();
            //t3.Start();

            //var a = 10;
            //var b = 20;
            //PFuncs(
            //    () => Sum(a, b), 
            //    () => Sum(a, b));

            //Timer timer = null;
            //timer = new Timer(o =>
            //{
            //    Console.WriteLine(DateTime.UtcNow);
            //    timer.Change(2000, -1);
            //}, null, 0, -1);

#endif
            ServicePointManager.DefaultConnectionLimit = int.MaxValue;
            //for (var i = 0; i < 1000; i++)
            //{
            //    var request = WebRequest.CreateHttp("https://www.bing.com");
            //    request.BeginGetResponse(ar =>
            //    {
            //        var response = request.EndGetResponse(ar);
            //        var source = response.GetResponseStream();
            //        var destination = new MemoryStream();
            //        ReadStream(source, destination, () =>
            //        {
            //            Console.WriteLine("Done");
            //            destination.Dispose();
            //            source.Dispose();
            //            response.Dispose();
            //        }, ex =>
            //        {
            //            Console.WriteLine($"ERROR: {ex}");
            //            destination.Dispose();
            //            source.Dispose();
            //            response.Dispose();
            //        });
            //    }, null);
            //    Console.WriteLine(i);
            //}

            //var tasks = new Task[1000];
            //for (var i = 0; i < tasks.Length; i++)
            //{
            //    tasks[i] = DoRequest(i);
            //}
            //await Task.WhenAll(tasks);
            //Console.WriteLine("Done");

            //var local = Volatile.Read(ref i);
            //Volatile.Write(ref i, 10);
            //Interlocked.CompareExchange(ref i, 10, 10);
            //Debugger.Launch();

            //using (var mre = new ManualResetEvent(false))
            //{
            //    mre.Set();
            //    mre.WaitOne();
            //}
            //using (var are = new AutoResetEvent(false))
            //{
            //    are.Set();
            //    are.WaitOne();
            //}
            //using (var sem = new Semaphore(10, 10))
            //{
            //    sem.WaitOne();
            //    sem.Release();
            //}
            //using (var m = new Mutex(true, @"Global\Test"))
            //{
            //    Console.ReadLine();
            //    m.WaitOne();
            //    m.ReleaseMutex();
            //}

            //var o = new object();
            //lock (o)
            //{
            //    lock (o)
            //    {

            //    }
            //}
            //Monitor.Enter(o);
            //Monitor.Exit(o);
            //Monitor.TryEnter();

            //var rwl = new ReaderWriterLockSlim();
            //rwl.EnterUpgradeableReadLock();
            //{
            //    rwl.EnterWriteLock();
            //    rwl.ExitWriteLock();
            //}
            //rwl.ExitUpgradeableReadLock();

            //Monitor.Enter();
            //{
            //    Console.WriteLine();
            //}
            //Monitor.Exit();

            //var sem = new SemaphoreSlim();
            //await sem.WaitAsync();
            //Lazy<int> l = new Lazy<int>(() => 5, LazyThreadSafetyMode.PublicationOnly);

            DeadlockExample();

            Console.ReadLine();
        }

        private static void DeadlockExample()
        {
            Monitor.Enter(_lock);
            ThreadPool.QueueUserWorkItem(o =>
            {
                Monitor.Enter(_lock);
            });
        }

        static object _lock = new object();

        class Countdown
        {
            int _count;
            ManualResetEvent _event;

            public Countdown(int count)
            {
                _count = count;
                _event = new ManualResetEvent(false);
            }

            public void Signal()
            {
                if (Interlocked.Decrement(ref _count) == 0)
                    _event.Set();
            }

            public void WaitOne()
            {
                _event.WaitOne();
            }
        }

        class SimpleLock
        {
            int _lockTaken;

            public void Enter()
            {
                while (Interlocked.Exchange(ref _lockTaken, 1) == 1)
                {
                    Thread.SpinWait(2000);
                }
            }

            public void Exit()
            {
                Volatile.Write(ref _lockTaken, 0);
            }
        }

        class SimpleLock2
        {
            Mutex _m;

            public SimpleLock2()
            {
                _m = new Mutex(false);
            }

            public void Enter()
            {
                _m.WaitOne();
            }

            public void Exit()
            {
                _m.ReleaseMutex();
            }
        }

        /*volatile*/
        static int i;

        static async Task DoRequest(int index)
        {
            var request = WebRequest.CreateHttp("https://www.bing.com");
            using (var response = await request.GetResponseAsync())
            {
                using (var source = response.GetResponseStream())
                {
                    using (var destination = new MemoryStream())
                    {
                        try
                        {
                            await ReadStreamAsync(source, destination);
                            Console.WriteLine($"Done: {index}");
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine($"ERROR: {ex}");
                            return;
                        }
                    }
                }
            }
        }


        static async Task ReadStreamAsync(Stream source, Stream destination)
        {
            var buffer = new byte[32 * 1024];
            while (true)
            {
                var read = await source.ReadAsync(buffer, 0, buffer.Length);
                if (read == 0)
                    break;
                await destination.WriteAsync(buffer, 0, read);
            }
        }

        static async Task Test()
        {
            Console.WriteLine();
            await Task.CompletedTask;
            Console.WriteLine("A");
            await Task.CompletedTask;
            Console.WriteLine("B");
            await Task.CompletedTask;
            Console.WriteLine("C");
        }

        static int await(Task t)
        {
            return 10;
        }

        static void ReadStream(Stream source, Stream destination, Action onDone, Action<Exception> onError)
        {
            var buffer = new byte[32 * 1024];
            Task.Factory.FromAsync(
                source.BeginRead,
                source.EndRead,
                buffer, 0, buffer.Length,
                null);
            source.BeginRead(buffer, 0, buffer.Length, ar =>
            {
                int read;
                try
                {
                    read = source.EndRead(ar);
                }
                catch (Exception ex)
                {
                    onError(ex);
                    return;
                }
                if (read == 0)
                {
                    onDone();
                    return;
                }
                destination.BeginWrite(buffer, 0, read, ar2 =>
                {
                    try
                    {
                        destination.EndWrite(ar2);
                    }
                    catch (Exception ex)
                    {
                        onError(ex);
                        return;
                    }
                    ReadStream(source, destination, onDone, onError);
                }, null);
            }, null);
        }

        static object[] PFuncs(params Func<object>[] funcs)
        {
            var tasks = new Task<object>[funcs.Length];
            for (var i = 0; i < funcs.Length; i++)
            {
                tasks[i] = Task.Run(funcs[i]);
            }
            Task.WaitAll(tasks);
            return tasks.Select(x => x.Result).ToArray();
        }

        static object[] PFuncs2(params Func<object>[] funcs)
        {
            return funcs.Select(Task.Run).Select(x => x.Result).ToArray();
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
