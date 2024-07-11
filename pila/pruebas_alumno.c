#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
void pruebas_pila_vacia(){
	/*Crear, esta_vacia, destruir*/
	printf("*INICIO PRUEBAS PILA VACIA \n");
	pila_t* pila = pila_crear();
	print_test("Crear pila vacia", pila != NULL);
	print_test("La pila esta vacia es true", pila_esta_vacia(pila));
	pila_destruir(pila);
	print_test("La pila fue destruida", true);
}

void pruebas_apilar_desapilar(){
	/* Crear, apilar, desapilar, destruir*/
	printf("*INICIO PRUEBAS APILAR Y DESAPILAR \n");
	pila_t* pila2 = pila_crear();
	print_test("Crear pila2", pila2 != NULL);
	int elem = 10; int elem1 = 20;
	print_test("Apilar en pila2 es true",pila_apilar(pila2,&elem));
	print_test("Apilar en pila2 es true",pila_apilar(pila2,&elem1));
	print_test("Desapilar en pila2 me da el elemento",pila_desapilar(pila2) == &elem1);
	print_test("Desapilar en pila2 me da el elemento",pila_desapilar(pila2) == &elem);
	pila_destruir(pila2);
	print_test("Destruir pila2", true);
}
	
void pruebas_ver_tope(){
	/* Crear, apilar, ver_tope, desapilar, destruir*/
	printf("*INICIO PRUEBA VER TOPE NO MODIFICA LA PILA\n");
	pila_t* pila3 = pila_crear();
	print_test("Tenemos pila3", pila3 != NULL);
	int elem = 1, elem1 = 2;
	print_test("Apilar en pila3 elemento1", pila_apilar(pila3,&elem));
	print_test("Apilar en pila3 elemento2", pila_apilar(pila3,&elem1));
	print_test("Ver tope pila3", pila_ver_tope(pila3) == &elem1);
	print_test("Desapilar en pila3 elemento2", pila_desapilar(pila3) == &elem1);
	print_test("Ver tope pila3", pila_ver_tope(pila3) == &elem);
	pila_destruir(pila3);
	print_test("Destruir pila3", true);
}

void pruebas_redimension(){
	/* Crear, apilar, desapilar, ver_tope, destuir*/
	printf("*INICIO PRUEBA REDIMENSION FUNCIONA Y DESAPILAR\n");
	pila_t* pila4 = pila_crear();
	print_test("Tenemos pila4", pila4 != NULL);	
	int elem1 = 0, elem2 = 20, elem3 = 30, elem4 = 40, elem5 = 50;
	print_test("Apilar elemento 1",pila_apilar(pila4,&elem1));
	print_test("Apilar elemento 2",pila_apilar(pila4,&elem2));	
	print_test("Apilar elemento 3",pila_apilar(pila4,&elem3));	    
	print_test("Apilar elemento 4",pila_apilar(pila4,&elem4));
	print_test("Apilar elemento 5",pila_apilar(pila4,&elem5));
	print_test("Desapilar en pila4 elemento5", pila_desapilar(pila4) == &elem5);
	print_test("Desapilar en pila4 elemento4", pila_desapilar(pila4) == &elem4);
	print_test("Desapilar en pila4 elemento3", pila_desapilar(pila4) == &elem3);
	print_test("Desapilar en pila4 elemento2", pila_desapilar(pila4) == &elem2);
	print_test("Desapilar en pila4 elemento1", pila_desapilar(pila4) == &elem1);
	print_test("Desapilar en pila4 (vacia) es NULL", !pila_desapilar(pila4));
	print_test("Ver tope en pila4 (vacia) es NULL", !pila_ver_tope(pila4));
	pila_destruir(pila4);
	print_test("Destruir pila4", true);
}

void pruebas_cond_borde1(){
		/* Crear, desapilar, ver_tope, esta_vacia, destruir*/
		printf("DESAPILAR HASTA QUE ESTA VACIA HACE QUE LA PILA SE COMPORTE COMO RECIEN CREADA\n");
		pila_t* pila5 = pila_crear();
		print_test("Tenemos pila5", pila5 != NULL);
		print_test("Desapilar pila5 vacia es NULL", !pila_desapilar(pila5));
		print_test("Ver tope en pila5 vacia es NULL", !pila_ver_tope(pila5));
		print_test("Pila esta vacia en pila5 es true", pila_esta_vacia(pila5));
		pila_destruir(pila5);
		print_test("Destruir pila5", true);
}

void pruebas_cond_borde2(){		
		/* Crear, desapilar, ver_tope, destruir*/
		printf("DESAPILAR Y VER TOPE EN PILA RECIEN CREADA SON INVALIDAS\n");
		pila_t* pila6 = pila_crear();
		print_test("Crear pila6 ", pila6 != NULL);
		print_test("Desapilar en pila recien creada es NULL", !pila_desapilar(pila6));
		print_test("Ver tope en pila recien creada es NULL", !pila_ver_tope(pila6));
		pila_destruir(pila6);
		print_test("Destruir pila6", true);
}

