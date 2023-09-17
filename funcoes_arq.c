#include "header.h"

FILE* abrir_arquivo_binario(char* nome_do_arquivo) {

    FILE* arq;
    arq = fopen(nome_do_arquivo, "rb");
    bool inexistencia = (arq == NULL);
    fclose(arq);

    arq = fopen(nome_do_arquivo, "r+b");
    
    if (inexistencia)
        return NULL;
    return arq;
}

void incluir(REGISTRO* registro) {
//hello
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

void removerRegistro(const char* nomeArquivo, const char* chavePrim) {
    FILE* arquivo = fopen(nomeArquivo, "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        exit(1);
    }

    size_t tamanhoRegistro = sizeof(struct Registro);

    int registroEncontrado = false;
    int final;
    while (true) {
        struct Registro registro;
        long offset = ftell(arquivo);

        // Lê registro
        final = fread(&registro, tamanhoRegistro, 1, arquivo);
        if (final == 0)
            break;
        //Se existe registro
        if (registro.codClie[0] != '*') {
            char chaveRegistro[21]; // codCliente = 12 / codVeiculo = 8 / fim do arquivo = 1

            // Concatena "codClie + codVei"
            snprintf(chaveRegistro, sizeof(chaveRegistro), "%s%s", registro.codClie, registro.codVei);

            // Verifica se a chave do registro corresponde à chave primária
            if (strcmp(chaveRegistro, chavePrim) == 0) {
                // Marca como removido
                registro.codClie[0] = '*';

                // Vai para a posição do reg a ser removido
                fseek(arquivo, offset, SEEK_SET);

                // Escreve o marcador de remoção no arquivo
                fwrite(&registro.codClie[0], sizeof(char), 1, arquivo);

                registroEncontrado = true;
                break;
            }
        }

    }
    fclose(arquivo);

    if (!registroEncontrado)
        printf("Registro com chave primária \"%s\" não encontrado no arquivo.\n", chavePrim);
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


