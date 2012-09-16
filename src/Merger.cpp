/*
 * Merger.cpp
 *
 *  Created on: Sep 14, 2012
 *      Author: hugo
 */
#include <iostream>
#include <vector>
#include "Merger.h"
#include "Texto.h"
#include "DirList.h"
#include "Archivo.h"
#include "Palabra.h"

Merger::Merger() {
	//system("echo -n '1. Current Directory is '; pwd");
	//system("mkdir temp");
	string basedir = "/home/hugo/aa";
	string linea;
	DirList dl;
	vector <Archivo> archivos;
	vector <Palabra> palabras;
	Palabra p;
	unsigned i;

	//archivos.push_back(Archivo());
	if (dl.crearDesdeDirectorio(basedir)) {
		cout << "Salida exitosa. Hay "<<dl.getCantidad()<<" archivos." << endl;
		for(i=0;i<dl.getCantidad();i++){
			archivos.push_back(Archivo());
			archivos[i].abrir(dl.siguienteLargo());
			linea = archivos[i].leerLinea();
			p.crearDesdeString(linea);
			cout<<"Primer linea archivo "<<i<<": "<<linea<<endl;
			palabras.push_back(p);
			p.resetearInformacion();
			cout<<"Primer palabra "<<i<<": "<<palabras[i].imprimir()<<endl;
		}
		archivos.clear();
	}


}

Merger::~Merger() {

}

