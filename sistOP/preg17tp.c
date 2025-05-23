#include <stdio.h>
#include <string.h>
int main(){
	char nombrearch[100];
	printf("ingrese nombre archivo: ");
	scanf("%s", nombrearch);
	getchar();
	FILE* archivo = fopen(nombrearch, "r");
	if (archivo == NULL){
	        printf("Error al abrir el archivo.\n");
       		 return 1;
	}
        char palabra[30];
        int contador= 0;
        while(fscanf(archivo, "%s", palabra) == 1){
            contador++;
        }
        fclose(archivo);
        printf("la cantidad de palbras es: %i", contador);
        return 0;
} 
