#include "uninstall.h"
#include <string.h>
#include <stdio.h>

bool IsServiceInstalled(char *ServiceName)
{
    SC_HANDLE l_SCMHandle = OpenSCManagerA(nullptr, "ServicesActive", SC_MANAGER_ALL_ACCESS);
    if (l_SCMHandle == nullptr)
	{
		return false;
	}

	SC_HANDLE l_Handle = OpenServiceA(l_SCMHandle, ServiceName, SC_MANAGER_CONNECT);
    if (l_Handle == nullptr)
	{
		CloseHandle(l_SCMHandle);
		return false;
	}

	CloseHandle(l_Handle);
	CloseHandle(l_SCMHandle);

	return true;
}

bool IsServiceStatus(char *ServiceName, DWORD ServiceStatus) // SERVICE_RUNNING or SERVICE_STOPPED
{
    SC_HANDLE l_SCMHandle = OpenSCManagerA(nullptr, "ServicesActive", SC_MANAGER_ALL_ACCESS);
    if (l_SCMHandle == nullptr)
	{
		return false;
	}

	SC_HANDLE l_Handle = OpenServiceA(l_SCMHandle, ServiceName, SC_MANAGER_ENUMERATE_SERVICE);
    if (l_Handle == nullptr)
	{
		CloseHandle(l_SCMHandle);
		return false;
	}

	SERVICE_STATUS l_ServiceStatus;
	if (QueryServiceStatus(l_Handle, &l_ServiceStatus) == 0)
	{
		CloseHandle(l_Handle);
		CloseHandle(l_SCMHandle);
		return false;
	}

	CloseHandle(l_Handle);
	CloseHandle(l_SCMHandle);

	if (l_ServiceStatus.dwCurrentState == ServiceStatus)
	{
		return true;
	}

	return false;
}

bool StartWinService(char *ServiceName)
{
    SC_HANDLE l_SCMHandle = OpenSCManagerA(nullptr, "ServicesActive", SC_MANAGER_ALL_ACCESS);
    if (l_SCMHandle == nullptr)
	{
		return false;
	}

	SC_HANDLE l_Handle = OpenServiceA(l_SCMHandle, ServiceName, SC_MANAGER_QUERY_LOCK_STATUS);
    if (l_Handle == nullptr)
	{
		CloseHandle(l_SCMHandle);
		return false;
	}

    if (StartService(l_Handle, 0, nullptr) == 0)
	{
		CloseHandle(l_Handle);
		CloseHandle(l_SCMHandle);
		return false;
	}

	CloseHandle(l_Handle);
	CloseHandle(l_SCMHandle);

	return true;
}

bool StopWinService(char *ServiceName)
{
    SC_HANDLE l_SCMHandle = OpenSCManagerA(nullptr, "ServicesActive", SC_MANAGER_ALL_ACCESS);
    if (l_SCMHandle == nullptr)
	{
		return false;
	}

	SC_HANDLE l_Handle = OpenServiceA(l_SCMHandle, ServiceName, SC_MANAGER_MODIFY_BOOT_CONFIG);
    if (l_Handle == nullptr)
	{
		CloseHandle(l_SCMHandle);
		return false;
	}

	SERVICE_STATUS l_ServiceStatus;
	if (ControlService(l_Handle, SERVICE_CONTROL_STOP, &l_ServiceStatus) == 0)
	{
		CloseHandle(l_Handle);
		CloseHandle(l_SCMHandle);
		return false;
	}

	CloseHandle(l_Handle);
	CloseHandle(l_SCMHandle);

	return true;
}

char *GetServiceExeFilename(char *ServiceName)
{
    SC_HANDLE l_SCMHandle = OpenSCManagerA(nullptr, "ServicesActive", SC_MANAGER_ALL_ACCESS);
    if (l_SCMHandle == nullptr)
	{
        return nullptr;
	}

	SC_HANDLE l_Handle = OpenServiceA(l_SCMHandle, ServiceName, SERVICE_QUERY_CONFIG);
    if (l_Handle == nullptr)
	{
		CloseHandle(l_SCMHandle);
        return nullptr;
	}

	DWORD l_BytesNeeded = 0;
    QueryServiceConfigA(l_Handle, nullptr, 0, &l_BytesNeeded);
	if (l_BytesNeeded == 0)
	{
		CloseHandle(l_Handle);
		CloseHandle(l_SCMHandle);
        return nullptr;
	}

	LPQUERY_SERVICE_CONFIGA l_QueryServiceConfig = (LPQUERY_SERVICE_CONFIGA)LocalAlloc(LPTR, l_BytesNeeded);
    if (l_QueryServiceConfig == nullptr)
	{
		CloseHandle(l_Handle);
		CloseHandle(l_SCMHandle);
        return nullptr;
	}

	if (QueryServiceConfigA(l_Handle, l_QueryServiceConfig, l_BytesNeeded, &l_BytesNeeded) == 0)
	{
		LocalFree(l_QueryServiceConfig);
		CloseHandle(l_Handle);
		CloseHandle(l_SCMHandle);
        return nullptr;
	}

	CloseHandle(l_Handle);
	CloseHandle(l_SCMHandle);

	char *ret = (char *)LocalAlloc(LPTR, strlen(l_QueryServiceConfig->lpBinaryPathName) + 1);
    if (ret == nullptr)
	{
		LocalFree(l_QueryServiceConfig);
		CloseHandle(l_Handle);
		CloseHandle(l_SCMHandle);
        return nullptr;
	}

	strcpy(ret, l_QueryServiceConfig->lpBinaryPathName);

	LocalFree(l_QueryServiceConfig);

	char *quote1 = strchr(ret, '"');
    if (quote1)
	{
		quote1++;
		char *quote2 = strchr(quote1, '"');
        if (quote2 == nullptr)
		{
			LocalFree(ret);
            return nullptr;
		}

		memmove(ret, quote1, quote2 - quote1);
		ret[quote2 - quote1] = 0;
	}

	return ret;
}

