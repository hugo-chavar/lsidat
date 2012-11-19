/*
 * main.cpp
 *
 *  Created on: 07/09/2012
 *      Author: Andres Sanabria
 */

#include <iostream>
#include <list>
#include <string.h>
#include "Parser.h"
#include "Sorter.h"
#include "Merger.h"
#include "Archivo.h"
#include "InitialMatrix.h"


#define DIR_SORTER 				"/tempsorter"
#define DIR_MERGER 				"/tempmerger"
#define DIR_MERGE_OUTPUT 		"/merge"
#define MERGE_FILE 				"/merge.txt"
#define DIR_MATRIX				"/matrix"
#define INITIAL_MATRIX_FILE		"/initialMatrix.txt"
#define REDUCED_MATRIX			"/reduced"
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


	createDirectory(dirsorter);

	cout<<"Realizando parseo de archivos.."<<flush;

	parser.ProcessFiles(dirsorter);
	cout<<"Listo."<<endl;

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
	cout<<"Realizando merge etapa 1.."<<flush;
	merger.merge();
	cout<<"Listo."<<endl;
	
	//Etapa 2
	//ahora la salida de la etapa anterior es la entrada para la etapa final
	merger.setInputDir(merger.getOutputFolderName());
	//indico el nombre del archivo final
	//esto se tiene que setear solo antes de hacer el merge final
	//ya que internamente se usa como outputFile las salidas intermedias de los merges
	merger.setOutputFileName(mergefile);
	merger.setMode(FINAL);
	cout<<"Realizando merge etapa 2.."<<flush;
	merger.merge();
	cout<<"Listo."<<endl;

	createDirectory(dirmatrix);
	InitialMatrix matrix;
	cout<<"Construyendo matriz inicial.."<<endl;
	if(matrix.buildInitialMatrix(merger.getMergedFilename(), initmatrix, parser.filesCount(),parser.maxLengthWord(),termList, stlist)){
		cout<<"Listo."<<endl;
	} else{
		cerr<<"Errores al construir la matriz inicial."<<endl;
	}

	cout<<"Reduciendo dimensiones de la matriz.."<<endl;
	if( matrix.SVD(initmatrix,reducedmatrix,rango)==0){
		cout<<"Listo."<<endl;
	}
	else{
		cerr<<"Errores al reducir la matriz."<<endl;
	}

	cout<<"Eliminando archivos temporales.."<<flush;
//	deleteDirectory(dirmerger);
//	deleteDirectory(dirsorter);
//	deleteDirectory(dirmergeoutput);
//	deleteDirectory(dirmatrix);
	cout<<"Listo."<<endl;

	cout<<"Guardando repositorio.."<<endl;
	Archivo repositorio;
	repositorio.abrirEscritura(rep+".lsi");
	repositorio.escribirLinea(toString(matrix.rows())+" "+toString(parser.filesCount()));
	repositorio.escribirLinea(filesList);
	repositorio.escribirLinea(reducedmatrix);
	repositorio.escribirLinea(termList);
	repositorio.escribirLinea(stlist);
	cout<<"Repositorio \""<<rep<<"\" creado exitosamente."<<endl;


	return 0;
}
