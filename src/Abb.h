/*
 * Abb.h
 *
 *  Created on: 14/09/2012
 *      Author: Andres Sanabria
 */

#ifndef ABB_H_
#define ABB_H_

#include "NodoArbol.h"

class Abb {
public:
	Abb();
	~Abb();
	void agregarPalabra(string palabra,unsigned documento);
	void escribirEnArchivo(const string& nombre);
	unsigned getCantidad();

private:
	NodoArbol* raiz;
	unsigned cantidad;
	void destruir();
	void escribirEnOrden(NodoArbol* nodo,fstream & archivo);
	void destruir(NodoArbol * nodo);
	void posicionarPunteros(const string clave,NodoArbol* &nodo,NodoArbol* & nodo_padre);
};

#endif /* ABB_H_ */
