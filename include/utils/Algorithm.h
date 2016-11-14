#pragma once
#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include "ckdef.h"
#include "types.h"
#include "dataframe.h"

namespace ckml{

class CK_EXPORTS Algorithm
{
public:

	/** @brief �洢�㷨����
	*/
	virtual void save(char* fname)=0;

	/** @brief ��ȡ�㷨����
	*/
	virtual void load(const char* fname)=0;

	/** @brief �洢�㷨����
	*/
	virtual bool train(DataFrame &x,DataFrame &y) = 0;

	/** @brief �洢�㷨����
	*/
	virtual void predict(DataFrame &x) = 0;
};

}//ckml

#endif