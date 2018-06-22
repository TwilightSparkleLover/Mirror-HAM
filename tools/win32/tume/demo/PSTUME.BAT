@echo off
dlcpe -Q ?
if errorlevel 2 goto SNES
if errorlevel 1 goto GENESIS
echo No response from Psy-Q
goto END
:SNES
    echo Initializing SNES
    dlcpe -Q -R psyqssfx.cpe
    if errorlevel 1 goto ERROR
    tUME
    goto END
:GENESIS
    echo Initializing Genesis
    dlcpe -Q -R psyqs68k.cpe
    if errorlevel 1 goto ERROR
    tUME
    goto END
:ERROR
    echo Unable to download tUME Map Scroller
:END
