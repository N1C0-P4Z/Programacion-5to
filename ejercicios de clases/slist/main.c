#include "slist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

int main() {

  SList lista = slist_crear();

  lista = slist_agregar_inicio(lista, 5);
  lista = slist_agregar_inicio(lista, 4);
  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_final(lista, 6);

  // Con las funciones de agregado alternativas
  slist_agregar_inicio_alt(&lista, 2);
  slist_agregar_inicio_alt(&lista, 1);
  slist_agregar_final_alt(&lista, 7);
  lista = slist_agregar_final_R(lista, 8);

  slist_recorrer(lista, imprimir_entero);
  puts("");

  slist_destruir(lista);

  return 0;
}
