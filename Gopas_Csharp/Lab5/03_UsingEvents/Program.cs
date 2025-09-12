using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace _03_UsingEvents
{
    class Program
    {       
        static void Main(string[] args)
        {
            IntListWithChangedEvent list = new IntListWithChangedEvent();
            list.Add(1);
            list.Add(2);
            list.Add(3);
            //list.Changed += EventListener;
            list.Changed += List_Changed;
            // volani udalosti
            list.Add(4);
            list.Add(5);
            list.Add(6);
            list[1] = 7;
        }

        private static void List_Changed(object sender)
        {
            Console.WriteLine("Changed");           
        }

        private static void List_Changed(object sender, ChangedEventArgs e)
        {
            Console.WriteLine(e.ChangedState);
        }

        private static void EventListener(object sender, EventArgs e)
        {
            IntListWithChangedEvent list = sender as IntListWithChangedEvent;
            if (list == null) return;

            Console.WriteLine();
            Console.WriteLine("Items:");
            foreach (var item in list)
            {
                Console.WriteLine("\t" + item);
            }
            
        }
    }
}
