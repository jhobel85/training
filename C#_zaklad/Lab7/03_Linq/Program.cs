using System;
using System.Collections.Generic;
using System.Linq;

namespace _03_Linq
{
    class Program
    {
        static void Main(string[] args)
        {
            Trainings trains = new Trainings();
            List<String> list = new List<string>();
            String a = "aaa";
            list.Add(a);
            String b = "bbb";
            list.Add(b);
            String c = "aabb";
            list.Add(c);

            //Predicate char a v nazvech
            var enumerable = list.Where(x2 => x2.Contains("b"));
            //vypis vsech nalezenych prvku
            enumerable.ToList().ForEach(x3 => Console.WriteLine(x3));

            // stejny zapis tehoz, Query syntax
            Console.WriteLine("alternative syntax");
            var enumerable2 = from t in list where t.Contains("a") select t;
            enumerable2.ToList().ForEach(x4 => Console.WriteLine(x4));        
        }
    }
}
