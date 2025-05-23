#include <stdio.h>

int main(){
    char texto1[] = "Esta es una cadena de texto larga";
    char texto2[] = "Esta es una tambien es una cadena";
    char texto3[] = "Si, tambien esta linea es texto";

    FILE* archivo = fopen("salida.txt", "w+");

    if (archivo == NULL){
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    fprintf(archivo, "Puedo usarlo como printf: %d", 2003);
    fprintf(archivo, "Ojo con los saltos de linea\n");
    fprintf(archivo,"%s\n", texto1);
    fprintf(archivo,"%s\n", texto2);
    fprintf(archivo,"%s\n", texto3);

    fclose(archivo);
    return 0;
} 
