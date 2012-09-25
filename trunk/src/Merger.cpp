/*
 * Merger.cpp
 *
 *  Created on: Sep 14, 2012
 *      Author: Hugo Chavar
 */

#include "Merger.h"
//#include "Texto.h"

Merger::Merger() {
	//system("echo -n '1. Current Directory is '; pwd");
	//system("mkdir temp");
	//pongo en 1 todos los flags


}

void Merger::setInputDir(string dir) {

	this->inputDir = dir;
	this->directories.limpiar();
	this->directories.crearDesdeDirectorio(inputDir);

}

void Merger::setOutputFileName(string filename) {
	this->outputFileName = filename;

}

void Merger::setOutputFolderName(string foldername) {
	this->outputFolderName = foldername;
	this->currentFileNumber = 0;
}

void Merger::setNextFileName(){
	if (this->mode == ETAPA){
		//si es FINAL debe estar seteado con setOutputFileName
		string aux = static_cast<ostringstream*>( &(ostringstream() << this->currentFileNumber) )->str();
		this->outputFileName = this->outputFolderName + "/"+"etapa"+aux+".txt";
		this->currentFileNumber++;
	}
}

void Merger::setMode(mergeMode mode){
	this->mode = mode;
	Palabra p;
	if (this->mode == ETAPA){
		this->filesByStep = this->calcularArchivosPorEtapa();
	} else { // es FINAL
		this->filesByStep = directories.getCantidad();
	}
	words.clear();
	for (unsigned i = 0; i < this->filesByStep; i++) {
		words.push_back(p);
	}
}

void Merger::inicializarEtapa() {
	unsigned i = 0;
	minCounted = false;

	this->wordsReaded.set();
	//cout<<"wordsReaded ANTES DE EMPEZAR "<<endl;
	//cout<<"wordsReaded: "<<wordsReaded.to_string()<<endl;
	this->openFiles.reset();

	//if (!finDelMerge()) { // TODO podria retornar falso si llego el fin del merge..
	while ((i < this->filesByStep) && (directories.haySiguiente())) {
		stepFiles[i] = new Archivo();
		stepFiles[i]->abrirLectura(directories.siguienteLargo());
		openFiles.set(i);
		leerEnArchivo(i);
		i++;
//			cout << "Primer palabra " << i << ": " << words[i].imprimir()
//					<< endl;
//			cout << "maxDoc: " << words[i].maxDoc() << endl;
//			cout << "minDoc: " << words[i].minDoc() << endl;
	}
	//cout<<"wordsReaded DESPUES DE INICIALIZAR "<<endl;
	//cout<<"wordsReaded: "<<wordsReaded.to_string()<<endl;
	//}
}

void Merger::leerEnArchivo(unsigned nroArchivo) {
	string linea;

	//if (openFiles.test(nroArchivo)) { // estoy haciendo doble chequeo del if..corregir
	linea = stepFiles[nroArchivo]->leerLinea();
	if (stepFiles[nroArchivo]->eof()) {
		delete stepFiles[nroArchivo];
		openFiles.reset(nroArchivo);
	} else {
		words[nroArchivo].crearDesdeString(linea);
		wordsReaded.reset(nroArchivo);
		//cout<<"Leido arch "<<nroArchivo<<"= " << linea << endl;
	}
//	} else {
//		cout
//				<< "Esta intentando leer un archivo que no pertenece al set actual."
//				<< endl;
//	}
	//return linea;
}

void Merger::leerMas() {
	// el ultimo metodo dificil de implementar.. veamos ..
	//en cada posicion donde WORDSREADED este en SET y el archivo sigue vivo
	//se debe leer el archivo en esa posicion
	// del resto del papeleo se encargan los otros metodos
	for (unsigned i = 0; i < this->filesByStep; i++) { //TODO mejorar este for.. mismo problema q en inicializar
		if ((wordsReaded.test(i)) && (openFiles.test(i))) {
			leerEnArchivo(i);
		}
	}

}

unsigned Merger::contarMinimos() {
	if (minCounted)
		return minWords.count();

	unsigned j, mins = 1;
	int comp;
	minWords.reset();
	this->minPosition = 0;
	string minPalabra = words[this->minPosition].getContenido();
//	cout << "menor palabra es: " << minPalabra << endl;
//	cout<<"wordsReaded ANTES DE BUSCAR MINIMO "<<endl;
//	cout<<"wordsReaded: "<<wordsReaded.to_string()<<endl;
	while (wordsReaded.test(this->minPosition)) {
		this->minPosition++;
		minPalabra = words[this->minPosition].getContenido();
		//cout << "menor palabra es: " << minPalabra << endl;
	}

	minPalabra = words[this->minPosition].getContenido();
//	cout << "menor palabra es: " << minPalabra << endl;
	minWords.set(this->minPosition);

	for (j = (this->minPosition + 1); j < words.size(); j++) {
		if (!wordsReaded.test(j)) {
			comp = words[j].compararCon(minPalabra);
			if (comp == 0) {
				mins++;
				minWords.set(j);
			} else if (comp < 0) {
				mins = 1;
				this->minPosition = j;
				minWords.reset();
				minWords.set(j);
				minPalabra = words[j].getContenido();
//				cout << "Ahora la menor palabra es: " << minPalabra << endl;
			}
		}
	}
	minCounted = true;

	return mins;
}

