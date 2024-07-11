class Nodo_heap(object):
	
	def __init__(self,clave,valor):
		self.dato = (clave,valor)
	
	def obtener_valor():
		return dato
		
	def __cmp__(self, other):
		
		if self.dato[1]<other.dato[1] : return 1
		if self.dato[1]>other.dato[1]: return -1
		
		return 0
		
	def __str__(self):
		return str(self.dato)
		
	def __repr__(self):
		return str(self.dato[0])
