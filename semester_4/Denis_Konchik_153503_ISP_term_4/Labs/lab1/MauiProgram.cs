using Microsoft.Extensions.Logging;
using lab1.Model;
using lab1.View;
using lab1.ViewModel;
using lab1.Services;

namespace lab1;

public static class MauiProgram
{
	public static MauiApp CreateMauiApp()
	{
		var builder = MauiApp.CreateBuilder();

#pragma warning disable MCT001 // `.UseMauiCommunityToolkit()` Not Found on MauiAppBuilder
        builder
			.UseMauiApp<App>()
			.ConfigureFonts(fonts =>
			{
				fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
				fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
                fonts.AddFont("Font-Awesome-6-Free-Solid-900.otf", "FAFS-900");
                fonts.AddFont("Segoe-UI.ttf", "Segoe-UI");
            });
#pragma warning restore MCT001 // `.UseMauiCommunityToolkit()` Not Found on MauiAppBuilder

#if DEBUG
        builder.Logging.AddDebug();
#endif
        
        // Register Views.
        builder.Services.AddSingleton<CalculatorPage>();
        builder.Services.AddSingleton<ProgressDemoPage>();
        builder.Services.AddSingleton<SQLiteDemoPage>();
        builder.Services.AddSingleton<CurrencyConverterPage>();
        
        // Register Models.
        builder.Services.AddTransient<Calculator>();
		builder.Services.AddTransient<Memory>();
        builder.Services.AddTransient<Integral>();

        // Register Services.
        builder.Services.AddTransient<IDbService, SQLiteService>();
        builder.Services.AddHttpClient<IRateService, RateService>(
            opt => opt.BaseAddress = new Uri("https://www.nbrb.by/api/exrates/rates"));

        // Register ViewModels.
        builder.Services.AddSingleton<CalculatorViewModel>();
        builder.Services.AddSingleton<ProgressDemoViewModel>();
        builder.Services.AddSingleton<SQLiteDemoViewModel>();
        builder.Services.AddSingleton<CurrencyConverterViewModel>();

        


        return builder.Build();
    }
}
