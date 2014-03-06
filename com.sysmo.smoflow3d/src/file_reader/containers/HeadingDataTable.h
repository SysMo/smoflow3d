/*
 * HeadingDataTable.h
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

#ifndef SMOFLOW_DATAREADER_HEADINGDATATABLE_H_
#define SMOFLOW_DATAREADER_HEADINGDATATABLE_H_

#include "file_reader/containers/DataTable.h"
#include <vector>
#include <string>

/*
 * Types
 */
typedef std::vector<std::string> THeaders;

namespace smoflow {
namespace filereader {

/**
 * This class presents a data table with headers.
 */
class HeadingDataTable: public DataTable {
public:
	/*
	 * Friend functions
	 */
	friend std::ostream& operator<<(std::ostream& out, const HeadingDataTable& dataTable);

	/*
	 * Initialize & Clear function
	 */
	virtual void clear();
	void initHeadersAndColumns(THeaders headers);

	/*
	 * Read data
	 */
	void readDataFromFile(
			const std::string& dataFileName,
			const std::string& dataSeparator,
			int headerLineNumber,
			int firstDataLineNumber,
			int maxReadLines);

	/*
	 * Get functions
	 */
	const THeaders& getHeaders() const;
	int getColumnIndex(const std::string& columnName) const;

private:

	/*
	 * Variables
	 */
	THeaders _headers;
};

} //namespace filereader
} //namespace smoflow
#endif /* SMOFLOW_DATAREADER_HEADINGDATATABLE_H_ */
