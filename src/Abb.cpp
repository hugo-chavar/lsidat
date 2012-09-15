/*
 * Abb.cpp
 *
 *  Created on: Sep 14, 2012
 *      Author: andy
 */

#include "Abb.h"
#include <iostream>


Abb::Abb() {
		this->raiz = NULL;
		this->cantidad = 0;
}

Abb::~Abb() {
	this->destruir();
}

void Abb::agregarPalabra(string palabra,unsigned documento)
{
	NodoArbol *nodo=this->raiz;
	NodoArbol *nodo_padre = NULL;
	while (nodo && (nodo->CompararCon(palabra)!=0)) // Devuelve -1 si la clave del nodo es menor, 0 si son iguales y 1 si la clave es mayor.
	{
		nodo_padre = nodo;
		if (nodo->CompararCon(palabra)==1)
			nodo=nodo->getIzquierdo();
		else
			nodo=nodo->getDerecho();
	}
	if (!nodo)
	{
		nodo= new NodoArbol(palabra);
		nodo->getPalabra().agregarAparicion(documento);
		if (nodo_padre)
		{
			if (nodo->CompararCon(nodo_padre->getPalabra().getContenido())==1)
				nodo_padre->setDerecho(nodo);
			else
				nodo_padre->setIzquierdo(nodo);
		}
		else
			this->raiz = nodo;
			this->cantidad++;
	}
	else
	{
		nodo->getPalabra().agregarAparicion(documento);
	}
}


void Abb::borrar(const string clave)
{
	NodoArbol *nodo = this->raiz;
	NodoArbol *nodo_padre = NULL;
	while (nodo && (nodo->CompararCon(clave)!=0)) // Devuelve -1 si la clave es menor, 0 si son iguales y 1 si la clave es mayor.
	{
		nodo_padre = nodo;
		if (nodo->CompararCon(clave)==1)
			nodo=nodo->getIzquierdo();
		else
			nodo=nodo->getDerecho();
	}
	NodoArbol *nodo_aux = NULL;
	if ((!nodo->getDerecho())&& (nodo->getIzquierdo()))
		nodo_aux = nodo->getIzquierdo();
	else if (!nodo->getIzquierdo() && nodo->getDerecho())
		nodo_aux = nodo->getDerecho();
	else if (nodo->getIzquierdo() && nodo->getDerecho())
	{
		NodoArbol *padre_aux = NULL;
		nodo_aux = nodo->getIzquierdo();//
		while (nodo_aux->getDerecho())
		{
			padre_aux = nodo_aux;
			nodo_aux = nodo_aux->getDerecho();
		}
		if (padre_aux)
		{
			padre_aux->setDerecho(nodo_aux->getIzquierdo());
			nodo_aux->setIzquierdo(nodo->getIzquierdo());
		}
		nodo_aux->setDerecho(nodo->getDerecho());
	}
	if (nodo_padre)
	{
		if (nodo->CompararCon(nodo_padre->getPalabra().getContenido())==1)
			nodo_padre->setDerecho(nodo_aux);
		else
			nodo_padre->setIzquierdo(nodo_aux);
	}
	else
		this->raiz = nodo_aux;
	delete nodo;
	this->cantidad--;
}

// Destruye el árbol.
void Abb::destruir(){
	while (this->raiz)
		this->borrar(this->raiz->getPalabra().getContenido());
}


