/*
 * Coseno.cpp
 *
 *  Created on: 11/11/2012
 *      Author: Andres Sanabria
 */

#include "Coseno.h"

Coseno::Coseno(int doc,float val) {

	documento=doc;
	valor=val;

}

Coseno::Coseno(const Coseno& cos){
	valor = cos.valor;
	documento = cos.documento;
}

Coseno::~Coseno() {

}

bool Coseno::operator<(const Coseno& cos){
	return (valor<cos.valor);
}

float Coseno::getCoseno(){
	return valor;
}

int Coseno::getDocumento(){
		return documento;
	}

