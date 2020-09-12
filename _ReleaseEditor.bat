C:\Factory\Tools\RDMD.exe ^
/RC bin ^
/MD bin\Editor\Editor\bin\Release

COPY /B *.* bin
COPY /B Editor\Editor\bin\Release\Editor.exe bin\Editor\Editor\bin\Release
C:\Factory\Tools\xcp.exe /C BootMenu bin\BootMenu
C:\Factory\Tools\xcp.exe /C EditorData bin\EditorData
C:\Factory\Tools\xcp.exe /C out bin\out
C:\Factory\Tools\xcp.exe /C Resource bin\Resource
C:\Factory\Tools\xcp.exe /C Tools bin\Tools

PAUSE
