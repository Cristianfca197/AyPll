#include "cola.h"
#include <stdlib.h>

struct nodo{
	void* datos;
	struct nodo* ref_siguiente;
}typedef nodo_t;
	
struct cola{
	nodo_t* cabeza;
	nodo_t* ultimo;
};

cola_t* cola_crear(void){
	cola_t* cola = malloc(sizeof(cola_t));
	
	if(cola == NULL){
		return NULL;
	} 
	cola->cabeza = NULL;
	cola->ultimo = NULL;
	return cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	if(cola == NULL){
		return;
	}
	while(!cola_esta_vacia(cola)){
		nodo_t* nodo_destruir = cola->cabeza;
		cola->cabeza = nodo_destruir->ref_siguiente;
		if(destruir_dato != NULL){
			destruir_dato(nodo_destruir->datos);
		}	
		free(nodo_destruir);
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t* cola){
	if(cola == NULL){
		return NULL;
	}
	return (cola->cabeza == NULL);
}

bool cola_encolar(cola_t *cola, void* valor){
	if(cola == NULL){
		return NULL;
	}
	nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
	
	if(nuevo_nodo == NULL){
		return false;
	}
	nuevo_nodo->datos = valor;
	nuevo_nodo->ref_siguiente = NULL;
	
	if(cola_esta_vacia(cola)){
		cola->cabeza = nuevo_nodo;
		cola->ultimo = nuevo_nodo;
	}else{
		cola->ultimo->ref_siguiente = nuevo_nodo;
		cola->ultimo = nuevo_nodo;
	}
	return true;
}

void* cola_ver_primero(const cola_t *cola){
	if(cola == NULL){
		return NULL;
	}
	if(cola_esta_vacia(cola)){
		return NULL;
	}
	return cola->cabeza->datos;
}
void* cola_desencolar(cola_t *cola){
	if(cola == NULL){
		return NULL;
	}
	if(cola_esta_vacia(cola)){
		return NULL;
	}
	nodo_t* nodo_aux = cola->cabeza;
	cola->cabeza = nodo_aux->ref_siguiente;
	void* primer_elem = nodo_aux->datos;
	free(nodo_aux);
	return primer_elem;
}
