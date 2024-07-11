#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_lista_vacia(){
	/*Crear, esta_vacia, destruir*/
	printf("*INICIO PRUEBAS LISTA VACIA \n");
	lista_t* lista = lista_crear();
	print_test("Crear lista vacia", lista != NULL);
	print_test("La lista esta vacia es true", lista_esta_vacia(lista));
	print_test("ver largo de la lista es 0", lista_largo(lista) == 0);
	lista_destruir(lista, NULL);
	print_test("La lista fue destruida", true);
}

void pruebas_insertar_borrar_primero(){
	/* Crear, insertar, borrar_primero, destruir*/
	printf("*INICIO PRUEBAS INSERTAR Y BORRAR PRIMERO \n");
	lista_t* lista2 = lista_crear();
	print_test("Crear lista2", lista2 != NULL);
	int elem = 10; int elem1 = 20;
	print_test("insertar en lista2 es true",lista_insertar_ultimo(lista2,&elem));
	print_test("insertar en lista2 es true",lista_insertar_ultimo(lista2,&elem1));
	print_test("borrar_primero en lista2 me da el elemento",lista_borrar_primero(lista2) == &elem);
	print_test("borrar_primero en lista2 me da el elemento",lista_borrar_primero(lista2) == &elem1);
	lista_destruir(lista2, NULL);
	print_test("Destruir lista2", true);
}
	
void pruebas_ver_primero_ultimo(){
	/* Crear, insertar, ver_primero, ver_ultimo, borrar_primero, destruir*/
	printf("*INICIO PRUEBA VER PRIMERO NO MODIFICA LA LISTA\n");
	lista_t* lista3 = lista_crear();
	print_test("Tenemos lista3", lista3 != NULL);
	int elem = 1, elem1 = 2;
	print_test("insertar en lista3 elemento1", lista_insertar_primero(lista3,&elem));
	print_test("insertar en lista3 elemento2", lista_insertar_ultimo(lista3,&elem1));
	print_test("Ver primero lista3", lista_ver_primero(lista3) == &elem);
	print_test("Ver ultimo lista3", lista_ver_ultimo(lista3) == &elem1);
	print_test("borrar_primero en lista3 elemento2", lista_borrar_primero(lista3) == &elem);
	print_test("Ver primero lista3", lista_ver_primero(lista3) == &elem1);
	print_test("Ver último lista3", lista_ver_ultimo(lista3) == &elem1);
	lista_destruir(lista3, NULL);
	print_test("Destruir lista3", true);
}

void pruebas_cond_borde1(){
		/* Crear, borrar_primero, ver_primero, esta_vacia, destruir*/
		printf("BORRAR_PRIMERO, HASTA QUE ESTA VACIA HACE QUE LA LISTA SE COMPORTE COMO RECIEN CREADA\n");
		lista_t* lista4 = lista_crear();
		print_test("Tenemos lista4", lista4 != NULL);
		print_test("borrar_primero lista4 vacia es NULL", !lista_borrar_primero(lista4));
		print_test("Ver primero en lista4 vacia es NULL", !lista_ver_primero(lista4));
		print_test("lista esta vacia en lista5 es true", lista_esta_vacia(lista4));
		lista_destruir(lista4, NULL);
		print_test("Destruir lista4", true);
}

void pruebas_cond_borde2(){		
		/* Crear, borrar_primero, ver_primerp, destruir*/
		printf("BORRAR_PRIMERO Y VER PRIMERO EN LISTA RECIEN CREADA SON INVALIDAS\n");
		lista_t* lista5 = lista_crear();
		print_test("Crear lista5 ", lista5 != NULL);
		print_test("borrar_primero en lista recien creada es NULL", !lista_borrar_primero(lista5));
		print_test("Ver primerp en lista recien creada es NULL", !lista_ver_primero(lista5));
		lista_destruir(lista5, NULL);
		print_test("Destruir lista5", true);
}

void pruebas_cond_borde3(){
	/* Crear, esta_vacia, destruir*/
	printf("ESTA VACIA EN LISTA RECIEN CREADA ES TRUE\n");
	lista_t* lista6 = lista_crear();
	print_test("Crear lista6 ", lista6 != NULL);
	print_test("Esta vacia en lista recien creada es true", lista_esta_vacia(lista6));	
	lista_destruir(lista6, NULL);
	print_test("Destruir lista6", true);
}

