namespace lab5.UI.Constants;

public static class PathConstants
{
    public static string AppData 
        => Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);

    public const string RootFolder = "lab5";

    public static string DbFolder => Path.Combine(AppData, RootFolder);
    public static string ImagesFolder => Path.Combine(AppData, RootFolder, "Images");
}
