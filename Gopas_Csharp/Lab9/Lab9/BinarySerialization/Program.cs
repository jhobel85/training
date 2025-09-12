using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace BinarySerialization
{
    class Program
    {
        static void Main(string[] args)
        {
            Employee empl = new Employee(1, "Josef", "Hobel", (decimal)300.0);
            Console.WriteLine("Original object: ");
            Console.WriteLine(empl.ToString());

            Console.WriteLine("Serialization ... ");
            String path = @"C:\UserData\z003xjtr\siemens\Trainings\GopasCS\Lab9\BinarySerializFile.bin";
            using (FileStream fs = new FileStream(path, FileMode.Create, FileAccess.Write))
            {
                IFormatter formatter = new BinaryFormatter();
                formatter.Serialize(fs, empl);
            }
            System.Threading.Thread.Sleep(2000);

            Console.WriteLine("Deserialization ... ");

            using (FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read))
            {
                IFormatter formatter = new BinaryFormatter();
                Employee e2 = (Employee)formatter.Deserialize(fs);
                Console.WriteLine(e2.ToString());
            }
        }
    }
}
