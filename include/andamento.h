#ifndef ANDAMENTO_H
#define ANDAMENTO_H
#include "item.h"
#include "combate.h"
#include "somefunctions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void save(PERSONAGEM *personagem);
void load(PERSONAGEM **personagem);
void atual(int pagina, PERSONAGEM *personagem);          // carrega a noite atual
void fazer_escolha(PERSONAGEM *personagem, char escolha); 
void tela_final(PERSONAGEM *personagem, int tipo_final); // exibe o final 

#endif // ANDAMENTO_H