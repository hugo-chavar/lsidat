//============================================================================
// Name        : TestRepo.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "DirList.h"
#include "Archivo.h"
#include "Palabra.h"
#include "Merger.h"

using namespace std;

int main() {
	string dir,unArchivo,unTexto;
	DirList dl;
	unsigned unaPos;
	bool abrioOk;
	Palabra pal("");


	cout <<"Indique el directorio: " << flush;
	getline(cin, dir);

	if (dl.crearDesdeDirectorio(dir)) {
		cout << "Salida exitosa" << endl;
		while(dl.haySiguiente()){
			//muestro el nombre del archivo sin el path completo
			cout << dl.siguiente() << endl;
		}
		//voy a una posicion en particular
		dl.seek(1);
		//muestro la posicion y el path completo
		unaPos = dl.posicionActual();
		unArchivo = dl.siguienteLargo() ;
		cout<<"Pos "<<unaPos<<": " <<unArchivo << endl;
		//pruebo la clase Archivo, abro y leo algo
		Archivo archivoActual(unArchivo,abrioOk);
		if(abrioOk){
			//leo una parte y la ignoro
			char caracterFin = '#';
			archivoActual.leerHastaCaracter(caracterFin,unTexto);
			caracterFin = '.';
			archivoActual.leerHastaCaracter(caracterFin,unTexto);
			unTexto = trim(unTexto);
			cout << "Se abrio bien el archivo y se leyo este txt: "<<unTexto << endl;

		} else {
			cout << "No se pudo abrir: "<<unArchivo << endl;
		}
		//otra forma de hacer lo mismo
		Archivo archivoActual2;
		if(archivoActual2.abrir(unArchivo)){
			//leo una parte y la ignoro
			char caracterFin = '#';
			archivoActual2.leerHastaCaracter(caracterFin,unTexto);
			caracterFin = '.';
			archivoActual2.leerHastaCaracter(caracterFin,unTexto);
			unTexto = trim(unTexto);
			cout << "Se abrio bien el archivo y se leyo este txt: "<<unTexto << endl;

		} else {
			cout << "No se pudo abrir: "<<unArchivo << endl;
		}
	} else {
		cout << "Hubieron problemas al abrir la carpeta." << endl;
	}
	string a ="string, 1, 4,6, 133";
	//pal.crearDesdeString(a);
	Merger m;

	return 0;
}