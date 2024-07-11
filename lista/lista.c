#include "lista.h"
#include <stdlib.h>

#define largo_ini 0;

struct nodo{
	void* datos;
	struct nodo* ref_siguiente;
}typedef nodo_t;
	
struct lista{
	nodo_t* cabeza;
	nodo_t* ultimo;
	size_t largo;
};

lista_t* lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));
	
	if(lista == NULL){
		return NULL;
	} 
	lista->cabeza = NULL;
	lista->ultimo = NULL;
	lista->largo = largo_ini;
	return lista;
}


bool lista_esta_vacia(const lista_t* lista){
	return (lista->cabeza == NULL);
}

nodo_t* crear_nodo(void* valor){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	
	if(nodo == NULL){
		return NULL;
	}
	nodo->datos = valor;
	nodo->ref_siguiente = NULL;
	return nodo;
}

void insertar_lista_vacia(lista_t *lista, nodo_t* nodo){
	lista->cabeza = nodo;
	lista->ultimo = nodo;
}

bool lista_insertar_primero(lista_t *lista, void* valor){
	nodo_t* nuevo_nodo = crear_nodo(valor);
	
	if(lista_esta_vacia(lista)){
		insertar_lista_vacia(lista, nuevo_nodo);
	}else{
		nuevo_nodo->ref_siguiente = lista->cabeza;
		lista->cabeza = nuevo_nodo;
	}
	lista->largo++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void* valor){
	nodo_t* nuevo_nodo = crear_nodo(valor);
	
	if(lista_esta_vacia(lista)){
		insertar_lista_vacia(lista, nuevo_nodo);
	}else{
		lista->ultimo->ref_siguiente = nuevo_nodo;
		lista->ultimo = nuevo_nodo;
	}
	lista->largo++;
	return true;
}

void* lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	nodo_t* nodo_aux = lista->cabeza;
	lista->cabeza = nodo_aux->ref_siguiente;
	void* primer_elem = nodo_aux->datos;
	free(nodo_aux);
	lista->largo--;
	return primer_elem;
}

void* lista_ver_primero(const lista_t *lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->cabeza->datos;
}

void* lista_ver_ultimo(const lista_t *lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->ultimo->datos;
}

size_t lista_largo(const lista_t *lista){
	return (lista->largo);
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void*)){
	if(lista == NULL){
		return;
	}
	while(!lista_esta_vacia(lista)){
		nodo_t* nodo_destruir = lista->cabeza;
		lista->cabeza = nodo_destruir->ref_siguiente;
		if(destruir_dato != NULL){
			destruir_dato(nodo_destruir->datos);
		}	
		free(nodo_destruir);
		lista->largo--;
	}
	free(lista);
}

struct lista_iter{
	lista_t* lista;
	nodo_t* actual;
	nodo_t* anterior;
}typedef lista_iter_t;

lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if(iter == NULL){
		return NULL;
	} 
	iter->lista = lista;
	iter->actual = lista->cabeza;
	iter->anterior = NULL;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if(lista_iter_al_final(iter) || lista_esta_vacia(iter->lista)){
		return false;
	}
	if(iter->actual == iter->lista->ultimo){
		iter->actual = NULL;
		iter->anterior = iter->lista->ultimo;
		return true;
	}
	if(iter->actual == iter->lista->cabeza){
		iter->anterior = iter->actual;
		iter->actual = iter->actual->ref_siguiente;
		return true;
	}
	iter->anterior = iter->actual;
	iter->actual = iter->actual->ref_siguiente;
	return true;
	
}

void* lista_iter_ver_actual(const lista_iter_t *iter){
	if(lista_esta_vacia(iter->lista)){
		return NULL;
	}
	if(lista_iter_al_final(iter)){
		return NULL;
	}
	return iter->actual->datos;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	return (iter->anterior == iter->lista->ultimo);
}

void lista_iter_destruir(lista_iter_t *iter){
	if(iter == NULL){
		return;
	}
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	if(iter->actual == iter->lista->cabeza){
		lista_insertar_primero(iter->lista, dato);
		iter->actual = iter->lista->cabeza;
		return true;
	}
	if(iter->anterior == iter->lista->ultimo){
		lista_insertar_ultimo(iter->lista, dato);
		iter->actual = iter->lista->ultimo;
		return true;
	}
	nodo_t* nuevo_nodo = crear_nodo(dato);
	nuevo_nodo->ref_siguiente = iter->actual;
	iter->anterior->ref_siguiente = nuevo_nodo;
	iter->actual = nuevo_nodo;
	iter->lista->largo++;
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
	if(lista_esta_vacia(iter->lista)){
		return NULL;
	}
	if(lista_iter_al_final(iter)){
		return NULL;
	}
	if(iter->actual == iter->lista->cabeza){
		iter->actual = iter->actual->ref_siguiente;
		void* elem_aux = lista_borrar_primero(iter->lista);
		return elem_aux;
	}
	if(iter->actual == iter->lista->ultimo){
		nodo_t* nodo_aux = iter->actual;
		iter->anterior->ref_siguiente = NULL;
		iter->actual = NULL;
		iter->lista->ultimo = iter->anterior;
		void* dato_aux = nodo_aux->datos;
		free(nodo_aux);
		iter->lista->largo--;
		return dato_aux;
	}
	nodo_t* nodo_aux = iter->actual;
	iter->anterior->ref_siguiente = nodo_aux->ref_siguiente;
	iter->actual = nodo_aux->ref_siguiente;
	void* dato_aux = nodo_aux->datos;
	free(nodo_aux);
	iter->lista->largo--;
	return dato_aux;
}

void lista_iterar(lista_t *lista, bool(*visitar)(void *dato, void *extra), void *extra){
	if(lista == NULL){
		return;
	}
	nodo_t* nodo_aux = lista->cabeza;
	while(nodo_aux){
		if(!visitar(nodo_aux->datos, extra)){
			return;
		}
		if(nodo_aux->ref_siguiente == NULL){
			nodo_aux = NULL;
		}else{
			nodo_aux = nodo_aux->ref_siguiente;
		}
	}
}
