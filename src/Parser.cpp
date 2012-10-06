/*
 * Parser.cpp
 *
 *  Created on: 14/09/2012
 *      Author: Yamila Glinsek
 */

#include <string.h>
#include "Parser.h"

Parser::Parser() { }

bool Parser::Process(Sorter* sorter, string filePath, int doc) {
	string word = "";
	//char character;
	Archivo file;
	unsigned i;
	if (!file.abrirLectura(filePath)) {
		return false;
	}
	while (!file.eof()) {
		string line = file.leerLinea();
		//cout<<line<<endl;

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
	}

	return true;
}

bool Parser::ProcessFiles() {
	int doc = 1;
	Sorter* sorter = new Sorter();
	DirList directories;
	if (!directories.crearDesdeDirectorio(Xstr(DIRECTORY)))
		return false;
	//creo una carpeta para q el sorter tire ahi la salida
	//TODO: esto debe corregirse.. es lento, inseguro, ineficiente...
	char comando[100];
	strcpy(comando,"mkdir -p ");
	strcat(comando,Xstr(DIR_SORTER));
	system(comando);
	//fin de creacion de dir temporal
	while (directories.haySiguiente()) {
		if (!Process(sorter, directories.siguienteLargo(), doc))
			return false;
		doc++;
	}
	sorter->terminar();
	delete sorter;
	return true;
}

Parser::~Parser() { }
