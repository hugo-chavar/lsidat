/*
 * Comparador.h
 *
 *  Created on: 08/11/2012
 *      Author: Andres Sanabria
 */

#ifndef COMPARADOR_H_
#define COMPARADOR_H_

#include "Eigen/Core"
#include "Archivo.h"
#include "RedSVD/redsvdFile.hpp"

using namespace std;
using namespace Eigen;

class Comparador {
public:
	Comparador(const string& fp_USinv,const string& fp_V,VectorXf consulta);
	bool leerVector(VectorXf& vectorXf);
	float ObtenerCoseno(const VectorXf& vector);
	~Comparador();

private:
	void generarConsultaRed(string fp_USinv, VectorXf& consulta);
	VectorXf consultaRed;
	Archivo V;
};

#endif /* COMPARADOR_H_ */
