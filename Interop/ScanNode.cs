using System.Runtime.InteropServices;

namespace SizeMonitor.Interop;

[StructLayout(LayoutKind.Sequential)]
public struct ScanNode
{
    public ulong Size;
    public uint  Parent;
    public uint  FirstChild;
    public uint  NextSibling;
    public uint  Flags;
    public uint  NameOffset;
    public uint  NameLen;
}

public static class ScanNodeFlags
{
    public const uint Directory = 0x01;
    public const uint Symlink   = 0x02;
    public const uint Reparse   = 0x04;
}
