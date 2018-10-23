#include "AbstractInterval.hpp"

domain::AbstractInterval::AbstractInterval(const domain::Bound& l,
                                           const domain::Bound& u) {
    lowerBound = l;
    upperBound = u;
}

domain::Bound domain::AbstractInterval::getLowerBound() const {
    return lowerBound;
}

void domain::AbstractInterval::setLowerBound(const domain::Bound& object) {
    lowerBound = object;
}

domain::Bound domain::AbstractInterval::getUpperBound() const {
    return upperBound;
}

void domain::AbstractInterval::setUpperBound(const domain::Bound& object) {
    upperBound = object;
}
