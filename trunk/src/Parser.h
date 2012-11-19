/*
 * Parser.h
 *
 *  Created on: 14/09/2012
 *      Author: Yamila Glinsek
 */

#ifndef PARSER_H_
#define PARSER_H_


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
	bool ProcessFiles( string outputDirectory);
	bool setInputDirectory(string inputDirectory);
	void setFilesProcessedPath(string filesProcessed);
	int filesCount();
	unsigned maxLengthWord();
private:
	int _filesCount;
	unsigned _maxLengthWord;
	bool Process(Sorter* sorter, string filePath, int doc);
	DirList directories;
};

#endif /* PARSER_H_ */
