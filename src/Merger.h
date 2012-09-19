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
	bool escribirSiguienteLinea();
	unsigned contarMinimos();

private:
	bitset<MAX_FILES_MERGE> flags;
	vector <Archivo> archivos;
	vector <Palabra> palabras;
};

#endif /* MERGER_H_ */
