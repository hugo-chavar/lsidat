/*
 * TermFile.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: Hugo Chavar
 */

#include "TermFile.h"

TermFile::TermFile() {
	pos = 0;
	crearVector = false;
	ultimoAgregado = true;
}

TermFile::~TermFile() {
//	if (crearVector){
//		delete vector;
//	}
}

bool TermFile::abrir(string path) {
	return t.abrirLectura(path);
}

bool TermFile::crear(string path) {
	return t.abrirEscritura(path);
}

void TermFile::agregar(string term) {
	t.escribirLinea(term);
}

int TermFile::buscarTerm(string buscado) {
	int comp = -1;

	if ((pos > 0) && (!ultimoAgregado)) {
		//si el ultimo fue agregado me evito una comparacion
		comp = comparar(buscado);
	}
	while (comp < 0) {
		actual = t.leerLinea();
		pos++;
		comp = comparar(buscado);
	}
	//si esta devuelve la posicion, sino devuelve -1
	return (comp > 0 ? -1 : pos);

}

int TermFile::comparar(string unterm){
	int comp;
	comp = actual.compare(unterm);
	// flag q indica si el ultimo termino leido es tenido en cta en el vector
	ultimoAgregado = false;
	if (comp <= 0) { //si comp >0 no se el valor en el vector
		//comp > 0 significa q el termino lo esta en la lista de terminos
		//vector.conservativeResize(pos);
		ultimoAgregado =true;
		if ((crearVector)&&(comp == 0)) {
			vector[pos - 1] = 1;
		}
//			cout<<"comp ="<<comp<<endl;
//			cout<<"vector["<<pos - 1<<"]="<<vector[pos - 1]<<endl;
//			if (pos>1)
//				cout<<"vector["<<pos - 2<<"]="<<vector[pos - 2]<<endl;
	}
	return comp;
}

void TermFile::iniciarVector(int filas) {
	//vector = new VectorXf(filas);
	crearVector = true;
	dimension = filas;
	vector.resize(dimension);
	for(int i = 0; i<dimension;i++){
		vector[i]=0;
	}
}

VectorXf TermFile::getVector(){
	return vector;
}
