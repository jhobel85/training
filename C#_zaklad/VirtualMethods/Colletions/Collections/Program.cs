using System;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Collections
{
    class Program
    {
        static void Main(string[] args)
        {
            Trainings trainings = new Trainings();
            foreach (Training item in trainings)
            {
                Console.WriteLine(item.Name);
            }
        }
    }
}
