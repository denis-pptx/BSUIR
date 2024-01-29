using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace lab1.Entities
{
    [Table(nameof(Song))]
    public class Song
    {
        [PrimaryKey, AutoIncrement, Indexed]
        public int Id { get; set; }
        public string Title { get; set; }
        public int Listenings { get; set; }
        public int Likes { get; set; }

        [Indexed]
        public int MusicianId { get; set; }
    }
}
