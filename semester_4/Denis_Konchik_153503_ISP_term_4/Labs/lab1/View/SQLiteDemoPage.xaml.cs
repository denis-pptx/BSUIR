using lab1.ViewModel;

namespace lab1.View;

public partial class SQLiteDemoPage : ContentPage
{
	public SQLiteDemoPage(SQLiteDemoViewModel vm)
	{
		BindingContext = vm;
		InitializeComponent();
	}

}