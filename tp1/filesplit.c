#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POS_INI 0
#define UNO 1
#define DOS 2
#define NUM_ARG 3
#define LARGO_NOM 50

int main(int argc, char* argv[]){
		if(argc != NUM_ARG){
			fprintf(stderr, "Número de parametros inválidos\n");
			return POS_INI;
		}
		int num_bytes = atoi(argv[DOS]);
		FILE* archivo_aux = fopen(argv[UNO], "r");
		
		if(!archivo_aux){
			fprintf(stderr, "No se pudo abrir el Archivo\n");
			return POS_INI;
		}
		char* buffer = malloc( num_bytes + UNO);
			
		if(!buffer){
			fprintf(stderr, "No se pudo reservar memoria para el buffer\n");				
			return POS_INI;
		}
		int num_arch = POS_INI;
		while(feof(archivo_aux) == POS_INI){
			char nom_aux[LARGO_NOM];
			sprintf(nom_aux, "%s_" "%i", argv[UNO],num_arch );
			FILE* archivo_div = fopen( nom_aux , "w");
			fwrite(buffer, UNO, fread(buffer, UNO, num_bytes , archivo_aux), archivo_div);
			fclose(archivo_div);
			memset(buffer, '\0', num_bytes);
			num_arch ++;
		}
		free(buffer);
		fclose(archivo_aux);
		return POS_INI;
}
