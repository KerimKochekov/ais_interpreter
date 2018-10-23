#include "Bound.hpp"
#include "Infinity.hpp"
#include "UndefinedOperationException.hpp"

namespace domain {

bool Bound::is_infinity() const {
    return value_type == 0;
}

bool Bound::is_integer() const {
    return value_type == 1;
}

bool Bound::is_float() const {
    return value_type == 2;
}

Bound operator+(const Bound& a, const Bound& b) {
    if (b.is_infinity()) {
        if (a.is_infinity())
            return Bound(b.getInfinityValue() + a.getInfinityValue());
        else if (a.is_float())
            return Bound(a.getFloatValue() + b.getInfinityValue());
        else
            return Bound(a.getIntValue() + b.getInfinityValue());
    } else if (b.is_float()) {

        if (a.is_infinity())
            return Bound(b.getFloatValue() + a.getInfinityValue());
        else if (a.is_float())
            return Bound(a.getFloatValue() + b.getFloatValue());
        else

            return Bound(a.getIntValue() + b.getFloatValue());
    } else {
        if (a.is_infinity())
            return Bound(b.getIntValue() + a.getInfinityValue());
        else if (a.is_float())
            return Bound(a.getFloatValue() + b.getIntValue());
        else
            return Bound(a.getIntValue() + b.getIntValue());
    }
}

Bound operator-(const Bound& a, const Bound& b) {
    if (b.is_infinity()) {
        if (a.is_infinity())
            if (a.getInfinityValue().getSign() !=
                b.getInfinityValue().getSign())
                return Bound(a.getInfinityValue());
            else
                throw exceptions::UndefinedOperationException();
        else if (a.is_float())
            return Bound(a.getFloatValue() - b.getInfinityValue());
        else
            return Bound(a.getIntValue() - b.getInfinityValue());
    } else if (b.is_float()) {

        if (a.is_infinity())
            return Bound(-b.getFloatValue() + a.getInfinityValue());
        else if (a.is_float())
            return Bound(a.getFloatValue() - b.getFloatValue());
        else
            return Bound(a.getIntValue() - b.getFloatValue());
    } else {
        if (a.is_infinity())
            return Bound(-b.getIntValue() + a.getInfinityValue());
        else if (a.is_float())
            return Bound(a.getFloatValue() - b.getIntValue());
        else
            return Bound(a.getIntValue() - b.getIntValue());
    }
}

Bound operator*(const Bound& a, const Bound& b) {
    if (b.is_infinity()) {
        if (a.is_infinity())
            return Bound(a.getInfinityValue() * b.getInfinityValue());
        else if (a.is_float())
            return Bound(a.getFloatValue() * b.getInfinityValue());
        else
            return Bound(a.getIntValue() * b.getInfinityValue());
    } else if (b.is_float()) {
        if (a.is_infinity())
            return Bound(b.getFloatValue() * a.getInfinityValue());
        else if (a.is_float())
            return Bound(a.getFloatValue() * b.getFloatValue());
        else
            return Bound(a.getIntValue() * b.getFloatValue());
    } else {
        if (a.is_infinity())
            return Bound(b.getIntValue() * a.getInfinityValue());
        else if (a.is_float())
            return Bound(a.getFloatValue() * b.getIntValue());
        else
            return Bound(a.getIntValue() * b.getIntValue());
    }
}

Bound operator/(Bound& a, Bound& b) {
    if (b.is_infinity()) {
        if (a.is_infinity())
            throw exceptions::UndefinedOperationException();
        else if (a.is_float())
            return Bound(a.getFloatValue() / b.getIntValue());
        else
            return Bound(0);
    } else if (b.is_float()) {
        if (b.getFloatValue() == 0.0)
            throw exceptions::UndefinedOperationException();
        if (a.is_infinity())
            return Bound(a.getInfinityValue() / b.getFloatValue());
        else if (a.is_float())
            return Bound(a.getFloatValue() / b.getFloatValue());
        else
            return Bound(a.getIntValue() / b.getFloatValue());
    } else {
        if (b.getIntValue() == 0)
            throw exceptions::UndefinedOperationException();
        if (a.is_infinity())
            return Bound(a.getInfinityValue() / b.getIntValue());
        else if (a.is_float())
            return Bound(a.getFloatValue() / b.getIntValue());
        else
            return Bound(a.getIntValue() / b.getIntValue());
    }
}

Bound Bound::revertSign() {
    if (is_infinity()) {
        Infinity inf = i;
        if (inf.isPositive())
            return Bound(Infinity('-'));
        else
            return Bound(Infinity('+'));
    } else if (is_integer()) {
        int val = int_value;
        return Bound(-val);
    }
    return Bound(-(float_value));
}

bool operator<(const Bound& a, const Bound& b) {
    if (a.is_infinity()) {
        if (b.is_infinity())
            return b.getInfinityValue() > a.getInfinityValue();
        else if (b.is_float())
            return b.getFloatValue() > a.getInfinityValue();
        else
            return b.getIntValue() > a.getInfinityValue();
    } else if (a.is_float()) {
        if (b.is_infinity())
            return a.getFloatValue() < b.getInfinityValue();
        else if (b.is_integer())
            return a.getFloatValue() < b.getIntValue();
        else
            return a.getFloatValue() < b.getFloatValue();
    } else {
        if (b.is_infinity())
            return a.getIntValue() < b.getInfinityValue();
        else if (b.is_integer())
            return a.getIntValue() < b.getIntValue();
        else
            return a.getIntValue() < b.getFloatValue();
    }
}

bool operator<=(const Bound& a, const Bound& b) {
    if (a.is_infinity()) {
        if (b.is_infinity())
            return b.getInfinityValue() >= a.getInfinityValue();
        else if (b.is_float())
            return b.getFloatValue() >= a.getInfinityValue();
        else
            return b.getIntValue() >= a.getInfinityValue();
    } else if (a.is_float()) {
        if (b.is_infinity())
            return a.getFloatValue() <= b.getInfinityValue();
        else if (b.is_integer())
            return a.getFloatValue() <= b.getIntValue();
        else
            return a.getFloatValue() <= b.getFloatValue();
    } else {
        if (b.is_infinity())
            return a.getIntValue() <= b.getInfinityValue();
        else if (b.is_integer())
            return a.getIntValue() <= b.getIntValue();
        else
            return a.getIntValue() <= b.getFloatValue();
    }
}

bool operator>(const Bound& a, const Bound& b) {
    if (a.is_infinity()) {
        if (b.is_infinity())
            return b.getInfinityValue() < a.getInfinityValue();
        else if (b.is_float())
            return b.getFloatValue() < a.getInfinityValue();
        else
            return b.getIntValue() < a.getInfinityValue();
    } else if (a.is_float()) {
        if (b.is_infinity())
            return a.getFloatValue() > b.getInfinityValue();
        else if (b.is_integer())
            return a.getFloatValue() > b.getIntValue();
        else
            return a.getFloatValue() > b.getFloatValue();
    } else {
        if (b.is_infinity())
            return a.getIntValue() > b.getInfinityValue();
        else if (b.is_integer())
            return a.getIntValue() > b.getIntValue();
        else
            return a.getIntValue() > b.getFloatValue();
    }
}

bool operator>=(const Bound& a, const Bound& b) {
    if (a.is_infinity()) {
        if (b.is_infinity())
            return b.getInfinityValue() <= a.getInfinityValue();
        else if (b.is_float())
            return b.getFloatValue() <= a.getInfinityValue();
        else
            return b.getIntValue() <= a.getInfinityValue();
    } else if (a.is_float()) {
        if (b.is_infinity())
            return a.getFloatValue() >= b.getInfinityValue();
        else if (b.is_integer())
            return a.getFloatValue() >= b.getIntValue();
        else
            return a.getFloatValue() >= b.getFloatValue();
    } else {
        if (b.is_infinity())
            return a.getIntValue() >= b.getIntValue();
        else if (b.is_integer())
            return a.getIntValue() >= b.getIntValue();
        else
            return a.getIntValue() >= b.getFloatValue();
    }
}

Bound::Bound(const Infinity& infinity) {
    i          = infinity;
    value_type = 0;
}

Bound::Bound(int value) {
    int_value  = value;
    value_type = 1;
}

Bound::Bound(double value) {
    float_value = value;
    value_type  = 2;
}

template<typename L> L Bound::getValue() {
    if (value_type == 0)
        return i;
    else if (value_type == 1)
        return int_value;
    else
        return float_value;
}

int Bound::getIntValue() const {
    return int_value;
}

double Bound::getFloatValue() const {
    return float_value;
}

Infinity Bound::getInfinityValue() const {
    return i;
}

bool operator==(const Bound& a, const Bound& b) {
    if (a.value_type == 1 && b.value_type == 2)
        return a.getIntValue() == b.getFloatValue();
    else if (a.value_type == 2 && b.value_type == 1)
        return a.getFloatValue() == b.getIntValue();
    else if (a.value_type == 0 && b.value_type == 0)
        return a.getInfinityValue() == b.getInfinityValue();
    else if (a.value_type == 1 && b.value_type == 1)
        return a.getIntValue() == b.getIntValue();
    else if (a.value_type == 2 && b.value_type == 2)
        return (float) a.getFloatValue() == (float) b.getFloatValue();
    else
        return false;
}

bool operator!=(const Bound& a, const Bound& b) {
    if (a.value_type == 1 && b.value_type == 2)
        return !(a.getIntValue() == b.getFloatValue());
    else if (a.value_type == 2 && b.value_type == 1)
        return !(a.getFloatValue() == b.getIntValue());
    else if (a.value_type == 0 && b.value_type == 0)
        return !(a.getInfinityValue() == b.getInfinityValue());
    else if (a.value_type == 1 && b.value_type == 1)
        return !(a.getIntValue() == b.getIntValue());
    else if (a.value_type == 2 && b.value_type == 2)
        return !((float) a.getFloatValue() == (float) b.getFloatValue());
    else
        return false;
}
} // namespace domain