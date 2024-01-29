using CommunityToolkit.Maui.Core.Extensions;
using lab1.Entities;
using lab1.Services;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace lab1.ViewModel
{
    public class SQLiteDemoViewModel : BaseViewModel
    {
        private IDbService _db;
        public SQLiteDemoViewModel(IDbService db)
        {
            _db = db;
            
            _updateMusicians();

            RefreshCommand = new Command(async () => 
            {
                if (IsBusy) return;

                Songs.Clear();
                await _updateMusicians();
                SelectedMusician = Musicians.FirstOrDefault();
            });
        }

        private async Task _updateMusicians()
        {
            if (IsBusy) return;

            IsBusy = true;
            IsRefreshing = true;

            await Task.Delay(300);

            Musicians = (await _db.GetAllMusicians()).ToObservableCollection();
            OnPropertyChanged(nameof(Musicians));

            IsBusy = false;
            IsRefreshing = false;
            
        }

        private async Task _updateSongs()
        {
            if (IsBusy) return;

            IsBusy = true;
            IsRefreshing = true;

            Songs.Clear();
            OnPropertyChanged(nameof(Songs));

            await Task.Delay(800);

            Songs = (await _db.GetMusicianSongs(_selectedMusician.Id)).ToObservableCollection();
            OnPropertyChanged(nameof(Songs));

            TotalListenings = Songs.Sum(s => s.Listenings);
            TotalLikes = Songs.Sum(s => s.Likes);

            IsBusy = false;
            IsRefreshing = false;

        }

        private Musician _selectedMusician;

        public Musician SelectedMusician
        {
            get { return _selectedMusician; }
            set 
            { 
                if (SetProperty(ref _selectedMusician, value))
                {
                    _updateSongs();
                }
            }
        }

        private int? _totalListenings;

        public int? TotalListenings
        {
            get { return _totalListenings; }
            set { SetProperty(ref _totalListenings, value); }
        }

        private int? _totalLikes;

        public int? TotalLikes
        {
            get { return _totalLikes; }
            set { SetProperty(ref _totalLikes, value); }
        }


        public ICommand RefreshCommand { get; set; }
        public ObservableCollection<Musician> Musicians { get; private set; } = new();
        public ObservableCollection<Song> Songs { get; private set; } = new();

    }
}
