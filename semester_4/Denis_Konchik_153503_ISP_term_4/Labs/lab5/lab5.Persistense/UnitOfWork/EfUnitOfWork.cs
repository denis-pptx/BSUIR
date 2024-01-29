using lab5.Domain.Abstractions;
using lab5.Domain.Entities;
using lab5.Persistense.Data;
using lab5.Persistense.Repository;

namespace lab5.Persistense.UnitOfWork;

public class EfUnitOfWork : IUnitOfWork
{
    private readonly AppDbContext _context;
    private readonly Lazy<IRepository<Musician>> _musicianRepository; 
    private readonly Lazy<IRepository<Song>> _songRepository;

    public EfUnitOfWork(AppDbContext context)
    {
        _context = context;
        _musicianRepository = new Lazy<IRepository<Musician>>(() => new EfRepository<Musician>(context));
        _songRepository = new Lazy<IRepository<Song>>(() => new EfRepository<Song>(context));
    }

    public IRepository<Musician> MusicianRepository => 
        _musicianRepository.Value;

    public IRepository<Song> SongRepository => 
        _songRepository.Value;

    public async Task CreateDatabaseAsync()
    {
        await _context.Database.EnsureCreatedAsync();
    }

    public async Task RemoveDatbaseAsync()
    {
        await _context.Database.EnsureDeletedAsync();
    }

    public async Task SaveAllAsync()
    {
        await _context.SaveChangesAsync();
    }
}
