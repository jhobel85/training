using System;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Xml.Serialization;

namespace BinarySerialization
{
    [Serializable]
    public class Employee : IDeserializationCallback
    {
        private int id { get; set; }

        [XmlElement(ElementName = "FName")]
        public string FirstName { get; set; }

        [XmlElement(ElementName = "LName")]
        public string LastName { get; set; }

        public readonly decimal Salary;

        //[XmlIgnore]
       
        public DateTime TimeStamp { get; set; }

        public Department depart { get; set; }

        //default constructor - because of serialization
        public Employee()
        {
            TimeStamp = DateTime.Now;
        }

        public Employee(int id, string FirstName, string LastName, decimal Salary): this()
        {            
            this.id = id;
            this.FirstName = FirstName;
            this.LastName = LastName;
            this.Salary = Salary;
        }

        public override string ToString()
        {
            return TimeStamp.ToString();
        }

        public void OnDeserialization(object sender)
        {
            Console.WriteLine("On deserialization.");
        }
    }
}