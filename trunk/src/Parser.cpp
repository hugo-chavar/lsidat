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
	_filesCount = 0;
}

bool Parser::Process(Sorter* sorter, string filePath, int doc) {
	string buffer, word;
	//considero delimitador: espacio, nueva linea, tab, punto y coma y parentesis
	//la coma y el punto no van por el tema de los numeros
	char delimiters[] = " \n\r\t\f\v;()\":";
	Archivo file;
	unsigned i, pos, lngthbuff, lngthtoken;
	if (!file.abrirLectura(filePath)) {
		cerr<<"Se produjo un error al abrir el archivo: "<<filePath<<endl;
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
	}

	return true;
}

bool Parser::ProcessFiles(string outputDirectory) {
	int doc = 0;
	Sorter* sorter = new Sorter(outputDirectory);

	while (directories.hasNext()) {
		if (!Process(sorter, directories.nextFullPath(), doc)){
			delete sorter;
			return false;
		}
		doc++;
	}
	_filesCount = doc;
	sorter->terminar();
	/*
	 * Se almacena la longitud de la palabra mas larga, para luego setear el tamanio del campo
	 * en el archivo de terminos de manera que tenga una longitud fija y minima.
	 */
	this->_maxLengthWord = sorter->getMaxLongPalabra();
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

int Parser::filesCount() {
	return _filesCount;
}

unsigned Parser::maxLengthWord(){
	return _maxLengthWord;
}

Parser::~Parser() {

}
