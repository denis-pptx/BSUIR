using lab5.Application.Abstractions;
using lab5.Domain.Abstractions;
using lab5.Domain.Entities;

namespace lab5.Application.Services;

public class SongService : ISongService
{
    private IUnitOfWork _unitOfWork;
    public SongService(IUnitOfWork unitOfWork)
    {
        _unitOfWork = unitOfWork;
    }

    public async Task AddAsync(Song item)
    {
        await _unitOfWork.SongRepository.AddAsync(item);
    }

    public async Task DeleteAsync(int id)
    {
        var song = await _unitOfWork.SongRepository.FirstOrDefaultAsync(m => m.Id == id);
        if (song != null)
        {
            await _unitOfWork.SongRepository.DeleteAsync(song);
        }
    }

    public async Task<IEnumerable<Song>> GetAllAsync()
    {
        return await _unitOfWork.SongRepository.ListAllAsync();
    }

    public async Task<Song> GetByIdAsync(int id)
    {
        return (await _unitOfWork.SongRepository.FirstOrDefaultAsync(s => s.Id == id))!;
    }

    public async Task UpdateAsync(Song item)
    {
        await _unitOfWork.SongRepository.UpdateAsync(item);
    }

    public async Task<IEnumerable<Song>> GetByMusicianIdAsync(int musicianId)
    {
        return await _unitOfWork.SongRepository.ListAsync(song => song.MusicianId == musicianId);
    }
}
