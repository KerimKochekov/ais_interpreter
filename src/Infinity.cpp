#include "../include/Infinity.hpp"
#include "../include/UndefinedOperationException.hpp"

domain::Infinity::Infinity() = default;

domain::Infinity::Infinity(char s) {
    if (s == '+')
        sign = 1;
    else if (s == '-')
        sign = 0;
}

domain::Infinity::~Infinity() = default;

int domain::Infinity::getSign() const {
    return sign;
}

void domain::Infinity::setSign(char s) {
    s == '+' ? sign = 1 : sign = 0;
}

bool domain::Infinity::isPositive() {
    return getSign() == 1;
}

bool domain::Infinity::isNegative() {
    return getSign() == 0;
}

void domain::Infinity::negate() {
    if (isPositive())
        sign = 0;
    else
        sign = 1;
}

domain::Infinity domain::Infinity::operator-(__attribute__((unused)) double f) {
    if (isPositive())
        return Infinity('+');
    else
        return Infinity('-');
}

domain::Infinity domain::Infinity::operator-(__attribute__((unused)) int i) {
    if (isPositive())
        return Infinity('+');
    else
        return Infinity('-');
}

domain::Infinity domain::Infinity::operator*(double f) {
    if (f == 0)
        throw exceptions::UndefinedOperationException();
    else {
        if (f > 0) {
            if (isPositive())
                return Infinity('+');
            else
                return (Infinity('-'));
        } else {
            if (isPositive())
                return Infinity('-');
            else
                return (Infinity('+'));
        }
    }
}

domain::Infinity domain::Infinity::operator*(int i) {
    if (i == 0)
        throw exceptions::UndefinedOperationException();
    else {
        if (i > 0) {
            if (isPositive())
                return Infinity('+');
            else
                return (Infinity('-'));
        } else {
            if (isPositive())
                return Infinity('-');
            else
                return (Infinity('+'));
        }
    }
}

domain::Infinity domain::Infinity::operator/(double f) {
    if (f == 0)
        throw exceptions::UndefinedOperationException();
    else {
        if (f > 0) {
            if (isPositive())
                return Infinity('+');
            else
                return (Infinity('-'));
        } else {
            if (isPositive())
                return Infinity('-');
            else
                return (Infinity('+'));
        }
    }
}

domain::Infinity domain::Infinity::operator/(int i) {
    if (i == 0)
        throw exceptions::UndefinedOperationException();
    else {
        if (i > 0) {
            if (isPositive())
                return Infinity('+');
            else
                return (Infinity('-'));
        } else {
            if (isPositive())
                return Infinity('-');
            else
                return (Infinity('+'));
        }
    }
}

domain::Infinity domain::Infinity::operator+(domain::Infinity& inf) {
    Infinity i;
    if (getSign() == 1 && inf.getSign() == 1)
        i.setSign('+');
    else if (getSign() == 0 && inf.getSign() == 0)
        i.setSign('-');
    else
        throw exceptions::UndefinedOperationException();
    return i;
}

domain::Infinity domain::Infinity::operator-(domain::Infinity& inf) {
    Infinity i;
    if (isNegative() && inf.isPositive())
        i.setSign('-');
    else if (isPositive() && inf.isNegative())
        i.setSign('+');
    else
        throw exceptions::UndefinedOperationException();
    return i;
}

domain::Infinity domain::Infinity::operator*(domain::Infinity& inf) {
    Infinity i;
    if ((isPositive() && inf.isPositive()) ||
        (isNegative() && inf.isNegative()))
        i.setSign('+');
    else
        i.setSign('-');
    return i;
}

domain::Infinity domain::Infinity::operator/(__attribute__((unused))
                                             domain::Infinity& inf) {
    throw exceptions::UndefinedOperationException();
}

bool domain::operator==(const domain::Infinity& i, const domain::Infinity& ii) {
    return i.getSign() == ii.getSign();
}

bool domain::Infinity::operator!=(domain::Infinity& inf) {
    return getSign() != inf.getSign();
}

bool domain::Infinity::operator<(domain::Infinity& inf) {
    return getSign() == 0 && inf.getSign() == 1;
}

bool domain::Infinity::operator<=(domain::Infinity& inf) {
    return getSign() == 0 || (getSign() == 1 && inf.getSign() == 1);
}

bool domain::Infinity::operator>(domain::Infinity& inf) {
    return getSign() == 1 && inf.getSign() == 0;
}

bool domain::Infinity::operator>=(domain::Infinity& inf) {
    return getSign() == 1 || (getSign() == 0 && inf.getSign() == 0);
}

domain::Infinity domain::Infinity::max(domain::Infinity* values) {
    Infinity i('-');
    for (unsigned int n = 0; n < (sizeof(values) / sizeof(values[0])); n++)
        if (i < values[n])
            i = values[n];
    return i;
}

