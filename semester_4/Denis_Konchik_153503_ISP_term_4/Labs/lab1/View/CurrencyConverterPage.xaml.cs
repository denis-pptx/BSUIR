namespace lab1.View;
using lab1.ViewModel;

public partial class CurrencyConverterPage : ContentPage
{
	public CurrencyConverterPage(CurrencyConverterViewModel vm)
	{
		InitializeComponent();
		BindingContext = vm;
	}

    private void Entry_Completed(object sender, EventArgs e)
    {
		if (sender is Entry entry)
		{
			entry.IsEnabled = false;
			entry.IsEnabled = true;
		}

    }
}