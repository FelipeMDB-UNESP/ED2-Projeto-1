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

char** criar_chaveiro() {
    char** chaveiro = (char**) malloc(sizeof(char*));
    chaveiro[0] = NULL;
    return chaveiro;
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

REGISTRO** criar_pasta() {
    REGISTRO** pasta = (REGISTRO**) malloc(sizeof(REGISTRO*));
    pasta[0] = NULL;
    return pasta;
}


//Funcoes de limpeza da alocacao de espaco.

void limpar_pasta(REGISTRO** pasta) {
    for(int i = 0; pasta[i] !=NULL; i++)
    limpar_registro(pasta[i]);
}

void limpar_registro(REGISTRO* registro) {
    limpar_string(registro->codClie);
    limpar_string(registro->codVei);
    limpar_string(registro->nomeCliente);
    limpar_string(registro->nomeVeiculo);
    limpar_int(registro->qtdDias);
}

void limpar_chaveiro(char** chaveiro) {
    for(int i = 0; chaveiro[i] !=NULL; i++)
        limpar_string(chaveiro[i]);
}

void limpar_string(char* string) {
    free(string);
}

void limpar_int(int* num) {
    free(num);
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
        segunda_string[strlen(string)+1] = '\0';
        strcpy(segunda_string, string);
        segunda_string[strlen(string)] = caractere;
    }
    limpar_string(string);
    string = segunda_string;
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

void adicionar_chave_chaveiro(char** chaveiro, char* chave) {
    
    char** segundo_chaveiro;

    if (chaveiro[0] == NULL) {
        segundo_chaveiro = (char**) malloc(sizeof(char*)*2);
        segundo_chaveiro[0] = chave;
        segundo_chaveiro[1] = NULL;
    } else {
        segundo_chaveiro = (char**) malloc(sizeof(char*)*(tam_chaveiro(chaveiro)+2));
        segundo_chaveiro[tam_chaveiro(chaveiro)+1] = NULL;
        copiar_chaveiros(segundo_chaveiro, chaveiro);
        segundo_chaveiro[tam_chaveiro(chaveiro)] = chave;
    }
    limpar_chaveiro(chaveiro);
    chaveiro = segundo_chaveiro;
}

int tam_chaveiro(char** chaveiro) {
    int i;
    for (i=0; chaveiro[i]!=NULL; i++) {
    }
    return i;
}

void copiar_chaveiros(char** chaveiro1, char** chaveiro2) {
    int i;
    for (i=0; chaveiro1[i]!=NULL && chaveiro2[i]!=NULL; i++) {
        chaveiro1[i] = chaveiro2[i];
    }
    chaveiro1[i]=NULL;
}

void copiar_pastas(REGISTRO** pasta1, REGISTRO** pasta2) {
    int i;
    for (i=0; pasta1[i]!=NULL && pasta2[i]!=NULL; i++) {
        pasta1[i] = pasta2[i];
    }
    pasta1[i]=NULL;
}

int tam_pasta(REGISTRO** pasta) {
    int i;
    for (i=0; pasta[i]!=NULL; i++) {
    }
    return i;
}

void adicionar_registro_pasta(REGISTRO** pasta, REGISTRO* registro) {
    
    REGISTRO** segunda_pasta;

    if (pasta[0] == NULL) {
        segunda_pasta = (REGISTRO**) malloc(sizeof(REGISTRO*)*2);
        segunda_pasta[0] = registro;
        segunda_pasta[1] = NULL;
    } else {
        segunda_pasta = (REGISTRO**) malloc(sizeof(REGISTRO*)*(tam_pasta(pasta)+2));
        segunda_pasta[tam_pasta(pasta)+1] = NULL;
        copiar_pastas(segunda_pasta, pasta);
        segunda_pasta[tam_pasta(pasta)] = registro;
    }
    limpar_pasta(pasta);
    pasta = segunda_pasta;
}

//Funcoes Arquivos Binarios

FILE* abrir_arquivo_binario(char* nome_do_arquivo) {

    FILE* arq;
    bool inexistencia;
    char recado[64];

    arq = fopen(nome_do_arquivo, "rb");
    inexistencia = (arq == NULL);
    fclose(arq);


    if (inexistencia) {
        strcpy(recado, "Arquivo Binário \"");
        strcat(recado, nome_do_arquivo);
        strcat(recado, "\" Inexistente.");
        atualiza_log(recado);
        return NULL;
    }


    strcpy(recado, "Arquivo Binário \"");
    strcat(recado, nome_do_arquivo);
    strcat(recado, "\" Aberto.");
    atualiza_log(recado);

    arq = fopen(nome_do_arquivo, "r+b");
    return arq;
}

FILE* abrir_criar_arq_bin(char* nome_do_arquivo) {
    FILE* arq;
    char recado[64];
    if ((arq = abrir_arquivo_binario(nome_do_arquivo))==NULL) {

        arq = fopen(nome_do_arquivo, "r+b");
        strcpy(recado, "Arquivo Binário \"");
        strcat(recado, nome_do_arquivo);
        strcat(recado, "\" Criado.");
        atualiza_log(recado);
    }
    return arq;
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
    fwrite(&ponteiro,sizeof(long),1,arq);
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

    for (rewind(arq),ler_cabecalho(arq);(aux = ler_registro(arq)) !=NULL;limpar_registro(aux)) {}

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
void compactar_arquivo(char* nomeArquivoDados) {

    /*Criacao de 2 ponteiros sobre o mesmo arquivo, um 
    para realizar a leitura e outro para realizar a escrita*/
    FILE* escritor = abrir_arquivo_binario(nomeArquivoDados);
    FILE* leitor = abrir_arquivo_binario(nomeArquivoDados); 
    REGISTRO* registro;

    //Leitura do cabecalho para comecar a ler os registros
    ler_cabecalho(leitor);

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

REGISTRO** carregar_dados(char* nomeArquivoInsercao) {
    FILE* arq;
    if ((arq = abrir_arquivo_binario(nomeArquivoInsercao)) == NULL) {
        fclose(arq);
        return NULL;
    }
    printf("Existe");
    int i;
    int cont;
    char caractere;
    REGISTRO** pasta = criar_pasta();
    REGISTRO* registro;
    bool fim_de_arquivo;

    char* inteiro; 
    atoi(inteiro);

    for (i=0; !fim_de_arquivo; i++) {
    printf("\nLaco %d fim do arquivo = %d", i, fim_de_arquivo);
        
        registro = criar_registro();
        inteiro = criar_string();
        printf("\nPos %d\n", i);

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0')
            adicionar_caractere_string(registro->codClie,caractere);

            printf("\nPos1 %d\n", i);

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0')
            adicionar_caractere_string(registro->codVei,caractere);

            printf("\nPos2 %d\n", i);

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0')
            adicionar_caractere_string(registro->nomeCliente,caractere);

            printf("\nPos3 %d\n", i);

        for (fread(&caractere,sizeof(char),1,arq);caractere == '\0';fread(&caractere,sizeof(char),1,arq)) {}
        fseek(arq,(-1)*sizeof(char),SEEK_CUR);

        printf("\nPos4 %d\n", i);

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0')
            adicionar_caractere_string(registro->nomeVeiculo,caractere);

            printf("\nPos5 %d\n", i);

        for (fread(&caractere,sizeof(char),1,arq);caractere == '\0';fread(&caractere,sizeof(char),1,arq)) {}
        fseek(arq,(-1)*sizeof(char),SEEK_CUR);

        printf("\nPos6 %d\n", i);

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0')
            adicionar_caractere_string(inteiro,caractere);

            printf("\nPos7 %d\n", i);

        for (fread(&caractere,sizeof(char),1,arq);caractere == '\0';fread(&caractere,sizeof(char),1,arq)) {}
        fseek(arq,(-1)*sizeof(char),SEEK_CUR);
        printf("\nPos8 %d\n", i);

        *(registro->qtdDias) = atoi(inteiro);
        limpar_string(inteiro);

        if (cont==0) {
            limpar_registro(registro);
            limpar_string(inteiro);
            fim_de_arquivo = true;
            break;
        }
        adicionar_registro_pasta(pasta,registro);
    }
    atualiza_log("Arquivo Dados Carregado.");
    return pasta;
}

char** carregar_chaves_delecao(char* nomeArquivoDelecao) {

    FILE* arq;
    if ((arq = abrir_arquivo_binario(nomeArquivoDelecao)) == NULL)
        return NULL;

    int i;
    int cont;
    char caractere;
    char** chaveiro = criar_chaveiro();
    REGISTRO* registro;
    bool fim_de_arquivo = false;



    for (i=0; !fim_de_arquivo; i++) {
        registro = criar_registro();

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0')
            adicionar_caractere_string(registro->codClie,caractere);
        

        while(((cont = fread(&caractere,sizeof(char),1,arq)) != 0) && caractere != '\0')
            adicionar_caractere_string(registro->codVei,caractere);
        
        if (cont==0) {
            fim_de_arquivo = true;
            limpar_registro(registro);
            break;
        }
        adicionar_chave_chaveiro(chaveiro,adicionar_string_string(registro->codClie,registro->codVei));
        limpar_registro(registro);
    }
    atualiza_log("Arquivo Chaves Carregado.");
    return chaveiro;
}