/*
 * Table.c
 *
 *  Created on: Oct 22, 2013
 *      Author: Milen Borisov
 */
#include "Table.h"
#include <stdio.h>
#include <string.h>


/**
 * Table - functions
 */
Table* Table_new(size_t rowNumber, size_t columnNumber) {
	NEW_OBJECT(Table, self);
	self->rowNumber = rowNumber;
	self->columnNumber = columnNumber;
	self->headers = ObjectArray_new(self->columnNumber);
	self->data = RealArray_new(self->rowNumber * self->columnNumber);
	return self;
}

void Table_free(Table** pSelf) {
	if (*pSelf == NULL) return;

	Table* self = *pSelf;
	ObjectArray_deleteElements(self->headers, (DestructorType)&String_free);
	ObjectArray_free(&(self->headers));
	RealArray_free(&(self->data));
	free(self);

	*pSelf = NULL;
}

String* Table_getHeader(Table* self, size_t columnIndex) {
	return (String*) self->headers->array[columnIndex];
}

double Table_getValue(Table* self, size_t rowIndex, size_t columnIndex) {
	return self->data->array[self->columnNumber*rowIndex + columnIndex];
}

void Table_setValue(Table* self, size_t rowIndex, size_t columnIndex, double value) {
	self->data->array[self->columnNumber*rowIndex + columnIndex] = value;
}

void Table_print(Table* self) {
	printf("Row: %d; Column: %d\n", self->rowNumber, self->columnNumber);

	for (size_t columnIndex = 0; columnIndex < self->columnNumber; columnIndex++) {
		printf("%s", Table_getHeader(self, columnIndex)->chars);
		if (columnIndex < self->columnNumber -1) {
			printf(",");
		}
	}
	printf("\n");

	for (size_t rowIndex = 0; rowIndex < self->rowNumber; rowIndex++) {
		for (size_t columnIndex = 0; columnIndex < self->columnNumber; columnIndex++) {
			printf("%f", Table_getValue(self, rowIndex, columnIndex));
			if (columnIndex < self->columnNumber -1) {
				printf(",");
			}
		}
		printf("\n");
	}
}


/**
 * CSVReader - functions
 */
#define CSV_MAX_ROW_SIZE 1024 //the max size of the *.csv row
#define CSV_COLUMN_DELIMITOR ","

void Table_readCSV(String* fileName, Table** pTable) {
	//Read the number of the columns and rows
	size_t rowCounter = 0;
	size_t columnCounter = 0;

	FILE* inFile = fopen(fileName->chars, "r");
	if(inFile == NULL) {
		raiseError(getDummyBase(), "Could not find the file '%s'", fileName->chars);
	}

	char row[CSV_MAX_ROW_SIZE];
	char columnDelimitor[] = CSV_COLUMN_DELIMITOR;
	while (fgets(row, sizeof(row), inFile)) {
		if (rowCounter == 0) { //header row
			char* tok = strtok(row, columnDelimitor);
			while (tok != NULL) {
				columnCounter++;
				tok = strtok(NULL, columnDelimitor);
			}
		}
		rowCounter++;
	}
	size_t rowNumber = rowCounter - 1; //'-1' remove the header row
	size_t columnNumber = columnCounter;


	// Allocate data memory
	Table* table = Table_new(rowNumber, columnNumber);


	//Read header
	rewind(inFile); //go to the beginning of the file
	if (fgets(row, sizeof(row), inFile)) {
		char* tok = strtok(row, columnDelimitor);
		int columnIndex = 0;
		while (tok != NULL) {
			String* columnName = String_new(tok);
			String_trim(columnName);
			table->headers->array[columnIndex] = columnName;

			columnIndex++;
			tok = strtok(NULL, columnDelimitor);
		}
	}


	// Read data
	int rowIndex = 0;
	while (fgets(row, sizeof(row), inFile)) {
		int columnIndex = 0;
		char* tok = strtok(row, columnDelimitor);
		while (tok != NULL) {
			double value = atof(tok);
			Table_setValue(table, rowIndex, columnIndex, value);

			tok = strtok(NULL, columnDelimitor);
			columnIndex++;
		}
		rowIndex++;
	}


	// Close the file
	fclose(inFile);


	// Return the table
	*pTable = table;
}
