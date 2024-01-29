using lab5.UI.ViewModels;

namespace lab5.UI.Pages;

public partial class AddMusicianPage : ContentPage
{
	public AddMusicianPage(AddMusicianViewModel vm)
	{
		InitializeComponent();
		BindingContext = vm;
	}
}