#include "header.h"
/*
Normal -> |<12>codClie|codVei|nomeCliente|nomeVeiculo|<qtdDias>
Apagado -> *<12>codClie|codVei|nomeCliente|nomeVeiculo|<qtdDias>
Fim de Arquivo -> #
    fseek(arq,sizeof(char),SEEK_END) -> caso vá adicionar um registro no final do arquivo -> ao adicionar, colocar #
*/

typedef struct registro {
    char* codClie;
    char* codVei;
    char* nomeCliente;
    char* nomeVeiculo;
    int* qtdDias;
} REGISTRO;

int* criar_int() {
    int* inteiro = (int*) malloc(sizeof(int));
    return inteiro;
}

char* criar_string() {
    char* string = (char*) malloc(sizeof(char));
    string[0] = '\0';
    return string;
}

REGISTRO* criar_registro() {
    REGISTRO* registro = (REGISTRO*) malloc(sizeof(REGISTRO));
    registro->codClie = criar_string();
    registro->codVei = criar_string();
    registro->nomeCliente = criar_string();
    registro->nomeVeiculo = criar_string();
    registro->qtdDias = criar_int();
    return registro;
}

void adicionar_caractere_string(char* string, char caractere) {
    
    char* segunda_string;

    if (string[0] == '\0') {
        segunda_string = (char*) malloc(sizeof(char)*2);
        segunda_string[0] = caractere;
        segunda_string[1] = '\0';
    } else {
        segunda_string = (char*) malloc(sizeof(char)*(strlen(string)+2));
        segunda_string[strlen(string)+2] = '\0';
        strcpy(segunda_string, string);
        segunda_string[strlen(string)+1] = caractere;
    }
    free(string);
    string = segunda_string;
    free(segunda_string);
}

char* adicionar_string_string(char* string, char* segunda_string) {
    
    char* string_nova;

    if (string[0] == '\0')
        return segunda_string;
    if (segunda_string[0] == '\0')
        return string;

    string_nova = (char*) malloc(sizeof(char)*(strlen(string) + strlen(segunda_string) + 1));
    string_nova[strlen(string) + strlen(segunda_string)+1] = '\0';
    strcpy(string_nova, string);
    strcat(string_nova,segunda_string);
    return string_nova;
}

REGISTRO* ler_registro(FILE* arq) {
    
    REGISTRO* registro;
    char num;
    char existe;
    char temp;

    fread(&existe,sizeof(char),1,arq);
    
    switch (existe) {
        case '#':
            return NULL;
        case '*':
            fread(&num,sizeof(char),1,arq);
            fseek(arq, sizeof(char)*num + sizeof(int),SEEK_CUR);
            return ler_registro(arq);
        case '|':
            registro = criar_registro();

            fread(&num,sizeof(char),1,arq);

            for(fread(&temp, sizeof(char),1,arq) ; temp!='|' ;) {
                adicionar_caractere_string(registro->codClie,temp);
                fread(&temp, sizeof(char),1,arq);
            }

            for(fread(&temp, sizeof(char),1,arq) ; temp!='|' ;) {
                adicionar_caractere_string(registro->codVei,temp);
                fread(&temp, sizeof(char),1,arq);
            }

            for(fread(&temp, sizeof(char),1,arq) ; temp!='|' ;) {
                adicionar_caractere_string(registro->nomeCliente,temp);
                fread(&temp, sizeof(char),1,arq);
            }

            for(fread(&temp, sizeof(char),1,arq) ; temp!='|' ;) {
                adicionar_caractere_string(registro->nomeVeiculo,temp);
                fread(&temp, sizeof(char),1,arq);
            }
            
            fread(registro->qtdDias, sizeof(int), 1, arq);

            return registro;
        default:
    }
}

void escrever_registro(FILE* arq, REGISTRO* registro) {

    fseek(arq,sizeof(char),SEEK_END);

    fputc('|',arq);

    char num = (char) (strlen(registro->codClie) + strlen(registro->codVei) + strlen(registro->nomeCliente) + strlen(registro->nomeVeiculo) + 4);
    fwrite(&num,sizeof(char),1,arq);

    fwrite(registro->codClie,sizeof(char),strlen(registro->codClie),arq);
    fputc('|',arq);

    fwrite(registro->codVei,sizeof(char),strlen(registro->codVei),arq);
    fputc('|',arq);

    fwrite(registro->nomeCliente,sizeof(char),strlen(registro->nomeCliente),arq);
    fputc('|',arq);

    fwrite(registro->nomeVeiculo,sizeof(char),strlen(registro->nomeVeiculo),arq);
    fputc('|',arq);

    fwrite(registro->qtdDias,sizeof(int),1,arq);
    
    fputc('#',arq);

    rewind(arq);
}

void remover_registro(FILE* arq, char* chave) {
    char* possivel_chavel;


}

void desfragmentar(char* nomeArquivo) {
    FILE* escritor = abrir_arquivo_binario(nomeArquivo);
    FILE* leitor = abrir_arquivo_binario(nomeArquivo);

    
}