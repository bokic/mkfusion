#ifndef UNINSTALL_H
#define UNINSTALL_H

#include <windows.h>

extern "C" bool IsServiceInstalled(char*);
extern "C" bool IsServiceStatus(char*, DWORD); // SERVICE_RUNNING or SERVICE_STOPPED
extern "C" bool StartWinService(char*);
extern "C" bool StopWinService(char*);
extern "C" char* GetServiceExeFilename(char*);
extern "C" bool AddMKFusionToApacheConfig(char*, char*);
extern "C" bool RemoveMKFusionFromApacheConfig(char*);

#endif // UNINSTALL_H
