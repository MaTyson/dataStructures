#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "busca.h"

int main(){
    char comando[20];
    char* e;
    tree* T = malloc(sizeof(tree));

    if(!T)
        return 1;
    
    T->root = NULL;
    /*lemos os comandos e chamamos as funcoes*/
    fgets(comando,20,stdin);
    while( !strstr(comando,"terminar")){
        if(strstr(comando,"inserir")){
            e = strpbrk(comando, " ");
            insert(T, atoi(e + 1));
        }
        else if(strstr(comando,"excluir")){
            e = strpbrk(comando, " ");
            remove_t(T, atoi(e + 1));
        }

        else if(strstr(comando,"buscar")){
            e = strpbrk(comando, " ");
            search(T->root, atoi(e+1));
        }

        else if(strstr(comando,"minimo"))
            minimum(T->root);

        else if(strstr(comando,"maximo"))
            maximum(T->root);

        else if(strstr(comando,"pos-ordem")){
            if(!T->root)
                printf("vazia\n");
            else {
                print_post_order(T->root);
                printf("\n");
            }
        }

        else if(strstr(comando,"em-ordem")){
            if(!T->root)
                printf("vazia\n");
            else {
                print_in_order(T->root);
                printf("\n");
            }
        }

        else if(strstr(comando,"pre-ordem")){
            if(!T->root)
                printf("vazia\n");
            else {
                print_pre_order(T->root);
                printf("\n");
            }
        }

        else if(strstr(comando,"largura")){
            if(!T->root)
                printf("vazia\n");
            else {
                print_breadth(T->root);
                printf("\n");
            }
        }
        
        fgets(comando,20,stdin);
    }
    
    /*destruimos a arvore*/
    destroy_tree(T->root);
    free(T);

    return 0;
}