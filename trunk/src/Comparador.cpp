/*
 * Comparador.cpp
 *
 *  Created on: 08/11/2012
 *      Author: Andres Sanabria
 */

#include "Comparador.h"

Comparador::Comparador(const string& fp_USinv,const string& fp_V,VectorXf consulta) {

		this->generarConsultaRed(fp_USinv,consulta);
		if(!V.abrirLectura(fp_V))
			cerr<<"No se ha encontrado el archivo de la matriz V"<<endl;

}

Comparador::~Comparador() {
	V.cerrar();
}

void Comparador::generarConsultaRed(string fp_USinv,VectorXf& consulta){
	MatrixXf USinv;
	REDSVD::readMatrix(fp_USinv,USinv);
	consultaRed=(consulta.transpose()*USinv).transpose();
}

float Comparador::ObtenerCoseno(const VectorXf& vector){

			float cos;
			cos = consultaRed.transpose() * vector;

		return cos;
}

bool Comparador::leerVector(VectorXf& vectorXf){

	  vector< float > vector;
	  string linea= V.leerLinea();
	  istringstream string(linea);
	  if(!string.eof()){
		  float valor;
	  	  while (string >> valor){
	  		  vector.push_back(valor);
	  	  }

	  	  size_t posiciones = vector.size();
	  	  if (posiciones == 0) return false;

	  	  vectorXf.resize(posiciones);

	  	  for (size_t i = 0; i < posiciones; ++i){
		      vectorXf(i) = vector[i];
	  	  }
	  	  return true;
	  }
	  else
		  return false;
}
