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

//#define DIRECTORY 				"/home/andy/Desktop/zzzz"//"/media/DATOS/Organizacion de Datos/Pruebas"
//#define DIR_SORTER 				DIRECTORY"/tempsorter"
//#define DIR_MERGER 				DIRECTORY"/tempmerger"
//#define DIR_MERGE_OUTPUT 		DIRECTORY"/merge"
//#define MERGE_FILE 				DIR_MERGE_OUTPUT"/merge.txt"
//#define DIR_MATRIX				DIRECTORY"/matrix"
//#define INITIAL_MATRIX_FILE		DIR_MATRIX"/initialMatrix.txt"
//#define DIR_ADM_FILES	 		DIRECTORY"/adm"
#define DIR_SORTER 				"/tempsorter"
#define DIR_MERGER 				"/tempmerger"
#define DIR_MERGE_OUTPUT 		"/merge"
#define MERGE_FILE 				"/merge.txt"
#define DIR_MATRIX				"/matrix"
#define INITIAL_MATRIX_FILE		"/initialMatrix.txt"
#define REDUCED_MATRIX			"/reduced"
//#define DIR_ADM_FILES	 		"/adm"
#define FILES_LIST		 		"/filesList.txt"
#define TERM_LIST		 		"/termList.txt"
#define STOPWORD_LIST		 	"/stopwordList.txt"

using namespace std;



void createDirectory(string directory) {
	string comando = "mkdir -p "+directory;
	system(comando.c_str());
}

void deleteDirectory(string directory) {
	string comando = "rm -rf "+directory;
	system(comando.c_str());
}

int main(int argc, char *argv[])
{
//	cmdline::optionparser a;
//	a.add<string>("repositorio", 'r', "nombre de repositorio", true, "");
//	a.add<string>("dir", 'd', "carpeta de documentos", true, "");
//	a.add<int>("rango", 'k', "rango de la matriz reducida", false, 200, cmdline::range(1, 65535));
//	a.add("help", 0, "muestra este mensaje");

//	bool ok=a.parse(argc, argv);
//
//	if (argc==1 || a.exist("help")){
//		cerr<<a.usage();
//		return 0;
//	}
//
//	if (!ok){
//		cerr<<a.error()<<endl<<a.usage();
//		return 0;
//	}
//
//	string rep =a.get<string>("indice");
//	string sourcefiles = a.get<string>("dir");
	//int rango = a.get<int>("rango");

	//cout<<"argc "<<argc<<endl;
	if (argc != 4){
		cerr<<"Cantidad de argumentos invalidos."<<endl;
		return 0;
	}

	string rep,sourcefiles;
	rep = argv[1];
	sourcefiles = argv[3];
	int rango = atoi(argv[2]);
	rango = abs(rango);
	if((rango < 20)||(rango>500)){
		cerr<<"Valor de reduccion fuera de rango, ingrese entre 20 y 500"<<endl;
		return 0;
	}


	string diradmfiles = rep;
	string filesList = diradmfiles+FILES_LIST;

	Parser parser;
	//se verifica si el directorio ingresado es valido
	if(!parser.setInputDirectory(sourcefiles)){
		return 0;
	}

	createDirectory(diradmfiles);
	parser.setFilesProcessedPath(filesList);

	// Parseo de documentos y creacion de archivos auxiliares ordenados.
	string dirsorter = rep+DIR_SORTER;

	string dirmerger = rep+DIR_MERGER;
	string dirmatrix = rep+DIR_MATRIX;
	string initmatrix = dirmatrix+INITIAL_MATRIX_FILE;
	string dirmergeoutput = rep+DIR_MERGE_OUTPUT;
	string mergefile = dirmergeoutput+ MERGE_FILE;
	string reducedmatrix = diradmfiles+REDUCED_MATRIX;

	string termList = diradmfiles+TERM_LIST;
	string stlist = diradmfiles+STOPWORD_LIST;
	Archivo repositorio;
	repositorio.abrirEscritura(rep+".lsi");
	repositorio.escribirLinea(filesList);
	repositorio.escribirLinea(reducedmatrix);
	repositorio.escribirLinea(termList);
	repositorio.escribirLinea(stlist);

	createDirectory(dirsorter);


	cout<<"Parsing files.."<<endl;

	parser.ProcessFiles(dirsorter);


	// Merge de los archivos auxiliares.
	createDirectory(dirmerger);
	createDirectory(dirmergeoutput);
	Merger merger;

	//Etapa 1
	//InputDir: es donde estan los archivos originales
	merger.setInputDir(dirsorter);
	//OutputFolder es a donde van los archivos mergeados en la primer etapa
	merger.setOutputFolderName(dirmerger);
	//setMode necesita que se haya seteado el inputDir
	merger.setMode(STAGE);
	cout<<"Merging stage 1..";
	merger.merge();
	cout<<"Done"<<endl;
	
	//Etapa 2
	//ahora la salida de la etapa anterior es la entrada para la etapa final
	merger.setInputDir(merger.getOutputFolderName());
	//indico el nombre del archivo final
	//esto se tiene que setear solo antes de hacer el merge final
	//ya que internamente se usa como outputFile las salidas intermedias de los merges
	merger.setOutputFileName(mergefile);
	merger.setMode(FINAL);
	cout<<"Merging stage 2..";
	merger.merge();
	cout<<"Done"<<endl;


	// Creacion de la matriz inicial.
	createDirectory(dirmatrix);
	Matrix matrix;
	cout<<"Building initial matrix.."<<endl;
	if(matrix.buildInitialMatrix(merger.getMergedFilename(), initmatrix, parser.numFiles(),termList, stlist)){
		cout<<"Done"<<endl;
	} else{
		cerr<<"Errores al construir la matriz inicial"<<endl;
	}

	cout<<"Reduccion y descomposicion en valores singulares"<<endl;
	if( matrix.SVD(initmatrix,reducedmatrix,rango)==0){
		cout<<"Descomposition done"<<endl;
	}
	else{
		cerr<<"Some Errors ocurred during Descomposition"<<endl;
	}

	cout<<"Removing some temporary files..";
	//comentar si es necesario revisar los archivos
//	deleteDirectory(dirmerger);
//	deleteDirectory(dirsorter);
//	deleteDirectory(dirmergeoutput);
//	deleteDirectory(dirmatrix);
	cout<<"Done."<<endl;


	return 0;
}
