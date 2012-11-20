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
		while (optind < argc)
			q.push_back(argv[optind++]);

	}
	Token consulta(q);
	cout << "Query:" << endl;
	consulta.sort();
	string termino;
	terms.iniciarVector(cantTerms);
	//cout<<terms.getVector()<<endl;
	consulta.print(); //
	//return 0;
	cout<<"Busqueda secuencial:"<<endl;
	int pos;
	while (consulta.hasNextTerm()) {
		termino = consulta.nextTerm() ;
		pos = terms.busquedaSecuencialTerm(termino);
		cout<<termino<<endl;
		if(pos==-1){
			cout<<" no es termino";
			pos = stw.busquedaSecuencialTerm(termino);
			if (pos>0){
				cout<<", es stopword pos: "<<pos<<endl;
			} else cout<<" ni stopword"<<endl;
		} else
		{
			cout<<" Es termino pos "<<pos<<endl;
		}
	}
	//pruebas de la busqueda binaria
	consulta.print();
	cout<<"Busqueda binaria:"<<endl;
	//TODO inicio vector de stopwords por la busqueda binaria CORREGIR FIXME FIXME
	stw.iniciarVector(8);
	while (consulta.hasNextTerm()) {
		termino = consulta.nextTerm() ;
		pos = terms.busquedaBinariaTerm(termino);
		cout<<termino<<endl;
		if(pos==-1){
			cout<<" no es termino";
			pos = stw.busquedaBinariaTerm(termino);
			if (pos>0){
				cout<<", es stopword pos: "<<pos<<endl;
			} else cout<<" ni stopword"<<endl;
		} else
		{
			cout<<" Es termino pos "<<pos<<endl;
		}
	}



	cout<<"Este es el vector:"<<endl;
	cout<<"fil:"<<terms.getVector().rows()<<endl;
	//cout<<terms.getVector()<<endl;

	//TODO Ranqueador. Podria nuclearse en una clase
	Comparador comp(repo+"/reduced.USinv",repo+"/reduced.V",terms.getVector());
	unsigned doc=0;
	VectorXf vector1;
	vector<Coseno> heap;
	make_heap(heap.begin(),heap.end());
	while(comp.leerVector(vector1))	{
		Coseno coseno(doc,comp.ObtenerCoseno(vector1));
		heap.push_back(coseno);
		push_heap (heap.begin(),heap.end());
		doc++;
	}
	//make_heap(heap.begin(),heap.end());

	TermFile docList;
	if(!docList.abrir(repo+"/filesList.txt")){
		cout<<"No se encontro el archivo:"<<repo+"/filesList.txt"<<endl;
		return 0;
	}
//	ifstream fp_doc;
//	fp_doc.open((repo+"/filesList.txt").c_str(),std::fstream::in);
//	if (!fp_doc.is_open()){
//		cout<<"No se encontro el archivo:"<<repo+"/filesList.txt"<<endl;
//		return 0;
//	}

	string s;
	//getline(fp_doc,s);
	//while(heap.size()!=0){
	for (int i=0;i<30;i++){
		//TODO Por el momento lo hago asi.Funciona si todos los nombres de doc tienen el mismo largo.
		//Se lee una linea,se mira su longitud y se multiplica el doc por esa long
		//El problema es que al ser de texto sino hay que leer uno por una las lineas cada vez hasta llegar al doc indicado.
		//fp_doc.seekg(heap.front().getDocumento()*(s.size()+1),ios::beg);
		//getline(fp_doc,s);
		s= docList.getTerm(heap.front().getDocumento()+1);
		cout<<"Documento:"<<heap.front().getDocumento()<<" Nombre:"<<s<<" coseno:" <<heap.front().getCoseno()<<endl;
		pop_heap (heap.begin(),heap.end());
		heap.pop_back();
	}

	return 0;
}

void usage() {
	cerr << "Modo de uso:" << endl << "-r   repositorio" << endl
			<< "-q   consulta a realizar[una o mas palabras]" << endl << endl
			<< "Ejemplo: TpDatos -r libros -q shakespeare borges" << endl;
}
