using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using lab5.Application.Abstractions;
using lab5.Domain.Entities;
using System.Diagnostics.Metrics;

namespace lab5.UI.ViewModels;

[QueryProperty(nameof(Musician), "Musician")]
public partial class AddSongViewModel : ObservableObject
{
    private ISongService _songService;
    public AddSongViewModel(ISongService songService)
    {
        _songService = songService;
    }

    [ObservableProperty]
    [NotifyCanExecuteChangedFor(nameof(SaveCommand))]
    private string _name = string.Empty;

    [ObservableProperty]
    [NotifyCanExecuteChangedFor(nameof(SaveCommand))]
    private string _listenings;

    [ObservableProperty]
    [NotifyCanExecuteChangedFor(nameof(SaveCommand))]
    private string _chartPlace;

    [ObservableProperty]
    private Musician _musician;

    [RelayCommand(CanExecute = nameof(CanSave))]
    public async Task Save()
    {
        await _songService.AddAsync(new()
        {
            Name = Name,
            Listenings = Int32.Parse(Listenings),
            ChartPlace = Int32.Parse(ChartPlace),
            Musician = Musician
        });

        await Shell.Current.GoToAsync("..");
    }

    private bool CanSave()
    {
        return Name.Length > 0
            && Int32.TryParse(Listenings, out int listenings)
            && listenings >= 0
            && Int32.TryParse(ChartPlace, out int chartPlace)
            && chartPlace > 0;
    }

    [RelayCommand]
    public async Task Cancel()
    {
        await Shell.Current.GoToAsync("..");
    }
}
