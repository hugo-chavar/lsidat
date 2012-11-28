/*
 * Abb.cpp
 *
 *  Created on: 14/09/2012
 *      Author: Andres Sanabria
 */

#include "Abb.h"
#include <iostream>
#include <fstream>

Abb::Abb() {
	this->raiz = NULL;
	this->cantidad = 0;
}

Abb::~Abb() {
	this->destruir();
}

unsigned Abb::getCantidad() {
	return this->cantidad;
}

void Abb::agregarPalabra(string palabra, unsigned documento) {
	NodoArbol *nodo = this->raiz;
	NodoArbol *nodo_padre = NULL;
	posicionarPunteros(palabra,nodo,nodo_padre);
	if (!nodo) {
		nodo = new NodoArbol(palabra);
		nodo->getPalabra()->agregarAparicion(documento);
		if (nodo_padre) {
			if ((nodo->getPalabra()->compararCon(
					nodo_padre->getPalabra()->getContenido())) > 0)
				nodo_padre->setDerecho(nodo);
			else
				nodo_padre->setIzquierdo(nodo);
		} else
			this->raiz = nodo;
		this->cantidad++;
	} else {
		nodo->getPalabra()->agregarAparicion(documento);
	}
}

void Abb::posicionarPunteros(const string clave,NodoArbol* &nodo,NodoArbol* &nodo_padre){

	while (nodo && ((nodo->getPalabra()->compararCon(clave)) != 0)) // Devuelve -1 si la clave es menor, 0 si son iguales y 1 si la clave es mayor.
		{
			nodo_padre = nodo;
			if ((nodo->getPalabra()->compararCon(clave)) > 0)
				nodo = nodo->getIzquierdo();
			else
				nodo = nodo->getDerecho();
		}
}

void Abb::destruir() {

	destruir(this->raiz);

}

void Abb::destruir(NodoArbol * nodo)
{
if (nodo!=0)
{
destruir(nodo->getIzquierdo());
destruir(nodo->getDerecho());
delete nodo;
}
}


void Abb::escribirEnArchivo(const string& nombre) {
	std::fstream archivo;
	archivo.open(nombre.c_str(), fstream::out);
	this->escribirEnOrden(this->raiz, archivo);
	archivo.close();
}

void Abb::escribirEnOrden(NodoArbol* nodo, fstream& archivo) {
	if (nodo->getIzquierdo())
		this->escribirEnOrden(nodo->getIzquierdo(), archivo);
	archivo << nodo->getPalabra()->imprimir() << endl;
	if (nodo->getDerecho())
		this->escribirEnOrden(nodo->getDerecho(), archivo);

}
