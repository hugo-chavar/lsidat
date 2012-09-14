/*
 * Palabra.h
 *
 *  Created on: Sep 8, 2012
 *      Author: andy
 */

#ifndef PALABRA_H_
#define PALABRA_H_

#include "InfoPalabra.h"
#include <list>

using namespace std;

class Palabra {

private:
	string contenido;
	list<InfoPalabra> informacion;

public:
	Palabra(string cont);
	~Palabra();
	void agregarAparicion(unsigned doc);
	InfoPalabra* buscarDoc(unsigned doc);
	void agregarNodo(unsigned doc, unsigned cantidad);

};

#endif /* PALABRA_H_ */
