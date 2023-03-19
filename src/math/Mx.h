#pragma once
#include <string>
#include "Fraction.hpp"
#include "Calculatable.hpp"
#include "Token.hpp"
#include <vector>
class Mx : public Calculatable
{

public:
	int R, C;
	std::vector<std::vector<int>> data;
	std::vector<std::vector<int>> Result;
	Mx(std::string& text);
	~Mx();
	std::string result() const;

	int get_data() const;
	//Calculatable* add(Calculatable* other);
	//Calculatable* sub(Calculatable* other);
	Calculatable* mul(Calculatable* other);
	//Calculatable* div(Calculatable* other);
	//Calculatable* rtd(Calculatable* other);
};

