#ifndef TURNO_H
#define TURNO_H

#include "mapa.h"
#include "estrategia.h"
int simular_turno(Mapa *mapa, Nivel *nivel, Coordenada*, int);

int buscarEnemigo(Coordenada*, int, Coordenada);

void inicializar_turno(Nivel *nivel, Mapa *mapa, DisposicionTorres estrategia);
void decidir_nueva_posicion_abajo(Enemigos *enemigos, Mapa *mapa); 
void decidir_nueva_posicion_derecha(Enemigos *enemigos, Mapa *mapa); 
int simular_turno_abajo(Mapa *mapa, Nivel *nivel, Coordenada posiciones_ataque[], int ataques_efectivos); 
int simular_turno_derecha(Mapa *mapa, Nivel *nivel, Coordenada posiciones_ataque[], int ataques_efectivos); 


#endif
