#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    double data;
    struct node* A;
    struct node* B;
}node;

typedef struct list{
    int count;
    node* head;
}list;

/*funcao que insere um no na lista na posicao in*/
void insert(list** L, double data, int in){
    node* p = (*L)->head;
    node* prev = NULL;
    node* aux = malloc(sizeof(node));
    int j;
    if(!aux)
        return;
    
    aux->data = data;
    aux->A = NULL;
    aux->B = NULL;
    /*se a lista esta vazia, apenas inserimos*/
    if (!p)
        (*L)->head = aux;
    else {
        /*se o indice for maior que o numero de elementos na lista, inserimos no fim*/
        if (in >= (*L)->count ) {
            /*se a lista possui apenas um elemento, inserimos logo apos a cabeca*/
            if (!p->A && !p->B){
                p->B = aux;
                aux->A = p;
            }
            else{
                /*caso contrario, andamos na lista ate o final e inserimos*/
                while(p){
                    if(!p->A && !prev){
                        prev = p;
                        p = p->B;
                    }
                    else if(!p->B && !prev){
                        prev = p;
                        p = p->A;
                    }
                    else if(p->A == prev){
                        prev = p;
                        p = p->B;
                    }
                    else if(p->B == prev){
                        prev = p;
                        p = p->A;
                    }
                }
                aux->A = prev;
                if(!prev->B)
                    prev->B = aux;
                else
                    prev->A = aux;
            }
        }    
        /*se o indice for menor que o numero de elementos, procuramos a posicao in*/
        else {
            /*se in for 0, o inicio da lista, inserimos ao inicio*/
            if (!in){
                aux->B = (*L)->head;
                if(!(*L)->head->A )
                    (*L)->head->A = aux;
                else {
                    (*L)->head->B = aux;
                }
                (*L)->head = aux;
            }
            /*caso contrario, andamos pela lista ate a posicao in*/
            else{
                for( j = 0; j < in; j++){
                    if(!p->A && !prev){
                        prev = p;
                        p = p->B;
                    }
                    else if(!p->B && !prev){
                        prev = p;
                        p = p->A;
                    }
                    else if(p->A == prev){
                        prev = p;
                        p = p->B;
                    }
                    else if(p->B == prev){
                        prev = p;
                        p = p->A;
                    }
                }
                /*e inserimos, fazendo as devidas atualizacoes*/
                aux->A = prev;
                aux->B = p;
                if (prev->A == p)
                    prev->A = aux;
                else if (prev->B == p)
                    prev->B = aux;
                if (p->A == prev)
                    p->A = aux;
                else if (p->B == prev)
                    p->B = aux;
            } 
        }
    }
    /*atualizamos o numero de elementos na lista*/
    (*L)->count += 1;
    return;
}

