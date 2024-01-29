using lab5.Domain.Abstractions;
using lab5.Domain.Entities;
using Microsoft.EntityFrameworkCore.Query.Internal;
using System.Linq;
using System.Linq.Expressions;

namespace lab5.Persistense.Repository;

public class FakeSongRepository : IRepository<Song>
{
    private List<Song> _songs;
    public FakeSongRepository()
    {
        _songs = new();

        Random rand = new Random();
        int k = 1;

        for (int i = 1; i <= 3; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                _songs.Add(new Song() 
                { 
                    Id = k,
                    Name = $"Song {k++}",
                    Listenings = rand.Next(1, 1000),
                    ChartPlace = rand.Next(1, 1000),
                    MusicianId = i
                });
            }
        }

    }

    public Task AddAsync(Song entity)
    {
        throw new NotImplementedException();
    }

    public Task DeleteAsync(Song entity)
    {
        throw new NotImplementedException();
    }

    public Task<Song?> FirstOrDefaultAsync(Func<Song, bool> filter)
    {
        throw new NotImplementedException();
    }

    public Task<Song?> GetByIdAsync(int id)
    {
        throw new NotImplementedException();
    }

    public Task<IEnumerable<Song>> ListAllAsync()
    {
        throw new NotImplementedException();
    }

    public Task<IEnumerable<Song>> ListAsync(Func<Song, bool> filter)
    {
        throw new NotImplementedException();
    }

    public Task UpdateAsync(Song entity)
    {
        throw new NotImplementedException();
    }
}
