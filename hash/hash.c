#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "lista.h"

#define CANT_TABLA_INI 277
#define FDC 5
#define AGRANDAR 5
#define ACHICAR 2

// Hash abierto

struct hash{
   size_t cant;
   size_t tam;
   hash_destruir_dato_t destructor;
   lista_t** tabla;
};

struct hash_iter{
   hash_t* hash;
   lista_iter_t* lista_iter;
   size_t indice;
};

typedef struct campo_hash campo_t;

struct campo_hash{
   char* clave;
   void* dato;
};

lista_t** hash_tabla_crear(size_t tam_nuevo){
   lista_t** tabla = malloc(tam_nuevo*sizeof(lista_t*));
   if(tabla == NULL)
      return NULL;

   for(int i = 0; i < tam_nuevo; i++){
      tabla[i] = lista_crear();
      if(tabla[i] == NULL)
         return NULL;
   }
   return tabla;
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
   hash_t* hash = malloc(sizeof(hash_t));
   hash->tabla = hash_tabla_crear((size_t)CANT_TABLA_INI);
   if(hash == NULL || hash->tabla == NULL)
      return NULL;
      
   hash->cant = 0;    
   hash->tam = CANT_TABLA_INI;
   hash->destructor = destruir_dato;
   
   return hash;
}

campo_t* crear_campo_hash(const char *clave, void *dato){
   campo_t* campo = malloc(sizeof(campo_t));
   if(campo == NULL)
      return NULL;
   campo->clave = malloc(strlen(clave) + 1);
   strcpy(campo->clave,clave);
   campo->dato = dato;
   return campo;
}

// Funcion de hashing
unsigned long func_hash(const char* str){   
   unsigned long func_hash = 5381;
   int c;
   while ((c = *str++) != 0)
      func_hash = ((func_hash << 5) + func_hash) + c; 
   return func_hash;
}


// Funcion para redimensionar el hash
// Creo una tabla nueva con el nuevo tamanio y le paso todos los elementos
void hash_redimensionar(hash_t *hash, size_t tamnuevo){
   lista_t** tabla_aux = hash_tabla_crear(tamnuevo);
   if(tabla_aux == NULL)
      return;
   lista_t** aux = tabla_aux;
   tabla_aux = hash->tabla;
   hash->tabla = aux;
   size_t tam_hash = hash->tam;
   hash->tam = tamnuevo;
   hash->cant = 0;
   for(int i = 0; i < tam_hash; i++){
      lista_iter_t* iter_lista = lista_iter_crear(tabla_aux[i]);
      while(!lista_iter_al_final(iter_lista)){
         campo_t* campo_act = lista_iter_borrar(iter_lista);
         hash_guardar(hash, campo_act->clave, campo_act->dato);
         free(campo_act->clave);
         free(campo_act);
      }
      lista_iter_destruir(iter_lista);
      lista_destruir(tabla_aux[i], NULL);
   }
   free(tabla_aux);
   return;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
   if(hash_pertenece(hash, clave)){
      if(hash->destructor != NULL)
         hash->destructor(hash_borrar(hash, clave));
      hash_borrar(hash, clave);
   }
   if (hash->cant > hash->tam * FDC)
      hash_redimensionar(hash, hash->tam * AGRANDAR);

   campo_t* campo_aux = crear_campo_hash(clave, dato);
   if(campo_aux == NULL)
      return false;

   hash->cant++;
   unsigned long pos_hash = func_hash(clave) % hash->tam;
   return lista_insertar_ultimo(hash->tabla[pos_hash], campo_aux);
}

// Funcion para buscar clave
// Itero la lista de esa pos hasta que las claves coincidan
lista_iter_t* buscar_clave(const hash_t* hash, const char* clave){
   unsigned long pos = func_hash(clave) % hash->tam;
   
   if (lista_esta_vacia(hash->tabla[pos]))
      return NULL;
   lista_iter_t* iterador = lista_iter_crear(hash->tabla[pos]);
   char* clave_actual = ((campo_t*)lista_iter_ver_actual(iterador))->clave;
   
   while (!lista_iter_al_final(iterador)){
      clave_actual = ((campo_t*)lista_iter_ver_actual(iterador))->clave;
      if (!strcmp(clave_actual,clave))
         return iterador;
      lista_iter_avanzar(iterador);
   }
   lista_iter_destruir(iterador);
   return NULL;
}

