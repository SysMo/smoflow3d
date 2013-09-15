/*
 * CSVReader.cpp
 *
 *  Created on: Sep 6, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "CSVProcessor.h"

/**
 * CSVRowReader - C++
 */
CSVRowReader::CSVRowReader() {
	delimiter = ',';
	currentPosition = 0;
}

void CSVRowReader::setDelimiter(char delimiter) {
	this->delimiter = delimiter;
}

void CSVRowReader::setRowContent(String& rowContent) {
	this->rowContent = rowContent;
	currentPosition = 0;
}
void CSVRowReader::reset() {
	currentPosition = 0;
}
int CSVRowReader::getNext(String& entry) {
	// TODO Check what happens at the end of the line
	if (currentPosition >= rowContent.size()) {
		return -1;
	}
	size_t i = currentPosition;
	for (; i < rowContent.size(); i++) {
		if (rowContent[i] == delimiter) {
			break;
		}
	}
	entry = this->rowContent.substr(currentPosition, i - currentPosition);
	currentPosition = i + 1;
	return 0;
}

int CSVRowReader::getNextFloat(double& entry) {
	String strEntry;
	int status = getNext(strEntry);
	entry = std::atof(strEntry.c_str());
	return status;
}

int CSVRowReader::getNextInteger(int& entry) {
	String strEntry;
	int status = getNext(strEntry);
	entry = std::atoi(strEntry.c_str());
	return status;
}

int CSVRowReader::getNextString(String& entry) {
	String strEntry;
	int status = getNext(strEntry);
	if (strEntry[0] != '"' || strEntry[strEntry.size() - 1] != '"') {
		RaiseError("Content of 'String' column in CSV file must be in quotes");
	} else {
		entry = strEntry.substr(1, strEntry.size() - 2);
	}
	return status;
}

bool CSVRowReader::isRowEmpty(String& rowContent) {
	bool isEmpty = true;
	for (size_t i = 0; i < rowContent.size(); i++) {
		char c = rowContent[i];
		if (!(c == ' ' || c == '\t' || c == '\n' || c == '\r')) {
			isEmpty = false;
			break;
		}
	}
	return isEmpty;
}

/**
 * CSVProcessor - C++
 */
CSVProcessor::CSVProcessor() {
}

CSVProcessor::~CSVProcessor() {
	if (file.is_open()) {
		file.close();
	}
}

void CSVProcessor::addFloatColumn(VectorFloat& storage) {
	columnTypes.push_back(Type_Float);
	floatStorages.push_back(&storage);
}

void CSVProcessor::addIntegerColumn(VectorInt& storage) {
	columnTypes.push_back(Type_Integer);
	intStorages.push_back(&storage);
}

void CSVProcessor::addStringColumn(VectorString& storage) {
	columnTypes.push_back(Type_String);
	stringStorages.push_back(&storage);
}

void CSVProcessor::read(String& fileName, char delimiter, int numSkipLines) {
	rowReader.setDelimiter(delimiter);
	file.open(fileName.c_str());
	if (!file.is_open()) {
		RaiseError("Failed to open file: " << fileName)
	}

	// Clear all the storage vectors
    for (size_t i = 0; i < floatStorages.size(); i++) {
    	floatStorages[i]->clear();
    }
    for (size_t i = 0; i < intStorages.size(); i++) {
    	intStorages[i]->clear();
    }
    for (size_t i = 0; i < stringStorages.size(); i++) {
    	stringStorages[i]->clear();
    }


    int currentRowNumber = 0;
	for( String rowContent; std::getline( file, rowContent ); )
	{
		currentRowNumber++;
		// Skip the initial lines
	    if (numSkipLines > 0) {
	    	numSkipLines--;
	    	continue;
	    }
	    if (rowContent.length() == 0 ||
	    		CSVRowReader::isRowEmpty(rowContent)) {
	    	continue;
	    }
	    rowReader.setRowContent(rowContent);
	    int floatIndex = 0;
	    int intIndex = 0;
	    int stringIndex = 0;
	    int status;

	    for (size_t i = 0; i < columnTypes.size(); i++) {
	    	switch (columnTypes[i]) {
	    	case Type_Float:
	    		double floatValue;
	    		status = rowReader.getNextFloat(floatValue);
	    		if (status == 0) {
	    			floatStorages[floatIndex]->push_back(floatValue);
	    			floatIndex++;
	    		} else {
	    			RaiseError("Couldn't read float value from CSV file, row #"
	    					<< currentRowNumber << ", column #" << i + 1 )
	    		}
	    		break;
	    	case Type_Integer:
	    		int intValue;
	    		status = rowReader.getNextInteger(intValue);
	    		if (status == 0) {
	    			intStorages[intIndex]->push_back(intValue);
	    			intIndex++;
	    		} else {
	    			RaiseError("Couldn't read integer value from CSV file, row #"
	    					<< currentRowNumber << ", column #" << i + 1 )
	    		}
	    		break;
	    	case Type_String:
	    		String stringValue;
	    		status = rowReader.getNextString(stringValue);
	    		if (status == 0) {
	    			stringStorages[stringIndex]->push_back(stringValue);
	    			stringIndex++;
	    		} else {
	    			RaiseError("Couldn't read string value from CSV file, row #"
	    					<< currentRowNumber << ", column #" << i + 1 )
	    		}
	    		break;
	    	}
	    }
	}

	file.close();
}
