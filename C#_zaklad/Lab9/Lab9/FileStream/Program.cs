using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace FileStream
{
    class Program
    {
        static void Main(string[] args)
        {
            String path = @"C:\UserData\z003xjtr\siemens\Trainings\GopasCS\Lab9\data.bin";
            //System.IO.FileStream fs = new System.IO.FileStream(path, FileMode.Create, FileAccess.Write);
            //fs.Close();

            //pouziti try - finally pomcoi using
            // ve finally se zavola dispose() --> a to funguje stejne jako fs.close()
            using (System.IO.FileStream fs1 = new System.IO.FileStream(path, FileMode.Create, FileAccess.Write))
            {
                BinaryWriter bw = new BinaryWriter(fs1);
                bw.Write(10);
                bw.Write("Ahoj");
                bw.Write(true);
                fs1.Flush(); // vyprazdneni streamu.               
            }

            //cteni
            using (System.IO.FileStream fs1 = new System.IO.FileStream(path, FileMode.Open, FileAccess.Read))
            {
                //cist musime ve stejnem poradi jako zapisujeme.
                BinaryReader br = new BinaryReader(fs1);
                Console.WriteLine(br.ReadInt32());
                Console.WriteLine(br.ReadString());
                Console.WriteLine(br.ReadBoolean());
            }
            
            // cteni - zapis - textoveho souboru
            Console.WriteLine("Text file reader: ");
            String path2 = @"C:\UserData\z003xjtr\siemens\Trainings\GopasCS\Lab9\TextFile.txt";
            if (File.Exists(path))
            {
                Encoding enc = Encoding.GetEncoding("Windows-1250");// umizni cist specialni znaky
                //Encoding enc = Encoding.UTF8;// umizni cist specialni znaky
                //cteni
                using (StreamReader sr = new System.IO.StreamReader(path2, enc))
                {
                    while (!sr.EndOfStream) {                    
                    Console.WriteLine(sr.ReadLine());
                    }
                }
            }           
        }
    }
}
