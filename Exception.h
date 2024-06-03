//
// Created by Owner on 6/1/2024.
//

#ifndef OOP_EXCEPTION_H
#define OOP_EXCEPTION_H

#include <stdexcept>

class GameError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};
class NameError : public GameError {
public:
    explicit NameError(char symbol) : GameError("alege alt simbol\n") {};
};
class FireError : public GameError {
public:
    explicit FireError() : GameError("deja ai tras!") {};
};


#endif //OOP_EXCEPTION_H
