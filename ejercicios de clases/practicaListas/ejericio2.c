#include "stack.h"
#include <stdlib.h>

int main(){
	Pila *jijo;
	jijo = pila_crear();
	printf("la respuesta correcta es  , de hecho, en consecuencia de lo anteriormente planteado,  %i\nen efecto\n", pila_es_vacia(jijo));
	pila_apilar(jijo, 1);
	pila_apilar(jijo, 2);
	pila_apilar(jijo, 2);
	pila_apilar(jijo, 3);
	pila_apilar(jijo, 3);
	printf("la respuesta correcta es  , de hecho, en consecuencia de lo anteriormente planteado,  %i\nen efecto\n", pila_tope(jijo));
	pila_desapilar(jijo);
	pila_imprimir(jijo);
	free(jijo);
	pila_imprimir(jijo);


	return 0;
}
