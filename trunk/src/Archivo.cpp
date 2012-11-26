#include "Archivo.h"
#include "Texto.h"

using namespace std;

Archivo::Archivo(const std::string& path, bool & hayErrores) {
	hayErrores = !this->abrirLectura(path);
}

Archivo::Archivo() {
}

Archivo::Archivo(const Archivo& a) {
}

Archivo&
Archivo::operator=(const Archivo& a) {
	return *this;
}

bool Archivo::abrirLectura(const std::string& path) {
	elArchivo.open(path.c_str(), std::fstream::in);

	if (!elArchivo.is_open()) {
		elArchivo.clear();
		return false;

	}
	return true;
}

bool Archivo::abrirEscritura(const std::string& path) {
	elArchivo.open(path.c_str(), std::fstream::out);

	if (!elArchivo.is_open()) {
		elArchivo.clear();
		return false;

	}
	return true;
}

Archivo::~Archivo() {
	this->cerrar();
}

bool Archivo::eof() {
	return elArchivo.eof();
}

void Archivo::irAlPrincipio() {
	elArchivo.tellg();
	elArchivo.clear();
	elArchivo.seekg(0, ios::beg);
	elArchivo.tellg();
}

void Archivo::irAlFinal() {
	elArchivo.tellg();
	elArchivo.clear();
	elArchivo.seekg(0, ios::end);
	elArchivo.tellg();
}

int Archivo::tamanio(){
	elArchivo.seekg(0, ios::end);
	int tam=elArchivo.tellg();
	return tam;
}

void Archivo::irAPos(unsigned pos){
	elArchivo.seekg(pos, ios::beg);
}

void Archivo::cerrar() {
	if (elArchivo.is_open()) {
		elArchivo.close();
	}
}

string Archivo::leerLinea() {
	string s;
	getline(elArchivo, s);
	return s;
}

string Archivo::leerBloque() {
	string s;
	getline(elArchivo, s,'\0');
	return s;
}

void Archivo::escribirLinea(const string& palabra) {
	if (palabra.size() > 0) {
		elArchivo << palabra << endl;
	}
}

void Archivo::escribirCampoLongitudFija(const string& campo,unsigned tamanio) {
	if (campo.size() > 0) {
		elArchivo <<left<< std::setw(tamanio)<< campo << endl;
	}
}
