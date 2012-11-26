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

#define MAX_WORD_LENGTH 60 //solo hay 3 palabras del idioma ingles con mas de 60 caracteres y no se usan
#define MAX_NUM_LENGTH 7
#define MAX_TOKEN_LENGTH 67
using namespace std;

//const string delimiters = " \'{}[]+*?<>=^#!";
//const string separators = "&-_/.,~|";
const string delimiters = " \'{}[]+*?<>=^#!";
const string separators_number = "&-_/~|";
const string separators_text = separators_number+".,";
const string numbers = "0123456789";
enum string_type {FLOAT1, INTEGER1, ALPHANUMERIC1, TEXT, GARBAGE};

class Token {
private:
	list<string> candidates;
	list<string>::iterator iterador;
	size_t _currentPosition;
	size_t _count;
	string_type whatIsIt(string str);
	string removeCharacters(string str, string characters);
	string completeYear(vector<string> v);
	string caseNotDigit(string str);
	string caseDigit(string str);
	string roundNumber(string str);
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
