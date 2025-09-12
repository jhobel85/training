using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _01_Generics
{
    class Stack
    {
        private readonly int size;
        private int currentIndex;
        private object[] items;

        public Stack(int size)
        {
            this.size = size;
            this.items = new Object[size];           
        }

        public Stack() : this(100)
        {
            // aa
        }

        public void Push(object item)
        {
            if (currentIndex >= size) throw new StackOverflowException();
            this.items[currentIndex] = item;
            currentIndex++;
        }

        public Object Pop()
        {
            currentIndex--;
            if (currentIndex < 0)
            {
                currentIndex = 0;
                throw new InvalidOperationException("Cannot pop an empty stack");
            }
            return items[currentIndex];
        }
    }
}
