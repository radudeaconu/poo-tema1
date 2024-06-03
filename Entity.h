//
// Created by Owner on 6/1/2024.
//

#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H

#include <memory>

class Entity{
protected:
    int x, y;
    char symbol;

public:
    int getX() const;
    int getY() const;
    char getSymbol() const;
    virtual void initialize() = 0;
    //Entity();

    virtual std::shared_ptr<Entity> clone() const = 0;
    Entity(int _x=1, int _y=1, char _symbol='*');
    virtual ~Entity() ;
    explicit Entity(char _symbol);
protected:
    Entity(const Entity &other);
    Entity& operator=(const Entity& other) = default;
};
#endif //OOP_ENTITY_H
