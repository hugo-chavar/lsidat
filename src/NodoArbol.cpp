/*
 * NodoArbol.cpp
 *
 *  Created on: 14/09/2012
 *      Author: Andres Sanabria
 */

#include "NodoArbol.h"

NodoArbol::NodoArbol(string palabra){
	this->dato=new Palabra(palabra);
	this->derecho=NULL;
	this->izquierdo=NULL;
}

NodoArbol::~NodoArbol() {
	delete (dato);
}

NodoArbol* NodoArbol::getIzquierdo(){
	return(this->izquierdo);
}

NodoArbol* NodoArbol::getDerecho(){
	return(this->derecho);
}

void NodoArbol::setIzquierdo(NodoArbol* izq){
	this->izquierdo=izq;
}

void NodoArbol::setDerecho(NodoArbol* der){
	this->derecho=der;
}

Palabra* NodoArbol::getPalabra(){
	return((this->dato));
}


//int NodoArbol::CompararCon(string clave){
//	if ((this->dato->getContenido())<clave)
//		return (-1);
//	else if((this->dato->getContenido())==clave)
//			return (0);
//		else
//			return (1);
//}


