#ifndef SNAKE_H_
#define SNAKE_H_

#include <list>
#include "field.h"

#define DEAD 1
#define OK 0

using namespace std;

class Snake {
    public:
        Snake();
        Snake(Field f);
        int move(Direction dir);
        Direction getCurrentDirection();
        void writeToField();
        void setCurrentDirection(Direction direction);
    private:
        void addLength(int nOfCells);
            
        Position snakeHeadPosition;
        list<Position> bodyPositions;
        Direction currentDirection;

        Field field;
};
#endif