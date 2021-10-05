#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char key;
    struct node* left;
    struct node* right;
}node;

void make_tree( node** u, char* p, char* o);
void print_post_order( node* u);
void destroy_tree( node* u);

/******************main********************/
int main(){
    char p[52], o[52];
    node* T ;

    /*escaneamos as sequencias e chamamos as funcoes, resetando a raiz para NULL
    apos destruir a arvore*/
    while ( (scanf("%s %s", p, o)) != EOF){
        T = NULL;
        make_tree(&T, p, o);
        print_post_order(T);
        printf("\n");
        destroy_tree(T);
    }

    return 0;
}

/*funcao que imprime a arvore em pos ordem*/
void print_post_order( node* u){
    if( !u)
        return;

    print_post_order(u->left);
    print_post_order(u->right);
    printf("%c", u->key);
}

/*funcao que destroi a arvore*/
void destroy_tree( node* u){
    if( !u)
        return;
    
    destroy_tree(u->left);
    destroy_tree(u->right);
    free(u);
    
    return;
}

/*funcao que constroi a arvore*/
void make_tree( node** u, char* p, char* o){
    int n, i;
    char* aux1, *aux2, *root;

    /*criamos o no com a raiz da subarvore, primeiro char da pre ordem*/
    (*u) = malloc(sizeof(node));
    (*u)->key = p[0];
    (*u)->left = (*u)->right = NULL;

    /*encontramos o indice da raiz na sequencia em ordem*/
    n = strlen(p);
    root = strchr(o, p[0]);
    i = root - o;

    /*criamos duas auxiliares para dividir as sequencias
    e montar as subarvores a esquerda e direita */  
    aux1 = malloc((n-1)*sizeof(char));
    aux2 = malloc((n-1)*sizeof(char));

    /*se a sequencia tiver apenas um elemento, a raiz, retornamos*/
    if (n == 1)
        return;
    
    /*se nao tem subarvore a esquerda, montamos a direita com as 
    sequencias sem a raiz atual*/
    else if( !i)
        make_tree(&((*u)->right), p+1, o+1);

    /*se nao tem sub arvore a direita, montamos a esquerda com as
    sequencias sem a raiz atual*/
     else if (i == (n-1)){
        strncpy(aux1,o,n-1);
        make_tree(&((*u)->left), p+1, aux1);
    }

    /*se tem subarvore a esquerda e a direita, dividimos as sequencias
     com as auxiliares e montamos as subarvores esquerda e direita*/
    else {
        /*para copiar um pedaço central da sequencia na auxiliar
        temos que adicionar tambem o caracter nulo ao final*/
        strncpy(aux1, (p+1), i);
        strncpy(aux2, o, i);        
        aux1[i]='\0';
        aux2[i]='\0';
        make_tree(&((*u)->left), aux1, aux2);
        
        strcpy(aux1, (p+i+1));
        strcpy(aux2,(o+i+1));
        make_tree(&((*u)->right), aux1, aux2);
    }

    /*liberamos as auxiliares*/
    free(aux1);
    free(aux2);

    return;
}