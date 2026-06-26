#include "andamento.h"
#include <stdint.h>

void tela_final(PERSONAGEM *personagem, int tipo_final);
void mostrar_pagina(int pagina);

void mostrar_pagina(int pagina) {
    FILE *fp = fopen("../historia.dat", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir historia.dat\n");
        return;
    }

    int32_t num_secoes;
    if (fread(&num_secoes, sizeof(int32_t), 1, fp) != 1) {
        fclose(fp);
        return;
    }

    if (pagina < 1 || pagina > num_secoes) {
        fclose(fp);
        return;
    }

    int32_t offset, length;
    long idx_pos = sizeof(int32_t) + (long)(pagina - 1) * 2 * sizeof(int32_t);
    fseek(fp, idx_pos, SEEK_SET);
    fread(&offset, sizeof(int32_t), 1, fp);
    fread(&length, sizeof(int32_t), 1, fp);

    long data_start = sizeof(int32_t) + (long)num_secoes * 2 * sizeof(int32_t);
    fseek(fp, data_start + offset, SEEK_SET);

    char *texto = (char *)malloc(length + 1);
    if (texto == NULL) {
        fclose(fp);
        return;
    }

    fread(texto, 1, length, fp);
    texto[length] = '\0';
    printf("%s\n", texto);

    free(texto);
    fclose(fp);
}

int ja_tem(PERSONAGEM *personagem, char *nome_item) {
    for (int i = 0; i < personagem->qnt_itens; i++) {
        if (strcmp(personagem->item[i].nome, nome_item) == 0) {
            printf("Voce ja tem esse item!\n");
            return 0;
        }
    }
    return 1;
}

void save(PERSONAGEM *personagem) {
    FILE *fp = fopen("../saves.dat", "wb");
    if (fp == NULL) {
        printf("Nao foi possivel salvar.\n");
        return;
    }
    if (fwrite(personagem, sizeof(PERSONAGEM), 1, fp) != 1)
        printf("Erro ao gravar!\n");
    else
        printf("Jogo salvo!\n");
    fclose(fp);
}

void load(PERSONAGEM **personagem) {
    FILE *fp = fopen("../saves.dat", "rb");
    if (fp == NULL) {
        printf("Nenhum save encontrado.\n");
        return;
    }
    *personagem = (PERSONAGEM *)malloc(sizeof(PERSONAGEM));
    if (*personagem == NULL) {
        fclose(fp);
        return;
    }
    if (fread(*personagem, sizeof(PERSONAGEM), 1, fp) != 1) {
        free(*personagem);
        *personagem = NULL;
    } else {
        limpar_tela();
        printf("Save carregado!\n");
        status_personagem(**personagem);
    }
    fclose(fp);
}

