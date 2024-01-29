using lab5.Domain.Entities;

namespace lab5.Domain.Abstractions;

public interface IUnitOfWork
{
    IRepository<Musician> MusicianRepository { get; }
    IRepository<Song> SongRepository { get; }
    public Task RemoveDatbaseAsync(); 
    public Task CreateDatabaseAsync(); 
    public Task SaveAllAsync();
}
