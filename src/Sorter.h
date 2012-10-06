/*
 * Sorter.h
 *
 *  Created on: Sep 7, 2012
 *      Author: Andres Sanabria
 */

#ifndef SORTER_H_
#define SORTER_H_

#define DIRECTORY 		/home/hugo/Downloads/classic //todo: ver otra manera de manejar los directorios
#define DIR_SORTER 		DIRECTORY/tempsorter
#define Str(x) 			#x
#define Xstr(x) 		Str(x)

#define MAX_NODOS 		1000

#include <iostream>
#include <string>
#include "Abb.h"
#include "Texto.h"

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
