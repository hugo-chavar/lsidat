/*
 * DirList.cpp
 *
 *  Created on: Sep 5, 2012
 *      Author: hugo
 */
#include "DirList.h"

using namespace std;

DirList::DirList() {
	// TODO Auto-generated constructor stub
	_cantidad = 0;
	_posicionActual=0;

}

DirList::~DirList() {
	// TODO Auto-generated destructor stub
}

bool DirList::crearDesdeDirectorio(string dir) {
	string filepath, filename;
	//ifstream fin; por si necesito abrir los archivos
	DIR *dp;
	struct dirent *dirp;
	struct stat filestat;
	dp = opendir(dir.c_str());
	if (dp == NULL) {
		cout << "Se produjo un error al abrir el directorio " << dir << endl;
		return false;
	}
	this->directorio = dir;

	while ((dirp = readdir(dp))) {
		filepath = dir + "/" + dirp->d_name;


		// Si hay directorios o cosas raras las ignora
		if (stat(filepath.c_str(), &filestat))
			continue;
		if (S_ISDIR( filestat.st_mode ))
			continue;
		filename = dirp->d_name;
		archivos.push_back(filename);
		_cantidad++;

		//por ahora solo muestro los nombres de archivos completos
		cout << filepath << endl;

		//por si hace falta abrir los archivos dejo el codigo para hacerlo
//		fin.open( filepath.c_str() );
//		    if (fin >> num) //leo un caracter (en este caso un numero)
//		      cout << filepath << ": " << num << endl;
//		    fin.close();
	}
	//queda ordenado por nombre de archivo
	archivos.sort();
	//dejo apuntando al primero
	iterador = archivos.begin();

	closedir(dp);
	return true;

}

string DirList::siguiente(){
	string sigte = *iterador;
	iterador++;
	_posicionActual++;

	return sigte;

}

string DirList::siguienteLargo(){
	string sigte = directorio+"/"+(*iterador);
	iterador++;
	_posicionActual++;

	return sigte;

}
bool DirList::haySiguiente(){
	return (_posicionActual<_cantidad);
}

bool DirList::seek(unsigned pos){
	bool status = (pos<_cantidad);
	if(status){
		_posicionActual=pos;
		iterador = archivos.begin();
		for (unsigned i=0;i<pos;i++){
			iterador++;
		}
	}
	return status;
}

unsigned DirList::getCantidad() const {
	return _cantidad;
}

unsigned DirList::posicionActual(){
	return _posicionActual;
}
