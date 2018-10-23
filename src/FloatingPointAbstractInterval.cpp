#include "FloatingPointAbstractInterval.hpp"
#include "AbstractInterval.hpp"
#include "Bound.hpp"
#include "Infinity.hpp"
#include "UndefinedOperationException.hpp"

namespace domain {

bool FloatingPointAbstractInterval::isFinite() {
    return !(getLowerBound().is_infinity() || getUpperBound().is_infinity());
}

FloatingPointAbstractInterval
operator+(const FloatingPointAbstractInterval& i,
          const FloatingPointAbstractInterval& ii) {
    FloatingPointAbstractInterval iii(ii.getLowerBound(), ii.getUpperBound());
    Bound                         l, u;
    l = i.getLowerBound() + iii.getLowerBound();
    u = i.getUpperBound() + iii.getUpperBound();

    return FloatingPointAbstractInterval(l, u);
}

FloatingPointAbstractInterval
operator-(const FloatingPointAbstractInterval& i,
          const FloatingPointAbstractInterval& ii) {
    FloatingPointAbstractInterval iii(ii.getLowerBound(), ii.getUpperBound());
    Bound                         l, u;
    l = iii.getUpperBound().revertSign() + i.getLowerBound();
    u = iii.getLowerBound().revertSign() + i.getUpperBound();

    return FloatingPointAbstractInterval(l, u);
}

FloatingPointAbstractInterval
operator*(const FloatingPointAbstractInterval& i,
          const FloatingPointAbstractInterval& ii) {
    Bound l, u, l1, u1, l2, u2;

    l1         = i.getLowerBound();
    u1         = i.getUpperBound();
    l2         = ii.getLowerBound();
    u2         = ii.getUpperBound();
    Bound* val = new Bound[4]{ l1 * l2, l1 * u2, l2 * u1, u1 * u2 };
    l          = val[0];
    u          = l;

    for (int k = 0; k < 4; k++) {
        if (val[k] < l)
            l = val[k];
        if (val[k] > u)
            u = val[k];
    }
    delete[] val;

    return FloatingPointAbstractInterval(l, u);
}

FloatingPointAbstractInterval
operator/(const FloatingPointAbstractInterval& i,
          const FloatingPointAbstractInterval& ii) {
    Bound l, u, l1, u1, l2, u2;

    l1         = i.getLowerBound();
    u1         = i.getUpperBound();
    l2         = ii.getLowerBound();
    u2         = ii.getUpperBound();
    Bound* val = new Bound[4]{ l1 / l2, l1 / u2, l2 / u1, u1 / u2 };
    l          = val[0];
    u          = l;

    for (int j = 0; j < 4; j++) {
        if (val[j] < l)
            l = val[j];
        if (val[j] > u)
            u = val[j];
    }

    delete[] val;

    return FloatingPointAbstractInterval(l, u);
}

bool operator==(const FloatingPointAbstractInterval& i,
                const FloatingPointAbstractInterval& ii) {
    return i.getUpperBound() == ii.getUpperBound() &&
           i.getLowerBound() == ii.getLowerBound();
}

FloatingPointAbstractInterval
FloatingPointAbstractInterval::lub(const FloatingPointAbstractInterval& i,
                                   const FloatingPointAbstractInterval& ii) {
    Bound lLub, uLub;

    if (i.getLowerBound() < ii.getLowerBound())
        lLub = i.getLowerBound();
    else
        lLub = ii.getLowerBound();

    if (i.getUpperBound() < ii.getUpperBound())
        uLub = ii.getUpperBound();
    else
        uLub = i.getUpperBound();

    return FloatingPointAbstractInterval(lLub, uLub);
}

bool FloatingPointAbstractInterval::intersects(const AbstractInterval& i) {
    return !((i.getUpperBound() < getLowerBound()) ^
             !(i.getLowerBound() <= getUpperBound()));
}

Bound FloatingPointAbstractInterval::width() {
    if (getUpperBound().is_infinity() || getLowerBound().is_infinity()) {
        return Bound(Infinity('+'));
    }
    return Bound(getUpperBound() - getLowerBound() + Bound(1));
}

FloatingPointAbstractInterval FloatingPointAbstractInterval::negate() {
    Bound l, u;

    u = getLowerBound().revertSign();
    l = getUpperBound().revertSign();

    return FloatingPointAbstractInterval(l, u);
}

FloatingPointAbstractInterval FloatingPointAbstractInterval::widening(
    const FloatingPointAbstractInterval& i) {
    Bound l, u;

    if (i.getLowerBound() < getLowerBound()) {
        Infinity inf('-');
        l = Bound(inf);
    } else
        l = getLowerBound();

    if (getUpperBound() < i.getUpperBound()) {
        Infinity inf('+');
        u = Bound(inf);
    } else
        u = getUpperBound();

    return FloatingPointAbstractInterval(l, u);
}

FloatingPointAbstractInterval FloatingPointAbstractInterval::narrowing(
    const FloatingPointAbstractInterval& i) {
    FloatingPointAbstractInterval res = FloatingPointAbstractInterval();
    if (getLowerBound() == Bound(Infinity('-'))) {
        res.setLowerBound(i.getLowerBound());
    } else {
        res.setLowerBound(getLowerBound());
    }

    if (getUpperBound() == Bound(Infinity('+'))) {
        res.setUpperBound(i.getUpperBound());
    } else {
        res.setUpperBound(getUpperBound());
    }

    return res;
}

bool FloatingPointAbstractInterval::isContainedIn(const AbstractInterval& i) {
    return getLowerBound() >= i.getLowerBound() &&
           getUpperBound() <= i.getUpperBound();
}
} // namespace domain