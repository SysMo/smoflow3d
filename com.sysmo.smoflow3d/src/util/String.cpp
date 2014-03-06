/*
 * String.cpp
 *
 * Created on: Mar 4, 2011
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
#include "util/String.h"
#include <cstdlib>

namespace smoflow {

bool String::toDouble(const std::string& strValue, double* value) {
	char* end = 0;
	*value = strtod(strValue.c_str(), &end);

	 if (*end == 0) {
		 return true;
	 } else {
		 return false;
	 }
}

void String::trim(std::string& str) {
	static const std::string WHITESPACE = " \n\r\t";
	str.erase(0, str.find_first_not_of(WHITESPACE)); //prefixing spaces
	str.erase(str.find_last_not_of(WHITESPACE) + 1); //surfixing spaces
}

} /* namespace smoflow */
