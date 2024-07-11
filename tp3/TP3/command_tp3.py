import grafo
import hashlib
import heapq
import heap_max
import random
import bfs
import math


""" ==================== """
""" FUNCIONES AUXILIARES """
""" ==================== """

"""Devuelve la cantidad de aristas totales del grafo"""
def cant_aristas(grafo):
	
	cant = 0
	
	for v in grafo:
		cant += len(grafo.vertices_adyacentes(v))
		
	return cant / 2 

"""Dado un vertice devuelve un diccionario con la cantidad de apariciones de n randomwalks""" 
def max_apariciones(grafo, vertice, n):
	
	res = {}
	
	for i in range (0, n):
		camino = grafo.randwalk(vertice,n)
		
		for v in camino:
			if (res.get(v, None) != None) and (v != vertice):
				res[v] += 1
			else: 
				res[v] = 1
	return res

"""Dado un diccionario devuelve los n elementos mayores de los mismos en O(klog(n))"""
def nmayores(dicc,n):
	
	heap = []
	
	for clave,valor in dicc.iteritems():
		heap.append(heap_max.Nodo_heap(clave, valor))
	heapq.heapify(heap)
	
	n_mayores = heapq.nsmallest(n, heap)
	return n_mayores

"""Dados dos diccionarios los mergea en uno solo"""
def merge_dicts(x, y):
	
    z = x.copy()
    z.update(y)
    return z

"""Funcion auxiliar para determinar las labels de los vertices con sus adyacentes"""
def max_label(labels, adyacentes):
	
	label_ady = {}
	
	for vertice in adyacentes:
		if label_ady.get(labels[vertice],None) != None:
			label_ady[labels[vertice]] += 1
		else:
			label_ady[labels[vertice]] = 1
			
	clave_valor = (None, 0)
	
	for clave,valor in label_ady.iteritems():
		if valor > clave_valor[1]:
			clave_valor = (clave,valor)
	return clave_valor[0]

""" ======== """
""" COMANDOS """
""" ======== """

"""Dado un vertice devuelve los n vertices mas similares"""
"""Pre: El grafo fue cargado"""
"""Post: Devuelve la lista similares, o una lista vacia si el vertice no pertenece al grafo"""
def similares(grafo, vertice, n):
	
	if not grafo.existe_vertice(vertice):
		print "El vertices no pertenece al grafo"
		return []
		
	max_aparecidos = max_apariciones(grafo, vertice, n + len(grafo.vertices_adyacentes(vertice)))
	return nmayores(max_aparecidos, n)

"""Dado un vertice devuelve los n vertices mas similares que no son adyacentes al ingresado """
"""Pre: El grafo fue cargado"""
"""Post: Devuelve lista recomendada, o una lista vacia si el vertice no pertenece al grafo"""
def recomendar(grafo, vertice, n):
	
	if not grafo.existe_vertice(vertice):
		print "El vertice no pertenece al grafo"
		return []
		
	max_aparecidos = max_apariciones(grafo, vertice, n + len(grafo.vertices_adyacentes(vertice)))
	
	for v in grafo.vertices_adyacentes(vertice):
		if max_aparecidos.get(v, None) != None:
			max_aparecidos.pop(v)
			
	return nmayores(max_aparecidos, n)

"""Devuelve una lista con el camino minimo de coneccion entre dos vertices"""
"""Pre: El grafo fue cargado"""
"""Post: Devuelve la lista camino, o una lista vacia si el/los vertice/s no pertenece/n al grafo o si el/los vertices no se pueden conectar"""
def camino(grafo, origen, destino):
	
	if not grafo.existe_vertice(origen) or not grafo.existe_vertice(destino):
		print "La/s ID/s no pertenece/n al grafo"
		return []
		
	padre_orden = bfs.bfs(grafo, origen)
	camino = []
	camino.append(destino)
	
	if padre_orden[0].get(destino, None) == None:
		return []
		
	v_act = padre_orden[0][destino]
	camino.append(v_act)
	
	while v_act != origen and v_act != None:
		v_act = padre_orden[0][v_act]
		camino.append(v_act)
		
	camino.reverse()
	return camino

"""Realiza caminos entre todos los vertices y devuelve los vertices que mas aparecieron"""
"""Pre: El grafo fue cargado"""
def centralidad_exacta(grafo, n):
	hash_aux = {}
	
	for vertice in grafo:
		
		for v in grafo:
			camino_act = camino(grafo, vertice, v)
			
			for i in range(1, len(camino_act)-2):
				if hash_aux.get(camino_act[i],None) == None:
					hash_aux[camino_act[i]] = 0
					
				hash_aux[camino_act[i]] += 1
				
	return nmayores(hash_aux, n)

"""Realiza muchos random walks de mucha longitud y devuelve los vertices que mas aparecieron"""
"""Pre: El grafo fue cargado"""
def centralidad(grafo,n):
	
	res = {}
	cant_caminos = long_caminos = int(math.sqrt(grafo.cant_vertices()))
	
	for i in range(0, cant_caminos):
		max_aparecidos = max_apariciones(grafo, random.choice(grafo.vertices()), long_caminos)
		res = merge_dicts(res,max_aparecidos)

	return nmayores(res, n)

"""Dado un vertice devuelve la cantidad de vertices que hay a todas sus distancias"""
"""Pre: El grafo fue cargado"""
"""Post: Devuelve la lista distancias, o una lista vacia si el vertice no pertenece al grafo"""
def distancia(grafo, vertice):
	
	if not grafo.existe_vertice(vertice):
		print "La ID no pertenece al grafo"
		return {}
		
	origen_distancia = bfs.bfs(grafo, vertice)
	distancia = {}
	
	for clave,valor in origen_distancia[1].iteritems():
		
		if(not valor in distancia.keys()):
			distancia[valor] = 0
		distancia[valor] += 1
		
	lista = []
	
	for clave,valor in distancia.iteritems():
		lista.append((clave,valor))
	
	for i in range(1, len(lista)):
		print 'Distancia', lista[i]

"""Devuelve las estadisticas del grafo"""
"""Pre: El grafo fue cargado"""
def estadisticas(grafo):
	
	aristas = cant_aristas(grafo)
	print "Cantidad de vertices: ", grafo.cant_vertices()
	print "Cantidad de aristas: ", aristas
	print "Promedio de grado de cada vertice: ", float(grafo.cant_vertices()) / aristas
	print "Densidad del grafo: ", float(aristas) / (grafo.cant_vertices() - 1)


"""Utilizando label propagation devuelve una parte de las comunidades del grafo"""
"""Pre: El grafo fue cargado"""
def comunidades(grafo):
	
	labels = {}
	
	for vertice in grafo:
		labels[vertice] = vertice
	lista_claves = labels.keys()
	
	for iter in range(0,5):
		random.shuffle(lista_claves)
		
		for clave in lista_claves:
			labels[clave] = max_label(labels, grafo.vertices_adyacentes(clave))
	
	lista_comunidades = {}
	
	for clave,valor in labels.iteritems():
		
		if lista_comunidades.get(valor, None) == None:
			lista_comunidades[valor] = []	
		lista_comunidades[valor].append(clave)
		
	contador = 0
	
	for clave,valor in lista_comunidades.iteritems():
		if len(valor) > 4 and len(valor) < 2000:
			print 'Comunidad:', clave
			print 'Cantidad de integrantes:', len(valor)
			print 'Integrantes:',valor
			contador += 1
		
