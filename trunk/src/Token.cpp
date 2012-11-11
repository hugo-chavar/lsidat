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
	string aux;
	size_t t = 0;
	vector<string> v;
	candidates.clear();

	removeSymbols(s, separators); //no son delimitadores: _&.-/ tratarlos como separadores
	split(candidates, s, delimiters);
	_count = candidates.size();
	iterador = candidates.begin();
	while (iterador != candidates.end()) {
		aux = trim_copy(*iterador, " \'{}[]-+.*/?<>=^#&!_");
		if ((!isdigit(aux[0])) || (aux[0] != '$')) { // hacer algo con los nros y los q empiezan en num luego
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
		stringToLower(aux);

		stemOfPlural(aux);
		*iterador = aux;
		iterador++;
	}
	iterador = candidates.begin();
	_currentPosition = 0;

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
