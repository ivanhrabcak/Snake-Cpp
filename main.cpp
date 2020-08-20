#include <iostream>
#include <ctime>

#include "field.h"
#include "time.h"
#include "snake.h"
#include "input.h"

using namespace std;

#define SIZEX 15
#define SIZEY 15
#define sizeofarray(x) sizeof(x) / sizeof(x[0]) // unsafe

int main() {
    Size size = (Size) {.sizeX = SIZEX, .sizeY = SIZEY};
    
    Field field(size);
    Snake snake(field);
    Input keyboard;
    bool dead;
    Direction *arrowKeysPressed;
    
    int start = clock();

    for (int i = 0; i < field.getSize().sizeX; i++) {
        for (int j = 0; j < field.getSize().sizeY; j++) {
            cout << field.getField()[i][j] << " ";
        }
        cout << endl;
    }

    while (!dead) {
        field.echo(false);
        snake.writeToField();
        int currentTime =  double(clock() - start) / CLOCKS_PER_SEC * 1000;
        // cout << currentTime << endl;
        if (currentTime >= 500) {
            dead = snake.move(snake.getCurrentDirection());
            field.clearScreen();
            cout << field.draw();
            start = clock();
        }
        arrowKeysPressed = keyboard.getArrowKeysPressed();
        if (!arrowKeysPressed == NULL) {
            snake.setCurrentDirection(arrowKeysPressed[0]);
        }
    }
    cout << field.draw();
    field.echo(true);
    
}