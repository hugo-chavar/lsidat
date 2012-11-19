/*
 * TermFile.h
 *
 *  Created on: 07/11/2012
 *      Author: Hugo Chavar
 */

#ifndef TERMFILE_H_
#define TERMFILE_H_


#include <string>
#include "Eigen/Core"
#include "Archivo.h"
#include "Texto.h"

using namespace Eigen;

class TermFile {
private:
	int pos;
	int dimension;
	int piso;
	unsigned tamaniocampo;
	Archivo t;
	string termactual;
	bool crearVector;
	bool ultimoAgregado;
	VectorXf vector;
public:
	TermFile();
	~TermFile();
	bool abrir(string);
	bool crear(string);
	void agregar(string);
	void setTamanioCampo(unsigned);
	int busquedaSecuencialTerm(string);
	int busquedaBinariaTerm(string);
	void iniciarVector(int);

	int comparar(string);
	VectorXf getVector();
	string getTerm(unsigned);
};

#endif /* TERMFILE_H_ */
