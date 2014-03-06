/*
 * DataTable.cpp
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

#include "file_reader/containers/DataTable.h"

namespace smoflow {
namespace filereader {

/*
 * Print the input handling data table.
 */
std::ostream& operator<<(std::ostream& out, const DataTable& dataTable) {

	int rowNumber = dataTable.getRowNumber();
	int columnNumber = dataTable.getColumnNumber();

	for (int row = 0; row < rowNumber; ++row) {
		for (int column = 0; column < columnNumber; ++column) {
			out << dataTable.getValue(row, column) << "|";
		}
		out << std::endl;
	}

	return out;
}

/*
 * Constructors & Destructor
 */
DataTable::DataTable() {
}

DataTable::DataTable(const DataTable& dataTable) {
}

DataTable::~DataTable() {
	clear();
}

/**
 * Clear the data table.
 */
void DataTable::clear() {
	for (TIterDataColumns it = _dataColumns.begin(); it != _dataColumns.end(); ++it) {
		delete *it;
	}

	_dataColumns.clear();
}

/**
 * Initialize the data table.
 * @note it should be called the clear() function before calling this function.
 *
 * @param columNumber the number of columns
 */
void DataTable::initColumns(int columnNumber) {
	for (int i = 0; i < columnNumber; i++) {
		_dataColumns.push_back(new TDataColumn());
	}
}

/**
 * Add the next value when the data table is being initialized.
 * @param columnIndex the column index
 * @param value the next value
 */
void DataTable::addValue(int columnIndex, double value) {
	_dataColumns[columnIndex]->push_back(value);
}

/**
 * @return the number of rows
 */
int DataTable::getRowNumber() const {
	if (_dataColumns.size() != 0) {
		return (*_dataColumns[0]).size();
	}

	return 0;
}

/**
 * @return the number of columns
 */
int DataTable::getColumnNumber() const {
	return _dataColumns.size();
}

/**
 * Get a data column.
 * @param columnIndex the index of the returned column
 * @return the data column
 */
const TDataColumn* DataTable::getDataColumn(int columnIndex) const {
	return _dataColumns[columnIndex];
}

/**
 * Get a value.
 * @param rowIndex the row index of the returned value
 * @param columnIndex the column index of the returned value
 * @return the value
 */
double DataTable::getValue(int rowIndex, int columnIndex) const {
	return (*_dataColumns[columnIndex])[rowIndex];
}

} //namespace filereder
} //namespace smoflow
