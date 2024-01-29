using System.Diagnostics;
using System;
using lab1.ViewModel;

namespace lab1.View;


public partial class ProgressDemoPage : ContentPage
{
    public ProgressDemoPage(ProgressDemoViewModel vm)
    {
        

        InitializeComponent();
        BindingContext = vm;
    }
}

