#pragma once
#ifndef __TYPES_H__
#define __TYPES_H__

#include "ckdef.h"

#include <string>

namespace ckml{
/*
*@brief dataframe�е��б������ͣ�ÿ��������vector���ɣ����ƶ���vector��Ԫ������
*/
struct CK_EXPORTS _Column
{
	//ervery column data type
	enum DataType{
		KIND_SHIFT = 16,

		KIND_MASK = 31 << KIND_SHIFT,

		STRING_TYPE = 1 << KIND_SHIFT,
		DOUBLE_TYPE = 2 << KIND_SHIFT,
		INT_TYPE = 3 << KIND_SHIFT,
	};

	//vector �����ͱ�־
	int type_flag;

	//ָ��vector����
	void* object = nullptr;

	//name
	std::string colName;
};

typedef struct _Column ColumnList;

typedef unsigned long ULong;

struct _shape
{
	ULong row;
	ULong col;
};

typedef struct _shape Shape;

}//ckml

#endif