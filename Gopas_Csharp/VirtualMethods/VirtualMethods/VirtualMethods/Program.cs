using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VirtualMethods
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("XXX");
            Animal[] animals = {new Dog(), new Cat(), new Dog(), new Cat()};
            foreach (var item in animals)
            {
               // Console.WriteLine(item.Sound());

                //shadowing - je treba pretypovani, protoze tady nefunguje polymorfizmus
                if (item is Cat)
                {
                    Console.WriteLine(((Cat)item).Sound());
                }else if (item is Dog)
                {
                    Console.WriteLine(((Dog)item).Sound());
                }
            }


        }
    }
}
