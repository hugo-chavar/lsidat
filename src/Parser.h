/*
 * Parser.h
 *
 *  Created on: 14/09/2012
 *      Author: Yamila Glinsek
 */

#ifndef PARSER_H_
#define PARSER_H_
#define DIRECTORY "/media/DATOS/Organizacion de Datos/PruebaPaths.txt" // CAMBIAR

#include <iostream>
#include <string>
#include <list>
#include "Archivo.h"
#include "Sorter.h"

using namespace std;

class Parser {
public:
	Parser();
	virtual ~Parser();
	bool ProcessFiles(Sorter sorter);
private:
	list<string> directories;
	void Initialize();
	bool Process(Sorter sorter, string filePath, int doc);
};

#endif /* PARSER_H_ */
