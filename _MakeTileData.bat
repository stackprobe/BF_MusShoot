SET OUTRT=C:\appdata\HakoIIITileData

C:\Factory\Tools\RDMD.exe ^
/RM %OUTRT% ^
/MD %OUTRT%\normal ^
/MD %OUTRT%\normal\map ^
/MD %OUTRT%\normal\enemy ^
/MD %OUTRT%\selected ^
/MD %OUTRT%\enemy

Tools\ToTile.exe Resource\STG01\CHR_BG.BMP %OUTRT%\normal\map\STG01
Tools\ToTile.exe Resource\STG02\CHR_BG.BMP %OUTRT%\normal\map\STG02
Tools\ToTile.exe Resource\STG03\CHR_BG.BMP %OUTRT%\normal\map\STG03
Tools\ToTile.exe Resource\STG04\CHR_BG.BMP %OUTRT%\normal\map\STG04
Tools\ToTile.exe Resource\STG05\CHR_BG.BMP %OUTRT%\normal\map\STG05
Tools\ToTile.exe Resource\STG06\CHR_BG.BMP %OUTRT%\normal\map\STG06
Tools\ToTile.exe Resource\STG07\CHR_BG.BMP %OUTRT%\normal\map\STG07
Tools\ToTile.exe Resource\STG08\CHR_BG.BMP %OUTRT%\normal\map\STG08
Tools\ToTile.exe Resource\STG09\CHR_BG.BMP %OUTRT%\normal\map\STG09

Tools\ToSmall.exe /RES EnemyPos.txt %OUTRT%\normal\enemy %OUTRT%\enemy

COPY empty.bmp %OUTRT%\normal\.

C:\Factory\Tools\xcp.exe %OUTRT%\normal\. %OUTRT%\selected\.

Tools\Hanten.exe /OverWrite /D %OUTRT%\selected\.

PAUSE
