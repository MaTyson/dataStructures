#include<stdio.h>

int main(){
	int i=32;
	printf("      +0 +1 +2 +3 +4 +5 +6 +7 \n");
	printf("    +------------------------ \n");
	printf("%3d |  ",i);
	for(i=32;i<=126;i++){
		printf("%c  ",i);
		if((i+1)%8==0){
			printf("\n");
			printf("%3d |  ",(i+1));
		}
	}
	printf("  \n");
	return 0;
}
