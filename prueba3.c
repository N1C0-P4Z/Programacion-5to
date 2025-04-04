#include <stdio.h>


#define masc_t 255
#define masc_h (127 << 8)
#define masc_p (2047 << 15)
struct hola {
    jijo
}

int main(void) {
	char temp;
	unsigned char hum;
	unsigned int pre, lect;
	
  printf("Ingrese valor lectura  :  ");
	scanf("%i", &lect);


	if (lect & 1<<31) {
		printf("Falla lectura presión\n");
		return 1;
	}
	if (lect & 1<<30) {
		printf("Falla lectura humedad\n");
		return 2;
	}
	if (lect & 1<<29) {
		printf("Falla lectura temperatura\n");
		return 3;
	}
	
	temp = lect & masc_t;
	hum = (lect & masc_h) >> 8;
	pre = (lect & masc_p) >> 15 ;




	if (temp >= -70 && pre >= 382) {
		printf("La temperatura es de %i grados centígrados\n", temp);
		printf("La humedad relativa es del %i %%\n", hum);
		printf("La presion es de %i Hectopascales\n", pre);
	} else {
		printf("ERROR_DE_LECTURA\n");
	}
	
  return 0;
}
