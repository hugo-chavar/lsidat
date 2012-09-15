/*
 * NodoArbol.h
 *
 *  Created on: Sep 14, 2012
 *      Author: andy
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
	Palabra getPalabra();
	int CompararCon(string clave);// Devuelve -1 si la clave del nodo es menor, 0 si son iguales y 1 si la clave es mayor.

private:
		Palabra* dato;
		NodoArbol *izquierdo;
		NodoArbol *derecho;
};

#endif /* NODOARBOL_H_ */
