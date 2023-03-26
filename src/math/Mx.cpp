#include "Mx.h"
#include <vector>
#include <sstream>
Mx::Mx(std::string& text)
{
    std::vector<std::vector<int>> res = parse_matrix(text);
}

Mx::~Mx()
{
}

std::string Mx::result() const
{
    std::string ResultStr = "";
    for (int i = 0; i < Result.size(); i++) {
        for (int j = 0; j < Result[0].size(); j++) {
            ResultStr += std::to_string(Result[i][j]) + " ";
        }
        ResultStr += "\n";
    }
    return ResultStr;
}

int Mx::get_data() const
{
    return 0;
}

Calculatable* Mx::add(Calculatable* other)
{
    Result = addMatrices(data, ((Mx*)other)->data);
    return this;
}

Calculatable* Mx::sub(Calculatable* other)
{
    Result = subtractMatrices(data, ((Mx*)other)->data);
    return this;
}

Calculatable* Mx::mul(Calculatable* other)
{
    Result = multiplyMatrices(data, ((Mx*)other)->data);
    return this;
}

Calculatable* Mx::div(Calculatable* other)
{
    Result = divideMatrixByNumber(data, ((Mx*)other)->data[0][0]);
    return this;
}

std::vector<std::vector<int>> Mx::parse_matrix(std::string s)
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

std::vector<std::vector<int>> Mx::multiplyMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B)
{
    // Проверяем, что матрицы можно перемножить
    if (A[0].size() != B.size()) {
        std::cout << "Error: The matrices cannot be multiplied!" << std::endl;
        return {};
    }
    // Инициализируем результат
    std::vector<std::vector<int>> C(A.size(), std::vector<int>(B[0].size(), 0));
    // Перемножаем матрицы
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            for (int k = 0; k < B.size(); k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    // Возвращаем результат
    return C;
}

std::vector<std::vector<int>> Mx::addMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B)
{
    // Проверяем, что матрицы имеют одинаковый размер
    if (A.size() != B.size() || A[0].size() != B[0].size()) {
        std::cout << "Error: The matrices have different sizes!" << std::endl;
        return {};
    }
    // Инициализируем результат
    std::vector<std::vector<int>> C(A.size(), std::vector<int>(A[0].size(), 0));
    // Складываем матрицы
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[0].size(); j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    // Возвращаем результат
    return C;
}

std::vector<std::vector<int>> Mx::subtractMatrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B)
{
    // Проверяем, что матрицы имеют одинаковый размер
    if (A.size() != B.size() || A[0].size() != B[0].size()) {
        std::cout << "Error: The matrices have different sizes!" << std::endl;
        return {};
    }
    // Инициализируем результат
    std::vector<std::vector<int>> C(A.size(), std::vector<int>(A[0].size(), 0));
    // Вычитаем матрицы
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[0].size(); j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    // Возвращаем результат
    return C;
}

std::vector<std::vector<int>> Mx::divideMatrixByNumber(const std::vector<std::vector<int>>& A, int num)
{
    // Инициализируем результат
    std::vector<std::vector<int>> C(A.size(), std::vector<int>(A[0].size(), 0));
    // Делим матрицу на число
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[0].size(); j++) {
            C[i][j] = A[i][j] / num;
        }
    }
    // Возвращаем результат
    return C;
}
