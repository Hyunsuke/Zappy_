/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GameException
*/

#ifndef GAMEEXCEPTION_HPP_
#define GAMEEXCEPTION_HPP_

#include <exception>
#include <string>

class GameException : public std::exception {
public:
    GameException(const std::string& message);
    virtual const char* what() const noexcept override;

private:
    std::string message;
};

#endif // GAMEEXCEPTION_HPP_

