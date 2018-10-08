/**
 * @authors Marco Colognese, Mattia Rossini
 * @version v1.0
 * @date September, 2018
 */

#ifndef INTERVAL_ABSTRACT_DOMAIN_BOUND_HPP
#define INTERVAL_ABSTRACT_DOMAIN_BOUND_HPP

#pragma once
#include "Infinity.hpp"

/**
 * @brief namespace containing the implemented domain
 */
namespace domain {
/**
 * @brief Class representing a bound for an interval.
 */
class Bound {
private:
    Infinity i;
    int      int_value;
    double   float_value;

public:
    int value_type; // 0 = inf, 1 = int, 2 = double

    /**
     * @brief Return the int value of the bound.
     *
     * @return the int value of the bound
     */
    int getIntValue() const;

    /**
     * @brief Return the float value of the bound.
     *
     * @return the float value of the bound
     */
    double getFloatValue() const;

    /**
     * @brief Return the infinity value of the bound.
     *
     * @return the infinity value of the bound
     */
    Infinity getInfinityValue() const;
    /**
     * @brief Create a bound starting from a infinite value.
     *
     * @param value value of the bound
     */
    explicit Bound(Infinity infinity);

    /**
     * @brief Create a bound starting from an integer value.
     *
     * @param value value of the bound
     */
    explicit Bound(int value);

    /**
     * @brief Create a bound starting from a double value.
     *
     * @param value value of the bound
     */
    explicit Bound(double value);

    /**
     * @brief Empty constructor for generic bound.
     */
    Bound();

    /**
     * @brief Return the value of the bound.
     *
     * @return the value of the bound
     */
    template<typename L> L getValue();

    /**
     * @brief Check if the bound's value is infinity.
     *
     * @return 'true' if value is infinity, 'false' otherwise
     */
    bool is_infinity() const;

    /**
     * @brief Check if the bound's value is an integer.
     *
     * @return 'true' if value is an integer, 'false' otherwise
     */
    bool is_integer() const;

    /**
     * @brief Check if the bound's value is a floating point.
     *
     * @return 'true' if value is a floating point, 'false' otherwise
     */
    bool is_float() const;

    /**
     * @brief Change the sign of the bound's value.
     *
     * @return the bound's value with changed sign
     */
    Bound revertSign();

    /**
     * @brief Performs the sum operation between this bound's value and the
     * parameter's value.
     *
     * @param b the bound argument
     * @return the resulting bound
     */
    Bound operator+(Bound b);

    /**
     * @brief Performs the subtract operation between this bound's value and
     * the parameter's value.
     *
     * @param b the bound argument
     * @return the resulting bound
     */
    Bound operator-(Bound b);

    /**
     * @brief Performs the multiply operation between this bound's value and
     * the parameter's value.
     *
     * @param b the bound argument
     * @return the resulting bound
     */
    Bound operator*(Bound b);

    /**
     * @brief Performs the divide operation between this bound's value and the
     * parameter's value.
     *
     * @param b the bound argument
     * @return the resulting bound
     */
    Bound operator/(Bound b);

    /**
     * @brief Check if this bound is less then the argument.
     *
     * @param b the bound argument
     * @return 'true' if this bound is less then the argument, 'false'
     * otherwise
     */
    bool operator<(Bound b);

    /**
     * @brief Check if this bound is less or equal then the argument.
     *
     * @param b the bound argument
     * @return 'true' if this bound is less  or equal then the argument,
     * 'false' otherwise
     */
    bool operator<=(Bound b);

    /**
     * @brief Check if this bound is greather then the argument.
     *
     * @param b the bound argument
     * @return 'true' if this bound is greather then the argument, 'false'
     * otherwise
     */
    bool operator>(Bound b);

    /**
     * @brief Check if this bound is greather or equal then the argument.
     *
     * @param b the bound argument
     * @return 'true' if this bound is greather or equal then the argument,
     * 'false' otherwise
     */
    bool operator>=(Bound b);
};

/**
 * @brief Check if this bound is equal then the argument.
 *
 * @param a the first bound argument
 * @param b the second bound argument
 * @return 'true' if this bound is equal then the argument, 'false'
 * otherwise
 */
bool operator==(const domain::Bound& a, const domain::Bound& b);

/**
 * @brief Check if this bound and the argument are different.
 *
 * @param b the bound argument
 * @return 'true' if the bounds are different, 'false'
 * otherwise
 */
bool operator!=(const Bound& a, const Bound& b);
} // namespace domain

#endif // INTERVAL_ABSTRACT_DOMAIN_BOUND_HPP
