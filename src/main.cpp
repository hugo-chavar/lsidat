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

#define DIR_MERGER 			DIRECTORY/tempmerger
#define DIR_MERGE_OUTPUT 	DIRECTORY/merge
#define MERGE_FILE 			DIR_MERGE_OUTPUT/merge.txt


using namespace std;

int main()
{
	Parser parser;
	parser.ProcessFiles();

	//creo una carpeta para q el MERGER tire ahi la salida
	//TODO: esto debe corregirse.. es lento, inseguro, ineficiente...bla bla
	char comando[100];
	strcpy(comando,"mkdir -p ");
	strcat(comando,Xstr(DIR_MERGER));
	system(comando);
	strcpy(comando,"mkdir -p ");
	strcat(comando,Xstr(DIR_MERGE_OUTPUT));
	system(comando);
	//fin de creacion de dir temporal


	Merger m;

	//Etapa 1
	//InputDir: es donde estan los archivos originales
	m.setInputDir(Xstr(DIR_SORTER));
	//OutputFolder es a donde van los archivos mergeados en la primer etapa
	//es una carpeta temporal interna al programa
	m.setOutputFolderName(Xstr(DIR_MERGER));
	//setMode necesita que se haya seteado el inputDir
	m.setMode(STAGE);
	//m.initializeStage();
	//cout<<"cant de minimos: "<<m.contarMinimos()<<endl;
	//m.merge();
	//cout<<"Archivos por etapa: "<<m.calcularArchivosPorEtapa()<<endl;
	m.merge();
	
	//Etapa 2
	//ahora la salida de la etapa anterior es la entrada para la etapa final
	m.setInputDir(Xstr(DIR_MERGER));
	//indico el nombre del archivo final
	//esto se tiene que setear solo antes de hacer el merge final
	//ya que internamente se usa como outputFile las salidas intermedias de los merges
	m.setOutputFileName(Xstr(MERGE_FILE));
	m.setMode(FINAL);
	m.merge();


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
