#include "estrategia.h"
#include "nivel.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

static int posiciones_validas(Coordenada *validas, TipoCasilla **casillas, int alto, int ancho) {
    int cant_posiciones_validas = 0;
    
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            if (casillas[i][j] == VACIO) {
                validas[cant_posiciones_validas].x = i;
                validas[cant_posiciones_validas++].y = j;
            }
        }
    }

    return cant_posiciones_validas;
}

static void colocar_torre(Mapa *mapa, int x, int y, int nro_torre) {
    // actualizar torre
    mapa->torres[nro_torre].x = x;
    mapa->torres[nro_torre].y = y;

    // actualizar mapa
    mapa->casillas[x][y] = TORRE;
}

static int determinar_posicion_torre(int *casilla_elegida, int cant_validas) {
    int nueva_posicion = rand() % cant_validas;
    while(casilla_elegida[nueva_posicion])
        nueva_posicion = rand() % cant_validas;

    return nueva_posicion;
}


void disponer(Nivel* nivel, Mapa* mapa) {
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];
    int casilla_elegida[cantidad_casillas];
    for(int i = 0; i < cantidad_casillas; casilla_elegida[i++] = 0);

    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);

    for (int colocadas = 0; colocadas < mapa->cant_torres; colocadas++) {
        int nueva_torre = determinar_posicion_torre(casilla_elegida, cant_validas);
        casilla_elegida[nueva_torre] = 1;
        int nueva_torre_x = posiciones_validas_torre[nueva_torre].x;
        int nueva_torre_y = posiciones_validas_torre[nueva_torre].y;
        colocar_torre(mapa, nueva_torre_x, nueva_torre_y, colocadas);
    }
}

void disponer_con_backtracking(Nivel* nivel, Mapa* mapa) {
    /* A cargo de la/el estudiante */
    return;
}

void disponer_custom(Nivel* nivel, Mapa* mapa) {
    /* A cargo de la/el estudiante */
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];

    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);

    for (int i = 0; i< cant_validas-1;i++){
        for (int j = 0;j<cant_validas-i-1; j++){
            if(calidad_torre(nivel, mapa, posiciones_validas_torre[j]) < calidad_torre(nivel, mapa, posiciones_validas_torre[j+1])){
                //swap
                Coordenada aux = posiciones_validas_torre[j];
                posiciones_validas_torre[j] = posiciones_validas_torre[j+1];
                posiciones_validas_torre[j+1] = aux;
            }
        }
    }
    for(int i = 0; i<cant_validas; i++){
        printf("%i, ", calidad_torre(nivel, mapa, posiciones_validas_torre[i]));
        }
    for (int colocadas = 0; colocadas < mapa->cant_torres; colocadas++) {
        int nueva_torre_x = posiciones_validas_torre[colocadas].x;
        int nueva_torre_y = posiciones_validas_torre[colocadas].y;
        colocar_torre(mapa, nueva_torre_x, nueva_torre_y, colocadas);
    }
    return;
}

int calidad_torre(Nivel* nivel, Mapa *mapa, Coordenada torre){
    int distancia_ataque = mapa->distancia_ataque;
    int count = 0;
    for (int dx = -distancia_ataque; dx <= distancia_ataque; dx++) {
        for (int dy = -distancia_ataque; dy <= distancia_ataque; dy++) {
            int nuevo_x = torre.x + dx;
            int nuevo_y = torre.y + dy;

            if (dx == 0 && dy == 0) continue;
            if (nuevo_x < 0 || nuevo_y < 0) continue;
            if (nuevo_x >= mapa->alto || nuevo_y >= mapa->ancho) continue;
            
            if(mapa->casillas[nuevo_x][nuevo_y] == CAMINO) {
                count++;
            }
        }
    } 
    return count;
}

