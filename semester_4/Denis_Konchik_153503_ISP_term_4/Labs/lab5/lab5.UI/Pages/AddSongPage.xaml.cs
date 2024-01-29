using lab5.UI.ViewModels;

namespace lab5.UI.Pages;

public partial class AddSongPage : ContentPage
{
	public AddSongPage(AddSongViewModel vm)
	{
		InitializeComponent();
		BindingContext = vm;
	}
}