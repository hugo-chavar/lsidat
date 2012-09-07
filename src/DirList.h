/*
 * DirList.h
 *
 *  Created on: Sep 5, 2012
 *      Author: hugo
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

using namespace std;

class DirList {
private:
	list <string> archivos;
	list <string>::iterator iterador;
	unsigned cantidad;
	unsigned _posicionActual;
	string directorio;
public:
	DirList();
	~DirList();
	bool crearDesdeDirectorio(string);
	bool haySiguiente();
	string siguiente();
	string siguienteLargo();
	bool seek(unsigned);
	unsigned posicionActual();

};

#endif /* DIRLIST_H_ */
