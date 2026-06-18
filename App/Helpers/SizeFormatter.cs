namespace SizeMonitor.Helpers;

public static class SizeFormatter
{
    public static string FormatBytes(ulong bytes)
    {
        return bytes switch
        {
            >= 1_000_000_000_000UL => $"{bytes / 1_099_511_627_776.0:F2} TB",
            >= 1_000_000_000UL     => $"{bytes / 1_073_741_824.0:F2} GB",
            >= 1_000_000UL         => $"{bytes / 1_048_576.0:F1} MB",
            >= 1_000UL             => $"{bytes / 1_024.0:F1} KB",
            _                      => $"{bytes} B",
        };
    }
}
