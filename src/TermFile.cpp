/*
 * TermFile.cpp
 *
 *  Created on: 07/11/2012
 *      Author: Hugo Chavar
 */

#include "TermFile.h"

TermFile::TermFile() {
	pos = 0;
	crearVector = false;
	ultimoAgregado = true;
}

TermFile::~TermFile() {
}

bool TermFile::abrir(string path) {
	bool result = t.abrirLectura(path);
	if (result){
		pos = 0;
		piso = 0;
		string aux = t.leerLinea();
		tamaniocampo = aux.length();
		dimension=t.tamanio()/(tamaniocampo+1);
		termactual = trim_copy(aux);
		ultimoAgregado = false;
	}
	return result;
}

bool TermFile::crear(string path) {
	return t.abrirEscritura(path);
}

void TermFile::agregar(string term) {
	t.escribirCampoLongitudFija(term, tamaniocampo);
}

void TermFile::setTamanioCampo(unsigned tam) {
	tamaniocampo = tam;
}

int TermFile::busquedaSecuencialTerm(string buscado) {
	int comp = -1;

	if ((pos >= 0) && (!ultimoAgregado)) {
		//si el ultimo fue agregado me evito una comparacion
		comp = comparar(buscado);
	}
	while ((comp < 0) && (!t.eof())) {
		termactual = trim_copy(t.leerLinea());
		pos++;
		comp = comparar(buscado);
	}
	//si esta devuelve la posicion, sino devuelve -1
	if (comp == 0)
		return pos;
	else
		return -1;
}
/*
 * Modificación al diseño
 * Busqueda binaria sobre los terminos, aprovechando el ordenamiento dado para armar la matriz.
 * Además aprovecha que los términos de la consulta están ordenados,
 * entonces el piso de la busqueda de un termino se mantiene para la siguiente busqueda, ya que
 * el siguiente termino sera por lo menos ese piso o mas grande en terminos del orden alfabetico.
 */

int TermFile::busquedaBinariaTerm(string buscado){
	int techo,comp = -1; //,base=0
	bool encontrado = false;
	techo = dimension-1;
	//leer = false;


//	if ((pos > 0) && (!ultimoAgregado)) {
//		//si el ultimo fue agregado me evito una comparacion
//		//si comp da negativo el termino buscado es menor al actual
//		//si da positivo es mayor
//		comp = comparar(buscado);
//	}
	while (!encontrado){
		pos = (piso + techo)/2; //base
		//cout<<endl<<"Pos actual: "<<posactual<<endl;
		termactual = getTerm(pos);
		//cout<<"Term leido: "<<termactual<<endl;
		comp = comparar(buscado);
		if (comp==0){
			encontrado = true;
		} else if (comp < 0) {
			piso = pos+1;
			//leer = true;
		} else {
			techo = pos -1;
			//pos = posactual; me quedo parado en un registro mayor al term buscado. ANDY:No es necesario
			//leer = true;
		}
		if (piso > techo){ //base
			encontrado = true;
			//leer = false;
		}
	}
	//si esta devuelve la posicion, sino devuelve -1
	if (comp == 0)
		return pos;
	else
		return -1;

}

int TermFile::comparar(string unterm) {
	int comp;
	comp = termactual.compare(unterm);
	// flag q indica si el ultimo termino leido es tenido en cta en el vector
	ultimoAgregado = false;
	if (comp <= 0) { //si comp >0 no se el valor en el vector
		//comp > 0 significa q el termino lo esta en la lista de terminos
		ultimoAgregado = true;
		if ((crearVector) && (comp == 0)) {
			vector[pos] = 1;
		}
//			cout<<"comp ="<<comp<<endl;
//			cout<<"vector["<<pos - 1<<"]="<<vector[pos - 1]<<endl;
//			if (pos>1)
//				cout<<"vector["<<pos - 2<<"]="<<vector[pos - 2]<<endl;
	}
	return comp;
}

void TermFile::iniciarVector() {

	crearVector = true;
	vector.resize(dimension);
	for (int i = 0; i < dimension; i++) {
		vector[i] = 0;
	}
}

VectorXf TermFile::getVector() {
	return vector;
}

string TermFile::getTerm(unsigned termNumber){
	t.irAPos((termNumber)*(tamaniocampo+1));

	string term = trim_copy(t.leerLinea());
	return term;
}
