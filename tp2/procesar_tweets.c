#include <stdio.h>
#include <stdlib.h>
#include "tp2.h"

int main(int argc, char* argv[]){
   if(argc != 3){
      fprintf(stderr,"Invocacion: <./procesar_tweets n k>\n");
      return 1;
   }
   size_t cant_tweets, cant_tts;
   cant_tweets = atoi(argv[1]);
   cant_tts = atoi(argv[2]);
   if(!cant_tweets || !cant_tts || cant_tweets < cant_tts){
      fprintf(stderr,"Parametros incorrectos\n");
      return 2;
   }
   char** tweet;
   bool sigue = true;
   cf_t* contfilt = cf_crear(cant_tweets);
   if(!contfilt){
      fprintf(stderr,"Memoria insuficiente\n");
      return 3;
   }
   while(sigue){
      for(size_t i = 0; i < cant_tweets; i++){
         tweet = tweet_leer(stdin);
         if(!tweet){   // Termino el archivo
            sigue = false;
            cant_tweets = i;
            break;
         }
         for(size_t j = 1; (tweet[j] != NULL); j++)
            if(!cf_sumar(contfilt, tweet[j]))
               break;
         tweet_borrar(tweet);
      }
      if(cant_tts > cant_tweets)   // Condicion borde del final
         cant_tts = cant_tweets;
      tag_t* tts_act = cf_trends(contfilt,cant_tts);
      if(!tts_act){
         fprintf(stderr,"Memoria insuficiente\n");
         cf_destruir(contfilt);
         return 3;
      }
      for(size_t i = 0; i < cant_tts; i++)
         printf("%s\n",tts_act[i].nombre);
      free(tts_act);
      cf_limpiar(contfilt);
      printf("---\n");   // Separacion entre TTs
   }
   cf_destruir(contfilt);
   return 0;
}
