#include "slist.h"

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodo_a_eliminar;
  while (lista != NULL) {
    nodo_a_eliminar = lista;
    lista = lista->sig;
    free(nodo_a_eliminar);
  }
}
int sList_length(SList lista){
  int i;
  for(i = 0; lista->sig != NULL; i++){
      lista = lista->sig;
  }
  return i;
}
SList slist_destruirUnNodo(SList lista, int numNodo) {
  SNodo *nodo_a_eliminar;
  SList temp = lista;
  if(sList_length(lista)==1){
	slist_destruir(lista);
	return lista;
  }
  if(lista != NULL && numNodo>=0 && numNodo < sList_length(lista)){
    for ( int i = 0; i < numNodo-1; i++){
      temp = temp->sig;
    }
    nodo_a_eliminar = temp->sig;
    temp->sig = temp->sig->sig;
    free(nodo_a_eliminar);
  }
  return lista;

}
int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevo_nodo = malloc(sizeof(SNodo));
  nuevo_nodo->dato = dato;
  nuevo_nodo->sig = NULL;

  if (lista == NULL)
    return nuevo_nodo;

  SList nodo_temp = lista;
  for (; nodo_temp->sig != NULL; nodo_temp = nodo_temp->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo_temp->sig = nuevo_nodo;
  return lista;
}

void slist_agregar_final_alt(SNodo** lista, int dato) {
  SNodo *nuevo_nodo = malloc(sizeof(SNodo));
  nuevo_nodo->dato = dato;
  nuevo_nodo->sig = NULL;

  if (*lista == NULL) {
    *lista = nuevo_nodo;
    return;
  }

  SList nodo_temp = *lista;
  for (; nodo_temp->sig != NULL; nodo_temp = nodo_temp->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo_temp->sig = nuevo_nodo;
}

SList slist_agregar_final_R(SList lista, int dato) {
  if (lista == NULL) {
    lista = malloc(sizeof(SNodo));
    lista->dato = dato;
    lista->sig = NULL;
  } else {
    lista->sig = slist_agregar_final_R(lista->sig, dato);
  }
  
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevo_nodo = malloc(sizeof(SNodo));
  nuevo_nodo->dato = dato;
  nuevo_nodo->sig = lista;
  return nuevo_nodo;
}

void slist_agregar_inicio_alt(SNodo** lista, int dato) {
  SNodo *nuevo_nodo = malloc(sizeof(SNodo));
  nuevo_nodo->dato = dato;
  nuevo_nodo->sig = *lista;
  *lista = nuevo_nodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

