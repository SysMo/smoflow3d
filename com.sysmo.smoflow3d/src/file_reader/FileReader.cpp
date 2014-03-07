/*
 * FileReader.cpp
 *
 * Created on: Mar 3, 2011
 *  Revisions:
 *     Author: Milen Borisov
 *
 *  Copyright: SysMo Ltd., 
 *             Klokotnitza 9A str., ap. 9
 *             Gabrovo 5300, Bulgaria
 *
 *    License: See License.txt in top level directory.
 *             If no licence file was distributed, contact SysMo Ltd.
 */

#include "file_reader/FileReader.h"

typedef std::map<int, FileReader*> FileReaderContainer;
static FileReaderContainer FileReaderRegistry;

/**
 * FileReader - C methods
 */

void FileReader_register(int fileReaderIndex, int timeColumnIndex) {
	// Check
	FileReaderContainer::iterator it = FileReaderRegistry.find(fileReaderIndex);
	if (it != FileReaderRegistry.end()) {
		RaiseError("File reader index " << fileReaderIndex << " already used.");
	}

	// Create a new file reader
	FileReader* fileReader = new FileReader(timeColumnIndex - 1);

	// Register the new file reader
	FileReaderRegistry[fileReaderIndex] = fileReader;
	std::cout << "Registered file reader with index = " << fileReaderIndex << ".\n";
}

FileReader* FileReader_get(int fileReaderIndex) {
	FileReaderContainer::iterator it = FileReaderRegistry.find(fileReaderIndex);
	if (it == FileReaderRegistry.end()) {
		RaiseError("No file reader defined with index " << fileReaderIndex << ".");
	}

	return (*it).second;
}

int FileReader_index(FileReader* fileReader) {
	for (FileReaderContainer::iterator it = FileReaderRegistry.begin();
			it != FileReaderRegistry.end(); it++) {
		if ((*it).second == fileReader) {
			return (*it).first;
		}
	}

	return -1;
}

void FileReader_readDataFromFile(
		FileReader* fileReader,
		const char* dataFileName,
		const char* dataSeparator,
		int headerLineNumber,
		int firstDataLineNumber,
		int maxReadLines) {
	// Read
	fileReader->readDataFromFile(
			dataFileName,
			dataSeparator,
			headerLineNumber - 1,
			firstDataLineNumber - 1,
			maxReadLines);

	// Check some read data
	fileReader->isTimeDataOK();

}

int FileReader_getColumnIndex(
		FileReader* fileReader,
		const char* columnName) {
	return fileReader->getColumnIndex(columnName) + 1;
}

double FileReader_getValue(
		FileReader* fileReader,
		int columnIndex,
		double time) {
	return fileReader->getValue(columnIndex - 1, time);
}
