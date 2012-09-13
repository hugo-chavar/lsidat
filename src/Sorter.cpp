/*
 * Sorter.cpp
 *
 *  Created on: Sep 7, 2012
 *      Author: andy
 */

#include "Sorter.h"

using namespace std;

Sorter::Sorter() {
	// TODO Auto-generated constructor stub
}

Sorter::~Sorter() {
	// TODO Auto-generated destructor stub
}

void Sorter::agregarPalabra(string palabra,int doc){
	//falta implementar
		cout<<"falta implementar agregar palabra"<<endl;
}

string Sorter::archivarVector(){

	//falta implementar
	cout<<"falta implementar archivar"<<endl;
return "falta Implementar archivar";
	}

list<string> Sorter::getListaArchivos(){

	return(this->listaArchivos);
	}

bool Sorter::completo(){

return((this->cantidadPalabras)<=VECTOR_SIZE);

	}

void Sorter::agregarArchivoALista(string filepath){

	this->listaArchivos.push_back(filepath);
}




/*void Sorter::sort(string palabra){
	cout <<"No Hay problema con la palabra"<<palabra<<endl;
}*/

