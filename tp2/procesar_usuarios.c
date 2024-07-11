#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "heap.h"
#include "lista.h"
#include "tp2.h"


#define NUM_ARG 2

tag_t* crear_campo(char* usuario, int cant){
   tag_t* campo_act = malloc(sizeof(tag_t));
   if(campo_act == NULL)
      return NULL;
   char* user_act = malloc(strlen(usuario) + 1);
   strcpy(user_act, usuario);
   campo_act->nombre = user_act;
   campo_act->cant = cant;
   return campo_act;
}

void destruir_campo (void* campo_act){
   free(((void*)((tag_t*)campo_act)->nombre));
   free(campo_act);
}

hash_t* inicializar_entrada(FILE* archivo){
   hash_t* hash_user = hash_crear(destruir_campo);
   
   if(hash_user == NULL){
      fprintf(stderr, "No se pudo crear el hash\n");
      fclose(archivo);
      return NULL;
   }
   
   while(feof(archivo) == 0){
      char** arr_linea = tweet_leer(archivo);
      if(arr_linea == NULL)
         break;
      int cant_hstg_act = 0;
      char* user_act = arr_linea[0];
      
      for(int i = 1; arr_linea[i] != NULL; i++){
         cant_hstg_act ++;
      }
      
      if(!hash_pertenece(hash_user, user_act)){
         tag_t* campo_act = crear_campo(user_act, cant_hstg_act);
         hash_guardar(hash_user, campo_act->nombre, campo_act);
      }else{
         tag_t* usuario = (tag_t*)hash_obtener(hash_user, user_act);
         usuario->cant += cant_hstg_act;
      }
      tweet_borrar(arr_linea);
   }
   fclose(archivo);
   return hash_user;
}

heap_t* heapificar_datos(hash_t* hash_user){
   hash_iter_t* iter_hash = hash_iter_crear(hash_user);
   if(iter_hash == NULL){
      fprintf(stderr, "No se pudo crear el iter del hash\n");
      return NULL;
   }
   void** vector = malloc(sizeof(tag_t*) * hash_cantidad(hash_user));
   if(vector == NULL){
      fprintf(stderr, "No se pudo crear el vector de los datos\n");
      hash_iter_destruir(iter_hash);
      return NULL;
   }
   int i = 0;
   while(!hash_iter_al_final(iter_hash)){
      char* user_act = (char*)hash_iter_ver_actual(iter_hash);
      tag_t* campo_act = hash_obtener(hash_user, user_act);
      vector[i] = campo_act;
      hash_iter_avanzar(iter_hash);
      i++;
   }
   heap_t* heap_aux = heap_crear_arr(vector, hash_cantidad(hash_user),comp_tags);
   if(heap_aux == NULL){
      fprintf(stderr, "No se pudo crear el heap\n");
      hash_iter_destruir(iter_hash);
      free(vector);
      return NULL;
   }
   hash_iter_destruir(iter_hash);
   free(vector);
   return heap_aux;
}

void imprimir_datos(heap_t* heap_aux, hash_t* hash_user){
   size_t cant_act = 0;
   while(!heap_esta_vacio(heap_aux)){
      tag_t* campo_act = (tag_t*)heap_desencolar(heap_aux);
      if(campo_act->cant != cant_act){
         cant_act = campo_act->cant;
         printf("\n%zu: %s", cant_act, campo_act->nombre);
      }else{
         printf(", %s", campo_act->nombre);
      }
   }
}
int main(int argc, char* argv[]){
   if(argc != NUM_ARG){
      fprintf(stderr, "Número de parametros inválidos\n");
      return 1;
   }
   FILE* archivo = fopen(argv[1], "r");
   
   if(!archivo){
      fprintf(stderr, "No se pudo abrir el Archivo\n");
      return 1;
   }

   hash_t* hash_user = inicializar_entrada(archivo);
   
   if(hash_user == NULL)
      return 2;
   
   heap_t* heap_aux = heapificar_datos(hash_user);
   
   if(heap_aux == NULL){
      hash_destruir(hash_user);
      return 2;
   }
   imprimir_datos(heap_aux, hash_user);
   hash_destruir(hash_user);
   heap_destruir(heap_aux, destruir_campo);
   return 0;
}
