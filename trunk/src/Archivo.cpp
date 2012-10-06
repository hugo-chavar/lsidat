#include "Archivo.h"
#include "Texto.h"

using namespace std;

/**
 * Pre: El string recibido debe ser un path valido.
 * Post: Abre el archivo indicado en modo lectura-escritura,
 * si no pudo abrirlo, devuelve indicando que hubo errores.
 */
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
	//Intenta abrir el archivo en modo lectura - escritura.
	elArchivo.open(path.c_str(), std::fstream::in | std::fstream::out);
	nombre = "Lectura:" + path;
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
	//Intenta abrir el archivo en modo lectura - escritura.
	elArchivo.open(path.c_str(), std::fstream::out);
	nombre = "Escritura:" + path;

	if (!elArchivo.is_open()) {
		//Si no hubo exito en la apertura...
		//limpia los flags de control de estado del archivo.
		elArchivo.clear();
		return false;

	}
	return true;
}

/**
 * Cierra el archivo (no lo destruye fisicamente).
 */
Archivo::~Archivo() {
	//cout << "Ejecutando destructor .." << nombre << endl;
	this->cerrar();
}

bool Archivo::eof() {
	return elArchivo.eof();
}

/**
 * Pre: El archivo XML debe estar abierto para lectura.
 * Post: Lee el siguiente caracter del archivo y lo devuelve en el parametro,
 * devuelve verdadero si la lectura fue exitosa, y falso sino.
 */
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


/**
 * Pre:  El archivo debe estar abierto para lectura.
 * Post: Posiciona el cursor al comienzo del archivo.
 */
void Archivo::irAlPrincipio() {
	elArchivo.tellg();
	elArchivo.clear();
	elArchivo.seekg(0, ios::beg);
	elArchivo.seekp(0, ios::beg);
	elArchivo.tellg();
}

/**
 * Pre: El archivo debe estar abierto para lectura.
 * Post: Posiciona el cursor al final del archivo.
 */
void Archivo::irAlFinal() {
	elArchivo.tellg();
	elArchivo.clear();
	elArchivo.seekg(0, ios::end);
	elArchivo.seekp(0, ios::end);
	elArchivo.tellg();
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

void Archivo::escribirLinea(const string& palabra) {
	//long size=palabra.size();
	if (palabra.size() > 0) {
		elArchivo << palabra << endl;
		//cout << "escribiendo: " << palabra << endl;
	}
	//elArchivo.write(palabra.c_str(),size);
}
