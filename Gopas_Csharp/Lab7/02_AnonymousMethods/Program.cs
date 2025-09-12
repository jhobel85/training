using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _02_AnonymousMethods
{
    class Program
    {
        delegate void ListArrayDelegate(int[] list);

        static void Main(string[] args)
        {
            // klasicke pouziti
            int[] list = {10, 20, 30, 40};
            ListArray(list);

            //pouziti delegate
            ListArrayDelegate d = new ListArrayDelegate(ListArray);
            d(new int[] { 10,20,30,40});

            //pouziti delegate s anonymni metodou
            d = delegate(int[] list2)
            {
                foreach (var item in list2)
                {
                    Console.WriteLine(item);
                }
            };
            d(new int[] { 10, 20, 30, 40 });

            Console.WriteLine("pouziti dalsi anonymni metody v metode foreach + predikce");
            //pouziti dalsi anonymni metody v metode foreach, pomoci predikce (vraci true / false)
            int[] list3 = Array.FindAll<int>(new int[] { 10, 20, 30, 40 }, delegate (int item) { return item > 20; });
            Array.ForEach<int>(list3, delegate(int item) { Console.WriteLine(item); });

            // vytvoreni anonymni metody pomoci lambda vyrazu
            Console.WriteLine("vytvoreni anonymni metody pomoci lambda vyrazu");
            int[] list4 = Array.FindAll<int>(new int[] { 10, 20, 30, 40 }, (int item) => { return item > 20; });
            Array.ForEach<int>(list4, delegate (int item) { Console.WriteLine(item); });

            Console.WriteLine("vytvoreni anonymni metody pomoci lambda vyrazu 2");
            int[] list5 = Array.FindAll<int>(new int[] { 10, 20, 30, 40 }, (item) => (item > 20));
            Array.ForEach<int>(list5, delegate (int item) { Console.WriteLine(item); });

            Console.WriteLine("vytvoreni anonymni metody pomoci lambda vyrazu 3");
            int[] list6 = Array.FindAll<int>(new int[] { 10, 20, 30, 40 }, item => item > 20);
            Array.ForEach<int>(list6, item => Console.WriteLine(item));

            Console.WriteLine("Func<> - anonymne vytvoreny delegat v parametru + Lambda expression ");
            ShowResult(10,20,(x,y) => x + y);
            ShowResult(10, 20, (x, y) => x - y);
            ShowResult(10, 20, (x, y) => x * y);
        }
        

        static void ListArray(int[] list)
        {
            foreach (var item in list)
            {
                Console.WriteLine(item);
            }
        }

        static int Sum(int a, int b)
        {
            return a + b;
        }

        static int Multiply(int a, int b)
        {
            return a + b;
        }

        // vytvoreni delegate anonymne - pouzitim predpripraveneho Func
        // 3. parametr je navratova hodnota
        static void ShowResult(int a, int b, Func<int, int, int> c)
        {
            Console.WriteLine(c(a, b));
        }
    }
}
