[Setup]
AppName=CFEditor
AppVerName=CFEditor version 0.4.1
AppPublisher=BokiCSoft
AppPublisherURL=http://mkfusion.bokicsoft.com/
AppVersion=0.4.1
DefaultDirName={pf}\BokiCSoft\CFEditor
DefaultGroupName=CFEditor
UninstallDisplayIcon={app}\cfeditor.exe
Compression=lzma
;Compression=none
SolidCompression=yes
OutputBaseFilename=CFEditor
OutputDir=.
VersionInfoVersion=0.4.1
VersionInfoDescription=CFEditor is free, opensource, multiplatform ColdFusion Editor(Qt 4.7.0)

[Files]

; MSVC9 runtime
; Source: "runtime\vcredist_x86.exe"; DestDir: "{tmp}";

; MinGW runtime
Source: "c:\Qt\4.7.0\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}";
Source: "c:\Qt\4.7.0\bin\mingwm10.dll"; DestDir: "{app}";

; QT library
Source: "c:\Qt\4.7.0\bin\QtCore4.dll"; DestDir: "{app}";
Source: "c:\Qt\4.7.0\bin\QtGui4.dll"; DestDir: "{app}";
Source: "c:\Qt\4.7.0\bin\QtNetwork4.dll"; DestDir: "{app}";
Source: "c:\Qt\4.7.0\bin\QtXml4.dll"; DestDir: "{app}";
Source: "c:\Qt\4.7.0\bin\QtWebKit4.dll"; DestDir: "{app}";

; libssh library
Source: "..\..\libs\libssh\bin\libeay32.dll"; DestDir: "{app}";
Source: "..\..\libs\libssh\bin\libssh.dll"; DestDir: "{app}";
Source: "..\..\libs\libssh\bin\ssleay32.dll"; DestDir: "{app}";

; main program
Source: "..\..\bin\cfeditor.exe"; DestDir: "{app}";

[Icons]
Name: "{group}\CFEditor"; Filename: "{app}\cfeditor.exe"

[Registry]
Root: HKCR; Subkey: ".cfes"; ValueData :"CFEditor"; Flags: uninsdeletekey;
Root: HKCR; Subkey: ".cfm"; ValueData :"CFEditor"; Flags: uninsdeletekey;
Root: HKCR; Subkey: ".cfc"; ValueData :"CFEditor"; Flags: uninsdeletekey;
Root: HKCR; Subkey: "CFEditor"; ValueType: "string"; ValueData :"Coldfusion editor site definition"; Flags: uninsdeletekey
Root: HKCR; Subkey: "CFEditor"; ValueName: "BrowserFlags"; ValueType: "dword"; ValueData :"8"; Flags: uninsdeletekey
Root: HKCR; Subkey: "CFEditor"; ValueName: "EditFlags"; ValueType: "dword"; ValueData :"0"; Flags: uninsdeletekey
Root: HKCR; Subkey: "CFEditor\DefaultIcon"; ValueType: "string"; ValueData :"{app}\cfeditor.exe,0"; Flags: uninsdeletekey
Root: HKCR; Subkey: "CFEditor\shell"; ValueType: "string"; ValueData :"open"; Flags: uninsdeletekey
Root: HKCR; Subkey: "CFEditor\shell\open\command"; ValueType: "string"; ValueData : "{app}\cfeditor.exe ""%1"""; Flags: uninsdeletekey

[Code]
//procedure InstallRTL();
//var
//  ResultCode: Integer;
//begin
//  Exec(ExpandConstant('{tmp}') + '\vcredist_x86.exe', '/q', ExpandConstant('{tmp}'), SW_SHOW, ewWaitUntilTerminated, ResultCode);
//end;
end.
