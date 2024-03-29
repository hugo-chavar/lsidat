/*
 * Merger.h
 *
 *  Created on: 14/09/2012
 *      Author: Hugo Chavar
 */

#ifndef MERGER_H_
#define MERGER_H_

#define MAX_FILES_MERGE 1024
#define MIN_FILES_STAGE_MERGE 10

#include <iostream>
#include <bitset>
#include "DirList.h"
#include "Archivo.h"
#include "Palabra.h"

enum mergeMode{
	STAGE,
	FINAL,
	NONE
};

class Merger {
public:
	Merger();
	~Merger();
	void setInputDir(string);
	void setOutputFileName(string);
	void setNextFileName();
	void setOutputFolderName(string);
	string getOutputFolderName();
	string getMergedFilename();
	void setMode(mergeMode);
	void initializeStage();
	void merge();
	bool writeNextLine();
	unsigned countMinima();
	void fixMinima();
	void writeMinimum();
	void readMore();
	void joinWords(unsigned,unsigned);
	unsigned calculateFilesPerStage();
	bool endOfStage();
	bool endOfMerge();
	void closeAllFiles();
	void readFromFileNumber(unsigned);

private:
	bitset<MAX_FILES_MERGE> wordsReaded;
	bitset<MAX_FILES_MERGE> minWords;
	bitset<MAX_FILES_MERGE> openFiles;
	mergeMode mode;
	bool minCounted;
	unsigned minPosition;
	unsigned currentFileNumber;
	string inputDir;
	string outputFileName;
	string outputFolderName;
	Archivo outputFile;
	Archivo * stepFiles[MAX_FILES_MERGE];
	vector <Palabra> words;
	DirList directories;
	unsigned filesByStep;
};

#endif /* MERGER_H_ */
