/*
 * DirList.h
 *
 *  Created on: Sep 5, 2012
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

using namespace std;

class DirList {
private:
	list<string> files;
	list<string>::iterator iterador;
	unsigned _count;
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
