/*
 * Palabra.cpp
 *
 *  Created on: Sep 8, 2012
 *      Author: andy
 */

#include "Palabra.h"

Palabra::Palabra(string cont) {

	this->contenido = cont;
}

Palabra::~Palabra() {
	// TODO Auto-generated destructor stub
}

void Palabra::agregarAparicion(unsigned doc) {

	InfoPalabra* nodo = this->buscarDoc(doc);
	if (nodo)
		nodo->incrementarCantidad();
	else {
		//this->informacion.push_back(*(new InfoPalabra(doc,1)));
		this->agregarNodo(doc, 1);
	}
}

InfoPalabra* Palabra::buscarDoc(unsigned doc) {
	list<InfoPalabra>::iterator it = this->informacion.begin();
	bool encontrado = false;
	while ((&(*it)) && (!encontrado)) {
		if (it->getDocumento() == doc) {
			encontrado = true;
		} else {
			advance(it, 1);
		}
	}
	return (&(*it));
}

void Palabra::agregarNodo(unsigned doc, unsigned cantidad) {
	this->informacion.push_back(*(new InfoPalabra(doc, cantidad)));
}

void Palabra::crearDesdeString(string  s){
	vector <string> v;
	split(v,s,",");
	string aux;

	unsigned doc,cant;
	this->contenido = v[ 0 ];

	for (size_t n = 1; n < v.size(); n+=2){
		aux = trim_copy(v[ n ]);
		doc = atoi(aux.c_str());
		aux = trim_copy(v[ n+1 ]);
		cant = atoi(aux.c_str());
		this->agregarNodo(doc,cant);
		//cout << "\" Doc: " << trim_copy(v[ n ]) <<" cant: "<<trim_copy(v[ n+1 ])<< "\"\n";
		//cout << "\" Doc: " << doc <<" cant: "<<cant<< "\"\n";
		//trim(v[ n ])
	}

	cout << endl;

}
