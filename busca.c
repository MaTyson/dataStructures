#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "busca.h"

/*funcao que remove o primeiro elemento de uma fila
e ja o libera*/
void removefirst(list** head){
    list* p = *head;
    *head = (*head)->next;
    free(p);

    return ;
}

/*funcao que insere um elemento ao final da fila*/
void insertlast(list** head,  node* u){
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

/*funcao que imprime a arvore em ordem*/
void print_in_order(node* u) {

    if (!u)   
        return ;

    print_in_order(u->left);
    printf("%d ",u->key);
    print_in_order(u->right);

}

/*funcao que imprime a arvore em pre ordem*/
void print_pre_order(node* u) {

    if (!u)   
        return ;
    
    printf("%d ",u->key);
    print_pre_order(u->left);
    print_pre_order(u->right);

}

/*funcao que imprime a arvore em pos ordem*/
void print_post_order(node* u) {

    if (!u)   
        return ;
    
    print_post_order(u->left);
    print_post_order(u->right);
    printf("%d ",u->key);
    
}

/*funcao que imprime a arvore em largura
atraves de uma fila com os nos da arvore*/
void print_breadth(node* u){
    list* L = NULL;
    node* p;
    
    insertlast(&L, u);
    while(L){
        p = L->queue;
        removefirst(&L);
        printf("%d ", p->key);
        if(p->left)
            insertlast(&L, p->left);
        if(p->right)
            insertlast(&L, p->right);
    }

    return ;
}

/*funcao que insere um no na arvore*/
int insert(tree* T, int key){
    node* z = malloc(sizeof(node));
    if(!z){
        printf("memoria insuficiente\n");
        return 0;
    }

    node* u = T->root;
    node* p = NULL;

    z->key = key;
    z->right = z->left = z->parent = NULL;

    while(u){
        p = u;
        if(key == u->key)
            return 1;
        else if(key < u->key)
            u = u->left;
        else
            u = u->right;
    }

    if(p == NULL)
        T->root = z;
    else {
        if(key < p->key)
            p->left = z;
        else 
            p->right = z;
        
        z->parent = p;
    }

    return 1;
}

/*funcao que busca um no na arvore*/
void search(node* u, int key){
    node* p = u;

    while(p){
        if(key == p->key){
            printf("pertence\n");
            return ;
        }
        else if(key < p->key)
            p = p->left;
        else
            p = p->right;
    }

    printf("nao pertence\n");

    return ;
}

/*funcao que busca o maximo da arvore*/
int maximum(node* u){
    node*p = u;
    
    if(!p){
        printf("vazia\n");
        return 0;
    }

    while(p->right)
        p = p->right;
    printf("%d\n",p->key);

    return 1;
}

/*funcao que busca o minimo da arvore*/
int minimum(node* u){
    node*p = u;
    
    if(!p){
        printf("vazia\n");
        return 0;
    }

    while(p->left)
        p = p->left;
    printf("%d\n",p->key);

    return 1;
}

/*funcao que remove um no da arvore*/
void remove_t(tree* T, int key){
    node* p = T->root;
    node* q;

    while(p){
        if(key == p->key){
            if(!p->left)
                replace(T, p, p->right);
            else if(!p->right)
                replace(T, p, p->left);
            else{
                q = p->right;
                while(q->left)
                    q = q->left;
                if(q->parent != p){
                    replace(T,q,q->right);
                    q->right = p->right;
                    q->right->parent = q;
                }
                replace(T,p,q);
                q->left = p->left;
                q->left->parent = q;
            }
            free(p);
            p = NULL;
        }
        else if(key < p->key)
            p = p->left;
        else
            p = p->right;
    }

    return ;
}

/*funcao que troca a subarvore enraizada em u pela subarvore enraizada em v */
void replace(tree* T, node* u, node* v){
    if(!u->parent)
        T->root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else 
        u->parent->right = v;
    if(v)
        v->parent = u->parent;

    return ;
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