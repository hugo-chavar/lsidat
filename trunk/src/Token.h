/*
 * Token.h
 *
 *  Created on: Nov 10, 2012
 *      Author: Hugo Chavar
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
#include <list>
#include <vector>
#include "Texto.h"

#define MAX_TOKEN_LENGTH 60 //solo hay 3 palabras del idioma ingles con mas de 60 caracteres y no se usan
using namespace std;

const string delimiters = " \'{}[]+*?<>=^#!";
const string separators = "&-_/.,";

class Token {
private:
	list<string> candidates;
	list<string>::iterator iterador;
	size_t _currentPosition;
	size_t _count;
public:
	Token();
	Token(string);
	~Token();
	bool hasNextTerm();
	string nextTerm();
};

#endif /* TOKEN_H_ */