void pruebas_cond_borde3(){
	/* Crear, esta_vacia, destruir*/
	printf("ESTA VACIA EN PILA RECIEN CREADA ES TRUE\n");
	pila_t* pila7 = pila_crear();
	print_test("Crear pila7 ", pila7 != NULL);
	print_test("Esta vacia en pila recien creada es true", pila_esta_vacia(pila7));	
	pila_destruir(pila7);
	print_test("Destruir pila7", true);
}

void pruebas_cond_borde4(){
	/* Crear, apilar, desapilar, esta_vacia, ver_tope, destruir*/
	printf("DESPILAR Y APILAR EN PILA A LA QUE SE APILO Y DESAPILO HASTA ESTAR VACIA SON INVALIDAS\n");
	pila_t* pila8 = pila_crear();
	print_test("Crear pila8 ", pila8 != NULL);
	char s1[] = "hola", s2[] = "esta", s3[] = "es", s4[] = "una", s5[] = "prueba"; 
	print_test("Apilar elem1 en pila 8 es true", pila_apilar(pila8,&s1));
	print_test("Apilar elem2 en pila 8 es true", pila_apilar(pila8,&s2));
	print_test("Apilar elem3 en pila 8 es true", pila_apilar(pila8,&s3));	
	print_test("Apilar elem4 en pila 8 es true", pila_apilar(pila8,&s4));	
	print_test("Apilar elem5 en pila 8 es true", pila_apilar(pila8,&s5));
	print_test("Desapilar elem en pila8 ", pila_desapilar(pila8) == &s5);
	print_test("Desapilar elem en pila8 ", pila_desapilar(pila8) == &s4);
	print_test("Desapilar elem en pila8 ", pila_desapilar(pila8) == &s3);
	print_test("Desapilar elem en pila8 ", pila_desapilar(pila8) == &s2);
	print_test("Desapilar elem en pila8 ", pila_desapilar(pila8) == &s1);
	print_test("Esta vacia pila8 es true", pila_esta_vacia(pila8));
	print_test("Desapilar elem en pila8 es NULL ", !pila_desapilar(pila8));
	print_test("Ver tope en pila8 es NULL", !pila_ver_tope(pila8));	
	pila_destruir(pila8);
	print_test("Destruir pila8", true);	
}	

void pruebas_volumen(){
	/* Crear, apilar, desapilar, destruir*/
	printf(" PRUEBA DE VOLUMEN \n");
	pila_t* pila9 = pila_crear();
	print_test("Crear pila9 ", pila9 != NULL);
	int vec[1000];
	for(int i = 0; i < 1000; i++){
		vec[i] = i;
		pila_apilar(pila9,&vec[i]);	
	}
	print_test("Apilar vector en pila 9 es true", true);
	for(int i = 999; i >= 0; i--){
		print_test("Desapilar Vec en pila9 da los elementos ", pila_desapilar(pila9) == &vec[i]);
	}
	print_test("Esta vacia pila9 es true", pila_esta_vacia(pila9));
	pila_destruir(pila9);
	print_test("Destruir pila9", true);	
}

void pruebas_memoria_dinamica(){
	/* Crear pila10 y pilasAux, apilar pilasAux, ver_tope, desapilar pilasAux, destruir*/
	printf(" PRUEBA DE MEMORIA DINAMICA \n");
	pila_t* pila10 = pila_crear();
	print_test("Crear pila10 ", pila10 != NULL);
	pila_t* vec[5];
	for(int i = 0; i < 5; i++){
		vec[i] = pila_crear();
		print_test("Apilar pilas en pila 10 es true", pila_apilar(pila10,&vec[i]));
	}
	print_test("Ver tope en pila10 es vec[4]", pila_ver_tope(pila10) == &vec[4]);
	for(int i = 4; i >= 0; i--){
		print_test("Desapilar Vec en pila10 da las pilas ", pila_desapilar(pila10) == &vec[i]);
		pila_destruir(vec[i]);
		print_test("Destruir pilaAux", true);	
	}	
	print_test("Esta vacia pila10 es true", pila_esta_vacia(pila10));
	pila_destruir(pila10);
	print_test("Destruir pila10", true);	
}

void pruebas_pila_alumno() {
	pruebas_pila_vacia();
	pruebas_apilar_desapilar();
	pruebas_ver_tope();
	pruebas_redimension();
	pruebas_cond_borde1();
	pruebas_cond_borde2();
	pruebas_cond_borde3();
	pruebas_cond_borde4();
	pruebas_volumen();
	pruebas_memoria_dinamica();
}
