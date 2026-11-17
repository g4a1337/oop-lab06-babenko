#include "complex.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

void Require(bool ok) { if (!ok) throw std::logic_error("Self-check failed"); }
Complex Make(double real, double imag) { Complex z; z.Init(real, imag); return z; }
void SelfCheck() {
    Complex a = Make(3, 4), b = Make(1, -2);
    Require((a + b).equ(Make(4, 2)) && (a - b).equ(Make(2, 6)));
    Require((a * b).equ(Make(11, -2)) && (a / b).equ(Make(-1, 2)));
    Require(a.equ(a) && !a.equ(b) && a.conj().equ(Make(3, -4)));
    bool rejected = false;
    try { a.div(Make(0, 0)); } catch (const std::domain_error&) { rejected = true; }
    Require(rejected);
    rejected = false;
    try { a.Init(std::numeric_limits<double>::infinity(), 1); }
    catch (const std::invalid_argument&) { rejected = true; }
    Require(rejected && a.equ(Make(3, 4)));
    std::cout << "Arithmetic and validation self-checks: PASS\n";
}
void CheckLifecycle() {
    int before = Complex::Live();
    {
        Complex zero; Complex value(2, 3); Complex copy(value);
        Require(Complex::Live() == before + 3 && copy.equ(value));
        std::cout << "Default constructor: "; zero.Display();
        std::cout << "Parameter constructor: "; value.Display();
        std::cout << "Copy constructor: "; copy.Display();
        std::cout << "Live objects in scope: " << Complex::Live() - before << '\n';
    }
    Require(Complex::Live() == before);
    std::cout << "Destructor self-check: PASS; 3 scope objects destroyed\n";
}
int main() {
    try {
        CheckLifecycle();
        SelfCheck();
        Complex a, b;
        std::cout << "Enter real and imaginary parts of a: "; a.Read();
        std::cout << "Enter real and imaginary parts of b: "; b.Read();
        std::cout << "a = "; a.Display(); std::cout << "b = "; b.Display();
        std::cout << "a + b = " << (a + b).toString() << '\n';
        std::cout << "a - b = " << (a - b).toString() << '\n';
        std::cout << "a * b = " << (a * b).toString() << '\n';
        std::cout << "a / b = " << (a / b).toString() << '\n';
        std::cout << "equ(a,b) = " << std::boolalpha << a.equ(b) << '\n';
        std::cout << "conj(a) = " << a.conj().toString() << '\n';
        try { a.div(Make(0, 0)); }
        catch (const std::domain_error& e) { std::cout << "Expected error: " << e.what() << '\n'; }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n'; return 1;
    }
}
