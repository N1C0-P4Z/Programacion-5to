#include <stdio.h>
#include <stdlib.h>
char hexaABinario(char hexa[2]);
int elem(int n,char a, char array[n]);
void imprimirBinario(char binary);
int main(){
	char hexa[10];
	printf("ingrese valor hexa: ");
	scanf("%s", hexa);
	printf("hexa: %s\n", hexa);
	for(int i = 0; i<10; i+=2){
		char doshexa[2] = {hexa[i], hexa[i]};
		printf("doshexa: %i, i: %i, i++ %i, ++i %i, char: %c\n",doshexa, i, i++, ++i, hexaABinario(doshexa));
	}
}
char hexaABinario(char hexa[2]){
	char resultado;
	for(int i = 0; i<2;i++){
		if(elem(10, hexa[i], "0123456789")){
			hexa[i] -= 48;
		}else if(elem(6, hexa[i], "abcdef")){
			hexa[i] -= 87;
		}else{
			hexa[i] -= 55;
		}	
	}
	resultado = hexa[0]<<4;
	resultado |= hexa[1];
	return resultado;
}
void imprimirBinario(char binary){
		for(unsigned int m=1<<7; m; m >>= 1) 
		printf("%i",(binary&m)/m);
		printf("\n");
}

int elem(int n, char a, char array[n]){
	for(int i = 0; i<n;i++){
		if(a == array[i]){
			return 1;
		}
	}
	return 0;
}
