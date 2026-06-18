#include "../include/smon_api.h"
#include <cstdio>

int wmain(int argc, wchar_t* argv[])
{
    const wchar_t* path = argc > 1 ? argv[1] : L"C:\\Windows\\System32";
    wprintf(L"scan_test: %s\n", path);

    ScanHandle h = Smon_BeginScan(path, nullptr, nullptr);
    if (!h) { wprintf(L"Smon_BeginScan returned null\n"); return 1; }

    Smon_Wait(h, INFINITE);

    ScanResult r{};
    if (Smon_GetResult(h, &r))
        wprintf(L"nodes=%u  total=%llu bytes\n", r.node_count, r.total_bytes);
    else
        wprintf(L"Smon_GetResult failed\n");

    Smon_FreeResult(h);
    return 0;
}
