using lab5.UI.Pages;

namespace lab5.UI
{
    public partial class AppShell : Shell
    {
        public AppShell()
        {
            InitializeComponent();

            Routing.RegisterRoute(nameof(SongDetailsPage), typeof(SongDetailsPage));
            Routing.RegisterRoute(nameof(AddMusicianPage), typeof(AddMusicianPage));
            Routing.RegisterRoute(nameof(AddSongPage), typeof(AddSongPage));
            Routing.RegisterRoute(nameof(EditSongPage), typeof(EditSongPage));
        }
    }
}