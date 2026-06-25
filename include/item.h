#ifndef ITEM_H
#define ITEM_H
#include "struct.h"
#include "somefunctions.h"
#include <stdio.h>
#include <string.h>

void gerar_item(ITEM *item, char *nome_item, int bonus_coragem, int bonus_sanidade, PERSONAGEM *personagem);
void printar_inventario(PERSONAGEM *personagem);
void usar_item(int indice, PERSONAGEM *personagem);  // aplica bonus_coragem e bonus_sanidade do item

#endif // ITEM_H