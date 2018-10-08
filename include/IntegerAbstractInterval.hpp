/**
 * @authors Marco Colognese, Mattia Rossini
 * @version v1.0
 * @date September, 2018
 */

#ifndef CPP_PROJECT_INTEGERABSTRACTINTERVAL_HPP
#define CPP_PROJECT_INTEGERABSTRACTINTERVAL_HPP

#pragma once
#include "AbstractInterval.hpp"
#include "UndefinedOperationException.hpp"
#include <iostream>

/**
 * @brief namespace containing the implemented domain
 */
namespace domain {
/**
 * @brief Class for generic integer interval. The bounds are integer numbers.
 *
 */
class IntegerAbstractInterval : public AbstractInterval {

public:
    /**
     * @brief Constructor for IntegerAbstractInterval class
     *
     * @param l the lower bound number
     * @param u the upper bound number
     */
    IntegerAbstractInterval(const Bound& l, const Bound& u) :
            AbstractInterval(l, u){};

    /**
     * @brief Default constructor for IntegerAbstractInterval class
     */
    IntegerAbstractInterval() = default;

    /**
     * @brief Destructor for IntegerAbstractInterval class
     */
    ~IntegerAbstractInterval() override = default;

    /**
     * @brief Controls if the current integer interval contains just finite
     * bounds.
     *
     * @return  'true' if the integer interval contains just finite bounds,
     * 'false' otherwise
     */
    bool isFinite() override;

    /**
     * @brief Performs the sum operation on two integer intervals.
     * The result of a sum [l1, u1] + [l2, u2] is the interval [l1 + l2, u1
     * + u2].
     *
     * @param i the integer interval to be added to the current interval
     * @return the resulting integer interval
     */
    IntegerAbstractInterval operator+(IntegerAbstractInterval& i);

    /**
     * @brief Performs the subtraction operation on two integer intervals.
     * The result of the subtraction [l1; u1] - [l2; u2] is the interval [l1
     * - u2; u1 - l2].
     *
     * @param i the integer interval to be subtracted from the current interval
     * @return the resulting interval
     */
    IntegerAbstractInterval operator-(IntegerAbstractInterval& i);

    /**
     * @brief Performs the multiplication operation on two integer intervals.
     * The result of a multiplication [l1, u1] * [l2, u2] is an interval [a,
     * b] such that: a = min{l1 * l2, l1 * u2, u1 * l2, u1 * u2} and b =
     * max{l1 * l2, l1 * u2, u1 * l2, u1 * u2}.
     *
     * @param i the integer interval to be multiplied per this
     * @return a new interval containing the multiplication result
     */
    IntegerAbstractInterval operator*(IntegerAbstractInterval& i);

    /**
     * @brief Performs the division on this integer interval.
     * The result of a division [l1, u1] / [l2, u2] is an interval
     * [a, b] such that:
     * a = min{l1 / l2, l1 / u2, u1 / l2, u1 / u2}
     * b = max{l1 / l2, l1 / u2, u1 / l2, u1 / u2}
     * If 0 is contained in the divider interval, the interval [-inf, +inf]
     * is returned.
     *
     * @param i the divider integer interval
     * @return the resulting interval
     */
    IntegerAbstractInterval operator/(IntegerAbstractInterval& i);

    /**
     * @brief Returns the integer interval resulting from the equality operator.
     * The resulting interval on is [1,1] if l1 = l2 = u1 = u2,
     * [0,0] if u1 < l2 or u2 < l1, [0,1] otherwise.
     *
     * @param i the integer interval compared to this interval
     * @return the resulting interval
     */
    bool operator==(IntegerAbstractInterval& i);

    /**
     * @brief Performs the least upper bound on two integer intervals.
     *
     * @param i the first integer interval
     * @param ii the second integer interval
     * @return the least upper bound of the given integer intervals
     */
    IntegerAbstractInterval lub(IntegerAbstractInterval& i,
                                IntegerAbstractInterval& ii);

    /**
     * @brief Computes the width of the current integer interval.
     * The width of the integer interval is computed subtracting the lower bound
     * from the upper bound.
     *
     * @return the width of this integer interval
     */
    Bound width() override;

    /**
     * @brief Performs the negation on this integer interval.
     * The negation on an interval [l, u] is a new interval [-u, -l].
     *
     * @return the negated integer interval.
     */
    IntegerAbstractInterval negate();

    /**
     * @brief Performs the widening operation on two integer intervals.
     * The result of a widening operation between two integer intervals [l1, u1]
     * and [l2, u2] is an interval [a, b] such that: a = -inf if l2 < l1, else
     * l1 b = +inf if u1 < u2, else u1
     *
     * @param i the second integer interval
     * @return the resulting integer interval
     */
    IntegerAbstractInterval widening(IntegerAbstractInterval& i);

    /**
     * @brief Performs the narrowing operator on two integer intervals.
     * Before performing the narrowing operation, an extra control to check
     * if intervals are ordered is needed. The narrowing operator is defined
     * only if this interval is ordered respect the parameter interval.
     *
     * The result of the narrowing operation between [l1, u1] and [l2, u2]
     * is a new integer interval [a, b] such that:
     * a = l2 if l1 = -inf, l1 otherwise
     * b = u2 if u1 = +inf, u1 otherwise
     *
     * @param i the second integer interval
     * @return the resulting integer interval
     */
    IntegerAbstractInterval narrowing(IntegerAbstractInterval& i);

    /**
     * @brief Controls if the integer interval intersects this integer interval.
     *
     * @param i  the second integer interval
     * @return 'true' if the first interval intersects this interval,
     * 'false' otherwise
     */
    bool intersects(AbstractInterval& i) override;

protected:
    /**
     * @brief Checks if the first integer interval is contained in the second
     * integer interval. An interval [l1, u1] is contained in [l2, u2] if l2 <=
     * l1 and u2 >= u1.
     *
     * @param i the integer interval
     * @return true if first interval is contained in the second interval,
     * false otherwise.
     */
    bool isContainedIn(AbstractInterval& i) override;
};

} // namespace domain

#endif // CPP_PROJECT_INTEGERABSTRACTINTERVAL_HPP
