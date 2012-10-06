/*
 * Parser.h
 *
 *  Created on: 14/09/2012
 *      Author: Yamila Glinsek
 */

#ifndef PARSER_H_
#define PARSER_H_
//#define DIRECTORY "/media/DATOS/Organizacion de Datos/Pruebas/Archivos" // CAMBIAR
//Hugo: pasé la linea de arriba a Sorter.h, para empezar a unificar

#include <iostream>
#include <string>
#include <list>
#include "Archivo.h"
#include "Sorter.h"
#include "DirList.h"

using namespace std;

class Parser {
public:
	Parser();
	virtual ~Parser();
	bool ProcessFiles();
private:
	bool Process(Sorter* sorter, string filePath, int doc);
};

#endif /* PARSER_H_ */
