#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

typedef struct hashing{
    int ind;
    char cadeia[250];
}hashing;

/*funcao que converte string em numero*/
unsigned long djb2( char *str) {
  unsigned long hash = 5381;
  int c;
  
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; // hash * 32 + hash + c
  
  return hash;
}

/*funcoes de hashing*/
unsigned long f1(unsigned long k, int m){
    return (k % m);
}

unsigned long f2(unsigned long k, int m){
    return (1 + (k %(m-2)));
}

/*incremento duplo*/
unsigned long f(unsigned long k, int m, int i){
    return ((f1(k,m) + i*f2(k,m)) % m );
}

/*funcao que busca uma chave na tabela*/
void search(hashing* T, int m, char* c, unsigned long hash){
    int j = 0;
    unsigned long i = f(hash, m, j);

    while(T[i].ind > INT_MIN && strcmp(T[i].cadeia,c)){
        j++;
        i = f(hash, m, j);
    }

    if(!strcmp(T[i].cadeia,c))
        printf("encontrado %d\n",T[i].ind);
    else 
        printf("nao encontrado\n");
    
    return ;
}

/*funcao que insere uma chave na tabela*/
int insert(hashing* T, int m, char* c, unsigned long hash, int k){
    int j = 0;
    unsigned long i = f(hash, m, j);

    /*primeiro verificamos se a chave ja esta na tabela*/
    while(T[i].ind > INT_MIN && strcmp(T[i].cadeia,c)){
        j++;
        i = f(hash, m, j);
    }

    /*caso nao esteja, inserimos na primeira posicao vazia/removida
    que encontramos*/
    if(strcmp(T[i].cadeia,c)){
        j = 0;
        i = f(hash, m, j);
        while(T[i].ind > (INT_MIN + 1)){
            j++;
            i = f(hash, m, j);
        }
        strcpy(T[i].cadeia,c);
        T[i].ind = k;
        return 1;
    }

    return 0;
}

/*funcao que remove uma chave da tabela*/
void remove_h(hashing* T, int m, char* c, unsigned long hash){
    int j = 0;
    unsigned long i = f(hash, m, j);

    while(T[i].ind > INT_MIN && strcmp(T[i].cadeia,c)){
        j++;
        i = f(hash, m, j);
    }

    /*marcamos a posicao removida como INT_MIN + 1 e mudamos a chave*/
    if(!strcmp(T[i].cadeia,c)){
        T[i].ind = INT_MIN + 1 ;
        strcpy(T[i].cadeia,"vote_no_IMECC");
    }
    
    return ;
}

/******** main ****************/
int main(){
    hashing* T;
    char cmd[255];
    char* chave;
    int i, key = 0, m = 5023, n;
    unsigned long hash;

    /*inicializamos a tabela*/
    T = malloc(m*sizeof(hashing));
    for(i = 0; i < m; i++)
        T[i].ind = INT_MIN;

    /*lemos os comandos e chamamos as funcoes*/    
    fgets(cmd,255,stdin);
    n = strlen(cmd);
    cmd[n-1] = '\0';
    while( cmd[0] != 'f'){
        chave = cmd+2;
        hash = djb2(chave);
        if (cmd[0] == 'i')
            key += insert(T, m, chave, hash, key);
        else if (cmd[0] == 'b')
            search(T, m, chave, hash);
        else if (cmd[0] == 'r')
            remove_h(T, m, chave, hash);
        
        fgets(cmd,255,stdin);
        n = strlen(cmd);
        
        if (n>1)
            cmd[n-1] = '\0';
    }

    /*liberamos a tabela*/
    free(T);

    return 0;
}