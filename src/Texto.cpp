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

inline std::string trim_right_copy(
  const std::string& s,
  const std::string& delimiters )
{
  return s.substr( 0, s.find_last_not_of( delimiters ) + 1 );
}

inline std::string trim_left_copy(
  const std::string& s,
  const std::string& delimiters )
{
  return s.substr( s.find_first_not_of( delimiters ) );
}

std::string trim_copy(
  const std::string& s,
  const std::string& delimiters )
{
  return trim_left_copy( trim_right_copy( s, delimiters ), delimiters );
}




