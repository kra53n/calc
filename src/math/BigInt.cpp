#include "BigInt.h"

BigInt::BigInt() 
{
    sign = 1;
}

BigInt::BigInt(string str)
{
    int i;
    for (i = str.size() - BASE; i >= BASE - 1; i -= BASE) {
    chunks.push_back(stoi(str.substr(i, BASE)));
    }

    //Дошли до начала строки, тут ищем знак и записываем последнюю чанку
    if (str[0] == '-') {
        sign = -1;
        if (i + BASE - 1 != 0) {
            chunks.push_back(stoi(str.substr(1, i + BASE - 1)));
        }
    }
    else {
        sign = 1;
        chunks.push_back(stoi(str.substr(0, i + BASE)));
    }
}

//Изменение размера массива с чанками
void BigInt::_resize(int newSize) {
    chunks.resize(newSize);
}
/*
* Функция нормализует большое число так, чтобы
* во всех чанках лежали BASE-разрядные числа
*/
void BigInt::_normalizationChunks() {
    int over = 0; //"Лишнее", которое будет кочевать в следующие чанки
    for (int i = 0; i < chunks.size() - 1; i++) {
        chunks[i] += over; //Прибавляем привесок от прошлых чанок
        over = my_div(chunks[i], BASE10); //Считаем перевес в текущей чанке
        chunks[i] = my_mod(chunks[i], BASE10); //Выравниваем чанку по базе
    }
    //Прибавляем перевес к последней чанке
    chunks[chunks.size() - 1] += over;
    //Обрабатываем перевес в последней чанке
    if (chunks[chunks.size() - 1] / BASE10) {
        over = my_div(chunks[chunks.size() - 1], BASE10);
        chunks[chunks.size() - 1] = my_mod(chunks[chunks.size() - 1], BASE10);
        chunks.push_back(over); //Создаем нову чанку с остатками
    }
    

    for (auto it = chunks.cbegin(); it != chunks.cend(); it++) {
        std::cout << *it << '_';
    }
}
//Функция нормализует большое число для печати так,
//чтобы все чанки были положительными, но sign = -1(если число отрицательное)
void BigInt::_normalizationSigns() {
    //Если в последней чанке отрицательное число
    if (chunks[chunks.size() - 1] < 0) {
        sign = -sign; //Меняем знак числа
        chunks[0] = BASE10 - chunks[0]; //Нормализуем первую чанку
        for (int i = 1; i < chunks.size(); i++) {
            chunks[i] = (BASE10 - chunks[i] - 1) % BASE10; //Нормализуем ост. чанки
        }
    }
    //Убираем из числа нулевые чанки
    int i = chunks.size() - 1;
    while (chunks[i] == 0) {
        if (i == 0) {
            sign = 1;
            return;
        }
        chunks.pop_back();
        i--;
    }
    return;
}
//Функция сложения
BigInt BigInt::_plus(BigInt& num) {
    BigInt res;
    res.sign = this->sign;
    for (int i = 0; i < this->chunks.size(); i++) {
        res.chunks.push_back(this->chunks[i] + num.chunks[i]);
    }
    return res;
}
//Функция вычитания
BigInt BigInt::_minus(BigInt& num) {
    BigInt res;
    res.sign = this->sign;
    for (int i = 0; i < this->chunks.size(); i++) {
        res.chunks.push_back(this->chunks[i] - num.chunks[i]);
    }
    return res;
}
//Оператор +, выполняет корректное сложение больших чисел
BigInt BigInt::operator + (BigInt& num) {
    BigInt res;
    //Приводим размер чанок обоих чисел
    if (this->chunks.size() > num.chunks.size()) {
        num._resize(chunks.size());
    }
    else {
        this->_resize(num.chunks.size());
    }
    //Выполняем операцию в зависимости от знаков чисел
    if (sign == num.sign) {
        res = this->_plus(num);
    }
    else {
        res = (*this)._minus(num);
    }
    //Нормализуем результат
    res._normalizationChunks();
    return res;
}

//Оператор -, выполняет корректное вычитание
BigInt BigInt::operator - (BigInt& num) {
    BigInt res;
    //Приводим размер чанок
    if (this->chunks.size() > num.chunks.size()) {
        num._resize(chunks.size());
    }
    else {
        (*this)._resize(num.chunks.size());
    }
    //В зависимости от знаков, выполняем нужное действие
    if (sign != num.sign) {
        res = (*this)._plus(num);
    }
    else {
        res = (*this)._minus(num);
    }
    //Нормализуем результат
    res._normalizationChunks();
    return res;
}
//Перегрузка оператора << для вывода в поток
ostream& operator << (ostream& os, BigInt& num) {
    num._normalizationSigns();
    if (num.sign == -1) {
        os << '-';
    }
    os << num.chunks[num.chunks.size() - 1];
    for (int i = num.chunks.size() - 2; i >= 0; i--) {
        os << setw(num.getBASE()) << setfill('0') << num.chunks[i];
    }
    return os;
}

int BigInt::getBASE() {
    return this->BASE;
}

int BigInt::my_div(int num, int diver) {
    if ((num < 0) && (num % diver))
        return num / diver - 1;
    else
        return num / diver;
}

int BigInt::my_mod(int num, int diver) {
    if ((num < 0) && (num % diver))
        return num % diver + diver;
    else
        return num % diver;
}

//Функция умножения больших чисел
BigInt BigInt::_simplemulti(BigInt& num) {
    BigInt result;

    result._resize(2 * this->chunks.size());
    result.sign = this->sign;

    for (int i = 0; i < this->chunks.size(); i++) {
        for (int j = 0; j < num.chunks.size(); j++) {
            result.chunks[i + j] += this->chunks[i] * num.chunks[j];
        }
    }

    result._normalizationChunks();
    return result;
}

//Функция приводит большие числа к нужному размеру
BigInt BigInt::_multi(BigInt& num) {
    auto maxSize = max(this->chunks.size(), num.chunks.size());

    int newSize = 1;
    while (newSize < maxSize) {
        newSize *= 2;
    }

    this->_resize(newSize);
    num._resize(newSize);

    return this->_simplemulti(num);
}

BigInt BigInt::operator * (BigInt num) {
    BigInt result;

    result = this->_multi(num);
    result._normalizationChunks();

    if (this->sign == num.sign) {
        result.sign = 1;
    }
    else {
        result.sign = -1;
    }

    return result;
}