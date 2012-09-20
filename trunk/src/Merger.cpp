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
	this->openFiles.reset();
	this->inputDir = "/home/hugo/aa";
	this->outputFileName = "/home/hugo/ff/merged.txt";
	//un flag en 0 significa que hay que leer el archivo en esa posicion
}

void Merger::inicializar(string dir) {
	string linea;
	DirList dl;
	Palabra p;
	unsigned i;
	//Archivo *a;

	if (dl.crearDesdeDirectorio(inputDir)) {
		//cout << "Salida exitosa. Hay "<<dl.getCantidad()<<" archivos." << endl;
		for (i = 0; i < dl.getCantidad(); i++) {
			archi[i] = new Archivo();
			//archivos.push_back(*a);
			//archivos[i].abrirLectura(dl.siguienteLargo());
			archi[i]->abrirLectura(dl.siguienteLargo());
			openFiles.set(i);
			//if (!archivos[i].eof()){
			if (!archi[i]->eof()){
				linea = archi[i]->leerLinea();
				cout<<linea<<endl;
			} else{
				delete archi[i];
				openFiles.reset(i);
			}
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

void Merger::merge(){
	this->outputFile.abrirEscritura(this->outputFileName);
	string linea = "juafasf";
	while(!archi[0]->eof()){
		linea = archi[0]->leerLinea();
		this->outputFile.escribirLinea(linea);

	}
}

Merger::~Merger() {
	//cierro todos los archivos
	int i=0;
	while ((openFiles.count()>0)&&(i< MAX_FILES_MERGE)){
		if (openFiles.test(i)){
			delete archi[i];
			openFiles.reset(i);
		} else{
			i++;
		}
	}
	//libero memoria
	palabras.clear();
}

