/*
 * TimeDataTable.h
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

#ifndef SMOFLOW_DATAREADER_TIMEDATATABLE_H_
#define SMOFLOW_DATAREADER_TIMEDATATABLE_H_

#include "file_reader/containers/HeadingDataTable.h"

namespace smoflow {
namespace filereader {


/**
 * This class presents data table with time column.
 */
class TimeDataTable : public HeadingDataTable {
public:
	/*
	 * Constructor & Desctructor
	 */
	TimeDataTable(int timeColumnIndex);
	virtual ~TimeDataTable();

	/*
	 * Get functions
	 */
	int getTimeColumnIndex() const ;
	const TDataColumn* getTimeDataColumn() const;

	double getValue(int columnIndex, double time);

	/*
	 * Checks
	 */
	void isTimeDataOK() const;

private:
	/*
	 * Variables
	 */
	int _timeColumnIndex;

	int _lastTimeRowIndex1;
	int _lastTimeRowIndex2;
	double _lastTimeValue1;
	double _lastTimeValue2;

	/*
	 * Helpful functions
	 */
	double getInterpolatedValue(int columnIndex, double time) const;
};

} //namespace filereader
} //namespace smoflow
#endif /* SMOFLOW_DATAREADER_TIMEDATATABLE_H_ */
