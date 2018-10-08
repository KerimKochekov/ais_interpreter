/**
 * @authors Marco Colognese, Mattia Rossini
 * @version v1.0
 * @date September, 2018
 */

#ifndef INTERVAL_ABSTRACT_DOMAIN_INFINITY_HPP
#define INTERVAL_ABSTRACT_DOMAIN_INFINITY_HPP

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
    Infinity();

    /**
     * @brief Creates an infinite value starting from its sign. Possible
     * parameters are '+' or '-'.
     *
     * @param s the sign parameter
     */
    explicit Infinity(char s);

    /**
     * @brief Destructor for Infinity class.
     */
    ~Infinity();

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
    bool isPositive();

    /**
     * @brief Check if the infinity's sign is 0.
     *
     * @return 'true' if the sign is 0, 'false' otherwise
     */
    bool isNegative();

    /**
     * @brief Changes the sign of the infinity.
     */
    void negate();

    // Operator overloading

    // Arithmetic
    /**
     * @brief Performs the sum operation on two infinity.
     *
     * @param i the second infinity
     * @return the resulting infinity
     */
    Infinity operator+(Infinity& i);

    /**
     * @brief Performs the subtract operation on two infinity.
     *
     * @param i the second infinity
     * @return the resulting infinity
     */
    Infinity operator-(Infinity& i);

    /**
     * @brief Performs the multiply operation on two infinity.
     *
     * @param i the second infinity
     * @return the resulting infinity
     */
    Infinity operator*(Infinity& i);

    /**
     * @brief Performs the divide operation on two infinity.
     *
     * @param i the second infinity
     * @return the resulting infinity
     */
    Infinity operator/(Infinity& i);

    /**
     * @brief Performs the sum operation between this infinity and a
     * floating point parameter.
     *
     * @param f the floating point argument
     * @return the resulting infinity
     */
    Infinity operator+(double f);

    /**
     * @brief Performs the sum operation between this infinity and a integer
     * parameter.
     *
     * @param i the integer argument
     * @return the resulting infinity
     */
    Infinity operator+(int i);

    /**
     * @brief Performs the subtract operation between this infinity and a
     * floating point parameter.
     *
     * @param f the floating point argument
     * @return the resulting infinity
     */
    Infinity operator-(double f);

    /**
     * @brief Performs the subtract operation between this infinity and a
     * integer parameter.
     *
     * @param i the integer argument
     * @return the resulting infinity
     */
    Infinity operator-(int i);

    /**
     * @brief Performs the multiply operation between this infinity and a
     * floating point parameter.
     *
     * @param f the floating point argument
     * @return the resulting infinity
     */
    Infinity operator*(double f);

    /**
     * @brief Performs the multiply operation between this infinity and a
     * integer parameter.
     *
     * @param i the integer argument
     * @return the resulting infinity
     */
    Infinity operator*(int i);

    /**
     * @brief Performs the divide operation between this infinity and a
     * floating point parameter.
     *
     * @param f the floating point argument
     * @return the resulting infinity
     */
    Infinity operator/(double f);

    /**
     * @brief Performs the divide operation between this infinity and a
     * integer parameter.
     *
     * @param i the integer argument
     * @return the resulting infinity
     */
    Infinity operator/(int i);

    // Comparison

    /**
     * @brief Check if two infinities are different.
     *
     * @param i the infinity argument
     * @return 'true' if the infinities have different sign, 'false'
     * otherwise
     */
    bool operator!=(Infinity& i);

    /**
     * @brief Check if this infinity is less then the argument.
     *
     * @param i the infinity argument
     * @return 'true' if this infinity is less then the argument, 'false'
     * otherwise
     */
    bool operator<(Infinity& i);

    /**
     * @brief Check if this infinity is less or equal then the argument.
     *
     * @param i the infinity argument
     * @return 'true' if this infinity is less or equal then the argument,
     * 'false' otherwise
     */
    bool operator<=(Infinity& i);

    /**
     * @brief Check if this infinity is greater then the argument.
     *
     * @param i the infinity argument
     * @return 'true' if this infinity is greater then the argument,
     * 'false' otherwise
     */
    bool operator>(Infinity& i);

    /**
     * @brief Check if this infinity is greater or equal then the argument.
     *
     * @param i the infinity argument
     * @return 'true' if this infinity is greater or equal then the
     * argument, 'false' otherwise
     */
    bool operator>=(Infinity& i);

    /**
     * @brief Check if this infinity and the floating point argument are
     * equals.
     *
     * @param f the floating point argument
     * @return 'always 'false'
     */
    bool operator==(double f);

    /**
     * @brief Check if this infinity and the integer argument are equals.
     *
     * @param i the integer argument
     * @return 'always 'false'
     */
    bool operator==(int i);

    /**
     * @brief Check if this infinity and the floating point argument are
     * different.
     *
     * @param f the floating point argument
     * @return 'always 'true'
     */
    bool operator!=(double f);

    /**
     * @brief Check if this infinity and the integer argument are
     * different.
     *
     * @param i the integer argument
     * @return 'always 'true'
     */
    bool operator!=(int i);

    /**
     * @brief Check if this infinity is less then the floating point
     * argument.
     *
     * @param f the floating point argument
     * @return 'true' if the infinity has sign 0, 'false' otherwise
     */
    bool operator<(double f);

    /**
     * @brief Check if this infinity is less then the integer argument.
     *
     * @param i the integer argument
     * @return 'true' if the infinity has sign 0, 'false' otherwise
     */
    bool operator<(int i);

    /**
     * @brief Check if this infinity is less or equal then the floating
     * point argument.
     *
     * @param f the floating point argument
     * @return 'true' if the infinity has sign 0, 'false' otherwise
     */
    bool operator<=(double f);

    /**
     * @brief Check if this infinity is less or equal then the integer
     * argument.
     *
     * @param i the integer argument
     * @return 'true' if the infinity has sign 0, 'false' otherwise
     */
    bool operator<=(int i);

    /**
     * @brief Check if this infinity is greater then the floating point
     * argument.
     *
     * @param f the floating point argument
     * @return 'true' if the infinity has sign 1, 'false' otherwise
     */
    bool operator>(double f);

    /**
     * @brief Check if this infinity is greater then the integer argument.
     *
     * @param i the integer argument
     * @return 'true' if the infinity has sign 1, 'false' otherwise
     */
    bool operator>(int i);

    /**
     * @brief Check if this infinity is greater or equal then the floating
     * point argument.
     *
     * @param f the floating point argument
     * @return 'true' if the infinity has sign 1, 'false' otherwise
     */
    bool operator>=(double f);

    /**
     * @brief Check if this infinity is greater or equal then the integer
     * argument.
     *
     * @param i the integer argument
     * @return 'true' if the infinity has sign 1, 'false' otherwise
     */
    bool operator>=(int i);

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
};

