#include <iostream>
#include <windows.h>

//Initialize
bool snakeGame, mainMenu, GAME;
enum game { MAIN, START };
const int width = 25;
const int height = 25;
int menu = 1;
game mode;
//User variable
int x, y, speed = 1;
int tailX[100], tailY[100], tailLength;
//tail coordinates
int fposX, fposY, sposX, sposY;
//target variables
int targetX, targetY;
//game variables
int score;
enum directions {STOP = 0, UP, DOWN, LEFT, RIGHT};
directions dir;


void game_Over() {
    score = 0;
    tailLength = 0;
    mode = MAIN;
}


void main_Setup() {
    GAME = true;
    mode = MAIN;
}

void main_Menu() {
    system("cls");
    std::cout << "This Is the Main Menu." << std::endl;
    if (menu == 1) {
        std::cout << ">> Play the Game." << std::endl;
        std::cout << "Options" << std::endl;
        std::cout << "End Game" << std::endl;
    }
    else if (menu == 2) {
        std::cout << "Play the Game." << std::endl;
        std::cout << ">> Options" << std::endl;
        std::cout << "End Game" << std::endl;
    }
    else if (menu == 3) {
        std::cout << "Play the Game." << std::endl;
        std::cout << "Options" << std::endl;
        std::cout << ">> End Game" << std::endl;
    }

    if (GetAsyncKeyState(VK_RETURN)) {
        switch (menu) {
        case 1:
            mode = START;
            break;
        case 2:
            return;
            break;
        case 3:
            exit(0);
            break;
        }

    }
    else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {
        dir = STOP;
    }
    else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
        dir = STOP;
    }
    else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
        dir = STOP;
        menu++;
        Sleep(50);
    }
    else if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {
        dir = STOP;
        menu--;
        Sleep(50);
    }

    if (menu <= -1) {
        menu = 2;
    }
    else if (menu > 3) {
        menu = 1;
    }
}



void game_Setup() {
    dir = STOP;

    x = rand() % width;
    y = rand() % height;
    targetX = rand() % width;
    targetY = rand() % width;
    //For no collusion
    while (x == targetX && y == targetY) {
        x = rand() % width;
        y = rand() % height;
        targetX = rand() % width;
        targetY = rand() % height;
    }

    score = 0;
}

void game_Window() {
    system("cls");
    //Top border
    for (int i = 0; i < width; i++) {
        std::cout << "*";
    }
    //Body
    for (int i = 0; i < height; i++) {
        std::cout << std::endl;
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) {
                std::cout << "*";
            }
            else if (i == y && j == x) {
                std::cout << "S";
            }
            else if (i == targetY && j == targetX) {
                std::cout << "X";
            }
            else {
                bool tail = false;
                for (int k = 0; k < tailLength; k++) {
                    if (j == tailX[k] && i == tailY[k]) {
                        std::cout << "s";
                        tail = true;
                    }
                }
                if (!tail) {
                    std::cout << " ";
                }
            }
        }
    }
    std::cout << std::endl;
    //Bottom border
    for (int i = 0; i < width; i++) {
        std::cout << "*";
    }
    std::cout << std::endl;
    std::cout << "YOUR SCORE IS: " << score;
}

void game_Input() {
    if (mode == START) {
        if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) && dir != RIGHT) {
            dir = LEFT;
        }
        else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) && dir != LEFT) {
            dir = RIGHT;
        }
        else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) && dir != UP) {
            dir = DOWN;
        }
        else if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) && dir != DOWN) {
            dir = UP;
        }
        else if (GetAsyncKeyState(VK_RETURN)) {
            return;
        }
    }

}

void game_Program() {

    //tail
    fposX = tailX[0];
    fposY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < tailLength; i++) {
        sposX = tailX[i];
        sposY = tailY[i];
        tailX[i] = fposX;
        tailY[i] = fposY;
        fposX = sposX;
        fposY = sposY;
    }


    //movement of snake
    switch (dir) {
    case LEFT:
        x -= speed;
        break;
    case RIGHT:
        x += speed;
        break;
    case UP:
        y -= speed;
        break;
    case DOWN:
        y += speed;
        break;
    }

    //Snake hits border
    if (x <= 0 || x >= width - 1 || y < 0 || y > height - 1) {
        game_Over();
    }
    //Snake tail hit
    for (int i = 0; i < tailLength; i++) {
        if (x == tailX[i] && y == tailY[i]) {
            game_Over();
        }
    }
    //Snake eats target
    if (x == targetX && y == targetY) {
        targetX = rand() % width;
        targetY = rand() % width;
        score += (tailLength + 1) * 10;
        tailLength++;
    }
}

int main()
{
    main_Setup();
    while(GAME == true){
        game_Input();
        if(mode == MAIN){
            main_Menu();
        }
        else if (mode == START) {
            game_Setup();
            while (mode == START) {
                game_Window();
                game_Input();
                game_Program();
                Sleep(30);
            }
        }
    }
}
