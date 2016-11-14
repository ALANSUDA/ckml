#pragma once
#ifndef __TYPES_H__
#define __TYPES_H__

#include "ckdef.h"

#include <string>

namespace ckml{
/*
*@brief dataframe中的列变量类型，每个列是由vector构成，并制定了vector的元素类型
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

	//vector 的类型标志
	int type_flag;

	//指向vector变量
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