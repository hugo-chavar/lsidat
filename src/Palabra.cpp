/*
 * Palabra.cpp
 *
 *  Created on: Sep 8, 2012
 *      Author: Andres Sanabria
 */

#include "Palabra.h"

Palabra::Palabra(string cont) {

	this->contenido = cont;
}
Palabra::Palabra() {

}

Palabra::~Palabra() {
	resetearInformacion();
}

list<InfoPalabra> Palabra::getInformacion() {
	return (this->informacion);
}

string Palabra::getContenido() {
	return (this->contenido);
}

void Palabra::agregarAparicion(unsigned doc,unsigned cant) {
	InfoPalabra* nodo = this->buscarDoc(doc);
	if (nodo)
		nodo->incrementarCantidad(cant);
	else {
		this->agregarNodo(doc, cant);
	}
}

void Palabra::agregarAparicion(unsigned doc) {
	agregarAparicion(doc,1);
}

unsigned Palabra::minDoc(){
	return (this->informacion.begin())->getDocumento();
}

void Palabra::borrarMinDoc(){
	this->informacion.pop_front();
}

unsigned Palabra::maxDoc(){
	return (this->informacion.back().getDocumento());
}

InfoPalabra* Palabra::buscarDoc(unsigned doc) {
	if ((informacion.size() > 0)) {
		if ( maxDoc()== doc){
			return (&this->informacion.back());
		}
	}
	return (0); //No fue encontrado
}

void Palabra::agregarNodo(unsigned doc, unsigned cantidad) {
	InfoPalabra aux(doc, cantidad);
	this->informacion.push_back(aux);
}

void Palabra::agregarListaAlFinal(list<InfoPalabra> toAppend){
	this->informacion.splice(informacion.end(),toAppend);
}

void Palabra::crearDesdeString(string s) {
	vector<string> v;
	split(v, s, ",");
	string aux;

	unsigned doc, cant;
	this->contenido = v[0];
//	cout<<"Palabra: "<<this->contenido<<endl;

	for (size_t n = 1; n < v.size(); n += 2) {
		aux = trim_copy(v[n]);
		doc = atoi(aux.c_str());
		aux = trim_copy(v[n + 1]);
		cant = atoi(aux.c_str());
		this->agregarNodo(doc, cant);
		//cout << "\" Doc: " << trim_copy(v[ n ]) <<" cant: "<<trim_copy(v[ n+1 ])<< "\"\n";
	//	cout << "\" Doc: " << doc <<" cant: "<<cant<< "\"\n";
		//trim(v[ n ])
	}
}

string Palabra::imprimir(){
	string salida =this->contenido;
	string aux;
	list<InfoPalabra>::iterator it = this->informacion.begin();
	unsigned i = 0;
	while (i < informacion.size()) {
		//aux = static_cast<ostringstream*>( &(ostringstream() << it->getDocumento()) )->str();
		aux = toString(it->getDocumento());
		salida = salida+","+ aux;
		aux = toString(it->getCantidad());
		//aux = static_cast<ostringstream*>( &(ostringstream() << it->getCantidad()) )->str();
		salida = salida+","+ aux;
		advance(it, 1);
		i++;
	}
	return salida;
}

void Palabra::resetearInformacion(){
	informacion.clear();
}

int Palabra::compararCon(string clave){
	return this->contenido.compare(clave);
}

unsigned Palabra::cantidad(){
	return (this->informacion.size());
}
