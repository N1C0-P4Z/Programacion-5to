#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int hexaADec(char hexa);
int elem(int n,char a, char array[n]);
void hexAAscii(char *hexa);
void imprimirBinario(char binary);
void asciiAHexa(char *ascii);
int main(){
	char hexa[10];
	printf("ingrese valor hexa: ");
	scanf("%s", hexa);
	hexAAscii(hexa);
	char ascii[10];
	printf("ingrese valor ascii: ");
	scanf("%s", ascii);
	asciiAHexa(ascii);
}

int hexaADec(char hexa){
	    if (hexa >= '0' && hexa <= '9') return hexa - '0';
	    hexa = tolower(hexa);
	    if (hexa >= 'a' && hexa <= 'f') return hexa - 'a' + 10;
	    return -1;
}
void hexAAscii(char *hexa){
       int i = 0;
	while(hexa[i] && hexa[i+1]){
		int right = hexaADec(hexa[i]);
		int left = hexaADec(hexa[i+1]);
		char result = (right << 4) | left;
		printf("%c", result);
		i += 2;
	}
	printf("\n");
}
char decAHexa(int num){
	if(num<10) return '0' + num;
	if(num>9 && num <16) return 'a' +num;
	return 'x';
}
void asciiAHexa(char *ascii){
	for(int i = 0; ascii[i]; i++){
		char prim = decAHexa(ascii[i]>>4);
		char sec = decAHexa(ascii[i] & 15);
		printf("%c%c", prim, sec);
	}
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
