#include <BigFraction.h>

Fraction::Fraction(BigInt left, BigInt right) {
  numenator = left;
  denumenator = right;
  bool Simple = denumenator.IsSimple();
}

// НОД для длинных чисел.
const BigInt GCD(BigInt x1, BigInt x2) {
  while (!(x1 == x2)) {
    if (x2 < x1) x1 -= x2;
    else x2 -= x1;
  }
  return x1;
}

// НОД для знаменателей двух длинных дробей.
const BigInt GCDForTwoFractions(const Fraction& x1, const Fraction& x2) {
  if (x1.Simple && x2.Simple) return BigInt(1);
  return GCD(x1.denumenator, x2.denumenator);
}

// НОД для знаменателя и числителя длинной дроби(для сокращения).
const BigInt GCDForOneFraction(const Fraction& x) {
  if (x.Simple) {
    return BigInt(1);
  }
  return GCD(x.numenator, x.denumenator);
}

// НОК для знаменателей длинных дробей.
const BigInt LCMForTwoFractions(const Fraction& x1, const Fraction& x2) {
  return x1.denumenator * x2.denumenator / GCDForTwoFractions(x1, x2);
}

// Сложение длинных дробей.
const Fraction operator+(const Fraction& left, const Fraction& right) {
  Fraction result;
  result.denumenator = LCMForTwoFractions(left, right);
  result.numenator = left.numenator * result.denumenator / left.denumenator + right.numenator * result.denumenator / right.denumenator;
  BigInt max_divisor = GCDForOneFraction(result);
  result.CutFraction(max_divisor);
  return result;
}

// Вычитание для длинных дробей.
const Fraction operator-(const Fraction& left, const Fraction& right) {
  Fraction result;
  result.denumenator = LCMForTwoFractions(left, right);
  result.numenator = left.numenator * result.denumenator / left.denumenator - right.numenator * result.denumenator / right.denumenator;
  BigInt max_divisor = GCDForOneFraction(result);
  result.CutFraction(max_divisor);
  return result;
}

// Умножение длинных дробей.
const Fraction operator*(const Fraction& left, const Fraction& right) {
  Fraction result;
  result.numenator = left.numenator * right.numenator;
  result.denumenator = left.denumenator * right.denumenator;
  BigInt max_divisor = GCDForOneFraction(result);
  result.CutFraction(max_divisor);
  return result;
}

// Деление длинных дробей.
const Fraction operator/(const Fraction& left, const Fraction& right) {
  Fraction result;
  result.numenator = left.numenator * right.denumenator;
  result.denumenator = left.denumenator * right.numenator;
  BigInt max_divisor = GCDForOneFraction(result);
  result.CutFraction(max_divisor);
  return result;
}

// Сокращение дроби.
void Fraction::CutFraction(BigInt& div) {
  this->numenator /= div;
  this->denumenator /= div;
}

// Вывод дроби.
void Fraction::PrintFraction() {
  numenator.Print();
  std::cout << '/';
  denumenator.Print();
}
