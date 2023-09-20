#include "header.h"
/*
Início de Arquivo -> |<cabecalho>
Normal -> |<ponteiro><12>codClie|codVei|nomeCliente|nomeVeiculo|<qtdDias>
Apagado -> *<ponteiro><12>codClie|codVei|nomeCliente|nomeVeiculo|<qtdDias>
Fim de Arquivo -> #
    fseek(arq,sizeof(char),SEEK_END) -> caso vá adicionar um registro no final do arquivo -> ao adicionar, colocar #
Espaços Vazios -> '\0'
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

void limpar_string(char* string) {
    free(string);
}

void limpar_int(int* num) {
    free(num);
}


void limpar_registro(REGISTRO* registro) {
    limpar_string(registro->codClie);
    limpar_string(registro->codVei);
    limpar_string(registro->nomeCliente);
    limpar_string(registro->nomeVeiculo);
    limpar_int(registro->qtdDias);
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

long ler_cabecalho(FILE* arq) {
    rewind(arq);
    long cabecalho;
    char inicial;
    fread(&inicial,sizeof(char),1,arq);
    fread(&cabecalho,sizeof(cabecalho),1,arq);
    return cabecalho;
}

void atualiza_cabecalho(FILE* arq, long ponteiro) {
    rewind(arq);
    char aux;
    fwrite(&aux,sizeof(char),1,arq);
    fwrite(&position,sizeof(long),1,arq);
    rewind(arq);
}

REGISTRO* ler_registro(FILE* arq) {
    
    REGISTRO* registro;
    char existe;
    long ponteiro;
    char num;
    char temp;

    fread(&existe,sizeof(char),1,arq);
    
    switch (existe) {
        case '#':
            return NULL;
        case '*':
            fread(&ponteiro,sizeof(char),1,arq);
            fread(&num,sizeof(char),1,arq);
            fseek(arq, sizeof(char)*num + sizeof(int),SEEK_CUR);
            return ler_registro(arq);
        case '|':
            registro = criar_registro();

            fread(&ponteiro,sizeof(char),1,arq);

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

            atualiza_log("Registro lido.");
            return registro;
        
        case '\0':
            return ler_registro(arq);
        default:
    }
}

int escrever_registro(FILE* arq, REGISTRO* registro) {

    char existe;
    long ponteiro_anterior = ftell(arq);
    long ponteiro_atual = ler_cabecalho(arq);
    long ponteiro_posterior;
    long ponteiro_nulo = -1;
    char num;
    char tamanho;

    while (ponteiro_atual != -1) {
        fseek(arq,ponteiro_atual,SEEK_SET);

        fread(&existe,sizeof(char),1,arq);
        fread(&ponteiro_posterior,sizeof(char),1,arq);
        fread(&tamanho,sizeof(char),1,arq);

        num = (char) (strlen(registro->codClie) + strlen(registro->codVei) + strlen(registro->nomeCliente) + strlen(registro->nomeVeiculo) + 4);
        if (tamanho==num||tamanho>num) {

            fseek(arq,ponteiro_atual,SEEK_SET);

            fputc('|',arq);
            fwrite(&ponteiro_nulo,sizeof(long),1,arq);
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

            while (tamanho>num) {
                fputc('\0',arq);
                num++;
            }

            fseek(arq,ponteiro_anterior+sizeof(char),SEEK_SET);
            fwrite(&ponteiro_posterior,sizeof(long),1,arq);

            rewind(arq);
            atualiza_log("Registro escrito sobre outro registro.");
            return 1;
        }
        ponteiro_anterior = ponteiro_atual;
        ponteiro_atual = ponteiro_posterior;
    }

    fseek(arq,sizeof(char),SEEK_END);

    fputc('|',arq);

    fwrite(&ponteiro_nulo,sizeof(long),1,arq);

    num = (char) (strlen(registro->codClie) + strlen(registro->codVei) + strlen(registro->nomeCliente) + strlen(registro->nomeVeiculo) + 4);
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
    atualiza_log("Registro escrito no final.");
    return 2;
}

bool remover_registro(FILE* arq, char* chave) {
    char* possivel_chave;
    REGISTRO registro;
    long cabecalho = ler_cabecalho(arq);
    long position;
    char recado[64];
    char asterisco[] = "*";


    for (position = ftell(arq);(registro = ler_registro(arq))!=NULL; ) {

        possivel_chave = adicionar_string_string(registro->codClie,registro->codVei);

        limpar_registro(registro);

        if (strcmp(possivel_chave,chave) == 0) {
            fseek(arq, position,SEEK_SET);
            fwrite(asterisco,sizeof(char),1,arq);
            fwrite(&cabecalho,sizeof(long),1,arq);
            
            strcpy(recado,"Registro de palavra chave \"");
            strcat(recado, chave);
            strcat(recado, "deletado.");
            atualiza_log(recado);

            atualiza_cabecalho(arq,position);

            limpar_string(possivel_chave);
            return true;
        }

        limpar_string(possivel_chave);
        position = ftell(arq);
    }

    strcpy(recado,"Registro de palavra chave \"");
    strcat(recado, chave);
    strcat(recado, "nao encontrado.");
    atualiza_log(recado);

    return false;
}

void desfragmentar(char* nomeArquivo) {
    FILE* escritor = abrir_arquivo_binario(nomeArquivo);
    FILE* leitor = abrir_arquivo_binario(nomeArquivo);
    REGISTRO* registro;

    ler_cabecalho(arq);

    while ((registro = ler_registro(leitor))!=NULL) {

        fputc('|',escritor);

        char num = (char) (strlen(registro->codClie) + strlen(registro->codVei) + strlen(registro->nomeCliente) + strlen(registro->nomeVeiculo) + 4);
        fwrite(&num,sizeof(char),1,escritor);

        fwrite(registro->codClie,sizeof(char),strlen(registro->codClie),escritor);
        fputc('|',escritor);

        fwrite(registro->codVei,sizeof(char),strlen(registro->codVei),escritor);
        fputc('|',escritor);

        fwrite(registro->nomeCliente,sizeof(char),strlen(registro->nomeCliente),escritor);
        fputc('|',escritor);

        fwrite(registro->nomeVeiculo,sizeof(char),strlen(registro->nomeVeiculo),escritor);
        fputc('|',escritor);

        fwrite(registro->qtdDias,sizeof(int),1,escritor);

        limpar_registro(registro);
    }
    fputc('#',escritor);
}