//============================================================================
// Name        : TestRepo.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Prueba1.h"

#include "DirList.h"

using namespace std;

int main() {
	string dir;
	DirList dl;

	cout << "Indique el directorio: " << flush;
	getline(cin, dir);

	if (dl.create(dir)) {
		cout << "Salida exitosa" << endl;
	} else {
		cout << "Hubieron problemas" << endl;
	}
	Prueba1 p;
	cout << "El numero es: " << p.muestraAlgo() << endl;
	return 0;
}
