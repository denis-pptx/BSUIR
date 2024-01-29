namespace lab5.Domain.Entities;

public class Song : Entity
{
    public string Name { get; set; } = null!;
    public int Listenings { get; set; }
    public int ChartPlace { get; set; }

    public Musician? Musician { get; set; }
    public int MusicianId { get; set; }
}
