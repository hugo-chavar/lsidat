/*
 * Matrix.cpp
 *
 *  Created on: 05/10/2012
 *      Author: Yamila Glinsek
 */

#include <iomanip>
#include "Matrix.h"

Matrix::Matrix() { }

int Matrix::calculateGlobalFrequency(list<InfoPalabra> wordInfo) {
	list<InfoPalabra>::iterator iter = wordInfo.begin();
	int gFreq = 0;
	unsigned i;
	for (i=0; i < wordInfo.size(); i++) {
		gFreq += iter->getCantidad();
		advance(iter, 1);
	}
	return gFreq;
}

double Matrix::calculateGlobalWeight(list<InfoPalabra> wordInfo, int gFreq, int numFiles) {
	list<InfoPalabra>::iterator iter = wordInfo.begin();
	double gWeight = 0;
	unsigned i;
	for (i=0; i < wordInfo.size(); i++) {
		int lFreq= iter->getCantidad();
		gWeight += (lFreq/(double)gFreq) * log(lFreq/(double)gFreq);
		advance(iter, 1);
	}
	gWeight = (gWeight/(double)log(numFiles)) + 1;
	return gWeight;
}

bool Matrix::buildInitialMatrix(string inputPath, string outputPath, int numFiles) {
	Archivo inputFile;
	Archivo outputFile;
	if (!inputFile.abrirLectura(inputPath) or !outputFile.abrirEscritura(outputPath)) {
		return false;
	}
	while (!inputFile.eof()) {
		string line = inputFile.leerLinea();
		Palabra word;
		word.crearDesdeString(line);
		//
		if ((word.cantidad()/(double)numFiles) > 0.80){
			cout<<"Palabra \""<<word.getContenido()<<"\" aparece en mas del 80% de los docs"<<endl;
		}
		list <InfoPalabra> wordInfo = word.getInformacion();
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
			string sWeight = toString(weight,4); //redondeo a 4 decimales
			lineToWrite += sDoc + ":" + sWeight + " ";
			wordInfo.pop_front();
		}
		lineToWrite = lineToWrite.substr(0, lineToWrite.size()-1);
		outputFile.escribirLinea(lineToWrite);
	}
	return true;
}

void Matrix::SVD() { }

Matrix::~Matrix() { }
