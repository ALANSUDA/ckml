#pragma once
#ifndef __SGDREGRESSION_H__
#define __SGDREGRESSION_H__

#include "utils/Algorithm.h"

namespace ckml {

class CK_EXPORTS SGDRegressor:public Algorithm
{
private:
	/*@brief The loss function to be used
	*@Param‘squared_loss’, ‘huber’, ‘epsilon_insensitive’, or ‘squared_epsilon_insensitive’
	*/
	std::string loss;

	/*@brief: The penalty (aka regularization term) to be used. 
	*@Param:‘none’, ‘l2’, ‘l1’, or ‘elasticnet’
	*/
	std::string penalty;

	/*@brief: Constant that multiplies the regularization term.
	*@Param:
	*/
	double alpha;

	/*@brief: The Elastic Net mixing parameter, with 0 <= l1_ratio <= 1. 
	*l1_ratio=0 corresponds to L2 penalty, l1_ratio=1 to L1. Defaults to 0.15.
	*@Param:
	*/
	double l1Ratio;

	/*@brief: Whether the intercept should be estimated or not.
	*If False, the data is assumed to be already centered. Defaults to True.
	*@Param:
	*/
	bool fitIntercept;

	/*@brief: The number of passes over the training data (aka epochs). 
	*The number of iterations is set to 1 if using partial_fit. Defaults to 5.
	*@Param:
	*/
	ULong numIter;

	/*@brief: Whether or not the training data should be shuffled after each epoch. Defaults to True.
	*@Param:
	*/
	bool shuffle;

	/*@brief: The seed of the pseudo random number generator to use when shuffling the data.
	*@Param: RandomState instance, or None (default)
	*/
	int randomState;

	/*@brief: The verbosity level.
	*@Param: 
	*/
	int verbose;

	/*@brief: Epsilon in the epsilon-insensitive loss functions; 
	*only if loss is ‘huber’, ‘epsilon_insensitive’, or ‘squared_epsilon_insensitive’. 
	*For ‘huber’, determines the threshold at which it becomes less important to get the 
	*prediction exactly right. For epsilon-insensitive, any differences between the
	*urrent prediction and the correct label are ignored if they are less than this threshold.
	*@Param:
	*/
	double epsilon;

	/*@brief: The learning rate schedule:
	*'constant’: eta = eta0
	*‘optimal’: eta = 1.0 / (alpha * (t + t0)) [default]
	*‘invscaling’: eta = eta0 / pow(t, power_t)
	* where t0 is chosen by a heuristic proposed by Leon Bottou.
	*@Param:
	*/
	std::string learningRate;

	/*@brief: The initial learning rate [default 0.01].
	*@Param:
	*/
	double eta0 = 0.01;

	/*@brief: The exponent for inverse scaling learning rate [default 0.25].
	*@Param:
	*/
	double powerT = 0.25;

	/*@brief: When set to True, reuse the solution of the previous 
	* call to fit as initialization, otherwise, just erase the previous solution.
	*@Param:
	*/
	bool warmStart;

	/*@brief: When set to True, computes the averaged SGD weights
	*and stores the result in the coef_ attribute. If set to an int greater than 1, 
	*averaging will begin once the total number of samples seen reaches average.
	*So average=10 will begin averaging after seeing 10 samples.
	*@Param:
	*/
	bool average;

	/*@brief: Weights assigned to the features.
	*@Param:shape (n_features)
	*/
	DataFrame *coef_;

	/*@brief: The intercept term.
	*@Param:shape (1)
	*/
	DataFrame *intercept_;

	/*@brief: Averaged weights assigned to the features.
	*@Param:shape (n_features)
	*/
	DataFrame *average_coef_;

	/*@brief: Averaged weights assigned to the features.
	*@Param:shape (1)
	*/
	DataFrame *average_intercept_;

public:
	/*@brief: 构造函数
	*@Param x :见私有变量
	*/
	SGDRegressor(std::string loss = "squared_loss",
				std::string penalty = "l2", 
				double alpha = 0.0001, 
				double l1_ratio = 0.15, 
				bool fit_intercept = true, 
				ULong n_iter = 5, 
				bool shuffle = true, 
				int verbose = 0, 
				double epsilon = 0.1, 
				int random_state = 0, 
				std::string learning_rate = "invscaling",
				double eta0 = 0.01, 
				double power_t = 0.25, 
				bool warm_start = false,
				bool average = false);

	SGDRegressor(SGDRegressor& SGDRegreesor);

	~SGDRegressor();

	/*@brief: 训练模型
	*@Param x :自变量，shape（n_features）
	*@Param y :因变量，shape（1）
	*/
	bool train(DataFrame& x, DataFrame& y);

	/*@brief: 模型预测
	*@Param x :自变量，shape（n_features）
	*@Param ret :因变量，shape（1）
	*/
	void predict(DataFrame &x, DataFrame& ret);

	/*@brief: 存储参数
	*@Param fname :全路径文件名称
	*/
	virtual void save(char* fname);

	/*@brief: 加载模型参数
	*@Param fname :全路径文件名称
	*/
	virtual void load(const char* fname);
};

}//ckml

#endif