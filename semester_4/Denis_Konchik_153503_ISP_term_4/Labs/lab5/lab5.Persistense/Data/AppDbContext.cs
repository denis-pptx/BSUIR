namespace lab5.Persistense.Data;

using lab5.Domain.Entities;
using Microsoft.EntityFrameworkCore;

public class AppDbContext : DbContext
{
	public DbSet<Musician> Musicians { get; set; }
	public DbSet<Song> Songs { get; set; }

	public AppDbContext(DbContextOptions<AppDbContext> opt)
		: base(opt)
	{
        //Database.EnsureCreated();
    }
}
