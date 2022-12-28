#include <BigInt.h>
#include <BigFraction.h>

int main()
{
  std::string s1("987654321000000000");
  std::string s2("123456789000000000");
  BigInt x1(s1);
  BigInt x2(s2);

  std::cout << "Examples:" << '\n' << '\n';
  std::cout << "BigInt:" << '\n';
  BigInt x4 = x1 + x2;
  x1.Print();
  std::cout << " + ";
  x2.Print();
  std::cout << " = ";
  x4.Print();
  std::cout << '\n';

  BigInt x5 = x1 - x2;
  x1.Print();
  std::cout << " - ";
  x2.Print();
  std::cout << " = ";
  x5.Print();
  std::cout << '\n';

  BigInt x6 = x1 * x2;
  x1.Print();
  std::cout << " * ";
  x2.Print();
  std::cout << " = ";
  x6.Print();
  std::cout << '\n';

  BigInt x7 = x1 / x2;
  x1.Print();
  std::cout << " / ";
  x2.Print();
  std::cout << " = ";
  x7.Print();
  std::cout << '\n';

  std::cout << '\n' << "Small Fractions:" << '\n';
  BigInt x12(2);
  BigInt x13(5);
  BigInt x14(4);
  BigInt x15(7);
  Fraction f7(x12, x13);
  Fraction f8(x14, x15);

  Fraction f9 = f7 + f8;
  f7.PrintFraction();
  std::cout << " + ";
  f8.PrintFraction();
  std::cout << " = ";
  f9.PrintFraction();
  std::cout << '\n';

  Fraction f10 = f7 - f8;
  f7.PrintFraction();
  std::cout << " - ";
  f8.PrintFraction();
  std::cout << " = ";
  f10.PrintFraction();
  std::cout << '\n';

  Fraction f11 = f7 * f8;
  f7.PrintFraction();
  std::cout << " * ";
  f8.PrintFraction();
  std::cout << " = ";
  f11.PrintFraction();
  std::cout << '\n';

  Fraction f12 = f7 / f8;
  f7.PrintFraction();
  std::cout << " / ";
  f8.PrintFraction();
  std::cout << " = ";
  f12.PrintFraction();
  std::cout << '\n';

  std::cout << '\n' << "BigFractions:" << '\n';
  BigInt x8(20000001);
  BigInt x9(50000001);
  BigInt x10(30000001);
  BigInt x11(90000001);
  Fraction f1(x8, x9);
  Fraction f2(x10, x11);

  Fraction f3 = f1 + f2;
  f1.PrintFraction();
  std::cout << " + ";
  f2.PrintFraction();
  std::cout << " = ";
  f3.PrintFraction();
  std::cout << '\n';

  Fraction f4 = f1 - f2;
  f1.PrintFraction();
  std::cout << " - ";
  f2.PrintFraction();
  std::cout << " = ";
  f4.PrintFraction();
  std::cout << '\n';

  Fraction f5 = f1 * f2;
  f1.PrintFraction();
  std::cout << " * ";
  f2.PrintFraction();
  std::cout << " = ";
  f5.PrintFraction();
  std::cout << '\n';

  Fraction f6 = f1 / f2;
  f1.PrintFraction();
  std::cout << " / ";
  f2.PrintFraction();
  std::cout << " = ";
  f6.PrintFraction();
  std::cout << '\n';

  return 0;
}
