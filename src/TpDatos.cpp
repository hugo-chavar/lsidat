/*
 * TpDatos.cpp
 *
 *  Created on: 05/11/2012
 *      Author: Hugo Chavar
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <unistd.h>
#include <list>
#include "Archivo.h"
#include "TermFile.h"
#include "Texto.h"
#include "Token.h"
#include "Comparador.h"
#include "Coseno.h"


using namespace std;
const int SHOW = 10;

void usage();

int main(int argc, char *argv[]) {

	if ((argc < 5) || (strcmp(argv[1], "-r") != 0)
			|| (strcmp(argv[3], "-q") != 0)) {
		usage();
		return 0;
	}

	int c;

	string repo;
	list<string> q;
	q.clear();
	while ((c = getopt(argc, argv, ":r:q:")) != -1) {

		switch (c) {
		case 'r':
			repo = optarg;
			break;
		case 'q':
			q.push_back(optarg);
			break;
		case '?':
			if (optopt == 'r')
				cerr << "Opcion -" << (char) optopt << " requiere argumentos."
						<< endl;
			else if (isprint(optopt))
				cerr << "Opcion -" << (char) optopt << " desconocida." << endl;
			else
				cerr << "Opcion -" << (char) optopt << " desconocida." << endl;
			usage();
			return 1;

			break;
		default:
			cout << "Error desconocido." << endl;
			break;
		}
	}

	if (optind < argc) {
		while (optind < argc)
			q.push_back(argv[optind++]);

	}

	Archivo admfiles;
	if (!admfiles.abrirLectura(repo + ".lsi")) {
		cerr << "No existe repositorio: " << repo << endl;
		return 0;
	}

//	string cantidades = admfiles.leerLinea();
//	vector<string> v;
//	split(v, cantidades, " ");
//	int cantTerms = atoi(v[0].c_str());
//	int cantDocs =  atoi(v[1].c_str());
//	cout<<"El repo tiene "<<cantTerms<<" terminos y "<<cantDocs<<" docs."<<endl;

	string fileList = admfiles.leerLinea();
	string matrices = admfiles.leerLinea();
	string termsFile = admfiles.leerLinea();
	string stopwordsFile = admfiles.leerLinea();

	TermFile terms, stw, docList;
	if (!terms.abrir(termsFile) || !stw.abrir(stopwordsFile)) {
		cerr << "Error al abrir archivos de terms y stopwords." << endl;
		return 0;
	}

	if (!docList.abrir(fileList)) { //repo+"/filesList.txt"
		cerr << "No se encontro el archivo:" << fileList << endl;
		return 0;
	}

	Token consulta(q);
	cout << "Ejecutando consulta.." << endl;
	consulta.sort();
	string termino;
	terms.iniciarVector();
	//cout<<terms.getVector()<<endl;
	//consulta.print();
	//return 0;
	int pos;


	while (consulta.hasNextTerm()) {
		termino = consulta.nextTerm();
		pos = stw.busquedaBinariaTerm(termino);
		//cout<<termino<<endl;
		if (pos == -1) {
			//cout<<" no es stopword";
			pos = terms.busquedaBinariaTerm(termino);
//			if (pos!=-1){
//				cout<<", es termino pos: "<<pos<<endl;
//			} else cout<<" ni termino"<<endl;
		}
//		else
//		{
//			cout<<" Es stopword pos "<<pos<<endl;
//		}
	}

	//cout<<"Este es el vector:"<<endl;
	//cout<<"fil:"<<terms.getVector().rows()<<endl;
	//cout<<terms.getVector()<<endl;

	//TODO Ranqueador. Podria nuclearse en una clase
	//cout << "Leyendo matriz. " << flush;
	Comparador comp(matrices + ".USinv", matrices + ".V", terms.getVector());
	//cout << "Listo." << endl;
	//Comparador comp(repo+"/reduced.USinv",repo+"/reduced.V",terms.getVector());
	unsigned doc = 0;
	VectorXf vector1;
	vector<Coseno> heap;
	make_heap(heap.begin(), heap.end());
	//cout << "Calculando cosenos. " << flush;
	while (comp.leerVector(vector1)) {
		//cout<<"."<<flush;
		//if ((doc % 100)==1)
		//cout<<doc<<" "<<endl;
		Coseno coseno(doc, comp.ObtenerCoseno(vector1));
		heap.push_back(coseno);
		push_heap(heap.begin(), heap.end());
		doc++;
	}
	//cout << "Listo." << endl;

	string s;

//	for (int i=0;i<6;i++){
//		s= docList.getTerm(heap.front().getDocumento());//+1);
//		cout<<"Doc No.:"<<heap.front().getDocumento()<<" Nombre:"<<s<<" coseno:" <<heap.front().getCoseno()<<endl;
//		pop_heap (heap.begin(),heap.end());
//		heap.pop_back();
//	}
	char seguir;
	cout << "Documentos ordenados por orden de relevancia:" << endl<<endl;

	s = docList.getTerm(heap.front().getDocumento());
	do {
		int cont = SHOW;
		while (heap.size() != 0 && cont > 0) {
			s = docList.getTerm(heap.front().getDocumento());
			//cout << "Documento:" << heap.front().getDocumento() << " Nombre:"<< s << " coseno:" << heap.front().getCoseno() << endl;
			cout << s << endl;
			pop_heap(heap.begin(), heap.end());
			heap.pop_back();
			cont--;
		}
		if (heap.size() > 0) {
			cout << "Mostrar los siguientes "<<SHOW<<" documentos [s/n]: "
					<< flush;
			cin >> seguir;
			seguir = tolower(seguir);
		}

	} while (heap.size() != 0 && seguir == 's');
	cout << "Consulta finalizada." << endl;
	return 0;
}

void usage() {
	cerr << "Modo de uso:" << endl << "-r   repositorio" << endl
			<< "-q   consulta a realizar[una o mas palabras]" << endl << endl
			<< "Ejemplo: TpDatos -r libros -q shakespeare borges" << endl;
}
