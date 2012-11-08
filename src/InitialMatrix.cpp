/*
 * Matrix.cpp
 *
 *  Created on: 05/10/2012
 *      Author: Yamila Glinsek
 */

#include "InitialMatrix.h"


InitialMatrix::InitialMatrix() {
}

int InitialMatrix::calculateGlobalFrequency(list<InfoPalabra> wordInfo) {
	list<InfoPalabra>::iterator iter = wordInfo.begin();
	int gFreq = 0;
	unsigned i;
	for (i = 0; i < wordInfo.size(); i++) {
		gFreq += iter->getCantidad();
		advance(iter, 1);
	}
	return gFreq;
}

double InitialMatrix::calculateGlobalWeight(list<InfoPalabra> wordInfo, int gFreq,
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

bool InitialMatrix::buildInitialMatrix(string inputPath, string outputPath,
		int numFiles, string terms, string stopwords) {
	Archivo inputFile;
	Archivo outputFile;

	TermFile termList;
	TermFile stopwordslist;
	if (!inputFile.abrirLectura(inputPath) || !outputFile.abrirEscritura(outputPath)
			|| !termList.crear(terms)|| !stopwordslist.crear(stopwords)) {
		return false;
	}

	double ratio, gWeight,lWeight,weight;
	int gFreq, doc, lFreq;
	string line, lineToWrite, sDoc, sWeight;
	this->_rows = 0;

	while (!inputFile.eof()) {
		line = inputFile.leerLinea();
		Palabra word;
		word.crearDesdeString(line);
		ratio = word.cantidad() / (double) numFiles;
		if (ratio > THRESHOLD_STOP_WORD) {
			//tratar las stop words, creando un archivo con la lista
//			cout << "Palabra \"" << word.getContenido()
//					<< "\" aparece en mas del "
//					<< toString(THRESHOLD_STOP_WORD * 100, 0) << "% ("
//					<< toString(ratio * 100, 2) << "%) de los docs" << endl;
			stopwordslist.agregar(word.getContenido());
		} else {
			//palabras que no son stop words
			//TODO crear un archivo con la lista de palabras
			list<InfoPalabra> wordInfo = word.getInformacion();
			gFreq = calculateGlobalFrequency(wordInfo);
			gWeight = calculateGlobalWeight(wordInfo, gFreq, numFiles);
			lineToWrite = "";
			while (!wordInfo.empty()) {
				doc = wordInfo.front().getDocumento();
				lFreq = wordInfo.front().getCantidad();
				lWeight = log(lFreq + 1);
				weight = lWeight * gWeight;
				sDoc = toString(doc);
				sWeight = toString(weight, 4); //redondeo a 4 decimales
				lineToWrite += sDoc + ":" + sWeight + " ";
				wordInfo.pop_front();
			}
			lineToWrite = lineToWrite.substr(0, lineToWrite.size() - 1);
			outputFile.escribirLinea(lineToWrite);
			termList.agregar(word.getContenido());
			this->_rows++;
		}
	}
	return true;
}

int InitialMatrix::SVD(string inputPath, string outputPath,int rank) {
	try{
	  //cout<<endl<<endl<<"Empieza mi Prueba"<<endl;
	  //cout<<"outputPath "<<outputPath<<endl;

	  REDSVD::fileProcess<REDSVD::SMatrixXf, REDSVD::RedSVD>(inputPath,outputPath,rank);
	  return 0;}
		catch (const string& error){
		  cerr << "Error: " << error << endl;
		  }
		return -1;
}

unsigned InitialMatrix::rows(){
	return this->_rows;
}

InitialMatrix::~InitialMatrix() {
}
