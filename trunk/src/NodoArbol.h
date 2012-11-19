/*
 * NodoArbol.h
 *
 *  Created on: 14/09/2012
 *      Author: Andres Sanabria
 */

#ifndef NODOARBOL_H_
#define NODOARBOL_H_

#include "Palabra.h"

class NodoArbol {
public:
	NodoArbol(string palabra);
	~NodoArbol();
	NodoArbol* getIzquierdo();
	NodoArbol* getDerecho();
	void setIzquierdo(NodoArbol* izq);
	void setDerecho(NodoArbol* der);
	Palabra* getPalabra();

private:
		Palabra* dato;
		NodoArbol *izquierdo;
		NodoArbol *derecho;
};

#endif /* NODOARBOL_H_ */
