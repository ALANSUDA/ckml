#include "preproccess/Normalizer.h"

namespace ckml {
Normalizer::Normalizer(std::string norm):Algorithm()
{
	this->norm = norm;
}

Normalizer::Normalizer(Normalizer& norm) : Algorithm()
{
	this->norm = norm.norm;
}

bool Normalizer::train(DataFrame &x, DataFrame& y)
{
	return true;
}

void Normalizer::predict(DataFrame &x, DataFrame& ret)
{

}

void Normalizer::save(char* fname)
{

}

void Normalizer::load(const char* fname)
{

}

}//ckml