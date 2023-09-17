#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Definindo a struct
struct Locacao {
    char codClie[11];
    char codVei[7];
    char chavePri[50];
    char nomeCliente[50];
    char nomeVeiculo[50];
    int qtdDias;
};


void incluir(){

}

void remover(){

}

void compactacao(){

}

void carregar(){

}



int main() {
    
    //chave primária deve ser criada ao se concatenar codClie e codVei
    // struct Locacao l1;
    // strcpy(l1.codClie, "73849561829");
    // strcpy(l1.codVei, "1547LASW");

    // strcpy(l1.chavePri, "73849561829");
    // strcat(l1.chavePri, l1.codVei);


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
                incluir();
                break;
            case 2:
                printf("Realizando a remoção:\n");
                remover();
                break;
            case 3:
                printf("Compactação:\n");
                compactacao();
                break;
            case 4:
                printf("Carregando arquivo:\n");
                carregar();
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