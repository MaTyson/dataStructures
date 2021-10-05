#include <stdio.h>
#include <string.h>

int main(){
	/*definimos as variaveis*/
	int numf, i, j, posi, posf, celebridade, count, fama;
	char lista[1000][200], nomei[1000][50], nomef[1000][50];
	char con[] = " conhece ", *acha, candidato[50];

	/* contamos o numero de frases enquanto as lemos e armazenamos em lista*/
	numf = 0;
	while(fgets(lista[numf], 200, stdin))
		numf++;

	/*encontramos a ocorrencia da palavra con - " conhece " - atraves do apontador *acha e da funcao 
	strstr para separarmos os nomes a esquerda de con em nomei e os a direita em nomef com strcpy*/	
	for(i = 0; i < numf; i++){
		acha = strstr(lista[i], con);
		/*posi e o indice da primeira posicao de con e posf o da ultima posicao de con*/
		posi = acha - lista[i];
		posf = acha - lista[i] + 9;
		strncpy(nomei[i], lista[i], posi);
		strcpy(nomef[i], (lista[i] + posf));
		/*removemos os \n que fgets colocou nos nomes da direita*/
		nomef[i][strlen(nomef[i])-1] = '\0';
	}

	/*inicializamos um vetor para indicar quem dos nomes da direita nao conhece ninguem
	1 se nao conhece, 0 caso contrario. A principio definimos todas as entradas como zero*/
	int ind[numf];
	for(i = 0; i < numf; i++)
		ind[i] = 0;	

	/*inicializamos o indicador celebridade que basicamente dita os rumos do programa, com ele
	descobrimos se alguem nao conhece ninguem, se tem mais de uma pessoa que nao conhece ninguem
	e ao final se todo mundo conhece a pessoa que nao conhece ninguem*/
	celebridade = 0;
	for(i = 0; i < numf; i++){
		celebridade = 1;
		j = 0;
		/*sempre que encontrarmos um nome na direita que esta na esquerda o indicador vale zero
		e partimos para o proximo nome*/
		while(celebridade && j < numf){
			if(strcmp(nomef[i], nomei[j]) == 0)
				celebridade = 0;
			j++;	
		}
		/*marcamos o indice do nome que nao conhece ninguem com 1 em ind[i]*/
		if(celebridade)
			ind[i] = 1;
	}

	/* definimos um candidato a celebridade, pois este nao conhece ninguem e
	entao testaremos se todos os outros o conhecem*/
	for(i = 0; i < numf; i++){
		if(ind[i]){
			strcpy(candidato, nomef[i]);
			celebridade = 1;
		}
	}

	/*mas antes conferimos se nao ha mais de uma pessoa que nao conhece ninguem, neste caso
	 e impossivel haver uma celebridade entao o indicador volta a valer 0*/
	for(i = 0; i < numf; i++){
		for(j = i+1; j < numf; j++){		
			if(ind[i] && ind[j] && strcmp(nomef[i], nomef[j]))
				celebridade = 0;	
		}
	}

	/*se apos isso celebridade ainda valer 1, testaremos se todos os nomes da direita
	conhecem o candidato*/
	if(celebridade){
		/*para isso definimos duas novas variaveis: count e fama, count contara as repeticoes
		 de nomes na direita e fama contara quantas pessoas conhecem o candidato*/
		count = 0;
		fama = 0;
		for(i = 0; i < numf; i++){
			for(j = i+1; j < numf; j++){
				/*contamos as repeticoes*/
				if(strcmp(nomei[i], nomei[j]) == 0){
					count ++;
					break;
				}
			}
		}
		/*retiramos do total de nomes o numero de repeticoes*/
		count = numf - count;	
		for(i = 0; i < numf; i++){
			/*contamos quem conhece o candidato da seguinte forma:
			se o nome da direita na linha do nome na esquerda for
			igual a candidato, somamos 1 em fama*/
			if(strcmp(nomef[i], candidato) == 0)
				fama ++;
		}
		/*aqui bastaria que fama fosse igual ao numero de nomes sem repeticao
		mas para garantir que nao havera mais de uma frase igual na entrada definimos 
		celebridade como zero apenas caso fama seja menor que o numero de nomes*/
		if(fama < count)
			celebridade = 0;
	}

	/*se ao final de tudo celebridade for 1, temos uma celebridade: o candidato
	caso contrario, nao ha' celebridade*/
	if( celebridade )
		printf("%s e' celebridade.\n", candidato);
	else
		printf("Nao ha' celebridade.\n");

	return 0;
}