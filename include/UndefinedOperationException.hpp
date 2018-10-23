/**
 * @authors Marco Colognese, Mattia Rossini
 * @version v1.0
 * @date October, 2018
 */

#pragma once
#include <stdexcept>
#include <string>

/**
 * @brief namespace containing the definitions of the exceptions thrown in the
 * domain.
 */
namespace exceptions {
/**
 * @brief Class representing the undefined operation exception.
 * The exception is thrown when an operation is required but is not defined
 */
class UndefinedOperationException : public std::exception {
    const char* what() const noexcept override {
        return "building intervals from invalid values";
    }
};

} // namespace exceptions
