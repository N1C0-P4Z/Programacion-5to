#include <stdio.h>

int main(){
	char nombrearch[30];
	char linea[100];
	printf("ingrese nombre archivo: ");
	scanf("%s", nombrearch);
	getchar();
	FILE* archivo = fopen(nombrearch, "r");
	if (archivo == NULL){
	        printf("Error al abrir el archivo.\n");
       		 return 1;
	}
 	for (; fscanf(archivo, "%[^\n]\n", linea) == 1; ) {
        	printf("%s\n", linea);
    	}
	fclose(archivo);
	return 0;
}