void Merger::aparearPalabras(unsigned a, unsigned b) {
	unsigned max, min;
	if ((words[a].maxDoc()) <= (words[b].minDoc())) {
		min = a;
		max = b;
	} else if ((words[b].maxDoc()) <= (words[a].minDoc())) {
		min = b;
		max = a;
	}

	if ((words[min].maxDoc()) == (words[max].minDoc())) {
		words[min].agregarAparicion((words[max].minDoc()),
				words[max].getInformacion().begin()->getCantidad());
		//elimino el nodo de la palabra 2
		words[max].borrarMinDoc();
	}
	words[min].agregarListaAlFinal(words[max].getInformacion());
	words[max].resetearInformacion();

	//desafecto a la palabra appendeada
	//cout<<"minWords: "<<minWords.to_string()<<endl;
	minWords.reset(max);
	//cout<<"minWords: "<<minWords.to_string()<<endl;
	//indico que el archivo del cual se desafecto la palabra debe ser leido
	//cout<<"wordsReaded: "<<wordsReaded.to_string()<<endl;
	wordsReaded.set(max);
	//cout<<"wordsReaded: "<<wordsReaded.to_string()<<endl;
	this->minPosition = min;
}

void Merger::resolverMinimos() {
	//Este metodo ya funciona bien
	//Atencion: supone que el orden de los documentos se mantiene en el orden de los archivos
	//cout<<"minWords: "<<minWords.to_string()<<endl;
	unsigned min1, j = 0;
	while (!minWords.test(j)) {
		j++;
	}
	min1 = j++;
	while (!minWords.test(j)) {
		j++;
	}
//	cout << "min1: " << words[min1].getContenido() << " min2: "<< words[j].getContenido() << endl;
	aparearPalabras(min1, j);
	//this->minCounted = false; esta linea es problematica, no volver a ponerla

}

void Merger::escribirMinimo() {
	//string linea;
	//linea = stepFiles[this->minPosition]->leerLinea();
	this->outputFile.escribirLinea(words[this->minPosition].imprimir());
	this->wordsReaded.set(this->minPosition);
	words[this->minPosition].resetearInformacion();
	this->minCounted = false;
	//cout<<"wordsReaded: "<<wordsReaded.to_string()<<endl;
}

void Merger::merge() {
	unsigned etapa,cantmin;
	etapa =1;
	while (!finDelMerge()) {
		cout<<"Etapa: "<<etapa<<endl;
		setNextFileName();
		this->outputFile.abrirEscritura(this->outputFileName);
		inicializarEtapa();

		while (!finDeEtapa()) {
			cantmin = contarMinimos();
			while (cantmin > 1) {
				//cout << "Antes de resolver, minimos: "<<cantmin << endl;
				//cout<<"wordsReaded: "<<wordsReaded.to_string()<<endl;
//			for (unsigned i = 0; i < this->filesByStep; i++) {
//				if (!wordsReaded.test(i)) {
//					cout << "Palabra " << i << ": " << words[i].imprimir()<< endl;
//				}
//			}
				resolverMinimos();
//			cout << "Despues de resolver " << endl;
//			cout<<"wordsReaded: "<<wordsReaded.to_string()<<endl;
//			for (unsigned i = 0; i < this->filesByStep; i++) {
//				if (!wordsReaded.test(i)) {
//					cout << "Palabra " << i << ": " << words[i].imprimir()<< endl;
//				}
//			}
				cantmin = contarMinimos();
			}
			escribirMinimo();
			//cout << "Leyendo archivos que tenian la minima palabra.. " << endl;
			leerMas();

		}
		this->outputFile.cerrar();
		etapa++;
	}
}

bool Merger::finDeEtapa() {
	//cout << "Archivos abiertos: " << openFiles.to_string() << endl;
	return !openFiles.any();
}

unsigned Merger::calcularArchivosPorEtapa() {
	unsigned i = 1;

	while ((i * i) < directories.getCantidad()) { //
		i++;
		//cout<<"todavia i =  "<<i<<"i<<1 = "<<(i*i)<<endl;
	}
	return i;
}

bool Merger::finDelMerge() {
	return !directories.haySiguiente();
}

void Merger::cerrarArchivos() {
	int i = 0;
	while ((openFiles.count() > 0) && (i < MAX_FILES_MERGE)) {
		if (openFiles.test(i)) {
			delete stepFiles[i];
			openFiles.reset(i);
		} else {
			i++;
		}
	}
}

Merger::~Merger() {
	//cierro todos los archivos
	cerrarArchivos();
	//libero memoria
	words.clear();
}
