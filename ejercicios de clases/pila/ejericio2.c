#include "stack.h"
#include <stdlib.h>

int main(){
	Pila *jijo;
	jijo = pila_crear();
	printf("la pila vacia? %i\n", pila_es_vacia(jijo));

	pila_apilar(jijo, 1);
	pila_apilar(jijo, 2);
	pila_apilar(jijo, 2);
	pila_apilar(jijo, 3);
	pila_apilar(jijo, 3);
	printf("pila es vacia? %i\n", pila_es_vacia(jijo));
	pila_desapilar(jijo);
	pila_imprimir(jijo);
	free(jijo);


	return 0;
}
