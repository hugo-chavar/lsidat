/*
 * Parser.cpp
 *
 *  Created on: 14/09/2012
 *      Author: Yamila Glinsek
 */

#include <string.h>
#include "Parser.h"

Parser::Parser() {
	cantArchivos = 0;
}

bool Parser::Process(Sorter* sorter, string filePath, int doc) {
	string word = "";
	Archivo file;
	unsigned i;
	if (!file.abrirLectura(filePath)) {
		return false;
	}
	while (!file.eof()) {
		string line = file.leerLinea();
		for (i=0; i < line.length(); i++) {
			if (((line[i]>='A') & (line[i]<='Z')) || ((line[i]>='a') & (line[i]<='z')))
				word += tolower(line[i]);
			else {
				if (word != "")
					sorter->agregarPalabra(word, doc);
				word = "";
			}
		}
		if (word != "")
			sorter->agregarPalabra(word, doc);
		word = "";
	}

	return true;
}

bool Parser::ProcessFiles(string inputDirectory, string outputDirectory) {
	int doc = 1;
	Sorter* sorter = new Sorter(outputDirectory);
	DirList directories;
	if (!directories.crearDesdeDirectorio(inputDirectory))
		return false;
	while (directories.haySiguiente()) {
		if (!Process(sorter, directories.siguienteLargo(), doc))
			return false;
		doc++;
	}
	cantArchivos = doc-1;
	sorter->terminar();
	delete sorter;
	return true;
}

int Parser::numFiles() {
	return cantArchivos;
}

Parser::~Parser() { }
