#include <stdio.h>
#include <stdlib.h>

/*criamos o no, composto por uma union com cada tipo possivel de ser armazenado,
o no next que indica o proximo e um indicador tipo que nos diz o que esta armazenado*/
typedef struct node{
    int tipo;
    union 
    {
        int d;
        float f;
        char c;
        char s[130];
    };
    
    struct node *next;
}node;

/*funcao que insere um no ao final da lista de acordo com o caracter lido*/
int insert_end(node** head, char c){
    int i;
    node* p = *head;
    node* aux = malloc(sizeof(node));

    if (!aux)
        return 0;
    
    /*de acordo com o caracter lido, escaneamos o tipo correspondente*/
    if (c == 'd')
    {
        scanf(" %d ",&aux->d);
        aux->tipo = 1;
    }
    
	else if (c == 'f')
    {
        scanf(" %f ",&aux->f);
        aux->tipo = 2;
    }
    
    else if (c == 'c')
    {
        scanf(" %c ",&aux->c);
        aux->tipo = 3;
    }
    else if (c == 's')
    {   
        /*para ler a string, usamos getchar para capturar o espaço que a antecede
        e tiramos o \n adicionado pelo fgets*/
        getchar();
        fgets(aux->s,130,stdin);
        aux->tipo = 4;
        i = 0;
        while(aux->s[i] != '\n')
            i++;
        aux->s[i] = '\0';
    }
    
	aux->next = NULL;

	if (p == NULL) 
		*head = aux;
	else{
		while (p->next)
			p = p->next;

		p->next = aux;
	}

	return 1;
}

/*funcao que reverte a lista da posicao i ate a posicao f*/
void reverse (node** L, int i, int f){
    int j;
    node* in, *in_prev, *in_next, *aux, *aux2;
    in_prev = NULL;
    in = *L;
    
    /*encontramos o no i e seu antecessor*/
    for ( j = 0; j < i; j++)
    {
        in_prev = in;
        in = in->next;
    }
    in_next = in->next;
    /*consideramos dois casos para reverter: se o no i esta ou nao no comeco na lista */
    if( in_prev)
    {   
        /*para a reversao fazemos uso de duas auxiliares para armazenar o antecessor inicial
        e o no inicial*/
        aux = in_prev;
        aux2 = in;

        /*apos isso, andamos pelo trecho da lista invertendo cada um dos nos, i.e. fazendo in->next 
        apontar para in_prev a cada passo*/
        for( j = 0; j < (f - i + 1); j++ )
        {   
            in_next = in->next;
            in->next = in_prev;
            in_prev = in;
            in = in_next; 
        }
        /*por fim, fazemos o antecessor inicial apontar para o ultimo no do trecho, que agora
        e o primeiro, e fazemos o no inicial, que agora e o ultimo do trecho, apontar para
        in_next, que e o no apontado anteriormente pelo antigo ultimo no do trecho*/
        aux->next = in_prev;
        aux2->next = in_next;
    }
    /*se i esta no comeco da lista, utilizamos apenas uma auxiliar e alteramos tambem a cabeca*/
    else
    {   
        aux = in;
        /*a reversao e analoga a anterior, percorremos o trecho da lista invertendo os nos*/
        for( j = 0; j < (f - i + 1); j++ )
        {   
            in_next = in->next;
            in->next = in_prev;
            in_prev = in;
            in = in_next;         
        }
        /*a cabeca ira apontar para o novo inicio do trecho e o antigo inicio do trecho
        ira apontar para in_next*/
        *L = in_prev;
        aux->next = in_next;
    }
    return ;
}

/*funcao que transpoe a lista de i ate f para a posicao apos t*/
void transpose(node** L, int i, int f, int t){
    int j;
    node* in, *in_prev = NULL, * end, * troca, *aux = NULL;
    in = end = troca = *L;
    
    /*encontramos o no i e seu antecessor*/
    for ( j = 0; j < i; j++)
    {
        in_prev = in;
        in = in->next;
    }

    /*encontramos o no f*/
    for(j = 0; j < f; j++)
        end = end->next;
    
    /*consideramos dois casos para transpor: se o no i esta ou nao no comeco na lista */
    if( in_prev)
    {   
        /*se queremos transpor para o inicio da lista, alteramos a cabeca*/
        if(t == -1)
        {   
            /*prev->next vai apontar para onde f->next apontava, f->next vai apontar para o antigo 
            comeco da lista e L vai apontar para i, o novo comeco*/
            in_prev->next = end->next;
            end->next = *L ;
            *L = in; 
        }
        /*para transpor para algum ponto no meio da lista, utilizamos duas auxiliares:
        uma para encontrar a posicao t e outra para fazer a troca dos apontamentos dos next*/
        else
        {
            for(j = 0; j < t; j++)
                troca = troca->next;

            aux = troca->next;
            in_prev->next = end->next;
            troca->next = in;
            end->next = aux;    
        }
    }
    /*se o no i esta no comeco da lista e queremos transpor para o comeco, nada fazemos
    caso contrario, encontramos a posicao t na lista e transpomos com auxilio de aux, tambem
    alterando a cabeca da lista*/
    else
    {
        if(t != -1)
        {
            for(j = 0; j < t; j++)
                troca = troca->next;

            aux = troca->next;
            *L = end->next;
            troca->next = in;
            end->next = aux;    
        }
    }  

    return ;
}

/*funcao que imprime os elementos da lista*/
void print_data(node* L) {
    node* p = L;
    
    /*imprimimos de acordo com o tipo indicado */
    while (p) {
        if (p->tipo == 1)
            printf("%d ",p->d);
        else if (p->tipo == 2)
            printf("%.4f ",p->f);
        else if(p->tipo == 3)
            printf("%c ",p->c);
        else if(p->tipo == 4)
            printf("%s ", p->s);         
        
        p = p->next;
    }
    printf("\n");
}

/*funcao que libera os nos da lista*/
void free_list(node* L) {

  node* p = L;
  node* q = L;

  while (p) {
    q = p->next;
    free(p);
    p = q;
  }
  return;
}

int main(){
    char dado;
    int n, j, i, f, t;
    node* head = NULL;

    /*escaneamos o numero de nos da lista*/
    scanf("%d ",&n);
    for ( j = 0; j < n; j++)
    {   
        /*lemos o caracter e chamamos a funcao inserir*/
        dado = getchar();
        insert_end(&head,dado);
    }

    /*imprimimos a lista*/
    print_data(head);

    /*escaneamos o numero de comandos de reverter/transpor*/
    scanf("%d ",&n);
    for ( j = 0; j < n; j++)
    {
        /*lemos o caracter e aplicamos a respectiva funcao
        imprimindo a lista logo em seguida*/
        dado = getchar();
        if (dado == 'r')
        {
            scanf(" %d %d ", &i, &f);
            reverse(&head, i, f);
            print_data(head);
        }
        else if(dado == 't')
        {
            scanf(" %d %d %d ", &i, &f, &t);
            transpose(&head, i, f, t);
            print_data(head);
        }
    }

    /*liberamos os nos da lista*/
    free_list(head);

    return 0;
}