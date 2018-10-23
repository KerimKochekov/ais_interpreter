#include "IntegerAbstractInterval.hpp"
#include "AbstractInterval.hpp"
#include "Bound.hpp"
#include "Infinity.hpp"
#include "UndefinedOperationException.hpp"

namespace domain {

IntegerAbstractInterval::~IntegerAbstractInterval() {
    delete[] a;
}

bool IntegerAbstractInterval::isFinite() {
    return !(getLowerBound().is_infinity() || getUpperBound().is_infinity());
}

IntegerAbstractInterval operator+(const IntegerAbstractInterval& i,
                                  const IntegerAbstractInterval& ii) {
    Bound l, u;

    l = i.getLowerBound() + ii.getLowerBound();
    u = i.getUpperBound() + ii.getUpperBound();

    return IntegerAbstractInterval(l, u);
}

IntegerAbstractInterval operator-(const IntegerAbstractInterval& i,
                                  const IntegerAbstractInterval& ii) {

    return IntegerAbstractInterval(i.getLowerBound() - ii.getUpperBound(),
                                   i.getUpperBound() - ii.getLowerBound());
}

IntegerAbstractInterval operator*(const IntegerAbstractInterval& i,
                                  const IntegerAbstractInterval& ii) {
    IntegerAbstractInterval iii(ii.getLowerBound(), ii.getUpperBound());
    Bound                   l, u, l1, u1, l2, u2;

    l1         = i.getLowerBound();
    u1         = i.getUpperBound();
    l2         = iii.getLowerBound();
    u2         = iii.getUpperBound();
    Bound* val = new Bound[4]{ l1 * l2, l1 * u2, l2 * u1, u1 * u2 };
    l          = val[0];
    u          = l;

    for (int j = 0; j < 4; j++) {
        if (val[j] < l)
            l = val[j];
        if (val[j] > u)
            u = val[j];
    }

    delete[] val;

    return IntegerAbstractInterval(l, u);
}

IntegerAbstractInterval operator/(const IntegerAbstractInterval& i,
                                  const IntegerAbstractInterval& ii) {
    IntegerAbstractInterval iii(ii.getLowerBound(), ii.getUpperBound());
    Bound                   l, u, l1, u1, l2, u2;

    l1         = i.getLowerBound();
    u1         = i.getUpperBound();
    l2         = iii.getLowerBound();
    u2         = iii.getUpperBound();
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

    return IntegerAbstractInterval(l, u);
}

bool operator==(const IntegerAbstractInterval& i,
                const IntegerAbstractInterval& ii) {
    return i.getUpperBound() == ii.getUpperBound() &&
           i.getLowerBound() == ii.getLowerBound();
}

IntegerAbstractInterval
IntegerAbstractInterval::lub(const IntegerAbstractInterval& i,
                             const IntegerAbstractInterval& ii) {
    Bound lLub, uLub;

    if (i.getLowerBound() < ii.getLowerBound())
        lLub = i.getLowerBound();
    else
        lLub = ii.getLowerBound();

    if (i.getUpperBound() < ii.getUpperBound())
        uLub = ii.getUpperBound();
    else
        uLub = i.getUpperBound();

    return IntegerAbstractInterval(lLub, uLub);
}

Bound IntegerAbstractInterval::width() {
    if (getUpperBound().is_infinity() || getLowerBound().is_infinity()) {
        return Bound(Infinity('+'));
    }
    return Bound(getUpperBound() - getLowerBound() + Bound(1));
}

IntegerAbstractInterval IntegerAbstractInterval::negate() {
    Bound u = getLowerBound().revertSign();
    Bound l = getUpperBound().revertSign();

    return IntegerAbstractInterval(l, u);
}

IntegerAbstractInterval
IntegerAbstractInterval::widening(const IntegerAbstractInterval& i) {
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

    return IntegerAbstractInterval(l, u);
}

IntegerAbstractInterval
IntegerAbstractInterval::narrowing(const IntegerAbstractInterval& i) {
    IntegerAbstractInterval res = IntegerAbstractInterval();
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

bool IntegerAbstractInterval::intersects(const AbstractInterval& i) {
    return !((i.getUpperBound() < getLowerBound()) ^
             !(i.getLowerBound() <= getUpperBound()));
}

bool IntegerAbstractInterval::isContainedIn(const AbstractInterval& i) {
    return getLowerBound() <= i.getLowerBound() &&
           !(getUpperBound() < i.getUpperBound());
}
} // namespace domain