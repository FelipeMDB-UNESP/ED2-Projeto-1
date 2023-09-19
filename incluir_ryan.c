#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


// Definindo a struct


int incluir(){

    // Struct para armazenar o input
    typedef struct buffer {
        char codClie[12];
        char codVei[8];
        char nomeCliente[50];
        char nomeVeiculo[50];
        int qtdDias;
    } BUFFER;
    FILE *in, *out;
    int i = 0, i_registro;
    
    //Abertura dos arquivos
    if((in = fopen("insere.bin","rb")) == NULL){
        printf("Erro durante a abertura do arquivo!\n");
        return 0;
    }
    
    else{
        
        printf("Qual registro gostaria de inserir? (Digite algum número correspondente)\n");
        scanf("%d", &i_registro); 
        BUFFER buffer_in;
        BUFFER buffer_in2;

        // - LEITURA NO INPUT - //
        int atual = 1;
        //PERCORRE O INPUT ATÉ CHEGAR NO INDICE DO QUE O USUARIO ESCOLHEU
        while (atual <= i_registro)
        {
            fread(&buffer_in, sizeof(struct buffer), 1, in);
            atual++;
        }  
        // ABERTURA ARQUIVO OUTPUT
        
         

        // - INSERÇÃO NO ARQUIVO OUTPUT --
        
        // Definir tamanho do registro (Torna-o Variável)
        
        //struct que seria o input
        int index_tam[4];
        index_tam[0] = strlen(buffer_in.codClie) + 1;
        index_tam[1] = strlen(buffer_in.codVei)+ 1;
        index_tam[2] = strlen(buffer_in.nomeCliente)+1;
        index_tam[3] = strlen(buffer_in.nomeVeiculo)+1;
 
        typedef struct registro_final {
        char tamanho;
        char codClie[index_tam[0]];
        char codVei[index_tam[1]];
        char nomeCliente[index_tam[2]];
        char nomeVeiculo[index_tam[3]];
        char qtdDias;
        } FINAL;
                
        
        struct registro_final registro_out; 

        strcpy(registro_out.codClie, buffer_in.codClie); 
        strcpy(registro_out.codVei, buffer_in.codVei); 
        strcpy(registro_out.nomeCliente, buffer_in.nomeCliente); 
        strcpy(registro_out.nomeVeiculo, buffer_in.nomeVeiculo); 
 
        //CALCULA TAMANHO DO REGISTRO
        int tamanho_registro = 0; 

        tamanho_registro = strlen(buffer_in.codClie) +
        strlen(buffer_in.codVei) + strlen(buffer_in.nomeCliente) +
        strlen(buffer_in.nomeVeiculo) + 7 + 1;
        registro_out.tamanho = tamanho_registro;
        
        //CHECAGEM DE ESPAÇO - (FIRST FIT)
        if((out = fopen("output.bin","ab")) == NULL){
            printf("Erro durante a criação do arquivo!\n");
            return 0;
        }
        fclose(out);


        //TESTES
        if((out = fopen("output.bin","rb")) == NULL){
            printf("Erro durante a criação do arquivo!\n");
            return 0;
        }
        int offset, total_offset;
        //inicializa no primeiro caractere do arquivo
        fseek(out, 0, SEEK_SET);

        offset = fgetc(out); // primeiro offset
        //printf("\n primeiro caractere = %d\n", offset);
        total_offset = offset;
        
        //printf("\n segundo caractere = %d\n", offset);
        
        while (offset != -1) // Enquanto não chegar no fim do arquivo
        {   
            fseek(out, offset-1, SEEK_CUR);
            offset = fgetc(out);
            if(offset == -1){ // Alcançou o fim do arquivo(não tem um registro a seguir)
                break;
            }else{
                total_offset = total_offset + offset;
            }
        }
        
        
        printf("offset%d\n", total_offset);
        fclose(out); 


        //INSERÇÃO EM SI 
         if((out = fopen("output.bin","ab")) == NULL){
            printf("Erro durante a criação do arquivo!\n");
            return 0;
        }        
        //Adiciono aqui para que no arquivo output seja escrito os '|'
        registro_out.codClie[strlen(buffer_in.codClie)] = '|'; 
        registro_out.codVei[strlen(buffer_in.codVei)] = '|';
        registro_out.nomeCliente[strlen(buffer_in.nomeCliente)] = '|';
        registro_out.nomeVeiculo[strlen(buffer_in.nomeVeiculo)] = '|'; 
        //QUNTIDADE DE DIAS (LINHA ABAIXO)
        registro_out.qtdDias = buffer_in.qtdDias;
        //Substituo o '|' no programa para manter a separação das strings
        //Nos possibilita armazenar as strings corretamente!
        fwrite(&registro_out, sizeof(struct registro_final), 1, out);
        registro_out.codClie[strlen(buffer_in.codClie)+0] = '\0'; 
        registro_out.codVei[strlen(buffer_in.codVei)+0] = '\0';
        registro_out.nomeCliente[strlen(buffer_in.nomeCliente)+0] = '\0';
        registro_out.nomeVeiculo[strlen(buffer_in.nomeVeiculo)+0] = '\0'; 
        
        //TESTES A RESPEITO DO NUMERO DE DIAS!
        // (Ambos funcionam!)
        //printf("TESTE cliente: %c\n", registro_out.qtdDias); // Transforma em Char
        //printf("Numero = %d", registro_out.qtdDias - '0');   // Transforma em Int
        
        // readme: O numero no código hex, vai ficar meio estranho, ele aparece como '-'(45),
        // mas como nos testes abaixo, ele pode ser lido normalmente como int pelo que vi
        // Além disso, o maior problema que não consegui resolver é para numeros de dias(ultimo campo)
        // que são maiores que 9(dois digitos), não estou conseguindo consertar... Mas para apenas
        // 1 digito está funcionando!
        
        fputc('|', out);
        //Adicionar isso faz com que tenham um "espaço nulo" no arquivo output, mas garante que os dados no programa fiquem corretos
        fputc('\0', out);
        fclose(out);
        
        
        fclose(in);

    }
}

void remover(){

}

void compactacao(){

}

void carregar(){

}



int main() {
    
    //chave primária deve ser criada ao se concatenar codClie e codVei
    // struct in l1;
    // strcpy(l1.codClie, "73849561829");
    // strcpy(l1.codVei, "1547LASW");

    // strcpy(l1.chavePri, "73849561829");
    // strcat(l1.chavePri, l1.codVei);


    int opcao;
    do {
        // Exibe o menu
        printf("\nMenu:\n");
        printf("1. Inserção\n");
        printf("2. Remoção\n");
        printf("3. Compactação\n");
        printf("4. Carrega Arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opção (0-4): ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Realizando a inserção:\n");
                incluir();
                break;
            case 2:
                printf("Realizando a remoção:\n");
                remover();
                break;
            case 3:
                printf("Compactação:\n");
                compactacao();
                break;
            case 4:
                printf("Carregando arquivo:\n");
                carregar();
                break;
            case 0:
                printf("Execução encerrada!\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida (0-4).\n");
                break;
        }
    } while (opcao != 0);



    return 0;
}