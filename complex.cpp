#include "complex.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

int Complex::live_ = 0;
Complex::Complex() { ++live_; }
Complex::Complex(double real, double imag) { Init(real, imag); ++live_; }
Complex::Complex(const Complex& other) : real_(other.real_), imag_(other.imag_) { ++live_; }
Complex::~Complex() noexcept { --live_; }
int Complex::Live() { return live_; }
void Complex::Init(double real, double imag) {
    if (!std::isfinite(real) || !std::isfinite(imag))
        throw std::invalid_argument("Components must be finite");
    real_ = real; imag_ = imag;
}
void Complex::Read() {
    double real, imag;
    if (!(std::cin >> real >> imag)) throw std::runtime_error("Invalid input");
    Init(real, imag);
}
void Complex::Display() const { std::cout << toString() << '\n'; }
std::string Complex::toString() const {
    std::ostringstream out;
    out << real_ << (imag_ < 0 ? " - " : " + ") << std::fabs(imag_) << "i";
    return out.str();
}
Complex Complex::FromWide(long double real, long double imag) {
    const long double limit = std::numeric_limits<double>::max();
    if (!std::isfinite(real) || !std::isfinite(imag) ||
        std::fabs(real) > limit || std::fabs(imag) > limit)
        throw std::overflow_error("Complex result overflow");
    return Complex(static_cast<double>(real), static_cast<double>(imag));
}
Complex Complex::add(const Complex& b) const {
    return FromWide((long double)real_ + b.real_, (long double)imag_ + b.imag_);
}
Complex Complex::sub(const Complex& b) const {
    return FromWide((long double)real_ - b.real_, (long double)imag_ - b.imag_);
}
Complex Complex::mul(const Complex& b) const {
    return FromWide((long double)real_ * b.real_ - (long double)imag_ * b.imag_,
                    (long double)real_ * b.imag_ + (long double)imag_ * b.real_);
}
Complex Complex::div(const Complex& b) const {
    if (b.real_ == 0 && b.imag_ == 0) throw std::domain_error("Division by zero complex");
    long double d = (long double)b.real_ * b.real_ + (long double)b.imag_ * b.imag_;
    return FromWide(((long double)real_ * b.real_ + (long double)imag_ * b.imag_) / d,
                    ((long double)imag_ * b.real_ - (long double)real_ * b.imag_) / d);
}
bool Complex::equ(const Complex& b) const { return real_ == b.real_ && imag_ == b.imag_; }
Complex Complex::conj() const { return FromWide(real_, -imag_); }
Complex Complex::operator+(const Complex& b) const { return add(b); }
Complex Complex::operator-(const Complex& b) const { return sub(b); }
Complex Complex::operator*(const Complex& b) const { return mul(b); }
Complex Complex::operator/(const Complex& b) const { return div(b); }
