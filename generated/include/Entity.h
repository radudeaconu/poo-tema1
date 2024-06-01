//
// Created by Owner on 6/1/2024.
//

#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H
class Entity{
protected:
    int x, y;
    char symbol;

public:
    int getX() const;
    int getY() const;
    char getSymbol() const;
    virtual void initialize() = 0;
    Entity() {}

    Entity( int _x, int _y, char _symbol);

    explicit Entity(char _symbol);

    Entity(const Entity &other);
    virtual ~Entity() {

    }
};
#endif //OOP_ENTITY_H
