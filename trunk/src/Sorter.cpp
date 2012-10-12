/*
 * Sorter.cpp
 *
 *  Created on: Sep 7, 2012
 *      Author: Andres Sanabria
 */

#include "Sorter.h"


using namespace std;

Sorter::Sorter(string outputDirectory) {
	this->archivosCreados = 0;
	this->arbol = new Abb();
	this->outputDirectory = outputDirectory;
}

Sorter::~Sorter() {
	//delete this->arbol; lo puse en terminar()
}

void Sorter::agregarPalabra(string palabra, int doc) {
	if (this->arbolCompleto()) {
		this->archivarArbol();
		delete this->arbol;
		this->arbol = new Abb();
	}
	this->arbol->agregarPalabra(palabra, doc);
	//cout<<"Se agrego palabra: "<<palabra<<" doc: "<<doc<<endl;
}

void Sorter::archivarArbol() {
	this->archivosCreados++;
	string aux = static_cast<ostringstream*>(&(ostringstream()
			<< this->archivosCreados))->str();
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

