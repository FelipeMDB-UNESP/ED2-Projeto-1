#include "header.h"

// Definindo a struct
typedef struct registro {
    char codClie[12];
    char codVei[8];
    char nomeCliente[50];
    char nomeVeiculo[50];
    int qtdDias;
} REGISTRO;

FILE* abrir_arquivo_binario(char* nome_do_arquivo) {

    FILE* arq;
    bool inexistencia;
    char recado[64];

    arq = fopen(nome_do_arquivo, "rb");
    inexistencia = (arq == NULL);
    fclose(arq);


    if (inexistencia) {
        strcpy(recado, "Arquivo Binário \"");
        strcat(recado, nome_do_arquivo);
        strcat(recado, "\" Inexistente.");
        atualiza_log(recado);
        return NULL;
    }


    strcpy(recado, "Arquivo Binário \"");
    strcat(recado, nome_do_arquivo);
    strcat(recado, "\" Aberto.");
    atualiza_log(recado);

    arq = fopen(nome_do_arquivo, "r+b");
    return arq;
}

FILE* abrir_criar_arq_bin(char* nome_do_arquivo) {
    FILE* arq;
    if ((arq = abrir_arquivo_binario(nome_do_arquivo))==NULL) {

        arq = fopen(nome_do_arquivo, "r+b");
        strcpy(recado, "Arquivo Binário \"");
        strcat(recado, nome_do_arquivo);
        strcat(recado, "\" Criado.");
        atualiza_log(recado);
    }
    return arq;
}

long tam_registro(FILE* arq) {

    REGISTRO registro;
    long offset = ftell(arq);
    fread(&registro, sizeof(REGISTRO), 1, arq);
    offset -= ftell(arq);
    fseek(arq, offset, SEEK_CUR);

    return offset;
}


//TODO: tem que usar o método first-fit sem considerar fragmentação

void incluir(REGISTRO* registro) {

    // FILE* registros = fopen("registros.bin", "rb+");

    // fwrite(&registros, sizeof(REGISTRO), 1, registros);
    // fclose(registros);
    
    // Big Ryan Version

    FILE *in;
    int i = 0, i_registro;
    
    if((in = fopen("insere.bin","rb")) == NULL){
        printf("Erro durante a abertura do arquivo!\n");
        return 0;
    }
    else{
        
        printf("Qual registro gostaria de inserir? (Digite algum número correspondente)\n");
        scanf("%d", &i_registro);
        printf("\n%d\n", i_registro);
        
        struct Locacao locacao1;
        //fread(&locacao1, sizeof(struct Locacao), 1, in);
        fread(&locacao1, sizeof(struct Locacao), 1, in);

        // ERROS NA LEITURA! só tá lendo o primeiro valor, ainda estou testando..

        printf("Codigo Cliente -> %s\n", locacao1.codClie);
        printf("Cod Veiculo -> %s\n", locacao1.codVei);
        printf("Chave Primaria -> %s\n", locacao1.chavePri);
        printf("Nome Cliente -> %s\n", locacao1.nomeCliente);
        printf("Nome Veic-> %s\n", locacao1.nomeVeiculo);
        printf("Dias -> %d\n", locacao1.qtdDias);
    }

}

bool removerRegistro(const char* nomeArquivo, const char* chavePrim) {

    FILE* arquivo = abrir_arquivo_binario(nomeArquivo);

    //size_t tamanhoRegistro = sizeof(REGISTRO);

    REGISTRO registro;
    char chaveRegistro[21]; // codCliente = 12 / codVeiculo = 8 / fim do arquivo = 1
    long offset = tam_registro(arquivo);

    while (fread(&registro, sizeof(REGISTRO), 1, arquivo)) {

        //marca posicao inicial do registro
        //offset = ftell(arquivo);

        // Lê registro e verifica se acabou o arquivo
        //if (fread(&registro, sizeof(REGISTRO), 1, arquivo))
           // break;
        //Se existe registro
        if (registro.codClie[0] != '*') {

            // Concatena "codClie + codVei"
            //snprintf(chaveRegistro, sizeof(chaveRegistro), "%s%s", registro.codClie, registro.codVei);
            strcpy(chaveRegistro, registro.codClie);
            strcat(chaveRegistro, registro.codVei);

            // Verifica se a chave do registro corresponde à chave primária
            if (strcmp(chaveRegistro, chavePrim) == 0) {
                // Marca como removido
                registro.codClie[0] = '*';

                // Vai para a posição do reg a ser removido
                //fseek(arquivo, offset, SEEK_SET);
                fseek(arquivo, offset, SEEK_CUR);

                // Escreve o marcador de remoção no arquivo
                fwrite(&registro.codClie[0], sizeof(char), 1, arquivo);

                strcpy(recado,"Registro com chave primária \"");
                strcat(recado, chavePrim);
                strcat(recado,"\" encontrado no arquivo.");
                atualiza_log(recado);

                fclose(arquivo);
                return true;
            }
        }
    }

    strcpy(recado,"Registro com chave primária \"");
    strcat(recado, chavePrim);
    strcat(recado,"\" não encontrado no arquivo.");
    atualiza_log(recado);
    
    fclose(arquivo);
    return false;
}

void compactacao(){

}


REGISTRO* carregarInclusao(const char* nomeArquivo, int* numRegistros) {
    FILE* arquivo = fopen(nomeArquivo, "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    //tamanho arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    rewind(arquivo);

    // calcular numero de registros
    (*numRegistros) = tamanhoArquivo / sizeof(REGISTRO);

    REGISTRO* vetorRegistros = (REGISTRO*)malloc((*numRegistros) * sizeof(REGISTRO));

    //Lê registros
    fread(vetorRegistros, sizeof(REGISTRO), (*numRegistros), arquivo);

    // Fecha o arquivo
    fclose(arquivo);

    return vetorRegistros;
}

char** carregarExclusao(const char* nomeArquivo, int* numChaves) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        exit(1);
    }

    char** vetorChaves = NULL;
    *numChaves = 0;

    char chave[20];

    // Lê as chaves primárias do arquivo e insere no vetor
    while (fscanf(arquivo, "%s", chave) == 1) {
        char* novaChave = (char*)malloc(strlen(chave) + 1);
        strcpy(novaChave, chave);

        // Realoca o vetor para incluir a nova chave primária
        vetorChaves = (char**)realloc(vetorChaves, (*numChaves + 1) * sizeof(char*));
        vetorChaves[*numChaves] = novaChave;

        (*numChaves)++;
    }

    // Fecha o arquivo
    fclose(arquivo);

    return vetorChaves;
}

void imprimirRegistros(REGISTRO* vetorRegistros, int numRegistros) {
    for (int i = 0; i < numRegistros; i++) {
        printf("Registro %d:\n", i + 1);
        printf("Código do Cliente: %s\n", vetorRegistros[i].codClie);
        printf("Código do Veículo: %s\n", vetorRegistros[i].codVei);
        printf("Nome do Cliente: %s\n", vetorRegistros[i].nomeCliente);
        printf("Nome do Veículo: %s\n", vetorRegistros[i].nomeVeiculo);
        printf("Quantidade de Dias: %c\n", vetorRegistros[i].qtdDias);
        printf("\n");
    }
}

char[] carregarExclusao(const char* nomeArquivo, int* numRegistros){`
}