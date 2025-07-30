@echo off
setlocal enabledelayedexpansion

:loop
echo IMPORTANTE: La compilazione non avviene se il progetto si trova in una cartella collegata 
echo a OneDrive/Google Drive/Dropbox e simili.

set /p choice="Vuoi compilare il programma prima di eseguirlo? [S/N]: "

if /i "%choice%"=="S" (
    rem Costruzione della lista dei file sorgente .c
    set sources=
    for /R src %%f in (*.c) do (
        set sources=!sources! "%%f"
    )

    mkdir out

    rem Compilazione
    gcc !sources! -lm -o out\gioco_oca_gruppo_5.exe

    rem Controllo se la compilazione è riuscita
    if %errorlevel% neq 0 (
        echo Errore durante la compilazione.
        pause
    ) else (
        rem Esecuzione del programma compilato
        if exist out\gioco_oca_gruppo_5.exe (
            cd out
            gioco_oca_gruppo_5.exe
            exit
        ) else (
            echo Il file eseguibile non e' presente. Assicurati di averlo compilato correttamente.
            pause
        )
    )

) else if /i "%choice%"=="N" (
    rem Esecuzione del programma senza compilazione
    if exist out\gioco_oca_gruppo_5.exe (
        cd out
        gioco_oca_gruppo_5.exe
        exit
    ) else (
        echo Il file eseguibile non e' presente. Assicurati di averlo compilato correttamente.
        pause
    )

) else (
    echo Scelta non valida, riprova.
)

goto loop
