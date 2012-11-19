/*
 * Matrix.h
 *
 *  Created on: 05/10/2012
 *      Author: Yamila Glinsek
 */

#ifndef INITIALMATRIX_H_
#define INITIALMATRIX_H_

#define THRESHOLD_STOP_WORD 0.65

#include <iostream>
#include <string>
#include <list>
#include <math.h>
#include <sstream>
#include "RedSVD/redsvd.hpp"
#include "RedSVD/redsvdFile.hpp"
#include "Archivo.h"
#include "TermFile.h"
#include "Palabra.h"
#include "InfoPalabra.h"

using namespace std;

class InitialMatrix {
public:
	InitialMatrix();
	bool buildInitialMatrix(string inPath, string outPath, int numFiles, unsigned l, string terms,string stopwords);
	int SVD(string inPath, string outPath,int rank);
	unsigned rows();
	virtual ~InitialMatrix();
private:
	unsigned _rows;
	int calculateGlobalFrequency(list<InfoPalabra> wordInfo);
	double calculateGlobalWeight(list<InfoPalabra> wordInfo, int gFreq, int numFiles);
};

#endif /* INITIALMATRIX_H_ */
