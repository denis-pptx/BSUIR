using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using lab1.Helpers;

namespace lab1.Model
{
    public class Memory 
    {
        public string Value { get; private set; } = string.Empty;
        public bool IsEmpty => Value == string.Empty;

        public void Clear()
        {
            Value = string.Empty;
        }

        public string Read()
        {
            return Value;
        }

        public void Plus(string number)
        {
            if (IsEmpty)
            {
                Value = "0";
            }
            Value = CalculatorHelper.Execute(Value, number, "+");
        }

        public void Minus(string number)
        {
            if (IsEmpty)
            {
                Value = "0";
            }
            Value = CalculatorHelper.Execute(Value, number, "-");
        }
        public void Save(string number)
        {
            Value = number;
        }
    }
}
