#include "../include/Bound.hpp"
#include "../include/Infinity.hpp"
#include "../include/UndefinedOperationException.hpp"

bool domain::Bound::is_infinity() const {
    return value_type == 0;
}

bool domain::Bound::is_integer() const {
    return value_type == 1;
}

bool domain::Bound::is_float() const {
    return value_type == 2;
}

domain::Bound::Bound() = default;

domain::Bound domain::Bound::operator+(domain::Bound b) {
    if (b.is_infinity()) {
        if (is_infinity())
            return Bound(i + b.i);
        else if (is_float())
            return Bound(b.i + float_value);
        else
            return Bound(b.i + int_value);
    } else if (b.is_float()) {

        if (is_infinity())
            return Bound(i + b.float_value);
        else if (is_float())
            return Bound(float_value + b.float_value);
        else

            return Bound(int_value + b.float_value);
    } else {
        if (is_infinity())
            return Bound(i + b.int_value);
        else if (is_float())
            return Bound(float_value + b.int_value);
        else
            return Bound(int_value + b.int_value);
    }
}

domain::Bound domain::Bound::operator-(domain::Bound b) {
    if (b.is_infinity()) {
        if (is_infinity())
            if (getInfinityValue().getSign() != b.getInfinityValue().getSign())
                return Bound(i);
            else
                throw exceptions::UndefinedOperationException();
        else if (is_float())
            return Bound(float_value - b.getInfinityValue());
        else
            return Bound(int_value - b.getInfinityValue());
    } else if (b.is_float()) {

        if (is_infinity())
            return Bound(i - b.float_value);
        else if (is_float())
            return Bound(float_value - b.float_value);
        else
            return Bound(int_value - b.float_value);
    } else {
        if (is_infinity())
            return Bound(i - b.int_value);
        else if (is_float())
            return Bound(float_value - b.int_value);
        else
            return Bound(int_value - b.int_value);
    }
}

domain::Bound domain::Bound::operator*(domain::Bound b) {
    if (b.is_infinity()) {
        if (is_infinity())
            return Bound(i * b.i);
        else if (is_float())
            return Bound(b.i * float_value);
        else
            return Bound(b.i * int_value);
    } else if (b.is_float()) {
        if (is_infinity())
            return Bound(i * b.float_value);
        else if (is_float())
            return Bound(float_value * b.float_value);
        else
            return Bound(int_value * b.float_value);
    } else {
        if (is_infinity())
            return Bound(i * b.int_value);
        else if (is_float())
            return Bound(float_value * b.int_value);
        else
            return Bound(int_value * b.int_value);
    }
}

domain::Bound domain::Bound::operator/(domain::Bound b) {
    if (b.is_infinity()) {
        if (is_infinity())
            throw exceptions::UndefinedOperationException();
        else if (is_float())
            return Bound(float_value / b.i);
        else
            return Bound(int_value / b.i);
    } else if (b.is_float()) {
        if (b.getFloatValue() == 0.0)
            throw exceptions::UndefinedOperationException();
        if (is_infinity())
            return Bound(i / b.float_value);
        else if (is_float())
            return Bound(float_value / b.float_value);
        else
            return Bound(int_value / b.float_value);
    } else {
        if (b.getIntValue() == 0)
            throw exceptions::UndefinedOperationException();
        if (is_infinity())
            return Bound(i / b.int_value);
        else if (is_float())
            return Bound(float_value / b.int_value);
        else
            return Bound(int_value / b.int_value);
    }
}

domain::Bound domain::Bound::revertSign() {
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

bool domain::Bound::operator<(domain::Bound b) {
    if (is_infinity()) {
        if (b.is_infinity())
            return i < b.i;
        else if (b.is_float())
            return i < b.float_value;
        else
            return i < b.int_value;
    } else if (is_float()) {
        if (b.is_infinity())
            return float_value < b.i;
        else if (b.is_integer())
            return float_value < b.int_value;
        else
            return float_value < b.float_value;
    } else {
        if (b.is_infinity())
            return int_value < b.i;
        else if (b.is_integer())
            return int_value < b.int_value;
        else
            return int_value < b.float_value;
    }
}

bool domain::Bound::operator<=(domain::Bound b) {
    if (is_infinity()) {
        if (b.is_infinity())
            return i <= b.i;
        else if (b.is_float())
            return i <= b.float_value;
        else
            return i <= b.int_value;
    } else if (is_float()) {
        if (b.is_infinity())
            return float_value <= b.i;
        else if (b.is_integer())
            return float_value <= b.int_value;
        else
            return float_value <= b.float_value;
    } else {
        if (b.is_infinity())
            return int_value <= b.i;
        else if (b.is_integer())
            return int_value <= b.int_value;
        else
            return int_value <= b.float_value;
    }
}

bool domain::Bound::operator>(domain::Bound b) {
    if (is_infinity()) {
        if (b.is_infinity())
            return i > b.i;
        else if (b.is_float())
            return i > b.float_value;
        else
            return i > b.int_value;
    } else if (is_float()) {
        if (b.is_infinity())
            return float_value > b.i;
        else if (b.is_integer())
            return float_value > b.int_value;
        else
            return float_value > b.float_value;
    } else {
        if (b.is_infinity())
            return int_value > b.i;
        else if (b.is_integer())
            return int_value > b.int_value;
        else
            return int_value > b.float_value;
    }
}

bool domain::Bound::operator>=(domain::Bound b) {
    if (is_infinity()) {
        if (b.is_infinity())
            return i >= b.i;
        else if (b.is_float())
            return i >= b.float_value;
        else
            return i >= b.int_value;
    } else if (is_float()) {
        if (b.is_infinity())
            return float_value >= b.i;
        else if (b.is_integer())
            return float_value >= b.int_value;
        else
            return float_value >= b.float_value;
    } else {
        if (b.is_infinity())
            return int_value >= b.i;
        else if (b.is_integer())
            return int_value >= b.int_value;
        else
            return int_value >= b.float_value;
    }
}

domain::Bound::Bound(domain::Infinity infinity) {
    i          = infinity;
    value_type = 0;
}

domain::Bound::Bound(int value) {
    int_value  = value;
    value_type = 1;
}

domain::Bound::Bound(double value) {
    float_value = value;
    value_type  = 2;
}

template<typename L> L domain::Bound::getValue() {
    if (value_type == 0)
        return i;
    else if (value_type == 1)
        return int_value;
    else
        return float_value;
}

int domain::Bound::getIntValue() const {
    return int_value;
}

double domain::Bound::getFloatValue() const {
    return float_value;
}

domain::Infinity domain::Bound::getInfinityValue() const {
    return i;
}

bool domain::operator==(domain::Bound const& a, domain::Bound const& b) {
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

bool operator!=(const domain::Bound& a, const domain::Bound& b) {
    return !(a == b);
}
