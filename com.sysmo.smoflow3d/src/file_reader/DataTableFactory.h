/*
 * DataTableFactory.h
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

#ifndef SMOFLOW_DATAREADER_DATATABLEFACTORY_H_
#define SMOFLOW_DATAREADER_DATATABLEFACTORY_H_

#include "file_reader/containers/TimeDataTable.h"
#include <vector>

namespace smoflow {
namespace filereader {

class DataTableFactory {
public:
	/*
	 * TimeDataTable functions
	 */
	static void clearTimeDataTables();

	static void createTimeDataTable(
			int dataTableIndex,
			const std::string& dataFileName,
			const std::string& dataSeparator,
			int headerLineNumber,
			int firstDataLineNumber,
			int maxReadLines,
			int timeColumnIndex);

	/*
	 * Get functions
	 */
	static double getValue(
			int dataTableIndex,
			int columnIndex,
			double time);

	static int getColumnIndex(
			int dataTableIndex,
			const std::string& columnName);

private:
	/*
	 * Variables
	 */
	static std::vector<TimeDataTable*> _dataTables;

	/*
	 * Helpful functions
	 */
	static TimeDataTable* getTimeDataTable_(int dataTableIndex);
	static TimeDataTable* getTimeDataTable(int dataTableIndex);
	static void addTimeDataTable(int dataTableIndex, TimeDataTable* dataTable);
};

} //namespace filereader
} //namespace smoflow
#endif /* SMOFLOW_DATAREADER_DATATABLEFACTORY_H_ */
