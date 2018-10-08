#include "../include/IntegerAbstractInterval.hpp"
#include "../include/AbstractInterval.hpp"
#include "../include/Bound.hpp"
#include "../include/Infinity.hpp"
#include "../include/UndefinedOperationException.hpp"

bool domain::IntegerAbstractInterval::isFinite() {
    return !(getLowerBound().is_infinity() || getUpperBound().is_infinity());
}

domain::IntegerAbstractInterval domain::IntegerAbstractInterval::
                        operator+(domain::IntegerAbstractInterval& i) {
    Bound l, u;

    l = getLowerBound() + i.getLowerBound();
    u = getUpperBound() + i.getUpperBound();

    return IntegerAbstractInterval(l, u);
}

domain::IntegerAbstractInterval domain::IntegerAbstractInterval::
                        operator-(domain::IntegerAbstractInterval& i) {

    return IntegerAbstractInterval(getLowerBound() - i.getUpperBound(),
                                   getUpperBound() - i.getLowerBound());
}

domain::IntegerAbstractInterval domain::IntegerAbstractInterval::
                        operator*(domain::IntegerAbstractInterval& i) {
    domain::IntegerAbstractInterval ii(i.getLowerBound(), i.getUpperBound());
    domain::Bound                   l, u, l1, u1, l2, u2;

    l1 = getLowerBound();
    u1 = getUpperBound();
    l2 = ii.getLowerBound();
    u2 = ii.getUpperBound();
    domain::Bound* val = new domain::Bound[4]{ l1 * l2, l1 * u2, l2 * u1, u1 * u2 };
    l = val[0];
    u = l;

    for (int j = 0; j < 4; j++) {
        if (val[j] < l)
            l = val[j];
        if (val[j] > u)
            u = val[j];
    }

    delete[] val;

    return IntegerAbstractInterval(l, u);
}

domain::IntegerAbstractInterval domain::IntegerAbstractInterval::
                        operator/(domain::IntegerAbstractInterval& i) {
    IntegerAbstractInterval ii(i.getLowerBound(), i.getUpperBound());
    Bound                   l, u, l1, u1, l2, u2;

    l1 = getLowerBound();
    u1 = getUpperBound();
    l2 = ii.getLowerBound();
    u2 = ii.getUpperBound();
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

    return IntegerAbstractInterval(l, u);
}

bool domain::IntegerAbstractInterval::operator==(domain::IntegerAbstractInterval& i) {
    return getUpperBound() == i.getUpperBound() &&
            getLowerBound() == i.getLowerBound();
}

domain::IntegerAbstractInterval
domain::IntegerAbstractInterval::lub(IntegerAbstractInterval& i,
                             IntegerAbstractInterval& ii) {
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

domain::Bound domain::IntegerAbstractInterval::width() {
    if (getUpperBound().is_infinity() || getLowerBound().is_infinity()) {
        return Bound(Infinity('+'));
    }
    return Bound(getUpperBound() - getLowerBound() + Bound(1));
}

domain::IntegerAbstractInterval domain::IntegerAbstractInterval::negate() {
    Bound u = getLowerBound().revertSign();
    Bound l = getUpperBound().revertSign();

    return IntegerAbstractInterval(l, u);
}

domain::IntegerAbstractInterval
domain::IntegerAbstractInterval::widening(domain::IntegerAbstractInterval& i) {
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

domain::IntegerAbstractInterval
domain::IntegerAbstractInterval::narrowing(domain::IntegerAbstractInterval& i) {
    domain::IntegerAbstractInterval res = domain::IntegerAbstractInterval();
    if (getLowerBound() == domain::Bound(Infinity('-'))) {
        res.setLowerBound(i.getLowerBound());
    } else {
        res.setLowerBound(getLowerBound());
    }

    if (getUpperBound() == domain::Bound(Infinity('+'))) {
        res.setUpperBound(i.getUpperBound());
    } else {
        res.setUpperBound(getUpperBound());
    }

    return res;
}

bool domain::IntegerAbstractInterval::intersects(domain::AbstractInterval& i) {
    return !((i.getUpperBound() < getLowerBound()) ^
             !(i.getLowerBound() <= getUpperBound()));
}

bool domain::IntegerAbstractInterval::isContainedIn(domain::AbstractInterval& i) {
    return getLowerBound() <= i.getLowerBound() &&
           !(getUpperBound() < i.getUpperBound());
}