/*
 * InfoPalabra.h
 *
 *  Created on: Sep 8, 2012
 *      Author: andy
 */

#ifndef INFOPALABRA_H_
#define INFOPALABRA_H_

#include <iostream>
#include <string>

using namespace std;

class InfoPalabra {

private:
	unsigned documento;
	unsigned cantidad;
public:
	InfoPalabra(unsigned doc,unsigned cant);
	InfoPalabra(const InfoPalabra& ip);
	~InfoPalabra();
	unsigned getCantidad();
	void incrementarCantidad(unsigned);
	unsigned getDocumento();
};

#endif /* INFOPALABRA_H_ */
