#include "regression/linearRegression.h"

namespace ckml{
LinearRegression::LinearRegression(bool fit_intercept, bool normalize):Algorithm()
{
	this->fit_intercept = fit_intercept;
	this->normalize = normalize;

	this->coef_ = nullptr;
	this->intercept_ = nullptr;
}

LinearRegression::LinearRegression(LinearRegression& estimator):Algorithm()
{
	this->fit_intercept = estimator.fit_intercept;
	this->normalize = estimator.normalize;

	this->coef_ = estimator.coef_;
	this->intercept_ = estimator.intercept_;
}

LinearRegression::~LinearRegression()
{
	if (this->coef_)
	{
		delete coef_;
	}
	
	if (this->intercept_)
	{
		delete intercept_;
	}
}

void LinearRegression::_preProcessData(DataFrame& x, DataFrame& y)
{

}
bool LinearRegression::train(DataFrame& x, DataFrame& y)
{
	if (normalize)
	{
		_preProcessData(x, y);
	}

	return true;
}

void LinearRegression::predict(DataFrame &x, DataFrame& ret)
{

}

void LinearRegression::save(char* fname)
{

}

void LinearRegression::load(const char* fname)
{

}

}//ckml