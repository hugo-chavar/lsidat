/*
 * Merger.cpp
 *
 *  Created on: Sep 14, 2012
 *      Author: hugo
 */

#include "Merger.h"
#include "Texto.h"
#include "DirList.h"

Merger::Merger() {
	string basedir = "/home/hugo/aa";
	DirList dl;
	if (dl.crearDesdeDirectorio(basedir)) {
		cout << "Salida exitosa" << endl;
	}



}

Merger::~Merger() {

}

