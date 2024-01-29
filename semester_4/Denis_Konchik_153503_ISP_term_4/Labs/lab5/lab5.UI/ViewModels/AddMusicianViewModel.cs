using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using lab5.Application.Abstractions;
using lab5.Domain.Entities;

namespace lab5.UI.ViewModels;

public partial class AddMusicianViewModel : ObservableObject
{
    private IMusicianService _musicianService;
    public AddMusicianViewModel(IMusicianService musicianService)
    {
        _musicianService = musicianService;
    }

    [ObservableProperty]
    [NotifyCanExecuteChangedFor(nameof(SaveCommand))]
    private string _name = string.Empty;

    [ObservableProperty]
    [NotifyCanExecuteChangedFor(nameof(SaveCommand))]
    private string _country = string.Empty;

    [ObservableProperty]
    [NotifyCanExecuteChangedFor(nameof(SaveCommand))]
    private string _subscribers;

    [RelayCommand(CanExecute = nameof(CanSave))]
    public async Task Save()
    {
        await _musicianService.AddAsync(new()
        {
            Name = Name,
            Country = Country,
            Subscribers = Int32.Parse(Subscribers)
        });

        await Shell.Current.GoToAsync("..");
    }

    private bool CanSave()
    {
        return Name.Length > 0 
            && Country.Length > 0 
            && Int32.TryParse(Subscribers, out int subscribers) 
            && subscribers >= 0;
    }

    [RelayCommand]
    public async Task Cancel()
    {
        await Shell.Current.GoToAsync("..");
    }
}
