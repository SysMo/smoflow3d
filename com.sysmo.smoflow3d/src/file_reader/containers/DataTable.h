/*
 * DataTable.h
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

#ifndef SMOFLOW_DATAREADER_DATATABLE_H_
#define SMOFLOW_DATAREADER_DATATABLE_H_

#include <vector>
#include <iostream>
#include "util/CommonDefinitions.h"

/*
 * Types
 */
typedef std::vector<double> TDataColumn;
typedef std::vector<TDataColumn*> TDataColumns;
typedef TDataColumns::iterator TIterDataColumns;

namespace smoflow {
namespace filereader {

/**
 * This class presents a data table that contains columns with double values
 * (i.e. vector<vector<double>*>).
 */
class DataTable {
public:
	/*
	 * Friend functions
	 */
	friend std::ostream& operator<<(std::ostream& out, const DataTable& dataTable);

	/*
	 * Constructor & Destructor
	 */
	DataTable();
	virtual ~DataTable();

	/*
	 * Initialize & Clear functions
	 */
	virtual void clear();
	void initColumns(int columnNumber);
	void addValue(int columnIndex, double value);

	/*
	 * Get functions
	 */
	int getRowNumber() const;
	int getColumnNumber() const;

	const TDataColumn* getDataColumn(int columnIndex) const;
	double getValue(int rowIndex, int columnIndex) const;

private:

	/*
	 * Variables
	 */
	TDataColumns _dataColumns;


	/*
	 * Constructor
	 */
	DataTable(const DataTable& dataTable);
};

} //namespace filereder
} //namespace smoflow
#endif /* SMOFLOW_DATAREADER_DATATABLE_H_ */
