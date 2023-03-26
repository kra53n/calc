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

	std::vector<std::vector<int>> parse_matrix(std::string s);
	std::vector<std::vector<int>> multiplyMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);
	std::vector<std::vector<int>> addMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);
	std::vector<std::vector<int>> subtractMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);
	std::vector<std::vector<int>> divideMatrixByNumber(const std::vector<std::vector<int>>& A, int num);
	std::string result() const;
	int get_data() const;

	Calculatable* add(Calculatable* other);
	Calculatable* sub(Calculatable* other);
	Calculatable* mul(Calculatable* other);
	Calculatable* div(Calculatable* other);
	//Calculatable* rtd(Calculatable* other);
};

