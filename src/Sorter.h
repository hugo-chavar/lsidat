/*
 * Sorter.h
 *
 *  Created on: 07/09/2012
 *      Author: Andres Sanabria
 */

#ifndef SORTER_H_
#define SORTER_H_

#define MAX_NODOS 		10000

#include <iostream>
#include <string>
#include "Abb.h"
#include "Texto.h"

using namespace std;

class Sorter {
public:
	Sorter(string outputDirectory);
	~Sorter();
	void agregarPalabra(string palabra,int doc);
	void terminar();
	unsigned getMaxLongPalabra();


private:
	unsigned archivosCreados;
	unsigned maxLongitudPalabra;
	Abb* arbol;
	string outputDirectory;
	bool arbolCompleto();
	void archivarArbol();
};

#endif /* SORTER_H_ */
