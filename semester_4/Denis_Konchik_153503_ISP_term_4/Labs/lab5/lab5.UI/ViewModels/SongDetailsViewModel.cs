using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using lab5.Domain.Entities;
using lab5.UI.Pages;
using System.Collections.ObjectModel;

namespace lab5.UI.ViewModels;

[QueryProperty(nameof(Song), "Song")]
[QueryProperty(nameof(Musicians), "Musicians")]
public partial class SongDetailsViewModel : ObservableObject
{
    public SongDetailsViewModel()
    {

    }

    [ObservableProperty]
    private Song _song;

    public ObservableCollection<Musician> Musicians { get; set; }

    [RelayCommand]
    public async Task Edit()
    {
        await Shell.Current.GoToAsync(nameof(EditSongPage),
            new Dictionary<string, object>()
            {
                { "Song", Song },
                { "Musicians", Musicians }
            });
    }

    //public void Foo()
    //{
    //    OnPropertyChanged(nameof(Song));
    //}
}