/**
 * @brief Check if two infinities are equals.
 *
 * @param i the infinity argument
 * @return 'true' if the infinities have same sign, 'false' otherwise
 */
bool operator==(const Infinity& i, const Infinity& ii);

/**
 * @brief Performs the sum operation between integer and infinity parameters.
 *
 * @param i integer parameter
 * @param inf infinity parameter
 * @return +inf if the infinity instance is positive, -inf otherwise
 */
Infinity operator+(int i, Infinity inf);

/**
 * @brief Performs the sum operation between floating point and infinity
 * parameters.
 *
 * @param f double parameter
 * @param inf infinity parameter
 * @return +inf if the infinity instance is positive, -inf otherwise
 */
Infinity operator+(double f, Infinity inf);

/**
 * @brief Performs the subtract operation between integer and infinity
 * parameters.
 *
 * @param i integer parameter
 * @param inf infinity parameter
 * @return +inf if the infinity instance is negative, -inf otherwise
 */
Infinity operator-(int i, Infinity inf);

/**
 * @brief Performs the subtract operation between floating point and infinity
 * parameters.
 *
 * @param f double parameter
 * @param inf infinity parameter
 * @return +inf if the infinity instance is negative, -inf otherwise
 */
Infinity operator-(double f, Infinity inf);

