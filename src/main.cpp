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
#include "Sorter.h"
#include "Merger.h"
#include "Archivo.h"

using namespace std;

int main()
{
	//Prueba parser
	//Parser parser = Parser();
	//parser.ProcessFiles();


	//Prueba Sorter
/*
	Sorter* sorter=new Sorter();

	sorter->agregarPalabra("hola",1);
	sorter->agregarPalabra("andres",1);
	sorter->agregarPalabra("como",1);
	sorter->agregarPalabra("es",1);
	sorter->agregarPalabra("como",1);
	sorter->agregarPalabra("tp",1);
	sorter->agregarPalabra("datos",1);
	sorter->agregarPalabra("sos",1);
	sorter->agregarPalabra("como",1);
	sorter->agregarPalabra("hola",2);
	sorter->agregarPalabra("hola",2);
	sorter->agregarPalabra("hola",2);
	sorter->agregarPalabra("andres",2);
	sorter->agregarPalabra("como",2);
	sorter->agregarPalabra("te",3);
	sorter->terminar();
	delete sorter;
*/
	//Prueba Merger

	Merger m;

	m.setInputDir("/home/hugo/aa");
	m.setOutputFileName("/home/hugo/ff/merged.txt");
	m.inicializarEtapa();
	//cout<<"cant de minimos: "<<m.contarMinimos()<<endl;
	//m.merge();
	//cout<<"Archivos por etapa: "<<m.calcularArchivosPorEtapa()<<endl;
	m.merge();
	

	return 0;
}
