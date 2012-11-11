/*
 * Texto.cpp
 *
 *  Created on: Sep 14, 2012
 *      Author: hugo
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

inline std::string trim_right_copy(const std::string& s,
		const std::string& delimiters) {
	if (s.length() > 0) {
		return s.substr(0, s.find_last_not_of(delimiters) + 1);
	}
	return s;
}

inline std::string trim_left_copy(const std::string& s,
		const std::string& delimiters) {
	if (s.length() > 0) {
		return s.substr(s.find_first_not_of(delimiters));
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
	//aux = static_cast<std::ostringstream*>( &(std::ostringstream() << n) )->str();
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
