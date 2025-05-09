#include "cola.h"
#include <stdlib.h>

Cola *cola_crear(){
	Cola *nuevo = malloc(sizeof (Cola));
	nuevo->pos_eliminar = -1;
	nuevo->pos_agregar = 0;
	return nuevo;
}
int cola_es_vacia(Cola *cola){
	if(cola->pos_eliminar = -1){
		return 1;
	}
	return 0;
}
int cola_primero(Cola *cola){
	if(cola->pos_eliminar == -1){
		printf("vacia\n");
		return 1;
	}else{
		printf("%i\n", cola->datos[cola->pos_eliminar]);
	}
	return cola->pos_eliminar;
}
void cola_encolar(Cola * cola, int nuevo){
	if(cola->pos_agregar == cola->pos_eliminar){
		printf("agregaste a una cola llena\n");
	}else if (cola->pos_eliminar == -1){
		cola->pos_eliminar = 0;
		cola->datos[cola->pos_agregar] = nuevo;
		cola->pos_agregar +=1;
	}else{
		cola->datos[cola->pos_agregar] = nuevo;
		cola->pos_agregar = (cola->pos_agregar + 1) % MAX_COLA;
	}
}
void cola_desencolar(Cola *cola){
	if(cola->pos_eliminar == -1){
		printf("eliminando a lista vacia");
	}else if((cola->pos_eliminar + 1)% MAX_COLA == cola->pos_agregar){
		cola->pos_eliminar = -1;
		cola->pos_agregar = 0;
	}else {
		cola->pos_eliminar = (cola->pos_eliminar + 1) % MAX_COLA;
	}
}
void cola_imprimir(Cola *cola){
	if(cola->pos_eliminar == -1){
		printf("imprimiendo lista vacia");
	}else{
		for(int i = cola->pos_eliminar; i != cola->pos_agregar; i = (i+1) % MAX_COLA){
			printf("i: %i, %i\n",i, cola->datos[i]);
		}
	}
}
