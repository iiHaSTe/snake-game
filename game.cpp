#include <iostream>
#include <ctime>
#include <conio.h>
using namespace std;
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

//---------Properitie---------//
const int tailSize = 1000;
int speed = 100;
int p = 1;
struct Map {
    int Width,
    Height,
    FruitX,
    FruitY,
    Time;
};
struct Snake {
    int HeadX,
    HeadY,
    Tail,
    TailX[tailSize],
    TailY[tailSize]; string Dir;
};
struct Player {
    int Score; bool Lose;
};

//---------Global Variable---------//
Map map;
Snake snake;
Player player;

//--------functions--------//
void setup(void);
void generateFruit(void);
void draw(void);
void input(void);
void move(void);
void sleepcp(int milliseconds);
void shiftRight(int arr[], int size);
void clear(void);
void setDifculty(char d);


int main(int argc, char *argv[]) {
    setup();
    while (!player.Lose) {
        if (snake.HeadX == 0 || snake.HeadX == map.Width)
        player.Lose = true;
        else if (snake.HeadY == 0 || snake.HeadY == map.Height)
        player.Lose = true;
        if (snake.HeadX == map.FruitX && snake.HeadY == map.FruitY) {
            player.Score += p;
            snake.Tail += p;
            generateFruit();
        }
        if (player.Lose) {
            cout << "Bye."
            << endl << "See you again";
        } else {
            draw();
            input();
            move();
            sleepcp(speed);
            map.Time++;
        }
    }
    return 0;
}
void setDifculty(char d) {
    if (d == 'e') {
        p = 15;
        speed = 250;
    }else if (d == 'n') {
        p = 1;
        speed = 150;
    }else if (d == 'h') {
        p = 1;
        speed = 50;
    }else {
        p = 1;
        speed = 170;
    }
}
void shiftRight(int arr[], int size) {
    int last = arr[size - 1];
    for (int i = size - 1; i > 0; i--)
        arr[i] = arr[i - 1];
    arr[0] = last;
}
void clear(void) {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
void sleepcp(int milliseconds) {
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif
}
void move(void) {
    shiftRight(snake.TailX, tailSize);
    shiftRight(snake.TailY, tailSize);
    snake.TailX[0] = snake.HeadX;
    snake.TailY[0] = snake.HeadY;

    string dir = snake.Dir;
    if (dir == "Top") snake.HeadY--;
    else if (dir == "Down") snake.HeadY++;
    else if (dir == "Left") snake.HeadX--;
    else if (dir == "Right") snake.HeadX++;
    else return;
}
void input(void) {
    if (_kbhit()) {
        char c = _getch();
        switch (c) {
            case 'w':
            snake.Dir = "Top";
            break;
            case 's':
            snake.Dir = "Down";
            break;
            case 'd':
            snake.Dir = "Right";
            break;
            case 'a':
            snake.Dir = "Left";
            break;
            default:
            break;
        }
    }
}
void draw(void) {
    clear();
    cout << "score [" << player.Score << "] | "
         << "time [" << map.Time << "] | "
         << "speed [" << speed << "]" << endl;
    for (int h = 0; h < map.Height; h++) {
        for (int w = 0; w < map.Width; w++) {
            if (h == 0 || h == map.Height-1) {
                cout << "#";
            }else if (w == 0 || w == map.Width-1) {
                cout << "#";
            } else if (h == snake.HeadY && w == snake.HeadX) {
                cout << "O";
            }else if (h == map.FruitY && w == map.FruitX) {
                cout << "$";
            }else {
                bool prented = false;
                for (int i = 0; i <= snake.Tail; i++) {
                    if (snake.TailX[i] == w && snake.TailY[i] == h) {
                        cout << "o";
                        prented = true;
                    }
                }
                if (!prented) {
                    cout << ".";
                }
            }
        }
        cout << endl;
    }
}
void setup(void) {
    map.Width = 40;
    map.Height = 20;
    map.Time = 0;
    generateFruit();

    //-------Difculty
    cout << "Difculty [e - n - h]: ";
    if (true) {
        char d;
        cin >> d;
        setDifculty(d);
    }

    //-------Snake
    snake.HeadX = map.Width/2;
    snake.HeadY = map.Height/2;
    snake.Tail = 0;

    //-------Player
    player.Score = 0;
    player.Lose = false;
}
void generateFruit(void) {
    srand(time(NULL));
    map.FruitX = rand() % (map.Width-2) + 1;
    map.FruitY = rand() % (map.Height-2) + 1;
}
