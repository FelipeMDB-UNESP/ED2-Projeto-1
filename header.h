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

// Definindo a struct
typedef struct registro {
    char codClie[12];
    char codVei[8];
    char nomeCliente[50];
    char nomeVeiculo[50];
    int qtdDias;
} REGISTRO;

void atualiza_log(char* sentenca);

void limpar_log();

FILE* abrir_arquivo_binario(char* nome_do_arquivo);

#endif