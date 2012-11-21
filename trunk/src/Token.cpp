/*
 * Token.cpp
 *
 *  Created on: 10/11/2012
 *      Author: Hugo Chavar
 */

#include "Token.h"

Token::Token() {
}

Token::Token(string s) {
	candidates.clear();
	removeSymbols(s, separators); //no son delimitadores: _&.-/ tratarlos como separadores
	split(candidates, s, delimiters);
	this->constructTerms();
}

Token::Token(list<string>& tokens) {
	candidates = tokens;
	this->constructTerms();
}

Token::~Token() {
}

bool Token::hasNextTerm() {
	return (_currentPosition < _count);
}

string Token::nextTerm() {
	string sigte = (*iterador);
	iterador++;
	_currentPosition++;
	return sigte;
}

void Token::print() {
	iterador = candidates.begin();
	_currentPosition = 0;
	while (hasNextTerm()) {

		cout << nextTerm() << " ";
	}
	cout << endl;
	iterador = candidates.begin();
	_currentPosition = 0;
}

number_type Token::isNumber(string str) {
	bool is_number = true;
	bool is_float = false;
	unsigned int i = 0;
	while ((is_number) && (i<str.length())) {
		if (str[i] == '.'){
			if (!is_float)
				is_float = true;
			else //tiene mas de un '.'
				is_number = false;
		}

		if ((!isdigit(str[i])) && (str[i] != '.'))
			is_number = false;
		i++;
	}
	if ((i == 1) && (!is_number))
		return NOT_A_NUMBER;
	if ((i > 1) && (!is_number))
		return ALPHANUMERIC;
	if ((is_number) && (is_float))
		return FLOAT;
	return INTEGER;
}

string Token::removeCharacters(string str, string characters) {
	vector<string> v;
	split (v, str, characters);
	if (v.size() > 1) {
		str = "";
		for (unsigned int i=0; i < v.size(); i++)
			str += v[i];
	}
	return str;
}

string Token::completeYear(vector<string> v) {
	int j=0, k=0;
	string str = "0000";
	for (int i=0; i<4; i++) {
		str[i] = v[j][k];
		if (j == k)
			k++;
		else {
			if (j<k) {
				j++;
				k--;
			} else
				k++;
		}
	}
	return str;
}

void Token::constructTerms() {
	string aux;
	size_t t = 0;
	vector<string> v;

	iterador = candidates.begin();
	while (iterador != candidates.end()) {
		aux = trim_copy(*iterador, " \'{}[]-+.*/%$?<>=^#&!_");
		if (!isdigit(aux[0]))  {   //&& (aux[0] != '$'))
			split(v, aux, separators);
			if (v.size() > 1) {
				aux = "";
				while (t < v.size()) {
					candidates.push_back(v[t]);
					aux += v[t];
					t++;
				}
			}
		} else {
			if ((isdigit(aux[0]))) {
				split (v, aux, "&-_/");
				if (v.size() > 1) {
					if (v.size() == 2)
						/*
						 * Modificación al diseño
						 * Se detectan rangos de años y se completa el valor que esta abreviado.
						 */
						if ((isNumber(v[0]) == INTEGER) && (isNumber(v[1]) == INTEGER) && (v[0].length() == 4))
							if (v[1].length() == 2)
								v[1] = completeYear(v);
					aux = "";
					for (unsigned int i=0; i < v.size(); i++) {
						aux += v[i];
						candidates.push_back(v[i]);
					}
					aux = removeCharacters(aux, ".,"); // Elimino los separadores restantes.
					if (isNumber(aux) != ALPHANUMERIC)
						aux = "";
				} else {
					aux = removeCharacters(aux, ","); // Elimino el separador de miles.
					if (isNumber(aux) == FLOAT) { // Redondeo el numero siempre para abajo.
						double num = atof(aux.c_str());
						num = (round(num*100))/100;
						//no me convencia el floor, buscando el nro 'e' no daba el resultado esperado
						aux = toString(num, 2);
					}
					else
						aux = removeCharacters(aux, ".");
				}
			}
		}
		aux = trim_copy(aux, " @\'{}[]-+.*/?<>=^$%#&!_");
		if (aux == "") {
			iterador = candidates.erase(iterador);
		} else {
			if ((isNumber(aux) == NOT_A_NUMBER) || (isNumber(aux) == ALPHANUMERIC)) {
				stringToLower(aux);
				stemOfPlural(aux);
			}
			*iterador = aux;
			iterador++;
		}
	}
	iterador = candidates.begin();
	_currentPosition = 0;
	_count = candidates.size();
}

void Token::sort() {
	candidates.sort();
	iterador = candidates.begin();
}
