/*
 * String.h
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

#ifndef SMO_CAST_H_
#define SMO_CAST_H_

#include <string>

namespace smoflow {

class String {
public:
	static bool toDouble(const std::string& strValue, double* value);
	static void trim(std::string& str);
};

} /* namespace smoflow */
#endif /* SMO_CAST_H_ */
