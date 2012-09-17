/*
 * Parser.cpp
 *
 *  Created on: 14/09/2012
 *      Author: Yamila Glinsek
 */

#include "Parser.h"

Parser::Parser() {
	Initialize();
}

void Parser::Initialize() {
	bool error = false;
	string path;
	char end = '#';
	Archivo fileDirectory(DIRECTORY, error);
	while (fileDirectory.leerHastaCaracter(end, path)) {
		directories.push_back(path);
	}
	fileDirectory.~Archivo();
}

bool Parser::ProcessFiles(Sorter sorter) {
	int doc = 1;
	while (!directories.empty()) {
		if (!Process(sorter, directories.front(), doc))
			return false;
		directories.pop_front();
		doc++;
	}
	return true;
}

bool Parser::Process(Sorter sorter, string filePath, int doc) {
	string word = "";
	char character;
	bool error = false;
	Archivo file = Archivo(filePath, error);
	if (error) {
		file.~Archivo();
		return false;
	}
	while (file.leerCaracter(character)) {
		if ((character>='A' & character<='Z') || (character>='a' & character<='z'))
			word += character;
		else {
			sorter.agregarPalabra(word, doc);
			word = "";
		}
	}
	file.~Archivo();
	return true;
}

Parser::~Parser() {
	directories.~list();
}
