#ifndef FIELD_H_
#define FIELD_H_

#include <iostream>

#define APPLE 3
#define SNAKE_HEAD 1
#define SNAKE_BODY 2
#define EMPTY 0

using namespace std;

typedef struct Size {
    int sizeX;
    int sizeY;
} Size;

enum Direction {
    UP, LEFT, RIGHT, DOWN
};

typedef struct Position {
    int x;
    int y;
} Position;

class Field {
    public:
        Field();
        Field(Size size);
        string draw();
        void clearScreen();
        void echo(bool state); // linux only?
        int **getField();
        Size getSize();
        void generateApple();
        int getCellAtPosition(Position pos);
        void setCellAtPosition(Position pos, int newCell);
        void writeSnakePositions();
    private:
        int generateRandomNumber(int low, int high);
        Position generateRandomPosition();
        bool isOutOfBounds(Position pos);

        Size size;
        int **field;

        Position apple;
};
#endif