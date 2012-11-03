/*
 * Matrix.h
 *
 *  Created on: 05/10/2012
 *      Author: Yamila Glinsek
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#define THRESHOLD_STOP_WORD 0.65

#include <iostream>
#include <string>
#include <list>
#include <math.h>
#include <sstream>
#include "RedSVD/redsvd.hpp"
#include "RedSVD/redsvdFile.hpp"
#include "Archivo.h"
#include "Palabra.h"
#include "InfoPalabra.h"

using namespace std;

class Matrix {
public:
	Matrix();
	bool buildInitialMatrix(string inputPath, string outputPath, int numFiles, string terms,string stopwords);
	int SVD(string inputPath, string outputPath,int rank);
	virtual ~Matrix();
private:
	int calculateGlobalFrequency(list<InfoPalabra> wordInfo);
	double calculateGlobalWeight(list<InfoPalabra> wordInfo, int gFreq, int numFiles);
};

#endif /* MATRIX_H_ */
