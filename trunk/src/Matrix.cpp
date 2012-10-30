/*
 * Matrix.cpp
 *
 *  Created on: 05/10/2012
 *      Author: Yamila Glinsek
 */

#include <iomanip>
#include "Matrix.h"
#include "RedSVD/redsvd.hpp"
#include "RedSVD/redsvdFile.hpp"


#define THRESHOLD_STOP_WORD 0.65

Matrix::Matrix() {
}

int Matrix::calculateGlobalFrequency(list<InfoPalabra> wordInfo) {
	list<InfoPalabra>::iterator iter = wordInfo.begin();
	int gFreq = 0;
	unsigned i;
	for (i = 0; i < wordInfo.size(); i++) {
		gFreq += iter->getCantidad();
		advance(iter, 1);
	}
	return gFreq;
}

double Matrix::calculateGlobalWeight(list<InfoPalabra> wordInfo, int gFreq,
		int numFiles) {
	list<InfoPalabra>::iterator iter = wordInfo.begin();
	double gWeight = 0;
	unsigned i;
	int lFreq;
	for (i = 0; i < wordInfo.size(); i++) {
		lFreq = iter->getCantidad();
		gWeight += (lFreq / (double) gFreq) * log(lFreq / (double) gFreq);
		advance(iter, 1);
	}
	gWeight = (gWeight / (double) log(numFiles)) + 1;
	return gWeight;
}

bool Matrix::buildInitialMatrix(string inputPath, string outputPath,
		int numFiles) {
	Archivo inputFile;
	Archivo outputFile;
	if (!inputFile.abrirLectura(inputPath)
			or !outputFile.abrirEscritura(outputPath)) {
		return false;
	}
	double ratio;
	while (!inputFile.eof()) {
		string line = inputFile.leerLinea();
		Palabra word;
		word.crearDesdeString(line);
		ratio = word.cantidad() / (double) numFiles;
		if (ratio > THRESHOLD_STOP_WORD) {
			//tratar las stop words, creando un archivo con la lista
			cout << "Palabra \"" << word.getContenido()
					<< "\" aparece en mas del "
					<< toString(THRESHOLD_STOP_WORD * 100, 0) << "% ("
					<< toString(ratio * 100, 2) << "%) de los docs" << endl;
		} else {
			//palabras que no son stop words
			//TODO crear un archivo con la lista de palabras
			list<InfoPalabra> wordInfo = word.getInformacion();
			int gFreq = calculateGlobalFrequency(wordInfo);
			double gWeight = calculateGlobalWeight(wordInfo, gFreq, numFiles);
			string lineToWrite = "";
			while (!wordInfo.empty()) {
				int doc = wordInfo.front().getDocumento();
				int lFreq = wordInfo.front().getCantidad();
				double lWeight = log(lFreq + 1);
				double weight = lWeight * gWeight;
				//string sDoc = static_cast<ostringstream*>( &(ostringstream() << doc) )->str();
				string sDoc = toString(doc);
				//string sWeight = static_cast<ostringstream*>( &(ostringstream()<< weight) )->str();
				string sWeight = toString(weight, 4); //redondeo a 4 decimales
				lineToWrite += sDoc + ":" + sWeight + " ";
				wordInfo.pop_front();
			}
			lineToWrite = lineToWrite.substr(0, lineToWrite.size() - 1);
			outputFile.escribirLinea(lineToWrite);
		}
	}
	return true;
}

int Matrix::SVD(string inputPath, string outputPath,int rank) {
	try{
	  cout<<endl<<endl<<"Empieza mi Prueba"<<endl;

	  REDSVD::fileProcess<REDSVD::SMatrixXf, REDSVD::RedSVD>(inputPath,outputPath,rank);
	  return 0;}
		catch (const string& error){
		  cerr << "Error: " << error << endl;
		  }
		return -1;
}

Matrix::~Matrix() {
}
