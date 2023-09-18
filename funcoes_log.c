#include "header.h"

    void atualiza_log(char* sentenca) {
        
        char c;

        bool inexistencia = false;
        FILE* log;
        
        log = fopen("log.txt", "r");
        
        if (log == NULL) {
            inexistencia = true;
        } else {
            inexistencia = false;
        }
        
        //inexistencia = fread(&c, sizeof(char),1,log);
        /*
        if ((log = fopen("log.txt", "r")) == NULL) {
            inexistencia = true;
        } else {
            inexistencia = false;
        }*/

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