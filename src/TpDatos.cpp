/*
 * TpDatos.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: Hugo Chavar
 */

#include <iostream>
#include <string.h>
#include <unistd.h>    /* for getopt */
#include <list>
#include "Archivo.h"
#include "TermFile.h"
#include "Texto.h"

using namespace std;

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
	list<string>::iterator i;
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

	Archivo admfiles;
	if (!admfiles.abrirLectura(repo+".lsi")){
		cerr<<"No existe repositorio: "<<repo<<endl;
		return 0;
	}
	string cantidades = admfiles.leerLinea();
	vector<string> v;
	split(v, cantidades, " ");
	int cantTerms = atoi(v[0].c_str());
	int cantDocs =  atoi(v[1].c_str());
	cout<<"El repo tiene "<<cantTerms<<" terminos y "<<cantDocs<<" docs."<<endl;
	string fileList = admfiles.leerLinea();
	string matrices = admfiles.leerLinea();
	string termsFile = admfiles.leerLinea();
	string stopwordsFile = admfiles.leerLinea();

	TermFile terms, stw;
	if (!terms.abrir(termsFile) || !stw.abrir(stopwordsFile)){
		cerr<<"Error al abrir archivos de terms y stopwords."<<endl;
	}

	if (optind < argc) {
		//cout<<"non-option ARGV-elements: "<<endl;
		while (optind < argc)
			q.push_back(argv[optind++]);

	}
	cout << "Query:" << endl;
	q.sort();
	i = q.begin();
	string termino;
	terms.iniciarVector(cantTerms);
	int pos;
	while (q.size() > 0) {
		termino = *i ;
		pos = terms.buscarTerm(termino);
		cout<<termino;
		if(pos==-1){
			cout<<" no es termino";
			pos= stw.buscarTerm(termino);
			if (pos>0){
				cout<<", es stopword pos: "<<pos<<endl;
			} else cout<<" ni stopword"<<endl;
		} else
		{
			cout<<" Es termino pos "<<pos<<endl;
		}

		q.pop_front();
		i = q.begin();
	}

	cout<<"Este es el vector:"<<endl;
	//TODO: Andy vos tendrias que partir de ese getVector y hacer la multiplicacion
	//nota: este vector es bastante largo.. hay q comentar el cout si se esta probando otra cosa
	// yo lo dejo como algo informativo de que mi parte funciona mas o menos bien. Hugo
	cout<<terms.getVector()<<endl;

	return 0;
}

void usage() {
	cerr << "Modo de uso:" << endl << "-r   repositorio" << endl
			<< "-q   consulta a realizar[una o mas palabras]" << endl << endl
			<< "Ejemplo: TpDatos -r libros -q shakespeare borges" << endl;
}
