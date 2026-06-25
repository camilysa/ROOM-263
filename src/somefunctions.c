#include "somefunctions.h"

void status_personagem(PERSONAGEM personagem) {
    printf("Nome:        %s\n",  personagem.nome);
    printf("Noite:       %i/6\n", personagem.LEVEL);
    printf("Sanidade:    %i/100\n", personagem.sanidade);
    printf("Coragem:     %i\n",  personagem.coragem);
    printf("Resistencia: %i\n",  personagem.resistencia);
    printf("Percepcao:   %i\n",  personagem.percepcao);
    printf("Pontos:      %i\n",  personagem.pontos);
    printf("Posicao:     %i\n",  personagem.posicao);
}

void pausar() {
    fflush(stdin);
    getchar();
}

void limpar_tela() {
    system("cls");
}