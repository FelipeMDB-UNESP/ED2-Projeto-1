#include "header.h"

/* Logica aplicada:
Início de Arquivo -> |<cabecalho>
Normal -> |<-1><39>codClie|codVei|nomeCliente|nomeVeiculo|<qtdDias>
Apagado -> *<ponteiro><39>codClie|codVei|nomeCliente|nomeVeiculo|<qtdDias>
Fim de Arquivo -> #
Espaços Vazios -> '\0'
*/

//Funcoes de alocacao de espaco, permitindo criar campos de tamanho variavel, variando tambem o tamanho do registro.

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


//Funcoes de limpeza da alocacao de espaco.

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


//Funcoes de trabalho com strings de tamanho variavel.

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


//Funcoes de leitura e manipulacao do cabecalho do arquivo binario trabalhado.

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


//Funcao de leitura de um registro do arquivo.

REGISTRO* ler_registro(FILE* arq) {
    
    REGISTRO* registro;
    char existe;
    long ponteiro;
    char num;
    char temp;

    //checagem do primeiro caractere que compoe o espaco suposto de ser do registro.
    fread(&existe,sizeof(char),1,arq);
    
    switch (existe) {
        case '#': //caso de fim de arquivo, retorna null.
            return NULL;

        case '*': //caso o registro esteja apagado, le o proximo.

            fread(&ponteiro,sizeof(char),1,arq);
            fread(&num,sizeof(char),1,arq);

            fseek(arq, sizeof(char)*num + sizeof(int),SEEK_CUR);

            return ler_registro(arq);

        case '|': /*caso tenha um registro, aloca espaco na memoria e passa as informacoes
            dele para este espaco, retornando o ponteiro do registro como parametro.*/
            
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
        
        case '\0': //caso haja uma lacuna, tenta ler o registro no proximo caractere.
            return ler_registro(arq);

        default:
    }
}


//Escreve, no local em que o ponteiro se encontra, o registro dado.

void escrever_registro(FILE* arq, REGISTRO* registro) {

    long ponteiro_nulo = -1;
    char num = (char) (strlen(registro->codClie) + strlen(registro->codVei) + strlen(registro->nomeCliente) + strlen(registro->nomeVeiculo) + 4);

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
}


/*Insere um registro dado no arquivo, usando a estrategia first fit, 
e se nao houver espaco vazio, escreve-o no final do mesmo.*/

int inserir_registro(FILE* arq, REGISTRO* registro) {

    /*declaracao de long como sendo as posicoes que sao escritas no arquivo, a fim de ler a "lista encadeada" de
    registros apagados, se houver.*/

    char existe;
    long ponteiro_anterior = ftell(arq);
    long ponteiro_atual = ler_cabecalho(arq);
    long ponteiro_posterior;
    long ponteiro_nulo = -1;
    char tamanho_necessario = (char) (strlen(registro->codClie) + strlen(registro->codVei) + strlen(registro->nomeCliente) + strlen(registro->nomeVeiculo) + 4);
    char tamanho_atual;
    REGISTRO* aux;

    while (ponteiro_atual != -1) {
        fseek(arq,ponteiro_atual,SEEK_SET); //ida a posicao do arquivo apagado.

        fread(&existe,sizeof(char),1,arq);
        fread(&ponteiro_posterior,sizeof(char),1,arq);
        fread(&tamanho_atual,sizeof(char),1,arq);

        

        if (tamanho_atual==tamanho_necessario||tamanho_atual>tamanho_necessario) {
            //comparacao para ver se tem como colocar o novo registro nele.

            fseek(arq,ponteiro_atual,SEEK_SET);

            inserir_registro(arq,registro);

            //preencher com caractere nulo para marcar a fragmentacao externa.
            while (tamanho_atual>tamanho_necessario) {
                fputc('\0',arq);
                tamanho_necessario++;
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

    //caso o cabecalho seja -1 ou se acabar a lista e nenhum item tiver espaco necessario, escreve no fim do arquivo

    for (rewind(arq),ler_cabecalho(ponteiro_atual);(aux = ler_registro(arq)) !=NULL;limpar_registro(aux))

    fseek(arq,(-1)*sizeof(char),SEEK_CUR);
    
    inserir_registro(arq,registro);
    
    fputc('#',arq);

    rewind(arq);
    atualiza_log("Registro escrito no final do Arquivo.");
    return 2;
}


//Remocao mediante a chave, marcando o espaco vago e adicionando na lista de espacos vagos no cabecalho
bool remover_registro(FILE* arq, char* chave) {

    char* possivel_chave;
    REGISTRO* registro;
    long cabecalho = ler_cabecalho(arq);
    long posicao;

    char recado[64];
    char asterisco[] = "*";

    //leitura da posicao antes da leitura do registro, permitindo voltar ao inicio do registro.
    for (posicao = ftell(arq);(registro = ler_registro(arq))!=NULL; ) {

        //criacao da chave do registro atual.
        possivel_chave = adicionar_string_string(registro->codClie,registro->codVei);

        limpar_registro(registro);

        if (strcmp(possivel_chave,chave) == 0) {
            //se for a chave, escreve o asterisco e o endereco do proximo item da lista de apagados.

            fseek(arq, posicao,SEEK_SET);
            fwrite(asterisco,sizeof(char),1,arq);
            fwrite(&cabecalho,sizeof(long),1,arq);
            
            strcpy(recado,"Registro de palavra chave \"");
            strcat(recado, chave);
            strcat(recado, "deletado.");
            atualiza_log(recado);

            //coloca esta posicao como primeiro item na lista de apagados.
            atualiza_cabecalho(arq,posicao);

            limpar_string(possivel_chave);
            return true;
        }

        limpar_string(possivel_chave);
        posicao = ftell(arq);
    }

    strcpy(recado,"Registro de palavra chave \"");
    strcat(recado, chave);
    strcat(recado, "nao encontrado.");
    atualiza_log(recado);

    return false;
}


/*Compactacao a fim de desfragmentar o arquivo, deixando bytes vagos no
final do arquivo a fim de serem utilizados ao inserir um novo registro*/
void compactar_arquivo(char* nomeArquivo) {

    /*Criacao de 2 ponteiros sobre o mesmo arquivo, um 
    para realizar a leitura e outro para realizar a escrita*/
    FILE* escritor = abrir_arquivo_binario(nomeArquivo);
    FILE* leitor = abrir_arquivo_binario(nomeArquivo); 
    REGISTRO* registro;

    //Leitura do cabecalho para comecar a ler os registros
    ler_cabecalho(arq);

    //leitura do arquivo completo pelo leitor e escrita pelo outro ponteiro, sobrepondo os dados nos espacos vazios
    while ((registro = ler_registro(leitor))!=NULL) {

        escrever_registro(escritor,registro);

        limpar_registro(registro);
    }
    //insercao do caractere de finalizacao do arquivo
    fputc('#',escritor);


    free(leitor);
    free(escritor);
}