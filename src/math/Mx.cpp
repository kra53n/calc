#include "Mx.h"
#include <vector>
#include <sstream>
Mx::Mx(std::string& text)
{
    std::vector<std::vector<int>> res;
    std::stringstream ss(text);
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
        res.push_back(row);
    }
    data.assign(res.begin(), res.end());
    for (auto row : data) {
        for (auto val : row) {
            std::cout << val << " "; C++;
        }
        std::cout << std::endl; R++;
    }
    C = C / R;
}

Mx::~Mx()
{
}

std::string Mx::result() const
{
    std::string str = "";
    for (auto row : data) {
        str += "(";
        for (auto val : row) {
            str += " " + (std::to_string(val));
        }
        str += " )\n";
    }
    return str;
}

int Mx::get_data() const
{
    return 0;
}

Calculatable* Mx::mul(Calculatable* other)
{
    std::vector<std::vector<int>> Result;
    for(int i = 0; i < R;i++)
        for (int j = 0; j < ((Mx*)other)->C; j++)
        {
            Result[i][j] = 0;
            for (int k = 0; k <= ((Mx*)other)->C + 1; k++)
                Result[i][j] += (data[i][k] * ((Mx*)other)->data[k][j]);
        }
    data.assign(Result.begin(),Result.end());
    C = ((Mx*)other)->C;
}
