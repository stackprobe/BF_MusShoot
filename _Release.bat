C:\Factory\Tools\RDMD.exe /RC out

SET RAWKEY=2e6b2873bda3ed7fcb72cae4252377efffd7ff91493f7ef52a19168072d50858

C:\Factory\SubTools\resCluster.exe /L Music.txt       /D C:\tmp /K %RAWKEY% /C out\Music.rclu
C:\Factory\SubTools\resCluster.exe /L Picture.txt     /D C:\tmp /K %RAWKEY% /C out\Picture.rclu
C:\Factory\SubTools\resCluster.exe /L SoundEffect.txt /D C:\tmp /K %RAWKEY% /C out\SoundEffect.rclu

COPY /B Hako3\Release\Hako3.exe out

COPY EditorData\* out

PAUSE
