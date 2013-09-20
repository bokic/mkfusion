[Setup]
AppName=CFEditor
AppVerName=CFEditor version {#PACKAGE_VERSION}
AppPublisher=BokiCSoft
AppPublisherURL=http://mkfusion.bokicsoft.com/
AppVersion={#PACKAGE_VERSION}
DefaultDirName={pf}\BokiCSoft\CFEditor
DefaultGroupName=CFEditor
UninstallDisplayIcon={app}\cfeditor.exe
Compression=lzma
;Compression=none
SolidCompression=yes
OutputBaseFilename=CFEditor_{#PACKAGE_VERSION}
OutputDir=.
VersionInfoVersion={#PACKAGE_VERSION}
VersionInfoDescription=CFEditor is free, ColdFusion IDE(Qt 5.1.1)

[Dirs]
Name: "{app}";
Name: "{app}\imageformats";
Name: "{app}\iconengines";

[Files]
; MinGW runtime
Source: "C:\Qt\5.1.1\mingw48_32\bin\libwinpthread-1.dll"; DestDir: "{app}";
Source: "C:\Qt\5.1.1\mingw48_32\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}";
Source: "C:\Qt\5.1.1\mingw48_32\bin\libstdc++-6.dll"; DestDir: "{app}";

; ICU unicode/utf conversion tables
Source: "C:\Qt\5.1.1\mingw48_32\bin\icudt51.dll"; DestDir: "{app}";
Source: "C:\Qt\5.1.1\mingw48_32\bin\icuin51.dll"; DestDir: "{app}";
Source: "C:\Qt\5.1.1\mingw48_32\bin\icuuc51.dll"; DestDir: "{app}";

; Qt library
Source: "C:\Qt\5.1.1\mingw48_32\bin\Qt5Core.dll"; DestDir: "{app}";
Source: "C:\Qt\5.1.1\mingw48_32\bin\Qt5Gui.dll"; DestDir: "{app}";
Source: "C:\Qt\5.1.1\mingw48_32\bin\Qt5Widgets.dll"; DestDir: "{app}";
Source: "C:\Qt\5.1.1\mingw48_32\bin\Qt5Network.dll"; DestDir: "{app}";
Source: "C:\Qt\5.1.1\mingw48_32\bin\Qt5Xml.dll"; DestDir: "{app}";
Source: "C:\Qt\5.1.1\mingw48_32\bin\Qt5WebKit.dll"; DestDir: "{app}";
Source: "C:\Qt\5.1.1\mingw48_32\bin\Qt5WebKitWidgets.dll"; DestDir: "{app}";
Source: "C:\Qt\5.1.1\mingw48_32\bin\Qt5Svg.dll"; DestDir: "{app}";

; Qt image icon engines
Source: "C:\Qt\5.1.1\mingw48_32\plugins\iconengines\qsvgicon.dll"; DestDir: "{app}\iconengines";

; Qt image formats
Source: "C:\Qt\5.1.1\mingw48_32\plugins\imageformats\qgif.dll"; DestDir: "{app}\imageformats";
Source: "C:\Qt\5.1.1\mingw48_32\plugins\imageformats\qico.dll"; DestDir: "{app}\imageformats";
Source: "C:\Qt\5.1.1\mingw48_32\plugins\imageformats\qjpeg.dll"; DestDir: "{app}\imageformats";
Source: "C:\Qt\5.1.1\mingw48_32\plugins\imageformats\qmng.dll"; DestDir: "{app}\imageformats";
Source: "C:\Qt\5.1.1\mingw48_32\plugins\imageformats\qsvg.dll"; DestDir: "{app}\imageformats";
Source: "C:\Qt\5.1.1\mingw48_32\plugins\imageformats\qtiff.dll"; DestDir: "{app}\imageformats";

; openssl libraries
Source: "..\..\libs\libssh\bin\libeay32.dll"; DestDir: "{app}";
Source: "..\..\libs\libssh\bin\ssleay32.dll"; DestDir: "{app}";

; libssh library
Source: "..\..\libs\libssh\bin\libssh.dll"; DestDir: "{app}";

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