void pruebas_cond_borde4(){
	/* Crear, insertar, borrar_primero, esta_vacia, ver_primerp, destruir*/
	printf("BORRAR_PRIMERO E INSERTAR EN LISTA A LA QUE SE INSERTO Y BORRO HASTA ESTAR VACIA SON INVALIDAS\n");
	lista_t* lista7 = lista_crear();
	print_test("Crear lista7 ", lista7 != NULL);
	char s1[] = "hola", s2[] = "esta", s3[] = "es", s4[] = "una", s5[] = "prueba"; 
	print_test("insertar elem1 en lista7 es true", lista_insertar_primero(lista7,&s3));
	print_test("insertar elem2 en lista7 es true", lista_insertar_primero(lista7,&s2));
	print_test("insertar elem3 en lista7 es true", lista_insertar_primero(lista7,&s1));	
	print_test("insertar elem4 en lista7 es true", lista_insertar_ultimo(lista7,&s4));	
	print_test("insertar elem5 en lista7 es true", lista_insertar_ultimo(lista7,&s5));
	print_test("borrar_primero elem1 en lista7 ", lista_borrar_primero(lista7) == &s1);
	print_test("borrar_primero elem2 en lista7 ", lista_borrar_primero(lista7) == &s2);
	print_test("borrar_primero elem3 en lista7 ", lista_borrar_primero(lista7) == &s3);
	print_test("borrar_primero elem4 en lista7 ", lista_borrar_primero(lista7) == &s4);
	print_test("borrar_primero elem5 en lista7 ", lista_borrar_primero(lista7) == &s5);
	print_test("Esta vacia lista7 es true", lista_esta_vacia(lista7));
	print_test("borrar_primero elem en lista7 es NULL ", !lista_borrar_primero(lista7));
	print_test("Ver primero en lista7 es NULL", !lista_ver_primero(lista7));	
	lista_destruir(lista7, NULL);
	print_test("Destruir lista7", true);	
}	

void pruebas_volumen(){
	/* Crear, insertar, borrar_primero, destruir*/
	printf(" PRUEBA DE VOLUMEN \n");
	lista_t* lista8 = lista_crear();
	print_test("Crear lista8 ", lista8 != NULL);
	int vec[1000];
	for(int i = 0; i < 1000; i++){
		vec[i] = i;
		lista_insertar_primero(lista8,&vec[i]);	
	}
	print_test("ver largo en lista8 es 1000", lista_largo(lista8) == 1000);
	print_test("insertar vector en lista8 es true", true);
	for(int i = 999; i >= 0; i--){
		print_test("borrar_primero Vec en lista8 da los elementos ", lista_borrar_primero(lista8) == &vec[i]);
	}
	print_test("Esta vacia lista8 es true", lista_esta_vacia(lista8));
	lista_destruir(lista8, NULL);
	print_test("Destruir lista8", true);	
}

void pruebas_lista_listas(){
	
	void destruir_p(void* dato){
		lista_t* p = (void*) dato;
		lista_destruir(p,NULL);
	}
	/* Crear lista y listaA, insertar listaA, borrar_primero listaA*/
	lista_t* lista9 = lista_crear();
	print_test("Se creo lista9", lista9 != NULL);
	lista_t* lista9_aux = lista_crear();
	print_test("Se creo lista9_aux", lista9_aux != NULL);
	int vector[10]; int i;
	for(i=0; i<10; i++){
		print_test("insertar en lista9_aux es true", lista_insertar_primero(lista9_aux,&vector[i]));		
	}
	print_test("insertar lista9_aux en lista9 es true", lista_insertar_primero(lista9, lista9_aux));
	print_test("Ver primero en lista9 es lista9_aux", lista_ver_primero(lista9) == lista9_aux);
	print_test("Ver último en lista9 es lista9_aux", lista_ver_ultimo(lista9) == lista9_aux);
	print_test("Ver largo en lista9 es 1", lista_largo(lista9) == 1);
	print_test("borrar_primero en lista9 me da lista9_aux", lista_borrar_primero(lista9) == lista9_aux);
		    
    /* Crear listaB, insertar listaA y listaB, destruir lista*/
    lista_t* lista9_b = lista_crear();
	print_test("Se creo lista9_b", lista9_b != NULL);  
	print_test("insertar  en lista9 es true", lista_insertar_primero(lista9, lista9_aux));
	print_test("insertar en lista9 es true", lista_insertar_ultimo(lista9, lista9_b));	 
	lista_destruir(lista9, destruir_p);
	print_test("Destruir lista9", true);  
	
}

