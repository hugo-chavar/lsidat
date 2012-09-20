/*
 * Sorter.cpp
 *
 *  Created on: Sep 7, 2012
 *      Author: andy
 */

#include "Sorter.h"

#define MAX_NODOS 6

using namespace std;

Sorter::Sorter() {
	this->archivosCreados=0;
	this->arbol=new Abb();
}

Sorter::~Sorter() {
	delete this->arbol;
}

void Sorter::agregarPalabra(string palabra,int doc){
	if (this->arbolCompleto()){
			this->archivarArbol();
			delete this->arbol;
			this->arbol=new Abb();
	}
	this->arbol->agregarPalabra(palabra,doc);
}

void Sorter::archivarArbol(){

	this->archivosCreados++;
	string aux = static_cast<ostringstream*>( &(ostringstream() << this->archivosCreados) )->str();
	string nombreArchivo=string("particion")+aux+".txt";
	this->arbol->escribirEnArchivo(nombreArchivo);
	}

bool Sorter::arbolCompleto(){

return((this->arbol->getCantidad())>=(MAX_NODOS));
}

void Sorter::terminar(){
	if (this->arbol->getCantidad()>0){
		this->archivarArbol();
	}
}



