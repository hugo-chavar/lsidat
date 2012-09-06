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

}

DirList::~DirList() {
	// TODO Auto-generated destructor stub
}

bool DirList::create(string dir) {
	string filepath;
	//ifstream fin; por si necesito abrir los archivos
	DIR *dp;
	struct dirent *dirp;
	struct stat filestat;
	dp = opendir(dir.c_str());
	if (dp == NULL) {
		cout << "Se produjo un error al abrir el directorio " << dir << endl;
		return false;
	}

	while ((dirp = readdir(dp))) {
		filepath = dir + "/" + dirp->d_name;

		// Si hay directorios o cosas raras las ignora
		if (stat(filepath.c_str(), &filestat))
			continue;
		if (S_ISDIR( filestat.st_mode ))
			continue;

		//por ahora solo muestro los nombres de archivos completos
		cout << filepath << endl;

		//por si hace falta abrir los archivos dejo el codigo para hacerlo
//		fin.open( filepath.c_str() );
//		    if (fin >> num) //leo un caracter (en este caso un numero)
//		      cout << filepath << ": " << num << endl;
//		    fin.close();
	}

	closedir(dp);
	return true;

}