void *hash_borrar(hash_t *hash, const char *clave){
   lista_iter_t* iterador = buscar_clave(hash, clave);
   if(iterador == NULL)
      return NULL;
   void* dato_aux = ((campo_t*)lista_iter_ver_actual(iterador))->dato;
   free(((campo_t*)lista_iter_ver_actual(iterador))->clave);
   free(lista_iter_ver_actual(iterador));
   lista_iter_borrar(iterador);
   lista_iter_destruir(iterador);
   hash->cant--;
   if (hash->cant < hash->tam / FDC && hash->tam > CANT_TABLA_INI)
      hash_redimensionar(hash, CANT_TABLA_INI);
   return dato_aux;
}


void *hash_obtener(const hash_t *hash, const char *clave){
   lista_iter_t* iterador = buscar_clave(hash, clave);
   if(iterador == NULL)
      return NULL;
   void* dato_aux = ((campo_t*)lista_iter_ver_actual(iterador))->dato;
   lista_iter_destruir(iterador);
   return dato_aux;
}



bool hash_pertenece(const hash_t *hash, const char *clave){
   lista_iter_t* iterador = buscar_clave(hash,clave);
   bool pertenece = (iterador != NULL);
   lista_iter_destruir(iterador);
   return pertenece;
}

size_t hash_cantidad(const hash_t *hash){
   return hash->cant;
}

void hash_destruir(hash_t *hash){
   if(hash == NULL)
      return;

   for(int i = 0; i < hash->tam; i++){
      lista_iter_t* iterador = lista_iter_crear(hash->tabla[i]);
      while(!lista_esta_vacia(hash->tabla[i])){
         if(hash->destructor != NULL)
            hash->destructor(((campo_t*)lista_iter_ver_actual(iterador))->dato);
         free(((campo_t*)lista_iter_ver_actual(iterador))->clave);
         free(lista_iter_borrar(iterador));
      }
      lista_iter_destruir(iterador);
      lista_destruir(hash->tabla[i], NULL);
   }
   free(hash->tabla);
   free(hash);
}

/* Iterador del hash */

hash_iter_t *hash_iter_crear(const hash_t *hash){

   hash_iter_t* iter = malloc(sizeof(hash_iter_t));
   if (iter == NULL)
      return NULL;
   iter->hash = (hash_t*)hash;
   iter->indice = 0;
   iter->lista_iter = lista_iter_crear(hash->tabla[0]); 
   if(lista_iter_al_final(iter->lista_iter))          // Si no esta apuntando a nada
      hash_iter_avanzar(iter);                        // Avanza hasta el primer elem

   return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){
   if (lista_iter_avanzar(iter->lista_iter))
      if (!lista_iter_al_final(iter->lista_iter)      // Si avanzo y no quedo apuntando a null
         return true;
   while(!hash_iter_al_final(iter)){                  // Mientras no llegue al final de la tabla
      if (lista_iter_al_final(iter->lista_iter)){     // Si llego al final de la lista
         iter->indice++;
         if (!hash_iter_al_final(iter)){              // Si no llego al final de la tabla
            lista_iter_destruir(iter->lista_iter);    // Paso a la siguiente lista
            iter->lista_iter = lista_iter_crear(iter->hash->tabla[iter->indice]);
         }
      }
      else      // La lista tiene elementos (y ahora apunta al primero)
         return true;
   }
   return false;
}


const char *hash_iter_ver_actual(const hash_iter_t *iter){
   campo_t* campo_aux = (campo_t*)lista_iter_ver_actual(iter->lista_iter);
   if(campo_aux == NULL)
      return NULL;
   return campo_aux->clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){
   return ((iter->indice == iter->hash->tam));
}

void hash_iter_destruir(hash_iter_t* iter){
   lista_iter_destruir(iter->lista_iter);
   free(iter);
}

