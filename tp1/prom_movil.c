#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "vector_dinamico.h"

#define POS_INI 0
#define UNO 1

	int main(){
	double* obtener_promedio_movil(int* arreglo, size_t n, size_t k){
		vector_t* vector = vector_crear(n);
		
		for(int i = POS_INI; i < n; i++){
			int suma = POS_INI, cant_repe = POS_INI;
			int aux = i - (int)k;
			if(aux < POS_INI){
				aux = POS_INI;
			}
			for (int j = aux; j <= i + k; j++){
				if(j >= POS_INI && j < n){
					cant_repe ++;
					suma += arreglo[j];					
				}
			}
			int prom = suma / cant_repe;
			vector_guardar(vector, i, prom);
		}
		return (double*)vector;
	}	


	double* obtener_promedio_movil2(int* arreglo, size_t n, size_t k){
		vector_t* vector = vector_crear(n);		
		
		long ki = (size_t)k;
		int suma = POS_INI, cant_repe = POS_INI;
		for(int i = POS_INI; i < n; i++){
			if( i <= ki ){
				suma += arreglo[i];
				cant_repe++;
			}
		}
		int prom = suma / cant_repe;
		vector_guardar(vector, POS_INI, prom);
		for (int i = UNO; i < n ; i++){
			if(i - ki <= POS_INI && i + ki < n){
				suma += arreglo[i + ki];
				cant_repe ++;
			}
			if(i - ki > POS_INI && i + ki < n){
				suma += arreglo[i + ki] - arreglo[i - ki -1];
			}
			if(i - ki > POS_INI && i + ki >= n ){
				suma -= arreglo[i - ki- 1];
				cant_repe --;
			}
			prom = suma / cant_repe;
			vector_guardar(vector, i, prom);
		}
		return (double*)vector;
	}
	
	
	vector_t* vector = vector_crear(10000);
	for(int i = 0; i < 10000; i++){
		vector_guardar(vector, i, i);
	}
	obtener_promedio_movil((int*)vector, 10000, 10);
	vector_destruir(vector);
}