/*funcao que reverte as posicoes in e fn da lista*/
void reverse(node** L, int in, int fn, int q){
    int i;
    node* ini, *fini, *prev1 = NULL, *prev2 = NULL;
    ini = *L;
    fini = *L;
    /*procuramos o no na posicao in*/
    for (i = 0; i < in; i++){
        if(!ini->A && !prev1){
            prev1 = ini;
            ini = ini->B;
        }
        else if(!ini->B && !prev1){
            prev1 = ini;
            ini = ini->A;
        }
        else if(ini->A == prev1){
            prev1 = ini;
            ini = ini->B;
        }
        else if(ini->B == prev1){
            prev1 = ini;
            ini = ini->A;
        }
    }
    /*procuramos o no na posicao fn*/
    for (i = 0; i < fn; i++){
        if(!fini->A && !prev2){
            prev2 = fini;
            fini = fini->B;
        }
        else if(!fini->B && !prev2){
            prev2 = fini;
            fini = fini->A;
        }
        else if(fini->A == prev2){
            prev2 = fini;
            fini = fini->B;
        }
        else if(fini->B == prev2){
            prev2 = fini;
            fini = fini->A;
        }
    }
    /*se a reversao for de apenas um no, nada fazemos*/
    if (in != fn){
        /*se queremos reverter o inicio da lista, atualizamos a cabeca*/
        if(!in){
            /*checamos se queremos reverter o inicio com o fim*/
            if(fn == (q-1)){
                if(prev1 == ini->A){
                    if (prev2 == fini->A) {
                        ini->A = fini->B;
                        fini->B = prev1;
                        *L = fini;
                    }
                
                    else {
                        ini->A = fini->A;
                        fini->A = prev1;
                        *L = fini;
                    }
                }
                else {
                    if (prev2 == fini->A) {
                        ini->B = fini->B;
                        fini->B = prev1;
                        *L = fini;
                    }
                    else {
                        ini->B = fini->A;
                        fini->A = prev1;
                        *L = fini;
                    }
                }
            }
            /*caso contrario, precisamos atualizar o no seguinte a fn tambem*/
            else{
                if(prev1 == ini->A){
                    if (prev2 == fini->A) {
                        ini->A = fini->B;
                        if((fini->B)->A == fini)
                            (fini->B)->A = ini;
                        else 
                            (fini->B)->B = ini;
                        fini->B = prev1;
                        *L = fini;
                    }
                
                    else {
                        ini->A = fini->A;
                        if((fini->A)->A == fini)
                            (fini->A)->A = ini;
                        else if((fini->A)->B == fini)
                            (fini->A)->B = ini;
                        fini->A = prev1;
                        *L = fini;
                    }
                }
                else {
                    if (prev2 == fini->A) {
                        ini->B = fini->B;
                        if((fini->B)->A == fini)
                            (fini->B)->A = ini;
                        else if((fini->B)->B == fini)
                            (fini->B)->B = ini;
                        fini->B = prev1;
                        *L = fini;
                    }
                    else {
                        ini->B = fini->A;
                        if((fini->A)->A == fini)
                            (fini->A)->A = ini;
                        else if((fini->A)->B == fini)
                            (fini->A)->B = ini;
                        fini->A = prev1;
                        *L = fini;
                    }
                }
            }
        }
        /*se nao for o inicio, nao mexemos na cabeca, mas mexemos no no anterior a ini*/
        else {
            /*novamente checamos se fn e o fim da lista para nao ter que atualizar
            o no seguinte a fini*/
            if(fn == (q-1)){
                if(prev1 == ini->A){
                    if (prev2 == fini->A) {
                        ini->A = fini->B;
                        fini->B = prev1;
                        if(prev1->A == ini)
                            prev1->A = fini;
                        else 
                            prev1->B = fini;                        
                    }
                    else { 
                        ini->A = fini->A;
                        fini->A = prev1;
                        if(prev1->A == ini)
                            prev1->A = fini;
                        else 
                            prev1->B = fini;
                    }
                }
                
                else {
                    if (prev2 == fini->A) {
                        ini->B = fini->B;
                        fini->B = prev1;
                        if(prev1->A == ini)
                            prev1->A = fini;
                        else 
                            prev1->B = fini;
                        
                    }
                    else {
                        ini->B = fini->A;
                        fini->A = prev1;
                        if(prev1->A == ini)
                            prev1->A = fini;
                        else 
                            prev1->B = fini;
                    }
                }    
            }
            /*caso nao seja o fim da lista, teremos que atualizar o no seguinte a fini tambem */
            else{
                if(prev1 == ini->A){
                    if (prev2 == fini->A) {
                        ini->A = fini->B;
                        if((fini->B)->A == fini)
                            (fini->B)->A = ini;
                        else if((fini->B)->B == fini)
                            (fini->B)->B = ini;
                        fini->B = prev1;
                        if(prev1->A == ini)
                            prev1->A = fini;
                        else 
                            prev1->B = fini;
                        
                    }
                    else { 
                        ini->A = fini->A;
                        if((fini->A)->A == fini)
                            (fini->A)->A = ini;
                        else if((fini->A)->B == fini)
                            (fini->A)->B = ini;
                        fini->A = prev1;
                        if(prev1->A == ini)
                            prev1->A = fini;
                        else 
                            prev1->B = fini;
                    }
                }
                else {
                    if (prev2 == fini->A) {
                        ini->B = fini->B;
                        if((fini->B)->A == fini)
                            (fini->B)->A = ini;
                        else if((fini->B)->B == fini)
                            (fini->B)->B = ini;
                        fini->B = prev1;
                        if(prev1->A == ini)
                            prev1->A = fini;
                        else 
                            prev1->B = fini;
                        
                    }
                    else {
                        ini->B = fini->A;
                        if((fini->A)->A == fini)
                            (fini->A)->A = ini;
                        else if((fini->A)->B == fini)
                            (fini->A)->B = ini;
                        fini->A = prev1;
                        if(prev1->A == ini)
                            prev1->A = fini;
                        else 
                            prev1->B = fini;
                    }
                }
            }
        }
    }

    return ;
}

/*funcao que imprime a lista*/
void print_data(node* L){
    node* p = L;
    node* prev = NULL;

    if(p){
        if (!p->A && !p->B)
            printf("%.4lf ",p->data);
        else {
            while(p){
                printf("%.4lf ",p->data);
                if(!p->A && !prev){
                    prev = p;
                    p = p->B;
                }
                else if(!p->B && !prev){
                    prev = p;
                    p = p->A;
                }
                else if(p->A == prev){
                    prev = p;
                    p = p->B;
                }
                else if(p->B == prev){
                    prev = p;
                    p = p->A;
                }
            }
        }
    }
    printf("\n");
    return;
}

/*funcao que libera a lista*/
void free_list(node* L){
    node* p, *prev = NULL;
    p = L;
    while(p){
        if(!p->A && !prev){
            prev = p;
            p = p->B;
            free(prev);
        }
        else if(!p->B && !prev){
            prev = p;
            p = p->A;
            free(prev);
        }
        else if(p->A == prev){
            prev = p;
            p = p->B;
            free(prev);
        }
        else if(p->B == prev){
            prev = p;
            p = p->A;
            free(prev);
        }
    }

    return;
}

/************main***************/
int main(){
    char c;
    double data;
    int i, f;
    list* list;
    /*inicializamos a lista*/
    list = malloc(sizeof(list));
    list -> count = 0;
    list -> head = NULL;
    /*lemos os comandos com getchar e chamamos as respectivas funcoes*/
    while((c = getchar())!= 't' && c != EOF){
        if (c == 'i') {
            scanf(" %d %lf ", &i, &data);
            insert(&list, data, i);
        }
        else if (c == 'p'){
            print_data(list->head);
        }
        else if(c == 'v'){
            scanf(" %d %d ", &i, &f);
            reverse(&(list->head), i, f, list->count);
        }
    }
    /*liberamos a memoria alocada*/
    free_list(list->head);
    free(list);

    return 0;
}
