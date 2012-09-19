/*
 * Merger.cpp
 *
 *  Created on: Sep 14, 2012
 *      Author: Hugo Chavar
 */

#include "Merger.h"
#include "Texto.h"

Merger::Merger() {
	//system("echo -n '1. Current Directory is '; pwd");
	//system("mkdir temp");
	//pongo en 1 todos los flags
	this->flags.set();
	//un flag en 0 significa que hay que leer el archivo en esa posicion
}

void Merger::inicializar(string dir) {
	string basedir = "/home/hugo/aa";
	string linea;
	DirList dl;
	Palabra p;
	unsigned i;

	if (dl.crearDesdeDirectorio(basedir)) {
		//cout << "Salida exitosa. Hay "<<dl.getCantidad()<<" archivos." << endl;
		for (i = 0; i < dl.getCantidad(); i++) {
			archivos.push_back(Archivo());
			archivos[i].abrir(dl.siguienteLargo());
			linea = archivos[i].leerLinea();
			p.crearDesdeString(linea);
			//cout<<"Primer linea archivo "<<i<<": "<<linea<<endl;
			palabras.push_back(p);
			p.resetearInformacion();
			//cout<<"Primer palabra "<<i<<": "<<palabras[i].imprimir()<<endl;
		}
	}
}

unsigned Merger::contarMinimos(){
	unsigned mins =1;
	int comp;
	string minPalabra=palabras[0].getContenido();
	cout<<"menor palabra es: "<<minPalabra<<endl;
	for (unsigned j=1;j<palabras.size();j++){
		comp = palabras[j].compararCon(minPalabra);
		if( comp == 0){
			mins++;
		} else if (comp < 0){
			mins = 1;
			minPalabra=palabras[j].getContenido();
			cout<<"Ahora la menor palabra es: "<<minPalabra<<endl;
		}
	}

	return mins;
}

Merger::~Merger() {
	//cierro todos los archivos
	archivos.clear();
	//libero memoria
	palabras.clear();
}

