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

std::string pad_left_copy(std::string& s, unsigned size, const char& fill){
	std::string aux = "";
	for (unsigned i = 0;i< (size -s.size());i++){
		aux+=fill;
	}
	aux+=s;
	return aux;

}

std::string toString(int n){
	std::string aux;
	aux = static_cast<std::ostringstream*>( &(std::ostringstream() << n) )->str();
	return aux;
}

std::string toString(unsigned n){
	std::string aux;
	aux = static_cast<std::ostringstream*>( &(std::ostringstream() << n) )->str();
	return aux;
}


std::string toString(double number, int decimals ){
	std::ostringstream aux;
	std::string s;
	aux << std::setprecision(decimals)  <<std::fixed<< number;
	s = aux.str();
	//aux = static_cast<std::ostringstream*>( &(std::ostringstream() << n) )->str();
	return s;
}
