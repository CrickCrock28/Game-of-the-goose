@echo off

:loop

set /p choice="Vuoi compilare il programma prima di eseguirlo? [S/N]: "

if /i "%choice%"=="S" (
    rem compilazione
    gcc progetto_eclipse/src/*.c progetto_eclipse/src/*.h progetto_eclipse/src/*/*.c progetto_eclipse/src/*/*.h progetto_eclipse/src/*/*/*.c progetto_eclipse/src/*/*/*.h -lm -o progetto_eclipse\\Debug\\gioco_oca_gruppo_5.exe

    rem Controllo se la compilazione è riuscita
    if %errorlevel% neq 0 (
        echo Errore durante la compilazione.
    ) else (
        rem Esecuzione del programma compilato
        if exist progetto_eclipse\\Debug\\gioco_oca_gruppo_5.exe (
            cd progetto_eclipse\\Debug
	    gioco_oca_gruppo_5.exe
            exit
        ) else (
            echo Il file eseguibile non e' presente. Assicurati di averlo compilato correttamente.
        )
    )   

) else if /i "%choice%"=="N" (
    rem Esecuzione del programma senza compilazione
    if exist progetto_eclipse\\Debug\\gioco_oca_gruppo_5.exe (
        cd progetto_eclipse\\Debug
	gioco_oca_gruppo_5.exe
        exit
    ) else (
        echo Il file eseguibile non e' presente. Assicurati di averlo compilato correttamente.
    )    

) else (
    echo Scelta non valida, riprova.
)

goto loop
