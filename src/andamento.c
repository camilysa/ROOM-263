#include "andamento.h"
#include <stdint.h>

void tela_final(PERSONAGEM *personagem, int tipo_final);
void mostrar_pagina(int pagina);

// Le e imprime a secao N do historia.dat (indexado por linha em branco)
void mostrar_pagina(int pagina) {
    FILE *fp = fopen("../historia.dat", "rb");
    if (fp == NULL) {
        printf("Nao foi possivel abrir o arquivo historia.dat!\n");
        return;
    }

    int32_t num_secoes;
    if (fread(&num_secoes, sizeof(int32_t), 1, fp) != 1) {
        printf("Arquivo historia.dat corrompido!\n");
        fclose(fp);
        return;
    }

    if (pagina < 1 || pagina > num_secoes) {
        printf("Secao %d nao encontrada (total: %d)!\n", pagina, num_secoes);
        fclose(fp);
        return;
    }

    // Cada entrada no indice: offset (4 bytes) + length (4 bytes)
    int32_t offset, length;
    long idx_pos = sizeof(int32_t) + (long)(pagina - 1) * 2 * sizeof(int32_t);
    if (fseek(fp, idx_pos, SEEK_SET) != 0) {
        printf("Erro ao posicionar no indice!\n");
        fclose(fp);
        return;
    }
    fread(&offset, sizeof(int32_t), 1, fp);
    fread(&length, sizeof(int32_t), 1, fp);

    // Area de dados começa apos o indice completo
    long data_start = sizeof(int32_t) + (long)num_secoes * 2 * sizeof(int32_t);
    if (fseek(fp, data_start + offset, SEEK_SET) != 0) {
        printf("Erro ao posicionar nos dados!\n");
        fclose(fp);
        return;
    }

    char *texto = (char *)malloc(length + 1);
    if (texto == NULL) {
        printf("Memoria insuficiente!\n");
        fclose(fp);
        return;
    }
    if (fread(texto, 1, length, fp) != (size_t)length) {
        printf("Erro ao ler secao %d!\n", pagina);
        free(texto);
        fclose(fp);
        return;
    }
    texto[length] = '\0';
    printf("%s\n", texto);
    free(texto);
    fclose(fp);
}

// ve se o personagem ja tem o item ou nao
int ja_tem(PERSONAGEM *personagem, char *nome_item) {
    for (int i = 0; i < personagem->qnt_itens; i++) {
        if (strcmp(personagem->item[i].nome, nome_item) == 0) {
            printf("Voce ja tem esse item!\n");
            return 0;
        }
    }
    return 1;
}

// salva o jogo
void save(PERSONAGEM *personagem) {
    FILE *fp = fopen("../saves.dat", "wb");
    if (fp == NULL) {
        printf("Nao foi possivel abrir o arquivo para salvar.\n");
        return;
    }
    if (fwrite(personagem, sizeof(PERSONAGEM), 1, fp) != 1)
        printf("Nao foi possivel gravar!\n");
    else
        printf("Jogo gravado com sucesso!\n");
    fclose(fp);
}

// carrega o progresso do jogo
void load(PERSONAGEM **personagem) {
    FILE *fp = fopen("../saves.dat", "rb");
    if (fp == NULL) {
        printf("Nao foi possivel abrir o arquivo de save!\n");
        return;
    }
    *personagem = (PERSONAGEM *)malloc(sizeof(PERSONAGEM));
    if (*personagem == NULL) {
        printf("Nao foi possivel alocar memoria!\n");
        fclose(fp);
        return;
    }
    if (fread(*personagem, sizeof(PERSONAGEM), 1, fp) != 1) {
        printf("Nao leu do arquivo saves.dat\n");
        free(*personagem);
        *personagem = NULL;
    } else {
        limpar_tela();
        printf("Jogo carregado com sucesso!\n");
        status_personagem(**personagem);
    }
    fclose(fp);
}

