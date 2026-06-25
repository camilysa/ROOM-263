#ifndef STRUCT_H
#define STRUCT_H

typedef struct ITEM {           // struct do item
    char nome[20];
    int atk;                    // bônus de coragem ao usar
    int hp;                     // bônus de sanidade ao usar
} ITEM;

typedef struct _personagem {    // struct do personagem
    char nome[50];
    int LEVEL;                 
    int coragem;               
    int resistencia;           
    int percepcao;              
    int sanidade;               
    int pontos;
    ITEM item[10];
    int qnt_itens;
    int posicao;
    int final;                  // flag de rota (0 = normal, 1 = loop/bad end)
    int bichos_mortos;          // confrontos com a entidade vencidos
    int classe;                 // 1-Corajoso  2-Cauteloso  3-Curioso
} PERSONAGEM;

typedef struct _inimigo {       // struct da entidade
    int id;
    char nome[50];
    int HP;                     // força psicológica da entidade
    int ATK;                    // dano de sanidade por turno
    int DEF;                    // resistência da entidade ao dano do jogador
    int SPD;                    // velocidade (comparada com coragem do jogador)
    int posicao;
    int dinheiro;               // coragem concedida ao vencer
    int pontos;
} INIMIGO;

#endif // STRUCT_H