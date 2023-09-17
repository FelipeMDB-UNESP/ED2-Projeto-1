#include "header.h"

int main() {
    
    FILE* leitura = fopen("insere.bin", "rb+");
    FILE* escrita = fopen("registros.bin", "rb+");

    //chave primária deve ser criada ao se concatenar codClie e codVei
    // REGISTRO r1;
    // strcpy(r1.codClie, "73849561829");
    // strcpy(r1.codVei, "1547LASW");

    // strcpy(r1.chavePri, "73849561829");
    // strcat(r1.chavePri, l1.codVei);

    int numRegistrosInserir = 0;
    int numRegistrosApagar = 0;
    REGISTRO* vetorRegistro; 


    int opcao;
    do {
        // Exibe o menu
        printf("Menu:\n");
        printf("1. Inserção\n");
        printf("2. Remoção\n");
        printf("3. Compactação\n");
        printf("4. Carrega Arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opção (0-4): ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Realizando a inserção:\n");
                //incluir();
                break;
            case 2:
                printf("Realizando a remoção:\n");
                //remover();
                break;
            case 3:
                printf("Compactação:\n");
                //compactacao();
                break;
            case 4:
                printf("Carregando arquivo:\n");
                vetorRegistrosInserir = carregar("insere.bin", &numRegistrosInserir);
                vetorRegistrosApagar = carregar("remove.bin", &numRegistrosApagar);
                printf("Registros a inserir:\n");
                imprimirRegistros(vetorRegistrosInserir, numRegistrosInserir);
                printf("Registros a apagar:\n");
                imprimirRegistros(vetorRegistrosApagar, numRegistrosApagar);
                break;
            case 0:
                printf("Execução encerrada!\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida (0-4).\n");
                break;
        }
    } while (opcao != 0);   



    return 0;
}