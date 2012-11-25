#include "Archivo.h"
#include "Texto.h"

using namespace std;

Archivo::Archivo(const std::string& path, bool & hayErrores) {
	hayErrores = !this->abrirLectura(path);
}

Archivo::Archivo() {
}

Archivo::Archivo(const Archivo& a) {
	//this->elArchivo=a.elArchivo;
}

Archivo&
Archivo::operator=(const Archivo& a) {
	return *this;
}

bool Archivo::abrirLectura(const std::string& path) {
	//Intenta abrir el archivo en modo lectura
	elArchivo.open(path.c_str(), std::fstream::in); //| std::fstream::out
	//nombre = "Lectura:" + path;
	//cout << "Abriendo .." << nombre << endl;

	if (!elArchivo.is_open()) {
		//Si no hubo exito en la apertura...
		//limpia los flags de control de estado del archivo.
		elArchivo.clear();
		return false;

	}
	return true;
}

bool Archivo::abrirEscritura(const std::string& path) {
	//Intenta abrir el archivo en modo escritura.
	elArchivo.open(path.c_str(), std::fstream::out);
	//nombre = "Escritura:" + path;

	if (!elArchivo.is_open()) {
		//Si no hubo exito en la apertura...
		//limpia los flags de control de estado del archivo.
		elArchivo.clear();
		return false;

	}
	return true;
}

Archivo::~Archivo() {
	//cout << "Ejecutando destructor .." << nombre << endl;
	this->cerrar();
}

bool Archivo::eof() {
	return elArchivo.eof();
}
bool Archivo::leerCaracter(char &salida) {
	char caracter;
	// lee del archivo parte de la linea, hasta haber leido:
	// 1 caracter o un fin de linea.
	elArchivo.read((char*) &caracter, 1);
	if (caracter != '\n') // ignoro los avances de lineas.
		salida = caracter;
	else
		salida = ' ';

	if (elArchivo.fail()) {
		//chequea si se ha producido un error, se devuelve false.
		elArchivo.clear();
		return false;
	}
	return true;
}

void Archivo::irAlPrincipio() {
	elArchivo.tellg();
	elArchivo.clear();
	elArchivo.seekg(0, ios::beg);
	//elArchivo.seekp(0, ios::beg);
	elArchivo.tellg();
}

void Archivo::irAlFinal() {
	elArchivo.tellg();
	elArchivo.clear();
	elArchivo.seekg(0, ios::end);
	//elArchivo.seekp(0, ios::end);
	elArchivo.tellg();
}

int Archivo::tamanio(){
	elArchivo.seekg(0, ios::end);
	int tam=elArchivo.tellg();
	return tam;
}

void Archivo::irAPos(unsigned pos){
	elArchivo.seekg(pos, ios::beg);
	//cout<<"a pos "<<elArchivo.tellg()<<" \n";
}

void Archivo::cerrar() {
	if (elArchivo.is_open()) {
		//cout << "cerrando .." << nombre << endl;
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
	//long size=palabra.size();
	if (palabra.size() > 0) {
		elArchivo << palabra << endl;
		//cout << "escribiendo: " << palabra << endl;
	}
	//elArchivo.write(palabra.c_str(),size);
}

void Archivo::escribirCampoLongitudFija(const string& campo,unsigned tamanio) {
	if (campo.size() > 0) {
		elArchivo <<left<< std::setw(tamanio)<< campo << endl;
	}
}
