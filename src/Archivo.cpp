#include "Archivo.h"
#include "Texto.h"

using namespace std;

/**
 * Pre: El string recibido debe ser un path valido.
 * Post: Abre el archivo indicado en modo lectura-escritura,
 * si no pudo abrirlo, devuelve indicando que hubo errores.
 */
Archivo::Archivo(const std::string& path, bool & hayErrores) {
	hayErrores = !this->abrir(path);
}

Archivo::Archivo() {

}

Archivo::Archivo(const Archivo& a){
	//this->elArchivo=a.elArchivo;
}

Archivo&
Archivo:: operator=(const Archivo& a){
	return *this;
}

bool Archivo::abrir(const std::string& path){
	  //Intenta abrir el archivo en modo lectura - escritura.
	  elArchivo.open(path.c_str(), std::fstream::in | std::fstream::out);

	  if (!elArchivo.is_open())
	  {
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
Archivo::~Archivo()
{
	this->cerrar();
}

/**
 * Pre: El archivo XML debe estar abierto para lectura.
 * Post: Lee el siguiente caracter del archivo y lo devuelve en el parametro,
 * devuelve verdadero si la lectura fue exitosa, y falso sino.
 */
bool Archivo::leerCaracter(char &salida)
{
  char caracter;
  // lee del archivo parte de la linea, hasta haber leido:
  // 1 caracter o un fin de linea.
  elArchivo.read( (char*)&caracter , 1);
  if (caracter != '\n') // ignoro los avances de lineas.
     salida = caracter;
  else
     salida = ' ';

  if (elArchivo.fail() ) {
    //chequea si se ha producido un error, se devuelve false.
    elArchivo.clear();
    return false;
  }
  return true;
}

/**
 * Pre: El archivo XML debe estar abierto para lectura.
 * Post: Posiciona el cursor a continuacion de la proxima aparicion del caracter indicado,
 * devuelve el texto sobre el que avanzo.
 */
bool Archivo::leerHastaCaracter(char &caracterFin, std::string &textoEncontrado)
{
    char caracterLeido = ' ';
    textoEncontrado = "";
    bool continuaArchivo = this->leerCaracter(caracterLeido);
    //Leo hasta que encuentre el caracter de fin o hasta que falle el leer caracter (por fin de archivo).
    while ((caracterLeido != caracterFin)&&(continuaArchivo))
    {
        textoEncontrado += caracterLeido;
        continuaArchivo = this->leerCaracter(caracterLeido);
    }
    return (caracterLeido == caracterFin);
}

/**
 * Pre: El archivo XML debe estar abierto para lectura.
 * Post: Recorre el archivo hasta el siguiente simbolo <,
 * devuelve el texto sobre el que avanzo.
 * Nota: Llamo Etiqueta a lo que se encuentra entre los simbolos < y >.
 */
bool Archivo::leerHastaInicioEtiqueta(std::string &textoObtenido)
{
    char caracterInicio = '<';
    return this->leerHastaCaracter(caracterInicio, textoObtenido);
}

/**
 * Pre: El archivo XML debe estar abierto para lectura.
 * Post: Recorre el archivo hasta el siguiente simbolo >,
 * devuelve el texto sobre el que avanzo.
 * Nota: Llamo Etiqueta a lo que se encuentra entre los simbolos < y >.
 */
bool Archivo::leerHastaFinEtiqueta(std::string &textoObtenido)
{
    char caracterFin = '>';
    return this->leerHastaCaracter(caracterFin, textoObtenido);
}

 /**
  * Pre:-
  * Post:
  *  Devuelve FIN_TAG si el segundo caracter de la etiqueta es /.
  *  Devuelve COMENTARIOS si el segundo caracter de la etiqueta es ?.
  *  Devuelve NUEVO_TAG en otro caso.
*/
tipoTag Archivo::tipoDeTag(std::string &textoObtenido)
{
    char primerCaracter = textoObtenido[0];
    tipoTag tipoDeTagActual = NUEVO_TAG;
    if (primerCaracter=='/')
        tipoDeTagActual = FIN_TAG;
    else if ((primerCaracter=='?')||(primerCaracter=='!'))
             tipoDeTagActual = COMENTARIOS;
    return tipoDeTagActual;
}

/**
 * Pre:  El archivo XML debe estar abierto para lectura.
 * Post: Posiciona el cursor al comienzo del archivo.
 */
void Archivo::irAlPrincipio()
{
    elArchivo.tellg();
    elArchivo.clear();
    elArchivo.seekg(0,ios::beg);
    elArchivo.seekp(0,ios::beg);
    elArchivo.tellg();
}

/**
 * Pre: El archivo XML debe estar abierto para lectura.
 * Post: Posiciona el cursor al final del archivo.
 */
void Archivo::irAlFinal()
{
    elArchivo.tellg();
    elArchivo.clear();
    elArchivo.seekg(0, ios::end);
    elArchivo.seekp(0, ios::end);
    elArchivo.tellg();
}

/**
 * Pre: -
 * Post: Determina si el Tag tiene contenido.
 */
bool Archivo::esContenidoDeTag(std::string &palabra)
{
    palabra = trim(palabra);
    return (palabra!="");
}

void Archivo::cerrar(){
	if (elArchivo.is_open()){
		elArchivo.close();
	}
}

string Archivo::leerLinea(){
	string s;
	getline(elArchivo,s);
	return s;
}

void Archivo::escribirLinea(const string& palabra){
	long size=palabra.size();
	elArchivo<<palabra<<endl;
	elArchivo.write(palabra.c_str(),size);
}