/**
 * @brief Performs the multiply operation between int and infinity parameters.
 *
 * @param i integer parameter
 * @param inf infinity parameter
 * @return +inf if the parameters have the same sign, -inf otherwise
 */
Infinity operator*(int i, Infinity inf);

/**
 * @brief Performs the multiply operation between floating point and infinity
 * parameters.
 *
 * @param f double parameter
 * @param inf infinity parameter
 * @return +inf if the parameters have the same sign, -inf otherwise
 */
Infinity operator*(double f, Infinity inf);

/**
 * @brief Performs the divide operation between integer and infinity parameters.
 *
 * @param i integer parameter
 * @param inf infinity parameter
 * @return always 0
 */
int operator/(int i, Infinity inf);

/**
 * @brief Performs the divide operation between floating point and infinity
 * parameters.
 *
 * @param f floating point parameter
 * @param inf infinity parameter
 * @return always 0.0f
 */
double operator/(double f, Infinity inf);

/**
 * @brief Check if the integer parameter is less then infinity parameter.
 *
 * @param i integer parameter
 * @param inf infinity parameter
 * @return 'true' if infinity has sign 1, 'false' otherwise
 */
bool operator<(int i, Infinity inf);

/**
 * @brief Check if the floating point parameter is less then infinity parameter.
 *
 * @param f floating point parameter
 * @param inf infinity parameter
 * @return 'true' if infinity has sign 1, 'false' otherwise
 */
bool operator<(double f, Infinity i);

/**
 * @brief Check if the integer parameter is less or equal then infinity
 * parameter.
 *
 * @param i integer parameter
 * @param inf infinity parameter
 * @return 'true' if infinity has sign 1, 'false' otherwise
 */
bool operator<=(int i, Infinity inf);

/**
 * @brief Check if the floating point parameter is less or equal then infinity
 * parameter.
 *
 * @param f floating point parameter
 * @param inf infinity parameter
 * @return 'true' if infinity has sign 1, 'false' otherwise
 */
bool operator<=(double f, Infinity i);

/**
 * @brief Check if the integer parameter is greater then infinity parameter.
 *
 * @param i integer parameter
 * @param inf infinity parameter
 * @return 'true' if infinity has sign 0, 'false' otherwise
 */
bool operator>(int i, Infinity inf);

/**
 * @brief Check if the floating point parameter is greater then infinity
 * parameter.
 *
 * @param f floating point parameter
 * @param inf infinity parameter
 * @return 'true' if infinity has sign 0, 'false' otherwise
 */
bool operator>(double f, Infinity i);

/**
 * @brief Check if the integer parameter is greater or equal then infinity
 * parameter.
 *
 * @param i integer parameter
 * @param inf infinity parameter
 * @return 'true' if infinity has sign 0, 'false' otherwise
 */
bool operator>=(int i, Infinity inf);

/**
 * @brief Check if the floating point parameter is greater or equal then
 * infinity parameter.
 *
 * @param f floating point parameter
 * @param inf infinity parameter
 * @return 'true' if infinity has sign 0, 'false' otherwise
 */
bool operator>=(double f, Infinity i);

/**
 * @brief Check if the integer parameter is equal to infinity parameter.
 *
 * @param i integer parameter
 * @param inf infinity parameter
 * @return always 'false'
 */
bool operator==(int i, Infinity inf);

/**
 * @brief Check if the floating point parameter is equal to infinity parameter.
 *
 * @param f floating point parameter
 * @param inf infinity parameter
 * @return always 'false'
 */
bool operator==(double f, Infinity i);

/**
 * @brief Check if the integer parameter is not equal to infinity parameter.
 *
 * @param i integer parameter
 * @param inf infinity parameter
 * @return always 'true'
 */
bool operator!=(int i, Infinity inf);

/**
 * @brief Check if the floating point parameter is not equal to infinity
 * parameter.
 *
 * @param f floating point parameter
 * @param inf infinity parameter
 * @return always 'true'
 */
bool operator!=(double f, Infinity i);
} // namespace domain

#endif // INTERVAL_ABSTRACT_DOMAIN_INFINITY_HPP
