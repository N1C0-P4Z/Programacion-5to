#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
        int caracter;
        int resultado[26];
        for(int i = 0;i<26;i++){
            resultado[i]=0;
    }
        while((caracter = fgetc (archivo)) != EOF){
            if(isalpha(caracter)){
                caracter = tolower(caracter);
                resultado[caracter - 'a']++;
            }
        }
        fclose(archivo);
        char nombreresult[100] = "resultado.";
        strcat(nombreresult, nombrearch);
        FILE* archivoresult = fopen(nombreresult, "w");
        if (archivoresult == NULL){
            printf("Error al abrir archivo resultado\n");
            return 1;
        }
        for (int i = 0; i < 26; i++) {
            fprintf(archivoresult, "%c: %d\n", 'a' + i, resultado[i]);
        }
        fclose(archivoresult);
        return 0;
}