domain::Infinity domain::Infinity::min(domain::Infinity* values) {
    Infinity i('+');
    for (unsigned int n = 0; n < (sizeof(values) / sizeof(values[0])); n++)
        if (i > values[n])
            i = values[n];
    return i;
}

domain::Infinity domain::Infinity::operator+(__attribute__((unused)) double f) {
    if (isPositive())
        return Infinity('+');
    else
        return Infinity('-');
}

domain::Infinity domain::Infinity::operator+(__attribute__((unused)) int i) {
    if (isPositive())
        return Infinity('+');
    else
        return Infinity('-');
}

bool domain::Infinity::operator==(__attribute__((unused)) double f) {
    return false;
}

bool domain::Infinity::operator==(__attribute__((unused)) int i) {
    return false;
}

bool domain::Infinity::operator!=(__attribute__((unused)) double f) {
    return true;
}

domain::Infinity domain::operator+(int i, domain::Infinity inf) {
    return inf + i;
}

domain::Infinity domain::operator+(double f, domain::Infinity inf) {
    return inf + f;
}

domain::Infinity domain::operator-(__attribute__((unused)) int i,
                                   domain::Infinity            inf) {
    if (inf.isNegative())
        return Infinity('+');
    else
        return Infinity('-');
}

domain::Infinity domain::operator-(__attribute__((unused)) double f,
                                   domain::Infinity               inf) {
    if (inf.isNegative())
        return Infinity('+');
    else
        return Infinity('-');
}

domain::Infinity domain::operator*(int i, domain::Infinity inf) {
    if (i == 0)
        throw exceptions::UndefinedOperationException();
    else if ((inf.isPositive() && i > 0) || (inf.isNegative() && i < 0))
        return Infinity('+');
    else
        return Infinity('-');
}

domain::Infinity domain::operator*(double f, domain::Infinity inf) {
    if (f == 0)
        throw exceptions::UndefinedOperationException();
    else if ((inf.isPositive() && f > 0) || (inf.isNegative() && f < 0))
        return Infinity('+');
    else
        return Infinity('-');
}

bool domain::Infinity::operator!=(__attribute__((unused)) int i) {
    return true;
}

bool domain::Infinity::operator<(__attribute__((unused)) double f) {
    return getSign() == 0;
}

bool domain::Infinity::operator<(__attribute__((unused)) int i) {
    return getSign() == 0;
}

bool domain::Infinity::operator<=(__attribute__((unused)) double f) {
    return getSign() == 0;
}

bool domain::Infinity::operator<=(__attribute__((unused)) int i) {
    return getSign() == 0;
}

bool domain::Infinity::operator>(__attribute__((unused)) double f) {
    return getSign() == 1;
}

bool domain::Infinity::operator>(__attribute__((unused)) int i) {
    return getSign() == 1;
}

bool domain::Infinity::operator>=(__attribute__((unused)) double f) {
    return getSign() == 1;
}

bool domain::Infinity::operator>=(__attribute__((unused)) int i) {
    return getSign() == 1;
}

bool domain::operator<(__attribute__((unused)) int i, domain::Infinity inf) {
    return !inf.isNegative();
}

bool domain::operator<(__attribute__((unused)) double f, domain::Infinity i) {
    return !i.isNegative();
}

bool domain::operator<=(int i, domain::Infinity inf) {
    return i < inf;
}

bool domain::operator<=(double f, domain::Infinity i) {
    return f < i;
}

bool domain::operator>(int i, domain::Infinity inf) {
    return !(i <= inf);
}

bool domain::operator>(double f, domain::Infinity i) {
    return !(f <= i);
}

bool domain::operator>=(int i, domain::Infinity inf) {
    return i > inf;
}

bool domain::operator>=(double f, domain::Infinity i) {
    return f > i;
}

bool domain::operator==(__attribute__((unused)) int              i,
                        __attribute__((unused)) domain::Infinity inf) {
    return false;
}

bool domain::operator==(__attribute__((unused)) double           f,
                        __attribute__((unused)) domain::Infinity i) {
    return false;
}

bool domain::operator!=(__attribute__((unused)) int              i,
                        __attribute__((unused)) domain::Infinity inf) {
    return true;
}

bool domain::operator!=(__attribute__((unused)) double           f,
                        __attribute__((unused)) domain::Infinity i) {
    return true;
}

int domain::operator/(__attribute__((unused)) int              i,
                      __attribute__((unused)) domain::Infinity inf) {
    return 0;
}

double domain::operator/(__attribute__((unused)) double           f,
                         __attribute__((unused)) domain::Infinity inf) {
    return 0.0f;
}
