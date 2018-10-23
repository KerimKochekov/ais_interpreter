/**
 * @authors Marco Colognese, Mattia Rossini
 * @version v1.0
 * @date October, 2018
 */
#pragma once

/**
 * @brief namespace containing the implemented domain
 */
namespace domain {
/**
 * @brief Class representing an infinite value with sign.
 */
class Infinity {
private:
    /**
     * @brief Specified the sign of the Infinity instance,
     * if 1 the Infinity is positive, if 0 is negative.
     */
    int sign;

public:
    /**
     * @brief Empty constructor for generic infinity. The infinity has no
     * sign when it's instantiated, the sign is set when the interval
     * containing the infinite value is instantiated.
     */
    Infinity() = default;

    /**
     * @brief Creates an infinite value starting from its sign. Possible
     * parameters are '+' or '-'.
     *
     * @param s the sign parameter
     */
    explicit Infinity(char s);

    /**
     * @brief Gets the sign of the infinity.
     *
     * @return the sign of the infinity
     */
    int getSign() const;

    /**
     * @brief Sets the sign of the infinity.
     *
     * @param s the sign parameter
     */
    void setSign(char s);

    /**
     * @brief Check if the infinity's sign is 1.
     *
     * @return 'true' if the sign is 1, 'false' otherwise
     */
    bool isPositive() const;

    /**
     * @brief Check if the infinity's sign is 0.
     *
     * @return 'true' if the sign is 0, 'false' otherwise
     */
    bool isNegative() const;

    /**
     * @brief Changes the sign of the infinity.
     */
    void negate();

    // Operator overloading

    // Arithmetic

    /**
     * @brief Iterated through an Infinity array to find the maximum value.
     *
     * @param values the array of infinities to iterate through
     * @return the maximum value of the array
     */
    static Infinity max(Infinity* values);

    /**
     * @brief Iterated through an Infinity array to find the minimum value.
     *
     * @param values the array of infinities to iterate through
     * @return the minimum value of the array
     */
    static Infinity min(Infinity* values);

    /**
     * @brief Check if two infinities are equals.
     *
     * @param i the infinity argument
     * @return 'true' if the infinities have same sign, 'false' otherwise
     */
    friend bool operator==(const Infinity& i, const Infinity& ii);

    /**
     * @brief Performs the sum operation between integer and infinity
     * parameters.
     *
     * @param i integer parameter
     * @param inf infinity parameter
     * @return +inf if the infinity instance is positive, -inf otherwise
     */
    friend Infinity operator+(int i, const Infinity& inf);

    /**
     * @brief Performs the sum operation between two infinites parameters.
     *
     * @param i infinity parameter
     * @param ii infinity parameter
     * @return +inf if the two infinites instances are positive, -inf if the two
     * infinites instances are negative
     */
    friend Infinity operator+(const Infinity& i, const Infinity& ii);

    /**
     * @brief Performs the subtract operation between two infinites parameters.
     *
     * @param i infinity parameter
     * @param ii infinity parameter
     * @return +inf if the first infinity instance is positive and the second is
     * negative, -inf if the first infinity instance is negative and the second
     * is positive
     */
    friend Infinity operator-(const Infinity& i, const Infinity& ii);

    /**
     * @brief Performs the multipliy operation between two infinites parameters.
     *
     * @param i infinity parameter
     * @param ii infinity parameter
     * @return +inf if the infinites instances are positive or negative, -inf
     * otherwise
     */
    friend Infinity operator*(const Infinity& i, const Infinity& ii);

    /**
     * @brief Performs the divide operation between two infinites parameters.
     *
     * @param i infinity parameter
     * @param ii infinity parameter
     * @return throw the exception
     */
    friend Infinity operator/(const Infinity& i, const Infinity& ii);

    /**
     * @brief Performs the sum operation between floating point and infinity
     * parameters.
     *
     * @param f double parameter
     * @param inf infinity parameter
     * @return +inf if the infinity instance is positive, -inf otherwise
     */
    friend Infinity operator+(double f, const Infinity& inf);

    /**
     * @brief Performs the subtract operation between integer and infinity
     * parameters.
     *
     * @param i integer parameter
     * @param inf infinity parameter
     * @return +inf if the infinity instance is negative, -inf otherwise
     */
    friend Infinity operator-(int i, const Infinity& inf);

    /**
     * @brief Performs the subtract operation between floating point and
     * infinity parameters.
     *
     * @param f double parameter
     * @param inf infinity parameter
     * @return +inf if the infinity instance is negative, -inf otherwise
     */
    friend Infinity operator-(double f, const Infinity& inf);

    /**
     * @brief Performs the multiply operation between int and infinity
     * parameters.
     *
     * @param i integer parameter
     * @param inf infinity parameter
     * @return +inf if the parameters have the same sign, -inf otherwise
     */
    friend Infinity operator*(int i, const Infinity& inf);

    /**
     * @brief Performs the multiply operation between floating point and
     * infinity parameters.
     *
     * @param f double parameter
     * @param inf infinity parameter
     * @return +inf if the parameters have the same sign, -inf otherwise
     */
    friend Infinity operator*(double f, const Infinity& inf);

    /**
     * @brief Performs the divide operation between integer and infinity
     * parameters.
     *
     * @param i integer parameter
     * @param inf infinity parameter
     * @return always 0
     */
    friend int operator/(int i, const Infinity& inf);

