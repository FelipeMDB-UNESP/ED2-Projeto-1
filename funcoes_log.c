#include "header.h"

    void atualiza_log(char* sentenca) {

        FILE* log = fopen("log.txt", "r");
        bool inexistencia = (log == NULL);
        fclose(log);
        log = fopen("log.txt", "a+");
        if (inexistencia)
            fprintf(log,"       REGISTRO DE ATIVIDADE:\n");
        fprintf(log,"  # %s\n", sentenca);
        fclose(log);
    }

    void limpar_log() {
        remove("log.txt");
    }