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
#ifndef __ARCHIVOXML_H__
#define __ARCHIVOXML_H__


#include <fstream>
#include <sstream>
#include <vector>

enum tipoTag
{
    FIN_TAG,
    COMENTARIOS,
    NUEVO_TAG
};

class Archivo {
private:
  std::fstream  elArchivo; //Referencia al archivo.


public:

/**
 * Pre: El string recibido debe ser un path valido.
 * Post: Abre el archivo indicado en modo lectura-escritura,
 * si no pudo abrirlo, devuelve indicando que hubo errores.
 */
  Archivo(const std::string& path, bool & hayErrores);
  //constructor sin parametros
  Archivo();

  /**
   * Cierra el archivo (no lo destruye fisicamente).
   */
  ~Archivo();


/**
 * Pre: El archivo XML debe estar abierto para lectura.
 * Post: Lee el siguiente caracter del archivo y lo devuelve en el parametro,
 * devuelve verdadero si la lectura fue exitosa, y falso sino.
 */
  bool leerCaracter(char &cadena );

/**
 * Pre: El archivo XML debe estar abierto para lectura.
 * Post: Posiciona el cursor a continuacion de la proxima aparicion del caracter indicado,
 * devuelve el texto sobre el que avanzo.
 */
  bool leerHastaCaracter(char &caracterFin, std::string &textoEncontrado);

/**
 * Pre: El archivo XML debe estar abierto para lectura.
 * Post: Recorre el archivo hasta el siguiente simbolo <,
 * devuelve el texto sobre el que avanzo.
 * Nota: Llamo Etiqueta a lo que se encuentra entre los simbolos < y >.
 */
  bool leerHastaInicioEtiqueta(std::string &textoObtenido);

/**
 * Pre: El archivo XML debe estar abierto para lectura.
 * Post: Recorre el archivo hasta el siguiente simbolo >,
 * devuelve el texto sobre el que avanzo.
 * Nota: Llamo Etiqueta a lo que se encuentra entre los simbolos < y >.
 */
  bool leerHastaFinEtiqueta(std::string &textoObtenido);

 /**
  * Pre:-
  * Post:
  *  Devuelve FIN_TAG si el segundo caracter de la etiqueta es /.
  *  Devuelve COMENTARIOS si el segundo caracter de la etiqueta es ? o !.
  *  Devuelve NUEVO_TAG en otro caso.
*/
  tipoTag tipoDeTag(std::string &textoObtenido);

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

/**
 * Pre: -
 * Post: Determina si el Tag tiene contenido.
 */
  bool esContenidoDeTag(std::string &palabra);

  void cerrar();
  bool abrir(const std::string& path);
  std::string leerLinea();

};

#endif
