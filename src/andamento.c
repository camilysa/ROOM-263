#include "andamento.h"

#define TAM_TEX_MAXIMO 4000

void tela_final(PERSONAGEM *personagem, int tipo_final);

//vê se o personagem já tem o item ou não
int ja_tem(PERSONAGEM *personagem, char *nome_item) {
    for (int i = 0; i < personagem->qnt_itens; i++) {
        if (strcmp(personagem->item[i].nome, nome_item) == 0) {
            printf("Voce ja tem esse item!\n");
            return 0;
        }
    }
    return 1;
}

//salva o jogo
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

//carrega o progresso do jogo
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

void atual(int pagina, PERSONAGEM *personagem) {
    switch (pagina) {
        case 1:
            printf("27 de maio de 2003.\n");
            printf("Voce entra no apartamento 263.\n");
            printf("Nao era o que voce esperaria de um milionario.\n");
            printf("Cheira a madeira velha... e algo mais.\n");
            printf("Algo que voce nao consegue identificar.\n");
            printf("\nO que voce faz?\n");
            printf("|A - Explorar o apartamento\n");
            printf("|B - Ir logo dormir\n");
            break;
        case 2:
            printf("29 de maio de 2003.\n");
            printf("Segunda noite. Nada de anormal.\n");
            printf("Talvez esse lugar nao seja tao estranho assim...\n");
            printf("\n|A - Avancar para a proxima noite\n");
            break;
        case 3:
            printf("30 de maio de 2003 - 3:26\n");
            printf("Tem um barulho vindo da cozinha.\n");
            printf("E impossivel dormir assim.\n");
            printf("\nO que voce vai fazer?\n");
            printf("|A - Ignorar o barulho e tentar voltar a dormir [-5 coragem | +10 resistencia]\n");
            printf("|B - Ir ate a cozinha investigar [+10 coragem]\n");
            break;
        case 4:
            printf("Voce chega na cozinha.\n");
            printf("Nao encontra nada...\n");
            printf("Tem certeza que ouviu alguma coisa?\n");
            printf("...\n");
            printf("\nDeseja usar o gravador antes de sair?\n");
            printf("|A - Sim [+5 percepcao | -10 sanidade]\n");
            printf("|B - Nao\n");
            break;
        case 5:
            printf("REBOBINANDO... <<\n");
            printf("...\n");
            printf("Uma voz surge da fita:\n");
            printf("\"Ela sabe que voce esta aqui\"\n");
            printf("\n|A - Voltar para o quarto\n");
            break;
        case 6:
            printf("31 de maio de 2003.\n");
            printf("Voce tropeca no piso. NO PISO?\n");
            printf("Uma das ripas de madeira nao esta bem encaixada.\n");
            printf("Parece um esconderijo...\n");
            printf("\nO que voce faz?\n");
            printf("|A - Ignorar [-5 coragem | +10 resistencia]\n");
            printf("|B - Examinar o piso [-20 sanidade | +5 coragem]\n");
            break;
        case 7:
            printf("Voce remove o piso falso e encontra uma caixa preta.\n");
            printf("Dentro: uma folha.\n\n");
            printf("\"Eu nao vou conseguir fugir daqui,\n");
            printf(" Ela nunca vai deixar eu sair...\n");
            printf(" So voce pode quebrar esse ciclo.\n");
            printf(" Fuja desse lugar.\"\n");
            printf("\n|A - Guardar o bilhete e continuar\n");
            break;
        case 8:
            printf("1 de junho de 2003 - 3:33\n");
            printf("Voce acorda sem ar.\n");
            printf("As paredes parecem longas demais.\n");
            printf("E entao voce ve ela.\n");
            printf("Parada no fim do corredor.\n");
            printf("Alta. Magra. Imóvel.\n");
            printf("O sorriso grande demais para um ser humano.\n");
            printf("\nO que voce faz?\n");
            printf("|A - Pegar o canivete no criado-mudo\n");
            printf("|B - Correr ate a sala [+5 coragem | -10 sanidade]\n");
            printf("|C - Se esconder no banheiro [+10 resistencia | -10 coragem]\n");
            break;
        case 9:
            printf("A televisao explode.\n");
            printf("Os cacos voam na sua direcao.\n");
            break;
        case 10:
            printf("Voce atravessa o corredor.\n");
            printf("As luzes piscam violentamente.\n");
            printf("Cada vez que escurece ela aparece mais perto.\n");
            printf("\"Voce deveria ter ficado no quarto.\"\n");
            break;
        case 11:
            printf("Voce bate a porta do banheiro.\n");
            printf("Silencio.\n");
            printf("...\n");
            printf("TOC. TOC. TOC.\n");
            printf("\"Voce realmente acha que portas funcionam aqui?\"\n");
            printf("A macaneta comeca a girar sozinha.\n");
            break;
        case 12:
            printf("As luzes acabam completamente.\n");
            printf("O gravador no chao comeca a funcionar sozinho.\n");
            printf("CLICK. REBOBINANDO... <<\n");
            printf("A voz do seu tio surge na fita:\n");
            printf("\"Nao escuta ela.\"\n");
            printf("\"Ela quer trocar de lugar com voce.\"\n");
            printf("\nO que voce faz?\n");
            printf("|A - Ouvir a fita ate o final [+15 percepcao | -10 sanidade]\n");
            printf("|B - Desligar o gravador [-5 percepcao]\n");
            break;
        case 13:
            printf("\"Ela nao suporta silencio...\"\n");
            printf("A narradora grita: PARA.\n");
            printf("As lampadas do apartamento explodem ao mesmo tempo.\n");
            break;
        case 14:
            printf("Silencio.\n");
            printf("...\n");
            printf("\"Obrigada.\"\n");
            printf("A voz soa gentil demais.\n");
            printf("\"Eu sabia que voce me entenderia.\"\n");
            break;
        case 15:
            printf("Ela comeca a aparecer fisicamente.\n");
            printf("Nao caminhando. Se arrastando pelas paredes.\n");
            printf("Eu preciso sobreviver.\n");
            printf("\nO que voce faz?\n");
            printf("|A - Destruir a televisao da sala\n");
            printf("|B - Enfrentar ela com o canivete\n");
            printf("|C - Usar o gravador\n");
            printf("|D - Fugir do apartamento\n");
            break;
        case 16:
            printf("Voce pega a televisao.\n");
            printf("As imagens na tela mudam rapidamente.\n");
            printf("\"SE VOCE QUEBRAR ISSO...\"\n");
            printf("Voce fecha os olhos e joga a televisao no chao.\n");
            printf("CRASH.\n");
            printf("Silencio total.\n");
            printf("Ela olha para voce pela primeira vez sem raiva.\n");
            printf("\"Eu nao queria ficar sozinha de novo...\"\n");
            printf("Ela desaparece.\n");
            printf("\n|A - Continuar\n");
            break;
        case 17:
            printf("A lamina atravessa o peito dela.\n");
            printf("Nao sai sangue. So estatica.\n");
            printf("\"Voce nao faz ideia do que acabou de libertar...\"\n");
            printf("Ela sorri de verdade pela primeira vez.\n");
            printf("\"Obrigada.\"\n");
            printf("\n|A - Continuar\n");
            break;
        case 18:
            printf("Voce hesitou. So por um segundo.\n");
            printf("Mas foi suficiente.\n");
            printf("Ela segura o canivete antes do golpe.\n");
            printf("\"Voce sera um otimo substituto.\"\n");
            printf("...\n");
            printf("27 de maio de 2009.\n");
            printf("Hoje e o enterro do seu tio...\n");
            printf("\n|A - Continuar\n");
            break;
        case 19:
            printf("Voce aperta PLAY.\n");
            printf("Uma voz humana. Assustada. Chorando.\n");
            printf("\"Se alguem encontrar isso... nao deixa ela pegar voce.\"\n");
            printf("A entidade recua.\n");
            printf("...\n");
            printf("\"Meu nome e Elena.\"\n");
            printf("Ela lembra.\n");
            printf("E ao lembrar, desaparece.\n");
            printf("O apartamento fica em silencio. De verdade.\n");
            printf("\n|A - Continuar\n");
            break;
        case 20:
            printf("A macaneta gira.\n");
            printf("Voce cai no corredor do predio.\n");
            printf("A porta bate sozinha atras de voce.\n");
            printf("Voce desce as escadas sem olhar para tras.\n");
            printf("Nunca mais volta.\n");
            printf("Mas as vezes, quando tenta dormir...\n");
            printf("\"Voce quase ficou comigo.\"\n");
            printf("\n|A - Continuar\n");
            break;
        case 21:
            printf("A porta abre.\n");
            printf("Mas nao existe corredor do outro lado.\n");
            printf("So o quarto.\n");
            printf("Voce nunca saiu do apartamento.\n");
            printf("\"Eu avisei.\"\n");
            printf("...\n");
            printf("27 de maio de 2009.\n");
            printf("\n|A - Continuar\n");
            break;
        case 22:
            printf("2 de junho de 2003 - 6:00\n");
            printf("Nao acredito que sobrevivi a sexta noite.\n");
            printf("Eu venci.\n");
            printf("Finalmente posso voltar para casa.\n");
            printf("\n|A - Continuar\n");
            break;
        default:
            printf("...\n");
            break;
    }
}

