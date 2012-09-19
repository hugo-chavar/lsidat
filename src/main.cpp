/*
 * main.cpp
 *
 *  Created on: Sep 7, 2012
 *      Author: andy
 */

#include "Sorter.h"
#include "InfoPalabra.h"
#include "Parser.h"
#include <iostream>
#include <list>
#include "Abb.h"
#include "Merger.h"
#include "Archivo.h"

using namespace std;

int main()
{
	//Prueba parser
	Parser parser = Parser();
	parser.ProcessFiles();


	//Prueba Sorter

	Abb* abb=new Abb();
	abb->agregarPalabra("hola",1);
	abb->agregarPalabra("andres",1);
	abb->agregarPalabra("como",1);
	abb->agregarPalabra("es",1);
	abb->agregarPalabra("hola",1);
	abb->agregarPalabra("sos",1);
	abb->agregarPalabra("como",1);
	abb->agregarPalabra("hola",2);
	abb->agregarPalabra("andres",2);
	abb->agregarPalabra("como",2);
	abb->escribirEnArchivo("prueba2.txt");
	delete abb;

	//Prueba merger
	Merger m;
	m.inicializar("hola");
	cout<<"cant de minimos: "<<m.contarMinimos()<<endl;
	
	return 0;
}
