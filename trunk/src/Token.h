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
#include <math.h>

#define MAX_TOKEN_LENGTH 60 //solo hay 3 palabras del idioma ingles con mas de 60 caracteres y no se usan
using namespace std;

const string delimiters = " \'{}[]+*?<>=^#!";
const string separators = "&-_/.,~|";
enum number_type {FLOAT, INTEGER, ALPHANUMERIC, NOT_A_NUMBER};

class Token {
private:
	list<string> candidates;
	list<string>::iterator iterador;
	size_t _currentPosition;
	size_t _count;
	number_type isNumber(string str);
	string removeCharacters(string str, string characters);
	string completeYear(vector<string> v);
public:
	Token();
	Token(string);
	Token(list<string>&);
	~Token();
	void constructTerms();
	void sort();
	bool hasNextTerm();
	string nextTerm();
	void print();
};

#endif /* TOKEN_H_ */
