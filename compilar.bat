@echo off
rem Script de compilação e execução do jogo em C

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