void pruebas_lista_iter(){
	/* Crear lista, crear_iter, destruir lista e iter*/
	printf(" CREAR Y DESTRUIR ITER \n");
	lista_t* lista10 = lista_crear();
	print_test("Crear lista10 ", lista10 != NULL);
	lista_iter_t* iter = lista_iter_crear(lista10);
	print_test("Crear iter ", iter != NULL);
	lista_iter_destruir(iter);
	print_test("Destruir iter", true);	
	lista_destruir(lista10, NULL);
	print_test("Destruir lista10", true);	
}

void pruebas_lista_iterador1(){
	/* insertar con iterador en una lista vacia y no vacia al inicio de lista*/
	/* Crear lista e iter, esta_vacia, iter_insertar,ver_actual, ver_primero, destruir */
	printf(" PRUEBA INSERTAR CON ITER RECIEN CREADO \n");
	lista_t* lista11 = lista_crear();
	print_test("Crear lista11 ", lista11 != NULL);
	lista_iter_t* iter1 = lista_iter_crear(lista11);
	print_test("Crear iter1 ", iter1 != NULL);
	int elem = 100;
	print_test("Ver_actual es NULL", !lista_iter_ver_actual(iter1));
	print_test("Insertar con iter1 elem", lista_iter_insertar(iter1, &elem));
	print_test("Ver_actual es elem", lista_iter_ver_actual(iter1) == &elem);
	print_test("ver_primero en lista11 es &elem ", lista_ver_primero(lista11) == &elem);
	print_test("ver_último en lista11 es &elem ", lista_ver_ultimo(lista11) == &elem);
	print_test("ver largo en lista11 es 1", lista_largo(lista11) == 1);
	int elem1 = 200;
	print_test("Insertar con iter1 elem1", lista_iter_insertar(iter1, &elem1));
	print_test("Ver_actual es elem", lista_iter_ver_actual(iter1) == &elem1);
	print_test("ver_primero en lista11 es &elem ", lista_ver_primero(lista11) == &elem1);
	print_test("ver_último en lista11 es &elem ", lista_ver_ultimo(lista11) == &elem);
	print_test("ver largo en lista11 es 2", lista_largo(lista11) == 2);
	lista_iter_destruir(iter1);
	print_test("Destruir iter1", true);	
	lista_destruir(lista11, NULL);
	print_test("Destruir lista11", true);	
}

void pruebas_lista_iterador2(){
	/* insertar con iterador en una lista vacia y no vacia al final de lista */
	/* Crear lista e iter, iter_insertar,ver_actual, ver_primero y último,largo, destruir*/
	printf(" PRUEBA INSERTAR CON ITER AL FINAL \n");
	lista_t* lista12 = lista_crear();
	print_test("Crear lista12 ", lista12 != NULL);
	lista_iter_t* iter2 = lista_iter_crear(lista12);
	print_test("Crear iter2 ", iter2 != NULL);
	print_test("Iter al final es true  ", lista_iter_al_final(iter2));
	print_test("Ver_actual es NULL", !lista_iter_ver_actual(iter2));
	int elem = 100;
	print_test("Insertar con iter2 elem", lista_iter_insertar(iter2, &elem));
	print_test("Iter al final es false  ", !lista_iter_al_final(iter2));
	print_test("Avanzar con iter2 es true", lista_iter_avanzar(iter2));
	print_test("Iter al final es true  ", lista_iter_al_final(iter2));
	print_test("Ver_actual es NULL", !lista_iter_ver_actual(iter2));
	int elem1 = 200;
	print_test("Insertar con iter2 elem1", lista_iter_insertar(iter2, &elem1));
	print_test("Ver_actual es elem1", lista_iter_ver_actual(iter2) == &elem1);
	print_test("ver_primero en lista12 es &elem ", lista_ver_primero(lista12) == &elem);
	print_test("ver_último en lista12 es &elem1 ", lista_ver_ultimo(lista12) == &elem1);
	print_test("ver largo en lista12 es 2", lista_largo(lista12) == 2);
	lista_iter_destruir(iter2);
	print_test("Destruir iter2", true);	
	lista_destruir(lista12, NULL);
	print_test("Destruir lista12", true);	
}