void atual(int pagina, PERSONAGEM *personagem) {
    switch (pagina) {
        case 1:
            mostrar_pagina(5);
            mostrar_pagina(6);
            mostrar_pagina(7);
            mostrar_pagina(8);
            mostrar_pagina(9);
            break;
        case 2:
            mostrar_pagina(11);
            mostrar_pagina(12);
            mostrar_pagina(13);
            mostrar_pagina(14);
            break;
        case 3:
            mostrar_pagina(20);
            mostrar_pagina(21);
            break;
        case 4:
            mostrar_pagina(26);
            mostrar_pagina(27);
            mostrar_pagina(28);
            break;
        case 5:
            mostrar_pagina(30);
            break;
        case 6:
            mostrar_pagina(34);
            mostrar_pagina(35);
            mostrar_pagina(36);
            break;
        case 7:
            mostrar_pagina(40);
            mostrar_pagina(41);
            mostrar_pagina(42);
            break;
        case 8:
            mostrar_pagina(44);
            mostrar_pagina(45);
            mostrar_pagina(46);
            mostrar_pagina(47);
            mostrar_pagina(48);
            mostrar_pagina(49);
            break;
        case 9:
            mostrar_pagina(68);
            mostrar_pagina(69);
            mostrar_pagina(70);
            break;
        case 10:
            mostrar_pagina(53);
            break;
        case 11:
            mostrar_pagina(55);
            break;
        case 12:
            mostrar_pagina(57);
            mostrar_pagina(58);
            mostrar_pagina(59);
            mostrar_pagina(60);
            mostrar_pagina(61);
            break;
        case 13:
            mostrar_pagina(64);
            break;
        case 14:
            mostrar_pagina(68);
            break;
        case 15:
            mostrar_pagina(76);
            mostrar_pagina(77);
            mostrar_pagina(78);
            mostrar_pagina(79);
            mostrar_pagina(81);
            break;
        case 16:
            mostrar_pagina(83);
            mostrar_pagina(84);
            break;
        case 17:
            mostrar_pagina(87);
            mostrar_pagina(88);
            break;
        case 18:
            mostrar_pagina(87);
            mostrar_pagina(89);
            break;
        case 19:
            mostrar_pagina(91);
            mostrar_pagina(92);
            mostrar_pagina(93);
            break;
        case 20:
            mostrar_pagina(95);
            mostrar_pagina(96);
            mostrar_pagina(97);
            break;
        case 21:
            mostrar_pagina(95);
            mostrar_pagina(96);
            mostrar_pagina(98);
            break;
        case 22:
            mostrar_pagina(100);
            mostrar_pagina(101);
            break;
        default:
            printf("...\n");
            break;
    }
}

