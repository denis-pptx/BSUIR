using CommunityToolkit.Maui;
using CommunityToolkit.Maui.Core;
using lab5.Application.Abstractions;
using lab5.Application.Services;
using lab5.Domain.Abstractions;
using lab5.Persistense.UnitOfWork;
using lab5.UI.ViewModels;
using lab5.UI.Pages;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Configuration;
using System.Reflection;
using lab5.Persistense.Data;
using Microsoft.EntityFrameworkCore;
using lab5.Domain.Entities;
using lab5.UI.Constants;
using Microsoft.Maui.Controls;

namespace lab5.UI;

public static class MauiProgram
{
    public static MauiApp CreateMauiApp()
    {
        CreateDirectories();

        string settingsStream = "lab5.UI.appsettings.json";

        var builder = MauiApp.CreateBuilder();
        builder
            .UseMauiApp<App>()
            .UseMauiCommunityToolkit()
            .ConfigureFonts(fonts =>
            {
                fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
                fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
                fonts.AddFont("Font-Awesome-6-Free-Solid-900.otf", "FAFS-900");
            });

       

        var a = Assembly.GetExecutingAssembly(); 
        using var stream = a.GetManifestResourceStream(settingsStream); 
        builder.Configuration.AddJsonStream(stream);

#if DEBUG
        builder.Logging.AddDebug();
#endif

        AddDbContext(builder);
        SetupServices(builder.Services);
        SeedData(builder.Services);


        return builder.Build();
    }

    private static void SetupServices(IServiceCollection services)
    {
        // Services.
        services.AddSingleton<IUnitOfWork, EfUnitOfWork>();
        services.AddSingleton<IMusicianService, MusicianService>();
        services.AddSingleton<ISongService, SongService>();

        // ViewModels.
        services.AddSingleton<MusiciansViewModel>();
        services.AddTransient<SongDetailsViewModel>();
        services.AddTransient<AddMusicianViewModel>();
        services.AddTransient<AddSongViewModel>();
        services.AddTransient<EditSongViewModel>();

        // Pages.
        services.AddSingleton<MusiciansPage>();
        services.AddTransient<SongDetailsPage>();
        services.AddTransient<AddMusicianPage>();
        services.AddTransient<AddSongPage>();
        services.AddTransient<EditSongPage>();

    }

    private static void AddDbContext(MauiAppBuilder builder)
    {
        var connectionString = string.Format(
            builder.Configuration.GetConnectionString("SqliteConnection"), PathConstants.DbFolder);

        var options = new DbContextOptionsBuilder<AppDbContext>()
            .UseSqlite(connectionString)
            .Options; 

        builder.Services.AddScoped<AppDbContext>((s) => new AppDbContext(options));
    }

    public async static void SeedData(IServiceCollection services)
    {
        using var provider = services.BuildServiceProvider(); 
        
        var unitOfWork = provider.GetService<IUnitOfWork>();

        await unitOfWork.RemoveDatbaseAsync(); 
        await unitOfWork.CreateDatabaseAsync();

        // Add musicians.
        IReadOnlyList<Musician> musicians = new List<Musician>()
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

        foreach (var musician in musicians) 
            await unitOfWork.MusicianRepository.AddAsync(musician);
        await unitOfWork.SaveAllAsync();

        // Add songs.
        Random rand = new Random(); 
        int k = 1; 
        foreach (var musician in musicians) 
            for (int j = 0; j < 10; j++) 
                await unitOfWork.SongRepository.AddAsync(new Song()
                {
                    Id = k,
                    Name = $"Song {k++}",
                    Listenings = rand.Next(1, 1000),
                    ChartPlace = rand.Next(1, 1000),
                    Musician = musician
                }); 
        await unitOfWork.SaveAllAsync();
    }

    private static void CreateDirectories()
    {
        if (!Directory.Exists(PathConstants.ImagesFolder))
        {
            Directory.CreateDirectory(PathConstants.ImagesFolder);
        }
    }
}