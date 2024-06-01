//
// Created by Owner on 6/1/2024.
//

#ifndef OOP_EXCEPTION_H
#define OOP_EXCEPTION_H

#include <stdexcept>

class InterestingError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};
class NameError : public InterestingError {
public:
    explicit NameError(char symbol) : InterestingError("alege alt simbol\n") {};
};
class FireError : public InterestingError {
public:
    explicit FireError() : InterestingError("deja ai tras!") {};
};


#endif //OOP_EXCEPTION_H
