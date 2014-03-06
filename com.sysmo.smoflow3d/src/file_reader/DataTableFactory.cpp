/*
 * DataTableFactory.cpp
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

#include "file_reader/DataTableFactory.h"

namespace smoflow {
namespace filereader {

#define MAX_NUMBER_TIME_DATA_TABELES 100
#define NULL_PTR_TO_TIME_DATA_TABELE (TimeDataTable*)0
std::vector<TimeDataTable*> DataTableFactory::_dataTables(
		MAX_NUMBER_TIME_DATA_TABELES, NULL_PTR_TO_TIME_DATA_TABELE);

TimeDataTable* DataTableFactory::getTimeDataTable_(int dataTableIndex) {
	TimeDataTable* dataTable = _dataTables[dataTableIndex];
	if (dataTable == NULL_PTR_TO_TIME_DATA_TABELE) {
		RaiseError("There is not a data table with index "
				<< dataTableIndex << ".");
	}

	return dataTable;
}

TimeDataTable* DataTableFactory::getTimeDataTable(int dataTableIndex) {
	TimeDataTable* dataTable = _dataTables[dataTableIndex];
	return dataTable;
}

void DataTableFactory::addTimeDataTable(int dataTableIndex, TimeDataTable* dataTable) {
	if (dataTableIndex < 0 || MAX_NUMBER_TIME_DATA_TABELES <= dataTableIndex) {
		RaiseError("The input data table index " << dataTableIndex
				<< " is incorrect. It should be between 0 and "
				<< (MAX_NUMBER_TIME_DATA_TABELES -1) <<	".");
	}

	if (_dataTables[dataTableIndex] != NULL_PTR_TO_TIME_DATA_TABELE) {
		RaiseError("It can not be created a new data table with index "
				<< dataTableIndex
				<< ", because a data table with this index already exists.");
	}

	_dataTables[dataTableIndex] = dataTable;
}

void DataTableFactory::clearTimeDataTables() {
	for (std::vector<TimeDataTable*>::iterator it = _dataTables.begin(); it != _dataTables.end(); ++it) {
		delete (*it);
	}

	_dataTables.clear();
}

void DataTableFactory::createTimeDataTable(
		int dataTableIndex,
		const std::string& dataFileName,
		const std::string& dataSeparator,
		int headerLineNumber,
		int firstDataLineNumber,
		int maxReadLines,
		int timeColumnIndex) {

	// Create a new time data table
	TimeDataTable* dataTable = new TimeDataTable(timeColumnIndex);
	dataTable->readDataFromFile(
			dataFileName,
			dataSeparator,
			headerLineNumber,
			firstDataLineNumber,
			maxReadLines);

	// Check some read data
	dataTable->isTimeDataOK();


	// Add the new time data table into data table stores
	addTimeDataTable(dataTableIndex, dataTable);
}

double DataTableFactory::getValue(
		int dataTableIndex,
		int columnIndex,
		double time) {
	TimeDataTable* dataTable = getTimeDataTable(dataTableIndex);
	return dataTable->getValue(columnIndex, time);
}

int DataTableFactory::getColumnIndex(
		int dataTableIndex,
		const std::string& columnName) {
	TimeDataTable* dataTable = getTimeDataTable_(dataTableIndex);
	return dataTable->getColumnIndex(columnName);
}

} //namespace filereader
} //namespace smoflow
