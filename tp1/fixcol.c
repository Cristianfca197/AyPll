#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POS_INI 0
#define UNO 1
#define DOS 2
#define NUM_ARG 3
#define LARGO_NOM 50

int main(int argc, char **argv){
	if(argc != NUM_ARG){
		fprintf(stderr, "Número de parametros inválidos");
		return POS_INI;
	}
	size_t num_bytes = atoi(argv[DOS]);
	FILE* archivo_aux = fopen(argv[UNO], "r");
		
	if(!archivo_aux){
		fprintf(stderr, "No se pudo abrir el Archivo\n");
		return POS_INI;
	}
	char* buffer = NULL;
	size_t linea;
	while(feof(archivo_aux) == POS_INI){
		ssize_t leidos;
		int cont = POS_INI, cont_aux = POS_INI;
		if((leidos = getline(&buffer, &linea, archivo_aux)) != -UNO){
			while((buffer[cont] != '\0')){
				printf("%c", buffer[cont]);
				cont ++;
				cont_aux ++;
				if(cont_aux == num_bytes){
					printf("\n");
					cont_aux = POS_INI;
				}
			}
			printf("\n");
		}
	}
	free(buffer);
	fclose(archivo_aux);
	return 0;
}

