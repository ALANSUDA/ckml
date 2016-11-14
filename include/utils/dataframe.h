#pragma once
#ifndef __DATAFRAME_H__
#define __DATAFRAME_H__

#include "ckdef.h"
#include "types.h"
#include <vector>
#include <string>

namespace ckml {

class CK_EXPORTS DataFrame
{
private:
	std::vector<ColumnList> *data;
	Shape shape;
	
	void _split(std::string& s, std::string& delim, std::vector< std::string >* ret);
	void _trim(std::string& s, std::string symbol);

public:
	//���캯��
	DataFrame(); 
	DataFrame(Shape shape, int initValue);
	DataFrame(Shape shape, std::string initValue);
	DataFrame(Shape shape, double initValue);
	DataFrame(DataFrame &frame);
	DataFrame(DataFrame *frame);

	~DataFrame();

	//���һ��vector��
	void addCol(const std::vector<int>& vec,std::string name);
	void addCol(const std::vector<std::string>& vec, std::string name);
	void addCol(const std::vector<double>& vec, std::string name);

	//����һ��cell
	void updateItem(int value, ULong cols, ULong rows);
	void updateItem(std::string value, ULong cols, ULong rows);
	void updateItem(double value, ULong cols, ULong rows);

	//��Ƭ
	DataFrame slice(ULong cols, ULong rows, int colsLength, int rowsLength);

	//����ָ���е�����
	void setColName(ULong col,std::string name);
	std::string getColName(ULong col);

	//���dataframe
	std::vector<ColumnList>* getDataFrame();

	//����������
	Shape& getShape();
	void reshape(Shape shape);

	//������������
	void as(ULong col, ColumnList::DataType type);

	//print head
	void head(ULong fistN);

	//��cvs�ļ���ȡ����
	int readFromCSV(char* file,bool hasTile);
	int writeToCSV(char* file,bool hasTile);
};

}//namespace ckml

#endif