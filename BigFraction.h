#include <BigInt.h>

//Реализация для несократимых дробей.
struct Fraction : public BigInt {
  // Числитель.
  BigInt numenator;
  // Знаменатель.
  BigInt denumenator;
  // Флаг простоты знаменателя.
  bool Simple = false;

public:
  Fraction() { numenator = BigInt(); denumenator = BigInt(); };
  Fraction(BigInt, BigInt);

  friend bool operator==(const BigInt&, const BigInt&);
  friend bool operator<(const BigInt&, const BigInt&);
  friend bool operator<=(const BigInt&, const BigInt&);

  friend const Fraction operator+(const Fraction&, const Fraction&);
  friend const Fraction operator-(const Fraction&, const Fraction&);
  friend const Fraction operator*(const Fraction&, const Fraction&);
  friend const Fraction operator/(const Fraction&, const Fraction&);

  void CutFraction(BigInt&);
  void PrintFraction();

private:
  BigInt const GCD(BigInt, BigInt);
  BigInt const GCDForTwoFractions(const Fraction&, const Fraction&);
  BigInt const GCDForOneFraction(const Fraction&);
  BigInt const LCMForTwoFractions(const Fraction&, const Fraction&);
};
