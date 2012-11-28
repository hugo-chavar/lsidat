/*
 * Sorter.cpp
 *
 *  Created on: 07/09/2012
 *      Author: Andres Sanabria
 */

#include "Sorter.h"


using namespace std;

Sorter::Sorter(string outputDirectory) {
	this->archivosCreados = 0;
	this->maxLongitudPalabra = 0;
	this->arbol = new Abb();
	this->outputDirectory = outputDirectory;
}

Sorter::~Sorter() {
}

void Sorter::agregarPalabra(string palabra, int doc) {
	if (this->arbolCompleto()) {
		this->archivarArbol();
		delete this->arbol;
		this->arbol = new Abb();
	}
	this->arbol->agregarPalabra(palabra, doc);
	if (this->maxLongitudPalabra < palabra.length())
		this->maxLongitudPalabra =  palabra.length();
}

void Sorter::archivarArbol() {
	this->archivosCreados++;
	string aux = toString(this->archivosCreados);
	string nombreArchivo = outputDirectory + string("/particion.") + pad_left_copy(aux,6,'0');
	this->arbol->escribirEnArchivo(nombreArchivo);
}

bool Sorter::arbolCompleto() {
	return ((this->arbol->getCantidad()) >= MAX_NODOS);
}

void Sorter::terminar() {
	if (this->arbol->getCantidad() > 0) {
		this->archivarArbol();
		delete this->arbol;
	}
}

unsigned Sorter::getMaxLongPalabra() {
	return this->maxLongitudPalabra;
}
