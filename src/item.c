#include "item.h"

void gerar_item(ITEM *item, char *nome_item, int bonus_coragem, int bonus_sanidade, PERSONAGEM *personagem) {
    for (int i = 0; i < personagem->qnt_itens; i++) {
        if (strcmp(personagem->item[i].nome, nome_item) == 0) {
            printf("Voce ja tem esse item!\n");
            return;
        }
    }

    if (personagem->qnt_itens < 3) {
        strcpy(item->nome, nome_item);
        item->atk = bonus_coragem;
        item->hp  = bonus_sanidade;

        strcpy(personagem->item[personagem->qnt_itens].nome, item->nome);
        personagem->item[personagem->qnt_itens].atk = item->atk;
        personagem->item[personagem->qnt_itens].hp  = item->hp;
        personagem->qnt_itens++;
    } else {
        printf("Voce nao pode carregar mais itens!\n");
    }
}

void printar_inventario(PERSONAGEM *personagem) {
    int escolha;
    printf("----------------------------SEUS ITENS----------------------------\n");
    for (int i = 0; i < personagem->qnt_itens; i++) {
        printf("\n\t\t%i\n%s\nBonus Coragem: %i\nBonus Sanidade: %i\n",
               i + 1,
               personagem->item[i].nome,
               personagem->item[i].atk,
               personagem->item[i].hp);
        printf("------------------------------------------------------------------\n");
    }

    printf("\nAperte qualquer letra para sair");
    printf("\nSua escolha: ");
    scanf("%i", &escolha);

    if (escolha > 0 && escolha <= personagem->qnt_itens) {
        usar_item(escolha - 1, personagem);
        printf("Voce usou %s.\n", personagem->item[escolha - 1].nome);
    }
    else if (escolha >= 4) {
        return;
    }
    else {
        printf("Escolha invalida!\n");
    }
}


void usar_item(int indice, PERSONAGEM *personagem) {
    if (indice >= 0 && indice < personagem->qnt_itens) {
        ITEM item = personagem->item[indice];

        personagem->coragem  += item.atk;
        personagem->sanidade += item.hp;

        if (personagem->sanidade > 100)
            personagem->sanidade = 100;

        printf("[+%i coragem | +%i sanidade]\n", item.atk, item.hp);

        for (int i = indice; i < personagem->qnt_itens - 1; i++) {
            personagem->item[i] = personagem->item[i + 1];
        }
        personagem->qnt_itens--;
    } else {
        printf("Indice de item invalido!\n");
    }
}