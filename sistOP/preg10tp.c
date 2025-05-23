#include <stdio.h>

int main(){
    char texto1[] = "Esta es una cadena de texto larga";
    char texto2[] = "Esta es una tambien es una cadena";
    char texto3[] = "Si, tambien esta linea es texto";

    char d = 'D';



    FILE* archivo = fopen("salida.txt", "w+");

    if (archivo == NULL){
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    fputc('A', archivo);
    fputc('B', archivo);
    fputc('C', archivo);
    fputc(d, archivo);
    fputc('\n', archivo);
    fputs(texto1, archivo);
    fputc('\n', archivo);
    fputs(texto2, archivo);
    fputc('\n', archivo);
    fputs(texto3, archivo);
    fputc('\n', archivo);

    fclose(archivo);
    return 0;
}