void fazer_escolha(PERSONAGEM *personagem, char escolha) {
    switch (personagem->posicao) {

        case 1:
            personagem->posicao = 2;
            pausar();
            break;

        case 2:
            if (escolha == 'A') {
                personagem->sanidade  -= 5;
                personagem->percepcao += 5;
                printf("[-5 sanidade | +5 percepcao]\n");
                mostrar_pagina(16);
                personagem->posicao = 3;
            }
            if (escolha == 'B') {
                personagem->resistencia += 5;
                printf("[+5 resistencia]\n");
                mostrar_pagina(18);
                personagem->posicao = 3;
            }
            pausar();
            break;

        case 3:
            if (escolha == 'A') {
                personagem->coragem     -= 5;
                personagem->resistencia += 10;
                mostrar_pagina(23);
                mostrar_pagina(24);
                personagem->posicao = 6;
            }
            if (escolha == 'B') {
                personagem->coragem += 10;
                printf("[+10 coragem]\n");
                personagem->posicao = 4;
            }
            pausar();
            break;

        case 4:
            if (escolha == 'A') {
                personagem->posicao = 5;
            }
            if (escolha == 'B') {
                mostrar_pagina(32);
                personagem->posicao = 6;
            }
            pausar();
            break;

        case 5:
            personagem->sanidade  -= 10;
            personagem->percepcao += 5;
            printf("[-10 sanidade | +5 percepcao]\n");
            personagem->posicao = 6;
            pausar();
            break;

        case 6:
            if (escolha == 'A') {
                personagem->coragem     -= 5;
                personagem->resistencia += 10;
                mostrar_pagina(38);
                personagem->posicao = 8;
            }
            if (escolha == 'B') {
                personagem->posicao = 7;
            }
            pausar();
            break;

        case 7:
            personagem->sanidade  -= 20;
            personagem->coragem   +=  5;
            personagem->percepcao += 15;
            printf("[-20 sanidade | +5 coragem | +15 percepcao]\n");
            if (ja_tem(personagem, "Canivete")) {
                ITEM canivete;
                gerar_item(&canivete, "Canivete", 5, 0, personagem);
                printf("[Voce encontrou o Canivete!]\n");
            }
            personagem->posicao = 8;
            pausar();
            break;

        case 8:
            if (escolha == 'A') {
                if (ja_tem(personagem, "Canivete")) {
                    ITEM canivete;
                    gerar_item(&canivete, "Canivete", 5, 0, personagem);
                }
                mostrar_pagina(51);
                personagem->posicao = 9;
            }
            if (escolha == 'B') {
                personagem->coragem  += 5;
                personagem->sanidade -= 10;
                mostrar_pagina(53);
                personagem->posicao = 10;
            }
            if (escolha == 'C') {
                personagem->resistencia += 10;
                personagem->coragem     -= 10;
                mostrar_pagina(55);
                personagem->posicao = 11;
            }
            pausar();
            break;

        case 9:
            if (personagem->resistencia >= 30) {
                personagem->sanidade -= 5;
                mostrar_pagina(72);
            } else {
                personagem->sanidade -= 15;
                mostrar_pagina(74);
            }
            personagem->posicao = 12;
            pausar();
            break;

        case 10:
            mostrar_pagina(57);
            personagem->sanidade -= 10;
            personagem->posicao = 12;
            pausar();
            break;

        case 11:
            personagem->posicao = 12;
            pausar();
            break;

        case 12:
            if (escolha == 'A') {
                personagem->percepcao += 15;
                personagem->sanidade  -= 10;
                mostrar_pagina(63);
                personagem->posicao = 13;
            }
            if (escolha == 'B') {
                personagem->percepcao -= 5;
                mostrar_pagina(66);
                personagem->posicao = 14;
            }
            pausar();
            break;

        case 13:
            personagem->posicao = 15;
            pausar();
            break;

        case 14:
            personagem->posicao = 15;
            pausar();
            break;

        case 15:
            if (escolha == 'A') {
                if (personagem->coragem >= 20)
                    personagem->posicao = 16;
                else {
                    personagem->sanidade -= 10;
                    mostrar_pagina(76);
                }
            }
            if (escolha == 'B') {
                if (personagem->coragem >= 30 && ja_tem(personagem, "Canivete") == 0) {
                    int chance = personagem->coragem + personagem->percepcao - personagem->sanidade / 2;
                    personagem->posicao = (chance >= 40) ? 17 : 18;
                } else {
                    mostrar_pagina(76);
                    personagem->sanidade -= 10;
                }
            }
            if (escolha == 'C') {
                if (personagem->percepcao >= 25)
                    personagem->posicao = 19;
                else {
                    mostrar_pagina(76);
                    personagem->sanidade -= 10;
                }
            }
            if (escolha == 'D') {
                int sorte = rand() % 100;
                personagem->posicao = (sorte < 10) ? 20 : 21;
            }
            pausar();
            break;

        case 16:
            mostrar_pagina(85);
            tela_final(personagem, 2);
            break;

        case 17:
            tela_final(personagem, 2);
            break;

        case 18:
            tela_final(personagem, 1);
            break;

        case 19:
            tela_final(personagem, 3);
            break;

        case 20:
            tela_final(personagem, 2);
            break;

        case 21:
            tela_final(personagem, 1);
            break;

        case 22:
            tela_final(personagem, 2);
            break;

        default:
            printf("Essa pagina ainda nao existe.\n");
            break;
    }
}

void tela_final(PERSONAGEM *personagem, int tipo_final) {
    limpar_tela();
    printf("========== FIM DE JOGO ==========\n\n");
    printf("Nome: %s\n", personagem->nome);
    printf("Coragem:     %d\n", personagem->coragem);
    printf("Resistencia: %d\n", personagem->resistencia);
    printf("Percepcao:   %d\n", personagem->percepcao);
    printf("Sanidade:    %d\n\n", personagem->sanidade);

    switch (tipo_final) {
        case 0: mostrar_pagina(105); break;
        case 1: mostrar_pagina(107); break;
        case 2:
            mostrar_pagina(109);
            printf("Parabens, %s.\n", personagem->nome);
            break;
        case 3: mostrar_pagina(93); break;
    }

    printf("\n1 - Jogar novamente\n2 - Sair\n> ");
    int opcao;
    scanf(" %d", &opcao);
    if (opcao == 1)
        load(&personagem);
    else if (opcao == 2)
        exit(0);
    else
        printf("Opcao invalida!\n");
}
