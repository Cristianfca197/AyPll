import hashlib
import random
	
class Grafo (object):
	
	def __init__(self):
		self.hash={}
	
	def agregar_vertice(self, clave):
		
		self.hash[clave] = {}
		return True
		
	def quitar_vertice(self, vertice):
		
		if self.hash.get(vertice,None) != None:
			adya_ver_act = self.vertices_adyacentes(vertice)
			for w in adya_ver_act:
				self.quitar_arista(vertice,w)
			del self.hash[vertice]
			return True
		
		return False
	
	def agregar_arista(self, vertice_a, vertice_b):
		
		if (self.hash.get(vertice_a,None) and self.hash.get(vertice_b,None)) != None:
			self.hash[vertice_a][vertice_b] = vertice_b
			self.hash[vertice_b][vertice_a] = vertice_a
			return True
		
		return False
			
	def quitar_arista(self, vertice_a, vertice_b): 
		
		if self.son_adyacentes(vertice_a, vertice_b):
			del self.hash[vertice_a][vertice_b]
			del self.hash[vertice_b][vertice_a]
			return True
		
		return False
		
	def son_adyacentes(self, vertice_a, vertice_b):
		
		if self.existe_vertice(vertice_a) and self.existe_vertice(vertice_b):
			if (self.hash[vertice_a].get(vertice_b, None) and self.hash[vertice_b].get(vertice_a, None)) != None:
				return True
		return False	
		
	def vertices_adyacentes(self, vertice):
		
		if self.hash.get(vertice, None) != None:
			return self.hash[vertice].keys()
		
		return False
		
	def existe_vertice(self, vertice):
		
		if self.hash.get(vertice, None) != None:
			return True
		return False
	
	def vertices(self):
		return self.hash.keys()
	
	def cant_vertices(self):
		return len(self.hash)
	
	def __iter__(self):
		return iter(self.hash)
		
	def randwalk(self, vertice, n):
		
		siguiente = vertice
		camino =[]
		
		while n != 0:
			siguiente = random.choice(self.vertices_adyacentes(siguiente))
			camino.append(siguiente)
			n -= 1
			
		return camino

'''
def pruebas_grafo_vacio():
	print "PRUENAS GRAFO VACIO"
	grafo = Grafo()
	print "Se creo grafo vacio:", grafo
	print "Quitar vertice'hola' es false:", grafo.quitar_vertice('hola')
	print "Agregar arista'gato'-'perro' es falso:", grafo.agregar_arista('gato', 'perro')
	print "Quitar arista'azul'-'rojo' es:", grafo.quitar_arista('azul', 'rojo')
	print "Son adyacentes 'perro'-'gato' es false:", grafo.son_adyacentes('perro','gato')
	print "Vertice Adyacentes'cono' es:",grafo.vertices_adyacentes('cono')
	print "Existe vertice 'gato' es false:", grafo.existe_vertice('gato')
	print "Vertices Grafo es:", grafo.vertices_grafo()
	print "Cant de vertices es 0:", grafo.cant_vertices() == 0


def pruebas_grafo_agregar():
	print "\nPRUEBAS GRAFO AGREGAR"
	grafo_ag = Grafo()
	print "Agregar vertice'perro' es true:", grafo_ag.agregar_vertice('perro')
	print "Agregar vertice'gato' es true:", grafo_ag.agregar_vertice('gato')
	print "Cant de vertices es 2:", grafo_ag.cant_vertices() == 2
	print "Vertices Grafo es none :", grafo_ag.vertices_grafo()
	print "Agregar arista'perro'-'gato' es true:", grafo_ag.agregar_arista('perro', 'gato')
	print "Son adyacentes 'perro'-'gato' es true:", grafo_ag.son_adyacentes('perro','gato')
	print "Vertice Adyacentes'perro' es:",grafo_ag.vertices_adyacentes('perro')
	print "Vertice Adyacentes'gato' es:",grafo_ag.vertices_adyacentes('gato')
	print "Quitar vertice'perro' es true:", grafo_ag.quitar_vertice('perro')
	print "Cant de vertices es 1:", grafo_ag.cant_vertices() == 1
	print "Existe vertice 'perro' es false:", grafo_ag.existe_vertice('perro')
	print "Son adyacentes 'perro'-'gato' es false:", grafo_ag.son_adyacentes('perro','gato')
	print "Vertices Grafo es gato :", grafo_ag.vertices_grafo()

pruebas_grafo_vacio()
pruebas_grafo_agregar()
'''