void pruebas_lista_iterador3(){
	/* insertar con iterador en una lista con tres elementos */
	/* Crear lista e iter, iter_insertar,ver_actual  ver_primero y último,largo, destruir */
	printf(" PRUEBA INSERTAR CON ITER EN EL MEDIO DE LA LISTA \n");
	lista_t* lista13 = lista_crear();
	print_test("Crear lista13 ", lista13 != NULL);
	lista_iter_t* iter3 = lista_iter_crear(lista13);
	print_test("Crear iter3 ", iter3 != NULL);
	int elem = 100, elem1 = 200, elem2 = 300;
	print_test("Insertar con iter3 elem", lista_iter_insertar(iter3, &elem));
	print_test("Insertar con iter3 elem1", lista_iter_insertar(iter3, &elem1));
	print_test("Insertar con iter3 elem2", lista_iter_insertar(iter3, &elem2));
	print_test("ver actual es elem2", lista_iter_ver_actual(iter3) == &elem2);
	print_test("Avanzar con iter es true", lista_iter_avanzar(iter3));
	print_test("ver actual es elem1", lista_iter_ver_actual(iter3) == &elem1);
	print_test("Iter al final es false", !lista_iter_al_final(iter3));
	int elem3 = 400;
	print_test("Insertar con iter3 elem3", lista_iter_insertar(iter3, &elem3));
	print_test("ver primero de lista13 es elem2", lista_ver_primero(lista13) == &elem2);
	print_test("ver último de lista13 es elem", lista_ver_ultimo(lista13) == &elem);
	print_test("ver actual es elem3", lista_iter_ver_actual(iter3) == &elem3);
	print_test("Avanzar con iter es true", lista_iter_avanzar(iter3));
	print_test("Iter al final es false", !lista_iter_al_final(iter3));
	print_test("ver actual es elem1", lista_iter_ver_actual(iter3) == &elem1);
	lista_iter_destruir(iter3);
	print_test("Destruir iter3", true);	
	lista_destruir(lista13, NULL);
	print_test("Destruir lista13", true);	
}

void pruebas_lista_iterador4(){
	/* borrar elemento con iterador recien creado borrar el primer elemento */
	/* Crear lista e iter, iter_insertar,ver_actual, ver_primero y último, borrar, destruir */
	printf(" PRUEBA BORRAR CON ITER RECIEN CREADO \n");
	lista_t* lista14 = lista_crear();
	print_test("Crear lista14 ", lista14 != NULL);
	lista_iter_t* iter4 = lista_iter_crear(lista14);
	print_test("Crear iter4 ", iter4 != NULL);
	print_test("Avanzar en iter4 es false", !lista_iter_avanzar(iter4));
	print_test("Borrar en lista14 es NULL", !lista_iter_borrar(iter4));
	int elem = 100, elem1 = 200;
	print_test("Insertar con iter4 elem", lista_iter_insertar(iter4, &elem));
	print_test("Insertar con iter4 elem1", lista_iter_insertar(iter4, &elem1));
	print_test("ver actual es elem", lista_iter_ver_actual(iter4) == &elem1);
	print_test("ver primero en lista14 es elem1", lista_ver_primero(lista14) == &elem1);
	print_test("ver último en lista14 es elem", lista_ver_ultimo(lista14) == &elem);
	print_test("Borrar en lista14 es elem1", lista_iter_borrar(iter4) == &elem1);
	print_test("ver primero en lista14 es elem", lista_ver_primero(lista14) == &elem);
	print_test("ver último en lista14 es elem", lista_ver_ultimo(lista14) == &elem);
	lista_iter_destruir(iter4);
	print_test("Destruir iter4", true);	
	lista_destruir(lista14, NULL);
	print_test("Destruir lista14", true);	
}

void pruebas_lista_iterador5(){
	/*iterador en el último borrar el último elemento */
	/* Crear lista e iter, iter_insertar,ver_actual  ver_primero y último, borrar, destruir */
	printf(" PRUEBA BORRAR CON ITER EN EL ULTIMO ELEMENTO \n");
	lista_t* lista15 = lista_crear();
	print_test("Crear lista15 ", lista15 != NULL);
	lista_iter_t* iter5 = lista_iter_crear(lista15);
	print_test("Crear iter5 ", iter5 != NULL);
	int elem = 100, elem1 = 200;
	print_test("Insertar con iter5 elem", lista_iter_insertar(iter5, &elem));
	print_test("Insertar con iter5 elem1", lista_iter_insertar(iter5, &elem1));
	print_test("ver primero en lista15 es elem1", lista_ver_primero(lista15) == &elem1);
	print_test("ver último en lista15 es elem", lista_ver_ultimo(lista15) == &elem);
	print_test("Avanzar con iter es true", lista_iter_avanzar(iter5));
	print_test("ver actual es elem", lista_iter_ver_actual(iter5) == &elem);
	print_test("Borrar en iter5 es elem", lista_iter_borrar(iter5) == &elem);
	print_test("ver primero en lista15 es elem", lista_ver_primero(lista15) == &elem1);
	print_test("ver último en lista15 es elem", lista_ver_ultimo(lista15) == &elem1);
	print_test("ver actual es NULL", !lista_iter_ver_actual(iter5));
	print_test("iter al final es true", lista_iter_al_final(iter5));
	print_test("Borrar en iter5 es NULL", !lista_iter_borrar(iter5));
	lista_iter_destruir(iter5);
	print_test("Destruir iter5", true);	
	lista_destruir(lista15, NULL);
	print_test("Destruir lista15", true);	
}

