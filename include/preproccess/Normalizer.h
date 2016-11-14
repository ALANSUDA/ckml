#pragma once
#ifndef __NORMALIZER_H__
#define __NORMALIZER_H__

#include "utils/Algorithm.h"

namespace ckml {

class CK_EXPORTS Normalizer:public Algorithm
{
private:
	std::string norm = "l2";

public:
	// l1 l2 max
	Normalizer(std::string norm = "l2");
	Normalizer(Normalizer& norm);

	bool train(DataFrame &x, DataFrame& y);

	void predict(DataFrame &x, DataFrame& ret);
	
	void save(char* fname);

	void load(const char* fname);
};

}//ckml

#endif