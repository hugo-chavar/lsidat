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

	//cout<<"libere"<<endl;
	informacion.clear();
}

list<InfoPalabra> Palabra::getInformacion() {
	return (this->informacion);
}

string Palabra::getContenido() {
	return (this->contenido);
}

void Palabra::agregarAparicion(unsigned doc) {

	InfoPalabra* nodo = this->buscarDoc(doc);
	if (nodo)
		nodo->incrementarCantidad();
	else {
		this->agregarNodo(doc, 1);
	}
}

InfoPalabra* Palabra::buscarDoc(unsigned doc) {
	if ((informacion.size() > 0)) {
		list<InfoPalabra>::iterator it = this->informacion.begin();
		unsigned i = 0;
		while (i < informacion.size()) {
			if (it->getDocumento() == doc) {
				return (&(*it)); //encontrado
			} else {
				advance(it, 1);
			}
			i++;
		}
	}
	return (0); //No fue encontrado
}

void Palabra::agregarNodo(unsigned doc, unsigned cantidad) {
	InfoPalabra aux(doc, cantidad);
	this->informacion.push_back(aux);
	//this->informacion.push_back(*(new InfoPalabra(doc, cantidad)));
}

void Palabra::crearDesdeString(string s) {
	vector<string> v;
	split(v, s, ",");
	string aux;

	unsigned doc, cant;
	this->contenido = v[0];

	for (size_t n = 1; n < v.size(); n += 2) {
		aux = trim_copy(v[n]);
		doc = atoi(aux.c_str());
		aux = trim_copy(v[n + 1]);
		cant = atoi(aux.c_str());
		this->agregarNodo(doc, cant);
		//cout << "\" Doc: " << trim_copy(v[ n ]) <<" cant: "<<trim_copy(v[ n+1 ])<< "\"\n";
		//cout << "\" Doc: " << doc <<" cant: "<<cant<< "\"\n";
		//trim(v[ n ])
	}

	cout << endl;

}

