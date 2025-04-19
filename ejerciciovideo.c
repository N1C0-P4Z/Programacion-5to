#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de alumno
typedef struct {
    char nombre[50];
    char apellido[50];
    int dni;
    int edad;
    int notas[3];
    float promedio;
} Alumno;

// Prototipos de las funciones
void agregarAlumnos(Alumno array[], int cantidad);
void mostrarTodos(Alumno array[], int cantidad);
void buscarPorDNI(Alumno array[], int cantidad, int dni);
void modificarAlumno(Alumno alumnos[], int cantidad, int dni);
int eliminarAlumno(Alumno alumnos[], int cantidad, int dni);

float calcularPromedio(int notas[]);


int main(void) 
{
    int cantidad_estudiantes;
    int dni, opcion;

    printf("¿Cuántos alumnos desea agregar? ");
    scanf("%d", &cantidad_estudiantes);

    Alumno array[cantidad_estudiantes];

    
    do {
        printf("\n--- MENU ---\n");
        printf("1. Agregar alumnos\n");
        printf("2. Buscar alumno por DNI\n");
        printf("3. Modificar alumno\n");
        printf("4. Eliminar alumno\n");
        printf("5. Mostrar todos los alumnos\n");
        printf("6. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                agregarAlumnos(array, cantidad_estudiantes);
                break;
            case 2:
                printf("Ingrese el DNI a buscar: ");
                scanf("%d", &dni);
                buscarPorDNI(array, cantidad_estudiantes, dni);
                break;
            case 3:
                printf("Ingrese el DNI a modificar: ");
                scanf("%d", &dni);
                modificarAlumno(array, cantidad_estudiantes, dni);
                break;
            case 4:
                printf("Ingrese el DNI a eliminar: ");
                scanf("%d", &dni);
                cantidad_estudiantes = eliminarAlumno(array, cantidad_estudiantes, dni);
                break;
            case 5:
                mostrarTodos(array, cantidad_estudiantes);
                break;
            case 6:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción inválida.\n");
        }

    } while(opcion != 6);

    return 0;
}

// Definición de las funciones

float calcularPromedio(int notas[]) {
    return (notas[0] + notas[1] + notas[2]) / 3.0;
}


void agregarAlumnos(Alumno alumnos[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        printf("\nAlumno #%d\n", i + 1);
        printf("Nombre: ");
        scanf("%s", alumnos[i].nombre);
        printf("Apellido: ");
        scanf("%s", alumnos[i].apellido);
        printf("DNI: ");
        scanf("%d", &alumnos[i].dni);
        printf("Edad: ");
        scanf("%d", &alumnos[i].edad);

        for (int j = 0; j < 3; j++) {
            printf("Nota %d: ", j + 1);
            scanf("%d", &alumnos[i].notas[j]);
        }

        alumnos[i].promedio = calcularPromedio(alumnos[i].notas);
    }
}

void mostrarTodos(Alumno alumnos[], int cantidad) 
{
    for (int i = 0; i < cantidad; i++) {
        printf("\nAlumno #%d\n", i + 1);
        printf("Nombre: %s\n", alumnos[i].nombre);
        printf("Apellido: %s\n", alumnos[i].apellido);
        printf("DNI: %d\n", alumnos[i].dni);
        printf("Edad: %d\n", alumnos[i].edad);
        printf("Notas: %d, %d, %d\n", alumnos[i].notas[0], alumnos[i].notas[1], alumnos[i].notas[2]);
        printf("Promedio: %.2f\n", alumnos[i].promedio);
    }
}

void buscarPorDNI(Alumno alumnos[], int cantidad, int dni) {
    int encontrado = 0;
    for (int i = 0; i < cantidad; i++) {
        if (alumnos[i].dni == dni) {
            printf("\nAlumno encontrado:\n");
            printf("Nombre: %s\n", alumnos[i].nombre);
            printf("Apellido: %s\n", alumnos[i].apellido);
            printf("Edad: %d\n", alumnos[i].edad);
            printf("DNI: %d\n", alumnos[i].dni);
            printf("Notas: %d, %d, %d\n", alumnos[i].notas[0], alumnos[i].notas[1], alumnos[i].notas[2]);
            printf("Promedio: %.2f\n", alumnos[i].promedio);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("Alumno no encontrado.\n");
    }
}

void modificarAlumno(Alumno alumnos[], int cantidad, int dni) {
    int encontrado = 0;
    for (int i = 0; i < cantidad; i++) {
        if (alumnos[i].dni == dni) {
            printf("Modificar datos del alumno:\n");
            printf("Nuevo nombre: ");
            scanf("%s", alumnos[i].nombre);
            printf("Nuevo apellido: ");
            scanf("%s", alumnos[i].apellido);
            printf("Nueva edad: ");
            scanf("%d", &alumnos[i].edad);

            for (int j = 0; j < 3; j++) {
                printf("Nueva nota %d: ", j + 1);
                scanf("%d", &alumnos[i].notas[j]);
            }

            alumnos[i].promedio = calcularPromedio(alumnos[i].notas);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Alumno no encontrado.\n");
    }
}

int eliminarAlumno(Alumno alumnos[], int cantidad, int dni) {
    int encontrado = 0;
    for (int i = 0; i < cantidad; i++) {
        if (alumnos[i].dni == dni) {
            for (int j = i; j < cantidad - 1; j++) {
                alumnos[j] = alumnos[j + 1];
            }
            cantidad--;
            printf("Alumno eliminado.\n");
            encontrado = 1;
            break; 
        }
    }
    if (!encontrado) {
        printf("Alumno no encontrado.\n");
    }
    return cantidad;
}

