using lab5.UI.ViewModels;

namespace lab5.UI.Pages;

public partial class EditSongPage : ContentPage
{
    public EditSongPage(EditSongViewModel vm)
    {
        InitializeComponent();
        BindingContext = vm;
    }
}