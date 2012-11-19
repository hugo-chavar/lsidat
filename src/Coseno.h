/*
 * Coseno.h
 *
 *  Created on: 11/11/2012
 *      Author: Andres Sanabria
 */

#ifndef COSENO_H_
#define COSENO_H_

class Coseno {
public:
	Coseno(int doc,float val);
	Coseno(const Coseno& cos);
	~Coseno();
	float getCoseno();
	int getDocumento();
	bool operator<(const Coseno& cos);
private:
	int documento;
	float valor;
};

#endif /* COSENO_H_ */
