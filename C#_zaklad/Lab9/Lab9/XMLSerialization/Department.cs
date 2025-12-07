namespace XMLSerialization
{
    public class Department
    {
        public int Id { get; set; } 
        public string Name { get; set; }

        public Department()
        {
            //because of serialization
        }

        public Department(int Id, string Name)
        {
            this.Id = Id;
            this.Name = Name;
        }

        public override string ToString()
        {
            return base.ToString();
        }
    }
}