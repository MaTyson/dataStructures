# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

//vertice
typedef struct vertex{
    int d;
    int pi;
    int mark;
}vertex;

//grafo
typedef struct graph {
    int** A;
    vertex* V;
}graph;

//fila
typedef struct list {
    int queue;
    struct list* next;
}list;

/*funcao que remove o primeiro elemento de uma fila
e ja o libera*/
void removefirst(list** head){
    list* p = *head;
    *head = (*head)->next;
    free(p);

    return ;
}

/*funcao que insere um elemento ao final da fila*/
void insertlast(list** head,  int u){
    list* p = *head;
    list* aux = malloc(sizeof(list));

    if(!aux)
        return;
    
    aux->queue = u;
    aux->next = NULL;

    if(!p)
        *head = aux;
    
    else {
        while(p->next)
            p = p->next;
        p->next = aux;
    }

    return ;
}

//funcao que faz a busca em largura no grafo e imprime os vertices e distancias alcancados
void bfs(graph* G, int n, int k){
    int i, u ;
    list* L = NULL;

    //inicializamos as distancias, predecessores e marcas
    for(i = 0; i < n; i++ ){
        G->V[i].d = INT_MAX;
        G->V[i].pi = INT_MIN;
        G->V[i].mark = 0;
    }

    printf("Origem da busca: %d\n",k+1);
    printf("Vertices alcancados e distancias:\n");

    //inicializamos a origem da busca, marcamos e a colocamos numa fila
    G->V[k].d = 0;
    G->V[k].mark = 1;
    insertlast(&L, k);

    //BFS
    while(L){
        u = L->queue;
        removefirst(&L);
        printf("%d %d\n", u+1, G->V[u].d);
        for(i = 0; i < n; i++){
            if(G->A[u][i]){
                if (! G->V[i].mark){
                    G->V[i].d = G->V[u].d + 1;
                    G->V[i].pi = u;
                    insertlast(&L, i);
                    G->V[i].mark = 1;  
                }                  
            }                
        }
    }

    return ;
}

/***  main  ***/
int main(){
    int i, j, n;
    graph* G = malloc(sizeof(graph));

    //numero de vertices do grafo
    scanf("%d",&n);

    //alocamos o grafo
    G->A = malloc(n*sizeof(int*));
    G->V = malloc(n*sizeof(vertex));
    for( i = 0; i < n; i++)
        G->A[i] = malloc(n*sizeof(int));

    //inicializamos a matriz de adjacencias com zeros
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++)
            G->A[i][j] = 0;
    }

    //inserimos as arestas na matriz
    scanf("%d,%d",&i,&j);
    while(j && i){
        G->A[i-1][j-1] = 1;
        G->A[j-1][i-1] = 1;
        scanf("%d,%d",&i,&j);
    }

    scanf("%d",&i);
    //chamamos bfs com origem em i
    bfs(G, n, i-1);

    //liberamos a memoria alocada
    for( i = 0; i < n; i++)
        free(G->A[i]);

    free(G->A);
    free(G->V);
    free(G);

    return 0;
}