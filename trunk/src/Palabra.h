/*
 * Palabra.h
 *
 *  Created on: 08/09/2012
 *      Author: Andres Sanabria
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
	void agregarNodo(unsigned doc, unsigned cantidad);
	InfoPalabra* buscarDoc(unsigned doc);

public:
	Palabra(string cont);
	Palabra();
	~Palabra();
	void agregarAparicion(unsigned doc);
	void agregarAparicion(unsigned doc,unsigned cant);
	void agregarListaAlFinal(list<InfoPalabra>);
	unsigned maxDoc();
	unsigned minDoc();
	unsigned cantidad();
	void borrarMinDoc();
	list<InfoPalabra> getInformacion();
	string getContenido();
	void crearDesdeString(string  s);
	string imprimir();
	void resetearInformacion();
	int compararCon(string clave);
};

#endif /* PALABRA_H_ */
