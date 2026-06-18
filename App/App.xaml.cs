using System.Windows;
using System.Windows.Media;
using Wpf.Ui.Appearance;
using Wpf.Ui.Controls;

namespace SizeMonitor;

public partial class App : Application
{
    protected override void OnStartup(StartupEventArgs e)
    {
        base.OnStartup(e);

        var accent = Color.FromArgb(0xFF, 0x4C, 0x9D, 0xFF);
        ApplicationAccentColorManager.Apply(accent, ApplicationTheme.Dark, systemGlassColor: false, systemAccentColor: false);
        ApplicationThemeManager.Apply(ApplicationTheme.Dark, WindowBackdropType.Mica, updateAccent: false);

        new MainWindow().Show();
    }
}
