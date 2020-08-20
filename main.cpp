#include <iostream>
#include <ctime>
#include <chrono>

#include "field.h"
#include "time.h"
#include "snake.h"
#include "input.h"

using namespace std;

#define SIZEX 30
#define SIZEY 30
#define sizeofarray(x) sizeof(x) / sizeof(x[0]) // unsafe

int main() {
    Size size = (Size) {.sizeX = SIZEX, .sizeY = SIZEY};
    
    Field field(size);
    Snake snake(field);
    Input keyboard;
    bool dead;
    Direction *arrowKeysPressed;
    
    // https://stackoverflow.com/questions/23615776/measure-time-milliseconds-or-microseconds-for-windows-c
    auto start = std::chrono::high_resolution_clock::now();

    while (!dead) {
        field.echo(false);
        snake.writeToField();
        int currentTime = (std::chrono::high_resolution_clock::now() - start) / std::chrono::milliseconds(1);
        // cout << currentTime << endl;
        if (currentTime >= 100) {
            dead = snake.move(snake.getCurrentDirection());
            field.clearScreen();
            cout << field.draw();
            start = std::chrono::high_resolution_clock::now();
        }
        arrowKeysPressed = keyboard.getArrowKeysPressed();
        if (!arrowKeysPressed == NULL) {
            snake.setCurrentDirection(arrowKeysPressed[0]);
        }
    }
    field.echo(true);
    
}