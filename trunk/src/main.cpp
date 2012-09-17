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

using namespace std;

int main()
{
	string word;
	Parser parser = Parser();
	Sorter sorter = Sorter();
	parser.ProcessFiles(sorter);

	/*
	Palabra hola("hola");
	hola.agregarAparicion(1);
	hola.agregarAparicion(5);
	hola.agregarAparicion(2);
	hola.agregarAparicion(2);
	hola.agregarAparicion(2);
	hola.agregarAparicion(1);
	string contenido=hola.getContenido();
	list<InfoPalabra> lista=hola.getInformacion();
	cout<<"La palabra de contenido "<<contenido<<" aparece:"<<endl;
	list<InfoPalabra>::iterator it= lista.begin();
	cout<<"size:"<<lista.size()<<endl;
	for(unsigned i=1;i<=lista.size();i++)
	{
		cout<<"documento:"<<it->getDocumento()<<" cantidad:"<<it->getCantidad()<<endl;
		advance(it,1);
	}
=======

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
	NodoArbol** vector=new NodoArbol*[abb->getCantidad()];
	abb->obtenerVectorOrdenado(vector);
	list<InfoPalabra>::iterator it2;
	for(unsigned i=0;i<abb->getCantidad();i++){
		Palabra palabra=vector[i]->getPalabra();
		cout<<palabra.getContenido()<<endl;
		it2=palabra.getInformacion().begin();
		cout<<"size:"<<palabra.getInformacion().size()<<endl;
		for(unsigned j=0;j<palabra.getInformacion().size();j++){
			cout<<"doc:"<<it2->getDocumento()<<" cant:"<<it2->getCantidad()<<endl;
			advance(it2,1);
		}
		cout<<endl;
	}
	abb->getCantidad();

	delete []vector;
	delete abb;

	Merger m;
	*/

	return 0;
}
