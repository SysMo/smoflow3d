/*
 * HeadingDataTable.cpp
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

#include <fstream>
#include <string>
#include <vector>

#include "file_reader/containers/HeadingDataTable.h"
#include "util/String.h"

namespace smoflow {
namespace filereader {

/*
 * Print the input data table.
 */
std::ostream& operator<<(std::ostream& out, const HeadingDataTable& dataTable) {

	// Print the headers
	const THeaders& headers = dataTable.getHeaders();
	for (unsigned i = 0; i < headers.size(); ++i) {
		out << headers[i] << "|";
	}
	out << std::endl << std::endl;

	// Printe the data
	out << (const DataTable&) dataTable;

	return out;
}

/**
 * Clear the heading data table.
 */
void HeadingDataTable::clear() {
	DataTable::clear();
	_headers.clear();
}

/**
 * Initialize the data table headers and columns.
 * @param headers
 */
void HeadingDataTable::initHeadersAndColumns(THeaders headers) {
	_headers = headers;
	initColumns(headers.size());
}

/**
 * @return the headers
 */
const THeaders& HeadingDataTable::getHeaders() const {
	return _headers;
}

/**
 * Get the column index by the input column name.
 *
 * @param the column name
 * @param the index of the found column.
 * @return the index of the found column.
 * @note if the column is not found then throw an exception.
 */
int HeadingDataTable::getColumnIndex(const std::string& columnName) {
	for (unsigned i = 0; i < _headers.size(); ++i) {
		if (_headers[i] == columnName) {
			return i;
		}
	}

	RaiseComponentError(this, "Could not find a column with name '" << columnName << "'.");
	return -1;
}

/**
 * Initialize heading data table from a file.
 *
 * @param dataFileName the full or the relative name of the data file.
 * @param dataSeparator the set from data separator.
 * @note it's not using for now (e.g. the ',' is always used).
 *
 * @param headerLineNumber the number of the line with headers
 * @note the first line is with number '0'.
 *
 * @param firstDataLineNumber the number of the line with first data
 * @note the first line is with number '0'.
 *
 * @param maxReadLines the maximum number of lines to be read (by default = -1 (all lines))
 */
void HeadingDataTable::readDataFromFile(
			const std::string& dataFileName,
			const std::string& dataSeparator,
			int headerLineNumber,
			int firstDataLineNumber,
			int maxReadLines) {

	// Define some types
	typedef std::vector<std::string> TParsedValues;


	// Clear the old data
	clear();


	// Try to open the file
	std::ifstream in(dataFileName.c_str());
	if (!in.is_open()) {
		RaiseComponentError(this, "Could not open the file '" << dataFileName << "'.");
	}


	// Try to read data and headers
	TParsedValues parsedValues;
	std::string line;
	std::string cell;

	int headersNumber = 0;
	int currLineNumber = 0;
	int readLines = 0;
	while (getline(in, line))
	{
		// Parse the current line and trim the parsed values
		std::stringstream lineStream(line);
		parsedValues.clear();

		while( getline(lineStream, cell, dataSeparator[0]) ) {
			String::trim(cell);
			parsedValues.push_back(cell);
		}


		// Try to read the header line
		if (currLineNumber == headerLineNumber) {
			initHeadersAndColumns(parsedValues);
			headersNumber = parsedValues.size();

			currLineNumber++;
			continue;
		}


		// Check the current line for containing data
		if (currLineNumber < firstDataLineNumber) {
			currLineNumber++;
			continue;
		}


		// Check the current line for correct number of data
		if (headersNumber != (int)parsedValues.size()) {
			RaiseComponentError(this, "The header line has " << (headersNumber + 1) << " columns, but "
					<< "the line " << currLineNumber << " has "
					<< (parsedValues.size() + 1) + " columns.");
		}


		// Read data
		int columnIndex = 0;
		for (TParsedValues::const_iterator it = parsedValues.begin(); it != parsedValues.end(); ++it) {
			std::string strValue = (*it);

			double value;
			if (!String::toDouble(strValue, &value)) {
				RaiseComponentError(this, "The value '" << strValue << "' has incorrect double format.\n"
						<< "@see line " << currLineNumber
						<< " and column " << columnIndex << ".");
			}
			addValue(columnIndex, value);

			columnIndex++;
		}


		// Increment the counters
		readLines++;
		currLineNumber++;


		// Check to stop reading
		if (maxReadLines > 0) {
			if (maxReadLines <= readLines) {
				break;
			}
		}
	}
}

} //namespace filereader
} //namespace smoflow
