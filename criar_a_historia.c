#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TEX_MAXIMO 4000
#define NUMERO_DE_PAGINAS 22

int main() {
    FILE *gravar;
    char texto[TAM_TEX_MAXIMO];
    char linha[TAM_TEX_MAXIMO];

    gravar = fopen("historia.dat", "wb");
    if (gravar == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    for (int i = 1; i <= NUMERO_DE_PAGINAS; i++) {
        printf("\n=== PAGINA %d / %d ===\n", i, NUMERO_DE_PAGINAS);
        printf("Digite o texto da cena (termine com uma linha em branco):\n");

        texto[0] = '\0';

        while (1) {
            fgets(linha, TAM_TEX_MAXIMO, stdin);
            if (strcmp(linha, "\n") == 0) break;
            if (strlen(texto) + strlen(linha) >= TAM_TEX_MAXIMO - 1) {
                printf("Texto muito longo para esta cena!\n");
                fclose(gravar);
                return 1;
            }
            strcat(texto, linha);
        }

        fwrite(texto, sizeof(char), TAM_TEX_MAXIMO, gravar);
    }

    fclose(gravar);
    printf("\nHistoria gravada com sucesso! (%d cenas)\n", NUMERO_DE_PAGINAS);
    return 0;
}