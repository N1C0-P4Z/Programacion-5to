#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUMNOS 100

typedef struct {
    char nombre[50];
    char apellido[50];
    int dni;
    int edad;
    int notas[3];
    float promedio;
} Alumno;

Alumno alumnos[MAX_ALUMNOS];
int cantidadAlumnos = 0;

// Calcular promedio
float calcularPromedio(int notas[]) {
    return (notas[0] + notas[1] + notas[2]) / 3.0;
}

// Agregar alumnos
void agregarAlumnos(int n) {
    int i;
    for (i = 0; i < n && cantidadAlumnos < MAX_ALUMNOS; i++) {
        printf("\nAlumno #%d\n", cantidadAlumnos + 1);
        printf("Nombre: ");
        scanf("%s", alumnos[cantidadAlumnos].nombre);
        printf("Apellido: ");
        scanf("%s", alumnos[cantidadAlumnos].apellido);
        printf("DNI: ");
        scanf("%d", &alumnos[cantidadAlumnos].dni);
        printf("Edad: ");
        scanf("%d", &alumnos[cantidadAlumnos].edad);
        
        for (int j = 0; j < 3; j++) {
            printf("Nota %d: ", j + 1);
            scanf("%d", &alumnos[cantidadAlumnos].notas[j]);
        }

        alumnos[cantidadAlumnos].promedio = calcularPromedio(alumnos[cantidadAlumnos].notas);
        cantidadAlumnos++;
    }
}

// Buscar por DNI
void buscarPorDNI(int dni) {
    int encontrado = 0;
    for (int i = 0; i < cantidadAlumnos; i++) {
        if (alumnos[i].dni == dni) {
            printf("\nAlumno encontrado:\n");
            printf("Nombre: %s\n", alumnos[i].nombre);
            printf("Apellido: %s\n", alumnos[i].apellido);
            printf("Edad: %d\n", alumnos[i].edad);
            printf("DNI: %d\n", alumnos[i].dni);
            printf("Notas: %d, %d, %d\n", alumnos[i].notas[0], alumnos[i].notas[1], alumnos[i].notas[2]);
            printf("Promedio: %.2f\n", alumnos[i].promedio);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Alumno no encontrado.\n");
    }
}

// Modificar alumno
void modificarAlumno(int dni) {
    int encontrado = 0;
    for (int i = 0; i < cantidadAlumnos; i++) {
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

// Eliminar alumno
void eliminarAlumno(int dni) {
    int encontrado = 0;
    for (int i = 0; i < cantidadAlumnos; i++) {
        if (alumnos[i].dni == dni) {
            for (int j = i; j < cantidadAlumnos - 1; j++) {
                alumnos[j] = alumnos[j + 1];
            }
            cantidadAlumnos--;
            printf("Alumno eliminado.\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Alumno no encontrado.\n");
    }
}

// Mostrar todos
void mostrarTodos() {
    if (cantidadAlumnos == 0) {
        printf("No hay alumnos cargados.\n");
    } else {
        for (int i = 0; i < cantidadAlumnos; i++) {
            printf("\nAlumno #%d\n", i + 1);
            printf("Nombre: %s\n", alumnos[i].nombre);
            printf("Apellido: %s\n", alumnos[i].apellido);
            printf("DNI: %d\n", alumnos[i].dni);
            printf("Edad: %d\n", alumnos[i].edad);
            printf("Notas: %d, %d, %d\n", alumnos[i].notas[0], alumnos[i].notas[1], alumnos[i].notas[2]);
            printf("Promedio: %.2f\n", alumnos[i].promedio);
        }
    }
}

// Menú principal
int main() {
    int opcion, dni, cantidad;

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
                printf("¿Cuántos alumnos desea agregar? ");
                scanf("%d", &cantidad);
                agregarAlumnos(cantidad);
                break;
            case 2:
                printf("Ingrese el DNI a buscar: ");
                scanf("%d", &dni);
                buscarPorDNI(dni);
                break;
            case 3:
                printf("Ingrese el DNI a modificar: ");
                scanf("%d", &dni);
                modificarAlumno(dni);
                break;
            case 4:
                printf("Ingrese el DNI a eliminar: ");
                scanf("%d", &dni);
                eliminarAlumno(dni);
                break;
            case 5:
                mostrarTodos();
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
