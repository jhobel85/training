using System;
using System.Collections.Generic;
using System.Linq;
using System.Security;
using System.Text;
using System.Threading.Tasks;

namespace Properties
{
    class Person
    {
        //snippet propfull
        /*
        private string firstName;

        public string FirstName
        {
            get { return firstName; }
            set { firstName = value; }
        }

        private string lastName;
            
        public string LastName
        {
            get { return lastName; }
            set { lastName = value; }
        }
        */

            //equivallent - snipet prop
        public virtual string FirstName { get; set; }
        public virtual string LastName { get; set; }    
    }
}
