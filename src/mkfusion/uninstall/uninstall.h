#pragma once

#include <windows.h>

extern "C" bool IsWinServiceInstalled(char *);
extern "C" bool GetWinServiceStatus(char *, DWORD); // SERVICE_RUNNING or SERVICE_STOPPED
extern "C" bool StartWinService(char *);
extern "C" bool StopWinService(char *);
extern "C" char *GetWinServiceExeFilename(char *);
extern "C" bool AddMKFusionToApacheConfig(char *, char *);
extern "C" bool RemoveMKFusionFromApacheConfig(char *);
