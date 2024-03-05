#define FRAME_RATE 150

#include <iostream>
#include <thread>
#include <chrono>
#include "keyboard.h" // Incluir el header de control del teclado

using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir = STOP;

const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0;
bool gameOver = false;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width; // Posici�n aleatoria de la fruta
    fruitY = rand() % height;
    score = 0;
}

void Draw() {

    system("cls"); // Limpia la consola
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "|";
            if (i == y && j == x)
                cout << "X "; // A�ade un espacio extra para la serpiente
            else if (i == fruitY && j == fruitX)
                cout << "O "; // A�ade un espacio extra para la fruta
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "x "; // A�ade un espacio extra para la cola
                        print = true;
                    }
                }
                if (!print)
                    cout << "  "; // A�ade dos espacios para las celdas vac�as
            }
            if (j == width - 1)
                cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    cout << "Score: " << score << endl;
}

void Input() {
    if (IsAPressed()) dir = LEFT;
    else if (IsDPressed()) dir = RIGHT;
    else if (IsWPressed()) dir = UP;
    else if (IsSPressed()) dir = DOWN;
}

// A�adir aqu� las variables globales y la inicializaci�n del juego (ver ejemplos anteriores)
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    Setup(); // Inicializar el juego

    bool bGameOver = false;

    while (!bGameOver) {
        Draw(); // Dibujar el tablero y la serpiente
        Input(); // Manejar la entrada del usuario
        Logic(); // Actualizar la l�gica del juego

        //Sleep main thread to control game speed execution
        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_RATE));

        if (gameOver) bGameOver = true; // Actualizar la condici�n de terminaci�n basada en la l�gica del juego
    }

    return 0; // A�adido para corregir el est�ndar de retorno de main.
}