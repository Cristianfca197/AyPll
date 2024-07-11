#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include "tp2.h"
#include "strutil.h"
#include "heap.h"
#include "hash.h"

#define CANT_FILT 5 // Cantidad de filtros que tiene el cf

struct cf{
   size_t** vecs;
   hash_t* tags;
   size_t vecs_tam;
   size_t vecs_cant;
};

cf_t *cf_crear(size_t tam){
   cf_t* cf = malloc(sizeof(cf_t));
   if(!cf)
      return NULL;
   cf->vecs_tam = tam;
   cf->vecs_cant = CANT_FILT;
   cf->vecs = malloc(sizeof(size_t*) * cf->vecs_cant);
   for(size_t i = 0; i < cf->vecs_cant; i++){
      cf->vecs[i] = calloc(cf->vecs_tam, sizeof(size_t));
      if(!cf->vecs[i]){
         for(size_t j = 0; j < i; j++)
            free(cf->vecs[j]);
         free(cf);
         return NULL;
      }
   }
   cf->tags = hash_crear(NULL);
   if (!cf->tags)
      return NULL;
   return cf;
}

// Funcion de hash que recibe un parametro variable
unsigned long func_hash_mult(const char* str, size_t k){   
   unsigned long func_hash = 5381;
    int c;
    while ((c = *str++) != 0)
      func_hash = ((func_hash << 5) + func_hash) + c; 
    return func_hash << k;
}

bool cf_sumar(cf_t *cf, const char *hashtag){
   size_t pos;
   for(size_t i = 0; i < cf->vecs_cant; i++){
      pos = func_hash_mult(hashtag,i) % cf->vecs_tam;
      cf->vecs[i][pos]++;
   }
   if(!hash_pertenece(cf->tags,hashtag))
      if(!hash_guardar(cf->tags,hashtag,NULL))
         return false;
   return true;
}

size_t cf_obtener(const cf_t *cf, const char *hashtag){
   size_t pos;
   size_t menor = -1;   // Como es size_t el valor es el mas grande del tipo
   for(size_t i = 0; i < cf->vecs_cant; i++){
      pos = func_hash_mult(hashtag,i) % cf->vecs_tam;
      if (cf->vecs[i][pos] < menor)
         menor = cf->vecs[i][pos];
   }
   return menor;
}

int comp_tags(const void *a, const void *b){
   tag_t* ta = (tag_t*)a;
   tag_t* tb = (tag_t*)b;   
   if(ta->cant < tb->cant)
      return 1;
   else if(ta->cant > tb->cant)
      return -1;
   return 0;
}









tag_t* cf_trends(cf_t *cf, size_t cant_tts){
   size_t tam_tabla = hash_cantidad(cf->tags);
   tag_t* tabla = malloc(sizeof(tag_t) * tam_tabla);
   if(!tabla)
      return NULL;
   hash_iter_t* iter_tabla = hash_iter_crear(cf->tags);
   if(!iter_tabla)
      return NULL;
   // Paso todo el counting filter a un array de tag_t
   for(size_t i = 0; !hash_iter_al_final(iter_tabla); i++){
      tabla[i].nombre = hash_iter_ver_actual(iter_tabla);
      tabla[i].cant = cf_obtener(cf,tabla[i].nombre);
      hash_iter_avanzar(iter_tabla);
   }
   hash_iter_destruir(iter_tabla);
   // Lo meto en un heap que guarde los K con mas menciones
   heap_t* heap = heap_crear(comp_tags);
   if(!heap)
      return NULL;
   for(size_t i = 0; i < tam_tabla; i++){
      heap_encolar(heap,&tabla[i]);
      if(heap_cantidad(heap) > cant_tts)
         heap_desencolar(heap);
   }
   // Lo devuelvo como arreglo de tag_t
   tag_t* res = malloc(sizeof(tag_t) * cant_tts);
   if(!res)
      return NULL;
   tag_t* buff;
   for(size_t i = 1; i <= cant_tts; i++){
      buff = heap_desencolar(heap);
      res[cant_tts - i].nombre = buff->nombre;
      res[cant_tts - i].cant = buff->cant;
   }
   // Libero las esructuras auxiliares usadas
   free(tabla);
   heap_destruir(heap,NULL);
   return res;
}

void cf_limpiar(cf_t *cf){
   hash_destruir(cf->tags);
   cf->tags = hash_crear(NULL);
}

void cf_destruir(cf_t *cf){
   hash_destruir(cf->tags);
   for(size_t i = 0; i < cf->vecs_cant; i++)
      free(cf->vecs[i]);
   free(cf->vecs);
   free(cf);
}

char** tweet_leer(FILE* flujo){
   char* linea = NULL;
   size_t capacidad = 0;
   size_t longitud = getline(&linea, &capacidad, flujo);
   if(longitud == -1){
      free(linea);
      return NULL;
   }
   linea[longitud - 1] = '\0';   // getline me incluye los saltos de linea
   char** res = split(linea,',');
   free(linea);
   return res;
}

void tweet_borrar(char** tweet){
   free_strv(tweet);
}


