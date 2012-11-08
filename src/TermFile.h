/*
 * TermFile.h
 *
 *  Created on: Nov 7, 2012
 *      Author: hugo
 */

#ifndef TERMFILE_H_
#define TERMFILE_H_

#include "Archivo.h"
#include <string>
#include "Eigen/Core"

using namespace Eigen;

class TermFile {
private:
	int pos;
	int dimension;
	Archivo t;
	string actual;
	bool crearVector;
	bool ultimoAgregado;
	VectorXf vector;
public:
	TermFile();
	~TermFile();
	bool abrir(string);
	bool crear(string);
	void agregar(string);
	int buscarTerm(string);
	void iniciarVector(int);
	int comparar(string);
	VectorXf getVector();
};

#endif /* TERMFILE_H_ */
