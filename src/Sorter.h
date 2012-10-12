/*
 * Sorter.h
 *
 *  Created on: Sep 7, 2012
 *      Author: Andres Sanabria
 */

#ifndef SORTER_H_
#define SORTER_H_

#define MAX_NODOS 		1000

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


private:
	unsigned archivosCreados;
	Abb* arbol;
	string outputDirectory;
	bool arbolCompleto();
	void archivarArbol();
};

#endif /* SORTER_H_ */
