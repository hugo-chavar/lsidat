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

#define DIRECTORY 				"/home/hugo/Downloads/classic"//"/media/DATOS/Organizacion de Datos/Pruebas"
#define DIR_SORTER 				DIRECTORY"/tempsorter"
#define DIR_MERGER 				DIRECTORY"/tempmerger"
#define DIR_MERGE_OUTPUT 		DIRECTORY"/merge"
#define MERGE_FILE 				DIR_MERGE_OUTPUT"/merge.txt"
#define DIR_MATRIX				DIRECTORY"/matrix"
#define INITIAL_MATRIX_FILE		DIR_MATRIX"/initialMatrix.txt"
#define DIR_ADM_FILES	 		DIRECTORY"/adm"
//lo siguiente no se usa, no quiero modificar el parser, x ahora lo harcodeo dentro del parser
//#define FILES_LIST		 		DIR_ADM_FILES"/fileList.txt"
#define Str(x) 					#x
#define Xstr(x) 				Str(x)

using namespace std;



void createDirectory(const char* directory) {
	char comando[100];
	strcpy(comando,"mkdir -p ");
	strcat(comando,directory);
	system(comando);
}

void deleteDirectory(const char* directory) {
	char comando[100];
	strcpy(comando,"rm -rf ");
	strcat(comando,directory);
	system(comando);
}

int main()
{

	// Parseo de documentos y creacion de archivos auxiliares ordenados.
	createDirectory(Xstr(DIR_SORTER));
	createDirectory(Xstr(DIR_ADM_FILES));
	Parser parser;
	cout<<"Parsing files.."<<endl;
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
	cout<<"Merging stage 1..";
	m.merge();
	cout<<"Done"<<endl;
	
	//Etapa 2
	//ahora la salida de la etapa anterior es la entrada para la etapa final
	m.setInputDir(DIR_MERGER);
	//indico el nombre del archivo final
	//esto se tiene que setear solo antes de hacer el merge final
	//ya que internamente se usa como outputFile las salidas intermedias de los merges
	m.setOutputFileName(MERGE_FILE);
	m.setMode(FINAL);
	cout<<"Merging stage 2..";
	m.merge();
	cout<<"Done"<<endl;


	// Creacion de la matriz inicial.
	createDirectory(Xstr(DIR_MATRIX));
	Matrix matrix;
	cout<<"Building initial matrix.."<<endl;
	matrix.buildInitialMatrix(MERGE_FILE, INITIAL_MATRIX_FILE, parser.numFiles());
	cout<<"Done"<<endl;

	cout<<"Removing some temporary files..";
	//solo borro el tempmerger como ejemplo, comentar si es necesario revisar los archivos
	deleteDirectory(Xstr(DIR_MERGER));
	cout<<"Done."<<endl;


	return 0;
}