void fazer_escolha(PERSONAGEM *personagem, char escolha) {
    switch (personagem->posicao) {

        case 1:
            if (escolha == 'A') {
                personagem->resistencia += 5;
                printf("[+5 resistencia]\n");
                personagem->posicao = 2;
            }
            if (escolha == 'B') {
                personagem->posicao = 2;
            }
            pausar();
            break;

        case 2:
            if (escolha == 'A') {
                personagem->posicao = 3;
            }
            pausar();
            break;

        case 3:
            if (escolha == 'A') {
                personagem->coragem     -= 5;
                personagem->resistencia += 10;
                printf("Voce coloca o travesseiro na cabeca e tenta ignorar o barulho...\n");
                printf("Depois de alguns minutos voce consegue voltar a dormir.\n");
                printf("Bons sonhos...\n");
                printf("[-5 coragem | +10 resistencia]\n");
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
                printf("Voce decide nao usar o gravador e volta para o quarto.\n");
                printf("Esse apartamento fica mais estranho a cada dia...\n");
                personagem->posicao = 6;
            }
            pausar();
            break;

        case 5:
            if (escolha == 'A') {
                personagem->sanidade  -= 10;
                personagem->percepcao += 5;
                printf("[+5 percepcao | -10 sanidade]\n");
                personagem->posicao = 6;
            }
            pausar();
            break;

        case 6:
            if (escolha == 'A') {
                personagem->coragem     -= 5;
                personagem->resistencia += 10;
                printf("Voce decide ignorar o piso...\n");
                printf("[-5 coragem | +10 resistencia]\n");
                personagem->posicao = 8;
            }
            if (escolha == 'B') {
                personagem->posicao = 7;
            }
            pausar();
            break;

        case 7:
            if (escolha == 'A') {
                personagem->sanidade  -= 20;
                personagem->coragem   +=  5;
                personagem->percepcao += 15;
                printf("[-20 sanidade | +5 coragem | +15 percepcao]\n");
                if (ja_tem(personagem, "Canivete")) {
                    ITEM canivete;
                    gerar_item(&canivete, "Canivete", 5, 0, personagem);
                    printf("Dentro da caixa havia tambem um canivete.\n");
                }
                personagem->posicao = 8;
            }
            pausar();
            break;

        case 8:
            if (escolha == 'A') {
                if (ja_tem(personagem, "Canivete")) {
                    ITEM canivete;
                    gerar_item(&canivete, "Canivete", 5, 0, personagem);
                }
                printf("Suas maos tremem enquanto segura o canivete.\n");
                printf("\"Ah... Entao voce quer brincar disso?\"\n");
                personagem->posicao = 9;
            }
            if (escolha == 'B') {
                personagem->coragem  += 5;
                personagem->sanidade -= 10;
                printf("[-10 sanidade | +5 coragem]\n");
                personagem->posicao = 10;
            }
            if (escolha == 'C') {
                personagem->resistencia += 10;
                personagem->coragem     -= 10;
                printf("[+10 resistencia | -10 coragem]\n");
                personagem->posicao = 11;
            }
            pausar();
            break;

        case 9:
            if (personagem->resistencia >= 30) {
                personagem->sanidade -= 5;
                printf("Voce protege o rosto a tempo dos estilhacoes.\n");
                printf("[-5 sanidade]\n");
            } else {
                personagem->sanidade -= 15;
                printf("Os cacos de vidro atingem voce.\n");
                printf("[-15 sanidade]\n");
            }
            personagem->posicao = 12;
            pausar();
            break;

        case 10:
            printf("Ela surge atras de voce.\n");
            personagem->sanidade -= 10;
            printf("[-10 sanidade]\n");
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
                printf("[+15 percepcao | -10 sanidade]\n");
                personagem->posicao = 13;
            }
            if (escolha == 'B') {
                personagem->percepcao -= 5;
                printf("[-5 percepcao]\n");
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
                    personagem->sanidade -= 10;
                    printf("Suas maos tremem demais. Voce nao consegue agir.\n");
                    printf("[-10 sanidade]\n");
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
                    printf("Voce nao tem coragem suficiente ou nao tem o canivete.\n");
                    personagem->sanidade -= 10;
                }
            }
            if (escolha == 'C') {
                if (personagem->percepcao >= 25) {
                    personagem->posicao = 19;
                } else {
                    printf("Sua percepcao nao e suficiente para encontrar o gravador a tempo.\n");
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
            if (escolha == 'A') {
                tela_final(personagem, 2);
            }
            pausar();
            break;

        case 17:
            if (escolha == 'A') {
                tela_final(personagem, 2);
            }
            pausar();
            break;

        case 18:
            tela_final(personagem, 1);
            pausar();
            break;

        case 19:
            if (escolha == 'A') {
                tela_final(personagem, 3);
            }
            pausar();
            break;

        case 20:
            if (escolha == 'A') {
                tela_final(personagem, 2);
            }
            pausar();
            break;

        case 21:
            tela_final(personagem, 1);
            pausar();
            break;

        case 22:
            if (escolha == 'A') {
                tela_final(personagem, 2);
            }
            pausar();
            break;

        default:
            printf("Essa pagina ainda nao existe.\n");
            break;
    }
}

