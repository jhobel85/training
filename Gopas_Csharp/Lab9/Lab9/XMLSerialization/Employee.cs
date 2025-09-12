using System;
using System.Runtime.InteropServices;
using System.Xml.Serialization;

namespace XMLSerialization
{
    public class Employee
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
    }
}