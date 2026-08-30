# 🔪 ROOM 263 — Jogo de Suspense em Texto (CLI)

Um jogo interativo de suspense desenvolvido em linguagem C para terminal, focado em tomadas de decisão, lógica de estados e manipulação de arquivos.

## 📌 Sobre o Projeto

Em **ROOM 263**, o jogador é imerso em uma narrativa de suspense interativa onde cada escolha molda o destino do personagem e o rumo da história. 

O projeto foi construído aplicando conceitos fundamentais da programação em C, incluindo modularização de código, manipulação de arquivos para armazenar a história, organização de estruturas de dados e controle de fluxo por estado no terminal.

## 📁 Estrutura do Repositório

```text
ROOM-263/
├── bin/                 # Executáveis compilados
├── include/             # Arquivos de cabeçalho (.h)
├── src/                 # Códigos-fonte (.c) da lógica do jogo
├── compilar.bat         # Script de compilação rápida para Windows
├── criar_a_historia.c   # Utilitário de geração da narrativa
├── historia.dat         # Arquivo de dados da história
└── jogo_texto.txt       # Arquivo de texto auxiliar

## 🛠️ Tecnologias e Conceitos Utilizados
Linguagem: C

Compilação & Scripts: GCC / Batch Scripting

Conceitos: Arquitetura modular, manipulação de ponteiros, alocação de memória e persistência de dados em arquivos.

## 🚀 Como Executar o Jogo
Pré-requisitos
Compilador C (como GCC / MinGW) instalado.

## Passo a Passo
Clonar o repositório:
```Bash
git clone [https://github.com/camilysa/ROOM-263.git](https://github.com/camilysa/ROOM-263.git)
cd ROOM-263

Compilar e Executar no Windows (via script):
```DOS
compilar.bat

Compilar e Executar Manualmente:
gcc src/*.c -I include -o bin/room263
./bin/room263
