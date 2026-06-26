#include "andamento.h"
#include "combate.h"
#include "struct.h"
#include "item.h"
#include "somefunctions.h"
#include "logo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

void imprimir_menu();
void menu_principal(PERSONAGEM **novo_personagem);
PERSONAGEM *criarPersonagem();
PERSONAGEM *novo_personagem;

int auto_resolve(int posicao) {
    return (posicao == 1  || posicao == 5  || posicao == 7  ||
            posicao == 9  || posicao == 10 || posicao == 11 ||
            posicao == 13 || posicao == 14 ||
            posicao == 16 || posicao == 17 || posicao == 18 ||
            posicao == 19 || posicao == 20 || posicao == 21 ||
            posicao == 22);
}

int main(){
    int rodando = 1;
    menu_principal(&novo_personagem);

    while (rodando) {
        char comando;
        limpar_tela();
        atual(novo_personagem->posicao, novo_personagem);

        if (auto_resolve(novo_personagem->posicao)) {
            pausar();
            fazer_escolha(novo_personagem, ' ');
            continue;
        }

        imprimir_menu();
        scanf(" %c", &comando);

        if (comando >= '1' && comando <= '4')
            comando = 'A' + (comando - '1');

        switch (toupper(comando)) {
            case 'E':
                printar_inventario(novo_personagem);
                pausar();
                break;
            case 'S':
                status_personagem(*novo_personagem);
                pausar();
                break;
            case 'A':
            case 'B':
            case 'C':
            case 'D':
                fazer_escolha(novo_personagem, toupper(comando));
                limpar_tela();
                break;
            case 'P':
                save(novo_personagem);
                pausar();
                break;
            case 'I':
                menu_principal(&novo_personagem);
                break;
            case 'Q':
                rodando = 0;
                break;
            default:
                printf("Use A/B/C/D ou 1/2/3/4 para escolher.\n");
                pausar();
                break;
        }
    }

    free(novo_personagem);
    return 0;
}

//Tela inicial do jogo
void menu_principal(PERSONAGEM **novo_personagem){
    int escolha = 0;
    int rodando = 1;

    while(rodando){
        logo();
        printf("\n\n\t\t\t\t\t\t\t\t\t|1-Novo Jogo");
        printf("\n\t\t\t\t\t\t\t\t\t|2-Continuar");
        printf("\n\t\t\t\t\t\t\t\t\t|3-Ranking");
        printf("\n\t\t\t\t\t\t\t\t\t|4-Desenvolvedor");
        printf("\n\t\t\t\t\t\t\t\t\t|0-Fechar Programa\n\t\t\t\t\t\t\t\t\t");

        scanf("%d", &escolha);

        limpar_tela();
        switch (escolha){
            case 1:
                printf("**  27 de maio de 2003.");
                printf("\n  Hoje e o enterro do seu tio...");
                printf("\n  Voce era o unico parente que ele tinha. Para sua surpresa, ele deixou uma heranca: 6 milhoes de dolares.");
                printf("\n  Mas ha uma condicao: voce precisa ficar 6 dias no apartamento que ele deixou.");
                printf("\n  Parece simples, nao acha?");
                pausar();
                *novo_personagem = criarPersonagem();
                pausar();
                rodando = 0;
                break;
            case 2:
                limpar_tela();
                load(novo_personagem);
                rodando = 0;
                pausar();
                break;
            case 3:
                printf("Noites sobrevividas: %i", (*novo_personagem)->pontos);
                pausar();
                break;
            case 4:
                limpar_tela();
                printf("Camily Silva de Araujo\n");
                pausar();
                break;
            case 0:
                rodando = 0;
                break;
            default:
                break;
        }
    }
}

//Função geradora de personagens e atributos
PERSONAGEM *criarPersonagem(){
    PERSONAGEM *novo_personagem = (PERSONAGEM*) malloc(sizeof(PERSONAGEM));
    char classe = ' ';
    int inteiro = 0;
    while(inteiro != 1 && inteiro != 2 && inteiro != 3){
        printf("\nAntes de entrar no apartamento, como voce se descreve?\n");
        printf("|1-Corajoso  (Coragem alta, Resistencia baixa)\n");
        printf("|2-Cauteloso (Resistencia alta, Percepcao media)\n");
        printf("|3-Curioso   (Percepcao alta, Sanidade fragil)\n");
        printf("Sua escolha:");
        scanf(" %c", &classe);
        limpar_tela();
        inteiro = classe - '0';
        switch (inteiro){
            case 1:
                printf("Voce e do tipo que enfrenta o que vier de frente.");
                novo_personagem->classe      = 1;
                novo_personagem->coragem     = 40;
                novo_personagem->resistencia = 15;
                novo_personagem->percepcao   = 20;
                novo_personagem->sanidade    = 100;
                break;
            case 2:
                printf("Voce prefere observar antes de agir.");
                novo_personagem->classe      = 2;
                novo_personagem->coragem     = 20;
                novo_personagem->resistencia = 40;
                novo_personagem->percepcao   = 25;
                novo_personagem->sanidade    = 100;
                break;
            case 3:
                printf("Voce nao consegue deixar um misterio sem solucao.");
                novo_personagem->classe      = 3;
                novo_personagem->coragem     = 20;
                novo_personagem->resistencia = 15;
                novo_personagem->percepcao   = 40;
                novo_personagem->sanidade    = 80;
                break;
            default:
                printf("Escolha invalida. Tente novamente!");
                continue;
        }
        pausar();
    }
    novo_personagem->posicao   = 1;
    novo_personagem->pontos    = 0;
    novo_personagem->qnt_itens = 0;
    limpar_tela();
    printf("Agora, como voce se chama? ");
    scanf("%s", novo_personagem->nome);
    limpar_tela();
    printf("Personagem criado!");
    printf("\nSeus atributos iniciais sao:\nCoragem:     %i\nResistencia: %i\nPercepcao:   %i\nSanidade:    %i",
           novo_personagem->coragem,
           novo_personagem->resistencia,
           novo_personagem->percepcao,
           novo_personagem->sanidade);
    pausar();
    limpar_tela();
    return novo_personagem;
}

void imprimir_menu(){
    printf("\n[A/B/C/D ou 1/2/3/4] Escolha  [E] Inventario  [S] Status  [P] Salvar  [I] Menu  [Q] Sair\n> ");
}