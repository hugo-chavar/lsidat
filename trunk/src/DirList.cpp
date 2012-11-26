/*
 * DirList.cpp
 *
 *  Created on: 05/09/2012
 *      Author: Hugo Chavar
 */
#include <algorithm>
#include "DirList.h"

using namespace std;

DirList::DirList() {
	_count = 0;
	_currentPosition = 0;
	maxFileNameLength = 0;

}

DirList::~DirList() {
}

bool DirList::createFromDirectory(string dir) {
	string filepath, filename;
	DIR *dp;
	struct dirent *dirp;
	struct stat filestat;
	dp = opendir(dir.c_str());
	if (dp == NULL) {
		cerr << "Se produjo un error al abrir el directorio " << dir << endl;
		return false;
	}
	this->directory = dir;

	while ((dirp = readdir(dp))) {
		filepath = dir + "/" + dirp->d_name;

		// Si hay directorios o cosas raras las ignora
		if (stat(filepath.c_str(), &filestat))
			continue;
		if (S_ISDIR( filestat.st_mode ))
			continue;
		filename = dirp->d_name;
		if (maxFileNameLength < filename.length())
			maxFileNameLength = filename.length();
		files.push_back(filename);
		_count++;

	}
	files.sort();
	iterador = files.begin();

	closedir(dp);

	return true;

}

string DirList::next() {
	string sigte = *iterador;
	iterador++;
	_currentPosition++;

	return sigte;

}

string DirList::nextFullPath() {
	string sigte = directory + "/" + (*iterador);
	iterador++;
	_currentPosition++;

	return sigte;

}
bool DirList::hasNext() {
	return (_currentPosition < _count);
}

void DirList::clean() {
	files.clear();
	_count = 0;
	_currentPosition = 0;
}

bool DirList::seek(unsigned pos) {
	bool status = (pos < _count);
	if (status) {
		_currentPosition = pos;
		iterador = files.begin();
		for (unsigned i = 0; i < pos; i++) {
			iterador++;
		}
	}
	return status;
}

unsigned DirList::count() const {
	return _count;
}

unsigned DirList::currentPosition() {
	return _currentPosition;
}

void DirList::writeToFile(string filepath) {
	TermFile file;
	file.crear(filepath);
	/**
	 * Modificacion al diseño:
	 * Los nombres de los archivos se guardan como campos de longitud fija.
	 * De esta manera una vez calculados los cosenos se accede directamente al nombre
	 * indicando el numero de documento indicado por el numero de columna de la Matriz V de la reduccion,
	 * evitando la no performante lectura secuencial.
	 * El tamaño del campo es la maxima longitud de un nombre de archivo.
	 * En este caso el espacio que se pierde al mantener esta estructura es muy baja,
	 * en contraposicion a la velocidad ganada en las consultas.
	 */

	file.setTamanioCampo(maxFileNameLength);
	while (this->hasNext()) {
		file.agregar(this->next());
	}
	seek(0);
}
