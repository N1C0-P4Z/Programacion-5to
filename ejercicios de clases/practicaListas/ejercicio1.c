#include "slist.h"
static void imprimir_entero(int dato){
	printf("%d ", dato);
}
int main(){
	printf("ejercicio 1 ");
	SList primera = slist_crear();

	primera = slist_agregar_inicio(primera, 5);
	primera = slist_agregar_inicio(primera, 4);
	primera = slist_agregar_inicio(primera, 3);
	primera = slist_agregar_final(primera, 6);
	
	SList segunda = slist_crear();

	segunda = slist_agregar_inicio(segunda, 14);
	segunda = slist_agregar_inicio(segunda, 6);
	segunda = slist_agregar_inicio(segunda, 8);
	segunda = slist_agregar_final(segunda, 7);

	concatenarListas(primera, segunda);
	slist_recorrer(primera, imprimir_entero);
	printf("\n");
	slist_recorrer(segunda, imprimir_entero);
	return 0;
}
