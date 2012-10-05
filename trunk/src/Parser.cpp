/*
 * Parser.cpp
 *
 *  Created on: 14/09/2012
 *      Author: Yamila Glinsek
 */

#include "Parser.h"

Parser::Parser() { }

bool Parser::Process(Sorter sorter, string filePath, int doc) {
	string word = "";
	char character;
	Archivo file;
	if (!file.abrirLectura(filePath)) {
		return false;
	}
	while (!file.eof()) {
		string line = file.leerLinea();
		int i;
		for (i=0; i < line.length(); i++) {
			if (((line[i]>='A') & (line[i]<='Z')) || ((line[i]>='a') & (line[i]<='z')))
				word += tolower(line[i]);
			else {
				if (word != "")
					sorter.agregarPalabra(word, doc);
				word = "";
			}
		}
		if (word != "")
			sorter.agregarPalabra(word, doc);
	}
	return true;
}

bool Parser::ProcessFiles() {
	int doc = 1;
	Sorter sorter;
	DirList directories;
	if (!directories.crearDesdeDirectorio(DIRECTORY))
		return false;
	while (directories.haySiguiente()) {
		if (!Process(sorter, directories.siguienteLargo(), doc))
			return false;
		doc++;
	}
	return true;
}

Parser::~Parser() { }
