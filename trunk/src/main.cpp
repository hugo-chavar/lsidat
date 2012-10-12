/*
 * main.cpp
 *
 *  Created on: Sep 7, 2012
 *      Author: andy
 */

#include <iostream>
#include <list>
#include <string.h>
#include "InfoPalabra.h"
#include "Parser.h"
#include "Sorter.h"
#include "Merger.h"
#include "Archivo.h"
#include "Matrix.h"

#define DIRECTORY 				"/media/DATOS/Organizacion de Datos/Pruebas"
#define DIR_SORTER 				DIRECTORY"/tempsorter"
#define DIR_MERGER 				DIRECTORY"/tempmerger"
#define DIR_MERGE_OUTPUT 		DIRECTORY"/merge"
#define MERGE_FILE 				DIR_MERGE_OUTPUT"/merge.txt"
#define DIR_MATRIX				DIRECTORY"/matrix"
#define INITIAL_MATRIX_FILE		DIR_MATRIX"/initialMatrix.txt"
#define Str(x) 					#x
#define Xstr(x) 				Str(x)

using namespace std;



void createDirectory(const char* directory) {
	//TODO: esto debe corregirse.. es lento, inseguro, ineficiente...
	char comando[100];
	strcpy(comando,"mkdir -p ");
	strcat(comando,directory);
	system(comando);
}


int main()
{

	// Parseo de documentos y creacion de archivos auxiliares ordenados.
	createDirectory(Xstr(DIR_SORTER));
	Parser parser;
	parser.ProcessFiles(DIRECTORY, DIR_SORTER);


	// Merge de los archivos auxiliares.
	createDirectory(Xstr(DIR_MERGER));
	createDirectory(Xstr(DIR_MERGE_OUTPUT));
	Merger m;

	//Etapa 1
	//InputDir: es donde estan los archivos originales
	m.setInputDir(DIR_SORTER);
	//OutputFolder es a donde van los archivos mergeados en la primer etapa
	//es una carpeta temporal interna al programa
	m.setOutputFolderName(DIR_MERGER);
	//setMode necesita que se haya seteado el inputDir
	m.setMode(STAGE);
	//m.initializeStage();
	//cout<<"cant de minimos: "<<m.contarMinimos()<<endl;
	//m.merge();
	//cout<<"Archivos por etapa: "<<m.calcularArchivosPorEtapa()<<endl;
	m.merge();
	
	//Etapa 2
	//ahora la salida de la etapa anterior es la entrada para la etapa final
	m.setInputDir(DIR_MERGER);
	//indico el nombre del archivo final
	//esto se tiene que setear solo antes de hacer el merge final
	//ya que internamente se usa como outputFile las salidas intermedias de los merges
	m.setOutputFileName(MERGE_FILE);
	m.setMode(FINAL);
	m.merge();


	// Creacion de la matriz inicial.
	createDirectory(Xstr(DIR_MATRIX));
	Matrix matrix;
	matrix.buildInitialMatrix(MERGE_FILE, INITIAL_MATRIX_FILE, parser.numFiles());


	//Prueba Sorter
/*
	Sorter* sorter=new Sorter();

	sorter->agregarPalabra("hola",1);
	sorter->agregarPalabra("andres",1);
	sorter->agregarPalabra("como",1);
	sorter->agregarPalabra("es",1);
	sorter->agregarPalabra("como",1);
	sorter->agregarPalabra("tp",1);
	sorter->agregarPalabra("datos",1);
	sorter->agregarPalabra("sos",1);
	sorter->agregarPalabra("como",1);
	sorter->agregarPalabra("hola",2);
	sorter->agregarPalabra("hola",2);
	sorter->agregarPalabra("hola",2);
	sorter->agregarPalabra("andres",2);
	sorter->agregarPalabra("como",2);
	sorter->agregarPalabra("te",3);
	sorter->terminar();
	delete sorter;
*/

	return 0;
}
