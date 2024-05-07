@echo off
SETLOCAL ENABLEDELAYEDEXPANSION

FOR /L %%G IN (0, 1, 1) DO (
    SET "frameNumber=%%G"
    SET "frameNumber=!frameNumber:~-4!"
    SET "outputFilename=frame_!frameNumber!.png"
    ECHO Rendering frame !frameNumber! to !outputFilename!
    povray +Iorbit.pov +K%%G +O"!outputFilename!" +W800 +H600 +A +FN +KFF240
)

ENDLOCAL
