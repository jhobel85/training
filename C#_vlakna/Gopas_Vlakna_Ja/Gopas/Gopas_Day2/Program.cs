using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Threading;
using System.Threading.Tasks;

namespace Gopas_Day2
{
    class Program
    {
        private static readonly Func<string, string> SayHello = (name) => "Hello " + name;
        private static byte[] someBuffer = new byte[20];
        private static int bytesRead = 0;
        private static int bytesNeeded = 40;
        private static int numberOfBytesRead;
        private static Stream myNetworkStream;
        private static Stream toWriteStream;
        private static List<Stream> awyncAwaitStream = new List<Stream>();

        static void Main(string[] args)
        {
            //Console.WriteLine("Hello World!");
            //InvokeVsFunc();
            //TimerExample();
            //HttpRequest();
            asyncAwait();
        }

        static async void asyncAwait()
        {
            var tasks = new Task[10000];
            for (int i = 0; i < tasks.Length; i++)
            {
                tasks[i] = Do();
            }
            await Task.WhenAll(tasks);
            Console.WriteLine("done READ AND WRITE");

            Console.WriteLine("show written result: " + awyncAwaitStream.ToString());
            
        }

        static async Task Do()
        {
            var resquest = WebRequest.CreateHttp("https://www.bing.com/");
            //Console.WriteLine("Request done " + resquest);
            using (var response = await resquest.GetResponseAsync())
            {
                Console.WriteLine("Response done " + response);
                using (var stream = response.GetResponseStream())
                {
                    Console.WriteLine("Read done " + stream);
                    awyncAwaitStream.Add(stream);//nejde protoze bych si mohl prepsat jednotlive polozky pridane zaroven.
               }
            }            

        }

        static void HttpRequestUkol()
        {            
            List<byte> toWriteList = new List<byte>();
            var resquest = WebRequest.CreateHttp("https://www.bing.com/");
            //var ar = resquest.BeginGetResponse(null,null);
            //using (var response = resquest.GetResponse())
            for (int i = 0; i < 10000; i++)
            {
                resquest.BeginGetResponse(ar =>
                {
                    using (var response = resquest.EndGetResponse(ar))//posli request a cekej na response ale neblokuj.
                    {
                        myNetworkStream = response.GetResponseStream();
                        BeginReading(); // start read and wait till end

                    }
                }, null);
                
                Console.ReadLine();
            }
        }

        public static void BeginReading()
        {
            myNetworkStream.BeginRead(
                someBuffer, bytesRead, bytesNeeded - bytesRead,
                new AsyncCallback(EndReading),
                myNetworkStream);
        }

        public static void EndReading(IAsyncResult ar)
        {
            numberOfBytesRead = myNetworkStream.EndRead(ar);

            if (numberOfBytesRead == 0)
            {
                // disconnected
                return;
            }

            bytesRead += numberOfBytesRead;
            BeginReading();
        }

        static void HttpRequest()
        {
            byte[] buffer = new byte[20];
            
            var resquest = WebRequest.CreateHttp("https://www.bing.com/");
            //var ar = resquest.BeginGetResponse(null,null);
            //using (var response = resquest.GetResponse())
            for (int i = 0; i < 10000; i++)
            {
                resquest.BeginGetResponse(ar =>
                {
                    using (var response = resquest.EndGetResponse(ar))//posli request a cekej na response ale neblokuj.
                    {
                        Console.WriteLine(response.ContentType);                        
                    }
                }, null);
                Console.ReadLine();
            }
            
        }

        static void TimerExample()
        {
            //var timer = new Timer(o => Console.WriteLine(DateTime.UtcNow), null, 0, 2000);
            var timer2 = new Timer(o => {

                Task.Run(() => Console.WriteLine(DateTime.UtcNow));                
                //Task.Run(() => Thread.Sleep(20000));

            },null, 0, 2000);
            //prirazeni do promenne, jinak ho GC smaze.
            Console.ReadLine();

            /*
            Timer timer2 = null;
            timer2 = new Timer(o =>
           {
               Console.WriteLine(DateTime.Now);
               timer2.Change(2000, -1);
           }, null, 0 -1);
            Console.ReadLine();
            */
        }

        private static void InvokeVsFunc()
        {
            //Like normal method
            var Tresult = SayHello("John");

            //Invoke is a late binding technique where you postpone determining a method name and signature until you are actually ready to call it
            Tresult = SayHello.Invoke("John");
        }
    }
}
