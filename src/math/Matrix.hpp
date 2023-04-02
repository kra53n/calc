#pragma once

#include <vector>
#include <string>

#include "Num.hpp"
#include "Fraction.hpp"
#include "../errors.hpp"
#include "Calculatable.hpp"
#include "../syntax/Token.hpp"

class Matrix : public Calculatable
{
    int R, C;
    std::vector<std::vector<int>> data;
public:
    Matrix(std::string& text);
    ~Matrix();

    std::vector<std::vector<int>> parse_matrix(std::string s);
    std::vector<std::vector<int>> add_matrix(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B);
    std::vector<std::vector<int>> sub_matrix(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B);
    std::vector<std::vector<int>> mul_matrix(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B);
    std::vector<std::vector<int>> add_num(std::vector<std::vector<int>>& matrix, int num);
    std::vector<std::vector<int>> mul_num(std::vector<std::vector<int>>& matrix, int num);
    std::vector<std::vector<int>> sub_num(std::vector<std::vector<int>>& matrix, int num);
    std::vector<std::vector<int>> div_num(std::vector<std::vector<int>>& matrix, int scalar);
    std::string result() const;

    Calculatable* add(Calculatable* other);
    Calculatable* sub(Calculatable* other);
    Calculatable* mul(Calculatable* other);
    Calculatable* div(Calculatable* other);
    Calculatable* rtd(Calculatable* other);
};

