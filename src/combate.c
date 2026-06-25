#include "combate.h"


void upar(PERSONAGEM *personagem) {
    personagem->LEVEL++;
    personagem->coragem     += 3;
    personagem->resistencia += 3;
    personagem->percepcao   += 3;
//sanidade não recupera
}

void subir_level(PERSONAGEM *personagem) {
    if (personagem->LEVEL == 1) {
        if (personagem->pontos >= 5)
            upar(personagem);
    }
    else if (personagem->LEVEL == 2) {
        if (personagem->pontos >= 12)
            upar(personagem);
    }
    else if (personagem->LEVEL == 3) {
        if (personagem->pontos >= 20)
            upar(personagem);
    }
    else if (personagem->LEVEL == 4) {
        if (personagem->pontos >= 30)
            upar(personagem);
    }
}


int rolagem_dado(int faces) {
    return rand() % faces + 1;
}

void combate(PERSONAGEM *personagem, INIMIGO *entidade) {
    int turno = 0;
    printf("A entidade apareceu: %s!\n", entidade->nome);
    pausar();

    while (1) {
        int escolha = 0;
        int dano    = 0;
        int dado1   = rolagem_dado(6);
        int dado2   = rolagem_dado(6);

        if (entidade->HP <= 0) {
            printf("Voce resistiu a %s!\n", entidade->nome);
            printf("Coragem ganha: %i  Pontos: %i\n", entidade->dinheiro, entidade->pontos);
            personagem->coragem  += entidade->dinheiro;
            personagem->pontos   += entidade->pontos;
            personagem->bichos_mortos++;
            subir_level(personagem);
            break;
        }

        if (personagem->sanidade <= 0) {
            printf("Voce nao aguentou... sua mente cedeu.\n");
            personagem->pontos -= 2;
            personagem->sanidade = 10; 
            morte(personagem);
            break;
        }

        limpar_tela();
        printf("\nSua sanidade: %d\nForca da entidade (%s): %d\n",
               personagem->sanidade, entidade->nome, entidade->HP);
        printf("|1-Enfrentar\n");
        printf("|2-Tentar fugir!\n");
        printf("|3-Usar item\n");
        printf("Turno: %d\n", (turno / 2) + 1);
        scanf("%i", &escolha);
        limpar_tela();

        if (escolha == 1) {
            if (personagem->coragem > entidade->SPD) {
                dano = (personagem->coragem - entidade->DEF) / 2;
                if (dano < 1) dano = 1;
                entidade->HP -= dano;
                if (entidade->HP < 0) entidade->HP = 0;
                printf("\nSua sanidade: %d\nForca da entidade: %d\n",
                       personagem->sanidade, entidade->HP);
                printf("\n[Voce resistiu e causou %d de dano psicologico na entidade!]\n", dano);
                sleep(1);
            }
            else if (entidade->SPD > personagem->coragem) {
                dano = (entidade->ATK - personagem->resistencia) / 2;
                if (dano < 1) dano = 1;
                personagem->sanidade -= dano;
                printf("\nSua sanidade: %d\nForca da entidade: %d\n",
                       personagem->sanidade, entidade->HP);
                printf("\n[A entidade te assustou! Voce perdeu %d de sanidade!]\n", dano);
            }
            else if (personagem->coragem == entidade->SPD) {
                personagem->coragem  = rolagem_dado(6) + personagem->coragem;
                entidade->SPD        = rolagem_dado(6) + entidade->SPD;
            }

            if (turno % 2 == 0) {
                int temp            = personagem->coragem;
                personagem->coragem = entidade->SPD;
                entidade->SPD       = temp;
                sleep(1);
            }
            turno += 2;
        }

        if (escolha == 2) {
            dado1 = rolagem_dado(6);
            dado2 = rolagem_dado(6);
            if (dado1 > dado2) {
                printf("\nVoce conseguiu fugir!\n");
                break;
            }
            else if (dado2 > dado1) {
                printf("\nNao conseguiu fugir. A entidade bloqueia o caminho.\n");
                personagem->sanidade -= 5;
                escolha = 1;
                pausar();
                continue;
            }
            else {
                printf("\nQuase! Mas ela ainda esta la...\n");
                escolha = 1;
                pausar();
                continue;
            }
        }

        if (escolha == 3) {
            printar_inventario(personagem);
        }

        limpar_tela();
    }

    pausar();
}

INIMIGO gerar_mob(int tipo) {
    INIMIGO mob;

    switch (tipo) {
        case 1:
            strcpy(mob.nome, "Presenca nas paredes");
            mob.id      = 1;
            mob.HP      = 10;
            mob.ATK     = 5;
            mob.DEF     = 1;
            mob.SPD     = 8;
            mob.dinheiro = 2; 
            mob.pontos  = 1;
            break;

        case 2:
            strcpy(mob.nome, "Sombra da cozinha");
            mob.id      = 2;
            mob.HP      = 20;
            mob.ATK     = 12;
            mob.DEF     = 5;
            mob.SPD     = 12;
            mob.dinheiro = 3;
            mob.pontos  = 2;
            break;

        case 3:
            strcpy(mob.nome, "Figura do corredor");
            mob.id      = 3;
            mob.HP      = 30;
            mob.ATK     = 18;
            mob.DEF     = 8;
            mob.SPD     = 15;
            mob.dinheiro = 4;
            mob.pontos  = 3;
            break;

        case 4:
            strcpy(mob.nome, "A Entidade");
            mob.id      = 4;
            mob.HP      = 50;
            mob.ATK     = 28;
            mob.DEF     = 15;
            mob.SPD     = 20;
            mob.dinheiro = 8;
            mob.pontos  = 5;
            break;

        case 5:
            strcpy(mob.nome, "Elena");
            mob.id      = 5;
            mob.HP      = 80;
            mob.ATK     = 20;
            mob.DEF     = 10;
            mob.SPD     = 10;
            mob.dinheiro = 15;
            mob.pontos  = 10;
            break;

        default:
            printf("Essa entidade nao existe.\n");
            break;
    }
    return mob;
}

void morte(PERSONAGEM *personagem) {
    int escolha;
    printf("Sua mente nao aguentou...\n");
    pausar();
    printf("1-Voltar no ultimo save\n");
    personagem->sanidade = 30; 
    scanf("%i", &escolha);
    if (escolha == 1) {
        load(&personagem);
    }
}