/*
 * Secoes do historia.dat (separadas por linha em branco no jogo_texto.txt):
 *   1-3   : Introducao (antes da NOITE 1)
 *   5-9   : NOITE 1
 *   11-14 : NOITE 2 (dia + padaria + gravador + escolha)
 *   16,18 : Resultados da escolha do gravador (NOITE 2)
 *   20-21 : NOITE 3 + escolha (barulho cozinha)
 *   23    : OPCAO 1 - Ignorar barulho
 *   24    : Manha apos ignorar (xicara)
 *   26-28 : OPCAO 2 - Ir ate cozinha + escolha do gravador
 *   30    : OPCAO 2.1 - Usar gravador na cozinha
 *   32    : OPCAO 2.2 - Nao usar gravador
 *   34-36 : NOITE 4 (piso + escolha)
 *   38    : OPCAO 1 - Evitar o piso
 *   40-42 : OPCAO 2 - Investigar piso + bilhete + aftermath
 *   44-49 : NOITE 5 (sequencia completa + escolha)
 *   51    : OPCAO 1 - Canivete
 *   53    : OPCAO 2 - Correr ate a sala
 *   55    : OPCAO 3 - Banheiro
 *   57-61 : FASE 2 (gravador + entidade + escolha)
 *   63-64 : OPCAO 1 - Ouvir fita (partes 1 e 2)
 *   66    : OPCAO 2 - Desligar gravador
 *   68-70 : FASE 3 - Cacada + ataque
 *   72    : Se voce acerta
 *   74    : Se voce erra
 *   76-79 : FASE FINAL (setup)
 *   81    : Escolha final (opcoes)
 *   83-85 : OPCAO 1 - Destruir televisao
 *   87-89 : OPCAO 2 - Canivete (sucesso/falha)
 *   91-93 : OPCAO 3 - Gravador (Elena)
 *   95-98 : OPCAO 4 - Fugir (sucesso/falha)
 *   100-101: NOITE 6
 *   103   : FIM DE JOGO
 *   105   : FINAL 0 - Heranca pro Estado
 *   107   : FINAL 1 - Nao foi forte o suficiente
 *   109   : FINAL 2 - Voce venceu
 */

