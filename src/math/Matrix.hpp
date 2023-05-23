#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "Num.hpp"
#include "Fraction.hpp"
#include "../errors.hpp"
#include "Calculable.hpp"
#include "../syntax/Token.hpp"

class Matrix : public Calculable
{
    int R, C;
    std::vector<std::vector<int>> data;
public:
    Matrix(std::string& text);
    Matrix(std::vector<std::vector<int>> data);
    ~Matrix();

    std::vector<std::vector<int>> parse_matrix(std::string s);
    std::vector<std::vector<int>> add_matrix(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B);
    std::vector<std::vector<int>> sub_matrix(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B);
    std::vector<std::vector<int>> mul_matrix(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B);
    std::vector<std::vector<int>> add_num(std::vector<std::vector<int>>& matrix, int num);
    std::vector<std::vector<int>> mul_num(std::vector<std::vector<int>>& matrix, int num);
    std::vector<std::vector<int>> sub_num(std::vector<std::vector<int>>& matrix, int num);
    std::vector<std::vector<int>> div_num(std::vector<std::vector<int>>& matrix, int scalar);
    std::vector<std::vector<int>> rtd_num(std::vector<std::vector<int>>& matrix, int power);

    bool isSquare(std::vector<std::vector<int>> matrix);

    void clear();
    std::string result() const;
    Calculable* copy() const;
    Calculable* add(Calculable* other);
    Calculable* sub(Calculable* other);
    Calculable* mul(Calculable* other);
    Calculable* div(Calculable* other);
    Calculable* rtd(Calculable* other);
};

