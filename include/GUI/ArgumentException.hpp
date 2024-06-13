/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ArgumentException
*/

#ifndef ARGUMENTEXCEPTION_HPP_
#define ARGUMENTEXCEPTION_HPP_

#include <stdexcept>

class ArgumentException : public std::runtime_error {
public:
    explicit ArgumentException(const std::string& message) : std::runtime_error(message) {}
};

#endif /* !ARGUMENTEXCEPTION_HPP_ */
