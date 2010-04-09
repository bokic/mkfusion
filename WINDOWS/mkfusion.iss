[Setup]
AppName=MKFusion
AppVerName=MKFusion
AppPublisher=BokiCSoft
AppPublisherURL=http://mkfusion.bokicsoft.com/
AppVersion=0.4.1
DefaultDirName={pf}\BokiCSoft\MKFusion
DefaultGroupName=CFEditor
UninstallDisplayIcon={app}\MKFusion.exe
Compression=lzma
;Compression=none
SolidCompression=yes
OutputBaseFilename=MKFusion
OutputDir=.
VersionInfoVersion=0.4.1
VersionInfoDescription=MKFusion is free, opensource, multiplatform ColdFusion application server(Qt 4.6.2)

[Dirs]
Name: "{app}\bin";
Name: "{app}\bin\sqldrivers";
Name: "{app}\include";
Name: "{app}\lib";
Name: "{app}\logs";
Name: "{app}\templates";

[Files]
; MinGW runtime
Source: "c:\Qt\4.6.2\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}\bin";
Source: "c:\Qt\4.6.2\bin\mingwm10.dll"; DestDir: "{app}\bin";

Source: "c:\Qt\4.6.2\bin\QtCore4.dll"; DestDir: "{app}\bin";
Source: "c:\Qt\4.6.2\bin\QtNetwork4.dll"; DestDir: "{app}\bin";
Source: "c:\Qt\4.6.2\bin\QtSql4.dll"; DestDir: "{app}\bin";
Source: "c:\Qt\4.6.2\bin\QtXml4.dll"; DestDir: "{app}\bin";
Source: "..\bin\mkfusion.exe"; DestDir: "{app}\bin"; Flags: ignoreversion;
Source: "..\bin\mod_mkfusion.dll"; DestDir: "{app}\bin"; Flags: ignoreversion;
Source: "..\install\mkfusion.db"; DestDir: "{app}\bin"; Flags: onlyifdoesntexist;
Source: "uninstall.dll"; DestDir: "{app}"; Flags: ignoreversion;

Source: "c:\Qt\4.6.2\plugins\sqldrivers\qsqlite4.dll"; DestDir: "{app}\bin\sqldrivers";
Source: "c:\Qt\4.6.2\plugins\sqldrivers\qsqlodbc4.dll"; DestDir: "{app}\bin\sqldrivers";
Source: "c:\Qt\4.6.2\plugins\sqldrivers\qsqlmysql4.dll"; DestDir: "{app}\bin\sqldrivers";
Source: "c:\Qt\4.6.2\plugins\sqldrivers\qsqlpsql4.dll"; DestDir: "{app}\bin\sqldrivers";

;Source: "..\runtime\comerr32.dll"; DestDir: "{app}\bin";
;Source: "runtime\gssapi32.dll"; DestDir: "{app}\bin";
;Source: "runtime\k5sprt32.dll"; DestDir: "{app}\bin";
;Source: "runtime\krb5_32.dll"; DestDir: "{app}\bin";
;Source: "..\libs\libssh\bin\libeay32.dll"; DestDir: "{app}\bin";
;Source: "runtime\libiconv-2.dll"; DestDir: "{app}\bin";
;Source: "runtime\libintl-8.dll"; DestDir: "{app}\bin";
;Source: "runtime\ssleay32.dll"; DestDir: "{app}\bin";

Source: "uninstall.dll"; Flags: dontcopy;

Source: "..\bin\lib\mkfusion.a"; DestDir: "{app}\lib"; Flags: ignoreversion;

Source: "..\bin\include\common.h"; DestDir: "{app}\include"; Flags: ignoreversion;
Source: "..\bin\include\qcfrunningtemplate.h"; DestDir: "{app}\include"; Flags: ignoreversion;
Source: "..\bin\include\qcftemplate.h"; DestDir: "{app}\include"; Flags: ignoreversion;
Source: "..\bin\include\qmkfusionexception.h"; DestDir: "{app}\include"; Flags: ignoreversion;
Source: "..\bin\include\qwddx.h"; DestDir: "{app}\include"; Flags: ignoreversion;

[Code]

