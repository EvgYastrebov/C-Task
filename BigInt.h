#include <iostream>
#include <vector>
#include<string>
#include <stdexcept>

class BigInt {    
  public:
  // Основание системы.
  static const int base = 1000 * 1000 * 1000;
  std::vector<int> digits;
        
  // Конструкторы.
  BigInt() {digits.push_back(0);};
  BigInt(std::string);
  BigInt(unsigned int);

  friend bool operator==(const BigInt&, const BigInt&);
  friend bool operator==(const BigInt&, const long long&);
  friend bool operator<(const BigInt&, const BigInt&);
  friend bool operator<=(const BigInt&, const BigInt&);
       
  friend const BigInt operator+(BigInt, const BigInt&);
  friend const BigInt operator-(BigInt, const BigInt&);
  friend const BigInt operator*(const BigInt&, const BigInt&);
  friend const BigInt operator*(BigInt&, const long long&);
  friend const BigInt operator/(const BigInt&, const BigInt&);
  friend const BigInt operator%(const BigInt&, const BigInt&);

  const BigInt operator++();
  BigInt& operator=(const BigInt&);
  BigInt& operator+=(const BigInt&);
  BigInt& operator-=(const BigInt&);
  BigInt& operator*=(const BigInt&);
  BigInt& operator/=(const BigInt&);

  void RemoveLeadingZero();
  void ShiftRight();
  bool IsSimple();
  void Print();
};
