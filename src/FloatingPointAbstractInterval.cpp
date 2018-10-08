#include "../include/FloatingPointAbstractInterval.hpp"
#include "../include/AbstractInterval.hpp"
#include "../include/Bound.hpp"
#include "../include/Infinity.hpp"
#include "../include/UndefinedOperationException.hpp"

bool domain::FloatingPointAbstractInterval::isFinite() {
    return !(getLowerBound().is_infinity() || getUpperBound().is_infinity());
}

domain::FloatingPointAbstractInterval domain::FloatingPointAbstractInterval::
                                      operator+(FloatingPointAbstractInterval& i) {
    FloatingPointAbstractInterval ii(i.getLowerBound(), i.getUpperBound());
    Bound                         l, u;
    l = getLowerBound() + ii.getLowerBound();
    u = getUpperBound() + ii.getUpperBound();

    return FloatingPointAbstractInterval(l, u);
}

domain::FloatingPointAbstractInterval domain::FloatingPointAbstractInterval::
                                      operator-(FloatingPointAbstractInterval& i) {
    FloatingPointAbstractInterval ii(i.getLowerBound(), i.getUpperBound());
    Bound                         l, u;
    l = ii.getUpperBound().revertSign() + getLowerBound();
    u = ii.getLowerBound().revertSign() + getUpperBound();

    return FloatingPointAbstractInterval(l, u);
}

domain::FloatingPointAbstractInterval domain::FloatingPointAbstractInterval::
                                      operator*(FloatingPointAbstractInterval& i) {
    Bound l, u, l1, u1, l2, u2;

    l1 = getLowerBound();
    u1 = getUpperBound();
    l2 = i.getLowerBound();
    u2 = i.getUpperBound();
    Bound* val = new Bound[4]{ l1 * l2, l1 * u2, l2 * u1, u1 * u2 };
    l = val[0];
    u = l;

    for (int k = 0; k < 4; k++) {
        if (val[k] < l)
            l = val[k];
        if (val[k] > u)
            u = val[k];
    }
    delete[] val;

    return FloatingPointAbstractInterval(l, u);
}

domain::FloatingPointAbstractInterval domain::FloatingPointAbstractInterval::
                                      operator/(FloatingPointAbstractInterval& i) {
    Bound l, u, l1, u1, l2, u2;

    l1 = getLowerBound();
    u1 = getUpperBound();
    l2 = i.getLowerBound();
    u2 = i.getUpperBound();
    Bound* val = new Bound[4]{ l1 / l2, l1 / u2, l2 / u1, u1 / u2 };
    l = val[0];
    u = l;

    for (int j = 0; j < 4; j++) {
        if (val[j] < l)
            l = val[j];
        if (val[j] > u)
            u = val[j];
    }

    delete[] val;

    return FloatingPointAbstractInterval(l, u);
}

bool domain::FloatingPointAbstractInterval::
     operator==(FloatingPointAbstractInterval& i) {
    return getUpperBound() == i.getUpperBound() &&
           getLowerBound() == i.getLowerBound();
}

domain::FloatingPointAbstractInterval
domain::FloatingPointAbstractInterval::lub(FloatingPointAbstractInterval& i,
                                           FloatingPointAbstractInterval& ii) {
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

bool domain::FloatingPointAbstractInterval::intersects(AbstractInterval& i) {
    return !((i.getUpperBound() < getLowerBound()) ^
             !(i.getLowerBound() <= getUpperBound()));
}

domain::Bound domain::FloatingPointAbstractInterval::width() {
    if (getUpperBound().is_infinity() || getLowerBound().is_infinity()) {
        return Bound(Infinity('+'));
    }
    return Bound(getUpperBound() - getLowerBound() + Bound(1));
}

domain::FloatingPointAbstractInterval
domain::FloatingPointAbstractInterval::negate() {
    Bound l, u;

    u = getLowerBound().revertSign();
    l = getUpperBound().revertSign();

    return FloatingPointAbstractInterval(l, u);
}

domain::FloatingPointAbstractInterval
domain::FloatingPointAbstractInterval::widening(
    FloatingPointAbstractInterval& i) {
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

domain::FloatingPointAbstractInterval
domain::FloatingPointAbstractInterval::narrowing(
    FloatingPointAbstractInterval& i) {
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

bool domain::FloatingPointAbstractInterval::isContainedIn(AbstractInterval& i) {
    return getLowerBound() >= i.getLowerBound() &&
           getUpperBound() <= i.getUpperBound();
}