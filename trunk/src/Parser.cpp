/*
 * Parser.cpp
 *
 *  Created on: 14/09/2012
 *      Author: Yamila Glinsek
 */

#include <string.h>
#include "Parser.h"
#include "Token.h"

Parser::Parser() {
	cantArchivos = 0;
}

bool Parser::Process(Sorter* sorter, string filePath, int doc) {
	string buffer, word;
	//considero delimitador: espacio, nueva linea, tab, punto y coma y parentesis
	//la coma y el punto no van por el tema de los numeros
	char delimiters[] = ", \n\r\t\f\v;()\":"; //no modificar
	Archivo file;
	unsigned i, pos, lngthbuff, lngthtoken;
	if (!file.abrirLectura(filePath)) {
		return false;
	}
	while (!file.eof()) {
		buffer = file.leerBloque();
		i = 0;
		lngthbuff = buffer.length();
		while (i < lngthbuff) {

			pos = buffer.find_first_of(delimiters, i);
			lngthtoken = pos - i;
			if (lngthtoken < MAX_TOKEN_LENGTH) {
				Token token(buffer.substr(i, lngthtoken));
				while (token.hasNextTerm()) {
					sorter->agregarPalabra(token.nextTerm(), doc);
				}
			}

			i = buffer.find_first_not_of(delimiters, pos);
		}

		//separadores & - _ /: . -- ver apostrofe  separar los ..  * entre palabras
		//x entre numeros
		//partir antes de sacar el plural
//		war--prisoners
//		war/prisoners/exchange
	}

	return true;
}

bool Parser::ProcessFiles(string outputDirectory) {
	int doc = 0;
	Sorter* sorter = new Sorter(outputDirectory);

	while (directories.hasNext()) {
		if (!Process(sorter, directories.nextFullPath(), doc))
			return false;
		doc++;
	}
	cantArchivos = doc;
	sorter->terminar();
	delete sorter;
	return true;
}

bool Parser::setInputDirectory(string inputDirectory) {
	if (!directories.createFromDirectory(inputDirectory))
		return false;

	return true;
}

void Parser::setFilesProcessedPath(string filesProcessed) {
	directories.writeToFile(filesProcessed);
}

int Parser::numFiles() {
	return cantArchivos;
}

Parser::~Parser() {
}
