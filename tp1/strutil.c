#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define POS_INI 0
#define UNO 1
#define LARGO_STR 100

int main(){
	
	void free_strv(char* strv[]){
		int i = POS_INI;
		while(strv[i] != NULL){
			free(strv[i]);
			i ++;
		}
		free(strv);
	}
	
	
	char** split( char* str, char sep){
		if(sep == '\0')
			return NULL;
		char** vector = malloc(sizeof(char*)*strlen(str));
		if(vector == NULL)
			return NULL;
		
		char string[strlen(str) + UNO];
		int pos_string = POS_INI;
		int csa = POS_INI;
		int i = POS_INI;
		while(i < strlen(str) + UNO){
			if(str[i] != sep && str[i] != '\0'){
				string[csa] = str[i];
				csa ++;
				i ++;
			}
			else{
				string[csa] = '\0';
				char* aux = strdup(string);
				if(aux == NULL){
					vector[pos_string] = NULL;
					free_strv(vector);
					return NULL;
				}
				vector[pos_string] = aux;
				pos_string ++;
				csa = POS_INI;
				i ++;
			}
		}
		vector[pos_string] = NULL;
		return vector;
	}
	
	char* join(char** strv, char sep){
		char string_aux[LARGO_STR];
		int pos = POS_INI;
		int pos_string = POS_INI;
		while(strv[pos] != NULL){
			if(pos != POS_INI){
				string_aux[pos_string] = sep;
				pos_string ++;
			}
			char* aux = strv[pos];
			int pos_sub = POS_INI;
			for(int i = pos_string; aux[i] != '\0'; i++){
				string_aux[i] = aux[pos_sub];
				pos_sub ++;
				pos_string ++;
			}
			pos ++;
		}
		string_aux[pos_string] = '\0';
		char* string = strdup(string_aux);
		return string;
	}	
	


	return 0;
}

