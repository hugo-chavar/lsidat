/*
 * Sorter.h
 *
 *  Created on: Sep 7, 2012
 *      Author: andy
 */

#ifndef SORTER_H_
#define SORTER_H_

//#define VECTOR_SIZE 1000;
#include <iostream>
#include <string>
#include <list>
#include "Palabra.h"
const unsigned VECTOR_SIZE=100;

using namespace std;

class Sorter {
public:
	Sorter();
	~Sorter();
	void agregarPalabra(string palabra,int doc);
	//void ordenarVector(); //Dependera de si se ordena a medida que se ingresa o al final
	string archivarVector();
	list<string> getListaArchivos();
	bool completo();

private:
	list<string> listaArchivos;
	//Palabra palabras[VECTOR_SIZE];//esto traia problemas
	unsigned cantidadPalabras;
	void agregarArchivoALista(string);
};

#endif /* SORTER_H_ */
