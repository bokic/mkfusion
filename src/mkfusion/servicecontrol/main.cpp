#include <windows.h>
#include <stdio.h>

bool StartWinService(char *ServiceName)
{
	SC_HANDLE l_SCMHandle = OpenSCManagerA(NULL, "ServicesActive", SC_MANAGER_ALL_ACCESS);
	if (l_SCMHandle == NULL)
	{
		return false;
	}

	SC_HANDLE l_Handle = OpenServiceA(l_SCMHandle, ServiceName, SC_MANAGER_QUERY_LOCK_STATUS);
	if (l_Handle == NULL)
	{
		CloseHandle(l_SCMHandle);
		return false;
	}

	if (StartService(l_Handle, 0, NULL) == 0)
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
	SC_HANDLE l_SCMHandle = OpenSCManagerA(NULL, "ServicesActive", SC_MANAGER_ALL_ACCESS);
	if (l_SCMHandle == NULL)
	{
		return false;
	}

	SC_HANDLE l_Handle = OpenServiceA(l_SCMHandle, ServiceName, SC_MANAGER_MODIFY_BOOT_CONFIG | SC_MANAGER_ENUMERATE_SERVICE);
	if (l_Handle == NULL)
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

	for (; ; )
	{
		if (QueryServiceStatus(l_Handle, &l_ServiceStatus) == 0)
		{
			CloseHandle(l_Handle);
			CloseHandle(l_SCMHandle);
			return false;
		}

		if (l_ServiceStatus.dwCurrentState != SERVICE_STOP_PENDING)
		{
			break;
		}

		Sleep(100);
	}

	CloseHandle(l_Handle);
	CloseHandle(l_SCMHandle);

	return true;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage:\nservicecontrol.exe <servicename> <start/stop>\n");
		return 1;
	}

	if (strcmp(argv[2], "start") == 0)
	{
		if (StartWinService(argv[1]) == false)
		{
			return 2;
		}
	}
	else if (strcmp(argv[2], "stop") == 0)
	{
		StopWinService(argv[1]);
	}
	else
	{
		printf("Error, second argument should be start or stop\nUsage:\nservicecontrol.exe <servicename> <start/stop>\n");
		return 3;
	}

	return 0;
}
