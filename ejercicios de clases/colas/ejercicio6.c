#include "cola.h"

int main(){
	Cola *jijo = cola_crear();
	cola_encolar(jijo, 1);
	cola_encolar(jijo, 2);
	cola_encolar(jijo, 3);
	cola_desencolar(jijo);
	cola_desencolar(jijo);
	cola_encolar(jijo, 4);
	cola_encolar(jijo, 5);
	cola_encolar(jijo, 6);
	cola_encolar(jijo, 7);
	cola_imprimir(jijo);
	/*cola_desencolar(jijo);*/
	/*cola_desencolar(jijo);*/
	/*cola_primero(jijo);*/
	/*cola_encolar(jijo, 3);*/
	/*cola_primero(jijo);*/
	/*cola_desencolar(jijo);*/
	/*cola_primero(jijo);*/

	return 0;
}
