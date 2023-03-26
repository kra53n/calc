#include <vector>
#include <sstream>

#include "Matrix.hpp"

Matrix::Matrix(std::string& text)
{
    data = parse_matrix(text);
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

int Matrix::get_data() const
{
    return 0;
}

Calculatable* Matrix::add(Calculatable* other)
{
    data = addMatrices(data, ((Matrix*)other)->data);
    return this;
}

Calculatable* Matrix::sub(Calculatable* other)
{
    data = subtractMatrices(data, ((Matrix*)other)->data);
    return this;
}

Calculatable* Matrix::mul(Calculatable* other)
{
    data = multiplyMatrices(data, ((Matrix*)other)->data);
    return this;
}

Calculatable* Matrix::div(Calculatable* other)
{
    data = divideMatrixByNumber(data, ((Matrix*)other)->data[0][0]);
    return this;
}

Calculatable* Matrix::rtd(Calculatable* other)
{
    return this;
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

std::vector<std::vector<int>> Matrix::multiplyMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B)
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

std::vector<std::vector<int>> Matrix::addMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B)
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

std::vector<std::vector<int>> Matrix::subtractMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B)
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

std::vector<std::vector<int>> Matrix::divideMatrixByNumber(const std::vector<std::vector<int>>& A, int num)
{
    // �������������� ���������
    std::vector<std::vector<int>> C(A.size(), std::vector<int>(A[0].size(), 0));
    // ����� ������� �� �����
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[0].size(); j++) {
            C[i][j] = A[i][j] / num;
        }
    }
    // ���������� ���������
    return C;
}
