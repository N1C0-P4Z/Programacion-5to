#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int escanearBits(int lectura, int inicio, int final);
void imprimirBinario(int binary);
void masks(int inicio, int final);
int main(){
	unsigned int lectura = 0;
	printf("ingrese la lectura: ");
	scanf("%i", &lectura);

	imprimirBinario(lectura);
	if(lectura & 1<<31){
		printf("error");
		return 1;
	}
	if(lectura & 1<<30){

		printf("error");
		return 2;
	}
	if(lectura & 1<<29){
		printf("error");
		return 3;
	}
	int temperatura = escanearBits(lectura,0,8);
	int presionHepto = escanearBits(lectura, 15, 26);
	int presionAtm = escanearBits(lectura,8,15);
	// complemento a 2: 
	temperatura=temperatura<<24;
	temperatura = temperatura>>24;

	printf("temp: %i\n", temperatura);
	printf("presion relativa: %i\n", presionAtm);
	printf("presion en heptopascales: %i", presionHepto);

	return 0;
}
int escanearBits(int lectura, int inicio, int final){
	unsigned int mask = (int)(pow(2, (final - inicio))-1)<< inicio;
	
	int resultado = lectura&mask;
	return resultado>>inicio;
}
void imprimirBinario(int binary){
		for(unsigned int m=1<<31; m; m >>= 1) 
		printf("%i",(binary&m)/m);
		printf("\n");
}	
void masks(int inicio, int final){
	unsigned int mask = (int)(pow(2, (final - inicio))-1)<< inicio;
	imprimirBinario(mask);
	printf("\n");
}
