/*
 * Coseno.cpp
 *
 *  Created on: Nov 11, 2012
 *      Author: andy
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