bool AddMKFusionToApacheConfig(char *FileName, char *MKFusionPath)
{
	HANDLE l_File;
	DWORD  l_FileSize;
    char  *l_FileContent;
	DWORD  l_Readed;
	int    l_BufWritten;
	DWORD  l_Written;

    l_File = CreateFileA(FileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (l_File == INVALID_HANDLE_VALUE)
	{
		return false;
	}

    l_FileSize = GetFileSize(l_File, nullptr);

    l_FileContent = (char *)LocalAlloc(LPTR, l_FileSize + 1024);
    if(l_FileContent == nullptr)
	{
		CloseHandle(l_File);
		return false;
	}

    if (ReadFile(l_File, l_FileContent, l_FileSize, &l_Readed, nullptr) == 0)
	{
		LocalFree(l_FileContent);
		CloseHandle(l_File);
		return false;
	}

	l_BufWritten = sprintf(&l_FileContent[l_FileSize],	"\r\n" \
														"### MkFusion from here\r\n" \
														"### Generated by MkFusion installer, please don\'t modify\r\n" \
														"Include \"%smkfusion.conf\"\r\n" \
														"### MkFusion to here\r\n", MKFusionPath);

	if (l_BufWritten == -1)
	{
		LocalFree(l_FileContent);
		CloseHandle(l_File);
		return false;
	}

    if (SetFilePointer(l_File, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		LocalFree(l_FileContent);
		CloseHandle(l_File);
		return false;
	}

    if (WriteFile(l_File, l_FileContent, l_FileSize + l_BufWritten, &l_Written, nullptr) == 0)
	{
		LocalFree(l_FileContent);
		CloseHandle(l_File);
		return false;
	}

	CloseHandle(l_File);
	return true;
}

bool RemoveMKFusionFromApacheConfig(char *FileName)
{
	HANDLE l_File;
	DWORD  l_FileSize;
    char  *l_FileContent;
	DWORD  l_Readed;
	DWORD  l_Written;

    l_File = CreateFileA(FileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (l_File == INVALID_HANDLE_VALUE)
	{
		return false;
	}

    l_FileSize = GetFileSize(l_File, nullptr);

    l_FileContent = (char *)LocalAlloc(LMEM_FIXED, l_FileSize + 1);

    if (ReadFile(l_File, l_FileContent, l_FileSize, &l_Readed, nullptr) == 0)
	{
		LocalFree(l_FileContent);
		CloseHandle(l_File);
		return false;
	}
	l_FileContent[l_FileSize] = 0;

    char *from = strstr(l_FileContent, "\r\n### MkFusion from here\r\n");
    if (from == nullptr)
	{
		LocalFree(l_FileContent);
		CloseHandle(l_File);
		return false;
	}

    char *to = strstr(from, "\r\n### MkFusion to here\r\n");
    if (to == nullptr)
	{
		LocalFree(l_FileContent);
		CloseHandle(l_File);
		return false;
	}

	if (to + strlen("\r\n### MkFusion to here\r\n") < l_FileContent + strlen(l_FileContent))
	{
		memmove(from, to + strlen("\r\n### MkFusion to here\r\n") - 2, strlen(to) - strlen("\r\n### MkFusion to here\r\n") + 3);
	}

    if (SetFilePointer(l_File, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		LocalFree(l_FileContent);
		CloseHandle(l_File);
		return false;
	}

    if (WriteFile(l_File, l_FileContent, strlen(l_FileContent), &l_Written, nullptr) == 0)
	{
		LocalFree(l_FileContent);
		CloseHandle(l_File);
		return false;
	}

    if (SetFilePointer(l_File, l_FileSize - (to - from + strlen("\r\n### MkFusion to here\r\n")), nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		LocalFree(l_FileContent);
		CloseHandle(l_File);
		return false;
	}

	bool ret = SetEndOfFile(l_File);

	CloseHandle(l_File);

	return ret;
}

/*int main(int argc, char *argv[])
{
	bool ret;

	//bool ret = IsServiceInstalled("apache2.2");
	//ret = IsServiceStatus("apache2.2", SERVICE_RUNNING); // SERVICE_RUNNING, SERVICE_STOPPED
	//ret = StartWinService("apache2.2");
	//ret = StopWinService("apache2.2");
    //char *name = GetServiceExeFilename("apache2.2");
    //if (name)
	//{
	//	LocalFree(name);
	//}
	ret = AddMKFusionToApacheConfig("D:\\Projects\\MKFusion\\install\\temp\\httpd.conf", "D:\\Projects\\MKFusion\\release\\");
	ret = RemoveMKFusionFromApacheConfig("D:\\Projects\\MKFusion\\install\\temp\\httpd.conf");

	return ret;
}*/
