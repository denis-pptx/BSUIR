using lab5.Domain.Entities;

namespace lab5.Application.Abstractions;

public interface IBaseService<T> where T : Entity
{
    Task<IEnumerable<T>> GetAllAsync(); 
    Task<T> GetByIdAsync(int id); 
    Task AddAsync(T item); 
    Task UpdateAsync(T item); 
    Task DeleteAsync(int id);
}
