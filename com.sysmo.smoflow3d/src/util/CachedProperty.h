/*
 * CachedProperty.h
 *
 *  Created on: Jul 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef CACHEDPROPERTY_H_
#define CACHEDPROPERTY_H_

class CachedProperty {
public:
	/// Default constructor
	CachedProperty();
	/// Assignment operator - sets the value and sets the flag
	void operator=( const double& value);
	/// Cast to boolean, for checking if cached
	operator bool() const;
	/// Cast to double, for returning value
	operator double() const;
	/// Clear the flag and the value
	void clear();
private:
	bool is_cached;
	double value;
};

#endif /* CACHEDPROPERTY_H_ */
