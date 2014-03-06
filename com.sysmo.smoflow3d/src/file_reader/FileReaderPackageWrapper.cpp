/*
 * FileReaderPackageWrapper.cpp
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

#include "file_reader/FileReaderPackageWrapper.h"
#include "file_reader/DataTableFactory.h"
#include <string>

using smoflow::filereader::DataTableFactory;

/*
 * FileReader
 */
void FileReader_createTimeDataTable(
		int dataTableIndex,
		const char* dataFileName,
		const char* dataSeparator,
		int headerLineNumber,
		int firstDataLineNumber,
		int maxReadLines,
		int timeColumnIndex) {
	DataTableFactory::createTimeDataTable(
			dataTableIndex - 1,
			dataFileName,
			dataSeparator,
			headerLineNumber - 1,
			firstDataLineNumber -1 ,
			maxReadLines,
			timeColumnIndex - 1);
}

void FileReader_getColumnIndex(
		int dataTableIndex,
		const char* columnName,
		int* columnIndex) {
	*columnIndex = DataTableFactory::getColumnIndex(
				dataTableIndex - 1,
				columnName) + 1;
}

void FileReader_getValue(
		int dataTableIndex,
		int columnIndex,
		double time,
		double* value) {
	*value = DataTableFactory::getValue(
				dataTableIndex - 1,
				columnIndex -1,
				time);
}
