/*
 * InfoPalabra.cpp
 *
 *  Created on: Sep 8, 2012
 *      Author: andy
 */

#include "InfoPalabra.h"

InfoPalabra::InfoPalabra(unsigned doc,unsigned cant) {
	this->documento = doc;
	this->cantidad = cant;
}

unsigned InfoPalabra::getCantidad(){
	return(this->cantidad);
}

void InfoPalabra::incrementarCantidad(){
	this->cantidad++;
}

unsigned InfoPalabra::getDocumento(){
	return(this->documento);
}

InfoPalabra::~InfoPalabra() {
	// TODO Auto-generated destructor stub
}

