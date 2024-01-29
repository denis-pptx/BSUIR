using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary
{
    public class Musician
    {
        public int Id { get; }
        public string? Name { get; }
        public int NumberOfSongs { get; }

        public Musician(int Id, string? Name, int NumberOfSongs)
        {
            this.Id = Id;
            this.Name = Name;
            this.NumberOfSongs = NumberOfSongs;
        }
    }
}
