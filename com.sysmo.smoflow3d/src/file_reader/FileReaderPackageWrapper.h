/*
 * FileReaderPackageWrapper.h
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

#ifndef FILEREADERPACKAGEWRAPPER_H_
#define FILEREADERPACKAGEWRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

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
		int timeColumnIndex);

void FileReader_getColumnIndex(
		int dataTableIndex,
		const char* columnName,
		int* columnIndex);

void FileReader_getValue(
		int dataTableIndex,
		int columnIndex,
		double time,
		double* value);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* FILEREADERPACKAGEWRAPPER_H_ */
