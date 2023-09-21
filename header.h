#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

/*DEFINICAO DE STRUCTS E FUNCOES*/

//Struct de ponteiros
typedef struct registro {
    char* codClie;
    char* codVei;
    char* nomeCliente;
    char* nomeVeiculo;
    int* qtdDias;
} REGISTRO;


//Funcoes Log
void atualiza_log(char* sentenca);

void limpar_log();


//Funcoes alocacao dinamica
int* criar_int();

char* criar_string();

REGISTRO* criar_registro();

REGISTRO** criar_pasta();


//Funcoes limpeza alocacao dinamica
void limpar_string(char* string);

void limpar_int(int* num);

void limpar_registro(REGISTRO* registro);

void limpar_chaveiro(char** chaveiro);



//Funcoes string dinamica
void adicionar_caractere_string(char* string, char caractere);

char* adicionar_string_string(char* string, char* segunda_string);

//Funcoes vetor chaves

void adicionar_chave_chaveiro(char** chaveiro, char* chave);

int tam_chaveiro(char** chaveiro);

void copiar_chaveiros(char** chaveiro1, char** chaveiro2);

//Funcoes vetor registro

void copiar_pastas(REGISTRO** pasta1, REGISTRO** pasta2);

int tam_pasta(REGISTRO** pasta);

void adicionar_registro_pasta(REGISTRO** pasta, REGISTRO* registro);


/*FUNCOES ARQUIVO BINARIO*/

FILE* abrir_arquivo_binario(char* nome_do_arquivo);

FILE* abrir_criar_arq_bin(char* nome_do_arquivo);

//Funcoes cabecalho
long ler_cabecalho(FILE* arq);

void atualiza_cabecalho(FILE* arq, long ponteiro);


//Funcoes registro
REGISTRO* ler_registro(FILE* arq);

void escrever_registro(FILE* arq, REGISTRO* registro);

int inserir_registro(FILE* arq, REGISTRO* registro);

bool remover_registro(FILE* arq, char* chave);

void compactar_arquivo(char* nomeArquivo);

REGISTRO** carregar_dados(char* nomeArquivoInsercao);

char** carregar_chaves_delecao(char* nomeArquivoDelecao);

#endif