// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ckml.h"
#include <iostream>

using namespace ckml;

int main()
{
	ckml::DataFrame data;
	std::cout << "read csv..." << std::endl;
	data.readFromCSV("test.csv", true);

	std::cout << std::endl;

	data.as(2, ColumnList::INT_TYPE);

	data.head(4);

	std::cout << std::endl;

	int ret = data.writeToCSV("kk.csv", true);
	if (ret == CK_ERROR)
	{
		std::cout << "write error" << std::endl;
	}

	system("pause");
    return 0;
}

