using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace lab1.Entities
{
    [Table(nameof(Musician))]
    public class Musician
    {
        [PrimaryKey, AutoIncrement, Indexed]
        public int Id { get; set; }
        public string Name { get; set; }
        public string Country { get; set; }
        public int Subscribers { get; set; }

    }
}
