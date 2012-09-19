/*
 * Parser.cpp
 *
 *  Created on: 14/09/2012
 *      Author: Yamila Glinsek
 */

#include "Parser.h"

Parser::Parser() { }

bool Parser::ProcessFiles() {
	int doc = 1;
	Sorter sorter = Sorter();
	DirList directories;
	if (!directories.crearDesdeDirectorio(DIRECTORY))
		return false;
	while (directories.haySiguiente()) {
		if (!Process(sorter, directories.siguienteLargo(), doc))
			return false;
		doc++;
	}
	if (!sorter.completo())										// FALTA IMPLEMENTACION DEL SORTER
		return false;
	return true;
}

bool Parser::Process(Sorter sorter, string filePath, int doc) {
	string word = "";
	char character;
	bool error = false;
	Archivo file = Archivo(filePath, error);
	if (error)
		return false;
	while (file.leerCaracter(character)) {
		if (((character>='A') & (character<='Z')) || ((character>='a') & (character<='z')))
			word += tolower(character);
		else {
			sorter.agregarPalabra(word, doc);
			word = "";
		}
	}
	file.~Archivo();
	return true;
}

Parser::~Parser() { }
