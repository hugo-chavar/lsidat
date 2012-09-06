/*
 * DirList.h
 *
 *  Created on: Sep 5, 2012
 *      Author: hugo
 */

#ifndef DIRLIST_H_
#define DIRLIST_H_


#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>

using namespace std;

class DirList {
public:
	DirList();
	~DirList();
	bool create(string);

};

#endif /* DIRLIST_H_ */