//tela final do jogo
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
            printf("Como chegou a esse ponto?\n");
            printf("Voce enlouqueceu...\n");
            printf("Depois da denuncia de alguns vizinhos,\n");
            printf("a policia te encontrou sentado no canto do quarto,\n");
            printf("rabiscando as paredes e falando sozinho...\n");
            printf("A heranca foi para o Estado e voce para o manicomio.\n");
            break;
        case 1:
            printf("Voce hesitou. So por um segundo.\n");
            printf("Mas foi suficiente.\n");
            printf("\"Voce sera um otimo substituto.\"\n");
            printf("...\n");
            printf("27 de maio de 2009.\n");
            printf("Hoje e o enterro do seu tio...\n");
            printf("(A narracao continua. Mas agora a voz e a sua.)\n");
            break;
        case 2:
            printf("Uau, parece que voce completou os 6 dias.\n");
            printf("Os 6 milhoes de dolares cairam na sua conta no dia seguinte.\n");
            printf("O que aconteceu naquele apartamento ficara com voce para sempre.\n");
            printf("Talvez voce precise de terapia...\n");
            printf("Mas o que isso importa agora? Voce venceu!\n");
            printf("Parabens, %s.\n", personagem->nome);
            break;
        case 3:
            printf("Final Verdadeiro.\n\n");
            printf("\"Meu nome e Elena.\"\n");
            printf("Ela lembrou. E ao lembrar, desapareceu.\n");
            printf("O apartamento ficou em silencio — de verdade.\n");
            printf("Voce liberou ela.\n");
            printf("E junto com ela, liberou seu tio tambem.\n");
            printf("Os 6 milhoes de dolares cairam na sua conta.\n");
            printf("Mas dessa vez... parece que voce merece de verdade.\n");
            break;
    }

    printf("\n\n|1 - Voltar no ultimo save\n|2 - Fechar o jogo\n");
    int opcao;
    scanf(" %d", &opcao);
    if (opcao == 1)
        load(&personagem);
    else if (opcao == 2)
        exit(0);
    else
        printf("Opcao invalida!\n");
}