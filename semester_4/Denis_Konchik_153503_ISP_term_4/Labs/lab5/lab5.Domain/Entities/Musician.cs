namespace lab5.Domain.Entities;

public class Musician : Entity
{
    public string Name { get; set; } = null!;
    public string Country { get; set; } = null!;
    public int Subscribers { get; set; }
    public List<Song>? Songs { get; set; }
}
