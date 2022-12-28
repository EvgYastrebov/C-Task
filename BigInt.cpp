#include <BigInt.h>
#include <iostream>
#include <vector>
#include<string>
#include <stdexcept>

// Создание длинного числа из строки.
BigInt::BigInt(std::string& s) {
  for (int i = (int)s.length(); i > 0; i -= 9)
    if (i < 9) digits.push_back(atoi(s.substr(0, i).c_str()));
    else digits.push_back(atoi(s.substr(i - 9, 9).c_str()));
  this->RemoveLeadingZero();
}

// Unsigned int к BigInt.
BigInt::BigInt(unsigned int x) {
  this->digits.push_back(x % BigInt::base);
  x /= BigInt::base;
  if (x != 0) this->digits.push_back(x);
}

// Проверка на равенство длинных чисел.
bool operator==(const BigInt& left, const BigInt& right) {
  if (left.digits.size() == 1 && left.digits[0] == 0 && right.digits.size() == 1 && right.digits[0] == 0) return true;
  if (left.digits.size() != right.digits.size()) return false;
  for (long long i = 0; i < left.digits.size(); ++i)
    if (left.digits[i] != right.digits[i]) return false;
  return true;
}

// Проверка на равенство длинного с коротким.
bool operator==(const BigInt& left, const long long& right) {
  if (left.digits.size() == 1 && left.digits[0] == 0 && right == 0) return true;
  if (left.digits.size() != right) return false;
  for (long long i = 0; i < left.digits.size(); ++i)
    if (left.digits[i] != right) return false;
  return true;
}

// Сравнение длинных числел.
bool operator <(const BigInt& left, const BigInt& right) {
  if (left == right) return false;
  if (left.digits.size() != right.digits.size()) return left.digits.size() < right.digits.size();
  else {
    for (long long i = left.digits.size() - 1; i >= 0; --i)
      if (left.digits[i] != right.digits[i]) return left.digits[i] < right.digits[i];
    return false;
  }
}

// Меньше или равно для длинных числел.
bool operator<=(const BigInt& left, const BigInt& right) {
    return left < right || left == right;
}

// Присваивание для длинного числа.
BigInt& BigInt::operator=(const BigInt & x){
  digits = x.digits;
  return *this;
}

// Сложение длинных числел.
const BigInt operator+(BigInt left, const BigInt& right) {
  int carry = 0;
  for (long long i = 0; i < std::max(left.digits.size(), right.digits.size()) || carry; ++i) {
    if (i == left.digits.size()) left.digits.push_back(0);
    left.digits[i] += carry + (i < right.digits.size() ? right.digits[i] : 0);
    carry = left.digits[i] >= BigInt::base;
    if (carry) left.digits[i] -= BigInt::base;
  }
  return left;
}

// Сложение для текущего числа.
BigInt& BigInt::operator+=(const BigInt& right) {
  return *this = (*this + right);
}


// Префиксный инкремент.
const BigInt BigInt::operator++() {
  return *this += 1;
}

// Постфиксный инкремент.
const BigInt BigInt::operator++(int) {
  *this += 1;
  return *this - 1;
}

// Префиксный декремент.
const BigInt BigInt::operator--() {
  return *this -= 1;
}

// Постфиксный декремент.
const BigInt BigInt::operator--(int) {
  *this -= 1;
  return *this + 1;
}

// Вычитание для длинных чисел.
const BigInt operator-(BigInt left, const BigInt& right) {
    int carry = 0;
    for (long long i = 0; i < right.digits.size() || carry; ++i) {
        left.digits[i] -= carry + (i < right.digits.size() ? right.digits[i] : 0);
        carry = left.digits[i] < 0;
        if (carry) left.digits[i] += BigInt::base;
    }
    left.RemoveLeadingZero();
    return left;
}

// Вычитание для текущего числа.
BigInt& BigInt::operator-=(const BigInt& right) {
  return *this = (*this - right);
}


// Умножение длинного числа на короткое.
const BigInt operator*(BigInt& left, const long long& right) {
  int carry = 0;
  BigInt tmp = left;
  for (long long i = 0; i < left.digits.size() || carry; ++i) {
    if (i == left.digits.size()) left.digits.push_back(0);
    long long current = carry + left.digits[i] * 1LL * right;
    left.digits[i] = int(current % BigInt::base);
    carry = int(current / BigInt::base);
  }
  left.RemoveLeadingZero();
  BigInt result = left;
  left = tmp;
  return result;
}

// Умножение длинных числел.
const BigInt operator*(const BigInt& left, const BigInt& right) {
  BigInt result;
  result.digits.resize(left.digits.size() + right.digits.size());
  for (long long i = 0; i < left.digits.size(); ++i) {
    for (int j = 0, carry = 0; j < (int)right.digits.size() || carry; ++j) {
      long long current = result.digits[i + j] + left.digits[i] * 1LL * (j < (int)right.digits.size() ? right.digits[j] : 0) + carry;
      result.digits[i + j] = int(current % BigInt::base);
      carry = int(current / BigInt::base);
    }
  }
  result.RemoveLeadingZero();
  return result;
}

// Умножение для текущего числа.
BigInt& BigInt::operator*=(const BigInt& right) {
  return *this = (*this * right);
}

// Деление длинных чисел.
const BigInt operator/(const BigInt& left, const BigInt& right) {
  if (right == 0) throw std::runtime_error("Math error: Attempted to divide by Zero\n");
  
  BigInt result;
  if (left < right) {
    result = left;
    return result;
  }
  if (left == right) {
    result = BigInt("1");
    return result;
  }

  result.digits.resize(left.digits.size());
  BigInt current;
  BigInt b = right;
  for (long long i = left.digits.size() - 1; i >= 0; --i) {
    current.ShiftRight();
    current.digits[0] = left.digits[i];
    current.RemoveLeadingZero();
    int x = 0;
    int l = 0;
    int r = BigInt::base;
    while (l <= r) {
      int m = (l + r) / 2;
      BigInt t = b * m;
      if (t <= current) {
        x = m;
        l = m + 1;
      }
      else r = m - 1;
    }
    result.digits[i] = x;
    current -= b * x;
    
  }
  result.RemoveLeadingZero();
  return result;
}

// Деление для текущего числа.
BigInt& BigInt::operator/=(const BigInt& x) {
  return *this = (*this / x);
}

// Остаток для длинных чисел.
const BigInt operator%(const BigInt& left, const BigInt& right) {
    return left - (left / right) * right;
}

// Удаление ведущих нулей.
void BigInt::RemoveLeadingZero() {
  while (this->digits.size() > 1 && this->digits.back() == 0) {
    this->digits.pop_back();
  }
}

// Сдвиг разрядов вправо на 1.
void BigInt::ShiftRight() {
  if (this->digits.size() == 1 && this->digits[0] == 0) return;
  this->digits.push_back(this->digits[this->digits.size() - 1]);
  for (size_t i = this->digits.size() - 2; i > 0; --i) this->digits[i] = this->digits[i - 1];
  this->digits[0] = 0;
}

// Проверка на простоту.
bool BigInt::IsSimple() {
  
  BigInt del = BigInt(2);
  for (; (del * del <= *this); ++del) {
    if (!(*this % del == BigInt(0))) return false;
  }
  return true;
}

// Вывод длинного числа.
void BigInt::Print() {
  printf("%d", this->digits.empty() ? 0 : this->digits.back());
  for (int i = (int)this->digits.size() - 2; i >= 0; --i)
    printf("%09d", this->digits[i]);
}
