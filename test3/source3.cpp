#include <iostream>
#include <numeric>

using namespace std;

int Nod(int A, int B) {
    while (A != B) {
        if (A > B) {
            A -= B;
        } else {
            B -= A;
        }
    }
    return A;
}

class Rational {
public:
    Rational() = default;

    Rational(int number) {
        numerator_ = number;
        denominator_ = 1;
    }

    Rational (int numerator, int denominator) {
        const int nod = Nod(abs(numerator), abs(denominator));
        numerator_ = numerator / nod;
        denominator_ = denominator / nod;
        if (denominator_ < 0) {
            numerator_ *= -1;
            denominator_ *= -1;
        }
    }

    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};