const
    // Some constants for CreateFile ().
    GENERIC_READ           = $80000000;
    GENERIC_WRITE          = $40000000;
    GENERIC_EXECUTE        = $20000000;
    GENERIC_ALL            = $10000000;
    FILE_SHARE_READ        = 1;
    FILE_SHARE_WRITE       = 2;
    FILE_SHARE_DELETE      = 4;
    CREATE_NEW             = 1;
    CREATE_ALWAYS          = 2;
    OPEN_EXISTING          = 3;
    OPEN_ALWAYS            = 4;
    TRUNCATE_EXISTING      = 5;
    FILE_READ_ATTRIBUTES   = $80;
    FILE_WRITE_ATTRIBUTES  = $100;

    // General Win32.
    INVALID_HANDLE_VALUE   = -1;

    SERVICE_STOPPED	= 1;
    SERVICE_RUNNING = 4;
    
const
    //SW_HIDE = 0;
    SW_NORMAL = 1;
    //SW_SHOWNORMAL = 1;
    //SW_SHOWMINIMIZED = 2;
    SW_MAXIMIZE = 3;
    //SW_SHOWMAXIMIZED = 3;
    SW_SHOWNOACTIVATE = 4;
    //SW_SHOW = 5;
    SW_MINIMIZE = 6;
    //SW_SHOWMINNOACTIVE = 7;
    SW_SHOWNA = 8;
    SW_RESTORE = 9;
    SW_SHOWDEFAULT = 10;
    SW_FORCEMINIMIZE = 11;
    SW_MAX = 11;

function CreateFile (
    lpFileName             : String;
    dwDesiredAccess        : Cardinal;
    dwShareMode            : Cardinal;
    lpSecurityAttributes   : Cardinal;
    dwCreationDisposition  : Cardinal;
    dwFlagsAndAttributes   : Cardinal;
    hTemplateFile          : Integer
): Integer; external 'CreateFileA@kernel32.dll stdcall';
function WriteFile (
     hFile:                      THandle;
     lpBuffer:                   String;
     nNumberOfBytesToWrite:      LongInt;
     var lpNumberOfBytesWritten: LongInt;
     lpOverlapped:               LongInt
) : Boolean; external 'WriteFile@kernel32.dll stdcall';
function CloseHandle (hHandle: THandle): Boolean; external 'CloseHandle@kernel32.dll stdcall';
function LocalFree(data: PChar): Integer; external 'LocalFree@Kernel32.dll stdcall';
function ShellExecute(hwnd: HWND; Operation: PChar; File: PChar; Parameters: PChar; Directory: PChar; ShowCmd: Integer): Integer; external 'ShellExecuteA@shell32.dll stdcall';

function IsServiceInstalled(ServiceName: PChar): Boolean; external 'IsServiceInstalled@files:uninstall.dll cdecl';
function IsServiceStatus(ServiceName: PChar; Status: DWORD): Boolean; external 'IsServiceStatus@files:uninstall.dll cdecl';
function StartWinService(ServiceName: PChar): Boolean; external 'StartWinService@files:uninstall.dll cdecl';
function StopWinService(ServiceName: PChar): Boolean; external 'StopWinService@files:uninstall.dll cdecl';
function GetServiceExeFilename(ServiceName: PChar): PChar; external 'GetServiceExeFilename@files:uninstall.dll cdecl';
function AddMKFusionToApacheConfig(FileName: PChar; MKFusionPath: String): Boolean; external 'AddMKFusionToApacheConfig@files:uninstall.dll cdecl';
function RemoveMKFusionFromApacheConfig(FileName: PChar): Boolean; external 'RemoveMKFusionFromApacheConfig@files:uninstall.dll cdecl';
function UnIsServiceInstalled(ServiceName: PChar): Boolean; external 'IsServiceInstalled@{app}\uninstall.dll cdecl uninstallonly';
function UnIsServiceStatus(ServiceName: PChar; Status: DWORD): Boolean; external 'IsServiceStatus@{app}\uninstall.dll cdecl uninstallonly';
function UnStartWinService(ServiceName: PChar): Boolean; external 'StartWinService@{app}\uninstall.dll cdecl uninstallonly';
function UnStopWinService(ServiceName: PChar): Boolean; external 'StopWinService@{app}\uninstall.dll cdecl uninstallonly';
function UnGetServiceExeFilename(ServiceName: PChar): PChar; external 'GetServiceExeFilename@{app}\uninstall.dll cdecl uninstallonly';
function UnRemoveMKFusionFromApacheConfig(FileName: PChar): Boolean; external 'RemoveMKFusionFromApacheConfig@{app}\uninstall.dll cdecl uninstallonly';

