#include "regression/sgdregressor.h"
#include "atlas/cblas.h"

namespace ckml {

SGDRegressor::SGDRegressor(std::string loss,
				std::string penalty, 
				double alpha, 
				double l1_ratio, 
				bool fit_intercept, 
				ULong n_iter, 
				bool shuffle, 
				int verbose, 
				double epsilon, 
				int random_state, 
				std::string learning_rate,
				double eta0, 
				double power_t, 
				bool warm_start,
				bool average):Algorithm()
{
	this->loss = loss;
	this->penalty = penalty;
	this->alpha = alpha;
	this->l1Ratio = l1_ratio;
	this->fitIntercept = fit_intercept;
	this->numIter = n_iter;
	this->shuffle = shuffle;
	this->verbose = verbose;
	this->epsilon = epsilon;
	this->randomState = random_state;
	this->learningRate = learning_rate;
	this->eta0 = eta0;
	this->powerT = power_t;
	this->warmStart = warm_start;
	this->average = average;

	this->coef_ = nullptr;
	this->intercept_ = nullptr;
	this->average_coef_ = nullptr;
	this->average_intercept_ = nullptr;
}

SGDRegressor::SGDRegressor(SGDRegressor& SGDReg)
{
	this->loss = SGDReg.loss;
	this->penalty = SGDReg.penalty;
	this->alpha = SGDReg.alpha;
	this->l1Ratio = SGDReg.l1Ratio;
	this->fitIntercept = SGDReg.fitIntercept;
	this->numIter = SGDReg.numIter;
	this->shuffle = SGDReg.shuffle;
	this->verbose = SGDReg.verbose;
	this->epsilon = SGDReg.epsilon;
	this->randomState = SGDReg.randomState;
	this->learningRate = SGDReg.learningRate;
	this->eta0 = SGDReg.eta0;
	this->powerT = SGDReg.powerT;
	this->warmStart = SGDReg.warmStart;
	this->average = SGDReg.average;

	//lower copy
	this->coef_ = SGDReg.coef_;
	this->intercept_ = SGDReg.intercept_;
	this->average_coef_ = SGDReg.average_coef_;
	this->average_intercept_ = SGDReg.average_intercept_;
}

SGDRegressor::~SGDRegressor()
{
	if (coef_)
	{
		delete coef_;
	}

	if (intercept_)
	{
		delete intercept_;
	}

	if (average_coef_)
	{
		delete average_coef_;
	}

	if (average_intercept_)
	{
		delete average_intercept_;
	}
}

bool SGDRegressor::train(DataFrame& x,DataFrame& y)
{
	return true;
}

void SGDRegressor::predict(DataFrame &x, DataFrame& ret)
{

}

void SGDRegressor::save(char* fname)
{

}

void SGDRegressor::load(const char* fname)
{

}

}//end ckml