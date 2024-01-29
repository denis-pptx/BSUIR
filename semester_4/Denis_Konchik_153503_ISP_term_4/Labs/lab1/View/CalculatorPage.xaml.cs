
using lab1.Model;
using lab1.ViewModel;
using System.Windows.Input;

namespace lab1.View;

public partial class CalculatorPage : ContentPage
{

    public CalculatorPage(CalculatorViewModel viewModel)
	{
        BindingContext = viewModel;
        InitializeComponent();
    }
}