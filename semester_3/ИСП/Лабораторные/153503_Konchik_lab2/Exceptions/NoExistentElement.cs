using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153503_Konchik_lab2.Exceptions
{
    internal class NoExistentElementException : Exception
    {
        public NoExistentElementException(string message) 
            : base(message) { }
    }
}
