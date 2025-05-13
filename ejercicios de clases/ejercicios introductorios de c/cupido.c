#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
    char nombre[30];
    char apellido[30];
    int edad;
    char localidad[30];
    int pareja; // 0 si no tiene pareja y 1 si tiene pareja
}persona;

int esCompatible(persona a, persona b);
void personasSolas(persona array[], int n);

int main()
{   
    int max_personas = 10;

    persona array[10] = {
        {"Juan", "Gomez", 18, "Rosario", 0},
        {"Maria", "Perez", 20, "Rosario", 0},
        {"Carlos", "Lopez", 25, "BuenosAires", 0},
        {"Lucia", "Fernandez", 22, "Rosario", 0},
        {"Diego", "Martinez", 15, "Rosario", 0},
        {"Sofia", "Gonzalez", 14, "Rosario", 0},
        {"Pedro", "Ramirez", 30, "BuenosAires", 0},
        {"Camila", "Diaz", 17, "Rosario", 0},
        {"Luis", "Fernandez", 19, "Rosario", 0},
        {"Ana", "Perez", 21, "Rosario", 0}
    };
    
    return 0;
}

int esCompatible(persona a, persona b)
{
    if(strcmp(a.localidad,b.localidad) != 0) return 0;
    if((a.edad < 16 && b.edad >= 16) || (b.edad < 16 && a.edad >= 16)) return 0;
    if((a.edad < 12) || (b.edad < 12)) return 0;
    if(strcmp(a.apellido,b.apellido) == 0) return 0;
    return 1;
}

//srand(time(NULL));
//int r = rand();
//preguntarle a la profe como hacer lo de la aleatoridad

void personasSolas(persona array[], int n)
{
    printf("LAs personas que se quedaron solas:\n");
    for(int i = 0; i < n; i++){
        if(array[i].pareja == 0){
            printf("%s %s\n", array[i].nombre, array[i].apellido);
        }
    }
}

//falta hacer el main fachero, la aleatoridad, y hacerlo para las 1000 personas dfiniendo una variable

