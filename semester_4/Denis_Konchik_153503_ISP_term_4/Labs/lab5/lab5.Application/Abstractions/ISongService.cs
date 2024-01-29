using lab5.Domain.Entities;

namespace lab5.Application.Abstractions;

public interface ISongService : IBaseService<Song>
{
    Task<IEnumerable<Song>> GetByMusicianIdAsync(int musicianId);
}