void atual(int pagina, PERSONAGEM *personagem) {
    switch (pagina) {
        case 1:
            // NOITE 1 - chegada e primeira noite (auto-avanca)
            mostrar_pagina(5);
            mostrar_pagina(6);
            mostrar_pagina(7);
            mostrar_pagina(8);
            mostrar_pagina(9);
            break;
        case 2:
            // NOITE 2 - dia, padaria, gravador se move + opcoes visiveis ao final
            mostrar_pagina(11);
            mostrar_pagina(12);
            mostrar_pagina(13);
            mostrar_pagina(14); // contem o texto "A - Deixar na sala / B - Pegar o gravador"
            break;
        case 3:
            // NOITE 3 - barulho na cozinha + escolha
            mostrar_pagina(20);
            mostrar_pagina(21);
            break;
        case 4:
            // Indo ate a cozinha + escolha do gravador
            mostrar_pagina(26);
            mostrar_pagina(27);
            mostrar_pagina(28);
            break;
        case 5:
            // Resultado de usar o gravador na cozinha
            mostrar_pagina(30);
            break;
        case 6:
            // NOITE 4 - piso solto + escolha
            mostrar_pagina(34);
            mostrar_pagina(35);
            mostrar_pagina(36);
            break;
        case 7:
            // Investigacao completa do piso (auto-avanca apos case 6 escolha B)
            mostrar_pagina(40);
            mostrar_pagina(41);
            mostrar_pagina(42);
            break;
        case 8:
            // NOITE 5 - acordar sem ar, entidade aparece
            mostrar_pagina(44);
            mostrar_pagina(45);
            mostrar_pagina(46);
            mostrar_pagina(47);
            mostrar_pagina(48);
            mostrar_pagina(49);
            break;
        case 9:
            // FASE 3 - ataque com canivete (resultado automatico)
            mostrar_pagina(68);
            mostrar_pagina(69);
            mostrar_pagina(70);
            break;
        case 10:
            // Resultado de correr ate a sala
            mostrar_pagina(53);
            break;
        case 11:
            // Resultado de se esconder no banheiro
            mostrar_pagina(55);
            break;
        case 12:
            // FASE 2 - gravador liga, voz do tio, escolha da fita
            mostrar_pagina(57);
            mostrar_pagina(58);
            mostrar_pagina(59);
            mostrar_pagina(60);
            mostrar_pagina(61);
            break;
        case 13:
            // Aftermath de ouvir a fita ate o fim
            mostrar_pagina(64);
            break;
        case 14:
            // Transicao para FASE FINAL apos desligar gravador
            mostrar_pagina(68);
            break;
        case 15:
            // FASE FINAL - entidade se revela, escolha final
            mostrar_pagina(76);
            mostrar_pagina(77);
            mostrar_pagina(78);
            mostrar_pagina(79);
            mostrar_pagina(81);
            break;
        case 16:
            // Destruir a televisao
            mostrar_pagina(83);
            mostrar_pagina(84);
            break;
        case 17:
            // Canivete - sucesso
            mostrar_pagina(87);
            mostrar_pagina(88);
            break;
        case 18:
            // Canivete - falha
            mostrar_pagina(87);
            mostrar_pagina(89);
            break;
        case 19:
            // Gravador - Elena
            mostrar_pagina(91);
            mostrar_pagina(92);
            mostrar_pagina(93);
            break;
        case 20:
            // Fugir - sucesso
            mostrar_pagina(95);
            mostrar_pagina(96);
            mostrar_pagina(97);
            break;
        case 21:
            // Fugir - falha
            mostrar_pagina(95);
            mostrar_pagina(96);
            mostrar_pagina(98);
            break;
        case 22:
            // NOITE 6 - sobreviveu
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
            // NOITE 1 terminou sem incidentes - avanca para NOITE 2
            personagem->posicao = 2;
            pausar();
            break;

        case 2:
            // Escolha do gravador (NOITE 2): A = deixar na sala, B = pegar no quarto
            if (escolha == 'A') {
                personagem->resistencia += 5;
                printf("[+5 resistencia]\n");
                mostrar_pagina(18); // OPCAO 2 - Deixar o gravador na sala
                personagem->posicao = 3;
            }
            if (escolha == 'B') {
                personagem->sanidade  -= 5;
                personagem->percepcao += 5;
                printf("[-5 sanidade | +5 percepcao]\n");
                mostrar_pagina(16); // OPCAO 1 - Pegar o gravador no quarto
                personagem->posicao = 3;
            }
            pausar();
            break;

        case 3:
            if (escolha == 'A') {
                personagem->coragem     -= 5;
                personagem->resistencia += 10;
                // Secao 23: OPCAO 1 - Ignorar o barulho
                mostrar_pagina(23);
                // Secao 24: manha seguinte (xicara no armario)
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
                // Secao 32: OPCAO 2.2 - Nao usar o gravador
                mostrar_pagina(32);
                personagem->posicao = 6;
            }
            pausar();
            break;

        case 5:
            // Auto-avanca: resultado de usar o gravador na cozinha
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
                // Secao 38: OPCAO 1 - Evitar o piso
                mostrar_pagina(38);
                personagem->posicao = 8;
            }
            if (escolha == 'B') {
                personagem->posicao = 7;
            }
            pausar();
            break;

        case 7:
            // Auto-avanca apos investigacao do piso (conteudo ja mostrado em atual)
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
                // Secao 51: OPCAO 1 - Canivete
                mostrar_pagina(51);
                personagem->posicao = 9;
            }
            if (escolha == 'B') {
                personagem->coragem  += 5;
                personagem->sanidade -= 10;
                // Secao 53: OPCAO 2 - Correr ate a sala
                mostrar_pagina(53);
                personagem->posicao = 10;
            }
            if (escolha == 'C') {
                personagem->resistencia += 10;
                personagem->coragem     -= 10;
                // Secao 55: OPCAO 3 - Banheiro
                mostrar_pagina(55);
                personagem->posicao = 11;
            }
            pausar();
            break;

        case 9:
            if (personagem->resistencia >= 30) {
                personagem->sanidade -= 5;
                // Secao 72: Se voce acerta
                mostrar_pagina(72);
            } else {
                personagem->sanidade -= 15;
                // Secao 74: Se voce erra
                mostrar_pagina(74);
            }
            personagem->posicao = 12;
            pausar();
            break;

        case 10:
            // Secao 57: FASE 2 - transicao apos correr
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
                // Secao 63: OPCAO 1 - Ouvir a fita
                mostrar_pagina(63);
                personagem->posicao = 13;
            }
            if (escolha == 'B') {
                personagem->percepcao -= 5;
                // Secao 66: OPCAO 2 - Desligar o gravador
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
                if (personagem->coragem >= 20) {
                    personagem->posicao = 16;
                } else {
                    // Nao tem coragem/percepcao suficiente - FASE 3 cacada
                    personagem->sanidade -= 10;
                    mostrar_pagina(76);
                }
            }
            if (escolha == 'B') {
                if (personagem->coragem >= 30 && ja_tem(personagem, "Canivete") == 0) {
                    int chance = personagem->coragem + personagem->percepcao - personagem->sanidade / 2;
                    if (chance >= 40)
                        personagem->posicao = 17;
                    else
                        personagem->posicao = 18;
                } else {
                    // Sem canivete ou coragem insuficiente
                    mostrar_pagina(76);
                    personagem->sanidade -= 10;
                }
            }
            if (escolha == 'C') {
                if (personagem->percepcao >= 25) {
                    personagem->posicao = 19;
                } else {
                    // Percepcao insuficiente
                    mostrar_pagina(76);
                    personagem->sanidade -= 10;
                }
            }
            if (escolha == 'D') {
                int sorte = rand() % 100;
                if (sorte < 10)
                    personagem->posicao = 20;
                else
                    personagem->posicao = 21;
            }
            pausar();
            break;

        case 16:
            // Auto: destruiu a TV, vitoria
            mostrar_pagina(85);
            tela_final(personagem, 2);
            break;

        case 17:
            // Auto: canivete acertou, vitoria
            tela_final(personagem, 2);
            break;

        case 18:
            // Auto: canivete falhou, derrota
            tela_final(personagem, 1);
            break;

        case 19:
            // Auto: usou gravador (Elena), vitoria verdadeira
            tela_final(personagem, 3);
            break;

        case 20:
            // Auto: fugiu com sucesso, vitoria
            tela_final(personagem, 2);
            break;

        case 21:
            // Auto: tentou fugir e falhou, derrota
            tela_final(personagem, 1);
            break;

        case 22:
            // Auto: sobreviveu as 6 noites, vitoria
            tela_final(personagem, 2);
            break;

        default:
            printf("Essa pagina ainda nao existe.\n");
            break;
    }
}

// tela final do jogo
void tela_final(PERSONAGEM *personagem, int tipo_final) {
    limpar_tela();
    printf("========== FIM DE JOGO ==========\n\n");
    printf("Nome: %s\n", personagem->nome);
    printf("Coragem:     %d\n", personagem->coragem);
    printf("Resistencia: %d\n", personagem->resistencia);
    printf("Percepcao:   %d\n", personagem->percepcao);
    printf("Sanidade:    %d\n\n", personagem->sanidade);

    switch (tipo_final) {
        case 0:
            // Secao 105: FINAL 0 - Heranca pro Estado
            mostrar_pagina(105);
            break;
        case 1:
            // Secao 107: FINAL 1 - Nao foi forte o suficiente
            mostrar_pagina(107);
            break;
        case 2:
            // Secao 109: FINAL 2 - Voce venceu
            mostrar_pagina(109);
            printf("Parabens, %s.\n", personagem->nome);
            break;
        case 3:
            // Secao 93: FINAL 3 - Final verdadeiro (Elena)
            mostrar_pagina(93);
            break;
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
