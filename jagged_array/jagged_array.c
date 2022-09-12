#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    /*inicializacao de variaveis*/
    int n, i, j, tot;
    double media, desvio;
    double** m;
    
    /*lemos o numero de linhas n e calculamos o total de elementos*/
    scanf("%d ",&n);
    tot = (n+1)*n/2;
    
    /*alocamos a matriz*/
    m = malloc(n * sizeof(double*));
    for(i = 0; i < n; i++)
        m[i] = malloc((i+1) * sizeof(double));
    
    /*lemos e armazenamos os elementos da matriz e calculamos a media*/
    media = 0;
    desvio = 0;
    for( i = 0; i < n; i++)
    {
        for( j = 0; j < i+1; j++)
        {
            scanf("%lf ",&m[i][j]);
            media += m[i][j];
        }  
    }
    media /= tot;
    
    /*calculamos o desvio*/
    for( i = 0; i < n; i++)
    {
        for( j = 0; j < i+1; j++)
        {
            desvio += pow(m[i][j] - media, 2);
        }  
    }
    desvio = sqrt(desvio/tot);
    
    /*normalizamos a matriz, calculando z e o armazenando diretamente na matriz m
    juntamente imprimimos a matriz normalizada e, em seguida, a media e o desvio*/
    for( i = 0; i < n; i++)
    {
        for( j = 0; j < i+1; j++)
        {
            m[i][j] = (m[i][j] - media)/desvio;
            printf("%.12lf ", m[i][j]);
        } 
        printf("\n"); 
    }
    printf("\n%.12lf %.12lf \n", media, desvio);
    
    /*liberamos a memoria alocada*/
    for(i = 0; i < n; i++)
        free(m[i]);
    free(m);

    return 0;
}