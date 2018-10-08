#include "../include/AbstractInterval.hpp"

domain::AbstractInterval::AbstractInterval(domain::Bound l, domain::Bound u) {
    lowerBound = l;
    upperBound = u;
}

domain::AbstractInterval::~AbstractInterval() = default;

domain::Bound domain::AbstractInterval::getLowerBound() const {
    return lowerBound;
}

void domain::AbstractInterval::setLowerBound(domain::Bound object) {
    lowerBound = object;
}

domain::Bound domain::AbstractInterval::getUpperBound() const {
    return upperBound;
}

void domain::AbstractInterval::setUpperBound(domain::Bound object) {
    upperBound = object;
}

domain::AbstractInterval::AbstractInterval() = default;
