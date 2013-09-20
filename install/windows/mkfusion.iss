[Setup]
AppName=MKFusion
AppVerName=MKFusion version {#PACKAGE_VERSION}
AppPublisher=BokiCSoft
AppPublisherURL=http://mkfusion.bokicsoft.com/
AppVersion={#PACKAGE_VERSION}
DefaultDirName={pf}\BokiCSoft\MKFusion
DefaultGroupName=CFEditor
UninstallDisplayIcon={app}\MKFusion.exe
Compression=lzma
;Compression=none
SolidCompression=yes
OutputBaseFilename=MKFusion_{#PACKAGE_VERSION}
OutputDir=.
VersionInfoVersion={#PACKAGE_VERSION}
VersionInfoDescription=MKFusion is free ColdFusion application server(Qt 5.1.1)

[Dirs]
Name: "{app}\bin";
Name: "{app}\bin\mingw";
Name: "{app}\bin\sqldrivers";
Name: "{app}\bin\qt";
Name: "{app}\include";
Name: "{app}\lib";
Name: "{app}\logs";
Name: "{app}\templates";

[Files]
; MinGW runtime
Source: "C:\Qt\5.1.1\mingw48_32\bin\libwinpthread-1.dll"; DestDir: "{app}\bin";
Source: "C:\Qt\5.1.1\mingw48_32\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}\bin";
Source: "C:\Qt\5.1.1\mingw48_32\bin\libstdc++-6.dll"; DestDir: "{app}\bin";

; ICU unicode/utf conversion tables
Source: "C:\Qt\5.1.1\mingw48_32\bin\icudt51.dll"; DestDir: "{app}\bin";
Source: "C:\Qt\5.1.1\mingw48_32\bin\icuin51.dll"; DestDir: "{app}\bin";
Source: "C:\Qt\5.1.1\mingw48_32\bin\icuuc51.dll"; DestDir: "{app}\bin";

; Qt library
Source: "C:\Qt\5.1.1\mingw48_32\bin\Qt5Core.dll"; DestDir: "{app}\bin";
Source: "C:\Qt\5.1.1\mingw48_32\bin\Qt5Network.dll"; DestDir: "{app}\bin";
Source: "C:\Qt\5.1.1\mingw48_32\bin\Qt5Sql.dll"; DestDir: "{app}\bin";
Source: "C:\Qt\5.1.1\mingw48_32\bin\Qt5Xml.dll"; DestDir: "{app}\bin";

; MKFusion service app
Source: "..\..\bin\mkfusion.exe"; DestDir: "{app}\bin"; Flags: ignoreversion;

; MKFusion Apache 2.2 module
Source: "..\..\bin\mod_mkfusion.dll"; DestDir: "{app}\bin"; Flags: ignoreversion;

; MKFusion config database
Source: "..\..\install\mkfusion.db"; DestDir: "{app}\bin"; Flags: onlyifdoesntexist;

; MKFusion uninstall dll
Source: "uninstall.dll"; DestDir: "{app}"; Flags: ignoreversion;

; MinGW 4.8
Source: "..\..\bin\mingw\*"; DestDir: "{app}\bin\mingw"; Flags: recursesubdirs;

; Qt 5.1.1 include and lib files
Source: "..\..\bin\qt\*"; DestDir: "{app}\bin\qt"; Flags: recursesubdirs;

; Qt Database modules
Source: "C:\Qt\5.1.1\mingw48_32\plugins\sqldrivers\qsqlite.dll"; DestDir: "{app}\bin\sqldrivers";
Source: "C:\Qt\5.1.1\mingw48_32\plugins\sqldrivers\qsqlodbc.dll"; DestDir: "{app}\bin\sqldrivers";
;Source: "C:\Qt\5.1.1\mingw48_32\plugins\sqldrivers\qsqlmysql.dll"; DestDir: "{app}\bin\sqldrivers";
;Source: "C:\Qt\5.1.1\mingw48_32\plugins\sqldrivers\qsqlpsql.dll"; DestDir: "{app}\bin\sqldrivers";

; MKFusion uninstall dll(forgot why is here)
Source: "uninstall.dll"; Flags: dontcopy;

; MKFusion support library for template compiling
Source: "..\..\lib\mkfusion.a"; DestDir: "{app}\lib"; Flags: ignoreversion;

; MKFusion support headers for template compiling
Source: "..\..\src\mkfusion\appserver\cffunctions.h"; DestDir: "{app}\include"; Flags: ignoreversion;
Source: "..\..\src\mkfusion\appserver\common.h"; DestDir: "{app}\include"; Flags: ignoreversion;
Source: "..\..\src\mkfusion\appserver\qcfrunningtemplate.h"; DestDir: "{app}\include"; Flags: ignoreversion;
Source: "..\..\src\mkfusion\appserver\qcftemplate.h"; DestDir: "{app}\include"; Flags: ignoreversion;
Source: "..\..\src\mkfusion\appserver\qmkfusionexception.h"; DestDir: "{app}\include"; Flags: ignoreversion;
Source: "..\..\src\mkfusion\appserver\qwddx.h"; DestDir: "{app}\include"; Flags: ignoreversion;

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

function IsWinServiceInstalled(ServiceName: PChar): Boolean; external 'IsWinServiceInstalled@files:uninstall.dll cdecl';
function GetWinServiceStatus(ServiceName: PChar; Status: DWORD): Boolean; external 'GetWinServiceStatus@files:uninstall.dll cdecl';
function StartWinService(ServiceName: PChar): Boolean; external 'StartWinService@files:uninstall.dll cdecl';
function StopWinService(ServiceName: PChar): Boolean; external 'StopWinService@files:uninstall.dll cdecl';
function GetWinServiceExeFilename(ServiceName: PChar): PChar; external 'GetWinServiceExeFilename@files:uninstall.dll cdecl';
function AddMKFusionToApacheConfig(FileName: PChar; MKFusionPath: String): Boolean; external 'AddMKFusionToApacheConfig@files:uninstall.dll cdecl';
function RemoveMKFusionFromApacheConfig(FileName: PChar): Boolean; external 'RemoveMKFusionFromApacheConfig@files:uninstall.dll cdecl';
function UnIsWinServiceInstalled(ServiceName: PChar): Boolean; external 'IsWinServiceInstalled@{app}\uninstall.dll cdecl uninstallonly';
function UnGetWinServiceStatus(ServiceName: PChar; Status: DWORD): Boolean; external 'GetWinServiceStatus@{app}\uninstall.dll cdecl uninstallonly';
function UnStartWinService(ServiceName: PChar): Boolean; external 'StartWinService@{app}\uninstall.dll cdecl uninstallonly';
function UnStopWinService(ServiceName: PChar): Boolean; external 'StopWinService@{app}\uninstall.dll cdecl uninstallonly';
function UnGetWinServiceExeFilename(ServiceName: PChar): PChar; external 'GetWinServiceExeFilename@{app}\uninstall.dll cdecl uninstallonly';
function UnRemoveMKFusionFromApacheConfig(FileName: PChar): Boolean; external 'RemoveMKFusionFromApacheConfig@{app}\uninstall.dll cdecl uninstallonly';

function InitializeSetup(): Boolean;
var
  tmpServiceFileName: PChar;
  ApacheDir: String;
begin
  if (IsWin64)Then
  begin
    MsgBox('Please use 32bit version of Apache.', mbinformation, MB_OK)
  end;

  if (IsWinServiceInstalled('Apache2.2') = False)Then
  begin
    MsgBox('Please install Apache2.2(http://httpd.apache.org/download.cgi).', mbError, MB_OK);
    ShellExecute(0, 'open', 'http://httpd.apache.org/download.cgi', '', '', SW_SHOWNOACTIVATE);
    Result := False;
    exit;
  end;

  tmpServiceFileName := GetWinServiceExeFilename('Apache2.2');
  ApacheDir := tmpServiceFileName;
  if (tmpServiceFileName <> nil) Then
    LocalFree(tmpServiceFileName);

  ApacheDir := ExtractFileDir(ApacheDir);

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
    ConfContent := 'LoadFile  "' + ExpandConstant('{app}\bin\libwinpthread-1.dll') + '"' + Chr(13) + Chr(10) +
                   'LoadFile  "' + ExpandConstant('{app}\bin\libgcc_s_dw2-1.dll') + '"' + Chr(13) + Chr(10) +
                   'LoadFile  "' + ExpandConstant('{app}\bin\libstdc++-6.dll') + '"' + Chr(13) + Chr(10) +
                   'LoadFile  "' + ExpandConstant('{app}\bin\icudt51.dll') + '"' + Chr(13) + Chr(10) +
                   'LoadFile  "' + ExpandConstant('{app}\bin\icuuc51.dll') + '"' + Chr(13) + Chr(10) +
                   'LoadFile  "' + ExpandConstant('{app}\bin\icuin51.dll') + '"' + Chr(13) + Chr(10) +
                   'LoadFile  "' + ExpandConstant('{app}\bin\Qt5Core.dll') + '"' + Chr(13) + Chr(10) +
                   'LoadFile  "' + ExpandConstant('{app}\bin\Qt5Network.dll') + '"' + Chr(13) + Chr(10) +
                   'LoadModule mkfusion_module "' + ExpandConstant('{app}\bin\mod_mkfusion.dll') + '"' + Chr(13) + Chr(10) +
                   '#<IfModule mod_mkfusion.c>' + Chr(13) + Chr(10) +
                   '  AddType application/x-httpd-mkfusion .cfm' + Chr(13) + Chr(10) +
                   '#</IfModule>' + Chr(13) + Chr(10);
    FileHdl := CreateFile(ExpandConstant('{app}') + '\bin\mkfusion.conf', GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
    WriteFile(FileHdl, PChar(ConfContent), Length(ConfContent), written, 0);
    CloseHandle(FileHdl);

    ApacheExec := GetWinServiceExeFilename('Apache2.2');
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

    if (GetWinServiceStatus('Apache2.2', SERVICE_RUNNING) = True)Then
    begin
      if (StopWinService('Apache2.2') = False)Then
        exit;

      repeat
      Sleep(100);
      until (GetWinServiceStatus('Apache2.2', SERVICE_STOPPED) = True)

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
    if (UnIsWinServiceInstalled('mkfusion') = False)Then
    begin
      MsgBox('mkfusion service not found.', mbError, MB_OK);
      UnloadDLL(ExpandConstant('{app}\uninstall.dll'));
      exit;
    end;

    if (UnIsWinServiceInstalled('Apache2.2') = False)Then
    begin
      MsgBox('Apache2.2 service not found.', mbError, MB_OK);
      UnloadDLL(ExpandConstant('{app}\uninstall.dll'));
      exit;
    end;

    WasMKFusionRunning := UnGetWinServiceStatus('mkfusion', SERVICE_RUNNING);

    if (WasMKFusionRunning = True)Then
    begin
      UnStopWinService('mkfusion')
    end;
    repeat
      Sleep(100);
    until (UnGetWinServiceStatus('mkfusion', SERVICE_STOPPED) = True)
    
    Exec(ExpandConstant('{app}\bin\mkfusion.exe'), '-u', '', SW_HIDE, ewWaitUntilTerminated, ResultCode);

    WasApacheRunning := UnGetWinServiceStatus('Apache2.2', SERVICE_RUNNING);

    if (WasApacheRunning = True)Then
    begin
      UnStopWinService('Apache2.2')
    end;
    repeat
      Sleep(100);
    until (UnGetWinServiceStatus('Apache2.2', SERVICE_STOPPED) = True)

    ApacheExec := UnGetWinServiceExeFilename('Apache2.2');
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

