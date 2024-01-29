using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab6
{
    public class Employee
    {
        public int Age { get; set; }
        public bool Male { get; set; }
        public string Name { get; set; } = "";

        public Employee(string Name, bool Male, int Age)
        {
            this.Name = Name;
            this.Male = Male;
            this.Age = Age;
        }

        public Employee()
        {

        }

        public override string ToString()
        {
            return $"Name: {Name}\n" +
                   $"Age: {Age}\n" +
                   $"Male: {Male}\n";
        }

    }
}
