using lab5.UI.ViewModels;

namespace lab5.UI.Pages;

public partial class SongDetailsPage : ContentPage
{
	public SongDetailsPage(SongDetailsViewModel vm)
	{
		InitializeComponent();
		BindingContext = vm;
	}

    protected override async void OnAppearing()
    {
        base.OnAppearing();

        //var vm = (SongDetailsViewModel)BindingContext;
        //vm.Foo();
    }
}