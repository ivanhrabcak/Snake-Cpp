#include "field.h"
#include <ctime>
#include <random>
#include <iostream>

Field::Field() {
    this->size = (Size) {.sizeX = -1, .sizeY = -1};
    this->field = NULL;
    this->apple = (Position) {.x = -1, .y = -1};
}

Field::Field(Size size) {
    this->size = size;
    field = new int*[size.sizeX];
    for (int i = 0; i < size.sizeY; i++) {
        int *line = new int[size.sizeY]; 
        for (int j = 0; j < size.sizeY; j++) {
            line[j] = 0;
        }
        field[i] = line;
    }
}

void Field::echo(bool state) {
    #ifdef _WIN32
        return;
    #endif
    if (state) {
        system("stty echo");
    }
    else {
        system("stty -echo");
    }
}

void Field::clearScreen() { // ????
    #ifdef _WIN32
        system("cls");
    #endif
    #ifdef __unix__
        system("clear");
    #endif
}

string Field::draw() { // todo: make the Sneak class always write cells
    string output = "";
    for (int i = 0; i < size.sizeX; i++) {
        if (i == 0) {
            for (int k = 0; k < size.sizeY + 2; k++) {
                output += "#";
            }   
        }
        output += "\n#";
        for (int j = 0; j < size.sizeY; j++) {
            int currentCell = field[i][j];
            if (currentCell == APPLE) {
                output += "a";
            }
            else if (currentCell == EMPTY) {
                output += " ";
            }
            else if (currentCell == SNAKE_HEAD) {
                output += "@";
            }
            else if (currentCell == SNAKE_BODY) {
                output += "#";
            }
        }
        output += "#";
        if (i == size.sizeX - 1) {
            output += "\n";
            for (int k = 0; k < size.sizeY + 2; k++) {
                output += "#";
            }
            output += "\n";
        }
    }
    return output;
    // for (int i = 0; i < size.sizeX; i++) {
    //     for (int j = 0; j < size.sizeY; j++) {
    //         cout << field[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // return "";
}

Position Field::generateRandomPosition() {
    return (Position) {.x = generateRandomNumber(0, size.sizeX), 
                       .y = generateRandomNumber(0, size.sizeY)};
}

int Field::getCellAtPosition(Position pos) {
    if (isOutOfBounds(pos)) {
        return -1;
    }
    else {
        return field[pos.x][pos.y];
    }
}

void Field::setCellAtPosition(Position pos, int newCell) {
    if (!isOutOfBounds(pos)) {
        field[pos.x][pos.y] = newCell;
    }
}

bool Field::isOutOfBounds(Position pos) {
    return pos.x >= size.sizeX ||
           pos.y >= size.sizeY ||
           pos.x < 0 ||
           pos.y < 0;
}

int Field::generateRandomNumber(int low, int high) {
    srand((unsigned) time(0));
    return rand() % (high - low + 1) + low;
}

void Field::generateApple() {
    Position newApplePosition = generateRandomPosition();
    while (getCellAtPosition(newApplePosition) != EMPTY) {
        newApplePosition = generateRandomPosition();
    }
    apple = newApplePosition;
}

int **Field::getField() {
    return field;
}

Size Field::getSize() {
    return size;
}