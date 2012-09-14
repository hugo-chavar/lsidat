/*
 * Texto.cpp
 *
 *  Created on: Sep 14, 2012
 *      Author: hugo
 */
#include "Texto.h"


std::string& trim_right_inplace(std::string& s, const std::string& delimiters =
		" \f\n\r\t\v") {
	return s.erase(s.find_last_not_of(delimiters) + 1);
}

std::string& trim_left_inplace(std::string& s, const std::string& delimiters =
		" \f\n\r\t\v") {
	return s.erase(0, s.find_first_not_of(delimiters));
}

std::string& trim(std::string& s,
		const std::string& delimiters) {
	return trim_left_inplace(trim_right_inplace(s, delimiters), delimiters);
}




