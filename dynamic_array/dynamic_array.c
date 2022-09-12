#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*criamos o struct para o vetor dinamico com um apontador que 
armazenara a sequencia, os indices do inicio e fim, seu tamanho
e a quantidade de elementos contidos por ela*/
typedef struct dinamico
{
    int* sequencia;
    int inicio;
    int fim;
    int tamanho;
    int quantidade;
}dinamico;

/*funcao que verifica se a sequencia esta vazia*/
void isempty(dinamico* din){
    int empty;
    empty = (din->quantidade == 0);
    if(empty)
        printf("yes\n");
    else
        printf("no\n");

    return ;
}

/*funcao que imprime o primeiro elemento da sequencia*/
void printfirst(dinamico* din){
    printf("%d\n",din->sequencia[din->inicio]);
    
    return ;
}
/*funcao que imprime o ultimo elemento da sequencia*/
void printlast(dinamico* din){
    printf("%d\n",din->sequencia[din->fim]);
    
    return ;
}

/*funcao que redimensiona a sequencia*/
void resize(dinamico* din, int t){
    /*criamos um vetor troca para armazenar os elementos da antiga sequencia
    e transferi-los para uma nova sequencia redimensionada e ja reordenada*/
    int troca[din->quantidade];
    int i;

    /*transferimos os elementos da sequencia para troca, ordenando-os*/
    for( i = 0; i < din->quantidade; i++)       
		troca[i] = din->sequencia[(din->inicio+i)%(din->tamanho)];      
    
    /*liberamos sequencia e alocamos uma nova com o tamanho t da entrada*/
    free(din->sequencia);
    din->sequencia = malloc(t*sizeof(int));

    /*transferimos os elementos de troca para a nova sequencia e atualizamos
    os valores de inicio, fim e tamanho*/
    for( i = 0; i < din->quantidade; i++)
        din->sequencia[i] = troca[i];
    din->inicio = 0;
    din->fim = din->quantidade-1;
    din->tamanho = t;
   
    return ;
}

/*funcao que remove o primeiro elemento da sequencia*/
void removefirst(dinamico* din){
    /*antes de remover, checamos se e necessario diminuir a sequencia
    i.e., se a quantidade de elementos na sequencia corresponde a um quarto
    de seu tamanho*/
    if(din->quantidade==din->tamanho/4)
        resize(din,din->tamanho/2);
    /*se o inicio da sequencia for o ultimo indice do vetor, atualizamos
    inicio para -1*/
    if(din->inicio==din->tamanho-1)
        din->inicio=-1;
    /*atualizamos inicio para o elemento seguinte da sequencia
    e diminuimos a quantidade de elementos na sequencia*/
    din->inicio++;
    din->quantidade--;

    return ;
}

/*funcao que remove o ultimo elemento da sequencia*/
void removelast(dinamico* din){
    /*antes de remover, novamente checamos se e necessario redimensionar*/
    if(din->quantidade==din->tamanho/4)
        resize(din,din->tamanho/2);
    /*se o fim da sequencia for o primeiro indice do vetor, atualizamos
    fim para tamanho*/
    if(din->fim==0)
        din->fim=din->tamanho;
    /*atualizamos fim para o elemento anterior da sequencia
    e diminuimos a quantidade de elementos na sequencia*/
    din->fim--;
    din->quantidade--;

    return ;
}

/*funcao que insere um inteiro ao inicio da sequencia*/
void insertfirst(dinamico* din, int n){
    /*antes de inserir, checamos se e necessario aumentar a sequencia
    i.e., se a quantidade de elementos na sequencia corresponde ao 
    seu tamanho */
    if(din->quantidade==din->tamanho)
        resize(din,2*din->tamanho);
    /*se o inicio da sequencia for o primeiro indice do vetor, atualizamos 
    inicio para tamanho*/
    if(din->inicio==0)
        din->inicio = din->tamanho;
    /*atualizamos inicio*/
    din->inicio--;
    /*caso o vetor tenha tamanho 1, ao inserir o primeiro elemento
    o inicio e o fim da fila sao os mesmos, entao assim o fazemos*/
	if(din->tamanho==1)
		din->fim=din->inicio;
    /*inserimos o elemento n na nova posicao de inicio e atualizamos quantidade*/
    din->sequencia[din->inicio] = n;
    din->quantidade++;

    return ;
}

/*funcao que insere um inteiro ao fim da sequencia*/
void insertlast(dinamico* din, int n){
    /*novamente checamos se necessario aumentar a sequencia*/
    if(din->quantidade==din->tamanho)
        resize(din,2*din->tamanho);
    /*se o fim da sequencia for o ultimo indice do vetor, atualizamos
    fim para -1*/
    if(din->fim==din->tamanho-1)
        din->fim = -1;
    /*atualizamos fim*/
    din->fim++;
    /*caso o vetor tenha tamanho 1, ao inserir o primeiro elemento
    o fim e o inicio da fila sao os mesmos, entao assim o fazemos*/
	if(din->tamanho==1)
		din->inicio=din->fim;
    /*inserimos n na nova posicao de fim e atualizamos quantidade*/
    din->sequencia[din->fim] = n;
    din->quantidade++;

    return ;
}

int main(){
    /*criamos as variaveis*/
    int num;
    char comando[13];
    dinamico din;

    /*inicializamos o vetor o vetor dinamico com tamanho 1*/
    din.tamanho = 1;
    din.sequencia = malloc(din.tamanho*sizeof(int));
    din.inicio = din.tamanho;
    din.fim = -1;
    din.quantidade = 0;

    /*lemos os comandos e chamamos as funcoes de acordo
    caso o comando seja imprimir ou remover, verificamos se ha
    algum elemento na sequencia para poder executar o comando
    caso o comando seja inserir, lemos tambem o inteiro a ser inserido*/
    while(fgets(comando,13,stdin)!=NULL){     
        if (strstr(comando,"is-empty")!=NULL) 
            isempty(&din);

        else if (strstr(comando,"insert-first")!=NULL) {
            scanf("%d",&num);
            insertfirst(&din,num);
        }
        else if (strstr(comando,"insert-last")!=NULL) {
            scanf("%d",&num);
            insertlast(&din,num);
        }
        else if (strstr(comando,"remove-first")!=NULL){
            if(din.quantidade!=0)
                removefirst(&din);
        } 
        else if (strstr(comando,"remove-last")!=NULL){
            if (din.quantidade!=0)
                removelast(&din);            
        } 

        else if (strstr(comando,"print-first")!=NULL){
            if(din.quantidade!=0)
                printfirst(&din);
        }           

        else if (strstr(comando,"print-last")!=NULL){
            if(din.quantidade!=0)
                printlast(&din);
        } 
    }

    /*liberamos a memoria alocada*/
    free(din.sequencia);

    return 0;
}