import sys
import grafo
import command_tp3
import heapq
import heap_max

if len(sys.argv) != 2:
	print "Numero de parametros invalido"

print "Cargando grafo"

grafo = grafo.Grafo()
with open(sys.argv[1], 'r') as archivo:
	
	with open('informacion.txt', 'w') as info:
		for x in range(0, 4):
			info.write(archivo.readline())
	
	for linea in archivo:

		arr = linea.split()
		if len(arr) == 2:
			
			if(not grafo.existe_vertice(arr[0])):
				grafo.agregar_vertice(arr[0])
				
			if(not grafo.existe_vertice(arr[1])):
				grafo.agregar_vertice(arr[1])
				
			grafo.agregar_arista(arr[0],arr[1])

print "Grafo cargado"
print "Ingrese accion, o \"salir\" para salir"
entrada = raw_input(">")

while(entrada != "salir"):
	comando = entrada.split(" ")
	if comando[0] == "similares" and len(comando) > 2:
		print command_tp3.similares(grafo,comando[1],int(comando[2]))
	elif comando[0] == "recomendar" and len(comando) > 2:
		print command_tp3.recomendar(grafo,comando[1], int(comando[2]))
	elif comando[0] == "camino" and len(comando) > 2:
		print command_tp3.camino(grafo,comando[1],comando[2])
	elif comando[0] == "centralidad" and len(comando) > 1:
		print command_tp3.centralidad(grafo,int(comando[1]))
	elif comando[0] == "centralidad_exacta" and len(comando) > 1:
		print command_tp3.centralidad_exacta(grafo,int(comando[1]))
	elif comando[0] == "distancia" and len(comando) > 1:
		command_tp3.distancia(grafo,comando[1])
	elif comando[0] == "estadisticas":
		command_tp3.estadisticas(grafo)
	elif comando[0] == "comunidades":
		command_tp3.comunidades(grafo)
	else:
		print "Comando incorrecto"
	entrada = raw_input(">")

print "Adios!"
