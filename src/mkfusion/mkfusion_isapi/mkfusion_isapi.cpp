#include <windows.h>
#include "iis/httpext.h"

BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO *pVer)
{
	pVer->dwExtensionVersion = HSE_VERSION;
	strncpy(pVer->lpszExtensionDesc, "MKFusion ISAPI Extension", HSE_MAX_EXT_DLL_NAME_LEN);

	return true;
}

DWORD WINAPI HttpExtensionProc(LPEXTENSION_CONTROL_BLOCK lpECB)
{
	lpECB->dwHttpStatusCode = 200;
	//lpECB->lpszContentType = "text/html";

	const char *header = "Content-Type: text/plain\r\n\r\n";
	DWORD headerlen  = strlen( header );
	lpECB->ServerSupportFunction(lpECB->ConnID, HSE_REQ_SEND_RESPONSE_HEADER, 0, &headerlen, (DWORD *)header);

	char l_sent[] = "Test";
	DWORD l_len = strlen(l_sent);
	lpECB->WriteClient(lpECB->ConnID, (void*)l_sent, &l_len, HSE_IO_SYNC);

	return HSE_STATUS_SUCCESS;
}
