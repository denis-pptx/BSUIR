using lab5.Domain.Abstractions;
using lab5.Domain.Entities;
using System.Diagnostics.Metrics;
using System.Linq.Expressions;
using System.Xml.Linq;

namespace lab5.Persistense.Repository;

public class FakeMusicianRepository : IRepository<Musician>
{
    private List<Musician> _musicians;

    public FakeMusicianRepository()
    {
        _musicians = new List<Musician>()
        {
            new Musician()
            {
                Id = 1,
                Name = "Denis Konchik",
                Country = "Belarus",
                Subscribers = 2536230,
                Songs = new()
            },
            new Musician()
            {
                Id = 2,
                Name = "Till Lindemann",
                Country = "Germany",
                Subscribers = 1004243,
                Songs = new()
            },
            new Musician()
            {
                Id = 3,
                Name = "Yaugen Kahnouski",
                Country = "China",
                Subscribers = 1954186,
                Songs = new()
            }
        };
    }

    public Task AddAsync(Musician entity)
    {
        throw new NotImplementedException();
    }

    public Task DeleteAsync(Musician entity)
    {
        throw new NotImplementedException();
    }

    public Task<Musician?> FirstOrDefaultAsync(Func<Musician, bool> filter)
    {
        throw new NotImplementedException();
    }

    public Task<Musician?> GetByIdAsync(int id)
    {
        throw new NotImplementedException();
    }

    public Task<IEnumerable<Musician>> ListAllAsync()
    {
        throw new NotImplementedException();
    }

    public Task<IEnumerable<Musician>> ListAsync(Func<Musician, bool> filter)
    {
        throw new NotImplementedException();
    }

    public Task UpdateAsync(Musician entity)
    {
        throw new NotImplementedException();
    }
}
