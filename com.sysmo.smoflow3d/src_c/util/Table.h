/*
 * Table.h
 *
 *  Created on: Oct 22, 2013
 *      Author: Milen Borisov
 */
#ifndef TABLE_H_
#define TABLE_H_

#include "util/Common.h"
#include "util/Arrays.h"
#include "util/String.h"


/**
 * Table - declaration
 */
typedef struct {
	size_t rowNumber;
	size_t columnNumber;
	ObjectArray* headers;
	RealArray* data;
} Table;

Table* Table_new(size_t rowNumber, size_t columnNumber);
void Table_free(Table** pSelf);

String* Table_getHeader(Table* self, size_t columnIndex);
double Table_getValue(Table* self, size_t rowIndex, size_t columnIndex);
void Table_setValue(Table* self, size_t rowIndex, size_t columnIndex, double value);

void Table_print(Table* self);


/**
 * CSVReader - declaration
 */
void Table_readCSV(String* fileName, Table** pTable);


#endif /* TABLE_H_ */
