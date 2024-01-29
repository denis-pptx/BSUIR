using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using lab5.Application.Abstractions;
using lab5.Domain.Entities;
using lab5.UI.Constants;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using System.Collections.ObjectModel;
using System.Diagnostics;
using Windows.Devices.Geolocation;

namespace lab5.UI.ViewModels;

public partial class EditSongViewModel : ObservableObject, IQueryAttributable
{
    private ISongService _songService;
    public EditSongViewModel(ISongService songService)
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

    public ObservableCollection<Musician> Musicians { get; set; }

    [ObservableProperty]
    private Song _song;


    public void ApplyQueryAttributes(IDictionary<string, object> query)
    {
        Musicians = query["Musicians"] as ObservableCollection<Musician>;
        OnPropertyChanged(nameof(Musicians));

        Song = query["Song"] as Song;
        Name = Song.Name;
        Listenings = Song.Listenings.ToString();
        ChartPlace = Song.ChartPlace.ToString();
        Musician = Song.Musician;
    }

    [RelayCommand]
    public void Reset()
    {
        Name = Song.Name;
        Listenings = Song.Listenings.ToString();
        ChartPlace = Song.ChartPlace.ToString();
        Musician = Song.Musician;
    }

    [RelayCommand]
    public async Task PickPicture()
    {
        var result = await FilePicker.PickAsync(new PickOptions()
        {
            PickerTitle = "Pick Image",
            FileTypes = FilePickerFileType.Images
        });

        if (result == null)
            return;

        string[] songImagePaths = Directory.GetFiles(PathConstants.ImagesFolder, $"{Song.Id}.*");
        foreach (var imagePath in songImagePaths)
        {
            if (File.Exists(imagePath))
            {
                File.Delete(imagePath);
            }
        }

       
        var destinationPath = Path.Combine(PathConstants.ImagesFolder,
            $"{Song.Id}{Path.GetExtension(result.FullPath)}");

        FileInfo fileInfo = new FileInfo(result.FullPath);
        if (fileInfo.Exists)
        {
            fileInfo.CopyTo(destinationPath, true);
        }

        OnPropertyChanged($"{nameof(Song)}");
    }

    [RelayCommand(CanExecute = nameof(CanSave))]
    public async Task Save()
    {
        Song.Name = Name;
        Song.ChartPlace = Int32.Parse(ChartPlace);
        Song.Listenings = Int32.Parse(Listenings);
        Song.Musician = Musician;

        await _songService.UpdateAsync(Song);

        await Shell.Current.GoToAsync("../..");
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
        await Shell.Current.GoToAsync("../..");
    }
}