    /**
     * @brief Performs the divide operation between floating point and infinity
     * parameters.
     *
     * @param f floating point parameter
     * @param inf infinity parameter
     * @return always 0.0f
     */
    friend double operator/(double f, const Infinity& inf);

    /**
     * @brief Performs the divide operation between infinity parameters and
     * integer.
     *
     * @param i infinity parameter
     * @param ii integer parameter
     * @return +inf if the parameters have the same sign, -inf otherwise
     */
    friend Infinity operator/(const Infinity& i, int ii);

    /**
     * @brief Performs the divide operation between infinity and floating point
     * parameters.
     *
     * @param i infinity parameter
     * @param f floating point parameter
     * @return +inf if the parameters have the same sign, -inf otherwise
     */
    friend Infinity operator/(const Infinity& i, double f);

    /**
     * @brief Check if the first infinity parameter is less then second infinity
     * parameter.
     *
     * @param i infinity parameter
     * @param ii infinity parameter
     * @return 'true' if first infinity has sign 0 and second infinity has sign
     * 1, 'false' otherwise
     */
    friend bool operator<(const Infinity& i, const Infinity& ii);

    /**
     * @brief Check if the integer parameter is less then infinity parameter.
     *
     * @param i integer parameter
     * @param inf infinity parameter
     * @return 'true' if infinity has sign 1, 'false' otherwise
     */
    friend bool operator<(int i, const Infinity& inf);

    /**
     * @brief Check if the floating point parameter is less then infinity
     * parameter.
     *
     * @param f floating point parameter
     * @param inf infinity parameter
     * @return 'true' if infinity has sign 1, 'false' otherwise
     */
    friend bool operator<(double f, const Infinity& i);

    /**
     * @brief Check if the first infinity parameter is less or equal then the
     * second infinity parameter.
     *
     * @param i infinity parameter
     * @param ii infinity parameter
     * @return 'false' if first infinity has sign 1 and second infinity has sign
     * 0, 'true' otherwise
     */
    friend bool operator<=(const Infinity& i, const Infinity& ii);

    /**
     * @brief Check if the integer parameter is less or equal then infinity
     * parameter.
     *
     * @param i integer parameter
     * @param inf infinity parameter
     * @return 'true' if infinity has sign 1, 'false' otherwise
     */
    friend bool operator<=(int i, const Infinity& inf);

    /**
     * @brief Check if the floating point parameter is less or equal then
     * infinity parameter.
     *
     * @param f floating point parameter
     * @param inf infinity parameter
     * @return 'true' if infinity has sign 1, 'false' otherwise
     */
    friend bool operator<=(double f, const Infinity& i);

    /**
     * @brief Check if the first infinity parameter is greater then the second
     * infinity parameter.
     *
     * @param i infinity parameter
     * @param ii infinity parameter
     * @return 'true' if first infinity has sign 1 and second infinity has sign
     * 0, 'false' otherwise
     */
    friend bool operator>(const Infinity& i, const Infinity& inf);

    /**
     * @brief Check if the integer parameter is greater then infinity parameter.
     *
     * @param i integer parameter
     * @param inf infinity parameter
     * @return 'true' if infinity has sign 0, 'false' otherwise
     */
    friend bool operator>(int i, const Infinity& inf);

    /**
     * @brief Check if the floating point parameter is greater then infinity
     * parameter.
     *
     * @param f floating point parameter
     * @param inf infinity parameter
     * @return 'true' if infinity has sign 0, 'false' otherwise
     */
    friend bool operator>(double f, const Infinity& i);

    /**
     * @brief Check if the first infinity parameter is greater or equal then the
     * second infinity parameter.
     *
     * @param i infinity parameter
     * @param ii infinity parameter
     * @return 'false' if first infinity has sign 0 and second infinty has sign
     * 1, 'true' otherwise
     */
    friend bool operator>=(const Infinity& i, const Infinity& inf);

    /**
     * @brief Check if the integer parameter is greater or equal then infinity
     * parameter.
     *
     * @param i integer parameter
     * @param inf infinity parameter
     * @return 'true' if infinity has sign 0, 'false' otherwise
     */
    friend bool operator>=(int i, const Infinity& inf);

    /**
     * @brief Check if the floating point parameter is greater or equal then
     * infinity parameter.
     *
     * @param f floating point parameter
     * @param inf infinity parameter
     * @return 'true' if infinity has sign 0, 'false' otherwise
     */
    friend bool operator>=(double f, const Infinity& i);

    /**
     * @brief Check if the integer parameter is equal to infinity parameter.
     *
     * @param i integer parameter
     * @param inf infinity parameter
     * @return always 'false'
     */
    friend bool operator==(int i, const Infinity& inf);

    /**
     * @brief Check if the floating point parameter is equal to infinity
     * parameter.
     *
     * @param f floating point parameter
     * @param inf infinity parameter
     * @return always 'false'
     */
    friend bool operator==(double f, const Infinity& i);

    /**
     * @brief Check if the integer parameter is not equal to infinity parameter.
     *
     * @param i integer parameter
     * @param inf infinity parameter
     * @return always 'true'
     */
    friend bool operator!=(int i, const Infinity& inf);

    /**
     * @brief Check if the floating point parameter is not equal to infinity
     * parameter.
     *
     * @param f floating point parameter
     * @param inf infinity parameter
     * @return always 'true'
     */
    friend bool operator!=(double f, const Infinity& i);
};

} // namespace domain

// namespace domain
