//============================================================================
// Name        : TestRepo.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "DirList.h"

using namespace std;

int main() {
	string dir;
	DirList dl;
	unsigned unaPos;

	cout <<"Indique el directorio: " << flush;
	getline(cin, dir);

	if (dl.crearDesdeDirectorio(dir)) {
		cout << "Salida exitosa" << endl;
		while(dl.haySiguiente()){
			cout << dl.siguiente() << endl;
		}
		//voy a una posicion en particular
		dl.seek(1);
		//muestro la posicion y el path completo
		unaPos = dl.posicionActual();
		cout<<"Pos "<<unaPos<<": " << dl.siguienteLargo() << endl;
	} else {
		cout << "Hubieron problemas al abrir la carpeta." << endl;
	}

	return 0;
}
