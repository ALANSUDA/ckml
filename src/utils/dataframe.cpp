#include "utils/dataframe.h"

#include <assert.h>
#include <fstream>
#include <iostream>
#include <iomanip>

namespace ckml {

DataFrame::DataFrame()
{
	data = nullptr;
	shape.col = 0;
	shape.row = 0;
}

DataFrame::DataFrame(Shape shape, int initValue)
{
	//初始化data指针
	data = new std::vector<ColumnList>;

	this->shape.col = shape.col;
	this->shape.row = shape.row;

	for (auto i = 0; i < shape.col; i++)
	{
		ColumnList item;
		item.colName = "NoName";
		item.type_flag = ColumnList::INT_TYPE;
		item.object = (void*) new std::vector<int>(shape.row, initValue);

		data->push_back(item);
	}
}

DataFrame::DataFrame(Shape shape, std::string initValue)
{
	//初始化data指针
	data = new std::vector<ColumnList>;

	this->shape.col = shape.col;
	this->shape.row = shape.row;

	for (auto i = 0; i < shape.col; i++)
	{
		ColumnList item;
		item.colName = "NoName";
		item.type_flag = ColumnList::STRING_TYPE;
		item.object = (void*) new std::vector<std::string>(shape.row, initValue);

		data->push_back(item);
	}
}

DataFrame::DataFrame(Shape shape, double initValue)
{
	//初始化data指针
	data = new std::vector<ColumnList>;

	this->shape.col = shape.col;
	this->shape.row = shape.row;

	for (auto i = 0; i < shape.col; i++)
	{
		ColumnList item;
		item.colName = "NoName";
		item.type_flag = ColumnList::DOUBLE_TYPE;
		item.object = (void*) new std::vector<double>(shape.row, initValue);

		data->push_back(item);
	}
}

//lower copy, this is a bug
DataFrame::DataFrame(DataFrame &frame)
{
	this->data = frame.getDataFrame();
	Shape shape = frame.getShape();
	this->shape.col = shape.col;
	this->shape.row = shape.row;
}

DataFrame::DataFrame(DataFrame *frame)
{

}

DataFrame::~DataFrame()
{
	if (data != nullptr)
	{
		for (std::vector<ColumnList>::iterator it = data->begin(); it != data->end(); ++it)
		{
			delete it->object;
			it->object = nullptr;
		}

		delete data;
		data = nullptr;
	}	
}

void DataFrame::addCol(const std::vector<int>& vec, std::string name)
{
	if (data == nullptr)
	{
		data = new std::vector<ColumnList>;
	}

	ColumnList item;
	item.colName = name;
	item.type_flag = ColumnList::INT_TYPE;
	item.object = (void*) new std::vector<int>(vec.begin(), vec.end());

	data->push_back(item);
	shape.col++;
	if (shape.row < vec.size())
	{
		shape.row = vec.size();
	}	
}

void DataFrame::addCol(const std::vector<std::string>& vec, std::string name)
{
	if (data == nullptr)
	{
		data = new std::vector<ColumnList>;
	}

	ColumnList item;
	item.colName = name;
	item.type_flag = ColumnList::STRING_TYPE;
	item.object = (void*) new std::vector<std::string>(vec.begin(), vec.end());

	data->push_back(item);
	shape.col++;
	if (shape.row < vec.size())
	{
		shape.row = vec.size();
	}
}

void DataFrame::addCol(const std::vector<double>& vec, std::string name)
{
	if (data == nullptr)
	{
		data = new std::vector<ColumnList>;
	}

	ColumnList item;
	item.colName = name;
	item.type_flag = ColumnList::DOUBLE_TYPE;
	item.object = (void*) new std::vector<double>(vec.begin(), vec.end());

	data->push_back(item);
	shape.col++;
	if (shape.row < vec.size())
	{
		shape.row = vec.size();
	}
}

//todo check type
void DataFrame::updateItem(int value, ULong cols, ULong rows)
{
	if (this->shape.col > cols)
	{
		ColumnList item = data->at(cols);

		if (rows < this->shape.row)
		{
			std::vector<int>* col = (std::vector<int>*)item.object;
			col->at(rows) = value;
		}
	}	
}

void DataFrame::updateItem(std::string value, ULong cols, ULong rows)
{
	if (this->shape.col > cols)
	{
		ColumnList item = data->at(cols);

		if (rows < this->shape.row)
		{
			std::vector<std::string>* col = (std::vector<std::string>*)item.object;
			col->at(rows) = value;
		}
	}
}

void DataFrame::updateItem(double value, ULong cols, ULong rows)
{
	if (this->shape.col > cols)
	{
		ColumnList item = data->at(cols);

		if (rows < this->shape.row)
		{
			std::vector<double>* col = (std::vector<double>*)item.object;
			col->at(rows) = value;
		}
	}
}

DataFrame DataFrame::slice(ULong cols, ULong rows, int colsLength, int rowsLength)
{
	return this;
}

void DataFrame::setColName(ULong col, std::string name)
{
	if (this->shape.col > col)
	{
		data->at(col).colName = name;
	}
}

std::string DataFrame::getColName(ULong col)
{
	std::string name = "";

	if (this->shape.col > col)
	{
		ColumnList item = data->at(col);

		name = item.colName;
	}

	return name;
}

std::vector<ColumnList>* DataFrame::getDataFrame()
{
	return this->data;
}

//todo drop other data or return new dataframe
void DataFrame::reshape(Shape shape)
{
	this->shape.col = shape.col;
	this->shape.row = shape.row;
}

Shape& DataFrame::getShape()
{
	return this->shape;
}

void DataFrame::as(ULong col,ColumnList::DataType type)
{
	ColumnList colItem = data->at(col);

	void* newColData = nullptr;

	//change int type into other
	if (colItem.type_flag == ColumnList::INT_TYPE)
	{
		if (type == ColumnList::INT_TYPE)
		{
			return;
		}

		if (type == ColumnList::DOUBLE_TYPE)
		{
			newColData = (void*) new std::vector<double>;
		}
		if (type == ColumnList::STRING_TYPE)
		{
			newColData = (void*) new std::vector<std::string>;
		}

		std::vector<int>* colData = ((std::vector<int>*)(colItem.object));
		for (std::vector<int>::iterator it = colData->begin(); it != colData->end(); ++it)
		{
			if (type == ColumnList::DOUBLE_TYPE)
			{
				((std::vector<double>*)newColData)->push_back((double)(*it));
			}
			if (type == ColumnList::STRING_TYPE)
			{
				((std::vector<std::string>*)newColData)->push_back(std::to_string(*it));
			}
		}

		delete colData;
	}

	//change double type into other
	if (colItem.type_flag == ColumnList::DOUBLE_TYPE)
	{
		if (type == ColumnList::DOUBLE_TYPE)
		{
			return;
		}

		if (type == ColumnList::INT_TYPE)
		{
			newColData = (void*) new std::vector<int>;
		}
		if (type == ColumnList::STRING_TYPE)
		{
			newColData = (void*) new std::vector<std::string>;
		}

		std::vector<double>* colData = ((std::vector<double>*)(colItem.object));
		for (std::vector<double>::iterator it = colData->begin(); it != colData->end(); ++it)
		{
			if (type == ColumnList::INT_TYPE)
			{
				((std::vector<int>*)newColData)->push_back((int)(*it));
			}
			if (type == ColumnList::STRING_TYPE)
			{
				((std::vector<std::string>*)newColData)->push_back(std::to_string(*it));
			}
		}

		delete colData;
	}

	//change string type into other
	if (colItem.type_flag == ColumnList::STRING_TYPE)
	{
		if (type == ColumnList::STRING_TYPE)
		{
			return;
		}
		
		if (type == ColumnList::INT_TYPE)
		{
			newColData = (void*) new std::vector<int>;
		}
		if (type == ColumnList::DOUBLE_TYPE)
		{
			newColData = (void*) new std::vector<double>;
		}

		std::vector<std::string>* colData = ((std::vector<std::string>*)(colItem.object));
		for (std::vector<std::string>::iterator it = colData->begin(); it != colData->end(); ++it)
		{
			if (type == ColumnList::INT_TYPE)
			{
				((std::vector<int>*)newColData)->push_back(atoi(it->c_str()));
			}
			if (type == ColumnList::DOUBLE_TYPE)
			{
				((std::vector<double>*)newColData)->push_back(atof(it->c_str()));
			}
		}

		delete colData;
	}

	colItem.object = newColData;
	colItem.type_flag = type;
	data->at(col) = colItem;
}

void DataFrame::head(ULong fistN)
{
	for (std::vector<ColumnList>::iterator it = data->begin(); it != data->end(); ++it)
	{
		std::cout << std::left << std::setw(40) << it->colName << "\t";
	}
	std::cout << std::endl;


	for (ULong row = 0; row < fistN; row++)
	{
		for (std::vector<ColumnList>::iterator it = data->begin(); it != data->end(); ++it)
		{
			if (it->type_flag == ColumnList::STRING_TYPE)
			{
				std::cout << std::left << std::setw(40) << ((std::vector<std::string>*)(it->object))->at(row) << "\t";
			}

			if (it->type_flag == ColumnList::INT_TYPE)
			{
				std::cout << std::left << std::setw(40) << ((std::vector<int>*)(it->object))->at(row) << "\t";
			}

			if (it->type_flag == ColumnList::DOUBLE_TYPE)
			{
				std::cout << std::left << std::setw(40) << ((std::vector<double>*)(it->object))->at(row) << "\t";
			}			
		}

		std::cout << std:: endl;
	}
}

int DataFrame::readFromCSV(char* file,bool hasTile)
{
	std::ifstream icsv(file,std::ifstream::binary);

	if (!icsv)
	{
		return CK_ERROR;
	}

	ULong col = 0, row = 0;

	data = new std::vector<ColumnList>;

	//construct head
	if (icsv)
	{
		std::string rowData;
		std::getline(icsv, rowData);

		std::vector<std::string> splitData;
		_split(rowData, std::string(","), &splitData);

		for (auto item : splitData)
		{
			ColumnList colItem ;
			colItem.object = (void*)new std::vector<std::string>;
			colItem.type_flag = ColumnList::STRING_TYPE;

			_trim(item,"\r");

			if (hasTile)
			{
				colItem.colName = item;
			}
			else
			{
				colItem.colName = "NoName";				
				((std::vector<std::string>*)colItem.object)->push_back(item);
			}

			data->push_back(colItem);

			col++;
		}
		row++;
	}

	while (icsv.good())
	{
		std::string rowData;
		std::getline(icsv, rowData);

		std::vector<std::string> splitData;
		_split(rowData, std::string(","), &splitData);

		col= 0;
		for (std::vector<ColumnList>::iterator it = data->begin(); it != data->end(); ++it)
		{
			try
			{
				std::string cellValue = splitData.at(col);
				_trim(cellValue, "\r");

				((std::vector<std::string>*)(it->object))->push_back(cellValue);
			}
			catch (...)
			{
				((std::vector<std::string>*)(it->object))->push_back("");
			}
			col++;
		}
		row++;
	}

	shape.col = col;
	shape.row = row;

	icsv.close();

	return CK_TRUE;
}

int DataFrame::writeToCSV(char* file, bool hasTile)
{
	std::ofstream ocsv(file, std::ofstream::binary);

	if (ocsv)
	{
		ULong rows = shape.row;

		if (hasTile)
		{
			ULong col = 1;
			for (std::vector<ColumnList>::iterator it = data->begin(); it != data->end(); ++it)
			{
				ocsv << it->colName;

				if (col < shape.col)
				{
					ocsv << ",";
				}
				else
				{
					ocsv << std::endl;
				}
				col++;
			}
			rows = shape.row - 1;
		}

		for (ULong row = 0; row < rows; row++)
		{
			ULong col = 1;
			for (std::vector<ColumnList>::iterator it = data->begin(); it != data->end(); ++it)
			{
				if (it->type_flag == ColumnList::STRING_TYPE)
				{
					std::vector<std::string>* colData = (std::vector<std::string>*)(it->object);

					std::string cellValue = colData->at(row);
					ocsv << cellValue;
				}

				if (it->type_flag == ColumnList::INT_TYPE)
				{
					std::vector<int>* colData = (std::vector<int>*)(it->object);

					int cellValue = colData->at(row);
					ocsv << cellValue;
				}

				if (it->type_flag == ColumnList::DOUBLE_TYPE)
				{
					std::vector<double>* colData = (std::vector<double>*)(it->object);

					double cellValue = colData->at(row);
					ocsv << cellValue;
				}				

				if (col < shape.col)
				{
					ocsv << ",";
				}
				else
				{
					ocsv << std::endl;
				}
				col++;
			}
		}

		return CK_TRUE;
	}

	return CK_ERROR;
}

void DataFrame::_split(std::string& s, std::string& delim, std::vector< std::string >* ret)
{
	size_t last = 0;
	size_t index = s.find_first_of(delim, last);
	while (index != std::string::npos)
	{
		ret->push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(delim, last);
	}
	if (index - last>0)
	{
		ret->push_back(s.substr(last, index - last));
	}
}

void DataFrame::_trim(std::string& s, std::string symbol)
{
	size_t n = s.find_last_not_of(symbol);
	if (n != std::string::npos)
	{
		s.erase(n + 1, s.size() - n);
	}

	n = s.find_first_not_of(symbol);
	if (n != std::string::npos)
	{
		s.erase(0, n);
	}

	if (s == symbol)
	{
		s = "";
	}
}

}//namespace ckml