#ifndef COMBATE_H
#define COMBATE_H
#include "struct.h"
#include "item.h"
#include "somefunctions.h"
#include "andamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int rolagem_dado(int faces);
void combate(PERSONAGEM *personagem, INIMIGO *entidade); // confronto com a entidade
void morte(PERSONAGEM *personagem);                      // colapso mental do jogador
INIMIGO gerar_mob(int tipo);                             // gera entidade pelo tipo (1-5)

#endif // COMBATE_H