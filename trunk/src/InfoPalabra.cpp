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
InfoPalabra::InfoPalabra(const InfoPalabra& ip){
	documento = ip.documento;
	cantidad = ip.cantidad;
}

unsigned InfoPalabra::getCantidad(){
	return(this->cantidad);
}

void InfoPalabra::incrementarCantidad(unsigned cant){
	this->cantidad+=cant;;
}

unsigned InfoPalabra::getDocumento(){
	return(this->documento);
}

InfoPalabra::~InfoPalabra() {

}

