#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Definindo a struct
struct Registro {
    char codClie[12];
    char codVei[8];
    char nomeCliente[50];
    char nomeVeiculo[50];
    int qtdDias;
};

void incluir(struct Registro registro) {

    FILE* registros = fopen("insere.bin", "rb+");

    fwrite(&registros, sizeof(struct Registro), 1, registros);
    fclose(registros);
    
}

void remover(){

}

void compactacao(){

}


struct Registro* carregar(int* numRegistros) {
    FILE* arquivo = fopen("insere.bin", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    //tam arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    rewind(arquivo);

    // calcular numRegistros
    *numRegistros = tamanhoArquivo / sizeof(struct Registro);

    // Aloca de memória
    struct Registro* vetorRegistros = (struct Registro*)malloc(*numRegistros * sizeof(struct Registro));

    //Lê registros
    fread(vetorRegistros, sizeof(struct Registro), *numRegistros, arquivo);

    // Fecha o arquivo
    fclose(arquivo);

    return vetorRegistros;
}


void imprimirRegistros(struct Registro* vetorRegistros, int numRegistros) {
    for (int i = 0; i < numRegistros; i++) {
        printf("Registro %d:\n", i + 1);
        printf("Código do Cliente: %s\n", vetorRegistros[i].codClie);
        printf("Código do Veículo: %s\n", vetorRegistros[i].codVei);
        printf("Nome do Cliente: %s\n", vetorRegistros[i].nomeCliente);
        printf("Nome do Veículo: %s\n", vetorRegistros[i].nomeVeiculo);
        printf("Quantidade de Dias: %d\n", vetorRegistros[i].qtdDias);
        printf("\n");
    }
}



int main() {
    
    FILE* leitura = fopen("insere.bin", "rb+");
    FILE* escrita = fopen("registros.bin", "rb+");

    //chave primária deve ser criada ao se concatenar codClie e codVei
    // struct Registro r1;
    // strcpy(r1.codClie, "73849561829");
    // strcpy(r1.codVei, "1547LASW");

    // strcpy(r1.chavePri, "73849561829");
    // strcat(r1.chavePri, l1.codVei);

    int numRegistros = 0;
    struct Registro* vetorRegistro = carregar(&numRegistros);
    imprimirRegistros(vetorRegistro, numRegistros);


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
                //carregar();
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