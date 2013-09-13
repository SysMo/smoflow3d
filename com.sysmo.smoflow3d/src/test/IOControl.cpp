/*
 * IOControl.cpp
 *
 *  Created on: Sep 6, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "io_control/CSVProcessor.h"
#include "io_control/DriveCycleReader.h"


#define BEGIN_TEST(name) \
	std::cout << "====================================\n" \
			  << " Begin test " << name << "\n" \
			  << "------------------------------------\n"

#define END_TEST \
	std::cout << "------------------------------------\n"

void testRowReader() {
	BEGIN_TEST("RowReader");
	String a("123,4567,\"lmnopq\"");
	CSVRowReader reader;
	reader.setDelimiter(',');
	reader.setRowContent(a);
	int status;
	double  floatVal;
	int intVal;
	String stringVal;
	status = reader.getNextFloat(floatVal);
	std::cout << floatVal << "(" << status << ")\n";
	status = reader.getNextInteger(intVal);
	std::cout << intVal << "(" << status << ")\n";
	status = reader.getNextString(stringVal);
	std::cout << stringVal << "(" << status << ")\n";
	status = reader.getNextFloat(floatVal);
	std::cout << floatVal << "(" << status << ")\n";
	END_TEST;
}

void testCSVProcessor() {
	BEGIN_TEST("CSVProcessor");
	String fileName("src\\test\\CSVExample.csv");
	CSVProcessor csv;
	VectorString name;
	VectorFloat age;
	VectorFloat salary;
	VectorInt children;
	csv.addStringColumn(name);
	csv.addFloatColumn(age);
	csv.addFloatColumn(salary);
	csv.addIntegerColumn(children);
	csv.read(fileName, ',', 1);
	std::cout << name.size() << " rows read from the csv file \n";
	for (size_t i = 0; i < name.size(); i++) {
		std::cout
			<< "Name: " << name.at(i)
			<< ", Age: " << age.at(i)
			<< ", Salary: " << salary.at(i)
			<< ", Children: " << children.at(i)
			<< std::endl;
	}
	END_TEST;
}

void testDriveCycleReader() {
	BEGIN_TEST("DriveCycleReader");
	String fileName("src/test/E149189.csv");
	DriveCycleReader dcReader(fileName);

	END_TEST;
}

int main(int argc, char* argv) {
	testRowReader();
	testCSVProcessor();
	testDriveCycleReader();
	return 0;
}
