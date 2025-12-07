using System;

namespace _02_Atributes
{
    [AttributeUsage(AttributeTargets.Property | AttributeTargets.Class)]
    public class AliasAttribute: Attribute
    {
         public string Name { get; set; }

        public AliasAttribute(string Name)
        {
            this.Name = Name;
        }
    }
}