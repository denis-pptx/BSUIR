using System.Globalization;
namespace lab1;

public partial class App : Application
{
	public App()
	{
		InitializeComponent();
        CultureInfo.DefaultThreadCurrentCulture = new CultureInfo("en-US");
        MainPage = new AppShell();
	}
}
