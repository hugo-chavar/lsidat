/**
 * Clase Archivo
 *
 * Version: 1.0
 * Autor: Andres Sanabria
 *        Hugo Chavar
 *
 **/
#ifndef __ARCHIVO_H__
#define __ARCHIVO_H__

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class Archivo {
private:
	std::fstream elArchivo;
	//std::string nombre;
public:
	Archivo(const std::string& path, bool & hayErrores);
	//constructor sin parametros
	Archivo();
	//constructor de copia
	Archivo(const Archivo&);
	Archivo& operator=(const Archivo&);
	~Archivo();
	bool eof();
	bool leerCaracter(char &cadena);
	void irAlPrincipio();
	void irAlFinal();
	void irAPos(unsigned);
	void cerrar();
	bool abrirLectura(const std::string& path);
	bool abrirEscritura(const std::string& path);
	std::string leerLinea();
	std::string leerBloque();
	void escribirLinea(const string& palabra);
	void escribirCampoLongitudFija(const string& campo,unsigned tamanio);
	int tamanio();

};

#endif
