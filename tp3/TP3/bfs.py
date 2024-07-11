import heapq
import heap_max
import grafo


def bfs(grafo, vertice):
	
	visitados = {}
	padre = {}
	orden = {}
	
	padre[vertice] = None
	orden[vertice] = 0
	bfs_visitar(grafo, vertice, visitados, padre, orden)
	
	return (padre,orden)
	
def bfs_visitar(grafo, origen, visitados, padre, orden):
	
	heap = [origen]
	visitados[origen] = True
	
	while len(heap) > 0:
		v = heapq.heappop(heap)
		
		for w in grafo.vertices_adyacentes(v):
			if w not in visitados:
				visitados[w] = True
				padre[w] = v
				orden[w] = orden[v] + 1
				heapq.heappush(heap, w)
