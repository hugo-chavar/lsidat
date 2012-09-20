/*
 * Sorter.h
 *
 *  Created on: Sep 7, 2012
 *      Author: andy
 */

#ifndef SORTER_H_
#define SORTER_H_

#include <iostream>
#include <string>
#include "Abb.h"

using namespace std;

class Sorter {
public:
	Sorter();
	~Sorter();
	void agregarPalabra(string palabra,int doc);
	void terminar();


private:
	unsigned archivosCreados;
	Abb* arbol;
	bool arbolCompleto();
	void archivarArbol();
};

#endif /* SORTER_H_ */
