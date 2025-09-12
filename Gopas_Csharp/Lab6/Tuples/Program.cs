using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tuples
{
    /// <summary>
    /// 
    /// </summary>
    class Program
    {
        static void Main(string[] args)
        {
            object[] result = (object[]) GetData();
            Console.WriteLine((int)result[0]);
            Console.WriteLine((string)result[1]);
            Console.WriteLine((bool)result[2]);
        }

        static object GetData()
        {
            int id = 10;
            string name = "Joe";
            bool isMember = true;

            return new object[] {id, name, isMember};

            //Tuple<int, string, bool> data = GetData2();
        }

        /*
        static Tuple<int, string, bool> GetData2()
        {
            //return new Tuple<int, string, bool>(id, name, isMember);
        }
        */
    }
}
