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
	removeSymbols(s, separators_text); //elimina secuencias de simbolos, no los individuales
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

string_type Token::whatIsIt(string str) {
	bool is_number = false;
	bool is_float = false;
	bool is_text = true;
	bool is_garbage = false;
	unsigned int i = 0;
	int j = 0, k = 0, l = 0;
	if (isdigit(str[0]))
		is_number = true;
	while ((i < str.length()) && (!is_garbage)) {
		if (is_number) {
			if (str[i] == '.') {
				if (!is_float)
					is_float = true;
				else
					//tiene mas de un '.'
					is_number = false;
			}
			if ((!isdigit(str[i])) && (str[i] != '.'))
				is_number = false;
			if ((!is_number)
					&& ((!((str[i] >= 'A') && (str[i] <= 'Z')))
							&& (!((str[i] >= 'a') && (str[i] <= 'z')))))
				is_garbage = true;
			j++;
		} else {
			if ((!((str[i] >= 'A') && (str[i] <= 'Z')))
					&& (!((str[i] >= 'a') && (str[i] <= 'z')))) {
				is_text = false;
				if (isdigit(str[i]))
					k++;
			} else {
				if (!is_text)
					is_garbage = true;
				l++;
			}
		}
		i++;
	}
	if (is_garbage)
		return GARBAGE;
	if ((j == 1) && (!is_number))
		return NOT_A_NUMBER1;
	if ((j > 1) && (!is_number))
		return ALPHANUMERIC1;
	if ((is_number) && (is_float))
		return FLOAT1;
	if ((is_number) && (!is_float)) {
		if (str.length() > 7)
			return GARBAGE;
		return INTEGER1;
	}
	if (is_text)
		return TEXT;
	if ((l + k) == i)
		return ALPHANUMERIC1;
	return GARBAGE;
}

string Token::removeCharacters(string str, string characters) {
	vector<string> v;
	split(v, str, characters);
	if (v.size() > 1) {
		str = "";
		for (unsigned int i = 0; i < v.size(); i++)
			str += v[i];
	}
	return str;
}

string Token::completeYear(vector<string> v) {
	int j = 0, k = 0;
	string str = "0000";
	for (int i = 0; i < 4; i++) {
		str[i] = v[j][k];
		if (j == k)
			k++;
		else {
			if (j < k) {
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
		aux = trim_copy(*iterador, " \'{}[]-+.*/%$?<>=^#&!_`");
		aux = replaceMultiByteChars(aux, '_');
		if (!isdigit(aux[0])) { //&& (aux[0] != '$'))
			split(v, aux, separators_text);
			if (v.size() > 1) {
				aux = "";
				while (t < v.size()) {
					candidates.push_back(v[t]);
					if (v.size() == 2) //palabras compuestas
						aux += v[t];
					t++;
				}
			}
			if (whatIsIt(aux) == GARBAGE)
				aux = "";
		} else {
			if ((isdigit(aux[0]))) {
				split(v, aux, separators_number);
				if (v.size() > 1) {
					if (v.size() == 2)
						/*
						 * Modificación al diseño
						 * Se detectan rangos de años y se completa el valor que esta abreviado.
						 */
						if ((whatIsIt(v[0]) == INTEGER1)
								&& (whatIsIt(v[1]) == INTEGER1)
								&& (v[0].length() == 4))
							if (v[1].length() == 2)
								v[1] = completeYear(v);
					aux = "";

					for (unsigned int i = 0; i < v.size(); i++) {
						if (v.size() == 2) //palabras compuestas
							aux += v[i];
						candidates.push_back(v[i]);
					}
					aux = removeCharacters(aux, ".,"); // Elimino los separadores restantes.
					if (whatIsIt(aux) != ALPHANUMERIC1)
						aux = "";
				} else {
					aux = removeCharacters(aux, ","); // Elimino el separador de miles.
					string_type tipo = whatIsIt(aux); //lo pongo para evaluar solo una vez
					if (tipo == FLOAT1) {
						double num = atof(aux.c_str());
						int numRounded;
						num = (round(num * 100)) / 100;
						numRounded = round(num);
						if ((num - numRounded) >= 0.01 )
							aux = toString(num, 2);
						else
							aux = toString(numRounded); //si es float y tiene .00 en decimales los saco
					} else {
						if (tipo == GARBAGE)
							aux = "";
						else if (tipo == INTEGER1){
							int entero = atoi(aux.c_str());
							aux = toString(entero);
						}
							//aux = trim_left_copy(aux,"0");//elimimo ceros a la izquierda

						//TODO no entiendo para q esta la siguiente linea
						//yami pone un comentario please
						aux = removeCharacters(aux, ".");
					}
				}
			}
		}
		aux = trim_copy(aux, " @\'{}[]-+.*/?<>=^$%#&!_");
		if (aux == "") {
			iterador = candidates.erase(iterador);
		} else {
			string_type tipo = whatIsIt(aux);
			if ((tipo == NOT_A_NUMBER1) || (tipo == ALPHANUMERIC1)
					|| (tipo == TEXT)) {
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
