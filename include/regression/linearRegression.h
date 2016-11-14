#pragma once
#ifndef __LINEARREGRESSION_H__
#define __LINEARREGRESSION_H__

#include "utils/Algorithm.h"

namespace ckml {

class CK_EXPORTS LinearRegression:public Algorithm
{
private:
	//是否有bias
	bool fit_intercept = true;

	//是否归一化x
	bool normalize = false;

	DataFrame *coef_ = nullptr;

	DataFrame *intercept_ =  nullptr;

protected:
	void _preProcessData(DataFrame& x, DataFrame& y);

public:
	LinearRegression(bool fit_intercept = true, bool normalize = false);
	LinearRegression(LinearRegression& estimator);
	~LinearRegression();

	bool train(DataFrame& x, DataFrame& y);

	void predict(DataFrame &x, DataFrame& ret);

	virtual void save(char* fname);

	virtual void load(const char* fname);
};

}//ckml

#endif