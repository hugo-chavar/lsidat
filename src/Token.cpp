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
	bool is_number = false, is_float = false, is_garbage = false, is_text = true;
	size_t i = 0, j = 1, k = 0;
	if (isdigit(str[0])) {
		is_number = true;
		is_text = false;
	}
	while ((i < str.length()) && (!is_garbage)) {
		if (is_number) {
			if (str[i] == '.') {
				if (!is_float)
					is_float = true;
				else // Tiene mas de un '.'
					is_number = false;
			}
			if (is_float)
				k++;
			if ((!isdigit(str[i])) && (str[i] != '.'))
				is_number = false;
			if ((!is_number)
					&& ((!((str[i] >= 'A') && (str[i] <= 'Z')))
							&& (!((str[i] >= 'a') && (str[i] <= 'z')))))
				is_garbage = true;
		} else {
			if ((!((str[i] >= 'A') && (str[i] <= 'Z')))
					&& (!((str[i] >= 'a') && (str[i] <= 'z'))))
				is_garbage = true;
			j++;
		}
		i++;
	}
	if ((!is_text) && (!is_number) && (((i-j) > MAX_NUM_LENGTH) || (j >= MAX_ALPHANUM_WORD_LENGTH))) // No puede haber palabras alfanumericas con numeros de mas de MAX_NUM_LENGTH digitos.
		is_garbage = true;
	if ((is_text) && (i >= MAX_WORD_LENGTH)) // No puede haber palabras con mas de MAX_WORD_LENGTH caracteres.
		is_garbage = true;
	if (is_garbage)
		return GARBAGE;
	if (!is_text) {
		if (!is_number)
			return ALPHANUMERIC1;
		else {
			if (is_float) {
				if ((i-k) <= MAX_NUM_LENGTH)
					return FLOAT1;
				else
					return GARBAGE;
			}
			else {
				if (str.length() > MAX_NUM_LENGTH)
					return GARBAGE;
				return INTEGER1;
			}
		}
	}
	else
		return TEXT;
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

string Token::roundNumber(string str) {
	double num = atof(str.c_str());
	int numRounded;
	num = (round(num * 100)) / 100;
	numRounded = round(num);
	if (abs(num - numRounded) >= 0.01 )
		str = toString(num, 2);
	else
		str = toString(numRounded); //si es float y tiene .00 en decimales los saco
	return str;
}

string Token::caseNotDigit(string str) {
	vector<string> v;
	size_t t = 0;
	split(v, str, separators_text);
	if (v.size() > 1) {
		str = "";
		while (t < v.size()) {
			candidates.push_back(v[t]);
			if (v.size() <= 4)
				str += v[t];
			t++;
		}
	}
	str = trim_right_copy(str, numbers);
	if (whatIsIt(str) == GARBAGE)
		str = "";
	return str;
}

string Token::caseDigit(string str) {
	vector<string> v;
	split(v, str, separators_number);
	if (v.size() > 1) {
		if (v.size() == 2)
			if ((whatIsIt(v[0]) == INTEGER1)
					&& (whatIsIt(v[1]) == INTEGER1)
					&& (v[0].length() == 4))
				if (v[1].length() == 2)
					v[1] = completeYear(v);
		str = "";
		for (unsigned int i = 0; i < v.size(); i++) {
			if (v.size() == 2) //palabras compuestas
				str += v[i];
			candidates.push_back(v[i]);
		}
		str = removeCharacters(str, ".,"); // Elimino los separadores restantes.
		if (whatIsIt(str) != ALPHANUMERIC1)
			str = "";
	} else {
		str = removeCharacters(str, ","); // Elimino el separador de miles.
		string_type tipo = whatIsIt(str); //lo pongo para evaluar solo una vez
		if (tipo == FLOAT1)
			str = roundNumber(str);
		else {
			if (tipo == GARBAGE)
				str = "";
			else if (tipo == INTEGER1) {
				int entero = atoi(str.c_str());
				str = toString(entero);
			}
			str = removeCharacters(str, "."); // Caso de numero.palabra elimina el punto. Ej: "1.the"
		}
		//str = trim_left_copy(str,"0"); //elimimo ceros a la izquierda
	}
	return str;
}

void Token::constructTerms() {
	string aux;
	iterador = candidates.begin();
	while (iterador != candidates.end()) {
		aux = trim_copy(*iterador, " \'{}[]-+.,*/%$?<>=^#&!_`");
		aux = replaceMultiByteChars(aux, '_');
		if (!isdigit(aux[0])) //&& (aux[0] != '$')
			aux = caseNotDigit(aux);
		else
			if ((isdigit(aux[0])))
				aux = caseDigit(aux);
		aux = trim_copy(aux, " @\'{}[]-+.*/?<>=^$%#&!_");
		if (aux == "") {
			iterador = candidates.erase(iterador);
		} else {
			string_type tipo = whatIsIt(aux);
			if ((tipo == ALPHANUMERIC1)	|| (tipo == TEXT)) {
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
