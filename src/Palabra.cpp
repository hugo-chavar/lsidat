/*
 * Palabra.cpp
 *
 *  Created on: Sep 8, 2012
 *      Author: andy
 */

#include "Palabra.h"

Palabra::Palabra(string cont) {

	this->contenido=cont;
}

Palabra::~Palabra() {
	// TODO Auto-generated destructor stub
}

void Palabra::agregarAparicion(unsigned doc){

	InfoPalabra* nodo= this->buscarDoc(doc);
	if(nodo)
	nodo->incrementarCantidad();
	else
	{
		this->informacion.push_back(*(new InfoPalabra(doc,1)));
	}
}

InfoPalabra* Palabra::buscarDoc(unsigned doc){
	list<InfoPalabra>::iterator it= this->informacion.begin();
	bool encontrado=false;
	while((&(*it)) && (!encontrado))
	{
	if(it->getDocumento()==doc){
		encontrado=true;
		}
	else{
		advance(it,1);
		}
	}
	return (&(*it));
}
