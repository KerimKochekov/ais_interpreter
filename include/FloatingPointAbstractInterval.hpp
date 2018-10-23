/**
 * @authors Marco Colognese, Mattia Rossini
 * @version v1.0
 * @date October, 2018
 */

#pragma once
#include "AbstractInterval.hpp"
#include "Bound.hpp"

/**
 * @brief namespace containing the implemented domain
 */
namespace domain {
/**
 * @brief Class for generic floating point interval. The bounds are float
 * numbers.
 *
 */
class FloatingPointAbstractInterval : public AbstractInterval {

public:
    /**
     * @brief Constructor for FloatingPointAbstractInterval class
     *
     * @param l the lower bound number
     * @param u the upper bound number
     */
    FloatingPointAbstractInterval(const Bound& l, const Bound& u) :
            AbstractInterval(l, u){};

    /**
     * @brief Default constructor for FloatingPointAbstractInterval class
     */
    FloatingPointAbstractInterval() = default;

    /**
     * @brief Controls if the current float interval contains just finite
     * bounds.
     *
     * @return  'true' if the float interval contains just finite bounds,
     * 'false' otherwise
     */
    bool isFinite() override;

    /**
     * @brief Performs the sum operation on two float intervals.
     * The result of a sum [l1, u1] + [l2, u2] is the interval [l1 + l2, u1
     * + u2].
     *
     * @param i the first float interval
     * @param ii the second float interval
     * @return the resulting float interval
     */
    friend FloatingPointAbstractInterval
    operator+(const FloatingPointAbstractInterval& i,
              const FloatingPointAbstractInterval& ii);

    /**
     * @brief Performs the subtraction operation on two float intervals.
     * The result of the subtraction [l1; u1] - [l2; u2] is the interval [l1
     * - u2; u1 - l2].
     *
     * @param i the first float interval
     * @param ii the second float interval
     * @return the resulting interval
     */
    friend FloatingPointAbstractInterval
    operator-(const FloatingPointAbstractInterval& i,
              const FloatingPointAbstractInterval& ii);

    /**
     * @brief Performs the multiplication operation on two float intervals.
     * The result of a multiplication [l1, u1] * [l2, u2] is an interval [a,
     * b] such that: a = min{l1 * l2, l1 * u2, u1 * l2, u1 * u2} and b =
     * max{l1 * l2, l1 * u2, u1 * l2, u1 * u2}.
     *
     * @param i the first float interval
     * @param ii the second float interval
     * @return a new interval containing the multiplication result
     */
    friend FloatingPointAbstractInterval
    operator*(const FloatingPointAbstractInterval& i,
              const FloatingPointAbstractInterval& ii);

    /**
     * @brief Performs the division on this float interval.
     * The result of a division [l1, u1] / [l2, u2] is an interval
     * [a, b] such that:
     * a = min{l1 / l2, l1 / u2, u1 / l2, u1 / u2}
     * b = max{l1 / l2, l1 / u2, u1 / l2, u1 / u2}
     * If 0 is contained in the divider interval, the interval [-inf, +inf]
     * is returned.
     *
     * @param i the first float interval
     * @param ii the second float interval
     * @return the resulting interval
     */
    friend FloatingPointAbstractInterval
    operator/(const FloatingPointAbstractInterval& i,
              const FloatingPointAbstractInterval& ii);

    /**
     * @brief Returns the float interval resulting from the equality operator.
     * The resulting interval on is [1,1] if l1 = l2 = u1 = u2,
     * [0,0] if u1 < l2 or u2 < l1, [0,1] otherwise.
     *
     * @param i the first float interval
     * @param ii the second float interval
     * @return the resulting interval
     */
    friend bool operator==(const FloatingPointAbstractInterval& i,
                           const FloatingPointAbstractInterval& ii);

    /**
     * @brief Performs the least upper bound on two float intervals.
     *
     * @param i the first float interval
     * @param ii the second float interval
     * @return the least upper bound of the given float intervals
     */
    FloatingPointAbstractInterval lub(const FloatingPointAbstractInterval& i,
                                      const FloatingPointAbstractInterval& ii);

    /**
     * @brief Controls if the float interval intersects this float interval.
     *
     * @param i  the second float interval
     * @return 'true' if the first interval intersects this interval,
     * 'false' otherwise
     */
    bool intersects(const AbstractInterval& i) override;

    /**
     * @brief Computes the width of the current float interval.
     * The width of the float interval is computed subtracting the lower bound
     * from the upper bound.
     *
     * @return the width of this float interval
     */
    Bound width() override;

    /**
     * @brief Performs the negation on this float interval.
     * The negation on an interval [l, u] is a new interval [-u, -l].
     *
     * @return the negated float interval.
     */
    FloatingPointAbstractInterval negate();

    /**
     * @brief Performs the widening operation on two float intervals.
     * The result of a widening operation between two float intervals [l1, u1]
     * and [l2, u2] is an interval [a, b] such that: a = -inf if l2 < l1, else
     * l1 b = +inf if u1 < u2, else u1
     *
     * @param i the second float interval
     * @return the resulting float interval
     */
    FloatingPointAbstractInterval
    widening(const FloatingPointAbstractInterval& i);

    /**
     * @brief Performs the narrowing operator on two float intervals.
     * Before performing the narrowing operation, an extra control to check
     * if intervals are ordered is needed. The narrowing operator is defined
     * only if this interval is ordered respect the parameter interval.
     *
     * The result of the narrowing operation between [l1, u1] and [l2, u2]
     * is a new float interval [a, b] such that:
     * a = l2 if l1 = -inf, l1 otherwise
     * b = u2 if u1 = +inf, u1 otherwise
     *
     * @param i the second float interval
     * @return the resulting float interval
     */
    FloatingPointAbstractInterval
    narrowing(const FloatingPointAbstractInterval& i);

protected:
    /**
     * @brief Checks if the first float interval is contained in the second
     * float interval. An interval [l1, u1] is contained in [l2, u2] if l2 <= l1
     * and u2 >= u1.
     *
     * @param i the float interval
     * @return true if first interval is contained in the second interval,
     * false otherwise.
     */
    bool isContainedIn(const AbstractInterval& i) override;
};
} // namespace domain
