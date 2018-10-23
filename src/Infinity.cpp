#include "Infinity.hpp"
#include "UndefinedOperationException.hpp"

namespace domain {
Infinity::Infinity(char s) {
    if (s == '+')
        sign = 1;
    else if (s == '-')
        sign = 0;
}

int Infinity::getSign() const {
    return sign;
}

void Infinity::setSign(char s) {
    s == '+' ? sign = 1 : sign = 0;
}

bool Infinity::isPositive() const {
    return getSign() == 1;
}

bool Infinity::isNegative() const {
    return getSign() == 0;
}

void Infinity::negate() {
    if (isPositive())
        sign = 0;
    else
        sign = 1;
}

bool operator==(const Infinity& i, const Infinity& ii) {
    return i.getSign() == ii.getSign();
}

Infinity Infinity::max(Infinity* values) {
    Infinity i('-');
    for (unsigned int n = 0; n < (sizeof(values) / sizeof(values[0])); n++)
        if (values[n] > i)
            i = values[n];
    return i;
}

Infinity Infinity::min(Infinity* values) {
    Infinity i('+');
    for (unsigned int n = 0; n < (sizeof(values) / sizeof(values[0])); n++)
        if (i > values[n])
            i = values[n];
    return i;
}

Infinity operator+(int, const Infinity& inf) {
    return inf;
}

Infinity operator+(double, const Infinity& inf) {
    return inf;
}

Infinity operator+(const Infinity& i, const Infinity& ii) {
    if ((!i.isPositive() && ii.isPositive()) ||
        (i.isPositive() && !ii.isPositive()))
        throw exceptions::UndefinedOperationException();
    else
        return Infinity(i.getSign());
}

Infinity operator-(const Infinity& i, const Infinity& ii) {
    if ((i.isPositive() && ii.isPositive()) ||
        (!i.isPositive() && !ii.isPositive()))
        throw exceptions::UndefinedOperationException();
    else
        return Infinity(i.getSign());
}

Infinity operator*(const Infinity& i, const Infinity& ii) {
    if ((i.isPositive() && ii.isPositive()) ||
        (!i.isPositive() && !ii.isPositive()))
        return Infinity('+');
    else
        return Infinity('-');
}

Infinity operator/(const Infinity&, const Infinity&) {
    throw exceptions::UndefinedOperationException();
}

Infinity operator-(int, const Infinity& inf) {
    if (inf.isNegative())
        return Infinity('+');
    else
        return Infinity('-');
}

Infinity operator-(double, const Infinity& inf) {
    if (inf.isNegative())
        return Infinity('+');
    else
        return Infinity('-');
}

Infinity operator*(int i, const Infinity& inf) {
    if (i == 0)
        throw exceptions::UndefinedOperationException();
    else if ((inf.isPositive() && i > 0) || (inf.isNegative() && i < 0))
        return Infinity('+');
    else
        return Infinity('-');
}

Infinity operator*(double f, const Infinity& inf) {
    if (f == 0)
        throw exceptions::UndefinedOperationException();
    else if ((inf.isPositive() && f > 0) || (inf.isNegative() && f < 0))
        return Infinity('+');
    else
        return Infinity('-');
}

bool operator<(int, const Infinity& inf) {
    return !inf.isNegative();
}

bool operator<(double, const Infinity& i) {
    return !i.isNegative();
}

bool operator>(const Infinity& i, const Infinity& ii) {
    if (i.isPositive() && !ii.isPositive())
        return true;
    else
        return false;
}

bool operator>=(const Infinity& i, const Infinity& ii) {
    if (!i.isPositive() && ii.isPositive())
        return false;
    else
        return true;
}

bool operator<(const Infinity& i, const Infinity& ii) {
    if (!i.isPositive() && ii.isPositive())
        return true;
    else
        return false;
}

bool operator<=(const Infinity& i, const Infinity& ii) {
    if (i.isPositive() && !ii.isPositive())
        return false;
    else
        return true;
}

bool operator<=(int, const Infinity& inf) {
    return !inf.isNegative();
}

bool operator<=(double, const Infinity& i) {
    return !i.isNegative();
}

bool operator>(int, const Infinity& inf) {
    return inf.isNegative();
}

bool operator>(double, const Infinity& i) {
    return i.isNegative();
}

bool operator>=(int, const Infinity& inf) {
    return inf.isNegative();
}

bool operator>=(double, const Infinity& i) {
    return i.isNegative();
}

bool operator==(int, Infinity&) {
    return false;
}

bool operator==(double, Infinity&) {
    return false;
}

bool operator!=(int, Infinity&) {
    return true;
}

bool operator!=(double, Infinity&) {
    return true;
}

int operator/(const int, const Infinity&) {
    return 0;
}

double operator/(double, const Infinity&) {
    return 0.0f;
}

Infinity operator/(const Infinity& i, int ii) {
    if (ii > 0) {
        if (i.getSign() == 1)
            return Infinity('+');
        else
            return Infinity('-');
    } else if (ii < 0) {
        if (i.getSign() == '+')
            return Infinity('-');
        else
            return Infinity('+');
    } else
        throw exceptions::UndefinedOperationException();
}

Infinity operator/(const Infinity& i, double f) {
    if (f > 0)
        if (i.getSign() == 1)
            return Infinity('+');
        else
            return Infinity('-');
    else if (f < 0) {
        if (i.getSign() == '+')
            return Infinity('-');
        else
            return Infinity('+');
    } else
        throw exceptions::UndefinedOperationException();
}
} // namespace domain