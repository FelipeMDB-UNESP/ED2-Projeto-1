#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


// Definindo a struct

typedef struct registro {
    char codClie[12];
    char codVei[8];
    char nomeCliente[50];
    char nomeVeiculo[50];
    int qtdDias;
} REGISTRO;

int incluir(){
    // Struct para armazenar o input
    typedef struct buffer {
        char codClie[12];
        char codVei[8];
        char nomeCliente[50];
        char nomeVeiculo[50];
        char qtdDias[4];
    } BUFFER;
    FILE *in, *out;
    int i = 0, i_registro;
    
    //Abertura dos arquivos
    if((in = fopen("insere.bin","rb")) == NULL){
        printf("Erro durante a abertura do arquivo!\n");
        return 0;
    }
    
    else{
        
        printf("Qual registro gostaria de inserir? (Digite algum número correspondente)\n");
        scanf("%d", &i_registro);
        printf("\n%d\n", i_registro);
        BUFFER buffer_in;

        fread(&buffer_in, sizeof(struct buffer), 1, in);

        //test se escreveu no output
        bool test = false;
        printf("\n%d\n", test); 

        if((out = fopen("output.bin","wb")) == NULL){
            printf("Erro durante a criação do arquivo!\n");
            return 0;
        }

        
    //Inserir no arquivo de Saída
        
        // Definir tamanho do registro

        //struct que seria o input
        typedef struct registro_final {
        int tamanho;
        char codClie[strlen(buffer_in.codClie) + 1];
        char codVei[strlen(buffer_in.codVei)+ 1];
        char nomeCliente[strlen(buffer_in.nomeCliente)+1];
        char nomeVeiculo[strlen(buffer_in.nomeVeiculo)+1];
        int qtdDias;
        } FINAL;

        //calcula tamanho do registro
        int tamanho_registro = 0;
        tamanho_registro = strlen(buffer_in.codClie) +
        strlen(buffer_in.codVei) + strlen(buffer_in.nomeCliente) +
        strlen(buffer_in.nomeVeiculo) + strlen(buffer_in.qtdDias);
        printf("tamanho do Registro: %d\n", tamanho_registro);
        
        // copia buffer pro registro final
        struct registro_final registro_out;
        registro_out.tamanho = tamanho_registro;
        strcpy(registro_out.codClie, buffer_in.codClie);
        strcpy(registro_out.codVei, buffer_in.codVei);
        strcpy(registro_out.nomeCliente, buffer_in.nomeCliente);
        strcpy(registro_out.nomeVeiculo, buffer_in.nomeVeiculo);
        registro_out.qtdDias = atoi(buffer_in.qtdDias);
        
        test = fwrite(&registro_out, sizeof(struct registro_final), 1, out);
        printf("%d", test);
        fclose(out);
    }
}

void remover(){

}

void compactacao(){

}

void carregar(){

}



int main() {
    
    //chave primária deve ser criada ao se concatenar codClie e codVei
    // struct in l1;
    // strcpy(l1.codClie, "73849561829");
    // strcpy(l1.codVei, "1547LASW");

    // strcpy(l1.chavePri, "73849561829");
    // strcat(l1.chavePri, l1.codVei);


    int opcao;
    do {
        // Exibe o menu
        printf("\nMenu:\n");
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