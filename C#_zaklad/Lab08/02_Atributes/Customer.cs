using System.Diagnostics;

namespace _02_Atributes
{
   
    [DebuggerDisplay("FirstName={FirstName}, LastName={LastName}, DALSI={Id}")]
    public class Customer
    {
        [Alias("CustomerID")]
        public int Id { get; set; }
        [Alias("FName")]
        public string FirstName { get; set; }
        [Alias("LName")]
        public string LastName { get; set; }


    }
}