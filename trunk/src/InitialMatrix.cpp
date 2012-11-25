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

double InitialMatrix::calculateGlobalWeight(list<InfoPalabra> wordInfo,
		int gFreq, int numFiles) {
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

double InitialMatrix::calculateThresholdStopWords(int n) {
	/*
	 * Calculo de una cota del porcentaje de apariciones de un termino dentro del dataset.
	 * Si n es menor que 10 el umbral es mayor a 1 (100%), y esto equivale a no usar stopwords, y a medida
	 * que n crece este porcentaje baja.
	 * Para n muy grande el resultado se vuelve negativo, entonces se pone un piso del 40%
	 */
	double threshold = 1 - 0.05 * log(0.1 * n);
	return max(threshold, 0.40);
}

bool InitialMatrix::buildInitialMatrix(string inputPath, string outputPath,
		int numFiles, unsigned fieldLength, string terms, string stopwords) {
	Archivo inputFile;
	Archivo outputFile;

	TermFile termList;
	termList.setTamanioCampo(fieldLength);
	TermFile stopwordslist;
	stopwordslist.setTamanioCampo(fieldLength);
	if (!inputFile.abrirLectura(inputPath)
			|| !outputFile.abrirEscritura(outputPath) || !termList.crear(terms)
			|| !stopwordslist.crear(stopwords)) {
		return false;
	}

	double ratio, threshold_stop_word, gWeight, lWeight, weight;
	int gFreq, doc, lFreq;
	string line, lineToWrite, sDoc, sWeight;
	this->_rows = 0;
	/*
	 * Se define un umbral para la aparicion de terminos con respecto a la cantidad
	 * de documentos, si un termino aparece por encima de ese porcentaje es considerado stop-word.
	 */

	threshold_stop_word = calculateThresholdStopWords(numFiles);

	line = inputFile.leerLinea();
	while (!inputFile.eof()) {

		Palabra word;
		word.crearDesdeString(line);
		ratio = word.cantidad() / (double) numFiles;
		if (ratio > threshold_stop_word) {
			/** Modificacion al diseño
			 *  Las palabras que aparecen en mas de cierto porcentaje de documentos
			 *  son stop-words. El porcentaje es funcion de la cantidad de documentos,
			 *  con pocos documentos es cercano a 95% decreciendo asintoticamente a medida que
			 *  aumenta la cantidad de documentos. Se agrega debido a que no hay un porcentaje que sea
			 *  optimo para todas las cantidades de documentos, ya que 70% es muy bajo cuando se tiene
			 *  alrededor de 50 documentos pero es alto cuando se tienen 5000 docs.
			 *  Ademas las stop-words son guardadas como campos de longitud fija,
			 *  de manera que se puedan hacer busquedas binarias.
			 */
			//cout<<"Stopword: "+word.getContenido()+" "<<toString(ratio,2)<<endl;
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
	cout << "Filas creadas: " << _rows << endl;
	return true;
}

int InitialMatrix::SVD(string inputPath, string outputPath, int rank) {
	try {
		REDSVD::fileProcess<REDSVD::SMatrixXf, REDSVD::RedSVD>(inputPath,
				outputPath, rank);
		return 0;
	} catch (const string& error) {
		cerr << "Error: " << error << endl;
	}
	return -1;
}

unsigned InitialMatrix::rows() {
	return this->_rows;
}

InitialMatrix::~InitialMatrix() {
}
