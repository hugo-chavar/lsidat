/******************************************************************************
 *                   Algoritmos y Programaci�n II - 75.41                     *
 *                        C�tedra Ing. Patricia Calvo                         *
 *            Facultad de Ingenier�a - Universidad de Buenos Aires            *
 *                                - Grupo 9 -                                 *
 *                             Juan Fuld (93395)                              *
 *                          Andr�s Sanabria (93403)                           *
 *                            F�lix Reyero (92979)                            *
 *                             Hugo Chavar (90541)                            *
 ******************************************************************************/

/**
 * Clase Archivo XML
 *
 * Versi�n: 1.0
 * Autor: Andr�s Sanabria
 *        Hugo Chavar
 *
 **/
#ifndef __ARCHIVO_H__
#define __ARCHIVO_H__


#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;


class Archivo {
private:
  std::fstream  elArchivo;
  std::string nombre;


public:

/**
 * Pre: El string recibido debe ser un path valido.
 * Post: Abre el archivo indicado en modo lectura-escritura,
 * si no pudo abrirlo, devuelve indicando que hubo errores.
 */
  Archivo(const std::string& path, bool & hayErrores);
  //constructor sin parametros
  Archivo();
  //constructor de copia
  Archivo(const Archivo&);
  Archivo& operator=(const Archivo&);

  /**
   * Cierra el archivo (no lo destruye fisicamente).
   */
  ~Archivo();

  bool eof();


/**
 * Pre: El archivo XML debe estar abierto para lectura.
 * Post: Lee el siguiente caracter del archivo y lo devuelve en el parametro,
 * devuelve verdadero si la lectura fue exitosa, y falso sino.
 */
  bool leerCaracter(char &cadena );

/**
 * Pre:  El archivo XML debe estar abierto para lectura.
 * Post: Posiciona el cursor al comienzo del archivo.
 */
  void irAlPrincipio();

/**
 * Pre: El archivo XML debe estar abierto para lectura.
 * Post: Posiciona el cursor al final del archivo.
 */
  void irAlFinal();

  void cerrar();
  bool abrirLectura(const std::string& path);
  bool abrirEscritura(const std::string& path);
  std::string leerLinea();
  void escribirLinea(const string& palabra);

};

#endif
