/*
 * Merger.cpp
 *
 *  Created on: Sep 14, 2012
 *      Author: Hugo Chavar
 */

#include "Merger.h"
//#include "Texto.h"

Merger::Merger() {
}

void Merger::setInputDir(string dir) {

	this->inputDir = dir;
	this->directories.clean();
	this->directories.createFromDirectory(inputDir);

}

void Merger::setOutputFileName(string filename) {
	this->outputFileName = filename;

}

void Merger::setOutputFolderName(string foldername) {
	this->outputFolderName = foldername;
	this->currentFileNumber = 0;
}

void Merger::setNextFileName(){
	if (this->mode == STAGE){
		//si es FINAL debe estar seteado con setOutputFileName
		//string aux = static_cast<ostringstream*>( &(ostringstream() << this->currentFileNumber) )->str();
		string aux = toString(this->currentFileNumber);
		this->outputFileName = this->outputFolderName + "/"+"etapa."+ pad_left_copy(aux,4,'0');;
		this->currentFileNumber++;
	}
}

void Merger::setMode(mergeMode mode){
	this->mode = mode;
	Palabra p;
	if (directories.count() < 5){
		//this->mode = FINAL; //TODO ver como evitar un paso
	}
	if (this->mode == STAGE){
		this->filesByStep = this->calculateFilesPerStage();
	} else { // es FINAL
		this->filesByStep = directories.count();
	}
	words.clear();
	for (unsigned i = 0; i < this->filesByStep; i++) {
		words.push_back(p);
	}
}

void Merger::initializeStage() {
	unsigned i = 0;
	minCounted = false;
	this->wordsReaded.set();
	this->openFiles.reset();

	while ((i < this->filesByStep) && (directories.hasNext())) {
		stepFiles[i] = new Archivo();
		stepFiles[i]->abrirLectura(directories.nextFullPath());
		openFiles.set(i);
		readFromFileNumber(i);
		i++;
	}
}

void Merger::readFromFileNumber(unsigned nroArchivo) {
	string linea;
	linea = stepFiles[nroArchivo]->leerLinea();
	if (stepFiles[nroArchivo]->eof()) {
		delete stepFiles[nroArchivo];
		openFiles.reset(nroArchivo);
	} else {
		words[nroArchivo].crearDesdeString(linea);
		wordsReaded.reset(nroArchivo);
	}
}

void Merger::readMore() {
	//en cada posicion donde WORDSREADED este en SET y el archivo sigue vivo
	//se debe leer el archivo en esa posicion
	for (unsigned i = 0; i < this->filesByStep; i++) { //TODO mejorar este for.. mismo problema q en inicializar
		if ((wordsReaded.test(i)) && (openFiles.test(i))) {
			readFromFileNumber(i);
		}
	}

}

unsigned Merger::countMinima() {
	if (minCounted)
		return minWords.count();

	unsigned j, mins = 1;
	int comp;
	minWords.reset();
	this->minPosition = 0;
	string minPalabra = words[this->minPosition].getContenido();
	while (wordsReaded.test(this->minPosition)) {
		this->minPosition++;
		minPalabra = words[this->minPosition].getContenido();
	}

	minPalabra = words[this->minPosition].getContenido();
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
			}
		}
	}
	minCounted = true;

	return mins;
}

void Merger::joinWords(unsigned a, unsigned b) {
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
	minWords.reset(max);
	//indico que el archivo del cual se desafecto la palabra debe ser leido
	wordsReaded.set(max);
	this->minPosition = min;
}

void Merger::fixMinima() {
	unsigned min1, j = 0;
	while (!minWords.test(j)) {
		j++;
	}
	min1 = j++;
	while (!minWords.test(j)) {
		j++;
	}
	joinWords(min1, j);
}

void Merger::writeMinimum() {
	this->outputFile.escribirLinea(words[this->minPosition].imprimir());
	this->wordsReaded.set(this->minPosition);
	words[this->minPosition].resetearInformacion();
	this->minCounted = false;
}

void Merger::merge() {
	unsigned etapa,cantmin;
	etapa =1;
	while (!endOfMerge()) {
		setNextFileName();
		this->outputFile.abrirEscritura(this->outputFileName);
		initializeStage();

		while (!endOfStage()) {
			cantmin = countMinima();
			while (cantmin > 1) {
				fixMinima();
				cantmin = countMinima();
			}
			writeMinimum();
			readMore();

		}
		this->outputFile.cerrar();
		etapa++;
	}
}

bool Merger::endOfStage() {
	return !openFiles.any();
}

unsigned Merger::calculateFilesPerStage() {
	unsigned i = 1;

	while ((i * i) < directories.count()) { //
		i++;
	}
	return i;
}

bool Merger::endOfMerge() {
	return !directories.hasNext();
}

void Merger::closeAllFiles() {
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
	closeAllFiles();
	words.clear();
}
