#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int key;
	int count;
	struct node* next;
}node;

node* create(int N);

int get_move_to_front_cost(int* comando, int t, int n);

int get_transpose_cost(int* comando, int t, int n);

int get_count_cost(int* comando, int t, int n);

int insert_end(node** head, int data);

void free_list(node* head);

int main(){
	/*declaramos variaveis*/
	int N, R, i, *comando;
	int custo_mtf, custo_tr, custo_c;

	/*lemos N e R*/
	scanf("%d",&N);
	scanf("%d",&R);

	/*criamos um vetor para armazenar os comandos*/
	comando = malloc(R*sizeof(int));
	/*inicializamos os custos como zero*/
	custo_mtf = custo_tr = custo_c = 0;
	
	/*lemos os comandos e armazenamos no vetor*/
	for(i = 0; i < R; i++)
		scanf("%d ",&comando[i]);

	/*chamamos as funcoes que calculam os custos*/
	custo_mtf += get_move_to_front_cost(comando, R, N);
	custo_tr += get_transpose_cost(comando, R, N);
	custo_c += get_count_cost(comando, R, N);
	
	/*impressao dos custos*/
	printf("%d %d %d\n", custo_mtf, custo_tr, custo_c);

	/*liberamos o vetor dos comandos*/
	free(comando);
	
	return 0;
}

/*funcao que cria uma lista com N nos e chaves de 1 a N*/
node* create(int N){
	node* head = NULL;
	int i;

	for(i = 1; i<=N; i++)
		insert_end(&head, i);

	return head;
}

/*funcao que calcula o custo de move to front*/
int get_move_to_front_cost(int* comando, int t, int n){
	node* head, *prev, *next;
	int i, custo = 0;
	/*criamos a lista*/
	head = create(n);

	/*para cada elemento em comando executamos o algoritmo
	move to front e aumentamos o custo em 1 a cada acesso na lista*/
	for(i = 0; i < t; i++){
		prev = NULL;
		next = head;
		/*caso o comando corresponda ao primeiro elemento da lista
		apenas atualizamos o custo em 1*/
		if(next->key == comando[i])
			custo ++;
		/*caso contrario, procuramos pela lista o no cuja key corresponde ao comando
		e o movimentamos para o inicio da lista atualizando o custo*/
		else{
			while(next->key != comando[i]){
				custo ++;
				prev = next;
				next = next->next;
			}
			custo++;
			prev->next = next->next;
			next->next = head;
			head = next;
		}
	}
	/*liberamos a lista criada*/
	free_list(head);

	return custo;
}

/*funcao que calcula o custo de transpose*/
int get_transpose_cost(int* comando, int t, int n){
	/*criamos 3 apontadores auxiliares para fazer a troca dos adjacentes*/
	node* prev, *curr, *next, *head;
	int i, custo = 0;
	/*criamos a lista*/
	head = create(n);

	for( i = 0; i < t; i++){	
		prev = NULL;
		curr = NULL;
		next = head;
		/*caso o comando corresponda ao primeiro no da lista 
		apenas atualizamos o custo em 1*/
		if(next->key == comando[i])
			custo ++;
		else{	
			while(next->key != comando[i]){
				custo ++;
				prev = curr;
				curr = next;
				next = next->next;
			}
			custo++;
			/*caso o comando corresponda ao segundo no da lista
			trocamos os nos e atualizamos a cabeca*/
			if(prev == NULL){
				curr->next = next->next;
				next->next = curr;
				head = next;
			}
			/*caso seja um no central, apenas trocamos os adjacentes*/
			else{
				prev->next = next;
				curr->next = next->next;
				next->next = curr;
			}
		}	
	}
	/*liberamos a lista*/
	free_list(head);

	return custo;
}

/*funcao que calcula custo de count*/
int get_count_cost(int* comando, int t, int n){
	/*alem dos 2 apontadores para trocar os nos de posicao, precisamos de 
	mais 2 apontadores para descobrir em que posicao o no sera inserido*/
	int i, custo = 0;
	node* head, *curr, *next, *troca, *troca_prev;
	/*criamos a lista*/
	head = create(n);

	for ( i = 0; i < t; i++){	
		curr = NULL;
		troca_prev = NULL;
		next = head;
		troca = head;
		/*caso o comando corresponda ao primeiro no da lista apenas
		atualizamos o custo e o contador em 1*/
		if (next->key == comando[i]){
			custo ++;
			next->count++;
		}
		else{
			while (next->key != comando[i]){
				custo++;
				curr = next;
				next = next->next;
			}
			/*ao encontrar o no do comando, alem de ir atualizando o custo,
			atualizamos seu contador*/
			custo ++;
			next->count ++;
			/*procuramos o primeiro no cujo contador e menor ou igual ao contador 
			do no que desejamos mudar de posicao*/
			while (next->count < troca->count){
				troca_prev = troca;
				troca = troca->next;
			}
			/*se nao houver no que satisfaca isso alem do que desejamos mudar, nada faremos
			caso contrario, trocamos sua posicao para frente do no encontrado*/
			if (next != troca){
				curr->next = next->next;
				next->next = troca;
				/*caso o no encontrado seja o primeiro da lista, atualizamos a cabeca tambem*/
				if (troca_prev == NULL)
					head = next;
				else
					troca_prev->next = next;
			}
		}
	}
	/*liberamos a lista*/
	free_list(head);

	return custo;
}

/*funcao que insere um no ao final da lista*/
int insert_end(node** head, int data){
	node* p = *head;
	node* aux = malloc(sizeof(node));
	
	if (!aux)
  		return 0;
	/*inserimos data em key do no criado e inicializamos count com zero*/
	aux->key = data;
	aux->count = 0;
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

/*funcao que libera os nos da lista*/
void free_list(node* head) {
	node* p = head;
	node* q = head;

	while (p){
		q = q->next;
		free(p);
		p = q;
  	}

  	return ;
}