#include <stdio.h>
#include <string.h>
int main (){
	char nombrearch[100];
	printf("ingrese nombre archivo: ");
	scanf("%s", nombrearch);
	getchar();
	FILE* archivo = fopen(nombrearch, "w");
	if (archivo == NULL){
	        printf("Error al abrir el archivo.\n");
       		 return 1;
	}
	char linea [100];
	while(1){
		printf("ingrese lineas: ");
		scanf("%[^\n]", linea);
		getchar();
		if(strcmp(linea, ":q") == 0){
			break;
		}
		fprintf(archivo, "%s\n", linea);
	}
	fclose(archivo);
}
