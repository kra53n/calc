#include <vector>
#include <sstream>

#include "Matrix.hpp"

Matrix::Matrix(std::string& text)
{
    data = parse_matrix(text);
    token_name = Token::TokenName::Matrix;
}

Matrix::~Matrix()
{
}

std::string Matrix::result() const
{
    std::string ResultStr = "";
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[0].size(); j++) {
            ResultStr += std::to_string(data[i][j]) + " ";
        }
        ResultStr += "\n";
    }
    return ResultStr;
}

Calculatable* Matrix::add(Calculatable* other)
{
    switch (other->get_token_name()) {
    case Token::TokenName::Matrix: {
        data = add_matrix(data, ((Matrix*)other)->data);
    } break;
    case Token::TokenName::Num: {
        data = add_num(data, ((Num*)other)->get_data());
    } break;
    default: {
        throw IncompatibleTypesError();
    } break;
    }

    return this;
}

Calculatable* Matrix::sub(Calculatable* other)
{
    switch (other->get_token_name()) {
    case Token::TokenName::Matrix: {
        data = sub_matrix(data, ((Matrix*)other)->data);
    } break;
    case Token::TokenName::Num: {
        data = sub_num(data, ((Num*)other)->get_data());
    } break;
    default: {
        throw IncompatibleTypesError();
    } break;
    }
    
    return this;
}

Calculatable* Matrix::mul(Calculatable* other)
{
    switch (other->get_token_name()) {
    case Token::TokenName::Matrix: {
        data = mul_matrix(data, ((Matrix*)other)->data);
    } break;
    case Token::TokenName::Num: {
        data = mul_num(data, ((Num*)other)->get_data());
    } break;
    default: {
		throw IncompatibleTypesError();
    } break;
    }

    return this;
}

Calculatable* Matrix::div(Calculatable* other)
{
    switch (other->get_token_name()) {
    case Token::TokenName::Matrix: {
    } break;
    case Token::TokenName::Num: {
        data = div_num(data, ((Num*)other)->get_data());
    } break;
    default: {
		throw IncompatibleTypesError();
    } break;
    }
    
    return this;
}

Calculatable* Matrix::rtd(Calculatable* other)
{
    throw UnsupportedOperationError();
}

std::vector<std::vector<int>> Matrix::parse_matrix(std::string s)
{
    std::vector<std::vector<int>> result;
    std::stringstream ss(s);
    char c;

    while (ss >> c) {
        std::vector<int> row;
        int val;

        while (ss >> val) {
            row.push_back(val);

            if (ss.peek() == ')') {
                ss.ignore();
                break;
            }
        }

        result.push_back(row);
    }
    return result;
}

std::vector<std::vector<int>> Matrix::mul_matrix(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B)
{
    // ���������, ��� ������� ����� �����������
    if (A[0].size() != B.size()) {
        std::cout << "Error: The matrices cannot be multiplied!" << std::endl;
        return {};
    }
    // �������������� ���������
    std::vector<std::vector<int>> C(A.size(), std::vector<int>(B[0].size(), 0));
    // ����������� �������
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            for (int k = 0; k < B.size(); k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    // ���������� ���������
    return C;
}

std::vector<std::vector<int>> Matrix::add_matrix(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B)
{
    // ���������, ��� ������� ����� ���������� ������
    if (A.size() != B.size() || A[0].size() != B[0].size()) {
        std::cout << "Error: The matrices have different sizes!" << std::endl;
        return {};
    }
    // �������������� ���������
    std::vector<std::vector<int>> C(A.size(), std::vector<int>(A[0].size(), 0));
    // ���������� �������
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[0].size(); j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    // ���������� ���������
    return C;
}

std::vector<std::vector<int>> Matrix::sub_matrix(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B)
{
    // ���������, ��� ������� ����� ���������� ������
    if (A.size() != B.size() || A[0].size() != B[0].size()) {
        std::cout << "Error: The matrices have different sizes!" << std::endl;
        return {};
    }
    // �������������� ���������
    std::vector<std::vector<int>> C(A.size(), std::vector<int>(A[0].size(), 0));
    // �������� �������
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[0].size(); j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    // ���������� ���������
    return C;
}

std::vector<std::vector<int>> Matrix::mul_num(std::vector<std::vector<int>>& matrix, int num) {
    // Получаем размер матрицы
    int rows = matrix.size();
    int cols = matrix[0].size();
    // Создаем новую матрицу, заполненную нулями
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0.0));
    // Умножаем каждый элемент матрицы на скаляр
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrix[i][j] * num;
        }
    }
    // Возвращаем новую матрицу
    return result;
}

std::vector<std::vector<int>> Matrix::add_num(std::vector<std::vector<int>>& matrix, int num) {
    // Получаем размер матрицы
    int rows = matrix.size();
    int cols = matrix[0].size();
    // Создаем новую матрицу
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols));
    // Складываем каждый элемент матрицы с числом
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrix[i][j] + num;
        }
    }
    // Возвращаем новую матрицу
    return result;
}

std::vector<std::vector<int>> Matrix::sub_num(std::vector<std::vector<int>>& matrix, int num) {
    // Получаем размер матрицы
    int rows = matrix.size();
    int cols = matrix[0].size();
    // Создаем новую матрицу, заполненную нулями
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0.0));
    // Вычитаем из каждого элемента матрицы скаляр
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrix[i][j] - num;
        }
    }
    // Возвращаем новую матрицу
    return result;
}

std::vector<std::vector<int>> Matrix::div_num(std::vector<std::vector<int>>& matrix, int num) {
    // Получаем размер матрицы
    int rows = matrix.size();
    int cols = matrix[0].size();
    // Создаем новую матрицу, заполненную нулями
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0.0));
    // Делим каждый элемент матрицы на скаляр
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrix[i][j] / num;
        }
    }
    // Возвращаем новую матрицу
    return result;
}
