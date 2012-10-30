/* 
 *  Copyright (c) 2010 Daisuke Okanohara
 * 
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 * 
 *   1. Redistributions of source code must retain the above Copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above Copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   3. Neither the name of the authors nor the names of its contributors
 *      may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 */

#include <string>
#include <fstream>
#include <sstream>

#include "redsvd.hpp"
#include "redsvdFile.hpp"

using namespace std;


int main(int argc, char* argv[]){

	try{
  cout<<endl<<endl<<"Empieza mi Prueba"<<endl;
  REDSVD::fileProcess<REDSVD::SMatrixXf, REDSVD::RedSVD>("/home/andy/Desktop/zzzz/matrix/initialMatrix.txt","/home/andy/Desktop/zzzz/reduce",50);
  return 0;}
	catch (const string& error){
	  cerr << "Error: " << error << endl;
	  return -1;
	  }

	Eigen::MatrixXf U;
	Eigen::MatrixXf V;
	Eigen::MatrixXf S;
	Eigen::MatrixXf Sinv;
	string name="/home/andy/reduce.Un";
	string name2="/home/andy/reduce.Vn";
	string name3="/home/andy/reduce.Sn";
	REDSVD::readMatrix(name.c_str(),U);
	REDSVD::readMatrix(name3.c_str(),S);
	REDSVD::readMatrix(name2.c_str(),V);

	Eigen::MatrixXf A = U * S* V.transpose();
	Sinv= S.inverse();
	REDSVD::writeMatrix_("/home/andy/reduce.V",V);

	  REDSVD::writeMatrix_("/home/andy/reduce.A",A);
	  cout<<"filas:"<<A.rows()<<" columnas:"<<A.cols()<<endl;

	  cout<<"termino"<<endl;
}
