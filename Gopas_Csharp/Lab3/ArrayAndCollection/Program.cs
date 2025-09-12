using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Diagnostics.Eventing.Reader;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ArrayAndCollection
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            /*
            Stopwatch sw = new Stopwatch();
            sw.Start();
            Console.WriteLine("Working....");

            List<int> list = new List<int>();
            for (int i = 0; i < 100000; i++)
            {                
                //Array.Resize<int>(list, list.Length + 1);
                list.Add(0);
                // nejrychlejsi pouziti je pres generiky, kde nic neboxuji ani nepretypovavam
            }

            Console.WriteLine("done");
            sw.Stop();
            Console.WriteLine(sw.ElapsedMilliseconds + " ms");                        
            */

            /*
            Queue<string> queue = new Queue<string>();
            queue.Enqueue("A");
            queue.Enqueue("B");
            queue.Enqueue("C");
            queue.Enqueue("D");

            Console.WriteLine(queue.Dequeue());
            Console.WriteLine(queue.Dequeue());

            Console.WriteLine(queue.Peek()); // hodnota nasledujiciho prvku, bez odstraneni z fronty

            foreach (var item in queue)
            {
                Console.WriteLine(item);                
            }

            */

            /*
            Stack<string> stack = new Stack<string>();
            stack.Push("A");
            stack.Push("B");
            stack.Push("C");
            stack.Push("D");

            Console.WriteLine(stack.Pop());
            Console.WriteLine(stack.Pop());
            Console.WriteLine(stack.Peek()); // jako prvni bere posledni pridany prvek, funguje stejne jako Queue

            */

            /*
            Dictionary<string, string> dict = new Dictionary<string, string>();
            dict.Add("do", "delat");
            dict.Add("go", "delat");
            dict.Add("wait", "delat");
            dict.Add("stand", "delat");
            
            Console.WriteLine(dict["go"]);
            */

            Dictionary<TrainingID, string> list = new Dictionary<TrainingID, string>();
            list.Add(new TrainingID("MOC", 2349),"C#" );
            list.Add(new TrainingID("GOC", 330), "ASP.NET");
            list.Add(new TrainingID("GOC", 311), "ADO.NET");

            String message = list[new TrainingID("GOC", 330)];
            Console.WriteLine(message);            



            //v pripade, ze polozku nenajde, pak vyhodi vyjmku
        }

    }
}
