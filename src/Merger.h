/*
 * Merger.h
 *
 *  Created on: Sep 14, 2012
 *      Author: Hugo Chavar
 */

#ifndef MERGER_H_
#define MERGER_H_

#define MAX_FILES_MERGE 32

#include <iostream>
#include <bitset>
#include "DirList.h"
#include "Archivo.h"
#include "Palabra.h"

class Merger {
public:
	Merger();
	~Merger();
	void setInputDir(string);
	void setOutputFileName(string);
	void inicializarEtapa();
	void merge();
	bool escribirSiguienteLinea();
	unsigned contarMinimos();
	void resolverMinimos();
	void escribirMinimo();
	void leerMas();
	void aparearPalabras(unsigned,unsigned);
	unsigned calcularArchivosPorEtapa();
	bool finDeEtapa();
	bool finDelMerge();
	void cerrarArchivos();
	void leerEnArchivo(unsigned);

private:
	bitset<MAX_FILES_MERGE> wordsReaded;
	bitset<MAX_FILES_MERGE> minWords;
	bitset<MAX_FILES_MERGE> openFiles;
	bool minCounted;
	unsigned minPosition;
	string inputDir;
	string outputFileName;
	Archivo outputFile;
	//vector <Archivo> archivos;
	Archivo * stepFiles[MAX_FILES_MERGE];
	vector <Palabra> words;
	DirList directories;
	unsigned filesByStep;
};

#endif /* MERGER_H_ */
