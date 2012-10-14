/*
 * DirList.cpp
 *
 *  Created on: Sep 5, 2012
 *      Author: Hugo Chavar
 */
#include "DirList.h"

using namespace std;

DirList::DirList() {
	_count = 0;
	_currentPosition=0;

}

DirList::~DirList() {
}

bool DirList::createFromDirectory(string dir) {
	string filepath, filename;
	//ifstream fin; por si necesito abrir los archivos
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
		files.push_back(filename);
		_count++;

		//por ahora solo muestro los nombres de archivos completos
		//cout << filepath << endl;

		//por si hace falta abrir los archivos dejo el codigo para hacerlo
//		fin.open( filepath.c_str() );
//		    if (fin >> num) //leo un caracter (en este caso un numero)
//		      cout << filepath << ": " << num << endl;
//		    fin.close();
	}
	//queda ordenado por nombre de archivo
	files.sort();
	//dejo apuntando al primero
	iterador = files.begin();

	closedir(dp);
	cout << "Procesamiento exitoso de directorio " << dir <<"."<< endl;
	cout << "Cantidad de archivos " << _count <<"."<< endl;
	return true;

}

string DirList::next(){
	string sigte = *iterador;
	iterador++;
	_currentPosition++;

	return sigte;

}

string DirList::nextFullPath(){
	string sigte = directory+"/"+(*iterador);
	iterador++;
	_currentPosition++;

	return sigte;

}
bool DirList::hasNext(){
	return (_currentPosition<_count);
}

void DirList::clean(){
	files.clear();
	_count = 0;
	_currentPosition=0;
}

bool DirList::seek(unsigned pos){
	bool status = (pos<_count);
	if(status){
		_currentPosition=pos;
		iterador = files.begin();
		for (unsigned i=0;i<pos;i++){
			iterador++;
		}
	}
	return status;
}

unsigned DirList::count() const {
	return _count;
}

unsigned DirList::currentPosition(){
	return _currentPosition;
}

void DirList::writeToFile(string filepath){
	Archivo file;
	file.abrirEscritura(filepath);
	while (this->hasNext()){
		file.escribirLinea(this->next());
	}
	seek(0);
}
