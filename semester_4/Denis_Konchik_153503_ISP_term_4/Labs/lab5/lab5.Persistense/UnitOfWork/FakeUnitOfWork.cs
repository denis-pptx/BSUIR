using lab5.Domain.Abstractions;
using lab5.Domain.Entities;
using lab5.Persistense.Repository;

namespace lab5.Persistense.UnitOfWork;

public class FakeUnitOfWork : IUnitOfWork
{
    private readonly IRepository<Musician> _musicianRepository;
    private readonly IRepository<Song> _songRepository;
    public FakeUnitOfWork()
    {
        _musicianRepository = new FakeMusicianRepository();
        _songRepository = new FakeSongRepository();
    }

    public IRepository<Musician> MusicianRepository => _musicianRepository;

    public IRepository<Song> SongRepository => _songRepository;

    public Task CreateDatabaseAsync()
    {
        throw new NotImplementedException();
    }

    public Task RemoveDatbaseAsync()
    {
        throw new NotImplementedException();
    }

    public Task SaveAllAsync()
    {
        throw new NotImplementedException();
    }
}
