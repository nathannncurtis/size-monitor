#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <stdint.h>

#ifdef SMON_CORE_EXPORTS
#  define SMON_API __declspec(dllexport)
#else
#  define SMON_API __declspec(dllimport)
#endif

#define SMON_FLAG_DIRECTORY 0x01u
#define SMON_FLAG_SYMLINK   0x02u
#define SMON_FLAG_REPARSE   0x04u

typedef struct ScanNode {
    uint64_t size;
    uint32_t parent;
    uint32_t first_child;
    uint32_t next_sibling;
    uint32_t flags;
    uint32_t name_offset;
    uint32_t name_len;
} ScanNode;

typedef struct ScanResult {
    ScanNode* nodes;
    uint32_t  node_count;
    wchar_t*  name_buf;
    uint64_t  total_bytes;
    uint64_t  file_count;
    uint64_t  dir_count;
    double    elapsed_sec;
} ScanResult;

typedef void (CALLBACK *SmonProgressCallback)(
    uint64_t dirs_visited,
    uint64_t files_visited,
    uint64_t bytes_seen,
    void*    user_data);

typedef void* ScanHandle;

#ifdef __cplusplus
extern "C" {
#endif

SMON_API ScanHandle WINAPI Smon_BeginScan(
    const wchar_t*       path,
    SmonProgressCallback callback,
    void*                user_data);

SMON_API BOOL WINAPI Smon_Cancel(ScanHandle handle);
SMON_API BOOL WINAPI Smon_Wait(ScanHandle handle, DWORD timeout_ms);
SMON_API BOOL WINAPI Smon_GetResult(ScanHandle handle, ScanResult* out);
SMON_API void WINAPI Smon_FreeResult(ScanHandle handle);
SMON_API BOOL WINAPI Smon_IsNtfsVolume(const wchar_t* path);

#ifdef __cplusplus
}
#endif
