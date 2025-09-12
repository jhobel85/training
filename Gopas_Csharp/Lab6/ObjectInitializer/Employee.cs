namespace ObjectInitializer
{
    public class Employee
    {
        private int id { get; set; } 
        public string FirstName { get; set; }
        public string LastName { get; set; }

        public Employee(int ID)
        {
            this.id = ID;
        }

        public override string ToString()
        {
            return string.Format("[{0}] {1} {2}", id, FirstName, LastName);
        }
    }
}