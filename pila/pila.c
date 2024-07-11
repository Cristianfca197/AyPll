#include "pila.h"
#include <stdlib.h>
/* Definición del struct pila proporcionado por la cátedra.*/
#define tam_ini 1
#define cant_ini 0
#define modificar_tam 2
#define max_cantidad 4

struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

pila_t* pila_crear(void){
	pila_t* pila=malloc(sizeof(pila_t));
	pila->datos=malloc((sizeof(void**)));
	
	if((pila == NULL) || (pila->datos == NULL)){
		free(pila);
		return NULL;
	}
	pila->cantidad = cant_ini;
	pila->capacidad = tam_ini;
	return pila;
}

void pila_destruir(pila_t* pila){
	if(pila == NULL){
		return;
	}
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t* pila){
	return (pila->cantidad == cant_ini);
}

bool pila_esta_llena(pila_t* pila){
	return (pila->cantidad == pila->capacidad);
}
bool redimensionar_pila(pila_t* pila) {
	size_t capacidad_nueva;
	if(pila_esta_llena(pila)){
		capacidad_nueva = pila->capacidad * modificar_tam;
	}else{
		capacidad_nueva = pila->capacidad / modificar_tam;
	}
    void** datos_nuevo = realloc(pila->datos, capacidad_nueva * sizeof(void**));
    if(datos_nuevo == NULL){
		return false;
	}
    pila->datos = datos_nuevo;
    pila->capacidad = capacidad_nueva;
    return true;
}

bool pila_apilar(pila_t* pila, void* valor){
	if(pila == NULL){
		return NULL;
	}
	if(pila_esta_llena(pila)){
		if(!redimensionar_pila(pila)){
			return false;
		}
	}
	pila->datos[pila->cantidad]=valor;
	pila->cantidad++;
	return true;
}

void* pila_ver_tope(const pila_t* pila){
	if(pila_esta_vacia(pila)){
		return NULL;
	}
	return (pila->datos[pila->cantidad - tam_ini]);
}

void* pila_desapilar(pila_t* pila){
	if(pila_esta_vacia(pila)){
		return NULL;
	}
	if(pila->cantidad * max_cantidad < pila->capacidad){
		redimensionar_pila(pila);
	}	
	void* ultimo_elem = pila_ver_tope(pila);
	pila->cantidad--;
	return ultimo_elem;
}
