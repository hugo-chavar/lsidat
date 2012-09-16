/*
 * main.cpp
 *
 *  Created on: Sep 7, 2012
 *      Author: andy
 */

#include "Sorter.h"
#include "InfoPalabra.h"
#include <iostream>
#include <list>
#include "Merger.h"

using namespace std;

int main()
{
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
	Merger m;

	return 0;
}
