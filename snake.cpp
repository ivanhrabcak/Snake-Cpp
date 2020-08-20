#include "snake.h"
#include "field.h"
#include <iostream>

Snake::Snake() {
    this->field = Field();
    this->snakeHeadPosition = (Position) {.x = -1, .y = -1};
    this->currentDirection = UP;
}

Snake::Snake(Field field) {
    this->field = field; 
    snakeHeadPosition = (Position) {.x = field.getSize().sizeX / 2, .y = field.getSize().sizeY / 2};
    // std::cout << "starting at x " << snakeHeadPosition.x << " and y " << snakeHeadPosition.y << endl;
    bodyPositions.push_back((Position) {.x = snakeHeadPosition.x, .y = snakeHeadPosition.y});
    addLength(2);
    bodyPositions.pop_front();
    currentDirection = UP;
    writeToField();
    field.generateApple();
}

void Snake::addLength(int nOfCells) {
    for (int i = 0; i < nOfCells; i++) {
        int x = bodyPositions.back().x;
        int y = bodyPositions.back().y;
        if (currentDirection == UP) {
            x -= 1;            
        }
        else if (currentDirection == DOWN) {
            x += 1;
        }
        else if (currentDirection == LEFT) {
            y += 1;
        }
        else { // currentDirection == RIGHT
            y -= 1;
        }
        bodyPositions.push_back((Position) {.x = x, .y = y});
    }   
}

int Snake::move(Direction dir) {
    list<Position> newBodyPositions;
    list<Position>::iterator it;

    
    

    Position newSnakeHeadPosition = snakeHeadPosition;
    if (dir == UP) {
        newSnakeHeadPosition.x -= 1;
    }
    else if (dir == DOWN) {
        newSnakeHeadPosition.x += 1;
    }
    else if (dir == LEFT) {
        newSnakeHeadPosition.y -= 1;
    }
    else { // dir == RIGHT
        newSnakeHeadPosition.y += 1;
    }
    if (field.getCellAtPosition(newSnakeHeadPosition) ==  APPLE) {
        addLength(1);
        field.generateApple();
    }
    else if (field.getCellAtPosition(newSnakeHeadPosition) == SNAKE_BODY) {
        return DEAD;
    }
    if (newSnakeHeadPosition.x == -1 || newSnakeHeadPosition.y == -1) {
        return DEAD;
    }
    if (newSnakeHeadPosition.x == field.getSize().sizeX || newSnakeHeadPosition.y == field.getSize().sizeY) {
        return DEAD;
    }

    for (it = bodyPositions.begin(); it != bodyPositions.end(); ++it) {
        field.getField()[it->x][it->y] = EMPTY;
    }

    Position previousHead = snakeHeadPosition;
    for (it = bodyPositions.begin(); it != bodyPositions.end(); ++it) {
        newBodyPositions.push_back(previousHead);
        previousHead = (Position) {.x = it->x, .y = it->y};
    }

    bodyPositions = newBodyPositions;
    snakeHeadPosition = newSnakeHeadPosition;

    writeToField();
    return OK;
}

Direction Snake::getCurrentDirection() {
    return currentDirection;
}

void Snake::setCurrentDirection(Direction direction) {
    currentDirection = direction;
}

void Snake::writeToField() {
    field.setCellAtPosition(snakeHeadPosition, SNAKE_HEAD);
    list<Position>::iterator it;
    for (it = bodyPositions.begin(); it != bodyPositions.end(); ++it) {
        Position currentPosition = (Position) {.x = it->x, .y = it->y};
        field.setCellAtPosition(currentPosition, SNAKE_BODY);
    }
}