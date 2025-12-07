using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Xml.Serialization;

namespace XMLSerialization
{
    class Program
    {
        static void Main(string[] args)
        {
            Employee empl = new Employee(1, "Josef", "Hobel", (decimal)300.0);
            Console.WriteLine("Original object: ");
            Console.WriteLine(empl.ToString());

            Console.WriteLine("Serialization ... ");
            String path = @"C:\UserData\z003xjtr\siemens\Trainings\GopasCS\Lab9\SerializFile.xml";
            using (FileStream fs = new FileStream(path, FileMode.Create, FileAccess.Write))
            {
                XmlSerializer formatter = new XmlSerializer(empl.GetType());
                formatter.Serialize(fs, empl);
            }
            System.Threading.Thread.Sleep(2000);

            Console.WriteLine("Deserialization ... ");
                       
            using (FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read))
            {
                XmlSerializer formatter = new XmlSerializer(empl.GetType());
                Employee e2 = (Employee)formatter.Deserialize(fs);
                Console.WriteLine(e2.ToString());
            }
        }
    }
}
