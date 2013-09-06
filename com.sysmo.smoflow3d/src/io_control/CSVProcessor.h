/*
 * CSVProcessor.h
 *
 *  Created on: Sep 6, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef CSVPROCESSOR_H_
#define CSVPROCESSOR_H_

#include "util/CommonDefinitions.h"

#ifdef __cplusplus

#include "Eigen/Core"

class CSVRowReader {
public:
	CSVRowReader();
	void setDelimiter(char delimiter);
	void setRowContent(String& rowContent);
	void reset();
	int getNextFloat(double& entry);
	int getNextInteger(int& entry);
	int getNextString(String& entry);
protected:
	int getNext(String& entry);
	char delimiter;
	String rowContent;
	size_t currentPosition;
};

class CSVProcessor {
	typedef enum {
		Type_Float,
		Type_Integer,
		Type_String
	} ColumnType ;
public:
	typedef std::vector<double> VectorFloat;
	typedef std::vector<int> VectorInt;
	typedef std::vector<String> VectorString;
public:
	CSVProcessor();
	void addFloatColumn(VectorFloat& storage);
	void addIntegerColumn(VectorInt& storage);
	void addStringColumn(VectorString& storage);
	void read(String& fileName, char delimiter, int numSkipLines);
	virtual ~CSVProcessor();
protected:
	String fileName;
	std::ifstream file;
	CSVRowReader rowReader;
	std::vector<ColumnType> columnTypes;
	std::vector<VectorFloat*> floatStorages;
	std::vector<VectorInt*> intStorages;
	std::vector<VectorString*> stringStorages;

};

#else // __cplusplus
DECLARE_C_STRUCT(CSVProcessor)
#endif //__cplusplus


#endif /* CSVPROCESSOR_H_ */
