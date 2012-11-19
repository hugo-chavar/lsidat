/*
 * DirList.h
 *
 *  Created on: 05/09/2012
 *      Author: Hugo Chavar
 */

#ifndef DIRLIST_H_
#define DIRLIST_H_

#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <list>
#include "Archivo.h"
#include "TermFile.h"

using namespace std;

class DirList {
private:
	list<string> files;
	list<string>::iterator iterador;
	unsigned _count;
	unsigned maxFileNameLength;
	unsigned _currentPosition;
	string directory;
public:
	DirList();
	~DirList();
	bool createFromDirectory(string);
	bool hasNext();
	string next();
	string nextFullPath();
	bool seek(unsigned);
	unsigned currentPosition();
	unsigned count() const;
	void clean();
	void writeToFile(string);

};

#endif /* DIRLIST_H_ */
