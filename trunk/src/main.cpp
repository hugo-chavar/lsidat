/*
 * main.cpp
 *
 *  Created on: Sep 7, 2012
 *      Author: andy
 */

#include "Sorter.h"
#include "InfoPalabra.h"
#include "Parser.h"
#include <iostream>
#include <list>
#include "Sorter.h"
#include "Merger.h"
#include "Archivo.h"

using namespace std;

int main()
{
	//Prueba parser
	//Parser parser = Parser();
	//parser.ProcessFiles();


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
	//Prueba Merger

	Merger m;
	//Etapa 1
	//InputDir: es donde estan los archivos originales
	//TODO el parser tendria que decirme la carpeta ya que el Sorter no lo veo
	m.setInputDir("/home/hugo/aa");
	//OutputFolder es a donde van los archivos mergeados en la primer etapa
	//es una carpeta temporal interna al programa
	m.setOutputFolderName("/home/hugo/bb");
	//setMode necesita que se haya seteado el inputDir
	m.setMode(ETAPA);
	//m.inicializarEtapa();
	//cout<<"cant de minimos: "<<m.contarMinimos()<<endl;
	//m.merge();
	//cout<<"Archivos por etapa: "<<m.calcularArchivosPorEtapa()<<endl;
	m.merge();
	
	//Etapa 2
	//ahora la salida de la etapa anterior es la entrada para la etapa final
	m.setInputDir("/home/hugo/bb");
	//indico el nombre del archivo final
	//esto se tiene que setear solo antes de hacer el merge final
	//ya que internamente se usa como outputFile las salidas intermedias de los merges
	m.setOutputFileName("/home/hugo/cc/merged.txt");
	m.setMode(FINAL);
	//crucemos los dedos
	m.merge();




	return 0;
}
