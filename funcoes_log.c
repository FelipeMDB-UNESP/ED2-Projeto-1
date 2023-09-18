#include "header.h"

    void atualiza_log(char* sentenca) {

        bool inexistencia;
        FILE* log;
        
        log = fopen("log.txt", "r");
        
        if (log == NULL) {
            inexistencia = true;
        } else {
            inexistencia = false;
        }

        fclose(log);

        log = fopen("log.txt", "a+");
        if (inexistencia) {
            fprintf(log,"       REGISTRO DE ATIVIDADE:\n");
        }
        fprintf(log,"  # %s\n", sentenca);
        fclose(log);
    }

    void limpar_log() {
        remove("log.txt");
    }