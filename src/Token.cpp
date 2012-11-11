/*
 * Token.cpp
 *
 *  Created on: Nov 10, 2012
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

void Token::constructTerms() {
	string aux;
	size_t t = 0;
	vector<string> v;

	iterador = candidates.begin();
	while (iterador != candidates.end()) {
		aux = trim_copy(*iterador, " \'{}[]-+.*/?<>=^#&!_");
		if ((!isdigit(aux[0])) && (aux[0] != '$')) { // hacer algo con los nros y los q empiezan en num luego
			split(v, aux, separators);
			if (v.size() > 1) {
				aux = "";
				while (t < v.size()) {
					candidates.push_back(v[t]);
					aux += v[t];
					t++;
				}
			}

		}
		aux = trim_copy(aux, " \'{}[]-+.*/?<>=^#&!_");
		if (aux == "") {
			iterador = candidates.erase(iterador);
		} else {
			stringToLower(aux);
			stemOfPlural(aux);
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
