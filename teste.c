#include "header.h"

int main() {

    FILE* arq = abrir_criar_arq_bin("Data.bin");
    REGISTRO* registro;
    bool load_de_arquivos = false;

    //chave primária deve ser criada ao se concatenar codClie e codVei
    // REGISTRO r1;
    // strcpy(r1.codClie, "73849561829");
    // strcpy(r1.codVei, "1547LASW");

    // strcpy(r1.chavePri, "73849561829");
    // strcat(r1.chavePri, l1.codVei);
    /*
    int numRegistrosInserir = 0;
    int numRegistrosApagar = 0;
    REGISTRO* vetorRegistrosInserir;
    char** vetorRegistrosApagar; 
    */

    int opcao;

    int posicao;

    REGISTRO** pasta;

    char** chaveiro;

    do {
        atualiza_log("Execucao do Menu");

        // Exibe o menu
        printf("Menu:\n");
        printf("1. Insercao\n");
        printf("2. Remocao\n");
        printf("3. Compactacao\n");
        printf("4. Carrega Arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao (0-4): ");
        scanf(" %d", &opcao);

        switch (opcao) {
            case 1:
                printf("Realizando a Insercao:\n");
                if(flag == true){
                    scanf(" %d", &posicao);
                    inserir_registro(arq,pasta[posicao]);
                    atualiza_log("Insercao realizada");
                } else{
                    atualiza_log("Insercao nao realizada. Insira um arquivo primeiro!");
                }

                break;
            case 2:
                printf("Realizando a remocao:\n");
                
                break;
            case 3:
                printf("Compactacao:\n");
                //compactacao();
                break;
            case 4:
                pasta = carregar_dados("insere.bin");
                chaveiro = carregar_chaves_delecao("remove.bin");
                atualiza_log("Arquivos carregados");
                load_de_arquivos = true;
                //vetorRegistrosApagar = carregarExclusao("remove.bin", &numRegistrosApagar);
                //printf("Registros a apagar:\n");
                //imprimirRegistros(vetorRegistrosApagar, numRegistrosApagar);
                break;
            case 0:
                atualiza_log("Execucao Finalizada.");
                exit(0);
            default:
                atualiza_log("Opcao invalida. Por favor, escolha uma opcao valida (0-4).");
                break;
        }
    } while (opcao != 0);   



    return 0;
}