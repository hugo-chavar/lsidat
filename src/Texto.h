/*
 * Texto.h
 *
 *  Created on: Sep 14, 2012
 *      Author: hugo
 */

#ifndef TEXTO_H_
#define TEXTO_H_

#include <cstddef>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

struct split {
	enum empties_t {
		empties_ok, no_empties
	};
};

template<typename Container>
Container& split(Container& result, const typename Container::value_type& s,
		const typename Container::value_type& delimiters,
		split::empties_t empties = split::empties_ok) {
	result.clear();
	size_t current;
	size_t next = -1;
	do {
		if (empties == split::no_empties) {
			next = s.find_first_not_of(delimiters, next + 1);
			if (next == Container::value_type::npos)
				break;
			next -= 1;
		}
		current = next + 1;
		next = s.find_first_of(delimiters, current);
		result.push_back(s.substr(current, next - current));
	} while (next != Container::value_type::npos);
	return result;
}

std::string& trim_right_inplace(std::string& s, const std::string& delimiters);

std::string& trim_left_inplace(std::string& s, const std::string& delimiters);

std::string& trim(std::string& s,
		const std::string& delimiters = " \f\n\r\t\v");

inline std::string trim_right_copy(const std::string& s,
		const std::string& delimiters);

inline std::string trim_left_copy(const std::string& s,
		const std::string& delimiters);

std::string trim_copy(const std::string& s, const std::string& delimiters =
		" \f\n\r\t\v");

std::string pad_left_copy(std::string& s, unsigned size,
		const char& fill);

std::string toString(int n);

std::string toString(unsigned n);

std::string toString(double number, int decimals );

#endif /* TEXTO_H_ */