function InitializeSetup(): Boolean;
var
  tmpServiceFileName: PChar;
  ApacheDir: String;
  QtDir: String;
  MinGWDir: String;
  Names: TArrayOfString;
  i: Integer;
begin
  if (IsWin64)Then
  begin
    MsgBox('Please use 32bit version of Apache.', mbinformation, MB_OK)
  end;

  if (IsServiceInstalled('Apache2.2') = False)Then
  begin
    MsgBox('Please install Apache2.2(http://httpd.apache.org/download.cgi).', mbError, MB_OK);
    ShellExecute(0, 'open', 'http://httpd.apache.org/download.cgi', '', '', SW_SHOWNOACTIVATE);
    Result := False;
    exit;
  end;

  tmpServiceFileName := GetServiceExeFilename('Apache2.2');
  ApacheDir := tmpServiceFileName;
  if (tmpServiceFileName <> nil) Then
    LocalFree(tmpServiceFileName);

  ApacheDir := ExtractFileDir(ApacheDir);

  if RegGetSubkeyNames(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall', Names) then
    begin
    for I := 0 to GetArrayLength(Names)-1 do
      begin
      if (Copy(Names[I], 0, 6) = 'Qt SDK') then
        begin
        RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\' + Names[I], 'QTSDK_INSTDIR', QtDir);
        MinGWDir := QtDir + '\mingw';
        end;
      if (Copy(Names[I], 0, 14) = 'Qt OpenSource ') then
        begin
        RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\' + Names[I], 'MINGW_INSTDIR', QtDir);// MINGW_INSTDIR = Qt Install bug.
        RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\' + Names[I], 'MinGWInstDir', MinGWDir);
        end;
      end;
    end
    else
    begin
    MsgBox('Failed to open registry.', mbError, MB_OK);
    Result := False;
    exit;
    end;

    if (QtDir = '') then
      begin
      MsgBox('Please install QtDevelopment(http://qt.nokia.com/downloads/windows-cpp) or QtSDK(http://qt.nokia.com/downloads/sdk-windows-cpp), and run this installer one more time.', mbError, MB_OK);
      ShellExecute(0, 'open', 'http://qt.nokia.com/downloads/windows-cpp', '', '', SW_SHOWNOACTIVATE);
      Result := False;
      exit;
      end;
  Result := True;
end;

procedure CurStepChanged(CurStep: TSetupStep);
var
  ApacheExec: PChar;
  ApacheDir: String;
  MKFusionBinDir: String;
  ConfContent: String;
  FileHdl: THandle;
  written: Integer;
  ResultCode: Integer;
begin
  if (CurStep=ssPostInstall)Then
  begin
    ConfContent := 'LoadFile  "' + ExpandConstant('{app}\bin\mingwm10.dll') + '"' + Chr(13) + Chr(10) +
                   'LoadFile  "' + ExpandConstant('{app}\bin\libgcc_s_dw2-1.dll') + '"' + Chr(13) + Chr(10) +
                   'LoadFile  "' + ExpandConstant('{app}\bin\QtCore4.dll') + '"' + Chr(13) + Chr(10) +
                   'LoadFile  "' + ExpandConstant('{app}\bin\QtNetwork4.dll') + '"' + Chr(13) + Chr(10) +
                   'LoadModule mkfusion_module "' + ExpandConstant('{app}\bin\mod_mkfusion.dll') + '"' + Chr(13) + Chr(10) +
                   '#<IfModule mod_mkfusion.c>' + Chr(13) + Chr(10) +
                   '  AddType application/x-httpd-mkfusion .cfm' + Chr(13) + Chr(10) +
                   '#</IfModule>' + Chr(13) + Chr(10);
    FileHdl := CreateFile(ExpandConstant('{app}') + '\bin\mkfusion.conf', GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
    WriteFile(FileHdl, PChar(ConfContent), Length(ConfContent), written, 0);
    CloseHandle(FileHdl);

    ApacheExec := GetServiceExeFilename('Apache2.2');
    ApacheDir := ApacheExec;
    if (ApacheExec <> nil) Then
      LocalFree(ApacheExec);

    ApacheDir := ExtractFileDir(ApacheDir);
    ApacheDir := ExtractFileDir(ApacheDir) + '\conf\httpd.conf';
    MKFusionBinDir := ExpandConstant('{app}') + '\bin\';

    RemoveMKFusionFromApacheConfig(ApacheDir);
    if (AddMKFusionToApacheConfig(ApacheDir, MKFusionBinDir) = False)Then
    begin
      MsgBox('Coulnd''t setup mkfusion apache module. Please add it manually.', mbError, MB_OK);
    end;

    DelTree(ExpandConstant('{app}\templates\*'), False, True, True);

    if (IsServiceStatus('Apache2.2', SERVICE_RUNNING) = True)Then
    begin
      if (StopWinService('Apache2.2') = False)Then
        exit;

      repeat
      Sleep(100);
      until (IsServiceStatus('Apache2.2', SERVICE_STOPPED) = True)

      StartWinService('Apache2.2')
    end;
    
    if Exec(ExpandConstant('{app}\bin\mkfusion.exe'), '-i', '', SW_HIDE, ewWaitUntilTerminated, ResultCode) then
    begin
      StartWinService('mkfusion');
    end;
  end;
end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
var
  ApacheExec: PChar;
  ApacheDir: String;
  ResultCode: Integer;
  WasApacheRunning: Boolean;
  WasMKFusionRunning: Boolean;
begin
  if (CurUninstallStep = usUninstall)Then
  begin
    if (UnIsServiceInstalled('mkfusion') = False)Then
    begin
      MsgBox('mkfusion service not found.', mbError, MB_OK);
      UnloadDLL(ExpandConstant('{app}\uninstall.dll'));
      exit;
    end;

    if (UnIsServiceInstalled('Apache2.2') = False)Then
    begin
      MsgBox('Apache2.2 service not found.', mbError, MB_OK);
      UnloadDLL(ExpandConstant('{app}\uninstall.dll'));
      exit;
    end;

    WasMKFusionRunning := UnIsServiceStatus('mkfusion', SERVICE_RUNNING);

    if (WasMKFusionRunning = True)Then
    begin
      UnStopWinService('mkfusion')
    end;
    repeat
      Sleep(100);
    until (UnIsServiceStatus('mkfusion', SERVICE_STOPPED) = True)
    
    Exec(ExpandConstant('{app}\bin\mkfusion.exe'), '-u', '', SW_HIDE, ewWaitUntilTerminated, ResultCode);

    WasApacheRunning := UnIsServiceStatus('Apache2.2', SERVICE_RUNNING);

    if (WasApacheRunning = True)Then
    begin
      UnStopWinService('Apache2.2')
    end;
    repeat
      Sleep(100);
    until (UnIsServiceStatus('Apache2.2', SERVICE_STOPPED) = True)

    ApacheExec := UnGetServiceExeFilename('Apache2.2');
    ApacheDir := ApacheExec;
    if (ApacheExec <> nil) Then
      LocalFree(ApacheExec);

    ApacheDir := ExtractFileDir(ApacheDir);
    ApacheDir := ExtractFileDir(ApacheDir) + '\conf\httpd.conf';
    
    if (UnRemoveMKFusionFromApacheConfig(ApacheDir) = False)Then
    begin
      MsgBox('Coulnd''t setup mkfusion apache module. Please remove it manually.', mbError, MB_OK);
      UnloadDLL(ExpandConstant('{app}\uninstall.dll'));
      exit;
    end;

    DeleteFile(ExpandConstant('{app}\bin\mkfusion.conf'));
    DelTree(ExpandConstant('{app}\templates'), True, True, True);

    if (WasApacheRunning = True)Then
    begin
      UnStartWinService('Apache2.2')
    end;

    UnloadDLL(ExpandConstant('{app}\uninstall.dll'));
    DeleteFile(ExpandConstant('{app}\uninstall.dll'));
  end;
end;
end.

