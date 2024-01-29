using CommunityToolkit.Maui.Core.Extensions;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using lab5.Application.Abstractions;
using lab5.Application.Services;
using lab5.Domain.Entities;
using lab5.UI.Pages;
using System.Collections.ObjectModel;

namespace lab5.UI.ViewModels;

public partial class MusiciansViewModel : ObservableObject
{
    private readonly IMusicianService _musicianService;
    private readonly ISongService _songService;

    public MusiciansViewModel(IMusicianService musicianService, ISongService songService)
    {
        _musicianService = musicianService;
        _songService = songService;
    }

    public ObservableCollection<Musician> Musicians { get; set; } = new();
    public ObservableCollection<Song> Songs { get; set; } = new();

    [ObservableProperty]
    [NotifyPropertyChangedFor(nameof(IsMusicianSelected))]
    private Musician _selectedMusician;

    public bool IsMusicianSelected => SelectedMusician != null;

    [RelayCommand]
    public async Task UpdateMusicianList()
    {
        var selectedMusician = SelectedMusician;

        Musicians.Clear();

        var musicians = await _musicianService.GetAllAsync();
        foreach (var musician in musicians)
            Musicians.Add(musician);


        if (selectedMusician != null)
        {
            SelectedMusician = await _musicianService.GetByIdAsync(selectedMusician.Id);
        }
    }

    [RelayCommand]
    public async Task UpdateSongsList()
    {
        Songs.Clear();

        if (IsMusicianSelected)
        {
            Songs = (await _songService.GetByMusicianIdAsync(SelectedMusician.Id)).ToObservableCollection();
            OnPropertyChanged(nameof(Songs));
        }
    }

    [RelayCommand]
    public async Task ShowDetails(Song song)
    {
        await Shell.Current.GoToAsync(nameof(SongDetailsPage),
            new Dictionary<string, object>()
        {
            { "Song", song },
            { "Musicians", Musicians }
        });
    }

    [RelayCommand]
    public async Task Add()
    {
        string action = IsMusicianSelected switch
        {
            true => await Shell.Current.DisplayActionSheet("Append", "Cancel", null, 
                            "Musician", $"Song (to {SelectedMusician.Name})"),
            _ => "Musician"
        };

        if (action == "Musician")
        {
            await Shell.Current.GoToAsync(nameof(AddMusicianPage));
        }
        else if (action != "Cancel")
        {
            await Shell.Current.GoToAsync(nameof(AddSongPage),
                new Dictionary<string, object>()
                {
                    { "Musician", SelectedMusician }
                });
        }
    }

}
