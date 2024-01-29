using lab5.Application.Abstractions;
using lab5.Domain.Abstractions;
using lab5.Domain.Entities;

namespace lab5.Application.Services;

public class MusicianService : IMusicianService
{
    private IUnitOfWork _unitOfWork;
    public MusicianService(IUnitOfWork unitOfWork)
    {
        _unitOfWork = unitOfWork;
    }


    public async Task AddAsync(Musician item)
    {
        await _unitOfWork.MusicianRepository.AddAsync(item);
    }

    public async Task DeleteAsync(int id)
    {
        var musician = await _unitOfWork.MusicianRepository.FirstOrDefaultAsync(m => m.Id == id);
        if (musician != null)
        {
            await _unitOfWork.MusicianRepository.DeleteAsync(musician);
        }
    }

    public async Task<IEnumerable<Musician>> GetAllAsync()
    {
        return await _unitOfWork.MusicianRepository.ListAllAsync();
    }

    public async Task<Musician> GetByIdAsync(int id)
    {
        return (await _unitOfWork.MusicianRepository.FirstOrDefaultAsync(m => m.Id == id))!;
    }

    public async Task UpdateAsync(Musician item)
    {
        await _unitOfWork.MusicianRepository.UpdateAsync(item);
    }
}
