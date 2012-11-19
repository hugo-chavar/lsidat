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
		int numFiles, unsigned fieldLength, string terms, string stopwords) {
	Archivo inputFile;
	Archivo outputFile;

	TermFile termList;
	termList.setTamanioCampo(fieldLength);
	TermFile stopwordslist;
	stopwordslist.setTamanioCampo(fieldLength);
	if (!inputFile.abrirLectura(inputPath) || !outputFile.abrirEscritura(outputPath)
			|| !termList.crear(terms)|| !stopwordslist.crear(stopwords)) {
		return false;
	}

	double ratio, gWeight,lWeight,weight;
	int gFreq, doc, lFreq;
	string line, lineToWrite, sDoc, sWeight;
	this->_rows = 0;
	line = inputFile.leerLinea();
	while (!inputFile.eof()) {

		Palabra word;
		word.crearDesdeString(line);
		ratio = word.cantidad() / (double) numFiles;
		if (ratio > THRESHOLD_STOP_WORD) {
			/** Modificacion al diseño
			 *  Las palabras que aparecen en mas de cierto porcentaje de documentos
			 *  son stopwords.
			 */
			stopwordslist.agregar(word.getContenido());
		} else {
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
			/** Modificacion al diseño
			 *  Los terminos son guardados como campos de longitud fija
			 *  de esta manera las busquedas son binarias y no secuenciales.
			 */
			termList.agregar(word.getContenido());
			this->_rows++;
		}
		line = inputFile.leerLinea();
	}
	cout<<"Filas creadas: "<<_rows<<endl;
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
