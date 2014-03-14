/*
 * TimeDataTable.cpp
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

#include "file_reader/containers/TimeDataTable.h"

namespace smoflow {
namespace filereader {

TimeDataTable::TimeDataTable(int timeColumnIndex) {
	_timeColumnIndex = timeColumnIndex;

	_lastTimeRowIndex1 = 0;
	_lastTimeRowIndex2 = 0;
	_lastTimeValue1 = -0.1; //TRICKY
	_lastTimeValue2 = -0.1; //TRICKY
}

TimeDataTable::~TimeDataTable() {

}

/**
 * @return the column index of the time column.
 */
int TimeDataTable::getTimeColumnIndex() const {
	return _timeColumnIndex;
}

/**
 * @return a pointer to the time data column
 */
const TDataColumn* TimeDataTable::getTimeDataColumn() const {
	return getDataColumn(getTimeColumnIndex());
}

/**
 * Get the linear interpolated value by time.
 * @note a linear interpolation is used.
 *
 * @example if we have this time data table:
 * <time>	<temperature>
 * 0		100
 * 1		200
 * 2		100
 *
 * Calling of getInterpolatedValue(1, 0.2) will return 120.
 * Calling of getInterpolatedValue(1, 1.2) will return 180.
 *
 *
 * @param columnIncex the index of column from which the interpolated value is returned.
 * @param time the input time value.
 * @return the interpolated value by time from the column with index columnIndex.
 */
double TimeDataTable::getValue(int columnIndex, double time) {

	if (_lastTimeValue1 <= time && time <= _lastTimeValue2) {
		return getInterpolatedValue(columnIndex, time);
	}


	int startRowIndex = 1;
	if (time > _lastTimeValue2) {
		startRowIndex = _lastTimeRowIndex2 + 1;
	} else if (time < _lastTimeValue1) {
		startRowIndex = 1;
	}

	const TDataColumn& timeDataColumn = (*getTimeDataColumn());
	for (int iRow = startRowIndex; iRow < getRowNumber(); ++iRow) {
		double currTimeValue = timeDataColumn[iRow];
		if (time <= currTimeValue) {
			_lastTimeRowIndex1 = iRow - 1;
			_lastTimeRowIndex2 = iRow;

			_lastTimeValue1 = timeDataColumn[_lastTimeRowIndex1];
			_lastTimeValue2 = timeDataColumn[_lastTimeRowIndex2];

			return getInterpolatedValue(columnIndex, time);
		}
	}

	//*/ Extrapolate with the last known value
	const TDataColumn& dataColumn = (*getDataColumn(columnIndex));
	return dataColumn[_lastTimeRowIndex2];
	//*/

	/*/
	// Throw an error
	RaiseComponentError(this, "The input time value " << time << " is out of range. "
			<< "It should be between " << timeDataColumn[0] << " and " << timeDataColumn[timeDataColumn.size() -1] << ".\n");

	return -1.0;
	//*/
}

/**
 * A private helpful function for getting the interpolated value by time.
 * @note a linear interpolation is used.
 *
 * @see \ref smoflow::filereader::TimeDataTable::getValue function.
 */
double TimeDataTable::getInterpolatedValue(int columnIndex, double time) const {
	const TDataColumn& dataColumn = (*getDataColumn(columnIndex));
	double value1 = dataColumn[_lastTimeRowIndex1];
	double value2 = dataColumn[_lastTimeRowIndex2];

	double ratio = (time - _lastTimeValue1)/(_lastTimeValue2 - _lastTimeValue1);
	return value1 + (value2 - value1)*ratio;
}

/**
 * Check the data time for correctness.
 * @note this function throws an exception.
 */
void TimeDataTable::isTimeDataOK() {
	const TDataColumn& timeDataColumn = (*getTimeDataColumn());
	if (timeDataColumn.size() < 1) {
		RaiseComponentError(this, "There is not time values in the data.");
	}

	if (timeDataColumn.size() == 1) {
		RaiseComponentError(this, "There is only one time value in the data.");
	}

	if (timeDataColumn[0] != 0.0) {
		RaiseComponentError(this, "The first value " << timeDataColumn[0] << " of time is different from zero.");
	}

	double timeValue1 = timeDataColumn[0];
	double timeValue2 = timeDataColumn[1];
	for (unsigned i = 1; i < timeDataColumn.size(); ++i) {
		timeValue2 = timeDataColumn[i];
		if (timeValue2 <= timeValue1) {
			RaiseComponentError(this, "Time values are not increasing.\n"
					<< "@see time[" << (i-1) << "] = " << timeDataColumn[i-1]
					<< " and time[" << i << "] = " << timeDataColumn[i]);
		}

		timeValue1 = timeValue2;
	}
}

} //namespace filereader
} //namespace smoflow
