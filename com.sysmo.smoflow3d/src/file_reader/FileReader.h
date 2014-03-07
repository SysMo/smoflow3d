/*
 * FileReader.h
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

#ifndef FILEREADER_H_
#define FILEREADER_H_

#include "util/CommonDefinitions.h"

#ifdef __cplusplus

#include "file_reader/containers/TimeDataTable.h"

typedef smoflow::filereader::TimeDataTable FileReader;

#else

DECLARE_C_STRUCT(FileReader)

#endif //__cplusplus

BEGIN_C_LINKAGE
void FileReader_register(int fileReaderIndex, int timeColumnIndex);
FileReader* FileReader_get(int fileReaderIndex);
int FileReader_index(FileReader* fileReader);

void FileReader_readDataFromFile(
		FileReader* fileReader,
		const char* dataFileName,
		const char* dataSeparator,
		int headerLineNumber,
		int firstDataLineNumber,
		int maxReadLines);

int FileReader_getColumnIndex(
		FileReader* fileReader,
		const char* columnName);

double FileReader_getValue(
		FileReader* fileReader,
		int columnIndex,
		double time);

END_C_LINKAGE

#endif /* FILEREADER_H_ */
