#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_cola_unElem(){
	/* Crear, encolar, destruir*/
	cola_t* cola = cola_crear();
	int elem = 7;
	print_test("Se creo cola", cola != NULL);
	print_test("Encolar en cola es true", cola_encolar(cola,&elem) == true);
	cola_destruir(cola, NULL);
	print_test("Destruir cola", true);
}
void pruebas_cola_crear_destruir(){
	/* Crear, destruir en cola*/
	cola_t* cola1 = cola_crear();
	print_test("Se creo cola1", cola1 != NULL);
	cola_destruir(cola1, NULL);
	print_test("Destruir cola1", true);
}
void pruebas_cola_encolar_desencolar(){
	/* Crear, esta_vacia, encolar, desencolar, destruir en cola*/
	cola_t* cola2 = cola_crear();
	print_test("Se creo cola2", cola2 != NULL);
	print_test("La cola2 esta vacia es true", cola_esta_vacia(cola2) == true);	
	
	int vector[100]; int i;
	for(i=0; i<100; i++){
		print_test("Encolar en cola2 es true", cola_encolar(cola2,&vector[i]) == true);		
	}
	for(i=0; i<100; i++){
		print_test("Desencolar en cola2 me da el elemento", cola_desencolar(cola2) == &vector[i]);		
	}
    cola_destruir(cola2, NULL);
    print_test("Destruir cola2", true);
}
void pruebas_cola_vacia(){
	/* Crear, esta_vacia, ver_primero, encolar, desencolar, destruir */
	cola_t* cola3 = cola_crear();
	print_test("Se creo cola3", cola3 != NULL);
	print_test("La cola3 esta vacia es true", cola_esta_vacia(cola3) == true);
	print_test("Ver primero en cola3 es NULL", cola_ver_primero(cola3) == NULL);
	print_test("Desencolar en cola3 es NULL", cola_desencolar(cola3) == NULL);
	
	int vector[100]; int i;
	for(i=0; i<99; i++){
		print_test("Encolar en cola3 es true", cola_encolar(cola3,&vector[i]) == true);		
	}
	print_test("Ver primero en cola3 es vector[0]", cola_ver_primero(cola3) == &vector[0]);
	print_test("La cola3 esta vacia es false", cola_esta_vacia(cola3) == false);	
    cola_destruir(cola3, NULL);
    print_test("Destruir cola3", true);
}
void pruebas_cola_colas(){
	
	void destruir_p(void* dato){
		cola_t* p = (void*) dato;
		cola_destruir(p,NULL);
	}
	/* Crear cola y colaA, encolar colaA, desencolar colaA*/
	cola_t* cola4 = cola_crear();
	print_test("Se creo cola4", cola4 != NULL);
	cola_t* cola4a = cola_crear();
	print_test("Se creo cola4a", cola4a != NULL);
	int vector[10]; int i;
	for(i=0; i<10; i++){
		print_test("Encolar en cola5 es true", cola_encolar(cola4a,&vector[i]) == true);		
	}
	print_test("Encolar cola5 en cola4 es true", cola_encolar(cola4, cola4a) == true);
	print_test("Ver primero en cola4 es cola4a", cola_ver_primero(cola4) == cola4a);
	print_test("Desencolar en cola4 me da cola4a", cola_desencolar(cola4) == cola4a);
		    
    /* Crear colaB, encolar colaA y colaB, destruir cola*/
    cola_t* cola4b = cola_crear();
	print_test("Se creo cola4b", cola4b != NULL);  
	print_test("Encolar  en cola4 es true", cola_encolar(cola4, cola4a) == true);
	print_test("Encolar en cola4 es true", cola_encolar(cola4, cola4b) == true);	 
	cola_destruir(cola4, destruir_p);
	print_test("Destruir cola4", true);  
	
}
void pruebas_cola_alumno() { 
	pruebas_cola_unElem();
	pruebas_cola_crear_destruir();
	pruebas_cola_encolar_desencolar();
	pruebas_cola_vacia();
	pruebas_cola_colas();
}
