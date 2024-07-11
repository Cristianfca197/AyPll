#ifndef TP2_H
#define TP2_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

// === Manejo de un string y una cantidad ===

struct tag{
   const char* nombre;
   size_t cant;
};

typedef struct tag tag_t;

// Funcion de comparacion de tag_t, devolviendo 1, 0 o -1 dependiendo la cantidad de cada uno
int comp_tags(const void *a, const void *b);

// === TDA Counting Filters ===

struct cf;
typedef struct cf cf_t;

// Crea un arreglo de cf vacio con un tamanio 'tam'
// Pos: El cf esta creado, o devuelvió NULL si no pudo hacerlo
cf_t *cf_crear(size_t tam);

// Suma una mencion en el arreglo del cf
// Pre: El cf fue creado
// Pos: Se le sumo una mencion a tal hashtag, devuelve false si no pudo hacerlo
bool cf_sumar(cf_t *cf, const char *hashtag);

// Obtiene la cantidad aproximada de menciones
// Pre: El cf fue creado
// Pos: Se obtuvo la cantidad aproximada de menciones del hashtag
size_t cf_obtener(const cf_t *cf, const char *hashtag);

// Toma un TDA counting filters y lo transforma en un arreglo de structs de hashtags y menciones
// Es responsabilidad del usuario liberar la memoria reservada del arreglo una vez usado
// Pre: El cf fue creado
tag_t* cf_trends(cf_t *cf, size_t cant_tts);

// Renueva la lista de hashtags que contiene el counting filter para poder almacenar nuevas menciones
// Pre: El cf fue creado 
void cf_limpiar(cf_t *cf);

// Libera el counting filter
// Pre: El cf fue creado
void cf_destruir(cf_t *cf);

// === Manejo de tweets ===

// Lee un tweet del flujo de archivo que se le pase, hay que liberar la memoria almacenada con tweet_borrar
// Post: Se devolvio un array de strings con el usuario y los hashtags del tweet
char** tweet_leer(FILE* flujo);

// Libera la memoria reservada por un tweet_leer
// Pre: Se habia leido el tweet
void tweet_borrar(char** tweet);

#endif // TP2_H

