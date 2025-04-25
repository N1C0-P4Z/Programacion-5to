#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef void (*FuncionVisitante) (int dato);

typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo* SList;
SList slist_crear();

int sList_length(SList lista);

void slist_destruir(SList lista);

SList slist_destruirUnNodo(SList lista, int numNodo); 

int slist_vacia(SList lista);

SList slist_agregar_final(SList lista, int dato);

SList slist_agregar_arbitraria(SList lista, int nuevo, int posicion);

void slist_agregar_final_alt(SNodo** lista, int dato);

SList slist_agregar_final_R(SList lista, int dato);

SList slist_agregar_inicio(SList lista, int dato);

void slist_agregar_inicio_alt(SNodo** lista, int dato);
void concatenarListas(SList primera, SList segunda);
void slist_recorrer(SList lista, FuncionVisitante visit);
#endif
