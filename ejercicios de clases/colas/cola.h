#ifndef  __COLA_H__
#define __COLA_H__
#include <stdlib.h>
#include <stdio.h>
#define MAX_COLA 5

typedef struct _Cola {
	int datos [MAX_COLA];
	int pos_eliminar, pos_agregar;
}Cola;

Cola *cola_crear();
int cola_es_vacia(Cola*);
int cola_primero(Cola*);
void cola_encolar(Cola *, int);
void cola_desencolar(Cola *);
void cola_imprimir(Cola *);

#endif
