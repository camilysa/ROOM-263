@echo off
rem Script de compilacao e execucao do jogo em C

rem Forca o diretorio de trabalho para a pasta onde este .bat esta salvo
cd /d "%~dp0"

gcc -o ./bin/Game.exe src\main.c src\combate.c src\item.c src\andamento.c src\somefunctions.c -Iinclude -lm

if %errorlevel% neq 0 (
    echo Compilacao falhou. Verifique os erros acima.
    pause
    exit /b %errorlevel%
)

echo Compilacao concluida. Iniciando o jogo...
cd bin
Game.exe
pause