using lab5.UI.ViewModels;

namespace lab5.UI.Pages;

public partial class MusiciansPage : ContentPage
{
    public MusiciansPage(MusiciansViewModel vm)
	{
		InitializeComponent();
		BindingContext = vm;
	}

    protected override async void OnAppearing()
    {
        base.OnAppearing();

        var vm = (MusiciansViewModel)BindingContext;
        await vm.UpdateMusicianList();
    }
}