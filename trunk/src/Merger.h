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
	void inicializar(string dir);
	void merge();
	bool escribirSiguienteLinea();
	unsigned contarMinimos();

private:
	bitset<MAX_FILES_MERGE> flags;
	bitset<MAX_FILES_MERGE> openFiles;
	string inputDir;
	string outputFileName;
	Archivo outputFile;
	//vector <Archivo> archivos;
	Archivo * archi[MAX_FILES_MERGE];
	vector <Palabra> palabras;
};

#endif /* MERGER_H_ */