void pruebas_lista_iterador6(){
	/*iterador en el medio borrar el elemento correcto */
	/* Crear lista e iter, iter_insertar,ver_actual  ver_primero y último, borrar, destruir */
	printf(" PRUEBA BORRAR CON ITER EN EL MEDIO DE LISTA \n");
	lista_t* lista16 = lista_crear();
	print_test("Crear lista16 ", lista16 != NULL);
	lista_iter_t* iter6 = lista_iter_crear(lista16);
	print_test("Crear iter6 ", iter6 != NULL);
	int elem = 100, elem1 = 200, elem2 = 300;
	print_test("Insertar con iter6 elem", lista_iter_insertar(iter6, &elem));
	print_test("Insertar con iter6 elem1", lista_iter_insertar(iter6, &elem1));
	print_test("Insertar con iter6 elem2", lista_iter_insertar(iter6, &elem2));
	print_test("ver primero en lista16 es elem2", lista_ver_primero(lista16) == &elem2);
	print_test("ver último en lista16 es elem", lista_ver_ultimo(lista16) == &elem);
	print_test("Avanzar con iter es true", lista_iter_avanzar(iter6));
	print_test("ver actual es elem1", lista_iter_ver_actual(iter6) == &elem1);
	print_test("Borrar en iter6 es elem1", lista_iter_borrar(iter6) == &elem1);
	print_test("ver primero en lista16 es elem2", lista_ver_primero(lista16) == &elem2);
	print_test("ver último en lista16 es elem", lista_ver_ultimo(lista16) == &elem);
	print_test("ver actual es elem", lista_iter_ver_actual(iter6) == &elem);
	print_test("iter al final es false", !lista_iter_al_final(iter6));
	print_test("Borrar en iter6 es elem", lista_iter_borrar(iter6) == &elem);
	lista_iter_destruir(iter6);
	print_test("Destruir iter6", true);	
	lista_destruir(lista16, NULL);
	print_test("Destruir lista16", true);	
}

void pruebas_lista_iterador7(){
	/* Iterar sin/con corte*/
	/* Definición de sumar_elem... y extra*/
	bool sumar_elementos(void *dato, void *extra){
		*(int*)extra += *(int*)dato;
		printf("%d, ",*(int*)dato);
		return true; 
	}
	bool imprimir_cinco_elementos(void *dato, void *extra){
		if(*(int*)extra >= 5){
			return false;
		}
		*(int*)extra += 1; // si dejo:*(int*)extra++; me devuelve value computed is not used
		printf("%d ",*(int*)dato);
		return true; 
	}
	int suma_total = 0;
	int contador_elementos = 0;
	/* Crear lista e iter, iter_insertar, iterar, destruir */
	printf(" PRUEBA ITERAR SIN/CON CORTE \n");
	lista_t* lista17 = lista_crear();
	print_test("Crear lista17 ", lista17 != NULL);
	lista_iter_t* iter7 = lista_iter_crear(lista17);
	print_test("Crear iter7 ", iter7 != NULL);
	int vector[10];
	for(int i = 0; i < 10; i++){
		vector[i] = i; 
		print_test("insertar elementos es true",lista_iter_insertar(iter7, &vector[i]));
	}
	lista_iterar(lista17, sumar_elementos, &suma_total);
	printf("%i\n", suma_total);
	lista_iterar(lista17, imprimir_cinco_elementos, &contador_elementos);
	lista_iter_destruir(iter7);
	print_test("Destruir iter7", true);	
	lista_destruir(lista17, NULL);
	print_test("Destruir lista17", true);	
}

void pruebas_lista_alumno() {
	pruebas_lista_vacia();
	pruebas_insertar_borrar_primero();
	pruebas_ver_primero_ultimo();
	pruebas_cond_borde1();
	pruebas_cond_borde2();
	pruebas_cond_borde3();
	pruebas_cond_borde4();
	pruebas_volumen();
	pruebas_lista_listas();
	pruebas_lista_iter();
	pruebas_lista_iterador1();
	pruebas_lista_iterador2();
	pruebas_lista_iterador3();
	pruebas_lista_iterador4();
	pruebas_lista_iterador5();
	pruebas_lista_iterador6();
	pruebas_lista_iterador7();
}
