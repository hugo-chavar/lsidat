/*
 * Palabra.h
 *
 *  Created on: Sep 8, 2012
 *      Author: andy
 */

#ifndef PALABRA_H_
#define PALABRA_H_

#include "InfoPalabra.h"
#include "Texto.h"
#include <list>
#include <vector>

using namespace std;

class Palabra {

private:
	string contenido;
	list<InfoPalabra> informacion;
	unsigned cantidad;
	void agregarNodo(unsigned doc, unsigned cantidad);
	InfoPalabra* buscarDoc(unsigned doc);

public:
	Palabra(string cont);
	Palabra();
	~Palabra();
	void agregarAparicion(unsigned doc);
	list<InfoPalabra> getInformacion();
	string getContenido();
	void crearDesdeString(string  s);
	string imprimir();
	void resetearInformacion();
};

#endif /* PALABRA_H_ */
