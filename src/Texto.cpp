/*
 * Texto.cpp
 *
 *  Created on: 14/09/2012
 *      Author: Hugo Chavar
 */
#include <iomanip>
#include "Texto.h"

std::string& trim_right_inplace(std::string& s, const std::string& delimiters =
		" \f\n\r\t\v") {
	return s.erase(s.find_last_not_of(delimiters) + 1);
}

std::string& trim_left_inplace(std::string& s, const std::string& delimiters =
		" \f\n\r\t\v") {
	return s.erase(0, s.find_first_not_of(delimiters));
}

std::string& trim(std::string& s, const std::string& delimiters) {
	return trim_left_inplace(trim_right_inplace(s, delimiters), delimiters);
}

std::string trim_right_copy(const std::string& s,
		const std::string& delimiters) {
	if (s.length() > 0) {
		return s.substr(0, s.find_last_not_of(delimiters) + 1);
	}
	return s;
}

std::string trim_left_copy(const std::string& s,
		const std::string& delimiters) {
	size_t pos = s.find_first_not_of(delimiters);
	if ((pos != std::string::npos)&&(s.length() > 0)) {
		return s.substr(pos);
	}
	return s;
}

std::string trim_copy(const std::string& s, const std::string& delimiters) {
	return trim_left_copy(trim_right_copy(s, delimiters), delimiters);
}

std::string pad_left_copy(std::string& s, unsigned size, const char& fill) {
	std::string aux = "";
	for (unsigned i = 0; i < (size - s.size()); i++) {
		aux += fill;
	}
	aux += s;
	return aux;

}

std::string toString(int n) {
	std::string aux;
	aux = static_cast<std::ostringstream*>(&(std::ostringstream() << n))->str();
	return aux;
}

std::string toString(unsigned n) {
	std::string aux;
	aux = static_cast<std::ostringstream*>(&(std::ostringstream() << n))->str();
	return aux;
}

std::string toString(double number, int decimals) {
	std::ostringstream aux;
	std::string s;
	aux << std::setprecision(decimals) << std::fixed << number;
	s = aux.str();
	return s;
}

char toLower(char in) {
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}

void stringToLower(std::string& s) {
	std::transform(s.begin(), s.end(), s.begin(), toLower);
}

void stemOfPlural(std::string& s) {
	if ((s[s.length() - 1] == 's') && (s.length() > 3)) {
		if ((s[s.length() - 2] == 'i') || (s[s.length() - 2] == 's')
				|| (s[s.length() - 2] == 'u')) {
			return;
		}
		if (s[s.length() - 2] == '\'') {
			s = s.substr(0, s.length() - 2);
			return;
		}
		std::string last = s.substr(s.length() - 4, s.length()).substr(0, 2);
		if (s[s.length() - 2] == 'e') {
			if ((last[1] == 'h') || (last[1] == 'x')
					|| (last.compare("ss") == 0)) {
				s = s.substr(0, s.length() - 2);
				return;
			}
			if (last[1] == 'i') {
				if (s.length() > 4) {
					s = s.substr(0, s.length() - 3);
					s += 'y';
					return;
				}
				if (s.length() == 4) {
					s = s.substr(0, s.length() - 1);
					return;
				}

			}
		}
		if (s[s.length() - 2] == 'a') {
			if (last[1] != 'i')
				return;
			s = s.substr(0, s.length() - 1);
			return;
		}
		s = s.substr(0, s.length() - 1);
	}
}

void removeSymbols(std::string& s, const std::string& symbols) {
	std::string aux;

	size_t m, u, d = s.find_last_of(symbols);
	m = std::string::npos;
	while (d != std::string::npos) {
		aux = s.substr(0, d);
		u = aux.find_last_of(symbols);
		if (u == (d - 1)) {
			s[d] = ' ';
			m = d;
		} else {
			if (d == (m - 1))
				s[d] = '*';
		}
		d = u;
	}
}

std::string replaceMultiByteChars(std::string& cad, char replacement) {
	/*	If you know that the data is UTF-8, then you just have to check the high bit:

	 0xxxxxxx = single-byte ASCII character
	 1xxxxxxx = part of multi-byte character
	 Or, if you need to distinguish lead/trail bytes:

	 10xxxxxx = 2nd, 3rd, or 4th byte of multi-byte character
	 110xxxxx = 1st byte of 2-byte character
	 1110xxxx = 1st byte of 3-byte character
	 11110xxx = 1st byte of 4-byte character
	 source: http://en.wikipedia.org/wiki/UTF-8 */
	//std::string special;
	std::string aux, special,d;
	unsigned plus,cont,j = 0;
	aux = "";

	while (j < cad.length()) {
		char c = cad[j];
		plus = 0;
		cont = 0;
		if ((0x80 & c) != 0) { //es caracter multibyte, se lo trata
			if (((0x10 & c) == 0) && ((0xE0 & c) == 0xE0)) { //caracter de 3 bytes
				//caracter bastante raro.. Lo reemplazo con un single character
				plus = 2;
				cont++;

				c = replacement;
			} else if (((0x20 & c) == 0) && ((0xC0 & c) == 0xC0)) { //caracter de 2 bytes
				//en esta seccion caen los caracteres con tildes y letras griegas en gral
				// se reemplazan por caracteres simples sin tildes
				d = cad.substr(j, 2);
				unsigned k = 0;
				while ((twoByteChars.substr(k, 2).compare(d) != 0)
						&& (k < twoByteChars.length())) {
					k += 2;
				}
				plus = 1;
				cont++;
				if ((twoByteChars.substr(k, 2)).compare(d) == 0) {
					c = replacementChars[k / 2];
				} else {
					//caracter un poco raro.. Lo reemplazo con un single character
					c = replacement;
				}
				//11110xxx = 1st byte of 4-byte character
			} else if (((0x08 & c) == 0) && ((0xF0 & c) == 0xF0)) { //caracter de 4 bytes
				//caracter muy raro.. Lo reemplazo con un single character
				plus = 3;
				cont++;
				c = replacement;
			} else {
				//en este punto se detecta q no es un caracter lo q se leyo
				//puede estar corrupto el texto
				//se avanza hasta el siguiente caracter simple
				plus = 4;
				cont++;
				while ((0x80 & cad[j + plus]) != 0) {
					plus++;
				}
			}
		}
		if (cont > 3)//si tiene mas de 3 caracteres multibyte es basura
			return "";
		j += (plus + 1);
		if (int(c) < 32)
			c  = replacement;
		aux += c;
	}
	return aux;

}
