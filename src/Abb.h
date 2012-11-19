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
	void borrar(const string clave);
	void escribirEnArchivo(const string& nombre);
	unsigned getCantidad();

private:
	NodoArbol* raiz;
	unsigned cantidad;
	void destruir();
	void escribirEnOrden(NodoArbol* nodo,fstream & archivo);
};

#endif /* ABB_H_ */
